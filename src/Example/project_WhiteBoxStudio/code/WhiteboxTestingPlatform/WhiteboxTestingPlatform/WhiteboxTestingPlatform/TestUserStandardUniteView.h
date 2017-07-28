#pragma once
#include "afxcmn.h"

#include "ListCtlStringSort.h"

// CTestUserStandardUniteView 窗体视图

class CTestUserStandardUniteView : public CFormView,CViewInterfaceForWorkPageManager
{
	DECLARE_DYNCREATE(CTestUserStandardUniteView)

protected:
	CTestUserStandardUniteView();           // 动态创建所使用的受保护的构造函数
	virtual ~CTestUserStandardUniteView();

public:
	enum { IDD = IDD_TESTUSER_STANDARD_UNITE_VIEW };
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
	afx_msg void OnBnClickedNewStandard();
	void OnInitialUpdate();
	BOOL UpdataUi();
	CListCtlStringSort m_UniteStandardList;
	CStandardSharedData  * m_pShareData;
	
	afx_msg void OnBnClickedComplateStandard();
	afx_msg void OnBnClickedEditStandard();
	afx_msg void OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReGetObject();
	afx_msg void OnReleaseObjectLock();
	afx_msg void OnGetObjectLock();
	void EnableEdit(BOOL bCanEdit);
	void UpDataObjectUiState();
	BOOL m_bCanEdit;

	void ProjectChange(BOOL bToTop);

	void UpDataBing(BOOL bToSecond);

	CString m_szDesc;
	CString m_szErrorNum;
	CString m_szErrorSuggest;
	CString m_szErrorType;
	CString m_szErrorWarning;

	_tagMachineCheckStandardSet m_CurDataSet;


	afx_msg void OnLvnItemchangedUinteStandardList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkUinteStandardList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDeleteCur();
	afx_msg void OnCanEdit(CCmdUI *pCmdUI);
protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
};


