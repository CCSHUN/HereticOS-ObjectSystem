#pragma once
#include "afxcmn.h"



// CTestUserReportNoFindStandardView ������ͼ
#include "ListCtlStringSort.h"

class CTestUserReportNoFindStandardView : public CFormView, public CViewInterfaceForWorkPageManager
{
	
	DECLARE_DYNCREATE(CTestUserReportNoFindStandardView)

protected:
	CTestUserReportNoFindStandardView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTestUserReportNoFindStandardView();

public:
	enum { IDD = IDD_TESTUSER_REPORT_NO_FIND_STANDARD_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

	void InitialListCtrlHeadData();
	void InitialListCtrlData();

public:
	CProjectSharedData *m_pShareData;
	CListCtlStringSort m_lstReport;
	afx_msg void OnNMClickListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRebuildCur();
	afx_msg void OnBnClickedRefresh();
protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
public:
	afx_msg void OnLvnItemchangedListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedEditThird();
};


