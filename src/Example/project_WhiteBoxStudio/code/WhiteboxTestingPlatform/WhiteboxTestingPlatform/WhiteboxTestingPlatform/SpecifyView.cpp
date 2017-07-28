// SpecifyView.cpp : 实现文件
//

#include "stdafx.h"
#include "mainfrm.h"
#include "ProjectView.h"
#include "Resource.h"
#include "WhiteboxTestingPlatform.h"
#include "SpecifyView.h"
#include "myworkthread.h"
#include "TestUserNewStandard.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNAMIC(CSpecifyView, CDockablePane)

CSpecifyView::CSpecifyView()
{

}

CSpecifyView::~CSpecifyView()
{
}


BEGIN_MESSAGE_MAP(CSpecifyView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_STANDARD_MENU_NEW, OnNewStandard)
	ON_COMMAND(ID_STANDARD_MENU_UPDATA, OnUpdataStandard)
	ON_COMMAND(ID_STANDARD_MENU_DELETE, OnDeleteStandard)
	ON_COMMAND(ID_STANDARD_MENU_REGET, OnReGetStandard)

	ON_UPDATE_COMMAND_UI(ID_STANDARD_MENU_NEW, &CSpecifyView::OnCanCreateDel)
	ON_UPDATE_COMMAND_UI(ID_STANDARD_MENU_DELETE, &CSpecifyView::OnCanCreateDel)

END_MESSAGE_MAP()

void CSpecifyView::OnCanCreateDel(CCmdUI *pCmdUI)
{
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanMangerProject()==FALSE)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	pCmdUI->Enable(TRUE);
	return;
}
void CSpecifyView::OnNewStandard()
{
	//theApp.m_WorkSpaceWndManger.m_StandardDataModel.NewStandard(_T("345435"));
	CTestUserNewStandard dlg;
	if(dlg.DoModal()==IDOK)
	{
		if(dlg.m_szStandardName.GetLength())
		{
			theApp.m_WorkSpaceWndManger.m_StandardDataModel.NewStandard(tstring(dlg.m_szStandardName.GetBuffer(0)));
			theApp.m_WorkSpaceWndManger.m_StandardDataModel.GetStandardTree(m_wndFileView);
		}else
		{
			AfxMessageBox(_T("请输入合法的"));
		}
	}
	
}
void CSpecifyView::OnDeleteStandard()
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	HTREEITEM item=pWndTree->GetSelectedItem();
	theApp.m_WorkSpaceWndManger.m_StandardDataModel.DelStandard(tstring(pWndTree->GetItemText(item).GetBuffer(0)));
	theApp.m_WorkSpaceWndManger.m_StandardDataModel.GetStandardTree(m_wndFileView);
}

void CSpecifyView::OnReGetStandard()
{

	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	HTREEITEM hSelectedItem = pWndTree->GetSelectedItem();
	if (hSelectedItem == NULL) {
		return;
	}
	TreeIndex *pTreeIndex = (TreeIndex *)pWndTree->GetItemData(hSelectedItem);
	if (!pTreeIndex ){
		return;	
	}

	CStandardSharedData * pData=(CStandardSharedData *)pTreeIndex->pSharedObject;
	if(pData->ReGetObject())
	{
		pData->m_bIsHopeUpdataThirdUi=TRUE;
		pData->m_bIsHopeUpdataUniteUi=TRUE;
	}
	
}
void CSpecifyView::OnUpdataStandard()
{
	theApp.m_WorkSpaceWndManger.m_StandardDataModel.GetStandardTree(m_wndFileView);
}

int CSpecifyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

void CSpecifyView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CSpecifyView::FillFileView()
{
	theApp.m_WorkSpaceWndManger.m_StandardDataModel.GetStandardTree(m_wndFileView);
}

void CSpecifyView::OnContextMenu(CWnd* pWnd, CPoint point)
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
			theApp.GetContextMenuManager()->ShowPopupMenu(IDR_STANDARD_MENU, point.x, point.y, this, TRUE);
		}
	}

	//pWndTree->SetFocus();IDR_PROJECTVIEW_POPUP
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);IDR_PROJECTVIEW_POPUP
}

void CSpecifyView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	//int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	//m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + 0 + 1, rectClient.Width() - 2, rectClient.Height() - 0 - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CSpecifyView::OnFileOpen()
{
	// TODO: 在此处添加命令处理程序代码
	
}

void CSpecifyView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CSpecifyView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}