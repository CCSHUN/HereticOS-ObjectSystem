
// WhiteboxTestingPlatform.cpp : ����Ӧ�ó��������Ϊ��
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
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CWhiteboxTestingPlatformApp ����

CWhiteboxTestingPlatformApp::CWhiteboxTestingPlatformApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CWhiteboxTestingPlatformApp ����

CWhiteboxTestingPlatformApp theApp;


// CWhiteboxTestingPlatformApp ��ʼ��



BOOL CWhiteboxTestingPlatformApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	/*CString str=_T("sadsad");
	TCHAR szret[512];

	sprintf_s_t(szret,512,_T("%s"),str);
	*/

	gDebugTool.init(NULL);
	ghInstance=NULL;
	gConfig.init(NULL);

	g_pOutWnd=NULL;
	m_WorkSpaceWndManger.init();

	//����
	//gpObjectSystem=&gobjsys;
	
	

	


	//test1.m_szAddr=_T("UserInfo");
	//test1.DeleteObject();


	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
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

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������

	//pDocTemplate = new CMultiDocTemplate(IDR_WhiteboxTestingTYPE,
	//	RUNTIME_CLASS(CWhiteboxTestingPlatformDoc),
	//	RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
	//	RUNTIME_CLASS(CWhiteboxTestingPlatformView));
	//if (!pDocTemplate)
	//	return FALSE;
	//AddDocTemplate(pDocTemplate);

	//pDocTemplate = new CMultiDocTemplate(IDR_WhiteboxTestingTYPE,
	//	RUNTIME_CLASS(CTestingTaskDoc),
	//	RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
	//	RUNTIME_CLASS(CTestingTaskView));
	//if (!pDocTemplate)
	//	return FALSE;
	//AddDocTemplate(pDocTemplate);

	/*m_pTestingTaskConfigDocTpl = new CMultiDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CTestingTaskConfigDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CTestingTaskConfigView));
	if (!m_pTestingTaskConfigDocTpl)
		return FALSE;
	//AddDocTemplate(m_pTestingTaskConfigDocTpl);

	m_pReportDocTpl = new CMultiDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
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

	if (Dlg.m_szAppType==CString(_T("�����������ϵͳ")))
	{
	}else if(Dlg.m_szAppType==CString(_T("�׺м��ϵͳ")))
	{
		CMainWindow DesignDlg;
		m_pMainWnd=&DesignDlg;
		DesignDlg.DoModal();
		return TRUE;
	}

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������



	//create work thread
	CreateWorkThread();

	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// �������жԻ����Ӧ�ó�������
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

// CWhiteboxTestingPlatformApp �Զ������/���淽��

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

	//��Ŀ��ͼ�����˵�
	bNameValid = strName.LoadString(IDS_PROJECT_VIEW);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_PROJECTVIEW_POPUP);

	//bNameValid = strName.LoadString(IDS_PROJECT_VIEW);
	//ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(_T("��׼��ͼ"), IDR_STANDARD_MENU);

	GetContextMenuManager()->AddMenu(_T("��������"), IDR_OBJECT_LOCK_MENU);
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



// CWhiteboxTestingPlatformApp ��Ϣ�������



