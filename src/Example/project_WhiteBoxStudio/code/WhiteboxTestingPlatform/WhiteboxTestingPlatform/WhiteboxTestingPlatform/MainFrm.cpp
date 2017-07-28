
// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
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
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);
	EnableMDITabs(TRUE,FALSE,CMFCTabCtrl::LOCATION_TOP,FALSE,CMFCTabCtrl::STYLE_3D_ROUNDED,FALSE,FALSE);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ROUNDED; // ����������ʽ...
	mdiTabParams.m_bActiveTabCloseButton = FALSE;      // ����Ϊ FALSE �Ὣ�رհ�ť������ѡ�������Ҳ�
	mdiTabParams.m_bTabIcons = FALSE;    // ����Ϊ TRUE ���� MDI ѡ��������ĵ�ͼ��
	mdiTabParams.m_bAutoColor = FALSE;    // ����Ϊ FALSE ������ MDI ѡ����Զ���ɫ
	mdiTabParams.m_bDocumentMenu = FALSE; // ��ѡ�������ұ�Ե�����ĵ��˵�
	mdiTabParams.m_bEnableTabSwap=FALSE;
	mdiTabParams.m_bTabCloseButton=FALSE;
	//EnableMDITabbedGroups(TRUE, mdiTabParams);
	//EnableMDITabs(TRUE,FALSE,CMFCTabCtrl::LOCATION_TOP,FALSE,CMFCTabCtrl::STYLE_3D_ROUNDED,FALSE,FALSE);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("δ�ܴ����˵���\n");
		return -1;      // δ�ܴ���
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);


	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	/*if (!m_wndToolBar.CreateEx(this, / *TBSTYLE_FLAT* /TBSTYLE_TRANSPARENT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_RIGHT / *| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC* /) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME_256))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
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

	// //�����û�����Ĺ���������:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	/*if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));*/

	// TODO: �������ϣ���������Ͳ˵�����ͣ������ɾ��������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	//DockPane(&m_wndToolBar);

	//CRect rect;
	//m_wndToolBar.GetItemRect(1,&rect);
	//m_edit.Create(WS_CHILD|WS_VISIBLE,rect,&m_wndToolBar,33333); 

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ���ز˵���ͼ��(�����κα�׼��������):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// ����ͣ������
	if (!CreateDockingWindows())
	{
		TRACE0("δ�ܴ���ͣ������\n");
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

	// ������ǿ�Ĵ��ڹ���Ի���
	EnableWindowsDialog(ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE);

	// ���ù�������ͣ�����ڲ˵��滻
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ���ÿ���(��ס Alt �϶�)�������Զ���
	//CMFCToolBar::EnableQuickCustomization();

	//if (CMFCToolBar::GetUserImages() == NULL)
	//{
	//	// �����û�����Ĺ�����ͼ��
	//	if (m_UserImages.Load(_T(".\\UserImages.bmp")))
	//	{
	//		m_UserImages.SetImageSize(CSize(16, 16), FALSE);
	//		CMFCToolBar::SetUserImages(&m_UserImages);
	//	}
	//}

	// ���ò˵����Ի�(���ʹ�õ�����)
	// TODO: �������Լ��Ļ������ȷ��ÿ�������˵�������һ���������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	//m_SpecifyManager;

#define ID_VIEW_SPECIFY  8898
	if (!m_SpecifyManager.Create(_T("��׼����"), this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_SPECIFY, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ�������Ŀ��ͼ������\n");
		return FALSE; // δ�ܴ���
	}
#define ID_VIEW_ADMIN  8899
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanMangerProject())
	{
		if (!m_AdminTreeView.Create(_T("ϵͳ����"), this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_ADMIN, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
		{
			TRACE0("δ�ܴ�����ϵͳ��������\n");
			return FALSE; // δ�ܴ���
		}
	}

#define ID_VIEW_MSG  8900
	//if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanMangerProject())
	{
		if (!m_MsgManager.Create(_T("��Ϣ����"), this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_MSG, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
		{
			TRACE0("δ�ܴ�������Ϣ��������\n");
			return FALSE; // δ�ܴ���
		}
	}
	// ��������ͼ
	/*CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ���������ͼ������\n");
		return FALSE; // δ�ܴ���
	}

	// �����ļ���ͼ
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������ļ���ͼ������\n");
		return FALSE; // δ�ܴ���
	}*/

#define ID_VIEW_PROJECTVIEW  8901

	// ������Ŀ��ͼ
	CString strProjectView;
	bNameValid = strProjectView.LoadString(IDS_PROJECT_VIEW);
	ASSERT(bNameValid);
	if (!m_wndProjectView.Create(strProjectView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROJECTVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ�������Ŀ��ͼ������\n");
		return FALSE; // δ�ܴ���
	}

	// �����������
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ����������\n");
		return FALSE; // δ�ܴ���
	}

	// �������Դ���
	/*CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ��������ԡ�����\n");
		return FALSE; // δ�ܴ���
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

// CMainFrame ���

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


// CMainFrame ��Ϣ�������

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
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

//���Զ�CxChildFrame/CxView�ٽ��г��������Ϊ��ʽ��������
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
	// ���ཫִ�������Ĺ���

	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// Ϊ�����û������������Զ��尴ť
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
