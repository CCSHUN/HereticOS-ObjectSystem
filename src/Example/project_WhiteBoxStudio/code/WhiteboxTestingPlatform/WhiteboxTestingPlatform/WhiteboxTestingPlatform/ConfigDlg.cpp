// ConfigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "ConfigDlg.h"


// CConfigDlg �Ի���

IMPLEMENT_DYNAMIC(CConfigDlg, CDialog)

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
	, m_szLocalSystemDir(_T(""))
	, m_szWSDL(_T(""))
	, m_nSoapTimeOut(0)
{

}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LOCALDIR, m_szLocalSystemDir);
	DDX_Text(pDX, IDC_SOAPDIR, m_szWSDL);
	DDV_MaxChars(pDX, m_szWSDL, 256);

	DDX_Text(pDX, IDC_SOAPTIMEOUT, m_nSoapTimeOut);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConfigDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CConfigDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CConfigDlg ��Ϣ�������


BOOL CConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_szLocalSystemDir=gConfig.m_Config.strLocalSystemDirectory.c_str();
	m_nSoapTimeOut=gConfig.m_Config.nSoapTimeout;
	m_szWSDL=gConfig.m_Config.strWSDLUrl.c_str();

	UpdateData(FALSE);
	return TRUE;
}

void CConfigDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	gConfig.m_Config.strLocalSystemDirectory=m_szLocalSystemDir;

	if (gConfig.m_Config.strLocalSystemDirectory.at(gConfig.m_Config.strLocalSystemDirectory.length()-1) != '\\')
	{
		gConfig.m_Config.strLocalSystemDirectory += '\\';
	}

	gConfig.m_Config.nSoapTimeout=m_nSoapTimeOut;
	gConfig.m_Config.strWSDLUrl=m_szWSDL;
	gConfig.Save();
	//gConfig.m_Config.

	CDialog::OnOK();
}

void CConfigDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
