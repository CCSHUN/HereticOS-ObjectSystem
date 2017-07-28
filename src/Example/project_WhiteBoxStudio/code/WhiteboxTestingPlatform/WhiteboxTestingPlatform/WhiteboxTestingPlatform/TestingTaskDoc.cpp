// TestingTaskDoc.cpp : 实现文件
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


// CTestingTaskDoc 诊断

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
// CTestingTaskDoc 序列化

void CTestingTaskDoc::Serialize(CArchive& ar)
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
#endif


// CTestingTaskDoc 命令
