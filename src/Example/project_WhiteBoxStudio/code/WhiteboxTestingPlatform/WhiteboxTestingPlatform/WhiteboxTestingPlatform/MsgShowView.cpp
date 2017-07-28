// MsgShowView.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "MsgShowView.h"


// CMsgShowView

IMPLEMENT_DYNCREATE(CMsgShowView, CFormView)

CMsgShowView::CMsgShowView()
	: CFormView(CMsgShowView::IDD)
{

}

CMsgShowView::~CMsgShowView()
{
}

void CMsgShowView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMsgShowView, CFormView)
END_MESSAGE_MAP()


// CMsgShowView 诊断

#ifdef _DEBUG
void CMsgShowView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMsgShowView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMsgShowView 消息处理程序
