#pragma once
#include "afxwin.h"


// CNewPost 对话框

class CNewPost : public CDialog
{
	DECLARE_DYNAMIC(CNewPost)

public:
	BOOL PreTranslateMessage(MSG* pMsg);
	CNewPost(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewPost();

// 对话框数据
	enum { IDD = IDD_NEWPOST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString m_sSubject;
	CString m_sPosition;
	CString m_sContent;
	CString m_szTitle;
};
