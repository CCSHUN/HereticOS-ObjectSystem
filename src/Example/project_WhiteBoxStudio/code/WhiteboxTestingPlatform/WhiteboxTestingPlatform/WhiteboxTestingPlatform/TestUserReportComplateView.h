#pragma once
#include "afxcmn.h"

#include "ListCtlStringSort.h"
#include "TabSheet.h"
#include "BaseReportInfoDlg.h"
#include "DevUserReportDlg2.h"
#include "CodeViewDlg.h"

// CTestUserReportComplateView 窗体视图

class CTestUserReportComplateView : public CFormView, public CViewInterfaceForWorkPageManager
{
	DECLARE_DYNCREATE(CTestUserReportComplateView)

protected:
	CTestUserReportComplateView();           // 动态创建所使用的受保护的构造函数
	virtual ~CTestUserReportComplateView();

public:
	enum { IDD = IDD_TESTUSER_REPORT_COMPLATE_VIEW };
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
	virtual void OnInitialUpdate();

public:
	CProjectSharedData *m_pShareData;
	CListCtlStringSort m_lstReport;
	BOOL m_bCanEdit;

	CBaseReportInfoDlg m_dataDlg1;
	CDevUserReportDlg2 m_dataDlg2;
	CCodeViewDlg		m_CodeViewDlg;
	CTabSheet m_tabData;

public:
	void InitTab();
	void InitialListCtrlHeadData();
	void InitialListCtrlData();
	void UpDataObjectUiState();
	void EnableEdit(BOOL bCanEdit);
	BOOL UpdataUi();

	afx_msg void OnBnClickedRefresh();
protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
public:
	afx_msg void OnNMCustomdrawListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedLookthird();
	afx_msg void OnBnClickedSubmit();
	afx_msg void OnBnClickedMakeSummary();
	afx_msg void OnBnClickedSendpost();

	afx_msg void OnReGetObject();
	afx_msg void OnReleaseObjectLock();
	afx_msg void OnGetObjectLock();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnBnClickedComplateReport();
	afx_msg void OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedEditreport();
	afx_msg void OnBnClickedDelreport();
};


