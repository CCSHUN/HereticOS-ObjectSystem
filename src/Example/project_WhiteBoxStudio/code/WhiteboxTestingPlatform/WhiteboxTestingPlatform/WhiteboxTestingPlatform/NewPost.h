#pragma once
#include "afxwin.h"


// CNewPost �Ի���

class CNewPost : public CDialog
{
	DECLARE_DYNAMIC(CNewPost)

public:
	BOOL PreTranslateMessage(MSG* pMsg);
	CNewPost(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewPost();

// �Ի�������
	enum { IDD = IDD_NEWPOST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString m_sSubject;
	CString m_sPosition;
	CString m_sContent;
	CString m_szTitle;
};
