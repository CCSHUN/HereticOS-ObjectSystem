// CreateProject.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "CreateProject.h"


// CCreateProject 对话框

IMPLEMENT_DYNAMIC(CCreateProject, CDialog)

CCreateProject::CCreateProject(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateProject::IDD, pParent)
	, m_sName(_T(""))
{

}

CCreateProject::~CCreateProject()
{
}

void CCreateProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_sName);
	DDV_MaxChars(pDX, m_sName, 60);
	DDX_Control(pDX, IDC_EDIT_NAME, m_ctlName);
}


BEGIN_MESSAGE_MAP(CCreateProject, CDialog)
	ON_BN_CLICKED(IDOK, &CCreateProject::OnBnClickedOk)
END_MESSAGE_MAP()


// CCreateProject 消息处理程序

BOOL CCreateProject::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(m_sTitleName);

	m_ctlName.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCreateProject::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (!m_sName.IsEmpty()){
		OnOK();
	}
}
