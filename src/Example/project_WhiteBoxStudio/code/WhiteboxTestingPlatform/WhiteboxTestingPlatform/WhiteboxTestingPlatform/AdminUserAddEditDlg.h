#pragma once
#include "afxwin.h"


// CAdminUserAddEditDlg �Ի���

class CAdminUserAddEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CAdminUserAddEditDlg)

public:
	BOOL OnInitDialog();
	BOOL m_bEdit;
	CUserShareData  * m_pShareData;

	CAdminUserAddEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdminUserAddEditDlg();

// �Ի�������
	enum { IDD = IDD_ADMINUSER_USERADDEDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancal();
	CString m_szUserName;
	CString m_szPassWord;
	CString m_szRePassword;
	CComboBox m_UserTypeCtl;
	CString m_szUserType;

	_tagUserMapSet			m_CurUser;
};
