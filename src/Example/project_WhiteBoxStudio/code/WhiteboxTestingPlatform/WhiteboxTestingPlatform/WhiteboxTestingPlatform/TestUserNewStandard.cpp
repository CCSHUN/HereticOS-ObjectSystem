// TestUserNewStandard.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestUserNewStandard.h"


// CTestUserNewStandard �Ի���

IMPLEMENT_DYNAMIC(CTestUserNewStandard, CDialog)

CTestUserNewStandard::CTestUserNewStandard(CWnd* pParent /*=NULL*/)
	: CDialog(CTestUserNewStandard::IDD, pParent)
	, m_szStandardName(_T(""))
{

}

CTestUserNewStandard::~CTestUserNewStandard()
{
}

void CTestUserNewStandard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_szStandardName);
}


BEGIN_MESSAGE_MAP(CTestUserNewStandard, CDialog)
	ON_BN_CLICKED(IDOK, &CTestUserNewStandard::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestUserNewStandard::OnBnClickedCancel)
END_MESSAGE_MAP()


// CTestUserNewStandard ��Ϣ�������
BOOL CTestUserNewStandard::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN ||pMsg->wParam == VK_ESCAPE))     
	{     
		return TRUE;     
	}    

	return CDialog::PreTranslateMessage(pMsg);
}

void CTestUserNewStandard::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void CTestUserNewStandard::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
