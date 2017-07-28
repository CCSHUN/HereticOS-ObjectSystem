// ReportDoc.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "ReportDoc.h"


// CReportDoc

IMPLEMENT_DYNCREATE(CReportDoc, CDocument)

CReportDoc::CReportDoc()
{
}

void  CReportDoc::SetTitle(LPCTSTR lpszTitle)
{
	

	//theApp.m_pMainWnd->SetWindowText(szDocTitle.c_str());
	CDocument::SetTitle(lpszTitle);
	
}

BOOL CReportDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	SetTitle(TEST_REPORT_MAKE_WORKSPACE);

	return TRUE;
}

CReportDoc::~CReportDoc()
{
}


BEGIN_MESSAGE_MAP(CReportDoc, CDocument)
END_MESSAGE_MAP()


// CReportDoc 诊断

#ifdef _DEBUG
void CReportDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CReportDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CReportDoc 序列化

void CReportDoc::Serialize(CArchive& ar)
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


// CReportDoc 命令
