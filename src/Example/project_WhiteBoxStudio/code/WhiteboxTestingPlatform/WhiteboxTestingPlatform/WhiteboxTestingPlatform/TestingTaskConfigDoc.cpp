// TestingTaskConfigDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestingTaskConfigDoc.h"


// CTestingTaskConfigDoc

IMPLEMENT_DYNCREATE(CTestingTaskConfigDoc, CDocument)

CTestingTaskConfigDoc::CTestingTaskConfigDoc()
{
}

BOOL CTestingTaskConfigDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	SetTitle(TEST_PROJECTCONFIG_WORKSPACE);

	return TRUE;
}

CTestingTaskConfigDoc::~CTestingTaskConfigDoc()
{
}


BEGIN_MESSAGE_MAP(CTestingTaskConfigDoc, CDocument)
END_MESSAGE_MAP()


// CTestingTaskConfigDoc ���

#ifdef _DEBUG
void CTestingTaskConfigDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CTestingTaskConfigDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CTestingTaskConfigDoc ���л�

void CTestingTaskConfigDoc::Serialize(CArchive& ar)
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


// CTestingTaskConfigDoc ����
