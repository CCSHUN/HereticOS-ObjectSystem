#pragma once
#include "afxwin.h"


// CCreateProject 对话框

class CCreateProject : public CDialog
{
	DECLARE_DYNAMIC(CCreateProject)

public:
	CCreateProject(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCreateProject();

// 对话框数据
	enum { IDD = IDD_DLG_CREATE_PROJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString m_sTitleName;
	CString m_sName;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CEdit m_ctlName;
};
