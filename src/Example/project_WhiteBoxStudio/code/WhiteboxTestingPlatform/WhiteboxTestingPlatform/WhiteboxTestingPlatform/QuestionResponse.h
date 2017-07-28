#pragma once

/*
class CQuestionResponse
{
public:
	CQuestionResponse(void);
	~CQuestionResponse(void);
};
*/

#include "htmlui/src/DHtmlViewSpec.h"


//反向调用接口
class CQuestionResponseReversedCall
{
public:
	CQuestionResponseReversedCall(){};
	~CQuestionResponseReversedCall(){};
	virtual void OnHtmlUiPostEdit(CString & szHtmlObject){return;};
protected:
	
private:
};


class CQuestionResponse : public CDHtmlViewSpec
{
protected: // create from serialization only
	
	DECLARE_DYNCREATE(CQuestionResponse)
	DECLARE_DISPATCH_MAP()

	//to support html's elements event
	DECLARE_DHTML_EVENT_MAP()
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//an event callback example of html element <input type=button> 
	HRESULT OnButtonPostEdit(IHTMLElement *pElement);
	VOID OnPostEdit(BSTR szData) ;
	void DocumentComplete(LPDISPATCH pDisp, VARIANT* URL);
	//DDX of html element <input type=radio>
	long m_iControl;
	// Attributes
public:
	virtual void PostNcDestroy() {  };
	CString m_EditData;
	//ChtmlExDoc* GetDocument() const;

	// Operations
public:
	//afx_msg void OnDestroy();
	void InsertHtmlObject(CString & szHtmlObject);
	void EmptyHtmlObject();
	// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
		void init(CQuestionResponseReversedCall * pRCall); // called first time after construct
protected:
	CQuestionResponseReversedCall * m_pReversedCall;
	

// Implementation
public:
	CQuestionResponse();
	virtual ~CQuestionResponse();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

/*
#ifndef _DEBUG  // debug version in htmlExView.cpp
inline ChtmlExDoc* ChtmlExView::GetDocument() const
   { return reinterpret_cast<ChtmlExDoc*>(m_pDocument); }
#endif*/

