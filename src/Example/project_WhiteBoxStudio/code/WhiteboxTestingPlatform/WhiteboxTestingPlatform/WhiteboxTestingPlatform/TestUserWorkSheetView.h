#pragma once
#include "afxwin.h"
#include "afxdtctl.h"



// CTestUserWorkSheetView 窗体视图

class CTestUserWorkSheetView : public CFormView, public CViewInterfaceForWorkPageManager
{
	DECLARE_DYNCREATE(CTestUserWorkSheetView)

protected:
	CTestUserWorkSheetView();           // 动态创建所使用的受保护的构造函数
	virtual ~CTestUserWorkSheetView();

public:
	enum { IDD = IDD_TEST_WORKSHEET_VIEW };
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
	BOOL InitDevList();

	void SetCtrlDate(CDateTimeCtrl &ctrlDate, const CString &sDate);

	CProjectSharedData *m_pShareData;
	void GetWorkSheetData();
	void InitComboBoxData();
	afx_msg void OnBnClickedButtonSave();
	CComboBox m_cmbCheckRange;
	CDateTimeCtrl m_dateApply;
	CDateTimeCtrl m_dateCheck;
	CComboBox m_cmbApply;
};


