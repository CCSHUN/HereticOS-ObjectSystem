#pragma once
#include "afxcmn.h"



// CReportView 窗体视图

class CReportView : public CFormView
{
	DECLARE_DYNCREATE(CReportView)

protected:
	CReportView();           // 动态创建所使用的受保护的构造函数
	virtual ~CReportView();

public:
	enum { IDD = IDD_REPORTVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_lstReport;
	afx_msg void OnLvnItemchangedListReport(NMHDR *pNMHDR, LRESULT *pResult);
};


