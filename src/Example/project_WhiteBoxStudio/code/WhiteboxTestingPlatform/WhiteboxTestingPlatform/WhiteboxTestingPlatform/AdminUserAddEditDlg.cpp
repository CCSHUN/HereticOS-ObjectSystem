// AdminUserAddEditDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "AdminUserAddEditDlg.h"


// CAdminUserAddEditDlg �Ի���

IMPLEMENT_DYNAMIC(CAdminUserAddEditDlg, CDialog)

CAdminUserAddEditDlg::CAdminUserAddEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdminUserAddEditDlg::IDD, pParent)
	, m_szUserName(_T(""))
	, m_szPassWord(_T(""))
	, m_szRePassword(_T(""))
	, m_szUserType(_T(""))
{
	m_bEdit=FALSE;

}

CAdminUserAddEditDlg::~CAdminUserAddEditDlg()
{
}

void CAdminUserAddEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USERNAME, m_szUserName);
	DDX_Text(pDX, IDC_PASSWORD, m_szPassWord);
	DDX_Text(pDX, IDC_REPASSWORD, m_szRePassword);
	DDX_Control(pDX, IDC_COMBO_USERTYPE, m_UserTypeCtl);
	DDX_CBString(pDX, IDC_COMBO_USERTYPE, m_szUserType);
}


BEGIN_MESSAGE_MAP(CAdminUserAddEditDlg, CDialog)
	ON_BN_CLICKED(IDC_OK, &CAdminUserAddEditDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CANCAL, &CAdminUserAddEditDlg::OnBnClickedCancal)
END_MESSAGE_MAP()


// CAdminUserAddEditDlg ��Ϣ�������

BOOL CAdminUserAddEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_UserTypeCtl.AddString(USER_TYPE_TESTER);
	m_UserTypeCtl.AddString(USER_TYPE_DEVELOP);
	m_UserTypeCtl.AddString(USER_TYPE_ADMIN);
	m_UserTypeCtl.SelectString(0,USER_TYPE_TESTER);
	if(m_bEdit)
	{
		GetDlgItem(IDC_USERNAME)->EnableWindow(FALSE);
		m_szUserName=m_pShareData->m_CurUser.szUserName.c_str();
		m_szPassWord=m_pShareData->m_CurUser.szPassword.c_str();
		m_szRePassword=m_pShareData->m_CurUser.szPassword.c_str();
		

		UpdateData(FALSE);
		m_UserTypeCtl.SelectString(0,m_pShareData->m_CurUser.szUserType.c_str());
	}
	return TRUE;
}
void CAdminUserAddEditDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	list<_tagUserMapSet>::iterator it=m_pShareData->m_UserList.begin();

	if(m_bEdit==FALSE)
	{
		for(;it!=m_pShareData->m_UserList.end();it++)
		{
			if(it->szUserName==tstring((LPCTSTR)m_szUserName))
			{
				AfxMessageBox(_T("�û����Ѵ��ڡ�����������"));
				return;
			}
		}
	}
	

	if((m_szRePassword==m_szPassWord)&&
		(!m_szUserName.IsEmpty()))
	{
		m_CurUser.szPassword=m_szPassWord;
		m_CurUser.szUserName=m_szUserName;
		m_CurUser.szUserType=m_szUserType;
		CDialog::OnOK();
	}else
	{
		AfxMessageBox(_T("���벻һ�¡����������"));
		return ;
	}
	
}

void CAdminUserAddEditDlg::OnBnClickedCancal()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
