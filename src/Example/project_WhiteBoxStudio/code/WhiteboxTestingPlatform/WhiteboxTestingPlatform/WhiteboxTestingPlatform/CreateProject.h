#pragma once
#include "afxwin.h"


// CCreateProject �Ի���

class CCreateProject : public CDialog
{
	DECLARE_DYNAMIC(CCreateProject)

public:
	CCreateProject(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCreateProject();

// �Ի�������
	enum { IDD = IDD_DLG_CREATE_PROJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString m_sTitleName;
	CString m_sName;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CEdit m_ctlName;
};
