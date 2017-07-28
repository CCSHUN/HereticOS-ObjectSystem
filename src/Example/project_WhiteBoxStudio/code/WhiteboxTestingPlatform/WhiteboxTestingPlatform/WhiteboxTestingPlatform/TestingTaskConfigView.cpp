// TestingTaskConfigView.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestingTaskConfigView.h"
#include "UiStructDef.h"
#include "ProjectDataModel.h"

// CTestingTaskConfigView

IMPLEMENT_DYNCREATE(CTestingTaskConfigView, CFormView)

CTestingTaskConfigView::CTestingTaskConfigView()
	: CFormView(CTestingTaskConfigView::IDD)
	, m_sCMDParam(_T(""))
	, m_sProjectName(_T(""))
	, m_sStandardParam(_T(""))
	, m_sPrivateParam(_T(""))
{

}

CTestingTaskConfigView::~CTestingTaskConfigView()
{
}

void CTestingTaskConfigView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SPECIFYNAME, m_cmbSpecifyName);
	DDX_Text(pDX, IDC_STATIC_CMDPARAM, m_sCMDParam);
	DDX_Text(pDX, IDC_STATIC_SUBPROJECT_NAME, m_sProjectName);
	DDV_MaxChars(pDX, m_sProjectName, 256);
	DDX_Text(pDX, IDC_EDIT_STANDARDPARAM, m_sStandardParam);
	DDX_Text(pDX, IDC_EDIT_PRIVATEPARAM, m_sPrivateParam);
	DDX_Control(pDX, IDC_EDIT_STANDARDPARAM, m_StandardParamCtl);
}

BEGIN_MESSAGE_MAP(CTestingTaskConfigView, CFormView)
	ON_COMMAND(ID_FILE_NEW, &CTestingTaskConfigView::OnFileNew)
	ON_EN_CHANGE(IDC_EDIT_STANDARDPARAM, &CTestingTaskConfigView::OnEnChangeEditStandardparam)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestingTaskConfigView::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTestingTaskConfigView 诊断

#ifdef _DEBUG
void CTestingTaskConfigView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTestingTaskConfigView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTestingTaskConfigView 消息处理程序

void CTestingTaskConfigView::OnFileNew()
{
	MessageBox(_T("1234"), _T("iop"), MB_OK);
	//CFormView::OnFileNew();
}

void CTestingTaskConfigView::ProjectChange()
{
}

void CTestingTaskConfigView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	//get sharedata
	m_pShareData=(CProjectSharedData *)(((CChildFrame *)GetParentFrame())->m_ProjectIndex.pSharedObject);
	((CChildFrame *)GetParentFrame())->m_ProjectIndex.pViewInterface = this;
	m_pShareData->init();

	//get specify name
	int nSelected = 0;
	vector<tstring> vAllStandardName;
	theApp.m_WorkSpaceWndManger.m_StandardDataModel.GetAllStandardNameArray(vAllStandardName);
	for (unsigned int i=0; i<vAllStandardName.size(); i++){
		m_cmbSpecifyName.AddString(vAllStandardName[i].c_str());
		if (m_pShareData->m_ProjectConfig.TestReportStandard == vAllStandardName[i]){
			nSelected = i;
		}
	}
	m_cmbSpecifyName.SetCurSel(nSelected);

	m_sStandardParam = m_pShareData->m_ProjectConfig.CheckCfgStandard.c_str();
	m_sPrivateParam = m_pShareData->m_UserProjectConfig.CheckCfgStandard.c_str();
	if(m_sPrivateParam.GetLength()==0)
	{
		m_sPrivateParam=_T("//-setenv(SOURCE_PATH=E:\\svn\\project\\project_WhiteBoxStudio\\code\\CodeTest)\r\n")
			_T("//-setenv(VC_PATH=C:\\Program Files\\Microsoft Visual Studio 9.0\\VC)\r\n")
			_T("//-setenv(SDK_PATH=C:\\Program Files\\Microsoft SDKs\\Windows\\v6.0A)\r\n");
	}

	tstring sConfigName = m_pShareData->GetProjectName() + tstring(_T("_")) + m_pShareData->GetSubProjectName() + tstring(_T(".lnt"));
	m_sCMDParam.Format(_T("%slint\\lint-nt.exe +v -i\"%s\" -u %s"),
		theApp.GetAppPath(), 
		theApp.GetAppPath()+_T("lint"), 
		sConfigName.c_str());

	m_sProjectName = CString(_T("[ ")) + CString(m_pShareData->GetProjectName().c_str()) + CString(_T(" ][ ")) + 
		CString(m_pShareData->GetSubProjectName().c_str()) + CString(_T(" ]"));

	//((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_WRITED, _T("当前文档处于可写状态"));

	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditTest()==FALSE)
	{
		//GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_SPECIFYNAME)->EnableWindow(FALSE);
		//GetDlgItem(IDC_EDIT_STANDARDPARAM)->EnableWindow(FALSE);
		m_StandardParamCtl.SetReadOnly(TRUE);
	}

	UpdateData(FALSE);
}

void CTestingTaskConfigView::OnEnChangeEditStandardparam()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CTestingTaskConfigView::OnBnClickedButton1()
{
	UpdateData(TRUE);

	int nSelected = m_cmbSpecifyName.GetCurSel();
	if (nSelected == -1){
		return;
	}

	CString sSpecifyName;
	m_cmbSpecifyName.GetLBText(nSelected, sSpecifyName);

	m_pShareData->m_UserProjectConfig.CheckCfgStandard = m_sPrivateParam;
	
	m_pShareData->m_ProjectConfig.CheckCfgStandard = m_sStandardParam;
	m_pShareData->m_ProjectConfig.TestReportStandard = sSpecifyName;
	if (m_pShareData){
		m_pShareData->UpdataConfigObject();
		m_pShareData->GetConfigObject();
	}
}
