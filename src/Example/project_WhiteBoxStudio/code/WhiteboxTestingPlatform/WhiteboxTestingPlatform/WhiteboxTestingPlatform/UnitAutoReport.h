#pragma once
#include "afxcmn.h"

#include "ListCtlStringSort.h"

// CUnitAutoReport 窗体视图

class CUnitAutoReport : public CFormView,CViewInterfaceForWorkPageManager
{
	DECLARE_DYNCREATE(CUnitAutoReport)

protected:
	CUnitAutoReport();           // 动态创建所使用的受保护的构造函数
	virtual ~CUnitAutoReport();

public:
	enum { IDD = IDD_UNIT_TEST_AUTOREPORT };
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
	_tagUnitReportSet m_CurSelSet;
	int m_iCurIndex;
	CProjectSharedData * m_pShareData;//=(CStandardSharedData *
	void OnInitialUpdate();
	afx_msg void OnBnClickedNew();
	afx_msg void OnBnClickedEdit();
	afx_msg void OnBnClickedAutomake();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtlStringSort m_UnitReportListCtl;
	afx_msg void OnBnClickedDelsel();
	afx_msg void OnBnClickedCopysel();
	afx_msg void OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult);

	void UpDataUnitReportUiList();
	afx_msg void OnHdnItemchangedUnitlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkUnitlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedUnitlist(NMHDR *pNMHDR, LRESULT *pResult);
};


