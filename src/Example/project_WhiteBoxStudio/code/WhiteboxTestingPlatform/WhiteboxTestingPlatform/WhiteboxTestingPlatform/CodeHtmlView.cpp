// htmlExView.cpp : implementation of the ChtmlExView class
//

#include "stdafx.h"
#import <mshtml.tlb>
#include "CodeHtmlView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ChtmlExView

IMPLEMENT_DYNCREATE(CCodeHtmlView, CDHtmlViewSpec)

BEGIN_MESSAGE_MAP(CCodeHtmlView, CDHtmlViewSpec)
	//ON_WM_DESTROY()
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CCodeHtmlView)
	//DHTML_EVENT_ONCLICK(_T("getHtml"), OnButtonPostEdit)
	//DHTML_EVENT_ONCLICK(_T("btnEnd"), OnButtonPostEdit)
END_DHTML_EVENT_MAP()
// ChtmlExView construction/destruction

// CDataRecordView 
//js call隐射
BEGIN_DISPATCH_MAP(CCodeHtmlView, CHtmlView)
	//{{AFX_DISPATCH_MAP(CMyHtmlView)
	//DISP_PROPERTY_EX(CHtmlEditor, "version", GetVersion, SetVersion, VT_BSTR)
	DISP_FUNCTION(CCodeHtmlView, "OnPostEdit", OnPostEdit, VT_NULL, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

void CCodeHtmlView::DocumentComplete(LPDISPATCH pDisp, VARIANT* URL)
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



void CCodeHtmlView::ShowCode(CString & szCode,CString & szLine)
{
	CComVariant Var;
	//szHtmlObject+=_T("InsertHtmlObject");
	CallJScript(CString("ShowCode"),szCode,szLine,&Var);

}

void CCodeHtmlView::EmptyCode()
{
	CComVariant Var;
	CStringArray sza;
	//szHtmlObject+=_T("InsertHtmlObject");
	CallJScript(CString("EmptyCode"),sza,&Var);

}


VOID CCodeHtmlView::OnPostEdit(BSTR szData) 
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
void CCodeHtmlView::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlViewSpec::DoDataExchange(pDX);
	//DDX_DHtml_Radio(pDX,_T("btnControl"),m_iControl);
}


HRESULT CCodeHtmlView::OnButtonPostEdit(IHTMLElement *pElement)
{
	UpdateData();
	/*CString str;
	str.Format(_T("value=%d\n"),m_iControl);
	AfxMessageBox(str);
	return S_OK;*/
	return S_OK;
}
CCodeHtmlView::CCodeHtmlView()
{
	m_pReversedCall=NULL;

}

CCodeHtmlView::~CCodeHtmlView()
{
}

BOOL CCodeHtmlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CDHtmlViewSpec::PreCreateWindow(cs);
}

void CCodeHtmlView::init(CCodeHtmlViewReversedCall * pRCall)
{
	//屏蔽IE的文件拖放功能
	m_pReversedCall=pRCall;
	SetRegisterAsDropTarget(FALSE);
	//允许脚本调用
	EnableAutomation();
	GotoUrl(_T("./ui/CodeHtmlView.html"));
	//GotoUrl(_T("../res/main/main.htm"));
}


// ChtmlExView printing



// ChtmlExView diagnostics

#ifdef _DEBUG
void CCodeHtmlView::AssertValid() const
{
	CDHtmlViewSpec::AssertValid();
}

void CCodeHtmlView::Dump(CDumpContext& dc) const
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
