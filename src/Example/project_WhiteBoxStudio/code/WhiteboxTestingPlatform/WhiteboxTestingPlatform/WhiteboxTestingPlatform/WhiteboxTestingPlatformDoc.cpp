
// WhiteboxTestingPlatformDoc.cpp : CWhiteboxTestingPlatformDoc ���ʵ��
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"

#include "WhiteboxTestingPlatformDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWhiteboxTestingPlatformDoc

IMPLEMENT_DYNCREATE(CWhiteboxTestingPlatformDoc, CDocument)

BEGIN_MESSAGE_MAP(CWhiteboxTestingPlatformDoc, CDocument)
END_MESSAGE_MAP()


// CWhiteboxTestingPlatformDoc ����/����

CWhiteboxTestingPlatformDoc::CWhiteboxTestingPlatformDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CWhiteboxTestingPlatformDoc::~CWhiteboxTestingPlatformDoc()
{
}

BOOL CWhiteboxTestingPlatformDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//SetTitle(L"��������");

	return TRUE;
}




// CWhiteboxTestingPlatformDoc ���л�

void CWhiteboxTestingPlatformDoc::Serialize(CArchive& ar)
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


// CWhiteboxTestingPlatformDoc ���

#ifdef _DEBUG
void CWhiteboxTestingPlatformDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWhiteboxTestingPlatformDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWhiteboxTestingPlatformDoc ����

void CWhiteboxTestingPlatformDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: �ڴ����ר�ô����/����û���

	CDocument::SetTitle(lpszTitle);
}
