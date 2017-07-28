// htmlExView.cpp : implementation of the ChtmlExView class
//

#include "stdafx.h"
#import <mshtml.tlb>
#include "QuestionResponse.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ChtmlExView

IMPLEMENT_DYNCREATE(CQuestionResponse, CDHtmlViewSpec)

BEGIN_MESSAGE_MAP(CQuestionResponse, CDHtmlViewSpec)
	//ON_WM_DESTROY()
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CQuestionResponse)
	//DHTML_EVENT_ONCLICK(_T("getHtml"), OnButtonPostEdit)
	//DHTML_EVENT_ONCLICK(_T("btnEnd"), OnButtonPostEdit)
END_DHTML_EVENT_MAP()
// ChtmlExView construction/destruction

// CDataRecordView 
//js call隐射
BEGIN_DISPATCH_MAP(CQuestionResponse, CHtmlView)
	//{{AFX_DISPATCH_MAP(CMyHtmlView)
	//DISP_PROPERTY_EX(CHtmlEditor, "version", GetVersion, SetVersion, VT_BSTR)
	DISP_FUNCTION(CQuestionResponse, "OnPostEdit", OnPostEdit, VT_NULL, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

void CQuestionResponse::DocumentComplete(LPDISPATCH pDisp, VARIANT* URL)
{
	CHtmlView::DocumentComplete(pDisp, URL);

	MSHTML::IHTMLDocument2Ptr ipDocument=GetHtmlDocument();
	if(ipDocument)
	{
		MSHTML::IHTMLElementPtr  ipBody;
		ipDocument->get_body(&ipBody);
		LPDISPATCH pDispatch = GetIDispatch(TRUE);
		HRESULT hr = ipBody->setAttribute(L"external", _variant_t(pDispatch, false), 0);
	}  
}



void CQuestionResponse::InsertHtmlObject(CString & szHtmlObject)
{
	CComVariant Var;
	//szHtmlObject+=_T("InsertHtmlObject");
	CallJScript(CString("InsertMessage"),szHtmlObject,&Var);

}

void CQuestionResponse::EmptyHtmlObject()
{
	CComVariant Var;
	CStringArray sza;
	//szHtmlObject+=_T("InsertHtmlObject");
	CallJScript(CString("EmptyMessage"),sza,&Var);

}


VOID CQuestionResponse::OnPostEdit(BSTR szData) 
{
	//CString str(szData);
	m_EditData=(TCHAR *)szData;
	//AfxMessageBox(m_EditData.GetBuffer());
	//InsertHtmlObject(m_EditData);
	if(m_pReversedCall)
	{
		m_pReversedCall->OnHtmlUiPostEdit(m_EditData);
	}
}
void CQuestionResponse::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlViewSpec::DoDataExchange(pDX);
	DDX_DHtml_Radio(pDX,_T("btnControl"),m_iControl);
}


HRESULT CQuestionResponse::OnButtonPostEdit(IHTMLElement *pElement)
{
	UpdateData();
	CString str;
	str.Format(_T("value=%d\n"),m_iControl);
	AfxMessageBox(str);
	return S_OK;
}
CQuestionResponse::CQuestionResponse()
{
	m_pReversedCall=NULL;

}

CQuestionResponse::~CQuestionResponse()
{
}

BOOL CQuestionResponse::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CDHtmlViewSpec::PreCreateWindow(cs);
}

void CQuestionResponse::init(CQuestionResponseReversedCall * pRCall)
{
	//屏蔽IE的文件拖放功能
	m_pReversedCall=pRCall;
	SetRegisterAsDropTarget(FALSE);
	//允许脚本调用
	EnableAutomation();
	GotoUrl(_T("./ui/QuestionResponse.html"));
	//GotoUrl(_T("../res/main/main.htm"));
}


// ChtmlExView printing



// ChtmlExView diagnostics

#ifdef _DEBUG
void CQuestionResponse::AssertValid() const
{
	CDHtmlViewSpec::AssertValid();
}

void CQuestionResponse::Dump(CDumpContext& dc) const
{
	CDHtmlViewSpec::Dump(dc);
}

/*
ChtmlExDoc* ChtmlExView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(ChtmlExDoc)));
	return (ChtmlExDoc*)m_pDocument;
}*/
#endif //_DEBUG


// ChtmlExView message handlers
