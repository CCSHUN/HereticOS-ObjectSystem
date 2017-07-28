// ReportView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "ReportView.h"


// CReportView

IMPLEMENT_DYNCREATE(CReportView, CFormView)

CReportView::CReportView()
	: CFormView(CReportView::IDD)
{

}

CReportView::~CReportView()
{
}

void CReportView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REPORT, m_lstReport);
}

BEGIN_MESSAGE_MAP(CReportView, CFormView)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CReportView::OnLvnItemchangedList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_REPORT, &CReportView::OnLvnItemchangedListReport)
END_MESSAGE_MAP()


// CReportView ���

#ifdef _DEBUG
void CReportView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CReportView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CReportView ��Ϣ�������

void CReportView::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void CReportView::OnLvnItemchangedListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
