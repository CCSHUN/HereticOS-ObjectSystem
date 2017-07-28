// LogoninDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "LogoninDlg.h"

#include "ConfigDlg.h"


// CLogoninDlg 对话框

IMPLEMENT_DYNAMIC(CLogoninDlg, CDialog)

CLogoninDlg::CLogoninDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogoninDlg::IDD, pParent)
	, m_szUSerName(_T(""))
	, m_szPassword(_T(""))
	, m_szLogonType(_T(""))
	, m_szAppType(_T(""))
{

}

CLogoninDlg::~CLogoninDlg()
{
}

void CLogoninDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_szUSerName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_szPassword);
	DDX_CBString(pDX, IDC_COMBO_LOGON_TYPE, m_szLogonType);
	DDX_Control(pDX, IDC_COMBO_LOGON_TYPE, m_LogonTypeCtl);
	DDX_CBString(pDX, IDC_COMBO_LOGON_APP_TYPE, m_szAppType);
	DDX_Control(pDX, IDC_COMBO_LOGON_APP_TYPE, m_AppTypeCtlCombo);
}


BEGIN_MESSAGE_MAP(CLogoninDlg, CDialog)
	ON_BN_CLICKED(ID_CONFIG, &CLogoninDlg::OnBnClickedConfig)
	ON_BN_CLICKED(IDOK, &CLogoninDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLogoninDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLogoninDlg 消息处理程序
BOOL CLogoninDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_LogonTypeCtl.AddString(LOGIN_TYPE_LOCAL);
	m_LogonTypeCtl.AddString(LOGIN_TYPE_NET_SOAPSERVICE);
	m_LogonTypeCtl.SelectString(0,LOGIN_TYPE_NET_SOAPSERVICE);
	m_AppTypeCtlCombo.AddString(_T("代码质量检查系统"));
	m_AppTypeCtlCombo.AddString(_T("白盒检查系统"));
	m_AppTypeCtlCombo.SelectString(0,_T("白盒检查系统"));

	((CWnd *)GetDlgItem(IDC_EDIT_USERNAME))->SetFocus();
	return TRUE;
}
void CLogoninDlg::OnBnClickedConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	CConfigDlg dlg;
	dlg.DoModal();
}

void CLogoninDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_szUSerName.GetLength())
	{
		if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.LonginSystem(
			tstring((LPCTSTR)m_szLogonType),
			tstring((LPCTSTR)m_szUSerName),
			tstring((LPCTSTR)m_szPassword))
			)
		{
			OnOK();
		}else
		{
			AfxMessageBox(_T("登陆失败"));
		}
		
	}else
	{
		AfxMessageBox(_T("请输入用户名"));
	}
	
}

void CLogoninDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
