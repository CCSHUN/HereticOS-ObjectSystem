
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"

#include "MainFrm.h"

#include "ChildFrm.h"
#include "WhiteboxTestingPlatformDoc.h"
#include "TestingTaskDoc.h"
#include "TestingTaskConfigDoc.h"
#include "ReportDoc.h"

#include "WhiteboxTestingPlatformView.h"
#include "TestingTaskView.h"
#include "TestingTaskConfigView.h"
#include "ReportView.h"
#include "myworkthread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_COMMAND_RANGE(ID_TEST_001, ID_TEST_010, &CMainFrame::OnApplicationTest)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_FILE_NEW, &CMainFrame::OnFileNew)
	ON_WM_CLOSE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2005);

	m_pFloatWnd = NULL;
	m_bInit=FALSE;
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{

	tstring szDocTitle;
	

	if ((GetStyle() & FWS_ADDTOTITLE) == 0)
		return;     // leave it alone!



	CMDIChildWnd* pActiveChild = NULL;
	LPCTSTR lpstrTitle = NULL;
	CDocument* pDocument = GetActiveDocument();
	//lpstrTitle = pDocument->GetTitle();
	if (bAddToTitle &&
		(pActiveChild = MDIGetActive()) != NULL &&
		(pActiveChild->GetStyle() & WS_MAXIMIZE) == 0 &&
		(pDocument != NULL ||
		(pDocument = pActiveChild->GetActiveDocument()) != NULL))
	{
		//UpdateFrameTitleForDocument(pDocument->GetTitle());
		lpstrTitle = pDocument->GetTitle();
	}
	else
	{
		
		CString strTitle;

		if (pActiveChild != NULL &&
			(pActiveChild->GetStyle() & WS_MAXIMIZE) == 0)
		{
			strTitle = pActiveChild->GetTitle();
			if (!strTitle.IsEmpty())
				lpstrTitle = strTitle;
		}
		//UpdateFrameTitleForDocument(lpstrTitle);
	}
	szDocTitle+=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginUserType()+_T("-");
	szDocTitle+=_T("[")+theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()+_T("] doc [");

	if(lpstrTitle)
	{
		szDocTitle+=lpstrTitle;
	}else
	{
		 //CMDIFrameWnd::OnUpdateFrameTitle(bAddToTitle);
		 return;
	}
	
	szDocTitle+=_T("]");
	SetWindowText(szDocTitle.c_str());
	//CMDIFrameWnd::OnUpdateFrameTitle(FALSE);
	//UpdateFrameTitleForDocument(szDocTitle.c_str());

}
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);
	EnableMDITabs(TRUE,FALSE,CMFCTabCtrl::LOCATION_TOP,FALSE,CMFCTabCtrl::STYLE_3D_ROUNDED,FALSE,FALSE);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ROUNDED; // 其他可用样式...
	mdiTabParams.m_bActiveTabCloseButton = FALSE;      // 设置为 FALSE 会将关闭按钮放置在选项卡区域的右侧
	mdiTabParams.m_bTabIcons = FALSE;    // 设置为 TRUE 将在 MDI 选项卡上启用文档图标
	mdiTabParams.m_bAutoColor = FALSE;    // 设置为 FALSE 将禁用 MDI 选项卡的自动着色
	mdiTabParams.m_bDocumentMenu = FALSE; // 在选项卡区域的右边缘启用文档菜单
	mdiTabParams.m_bEnableTabSwap=FALSE;
	mdiTabParams.m_bTabCloseButton=FALSE;
	//EnableMDITabbedGroups(TRUE, mdiTabParams);
	//EnableMDITabs(TRUE,FALSE,CMFCTabCtrl::LOCATION_TOP,FALSE,CMFCTabCtrl::STYLE_3D_ROUNDED,FALSE,FALSE);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);


	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	/*if (!m_wndToolBar.CreateEx(this, / *TBSTYLE_FLAT* /TBSTYLE_TRANSPARENT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_RIGHT / *| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC* /) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME_256))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}*/

	//m_wndToolBar.Create(IDD_FLOATWND, this);
	//m_wndToolBar.Create(this,IDD_FLOATWND,WS_CHILD|CBRS_TOP,AFX_IDW_STATUS_BAR);
	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	//m_wndToolBar.SetWindowText(strToolBarName);

	//
	//ASSERT(bNameValid);
	////m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);

	// //允许用户定义的工具栏操作:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	/*if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));*/

	// TODO: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	//DockPane(&m_wndToolBar);

	//CRect rect;
	//m_wndToolBar.GetItemRect(1,&rect);
	//m_edit.Create(WS_CHILD|WS_VISIBLE,rect,&m_wndToolBar,33333); 

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 加载菜单项图像(不在任何标准工具栏上):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// 创建停靠窗口
	if (!CreateDockingWindows())
	{
		TRACE0("未能创建停靠窗口\n");
		return -1;
	}

	//m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	
	m_SpecifyManager.EnableDocking(CBRS_ALIGN_ANY);
	
	m_wndProjectView.EnableDocking(CBRS_ALIGN_ANY);
	
	m_MsgManager.EnableDocking(CBRS_ALIGN_ANY);

	DockPane(&m_wndProjectView);

	

	CDockablePane* pTabbedBar = NULL;
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanMangerProject())
	{
		m_AdminTreeView.EnableDocking(CBRS_ALIGN_ANY);
		m_AdminTreeView.AttachToTabWnd(&m_wndProjectView, DM_SHOW, TRUE, &pTabbedBar);
	}

	if(pTabbedBar==NULL)
	{
		pTabbedBar=&m_wndProjectView;
	}

	m_SpecifyManager.AttachToTabWnd(pTabbedBar, DM_SHOW, TRUE, &pTabbedBar);
	m_MsgManager.AttachToTabWnd(pTabbedBar, DM_SHOW, TRUE, &pTabbedBar);


	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	//m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndProperties);

	// 启用增强的窗口管理对话框
	EnableWindowsDialog(ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE);

	// 启用工具栏和停靠窗口菜单替换
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 启用快速(按住 Alt 拖动)工具栏自定义
	//CMFCToolBar::EnableQuickCustomization();

	//if (CMFCToolBar::GetUserImages() == NULL)
	//{
	//	// 加载用户定义的工具栏图像
	//	if (m_UserImages.Load(_T(".\\UserImages.bmp")))
	//	{
	//		m_UserImages.SetImageSize(CSize(16, 16), FALSE);
	//		CMFCToolBar::SetUserImages(&m_UserImages);
	//	}
	//}

	// 启用菜单个性化(最近使用的命令)
	// TODO: 定义您自己的基本命令，确保每个下拉菜单至少有一个基本命令。
	//CList<UINT, UINT> lstBasicCommands;

	//lstBasicCommands.AddTail(ID_FILE_NEW);
	//lstBasicCommands.AddTail(ID_FILE_OPEN);
	//lstBasicCommands.AddTail(ID_FILE_SAVE);
	//lstBasicCommands.AddTail(ID_FILE_PRINT);
	//lstBasicCommands.AddTail(ID_APP_EXIT);
	//lstBasicCommands.AddTail(ID_EDIT_CUT);
	//lstBasicCommands.AddTail(ID_EDIT_PASTE);
	//lstBasicCommands.AddTail(ID_EDIT_UNDO);
	//lstBasicCommands.AddTail(ID_APP_ABOUT);
	//lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	//lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	//lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
	//lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
	//lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
	//lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);


	//lstBasicCommands.AddTail(ID_TEST_001);
	//lstBasicCommands.AddTail(ID_TEST_002);

	//CMFCToolBar::SetBasicCommands(lstBasicCommands);

	m_pFloatWnd = new CFloatWnd(&m_wndMenuBar);
	m_pFloatWnd->Create(IDD_FLOATWND, &m_wndMenuBar);
	unsigned int nWinLen=250;
	RECT MenuBarRect;
	this->GetWindowRect(&MenuBarRect);
	unsigned int nStateWndLeft=MenuBarRect.right-MenuBarRect.left-nWinLen;
	RECT pos={nStateWndLeft,0,
		MenuBarRect.right-2,MenuBarRect.bottom-MenuBarRect.top};

	m_pFloatWnd->MoveWindow(&pos,TRUE);
	m_pFloatWnd->ShowWindow(SW_SHOW);

	RECT pos1={300,0,
		nStateWndLeft-10,MenuBarRect.bottom-MenuBarRect.top};
	m_AddressNavigate.Create(IDD_ADDR_NAVIGATE,&m_wndMenuBar);
	m_AddressNavigate.MoveWindow(&pos1,TRUE);
	m_AddressNavigate.ShowWindow(SW_SHOW);
	//m_AddressNavigate.OnInitDialog();



	//pFloatWnd->OnUpdateTransparent(iTransparent);

	
	m_bInit=TRUE;

	return 0;
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CMyMDIFrameWndEx::OnSize(nType, cx, cy);
	if(m_bInit)
	{
		unsigned int nWinLen=250;
		RECT MenuBarRect;
		

		if(m_AddressNavigate.GetSafeHwnd())
		{
			m_AddressNavigate.UpDataSize();
		}
		if(m_wndMenuBar.GetSafeHwnd()&&m_pFloatWnd->GetSafeHwnd())
		{
			m_wndMenuBar.GetWindowRect(&MenuBarRect);
			RECT pos={MenuBarRect.right-MenuBarRect.left-nWinLen,0,
				MenuBarRect.right-MenuBarRect.left-2,MenuBarRect.bottom-MenuBarRect.top};

			m_pFloatWnd->MoveWindow(&pos,TRUE);
			//m_pFloatWnd->ShowWindow(SW_SHOW);
		}
	}
	
}

void CMainFrame::WriteStringToOutputWnd(const CString &sInfo, int nSB_POSITION, BOOL bResetContent)
{
	__try
	{
		if(m_wndOutput.GetSafeHwnd()!=NULL)
		{
			m_wndOutput.WriteString(sInfo, nSB_POSITION, bResetContent);
		}
		
	}
	__except(0)
	{
		
	}
}

void CMainFrame::SetObjectStatus(int nDocStatus, const CString &sDec)
{
	m_pFloatWnd->SetStatus(nDocStatus, sDec);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	//m_SpecifyManager;

#define ID_VIEW_SPECIFY  8898
	if (!m_SpecifyManager.Create(_T("标准管理"), this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_SPECIFY, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“项目视图”窗口\n");
		return FALSE; // 未能创建
	}
#define ID_VIEW_ADMIN  8899
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanMangerProject())
	{
		if (!m_AdminTreeView.Create(_T("系统管理"), this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_ADMIN, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
		{
			TRACE0("未能创建“系统管理”窗口\n");
			return FALSE; // 未能创建
		}
	}

#define ID_VIEW_MSG  8900
	//if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanMangerProject())
	{
		if (!m_MsgManager.Create(_T("消息管理"), this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_MSG, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
		{
			TRACE0("未能创建“消息管理”窗口\n");
			return FALSE; // 未能创建
		}
	}
	// 创建类视图
	/*CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“类视图”窗口\n");
		return FALSE; // 未能创建
	}

	// 创建文件视图
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“文件视图”窗口\n");
		return FALSE; // 未能创建
	}*/

#define ID_VIEW_PROJECTVIEW  8901

	// 创建项目视图
	CString strProjectView;
	bNameValid = strProjectView.LoadString(IDS_PROJECT_VIEW);
	ASSERT(bNameValid);
	if (!m_wndProjectView.Create(strProjectView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROJECTVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“项目视图”窗口\n");
		return FALSE; // 未能创建
	}

	// 创建输出窗口
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}

	// 创建属性窗口
	/*CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“属性”窗口\n");
		return FALSE; // 未能创建
	}*/

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	/*HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);*/

	HICON hProjectViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProjectView.SetIcon(hProjectViewIcon, FALSE);

	HICON hSpecifyViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_SpecifyManager.SetIcon(hProjectViewIcon, FALSE);

	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanMangerProject())
	{
		HICON hAdminViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
		m_AdminTreeView.SetIcon(hAdminViewIcon, FALSE);
	}


	HICON hMsgViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_MsgManager.SetIcon(hMsgViewIcon, FALSE);


	/*HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);*/

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	/*HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);*/

	UpdateMDITabbedBarsIcons();
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

void CMainFrame::UpdateTabs()
{
	m_wndClientArea.GetMDITabs().RemoveAllTabs();
	//m_wndClientArea.UpdateTabs();
}
LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	return lres;
}
UINT nNum=0;


void CMainFrame::OnApplicationTest(UINT id)
{
	switch(id)
	{
	case ID_TEST_001:
		//CMFCTabCtrl & Tabs=m_wndClientArea.GetMDITabs();
		//m_wndClientArea.GetMDITabs().RemoveAllTabs();
		gpObjectSystem=&gSoapObjectSystem;
		break;
	case ID_TEST_002:
		m_wndClientArea.UpdateTabs();
		break;
	}
}
	
void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	//MessageBox(_T("1221334"), _T("iop"), MB_OK);
	//CMFCBaseTabCtrl * pTabCtl=(CMFCBaseTabCtrl *)this;
	//pTabCtl->m_bAutoDestroyWindow=TRUE;
	

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		if(nNum>=1)
		{
			//if(GetMDITabs().GetTabsNum()>=1)
			{
				
			}
		}
		nNum++;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;
	
	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

//可以对CxChildFrame/CxView再进行抽象出来作为形式参数出现
int CMainFrame::CreateNewView()
{
	CChildFrame* pHtmlChild=new CChildFrame();//use CRuntimeClass* is also OK

	CReportDoc* pDoc = (CReportDoc*)GetActiveDocument();
	ASSERT_VALID(pDoc);

	CMultiDocTemplate* pTemplate=(CMultiDocTemplate*)(pDoc->GetDocTemplate());
	ASSERT_VALID(pTemplate);

	CCreateContext context;
	context.m_pCurrentDoc = pDoc;// use existing document
	context.m_pCurrentFrame = pHtmlChild;// new child frame to be upon
	context.m_pNewViewClass = RUNTIME_CLASS(CReportView);// new view to be created
	context.m_pNewDocTemplate = pTemplate;// use existing document
	context.m_pLastView = NULL;// no 

	if (!pHtmlChild->LoadFrame(IDI_CLASS_VIEW, WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE, this, &context)) 
	{
		TRACE0("Warning: Couldn't load frame window!\n");
		return -1;
	}
	//pHtmlChild->ShowWindow(SW_SHOWMAXIMIZED);
	pHtmlChild->InitialUpdateFrame(pDoc, TRUE);
	pTemplate->InitialUpdateFrame(pHtmlChild,pDoc,TRUE);

	//it worked!
	return 0;
}

LRESULT CMainFrame::OnMoveTabComplete(WPARAM wp, LPARAM lp)
{

	return 0;
}
void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 基类将执行真正的工作

	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// 为所有用户工具栏启用自定义按钮
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnFileNew()
{
	
}

void CMainFrame::OnClose()
{
	g_bExit = 1;

	CMyMDIFrameWndEx::OnClose();
}
