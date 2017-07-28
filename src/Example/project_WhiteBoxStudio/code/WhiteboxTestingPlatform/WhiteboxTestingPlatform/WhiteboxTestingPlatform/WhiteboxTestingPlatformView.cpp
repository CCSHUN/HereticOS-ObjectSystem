
// WhiteboxTestingPlatformView.cpp : CWhiteboxTestingPlatformView ���ʵ��
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

// CWhiteboxTestingPlatformView ����/����

CWhiteboxTestingPlatformView::CWhiteboxTestingPlatformView()
	: CFormView(CWhiteboxTestingPlatformView::IDD)
{
	// TODO: �ڴ˴���ӹ������

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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CWhiteboxTestingPlatformView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

	SetWindowText(_T("������������"));

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


// CWhiteboxTestingPlatformView ���

#ifdef _DEBUG
void CWhiteboxTestingPlatformView::AssertValid() const
{
	CFormView::AssertValid();
}

void CWhiteboxTestingPlatformView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CWhiteboxTestingPlatformDoc* CWhiteboxTestingPlatformView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWhiteboxTestingPlatformDoc)));
	return (CWhiteboxTestingPlatformDoc*)m_pDocument;
}
#endif //_DEBUG


// CWhiteboxTestingPlatformView ��Ϣ�������

void CWhiteboxTestingPlatformView::OnFileNew()
{
	// TODO: �ڴ���������������
}
