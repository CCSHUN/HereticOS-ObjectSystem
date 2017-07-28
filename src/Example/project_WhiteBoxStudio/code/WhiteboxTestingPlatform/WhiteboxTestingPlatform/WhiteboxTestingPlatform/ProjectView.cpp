// ProjectView.cpp : 实现文件
//

#include "stdafx.h"
#include "mainfrm.h"
#include "ProjectView.h"
#include "Resource.h"
#include "WhiteboxTestingPlatform.h"
#include "Report.h"
#include "myworkthread.h"
#include "CreateProject.h"
#include "SubProjectManger.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif




// CProjectView

IMPLEMENT_DYNAMIC(CProjectView, CDockablePane)

CProjectView::CProjectView()
{

}

CProjectView::~CProjectView()
{
}

BEGIN_MESSAGE_MAP(CProjectView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_BUILD_REPORT, OnBuildReport)
	ON_COMMAND(ID_REBUILD_REPORT, OnReBuildReport)
	ON_COMMAND(ID_STOP_BUILD, OnStopbuildReport)
	ON_COMMAND(ID_CREATE_PROJECT, OnCreateTestingProject)
	ON_COMMAND(ID_CREATE_DIRECTORY, OnCreateDirectory)
	ON_COMMAND(ID_CREATE_TASK, OnCreateSubTestingProject)
	ON_COMMAND(ID_PROJECTVIEW_DEL, OnProjectDel)
	ON_COMMAND(ID_GET_NODEPATH, OnGetNodePath)

	ON_COMMAND(ID_PROJECT_UNLOCK, UnLockProject)
	ON_COMMAND(ID_PROJECTTREE_REGET, OnReGetProjectTree)
	ON_COMMAND(ID_PROJECT_MANGER,OnMangerProject)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_UPDATE_COMMAND_UI(ID_BUILD_REPORT, &CProjectView::OnUpdateBuildReport)
	ON_UPDATE_COMMAND_UI(ID_REBUILD_REPORT, &CProjectView::OnUpdateRebuildReport)
	ON_UPDATE_COMMAND_UI(ID_STOP_BUILD, &CProjectView::OnUpdateCanStopbuild)
	ON_UPDATE_COMMAND_UI(ID_PROJECTTREE_REGET, &CProjectView::OnProjectTreeCanReGet)
	ON_UPDATE_COMMAND_UI(ID_CREATE_PROJECT, &CProjectView::OnUpdateCreateProject)
	ON_UPDATE_COMMAND_UI(ID_CREATE_TASK, &CProjectView::OnUpdateCreateSubProject)
	ON_UPDATE_COMMAND_UI(ID_CREATE_DIRECTORY, &CProjectView::OnUpdateCreateDirectory)
	ON_UPDATE_COMMAND_UI(ID_PROJECTVIEW_DEL, OnCanDel)
	ON_UPDATE_COMMAND_UI(ID_PROJECT_UNLOCK,OnCanUnLockSubProject)
	ON_UPDATE_COMMAND_UI(ID_PROJECT_MANGER,OnProjectMangerCanEdit)
	
END_MESSAGE_MAP()


int CProjectView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("未能创建文件视图\n");
		return -1;      // 未能创建
	}

	// 加载视图图像:
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	/*m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE / * 已锁定* /);

	//OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);*/

	// 填入一些静态树视图数据(此处只需填入虚拟代码，而不是复杂的数据)
	FillFileView();
	AdjustLayout();

	return 0;
}

void CProjectView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CProjectView::FillFileView()
{
	theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectTree(m_wndFileView);
}

void CProjectView::OnGetNodePath()
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		return;
	}

	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex){
		return;	
	}

	tstring sPath = tstring(_T(""));
	for (unsigned int i=0; i<pTreeIndex->IndexList.size(); i++){
		sPath += pTreeIndex->IndexList[i] + _T("\\");
	}

	CCreateProject project;
	project.m_sTitleName = sPath.c_str();
	project.DoModal();
}

void CProjectView::OnProjectDel()
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		return;
	}
	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex){
		return;	
	}

	tstring sNodeName = pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1];
	if (!(sNodeName.find(_T("Project_")) != -1 ||
		sNodeName.find(_T("Directory_")) != -1 ||
		sNodeName.find(_T("ChildTest_")) != -1)){
		return;
	}

	CString sProjectName = pWndTree->GetItemText(hSelectedItem);
	if (sNodeName.find(_T("Project_")) != -1 && pTreeIndex->IndexList.size() ==1){
		theApp.m_WorkSpaceWndManger.m_ProjectDataModel.DelProject(tstring(sProjectName.GetBuffer(0)));
		theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectTree(m_wndFileView);
	}else{
		HTREEITEM hParentItem = m_wndFileView.GetParentItem(hSelectedItem);
		if (hParentItem == NULL){
			return;
		}

		tstring sDirectoryPath = tstring(_T("WhiteBoxTestProject\\"));
		for (unsigned int i=0; i<pTreeIndex->IndexList.size(); i++){
			sDirectoryPath += pTreeIndex->IndexList[i];
			if (i < pTreeIndex->IndexList.size()-1){
				sDirectoryPath += tstring(_T("\\"));
			}
		}
		theApp.m_WorkSpaceWndManger.m_ProjectDataModel.DelSubProject(sDirectoryPath);
		theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectTree(m_wndFileView);
	}
}

void CProjectView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);

			pWndTree->SetFocus();
			theApp.GetContextMenuManager()->ShowPopupMenu(IDR_PROJECTVIEW_POPUP, point.x, point.y, this, TRUE);
		}
	}

	//pWndTree->SetFocus();IDR_PROJECTVIEW_POPUP
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);IDR_PROJECTVIEW_POPUP
}

void CProjectView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = 0;//m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	//m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CProjectView::OnCreateTestingProject()
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		return;
	}

	CString sItemName = pWndTree->GetItemText(hSelectedItem);
	if (sItemName != _T("所有项目")){
		return;	
	}

	CCreateProject project;
	project.m_sTitleName = _T("创建项目");
	if (project.DoModal() != IDOK){
		return;
	}

	theApp.m_WorkSpaceWndManger.m_ProjectDataModel.NewProject(tstring(project.m_sName.GetBuffer(0)));
	theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectTree(m_wndFileView);
}

void CProjectView::OnMangerProject()
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		return;
	}

	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex){
		return;	
	}

	CSubProjectManger Manger;
	Manger.m_pShareData=(CProjectSharedData *)pTreeIndex->pSharedObject;
	Manger.DoModal();
}

void CProjectView::OnCreateDirectory()
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		return;
	}

	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex){
		return;	
	}

	if (!(pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("Project_")) != -1 || 
		pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("Directory_")) != -1  ||
		pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("ChildTest_")) != -1) ){
			return;
	}

	CCreateProject project;
	project.m_sTitleName = _T("创建目录");
	if (project.DoModal() != IDOK){
		return;
	}

	tstring sPath = tstring(_T("WhiteBoxTestProject\\"));
	for (unsigned int i=0; i<pTreeIndex->IndexList.size(); i++){
		sPath += pTreeIndex->IndexList[i] + _T("\\");
	}
	sPath += tstring(_T("Directory_")) + tstring(project.m_sName.GetBuffer(0));
	theApp.m_WorkSpaceWndManger.m_ProjectDataModel.NewDirectory(sPath);
	theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectTree(m_wndFileView);
}


void CProjectView::OnCreateSubTestingProject()
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		return;
	}

	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex){
		return;	
	}

	if (!(pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("Project_")) != -1 || 
		pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("Directory_")) != -1) ){
			return;
	}

	CCreateProject project;
	project.m_sTitleName = _T("创建子项目");
	if (project.DoModal() != IDOK){
		return;
	}

	tstring sPath = tstring(_T("WhiteBoxTestProject\\"));
	for (unsigned int i=0; i<pTreeIndex->IndexList.size(); i++){
		sPath += pTreeIndex->IndexList[i] + _T("\\");
	}
	sPath += tstring(_T("ChildTest_")) + tstring(project.m_sName.GetBuffer(0));
	theApp.m_WorkSpaceWndManger.m_ProjectDataModel.NewSubProject(sPath);
	theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectTree(m_wndFileView);
}

void CProjectView::OnBuildReport()
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditTest()==FALSE)
	{
		return;
	}

	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		return;
	}

	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex){
		return;	
	}

	if (!(pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("ChildTest_")) != -1 || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("Worksheet")) || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("TestReport")) || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("CheckCfg")))){
			return;
	}

	g_nBuildCount++;

	CReport *pReport = new CReport;
	pReport->m_pShareData = (CProjectSharedData *)pTreeIndex->pSharedObject;
	pReport->SetBuildType(CReport::BUILD_TYPE);
	AddTaskToWorkThread(pReport);
}

void CProjectView::OnReBuildReport()
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditTest()==FALSE)
	{
		return;
	}

	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		return;
	}

	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex){
		return;	
	}

	if (!(pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("ChildTest_")) != -1 || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("Worksheet")) || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("TestReport")) || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("CheckCfg")))){
			return;
	}

	g_nBuildCount++;

	CReport *pReport = new CReport;
	pReport->m_pShareData = (CProjectSharedData *)pTreeIndex->pSharedObject;
	pReport->SetBuildType(CReport::REBUILD_TYPE);
	AddTaskToWorkThread(pReport);
}

void CProjectView::OnFileOpen()
{
	// TODO: 在此处添加命令处理程序代码
}

void CProjectView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CProjectView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}



void CProjectView::OnUpdateCreateDirectory(CCmdUI *pCmdUI)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanMangerProject()==FALSE)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		pCmdUI->Enable(FALSE);
		return;
	}

	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex){
		pCmdUI->Enable(FALSE);
		return;	
	}

	if (pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("Project_")) != -1 || 
		pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("Directory_")) != -1  ||
		pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("ChildTest_")) != -1 ){
		pCmdUI->Enable(TRUE);
		return;
	}

	pCmdUI->Enable(FALSE);
	return;	
}

void CProjectView::OnCanDel(CCmdUI *pCmdUI)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanMangerProject()==FALSE)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		pCmdUI->Enable(FALSE);
		return;
	}
	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);


	if(pTreeIndex==NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	tstring sNodeName = pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1];
	if (!(sNodeName.find(_T("Project_")) != -1 ||
		sNodeName.find(_T("Directory_")) != -1 ||
		sNodeName.find(_T("ChildTest_")) != -1)){
			pCmdUI->Enable(FALSE);
			return;
	}

	pCmdUI->Enable(TRUE);
	return;

}

void CProjectView::OnUpdateCreateSubProject(CCmdUI *pCmdUI)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanMangerProject()==FALSE)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		pCmdUI->Enable(FALSE);
		return;
	}

	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex){
		pCmdUI->Enable(FALSE);
		return;	
	}

	if (pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("Project_")) != -1 || 
		pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("Directory_")) != -1){
			pCmdUI->Enable(TRUE);
			return;
	}

	pCmdUI->Enable(FALSE);
	return;	
}

void CProjectView::OnUpdateCreateProject(CCmdUI *pCmdUI)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanMangerProject()==FALSE)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		pCmdUI->Enable(FALSE);
		return;
	}

	CString sItemName = pWndTree->GetItemText(hSelectedItem);
	if (sItemName == _T("所有项目")){
		pCmdUI->Enable(TRUE);
		return;	
	}

	pCmdUI->Enable(FALSE);
	return;	
}

void CProjectView::OnUpdateBuildReport(CCmdUI *pCmdUI)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditTest()==FALSE)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		pCmdUI->Enable(FALSE);
		return;
	}

	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex){
		pCmdUI->Enable(FALSE);
		return;	
	}

	if (pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("ChildTest_")) != -1 || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("Worksheet")) || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("TestReport")) || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("CheckCfg"))){
			pCmdUI->Enable(g_nBuildCount<=0);
			return;
	}

	pCmdUI->Enable(FALSE);
}

void CProjectView::OnUpdateRebuildReport(CCmdUI *pCmdUI)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditTest()==FALSE)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		pCmdUI->Enable(FALSE);
		return;
	}

	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex){
		pCmdUI->Enable(FALSE);
		return;	
	}

	if (pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("ChildTest_")) != -1 || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("Worksheet")) || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("TestReport")) || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("CheckCfg"))){
			pCmdUI->Enable(g_nBuildCount<=0);
			return;
	}

	pCmdUI->Enable(FALSE);
}
void CProjectView::OnUpdateCanStopbuild(CCmdUI *pCmdUI)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditTest()==FALSE)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		pCmdUI->Enable(FALSE);
		return;
	}

	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex){
		pCmdUI->Enable(FALSE);
		return;	
	}

	if (pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("ChildTest_")) != -1 || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("Worksheet")) || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("TestReport")) || 
		!pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].compare(_T("CheckCfg"))){
			pCmdUI->Enable(g_nBuildCount>0);
			return;
	}

	pCmdUI->Enable(FALSE);
}
void CProjectView::OnProjectTreeCanReGet(CCmdUI *pCmdUI)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	pCmdUI->Enable(TRUE);
}

void CProjectView::UnLockProject()
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		AfxMessageBox(_T("请选定子项目"));
		return;
	}
	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex){
		AfxMessageBox(_T("UnLockProject Fail"));
		return;	
	}
	tstring szPath=theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectWholePath(pTreeIndex);
	CObjectSystemInterface::SYSTEMERROR Error;
	if(gpObjectSystem->ReleaseObjectState(szPath,&Error)==FALSE)
	{
		AfxMessageBox(_T("UnLockProject Fail"));
	}
	
}

void CProjectView::OnProjectMangerCanEdit(CCmdUI *pCmdUI)
{
	OnCanUnLockSubProject(pCmdUI);
}

void CProjectView::OnCanUnLockSubProject(CCmdUI *pCmdUI)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanMangerProject()==FALSE)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		pCmdUI->Enable(FALSE);
		return;
	}

	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex){
		pCmdUI->Enable(FALSE);
		return;	
	}

	if (pTreeIndex->IndexList[pTreeIndex->IndexList.size()-1].find(_T("ChildTest_")) != -1 ){
		pCmdUI->Enable(TRUE);
		return;
	}

	pCmdUI->Enable(FALSE);
	return;	
}

void CProjectView::OnReGetProjectTree()
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;

	BOOL bRet=theApp.m_WorkSpaceWndManger.m_AccessDataModel.UpDataAccessControl();
	if (bRet)
	{
		bRet=theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectTree(m_wndFileView);
		if(bRet)
		{
			return;
		}
	}
	AfxMessageBox(_T("获取项目树失败"));


}



void CProjectView::OnStopbuildReport()
{
	//pCmdUI->Enable(g_nBuildCount<=0);
	g_bStopBuild=TRUE;
}