// WorkSheetDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "WorkSheetDoc.h"


// CWorkSheetDoc

IMPLEMENT_DYNCREATE(CWorkSheetDoc, CDocument)

CWorkSheetDoc::CWorkSheetDoc()
{
}

BOOL CWorkSheetDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	SetTitle(TEST_WORKSHEET_EDIT_WORKSPACE);
	return TRUE;
}

CWorkSheetDoc::~CWorkSheetDoc()
{
}


BEGIN_MESSAGE_MAP(CWorkSheetDoc, CDocument)
END_MESSAGE_MAP()


// CWorkSheetDoc ���

#ifdef _DEBUG
void CWorkSheetDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CWorkSheetDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CWorkSheetDoc ���л�

void CWorkSheetDoc::Serialize(CArchive& ar)
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


// CWorkSheetDoc ����
