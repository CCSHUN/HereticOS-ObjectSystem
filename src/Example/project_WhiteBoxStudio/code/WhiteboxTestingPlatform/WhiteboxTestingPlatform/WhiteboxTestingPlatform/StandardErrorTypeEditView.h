#pragma once
#include "afxwin.h"



// CStandardErrorTypeEditView 窗体视图

class CStandardErrorTypeEditView : public CFormView ,CViewInterfaceForWorkPageManager 
{
	DECLARE_DYNCREATE(CStandardErrorTypeEditView)

protected:
	CStandardErrorTypeEditView();           // 动态创建所使用的受保护的构造函数
	virtual ~CStandardErrorTypeEditView();

public:
	enum { IDD = IDD_STANDARD_FIELD_EDIT };
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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

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
	CListBox m_StandardErrorTypeList;
	CListBox m_StandardErrorClassList;

	void OnInitialUpdate();
	BOOL UpdataUi();
	CStandardSharedData  * m_pShareData;
	_tagMachineCheckStandardTypeLib m_CurMachineCheckStandardTypeLib;
	_tagErrorWarningArray			m_CurErrorWarningArray;
	void UpDataBing(BOOL bToSecond);

	afx_msg void OnBnClickedErrortypeDelete();
	afx_msg void OnBnClickedErrclassDelete();
	afx_msg void OnBnClickedErrtypeAdd();
	CString m_szErrorType;
	afx_msg void OnBnClickedErrclassAdd();
	CString m_szErrorWraning;
};


