// WorkSheetView.cpp : ʵ���ļ�
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


// CWorkSheetView ���

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


// CWorkSheetView ��Ϣ�������

void CWorkSheetView::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
