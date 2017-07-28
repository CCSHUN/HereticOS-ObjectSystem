#pragma once
#include "afxcmn.h"
#include "ListCtlStringSort.h"


// CTestUserStandardThirdView 窗体视图

class CTestUserStandardThirdView : public CFormView ,CViewInterfaceForWorkPageManager
{
	DECLARE_DYNCREATE(CTestUserStandardThirdView)

protected:
	CTestUserStandardThirdView();           // 动态创建所使用的受保护的构造函数
	virtual ~CTestUserStandardThirdView();

public:
	enum { IDD = IDD_TESTUSER_STANDARD_THIRD_VIEW };
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
	

	BOOL UpdataUi();

	void UpDataBing(BOOL bToSecond);
	_tagThirdStandardSet m_CurDataSet;
	CStandardSharedData  * m_pShareData;
	CString m_szUniteStandardErrorNum;		//机械走读统一规范
	CString m_szThirdStandardErrorNum;		//PCLINT或者CTester的错误ID
	CString m_szThirdStandardErrorDesc;
	BOOL m_is_manual_check;					//是否需要人工检查
	CString m_szManual_check_MethodSpecify;	//人工复查标准说明，指导测试人员人工复查。
	CString m_szErrorSuggest;
	//BOOL m_is_dealwith;						//是否需要处理

	CString m_ToolType;						//类似"PCLINT", "C++ TESTER"

	afx_msg void OnBnClickedDeleteCur();
	afx_msg void OnBnClickedComplateStandard();

	void ProjectChange(BOOL bToTop);
	BOOL m_is_dealwith;
	CListCtlStringSort m_ThirdStandardList;
	afx_msg void OnBnClickedEditStandard();

	void OnInitialUpdate();
	afx_msg void OnLvnItemchangedReportList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemdblclickReportList(NMHDR *pNMHDR, LRESULT *pResult);



	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReGetObject();
	afx_msg void OnReleaseObjectLock();
	afx_msg void OnGetObjectLock();
	afx_msg void OnCanEdit(CCmdUI *pCmdUI);
	void EnableEdit(BOOL bCanEdit);
	void UpDataObjectUiState();
	BOOL m_bCanEdit;

protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
public:
	afx_msg void OnNMDblclkReportList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult);
};


