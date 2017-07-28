#pragma once

/*
class CCodeHtmlView
{
public:
	CCodeHtmlView(void);
	~CCodeHtmlView(void);
};
*/


#include "htmlui/src/DHtmlViewSpec.h"


//反向调用接口
class CCodeHtmlViewReversedCall
{
public:
	CCodeHtmlViewReversedCall(){};
	~CCodeHtmlViewReversedCall(){};
	virtual void OnHtmlUiPostEdit(CString & szHtmlObject){return;};
protected:

private:
};


class CCodeHtmlView : public CDHtmlViewSpec
{
protected: // create from serialization only

	DECLARE_DYNCREATE(CCodeHtmlView)
	DECLARE_DISPATCH_MAP()

	//to support html's elements event
	DECLARE_DHTML_EVENT_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//an event callback example of html element <input type=button> 
	HRESULT OnButtonPostEdit(IHTMLElement *pElement);
	VOID OnPostEdit(BSTR szData) ;
	void DocumentComplete(LPDISPATCH pDisp, VARIANT* URL);
	
	// Attributes
public:
	virtual void PostNcDestroy() {  };
	CString m_EditData;
	//ChtmlExDoc* GetDocument() const;

	// Operations
public:
	//afx_msg void OnDestroy();
	void ShowCode(CString & szCode,CString & szLine);
	void EmptyCode();

	

	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void init(CCodeHtmlViewReversedCall * pRCall); // called first time after construct
protected:
	CCodeHtmlViewReversedCall * m_pReversedCall;


	// Implementation
public:
	CCodeHtmlView();
	virtual ~CCodeHtmlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

