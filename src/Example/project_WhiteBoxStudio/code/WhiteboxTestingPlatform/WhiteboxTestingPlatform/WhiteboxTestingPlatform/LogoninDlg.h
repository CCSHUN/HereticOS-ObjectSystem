#pragma once
#include "afxwin.h"


// CLogoninDlg 对话框

class CLogoninDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogoninDlg)

public:
	CLogoninDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogoninDlg();

// 对话框数据
	enum { IDD = IDD_LOGONIN_DLG };

	BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConfig();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_szUSerName;
	CString m_szPassword;
	CString m_szLogonType;
	CComboBox m_LogonTypeCtl;
	CString m_szAppType;
	CComboBox m_AppTypeCtlCombo;
};
