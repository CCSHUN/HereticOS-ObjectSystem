// SubProjectManger.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "SubProjectManger.h"


// CSubProjectManger �Ի���

IMPLEMENT_DYNAMIC(CSubProjectManger, CDialog)

CSubProjectManger::CSubProjectManger(CWnd* pParent /*=NULL*/)
	: CDialog(CSubProjectManger::IDD, pParent)
	, m_szProjectState(_T(""))
{

}

CSubProjectManger::~CSubProjectManger()
{
}

void CSubProjectManger::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PROJECTSTATE, m_ProjectStateComboCtl);
	DDX_CBString(pDX, IDC_COMBO_PROJECTSTATE, m_szProjectState);
}


BEGIN_MESSAGE_MAP(CSubProjectManger, CDialog)
	ON_BN_CLICKED(IDOK, &CSubProjectManger::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CSubProjectManger::OnInitDialog()
{
	BOOL bRet=CDialog::OnInitDialog();
	m_pShareData->init();
	m_ProjectStateComboCtl.AddString(PROJECT_STATE_NEW_OVER);
	m_ProjectStateComboCtl.AddString(PROJECT_STATE_TEST_OVER);
	m_ProjectStateComboCtl.AddString(PROJECT_STATE_DEV_OVER);
	m_ProjectStateComboCtl.AddString(PROJECT_STATE_FILE_OVER);
	m_ProjectStateComboCtl.SelectString(0,m_pShareData->m_ProjectState.m_Data.szProjectState.c_str());
	return bRet;
}
// CSubProjectManger ��Ϣ�������

void CSubProjectManger::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_pShareData->m_ProjectState.m_Data.szProjectState=tstring((LPCTSTR)m_szProjectState);
	if(m_pShareData->UpdataProjectState())
	{
		OnOK();
	}else
	{
		AfxMessageBox(_T("����ʧ��"));
	}
	
}
