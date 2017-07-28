// DevUserReportView.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "DevUserReportView.h"
#include "CommonFunc.h"
#include "NewPost.h"

// CDevUserReportView

IMPLEMENT_DYNCREATE(CDevUserReportView, CFormView)

CDevUserReportView::CDevUserReportView()
	: CFormView(CDevUserReportView::IDD)
{
	//m_CurSelTab = 0;
}

CDevUserReportView::~CDevUserReportView()
{
}

void CDevUserReportView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_DATA, m_tabData);
	DDX_Control(pDX, IDC_LIST_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_COMBO_DISPATCH, m_cmbDispatch);
	DDX_Control(pDX, IDC_COMBO_DEVSTATE, m_cmbDevStatus);
}

BEGIN_MESSAGE_MAP(CDevUserReportView, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_DATA, &CDevUserReportView::OnTcnSelchangeTabData)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_REPORT, &CDevUserReportView::OnNMCustomdrawListReport)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_REPORT, &CDevUserReportView::OnLvnColumnclickListReport)
	//ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_REPORT, &CDevUserReportView::OnLvnColumnclickListReport)

	ON_NOTIFY(HDN_ITEMCLICK, 0, &CDevUserReportView::OnHdnItemclickListReport)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_REPORT, &CDevUserReportView::OnLvnItemchangedListReport)
	ON_CBN_SELCHANGE(IDC_COMBO_DISPATCH, &CDevUserReportView::OnCbnSelchangeComboDispatch)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVSTATE, &CDevUserReportView::OnCbnSelchangeComboDevstate)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_OBJ_REGET, OnReGetObject)
	ON_COMMAND(ID_OBJ_RELEASE_LOCK, OnReleaseObjectLock)
	ON_COMMAND(ID_OBJ_GETLOCK, OnGetObjectLock)
	ON_UPDATE_COMMAND_UI(ID_OBJ_REGET, OnCanEdit)
	ON_UPDATE_COMMAND_UI(ID_OBJ_RELEASE_LOCK, OnCanEdit)
	ON_UPDATE_COMMAND_UI(ID_OBJ_GETLOCK, OnCanEdit)
	ON_BN_CLICKED(IDC_SUBMIT, &CDevUserReportView::OnBnClickedSubmit)
	ON_BN_CLICKED(IDC_REFRESH, &CDevUserReportView::OnBnClickedRefresh)
	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &CDevUserReportView::OnHdnItemdblclickListReport)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_REPORT, &CDevUserReportView::OnNMDblclkListReport)
	ON_BN_CLICKED(IDC_SENDPOST, &CDevUserReportView::OnBnClickedSendpost)
	ON_BN_CLICKED(IDC_EDITPOST, &CDevUserReportView::OnBnClickedEditpost)
END_MESSAGE_MAP()

void CDevUserReportView::OnCanEdit(CCmdUI *pCmdUI)
{
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditProject(m_pShareData->m_ProjectState.m_Data))
	{
		pCmdUI->Enable(TRUE);
		return;
	}

	pCmdUI->Enable(FALSE);
	return;
}

// CDevUserReportView 诊断

#ifdef _DEBUG
void CDevUserReportView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDevUserReportView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CDevUserReportView::ProjectChange(BOOL bToTop)
{
	if(bToTop)
	{
		//m_pShareData->GetObject();
		//UpdataUi();
		//((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== 项目变更自动加载标准数据 ========\r\n"));
	}else{
		//if (m_pShareData->m_bManualReportSaved){
		//	m_pShareData->m_bComplateReportUpdated = TRUE;

		//	m_pShareData->m_bManualReportSaved = FALSE;
		//	m_pShareData->UpdataReportObject();
		//	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== 项目变更自动保存报表数据 ========\r\n"), SB_BOTTOM);
		//}
	}
}
// CDevUserReportView 消息处理程序

void CDevUserReportView::InitTab()
{
	/*m_tabData.InsertItem(0, _T("测试信息"));
	m_tabData.InsertItem(1, _T("反馈信息"));
	m_tabData.InsertItem(2, _T("代码定位"));

	//创建两个对话框
	m_dataDlg1.Create(IDD_DEVUSER_REPORT_VIEW_1, &m_tabData);
	m_dataDlg2.Create(IDD_DEVUSER_REPORT_VIEW_2, &m_tabData);
	m_CodeViewDlg.Create(IDD_CODEVIEW,&m_tabData);*/

	m_tabData.AddPage(_T("测试信息"),&m_dataDlg1,IDD_DEVUSER_REPORT_VIEW_1);
	m_tabData.AddPage(_T("交流反馈"),&m_dataDlg2,IDD_DEVUSER_REPORT_VIEW_2);
	m_tabData.AddPage(_T("问题定位"),&m_CodeViewDlg,IDD_CODEVIEW_DLG);
	m_tabData.Show();

}

void CDevUserReportView::InitialListCtrlHeadData()
{
	m_lstReport.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lstReport.InsertColumn(0,_T("编号"));
	m_lstReport.InsertColumn(1,_T("描述"));
	m_lstReport.InsertColumn(2,_T("问题位置"));
	m_lstReport.InsertColumn(3,_T("行号"));
	m_lstReport.InsertColumn(4,_T("建议"));
	m_lstReport.InsertColumn(5,_T("UID"));
	m_lstReport.InsertColumn(6,_T("TID"));
	m_lstReport.InsertColumn(7,_T("数组序号"));
	m_lstReport.InsertColumn(8,_T("报告等级"));
	m_lstReport.InsertColumn(9,_T("人员指派"));
	m_lstReport.InsertColumn(10,_T("反馈状态"));
	m_lstReport.InsertColumn(11,_T("来源"));
	m_lstReport.InsertColumn(12,_T("创建时间"));
	m_lstReport.InsertColumn(13,_T("修改时间"));

	m_lstReport.SetColumnWidth(0, 40);
	m_lstReport.SetColumnWidth(1, 270);
	m_lstReport.SetColumnWidth(2, 170);
	m_lstReport.SetColumnWidth(3, 40);
	m_lstReport.SetColumnWidth(4, 0);
	m_lstReport.SetColumnWidth(5, 40);
	m_lstReport.SetColumnWidth(6, 40);
	m_lstReport.SetColumnWidth(7, 0);
	m_lstReport.SetColumnWidth(8, 75);
	m_lstReport.SetColumnWidth(9, 70);
	m_lstReport.SetColumnWidth(10, 65);
	m_lstReport.SetColumnWidth(11, 65);
	m_lstReport.SetColumnWidth(12, 110);
	m_lstReport.SetColumnWidth(13, 110);
}


void CDevUserReportView::InitialListCtrlData()
{
	m_lstReport.DeleteAllItems();
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditProject(m_pShareData->m_ProjectState.m_Data)==FALSE)
	{
		return;
	}
	CString sno, sIndex;
	int nCount = m_pShareData->m_Report.m_Data.items.size(), nIndex=1;
	for (int i=0; i<nCount; i++){
		if (m_pShareData->m_Report.m_Data.items[i].szTestState != _T("检查通过")){
			continue;
		}

		sno.Format(_T("%d"), i);
		sIndex.Format(_T("%d"), nIndex++);
		int Pos = m_lstReport.InsertItem(m_lstReport.GetItemCount(), sIndex);

		//统一规范描述
		m_lstReport.SetItemText(Pos, 1, m_pShareData->m_Report.m_Data.items[i].szUniteDesc.c_str());

		//文件名
		CString sFileName = m_pShareData->m_Report.m_Data.items[i].szModule.c_str();
		//int nPos = sFileName.ReverseFind('(');
		//if (nPos != -1){
		//	m_lstReport.SetItemText(Pos, 2, sFileName.Left(nPos));
		//}
		m_lstReport.SetItemText(Pos, 2, sFileName);
		
		//行号
		CString szErrorCodePosition = m_pShareData->m_Report.m_Data.items[i].szErrorCodePosition.c_str();
		int nPos = szErrorCodePosition.ReverseFind('(');
		if (nPos != -1){
			int nPos2 = szErrorCodePosition.ReverseFind(')');
			if (nPos2 != -1){
				m_lstReport.SetItemText(Pos, 3, szErrorCodePosition.Mid(nPos, nPos2-1));
			}
		}

		//m_lstReport.SetItemText(Pos, 4, m_pShareData->m_Report.m_Data.items[i].szSuggest.c_str());
		m_lstReport.SetItemText(Pos, 5, m_pShareData->m_Report.m_Data.items[i].szUniteStandardErrorNum.c_str());
		m_lstReport.SetItemText(Pos, 6, m_pShareData->m_Report.m_Data.items[i].szThirdStandardErrorNum.c_str());
		m_lstReport.SetItemText(Pos, 7, sno);
		m_lstReport.SetItemText(Pos, 8, m_pShareData->m_Report.m_Data.items[i].szErrorWarning.c_str());

		if ((m_pShareData->m_Report.m_Data.items[i].szProcessUser == _T("") || m_pShareData->m_Report.m_Data.items[i].szProcessUser == _T("未指定"))
			&& m_pShareData->m_WorkSheet.szApplyMan != _T("")){
			m_pShareData->m_Report.m_Data.items[i].szProcessUser = m_pShareData->m_WorkSheet.szApplyMan;
		}else if (m_pShareData->m_Report.m_Data.items[i].szProcessUser == _T("")){
			m_pShareData->m_Report.m_Data.items[i].szProcessUser = _T("未指定");
		}

		m_lstReport.SetItemText(Pos, 9, m_pShareData->m_Report.m_Data.items[i].szProcessUser.c_str());
		m_lstReport.SetItemText(Pos, 10, m_pShareData->m_Report.m_Data.items[i].szDevelopState.c_str());
		m_lstReport.SetItemText(Pos, 11, m_pShareData->m_Report.m_Data.items[i].szTestItemSource.c_str());
		m_lstReport.SetItemText(Pos, 12, m_pShareData->m_Report.m_Data.items[i].szCreateTime.c_str());
		m_lstReport.SetItemText(Pos, 13, m_pShareData->m_Report.m_Data.items[i].szLastEditTime.c_str());
	}
}

BOOL CDevUserReportView::InitDevList()
{
	_tagProjectOwnUser ProjectUserMap;
	tstring sProjectName = m_pShareData->m_pTreeIndex->IndexList[0];
	sProjectName = sProjectName.c_str() + strlen_t(_T("Project_"));
	if (!theApp.m_WorkSpaceWndManger.m_UserDataModel.GetProjectOwnUser(sProjectName, ProjectUserMap)){
		return FALSE;
	}
	m_cmbDispatch.AddString(_T("未指定"));

	map<tstring,_tagProjectOwnUserSet,less<tstring> >::iterator itPos = ProjectUserMap.OwnUserMap.begin();
	for(; itPos!=ProjectUserMap.OwnUserMap.end(); itPos++)
	{

		if ((itPos->second.szUserType == USER_TYPE_DEVELOP)
		||(itPos->second.szUserType == USER_TYPE_ADMIN))
		{
			m_cmbDispatch.AddString(itPos->second.szUserName.c_str());
		}

		
	}
	return TRUE;
}

void CDevUserReportView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	CProjectSharedData *pShareData = (CProjectSharedData *)(((CChildFrame *)GetParentFrame())->m_ProjectIndex.pSharedObject);
	((CChildFrame *)GetParentFrame())->m_ProjectIndex.pViewInterface = this;

	m_pShareData = new CProjectSharedData;
	m_pShareData->m_pTreeIndex = pShareData->m_pTreeIndex;
	//m_pShareData->init();

	InitDevList();

	InitTab();
	InitialListCtrlHeadData();

	//m_pShareData->m_Report.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
	//m_pShareData->m_Report.m_ObjectState.bLock=FALSE;
	//m_pShareData->m_Report.m_ObjectState.nLockTime=0;
	//m_pShareData->m_Report.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;
	//EnableEdit(FALSE);
	//UpdataUi();
	OnReGetObject();
	
		InitialListCtrlData();
	
}

void CDevUserReportView::OnTcnSelchangeTabData(NMHDR *pNMHDR, LRESULT *pResult)
{
	/*m_pDataDlg[m_CurSelTab]->ShowWindow(SW_HIDE);
	m_CurSelTab = m_tabData.GetCurSel();
	m_pDataDlg[m_CurSelTab]->ShowWindow(SW_SHOW);*/

	*pResult = 0;
}

void CDevUserReportView::OnNMCustomdrawListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = CDRF_DODEFAULT;
	NMLVCUSTOMDRAW * lplvdr=(NMLVCUSTOMDRAW*)pNMHDR;
	NMCUSTOMDRAW &nmcd = lplvdr->nmcd;
	switch(lplvdr->nmcd.dwDrawStage)//判断状态
	{
	case CDDS_PREPAINT:
		{
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;
		}
	case CDDS_ITEMPREPAINT://如果为画ITEM之前就要进行颜色的改变
		{
			int nItem = static_cast<int>(lplvdr->nmcd.dwItemSpec);
			CString sIndex = m_lstReport.GetItemText(nItem, 7);
			if (m_pShareData->m_Report.m_Data.items[atol_t(sIndex.GetBuffer(0))].szErrorWarning.find(_T("错误")) != -1){
				lplvdr->clrTextBk = RGB(255, 0, 0);
				*pResult = CDRF_NOTIFYSUBITEMDRAW;	
			}
			if (m_pShareData->m_Report.m_Data.items[atol_t(sIndex.GetBuffer(0))].szErrorWarning.find(_T("警告")) != -1){
				lplvdr->clrTextBk = RGB(255, 0xd7, 0);
				*pResult = CDRF_NOTIFYSUBITEMDRAW;	
			}
		}
		break;
	}
}

void CDevUserReportView::OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	SetRedraw(FALSE);
	m_lstReport.OnLvnColumnclickList1(pNMHDR, pResult);
	SetRedraw(TRUE);
	m_lstReport.Invalidate();
	m_lstReport.UpdateWindow();
	*pResult = 0;
}

void CDevUserReportView::OnHdnItemclickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CDevUserReportView::OnLvnItemchangedListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nItem = pNMItemActivate->iItem;
	if (nItem == -1){
		return;
	}

	int nIndex = atol_t(m_lstReport.GetItemText(nItem, 7).GetBuffer(0));
	m_CodeViewDlg.m_iDataIndex = m_dataDlg1.m_iDataIndex = m_dataDlg2.m_iDataIndex = nIndex;
	m_CodeViewDlg.m_pShareData = m_dataDlg1.m_pShareData = m_dataDlg2.m_pShareData = m_pShareData;
	m_CodeViewDlg.m_szUiName = m_dataDlg1.m_szUiName = m_dataDlg2.m_szUiName = _T("#Dev");

	

	CWnd *pWnd =NULL;

	pWnd = (CWnd *)GetDlgItem(IDC_ERROR_NUM_UNITE);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 5));

	pWnd = (CWnd *)GetDlgItem(IDC_ERROR_NUM_THIRD);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 6));

	pWnd = (CWnd *)GetDlgItem(IDC_ERROR_TYPE);
	pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[nIndex].szErrorType.c_str());
	pWnd = (CWnd *)GetDlgItem(IDC_ERROR_CLASS);
	pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[nIndex].szErrorWarning.c_str());

	//如果有编辑好的描述建议，则设置为编辑好的描述建议
	

	if (m_pShareData->m_Report.m_Data.items[nIndex].szProcessUser == _T("")){
		m_pShareData->m_Report.m_Data.items[nIndex].szProcessUser = _T("未指定");
	}

	m_cmbDispatch.SelectString(0, m_pShareData->m_Report.m_Data.items[nIndex].szProcessUser.c_str());
	m_cmbDevStatus.SelectString(0, m_pShareData->m_Report.m_Data.items[nIndex].szDevelopState.c_str());

	

	if((pNMItemActivate->uOldState==0)&&(pNMItemActivate->uNewState==3))
	{
		int nTab=m_tabData.GetCurSel();
		//m_dataDlg1.UpdataUi();
		
		m_dataDlg1.UpdataUi();
		
		m_dataDlg2.UpdataUi();
		
		m_CodeViewDlg.UpdataUi();
		
	
	}
	
}

void CDevUserReportView::OnCbnSelchangeComboDispatch()
{
	POSITION pos = m_lstReport.GetFirstSelectedItemPosition();
	if (pos == NULL){
		return;
	}

	int nSelectedItem = m_lstReport.GetNextSelectedItem(pos);
	if (nSelectedItem == -1){
		return;
	}

	int nIndex = atol_t(m_lstReport.GetItemText(nSelectedItem, 7).GetBuffer(0));

	CString sUserDispatch;
	m_cmbDispatch.GetWindowText(sUserDispatch);
	m_pShareData->m_Report.m_Data.items[nIndex].szProcessUser = sUserDispatch.GetBuffer(0);
	m_pShareData->m_Report.m_Data.items[nIndex].szLastEditTime = theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetCurTime();

	m_lstReport.SetItemText(nSelectedItem, 9, sUserDispatch);
}

void CDevUserReportView::OnCbnSelchangeComboDevstate()
{
	POSITION pos = m_lstReport.GetFirstSelectedItemPosition();
	if (pos == NULL){
		return;
	}

	int nSelectedItem = m_lstReport.GetNextSelectedItem(pos);
	if (nSelectedItem == -1){
		return;
	}

	int nIndex = atol_t(m_lstReport.GetItemText(nSelectedItem, 7).GetBuffer(0));

	CString sDevStatus;
	m_cmbDevStatus.GetWindowText(sDevStatus);
	m_pShareData->m_Report.m_Data.items[nIndex].szDevelopState = sDevStatus.GetBuffer(0);
	m_pShareData->m_Report.m_Data.items[nIndex].szLastEditTime = theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetCurTime();

	m_lstReport.SetItemText(nSelectedItem, 10, sDevStatus);
}

void CDevUserReportView::EnableEdit(BOOL bCanEdit)
{
	m_bCanEdit=bCanEdit;
	GetDlgItem(IDC_SUBMIT)->EnableWindow(m_bCanEdit);
	GetDlgItem(IDC_SENDPOST)->EnableWindow(m_bCanEdit);
	GetDlgItem(IDC_EDITPOST)->EnableWindow(m_bCanEdit);
}

void CDevUserReportView::UpDataObjectUiState()
{
	if(m_pShareData->m_Report.m_ObjectState.bLock)
	{
		if(m_pShareData->m_Report.m_ObjectState.szLockUser==
			theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()+_T("#Dev"))
		{
			//被本人锁定
			((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_WRITED,CString(_T("已获取对象锁定可以编辑")));
		}else
		{
			//被别人锁定　红色
			CString szMsg=CString(_T("对象已被["))+CString(m_pShareData->m_Report.m_ObjectState.szLockUser.c_str())+CString(_T("]锁定，暂时无法编辑"));
			((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_READONLY,szMsg);

		}
	}else
	{
		//灰色，没有用户锁定
		((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_OK,CString(_T("对象无人锁定，可申请锁定")));
	}

}

BOOL CDevUserReportView::UpdataUi()
{
	UpDataObjectUiState();
	InitialListCtrlData();

	return TRUE;
}

void  CDevUserReportView::OnReGetObject()
{
	m_pShareData->m_Report.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()+_T("#Dev");
	m_pShareData->m_Report.m_ObjectState.bLock=FALSE;
	m_pShareData->m_Report.m_ObjectState.nLockTime=0;
	m_pShareData->m_Report.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;
	m_pShareData->ReGetObject();

	EnableEdit(FALSE);

	UpdataUi();
	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== 重新获取报表　刷新报表数据 ========\r\n"));
}

void  CDevUserReportView::OnReleaseObjectLock()
{
	OnReGetObject();
	EnableEdit(FALSE);

	UpdataUi();
}

void  CDevUserReportView::OnGetObjectLock()
{
	m_pShareData->m_Report.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()+_T("#Dev");
	m_pShareData->m_Report.m_ObjectState.bLock=TRUE;
	m_pShareData->m_Report.m_ObjectState.nLockTime=20*60*1000;
	m_pShareData->m_Report.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;
	if(m_pShareData->ReGetObject())
	{
		if(m_pShareData->m_Report.m_ObjectState.bLock)
		{
			if(m_pShareData->m_Report.m_ObjectState.szLockUser==
				theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()+_T("#Dev"))
			{
				//申请锁定成功
				EnableEdit(TRUE);
			}else
			{
				//已被其它用户锁定
				EnableEdit(FALSE);
			}
		}else
		{
			//没有用户锁定对象
			EnableEdit(FALSE);
		}
		UpdataUi();
	}else
	{
		EnableEdit(FALSE);
	}
}

void CDevUserReportView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_OBJECT_LOCK_MENU, point.x, point.y, this, TRUE);
	return;
}

void CDevUserReportView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	__super::OnActivateView(bActivate, pActivateView, pDeactiveView);
	if(bActivate)
	{
		UpDataObjectUiState();
		//if(m_pShareData->m_bIsHopeUpdataThirdUi)
		//{
		//	//m_pShareData->GetObject();
		//	UpdataUi();
		//	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== 第三方标准管理器 页面激活自动刷新标准数据 ========\r\n"));
		//	m_pShareData->m_bIsHopeUpdataThirdUi=FALSE;
		//}

	}else
	{
		//m_pShareData->UpdataObject();
		//((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== 页面失去焦点自动保存标准数据 ========\r\n"));
	}
}

void CDevUserReportView::OnBnClickedSubmit()
{
	m_pShareData->UpdataReportObject();
	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== 开发反馈报告数据已经提交 ========\r\n"), SB_BOTTOM);
	InitialListCtrlData();
	OnReleaseObjectLock();
}

void CDevUserReportView::OnBnClickedRefresh()
{
	//m_pShareData->GetReportObject();
	//m_pShareData->GetProjectState();
	OnReGetObject();
	//InitialListCtrlData();
}

void CDevUserReportView::OnHdnItemdblclickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//m_CodeViewDlg.ShowCode()
	//m_tabData.SetCurSelFromID(IDD_CODEVIEW);
	*pResult = 0;
}

void CDevUserReportView::OnNMDblclkListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	int nItem = pNMItemActivate->iItem;
	if (nItem == -1){
		return;
	}

	int nIndex = atol_t(m_lstReport.GetItemText(nItem, 7).GetBuffer(0));
	m_CodeViewDlg.m_iDataIndex = m_dataDlg1.m_iDataIndex = m_dataDlg2.m_iDataIndex = nIndex;
	m_CodeViewDlg.m_pShareData = m_dataDlg1.m_pShareData = m_dataDlg2.m_pShareData = m_pShareData;
	m_CodeViewDlg.m_szUiName = m_dataDlg1.m_szUiName = m_dataDlg2.m_szUiName = _T("#Dev");

	m_tabData.SetCurSelFromID(IDD_CODEVIEW_DLG);
	m_CodeViewDlg.UpdataUi();
	*pResult = 0;
}

void CDevUserReportView::OnBnClickedSendpost()
{
	CNewPost NewPost;
	if (NewPost.DoModal() != IDOK){
		return;
	}

	REPORT_ITEM post;
	post.szUniteDesc = NewPost.m_sSubject;
	post.szUniteSuggest = NewPost.m_sContent;
	post.szModule = NewPost.m_sPosition;
	post.szTestItemSource = _T("人工检查");
	post.szTestState = _T("检查通过");
	post.szCreateTime = post.szLastEditTime = theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetCurTime();
	m_pShareData->m_Report.m_Data.items.push_back(post);

	//add to grid
	InitialListCtrlData();
}

void CDevUserReportView::OnBnClickedEditpost()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CNewPost EditPost;
	POSITION pos=m_lstReport.GetFirstSelectedItemPosition();
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("请选择要编辑的元素"));
		return;
	}
	int   nItem   =   m_lstReport.GetNextSelectedItem(pos);  
	int nIndex = atol_t(m_lstReport.GetItemText(nItem, 7).GetBuffer(0));

	if(strstr_t(m_pShareData->m_Report.m_Data.items[nIndex].szTestItemSource.c_str(),_T("人工检查-"))&&
		strstr_t(m_pShareData->m_Report.m_Data.items[nIndex].szTestItemSource.c_str(),
		theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName().c_str())
		)
	{
		EditPost.m_sSubject=m_pShareData->m_Report.m_Data.items[nIndex].szUniteDesc.c_str();
		EditPost.m_sContent=m_pShareData->m_Report.m_Data.items[nIndex].szUniteSuggest.c_str();
		EditPost.m_sPosition=m_pShareData->m_Report.m_Data.items[nIndex].szModule.c_str();
		//EditPost.SetWindowText(_T("编辑报告"));
		EditPost.m_szTitle=_T("编辑问题");
		if (EditPost.DoModal() != IDOK){
			return;
		}

		REPORT_ITEM post;
		m_pShareData->m_Report.m_Data.items[nIndex].szUniteDesc = EditPost.m_sSubject;
		m_pShareData->m_Report.m_Data.items[nIndex].szUniteSuggest = EditPost.m_sContent;
		m_pShareData->m_Report.m_Data.items[nIndex].szModule = EditPost.m_sPosition;
		m_lstReport.SetItemText(nItem,1,EditPost.m_sSubject);
		m_lstReport.SetItemText(nItem,2,EditPost.m_sPosition);
		tstring szTestItemSource=_T("人工检查-")+theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
		m_pShareData->m_Report.m_Data.items[nIndex].szTestItemSource = szTestItemSource;
		m_lstReport.SetItemText(nItem,11,szTestItemSource.c_str());
		

		m_pShareData->m_Report.m_Data.items[nIndex].szTestState = _T("检查通过");
		m_pShareData->m_Report.m_Data.items[nIndex].szLastEditTime = theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetCurTime();
		m_lstReport.SetItemText(nItem,13,m_pShareData->m_Report.m_Data.items[nIndex].szLastEditTime.c_str());
		//m_pShareData->m_Report.m_Data.items.push_back(post);
	}else
	{
		AfxMessageBox(_T("非法编辑,只允许编辑人工检查的问题"));
	}
}
