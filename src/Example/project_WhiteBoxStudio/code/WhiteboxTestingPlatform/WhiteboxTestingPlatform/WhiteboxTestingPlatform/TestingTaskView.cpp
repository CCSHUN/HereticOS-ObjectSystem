// TestingTaskView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestingTaskView.h"


// CTestingTaskView

IMPLEMENT_DYNCREATE(CTestingTaskView, CFormView)

CTestingTaskView::CTestingTaskView()
	: CFormView(CTestingTaskView::IDD)
{

}

CTestingTaskView::~CTestingTaskView()
{
}

void CTestingTaskView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestingTaskView, CFormView)
END_MESSAGE_MAP()


// CTestingTaskView ���

#ifdef _DEBUG
void CTestingTaskView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTestingTaskView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTestingTaskView ��Ϣ�������
