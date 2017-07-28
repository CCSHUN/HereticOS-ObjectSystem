// TestingTaskConfigDoc.cpp : 实现文件
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


// CTestingTaskConfigDoc 诊断

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
// CTestingTaskConfigDoc 序列化

void CTestingTaskConfigDoc::Serialize(CArchive& ar)
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


// CTestingTaskConfigDoc 命令
