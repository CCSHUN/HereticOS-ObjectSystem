#pragma once
#include "afxwin.h"


// CSubProjectManger �Ի���

class CSubProjectManger : public CDialog
{
	DECLARE_DYNAMIC(CSubProjectManger)

public:
	CSubProjectManger(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSubProjectManger();

// �Ի�������
	enum { IDD = IDD_SUBPROJECTMANGERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CProjectSharedData * m_pShareData;
	BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CComboBox m_ProjectStateComboCtl;
	CString m_szProjectState;
};
