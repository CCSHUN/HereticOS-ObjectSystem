
// WhiteboxTestingPlatformDoc.cpp : CWhiteboxTestingPlatformDoc 类的实现
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


// CWhiteboxTestingPlatformDoc 构造/析构

CWhiteboxTestingPlatformDoc::CWhiteboxTestingPlatformDoc()
{
	// TODO: 在此添加一次性构造代码

}

CWhiteboxTestingPlatformDoc::~CWhiteboxTestingPlatformDoc()
{
}

BOOL CWhiteboxTestingPlatformDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//SetTitle(L"任务配置");

	return TRUE;
}




// CWhiteboxTestingPlatformDoc 序列化

void CWhiteboxTestingPlatformDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CWhiteboxTestingPlatformDoc 诊断

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


// CWhiteboxTestingPlatformDoc 命令

void CWhiteboxTestingPlatformDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: 在此添加专用代码和/或调用基类

	CDocument::SetTitle(lpszTitle);
}
