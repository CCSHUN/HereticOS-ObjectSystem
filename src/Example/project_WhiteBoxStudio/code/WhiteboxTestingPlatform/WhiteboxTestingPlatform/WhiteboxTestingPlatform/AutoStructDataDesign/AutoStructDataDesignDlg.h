
// AutoStructDataDesignDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TestConfig.h"
#include "TestLibDataMode.h"
class CAutoStructDataDesignDlgAutoProxy;


// CAutoStructDataDesignDlg 对话框
class CAutoStructDataDesignDlg : public CDialog
{
	DECLARE_DYNAMIC(CAutoStructDataDesignDlg);
	friend class CAutoStructDataDesignDlgAutoProxy;

// 构造
public:
	CAutoStructDataDesignDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CAutoStructDataDesignDlg();

// 对话框数据
	enum { IDD = IDD_AUTOSTRUCTDATADESIGN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	BOOL LoadToUi();
	//BOOL SaveToXml();
	BOOL UpDataUi(BOOL ToUi);


// 实现
protected:
	CAutoStructDataDesignDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedAddfunc();
	afx_msg void OnBnClickedDelfunc();
	afx_msg void OnBnClickedAddprrarm();
	afx_msg void OnBnClickedDelparam();
	afx_msg void OnBnClickedUpdataParamdef();
	
	CListBox m_FuncListCtl;
	CListCtrl m_FuncPrarmDefListCtl;
	
	CString m_szFuncName;
	CComboBox m_FuncTypeComboCtl;
	CString m_szFuncDesc;
	CString m_szParamName;
	CString m_szParamDesc;
	
	afx_msg void OnLbnSelchangeListFunc();
	
	afx_msg void OnLvnItemchangedListPrarmdef(NMHDR *pNMHDR, LRESULT *pResult);

	
	CString m_szFuncType;

	TestLibDataMode * m_pLib;


	int m_nCurFuncPos;
	CString m_szDefaultParamVal;
	
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedEditfunc();
	//afx_msg void OnBnClickedCheckM();
	//CString m_szRefMacroName;
};
