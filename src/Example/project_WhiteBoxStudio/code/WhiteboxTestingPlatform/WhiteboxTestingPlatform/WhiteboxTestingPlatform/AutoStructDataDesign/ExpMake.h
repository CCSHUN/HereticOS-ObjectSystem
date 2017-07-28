#pragma once


// CExpMake 对话框
#include "TestLibDataMode.h"
class CExpMake : public CDialog
{
	DECLARE_DYNAMIC(CExpMake)

public:
	CExpMake(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExpMake();

// 对话框数据
	enum { IDD = IDD_ExpMake };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddcaseexp();
	afx_msg void OnBnClickedDelcaseexp();
	afx_msg void OnBnClickedUpdataParam2();
	afx_msg void OnBnClickedRunsel();
	afx_msg void OnBnClickedRunall();

	afx_msg void OnLbnSelchangeListExp();
	afx_msg void OnLvnItemchangedListPrarm2(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL OnInitDialog();
	BOOL UpDataUi(BOOL ToUi);

	CListBox m_ExpListCtl;
	CListCtrl m_ExpParamValList;
	CString m_szParamVal;
	CString m_szRunfmt;

	TestLibDataMode  * m_pLib;

	int m_nCurExpPos;
	
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLbnDblclkListExp();
	CString m_szExpDesc;
};
