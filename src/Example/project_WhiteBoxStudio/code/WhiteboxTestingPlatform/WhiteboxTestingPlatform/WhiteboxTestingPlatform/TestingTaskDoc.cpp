// TestingTaskDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestingTaskDoc.h"


// CTestingTaskDoc

IMPLEMENT_DYNCREATE(CTestingTaskDoc, CDocument)

CTestingTaskDoc::CTestingTaskDoc()
{
}

BOOL CTestingTaskDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CTestingTaskDoc::~CTestingTaskDoc()
{
}


BEGIN_MESSAGE_MAP(CTestingTaskDoc, CDocument)
END_MESSAGE_MAP()


// CTestingTaskDoc ���

#ifdef _DEBUG
void CTestingTaskDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CTestingTaskDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CTestingTaskDoc ���л�

void CTestingTaskDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}
#endif


// CTestingTaskDoc ����
