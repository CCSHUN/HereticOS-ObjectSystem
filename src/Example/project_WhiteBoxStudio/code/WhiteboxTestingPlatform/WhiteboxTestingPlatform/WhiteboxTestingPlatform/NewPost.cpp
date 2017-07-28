// NewPost.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "NewPost.h"


// CNewPost 对话框

IMPLEMENT_DYNAMIC(CNewPost, CDialog)

CNewPost::CNewPost(CWnd* pParent /*=NULL*/)
	: CDialog(CNewPost::IDD, pParent)
	, m_sSubject(_T(""))
	, m_sPosition(_T(""))
	, m_sContent(_T(""))
{

}

CNewPost::~CNewPost()
{
}

void CNewPost::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SUBJECT, m_sSubject);
	DDX_Text(pDX, IDC_EDIT_POSITION, m_sPosition);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_sContent);
}


BEGIN_MESSAGE_MAP(CNewPost, CDialog)
	ON_BN_CLICKED(IDOK, &CNewPost::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewPost 消息处理程序

void CNewPost::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}
BOOL CNewPost::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN ||pMsg->wParam == VK_ESCAPE))     
	{     
		return ::TranslateMessage(pMsg);     
	}    

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CNewPost::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(m_szTitle);
	((CWnd *)GetDlgItem(IDC_EDIT_SUBJECT))->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
