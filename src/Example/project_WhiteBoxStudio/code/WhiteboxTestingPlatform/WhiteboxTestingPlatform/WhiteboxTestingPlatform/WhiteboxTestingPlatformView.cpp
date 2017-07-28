
// WhiteboxTestingPlatformView.cpp : CWhiteboxTestingPlatformView 类的实现
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"

#include "WhiteboxTestingPlatformDoc.h"
#include "WhiteboxTestingPlatformView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWhiteboxTestingPlatformView

IMPLEMENT_DYNCREATE(CWhiteboxTestingPlatformView, CFormView)

BEGIN_MESSAGE_MAP(CWhiteboxTestingPlatformView, CFormView)
	ON_COMMAND(ID_FILE_NEW, &CWhiteboxTestingPlatformView::OnFileNew)
END_MESSAGE_MAP()

// CWhiteboxTestingPlatformView 构造/析构

CWhiteboxTestingPlatformView::CWhiteboxTestingPlatformView()
	: CFormView(CWhiteboxTestingPlatformView::IDD)
{
	// TODO: 在此处添加构造代码

}

CWhiteboxTestingPlatformView::~CWhiteboxTestingPlatformView()
{
}

void CWhiteboxTestingPlatformView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CWhiteboxTestingPlatformView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CWhiteboxTestingPlatformView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

	SetWindowText(_T("测试任务配置"));

}

void CWhiteboxTestingPlatformView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWhiteboxTestingPlatformView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CWhiteboxTestingPlatformView 诊断

#ifdef _DEBUG
void CWhiteboxTestingPlatformView::AssertValid() const
{
	CFormView::AssertValid();
}

void CWhiteboxTestingPlatformView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CWhiteboxTestingPlatformDoc* CWhiteboxTestingPlatformView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWhiteboxTestingPlatformDoc)));
	return (CWhiteboxTestingPlatformDoc*)m_pDocument;
}
#endif //_DEBUG


// CWhiteboxTestingPlatformView 消息处理程序

void CWhiteboxTestingPlatformView::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
}
