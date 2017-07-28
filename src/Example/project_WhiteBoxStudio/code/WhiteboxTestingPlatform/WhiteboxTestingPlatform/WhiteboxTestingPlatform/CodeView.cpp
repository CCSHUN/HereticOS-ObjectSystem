// CodeView.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "CodeView.h"


// CCodeView

IMPLEMENT_DYNCREATE(CCodeView, CFormView)

CCodeView::CCodeView()
	: CFormView(CCodeView::IDD)
{
	
}

CCodeView::~CCodeView()
{
}

void CCodeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCodeView, CFormView)
END_MESSAGE_MAP()


void CCodeView::ProjectChange(BOOL bToTop)
{

}

//要求跟新数据到界面时
void CCodeView::UpDataUi()
{
	m_CodeViewCtl.m_iDataIndex=m_pShareData->m_nReportIndex;
	m_CodeViewCtl.UpdateWindow();
	m_CodeViewCtl.ShowWindow(SW_SHOW);
	m_CodeViewCtl.UpdataUi();

	/*Sleep(2000);
	m_CodeViewCtl.UpdateWindow();
	m_CodeViewCtl.ShowWindow(SW_SHOW);
	m_CodeViewCtl.UpdataUi();*/
	/*m_CodeViewCtl.UpdateWindow();
	m_CodeViewCtl.ShowWindow(SW_SHOW);*/
}
void CCodeView::OnInitialUpdate()
{
	__super::OnInitialUpdate();
	m_pShareData = (CProjectSharedData *)(((CChildFrame *)GetParentFrame())->m_ProjectIndex.pSharedObject);
	((CChildFrame *)GetParentFrame())->m_ProjectIndex.pViewInterface = this;
	m_pShareData->m_pCodeViewCtl=this;
	m_pShareData->init();
	m_CodeViewCtl.Create(IDD_CODEVIEW_DLG,this);
	m_CodeViewCtl.m_pShareData=m_pShareData;

	m_CodeViewCtl.Invalidate();
	m_CodeViewCtl.UpdateWindow();
	//m_CodeViewCtl,UpdateWindow();
	//m_CodeViewCtl.ShowWindow(SW_SHOW);
	//UpdateWindow();
	//ShowWindow(SW_SHOW);
}
// CCodeView 诊断

/*
BOOL CCodeView::PreTranslateMessage(MSG* pMsg)
{
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		if(pMsg->wParam==VK_RETURN)
		{
			/ *UpdateData(TRUE);
			GotoAddr(tstring(m_szAddress.GetBuffer(0)));
			return TRUE;* /
		}
		return GetDlgItem(IDC_STATIC)->PreTranslateMessage(pMsg);
		//pMsg->wParam;
	default:
		return CDialog::PreTranslateMessage(pMsg);

	}
	return CDialog::PreTranslateMessage(pMsg);
}*/

#ifdef _DEBUG
void CCodeView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCodeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCodeView 消息处理程序
