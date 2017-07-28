// WorkSheetView.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "WorkSheetView.h"


// CWorkSheetView

IMPLEMENT_DYNCREATE(CWorkSheetView, CFormView)

CWorkSheetView::CWorkSheetView()
	: CFormView(CWorkSheetView::IDD)
{

}

CWorkSheetView::~CWorkSheetView()
{
}

void CWorkSheetView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWorkSheetView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CWorkSheetView::OnBnClickedButton1)
END_MESSAGE_MAP()


// CWorkSheetView 诊断

#ifdef _DEBUG
void CWorkSheetView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CWorkSheetView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CWorkSheetView 消息处理程序

void CWorkSheetView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
