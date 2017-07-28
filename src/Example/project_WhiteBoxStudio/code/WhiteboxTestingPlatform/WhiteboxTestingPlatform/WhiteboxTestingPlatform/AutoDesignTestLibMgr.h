#pragma once
#include "afxwin.h"
#include "TestConfig.h"
#include "TestLibDataMode.h"
#include "afxcmn.h"

// CAutoDesignTestLibMgr 对话框

class CAutoDesignTestLibMgr : public CDialog
{
	DECLARE_DYNAMIC(CAutoDesignTestLibMgr)

public:
	CAutoDesignTestLibMgr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAutoDesignTestLibMgr();

	BOOL OnInitDialog();
	BOOL UpDataUi(BOOL bToUi);

// 对话框数据
	enum { IDD = IDD_TESTLIBMGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_szTestLibName;
	CComboBox m_LibCombo;
	TestLibDataMode * m_pLib;
	afx_msg void OnBnClickedNewtestlib();
	afx_msg void OnBnClickedDellib();
	afx_msg void OnBnClickedButtonLoadlib();
	CListCtrl m_TestLibList;
	CString m_szFromLibName;
	afx_msg void OnBnClickedCheckIscopylib();
	BOOL m_bIsCopyLib;
};
