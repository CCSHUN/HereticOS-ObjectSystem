#pragma once


#include "CodeViewDlg.h"
// CCodeView 窗体视图

class CCodeView : public CFormView, public CViewInterfaceForWorkPageManager
{
	DECLARE_DYNCREATE(CCodeView)

protected:
	CCodeView();           // 动态创建所使用的受保护的构造函数
	virtual ~CCodeView();

public:
	CCodeViewDlg m_CodeViewCtl;
	CProjectSharedData *m_pShareData;
	virtual void OnInitialUpdate();
	void ProjectChange(BOOL bToTop);
	void UpDataUi();

	enum { IDD = IDD_CODEVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


