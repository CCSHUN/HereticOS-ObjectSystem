#pragma once
#include "afxcmn.h"


// CMainWindow 对话框
#include "TabSheet.h"
#include "AutoStructDataDesignDlg.h"
#include "ExpMake.h"
#include "TestLibDataMode.h"
#include "AutoDesignTestLibMgr.h"
class CMainWindow : public CDialog
{
	DECLARE_DYNAMIC(CMainWindow)

public:
	CMainWindow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainWindow();

// 对话框数据
	enum { IDD = IDD_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	TestLibDataMode m_Lib;
	CExpMake m_ExpMakePage;
	CAutoStructDataDesignDlg m_FuncPage;
	CAutoDesignTestLibMgr m_LibMgr;
	CTabSheet m_MainTab;
	afx_msg void OnClose();
	afx_msg void OnBnClickedSave();
};
