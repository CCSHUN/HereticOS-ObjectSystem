// TestUserNewStandard.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestUserNewStandard.h"


// CTestUserNewStandard 对话框

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


// CTestUserNewStandard 消息处理程序
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
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CTestUserNewStandard::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
