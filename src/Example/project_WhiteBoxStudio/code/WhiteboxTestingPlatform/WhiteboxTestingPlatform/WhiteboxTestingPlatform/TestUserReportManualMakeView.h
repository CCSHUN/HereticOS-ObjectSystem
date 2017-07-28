#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "ListCtlStringSort.h"
#include "CodeView.h"
// CTestUserReportManualMakeView 窗体视图

class CTestUserReportManualMakeView : public CFormView, public CViewInterfaceForWorkPageManager
{
	DECLARE_DYNCREATE(CTestUserReportManualMakeView)

protected:
	CTestUserReportManualMakeView();           // 动态创建所使用的受保护的构造函数
	virtual ~CTestUserReportManualMakeView();

public:
	enum { IDD = IDD_TESTUSER_REPORT_MANUAL_MAKE_VIEW };
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
	
	CCodeView  * m_pCodeViewCtl;
	void ProjectChange(BOOL bToTop);

	void DoWithCurReportItem(const CString &sItemState);
	BOOL InitCombo();
	void InitialListCtrlHeadData();
	void InitialListCtrlData();
	afx_msg void OnNMClickListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedComplateCurReport();
	afx_msg void OnBnClickedRefresh();
protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
public:
	CComboBox m_cmbErrorType;
	CComboBox m_cmbErrorClass;
	afx_msg void OnCbnEditchangeComboErrorType();
	afx_msg void OnCbnEditupdateComboErrorType();
	afx_msg void OnLvnItemchangedListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedIgnoreCurReport();
	afx_msg void OnBnClickedLookthird();
	afx_msg void OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSubmit();
	afx_msg void OnNMDblclkListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDelselig();
};


