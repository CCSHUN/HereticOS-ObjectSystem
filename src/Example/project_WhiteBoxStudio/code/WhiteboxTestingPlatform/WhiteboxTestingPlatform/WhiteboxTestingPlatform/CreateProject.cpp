// CreateProject.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "CreateProject.h"


// CCreateProject �Ի���

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


// CCreateProject ��Ϣ�������

BOOL CCreateProject::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(m_sTitleName);

	m_ctlName.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CCreateProject::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (!m_sName.IsEmpty()){
		OnOK();
	}
}
