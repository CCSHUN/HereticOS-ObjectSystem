
// WhiteboxTestingPlatform.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "WhiteboxTestingPlatform.h"
#include "MainFrm.h"
#include "myworkthread.h"

#include "ChildFrm.h"
#include "WhiteboxTestingPlatformDoc.h"
#include "TestingTaskDoc.h"
#include "TestingTaskConfigDoc.h"
#include "ReportDoc.h"

#include "WhiteboxTestingPlatformView.h"
#include "TestingTaskView.h"
#include "TestingTaskConfigView.h"
#include "ReportView.h"
#include "LogoninDlg.h"
#include "MainWindow.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString		gCols[100] = 
{
	_T(""), _T("A"), _T("B"), _T("C"), _T("D"), 
	_T("E"), _T("F"), _T("G"), _T("H"), _T("I"), 
	_T("J"), _T("K"), _T("L"), _T("M"), _T("N"), 
	_T("O"), _T("P"), _T("Q"), _T("R"), _T("S"), 
	_T("T"), _T("U"), _T("V"), _T("W"), _T("X"), 
	_T("Y"), _T("Z"), _T("AA"), _T("AB"), _T("AC"),
	_T("AD"), _T("AE"), _T("AF"), _T("AG"), _T("AH"),
	_T("AI"), _T("AJ"), _T("AK"), _T("AL"), _T("AM"),
	_T("AN"), _T("AO"), _T("AP"), _T("AQ"), _T("AR"),
	_T("AS"), _T("AT"), _T("AU"), _T("AV"), _T("AW"),

	_T("AX"), _T("AY"), _T("AZ"), _T("BA"), _T("BB"), 
	_T("BC"), _T("BD"), _T("BE"), _T("BF"), _T("BG"), 
	_T("BH"), _T("BI"), _T("BJ"), _T("BK"), _T("BL"), 
	_T("BM"), _T("BN"), _T("BO"), _T("BP"), _T("BQ"), 
	_T("BR"), _T("BS"), _T("BT"), _T("BU"), _T("BV"), 
	_T("BW"), _T("BX"), _T("BY"), _T("BZ"), _T("CA"),
	_T("CB"), _T("CC"), _T("CD"), _T("CE"), _T("CF"),
	_T("CG"), _T("CH"), _T("CI"), _T("CJ"), _T("CK"),
	_T("CL"), _T("CM"), _T("CN"), _T("CO"), _T("CP"),
	_T("CQ"), _T("CR"), _T("CS"), _T("CT"), _T("CU")
};

BEGIN_MESSAGE_MAP(CWhiteboxTestingPlatformApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CWhiteboxTestingPlatformApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CWhiteboxTestingPlatformApp 构造

CWhiteboxTestingPlatformApp::CWhiteboxTestingPlatformApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CWhiteboxTestingPlatformApp 对象

CWhiteboxTestingPlatformApp theApp;


// CWhiteboxTestingPlatformApp 初始化



BOOL CWhiteboxTestingPlatformApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	/*CString str=_T("sadsad");
	TCHAR szret[512];

	sprintf_s_t(szret,512,_T("%s"),str);
	*/

	gDebugTool.init(NULL);
	ghInstance=NULL;
	gConfig.init(NULL);

	g_pOutWnd=NULL;
	m_WorkSpaceWndManger.init();

	//测试
	//gpObjectSystem=&gobjsys;
	
	

	


	//test1.m_szAddr=_T("UserInfo");
	//test1.DeleteObject();


	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// START GDI+ SUB SYSTEM
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);


	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接

	//pDocTemplate = new CMultiDocTemplate(IDR_WhiteboxTestingTYPE,
	//	RUNTIME_CLASS(CWhiteboxTestingPlatformDoc),
	//	RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
	//	RUNTIME_CLASS(CWhiteboxTestingPlatformView));
	//if (!pDocTemplate)
	//	return FALSE;
	//AddDocTemplate(pDocTemplate);

	//pDocTemplate = new CMultiDocTemplate(IDR_WhiteboxTestingTYPE,
	//	RUNTIME_CLASS(CTestingTaskDoc),
	//	RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
	//	RUNTIME_CLASS(CTestingTaskView));
	//if (!pDocTemplate)
	//	return FALSE;
	//AddDocTemplate(pDocTemplate);

	/*m_pTestingTaskConfigDocTpl = new CMultiDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CTestingTaskConfigDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CTestingTaskConfigView));
	if (!m_pTestingTaskConfigDocTpl)
		return FALSE;
	//AddDocTemplate(m_pTestingTaskConfigDocTpl);

	m_pReportDocTpl = new CMultiDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CReportView));
	if (!m_pReportDocTpl)
		return FALSE;*/
	//AddDocTemplate(m_pReportDocTpl);

	//CMainWindow DesignDlg;
	//DesignDlg.DoModal();


	CLogoninDlg Dlg;

	if(Dlg.DoModal()!=IDOK)
	{
		return FALSE;
	}

	if (Dlg.m_szAppType==CString(_T("代码质量检查系统")))
	{
	}else if(Dlg.m_szAppType==CString(_T("白盒检查系统")))
	{
		CMainWindow DesignDlg;
		m_pMainWnd=&DesignDlg;
		DesignDlg.DoModal();
		return TRUE;
	}

	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 MDI 应用程序中，这应在设置 m_pMainWnd 之后立即发生



	//create work thread
	CreateWorkThread();

	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	g_pOutWnd=pMainFrame;

	return TRUE;
}


CString CWhiteboxTestingPlatformApp::GetAppPath()
{
	if (m_sAppPath.IsEmpty())
	{
		TCHAR   szPath[MAX_PATH]; 
		::GetModuleFileName(NULL, szPath, MAX_PATH);

		m_sAppPath = szPath;  
		int   index =  m_sAppPath.ReverseFind(_T( '\\'));  
		m_sAppPath = m_sAppPath.Left(index + 1);
	}

	return m_sAppPath;
}


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CWhiteboxTestingPlatformApp::OnAppAbout()
{
	//POSITION pos = m_pDocManager->GetFirstDocTemplatePosition();
	//CMultiDocTemplate *pDocTpl = NULL;
	//CDocument *pDoc = NULL;
	//POSITION pos2 = NULL;

	//while(pos && (pDocTpl = (CMultiDocTemplate *)m_pDocManager->GetNextDocTemplate(pos))){
	//	CReportDoc *pReportDoc = (CReportDoc *)pDocTpl->CreateNewDocument();
	//	pDocTpl->CreateNewFrame(pReportDoc, NULL);


	//	pos2 = pDocTpl->GetFirstDocPosition();
	//	while(pos2 && (pDoc = pDocTpl->GetNextDoc(pos2))){
	//		if (pDoc && (RUNTIME_CLASS(CReportDoc) == pDoc->GetRuntimeClass())){
	//			pDoc->GetTitle();
	//		}
	//	}
	//}


	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CWhiteboxTestingPlatformApp 自定义加载/保存方法

void CWhiteboxTestingPlatformApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);

	//项目视图弹出菜单
	bNameValid = strName.LoadString(IDS_PROJECT_VIEW);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_PROJECTVIEW_POPUP);

	//bNameValid = strName.LoadString(IDS_PROJECT_VIEW);
	//ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(_T("标准视图"), IDR_STANDARD_MENU);

	GetContextMenuManager()->AddMenu(_T("对象锁定"), IDR_OBJECT_LOCK_MENU);
}

void CWhiteboxTestingPlatformApp::LoadCustomState()
{
}

void CWhiteboxTestingPlatformApp::SaveCustomState()
{
}

void CWhiteboxTestingPlatformApp::CreateNewView(CMultiDocTemplate  *pDocTpl)
{ 
	return;

	CMultiDocTemplate  *m_pTempDocTpl = pDocTpl;
	ASSERT_VALID(m_pTempDocTpl);

	// There may be only one View of that doc type!
	// Is the template initialized?
	m_pTempDocTpl->OpenDocumentFile(NULL);// Create view
	return;

	POSITION Pos = m_pTempDocTpl->GetFirstDocPosition();
	if( NULL == Pos ) // No
	{ 
		m_pTempDocTpl->OpenDocumentFile(NULL);// Initialize
		return;
	}

	// Is there an entry for that document type?
	CDocument *pDoc = m_pTempDocTpl->GetNextDoc(Pos);
	if( NULL == pDoc )// No
	{ 
		m_pTempDocTpl->OpenDocumentFile(NULL);// Initialize
		return;
	}

	// Is the View for that document type initialized?
	Pos = pDoc->GetFirstViewPosition();
	if( NULL == Pos )// No
	{ 
		m_pTempDocTpl->OpenDocumentFile(NULL);// Initialize
		return;
	}
	// Exists a view for that document type?
	CView *pView = pDoc->GetNextView(Pos);
	if( NULL == pView )// No
	{ 
		m_pTempDocTpl->OpenDocumentFile(NULL);// Create view
		return;
	}

	//Exists a window for that view?
	CWnd *pWnd = pView->GetParent();
	if( NULL == pWnd )//No
	{ 
		m_pTempDocTpl->OpenDocumentFile(NULL);// Create view
		return;
	}

	// A View and a window exists. Restore or activate?
	WINDOWPLACEMENT wpl;
	pWnd->GetWindowPlacement(&wpl);
	if( SW_SHOWMINIMIZED  == wpl.showCmd )// Iconized window must be restored
	{ 
		wpl.showCmd = SW_RESTORE;
		if( WPF_RESTORETOMAXIMIZED == wpl.flags )
			wpl.showCmd = SW_SHOWMAXIMIZED;

		pWnd->SetWindowPlacement(&wpl);
	}
	else
	{ 
		wpl.showCmd = SW_RESTORE; // Bring window to top
		pWnd->SetWindowPlacement(&wpl);
		pWnd->BringWindowToTop();
	}
}



// CWhiteboxTestingPlatformApp 消息处理程序



