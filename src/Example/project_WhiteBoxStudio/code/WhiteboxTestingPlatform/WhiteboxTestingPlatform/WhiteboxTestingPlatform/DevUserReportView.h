#pragma once
#include "afxcmn.h"

#include "ListCtlStringSort.h"
#include "afxwin.h"

#include "TabSheet.h"
#include "BaseReportInfoDlg.h"
#include "DevUserReportDlg2.h"
#include "CodeViewDlg.h"
// CDevUserReportView 窗体视图

class CDevUserReportView : public CFormView, public CViewInterfaceForWorkPageManager
{
	DECLARE_DYNCREATE(CDevUserReportView)

protected:
	CDevUserReportView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDevUserReportView();

public:
	enum { IDD = IDD_DEVUSER_REPORT_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	void InitTab();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ProjectChange(BOOL bToTop);
	virtual void OnInitialUpdate();
public:
	CProjectSharedData *m_pShareData;

	//CDialog *m_pDataDlg[3];
	CBaseReportInfoDlg m_dataDlg1;
	CDevUserReportDlg2 m_dataDlg2;
	CCodeViewDlg		m_CodeViewDlg;
	CTabSheet m_tabData;
	//int m_CurSelTab;
	BOOL m_bCanEdit;

	void UpDataObjectUiState();
	void EnableEdit(BOOL bCanEdit);

	afx_msg void OnTcnSelchangeTabData(NMHDR *pNMHDR, LRESULT *pResult);

	BOOL UpdataUi();
	void InitialListCtrlHeadData();
	void InitialListCtrlData();
	CListCtlStringSort m_lstReport;
	afx_msg void OnNMCustomdrawListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclickListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboDispatch();
	afx_msg void OnCbnSelchangeComboDevstate();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

	afx_msg void OnReGetObject();
	afx_msg void OnReleaseObjectLock();
	afx_msg void OnGetObjectLock();

	BOOL InitDevList();
protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
public:
	CComboBox m_cmbDispatch;
	CComboBox m_cmbDevStatus;
	afx_msg void OnBnClickedSubmit();
	afx_msg void OnBnClickedRefresh();
	afx_msg void OnHdnItemdblclickListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCanEdit(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedSendpost();
	afx_msg void OnBnClickedEditpost();
};


