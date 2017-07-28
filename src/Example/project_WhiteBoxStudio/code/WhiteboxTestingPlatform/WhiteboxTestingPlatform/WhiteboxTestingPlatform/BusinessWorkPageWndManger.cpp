#include "StdAfx.h"
#include "BusinessWorkPageWndManger.h"

#include "WhiteboxTestingPlatform.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "WhiteboxTestingPlatformDoc.h"
#include "TestingTaskDoc.h"
#include "TestingTaskConfigDoc.h"
#include "ReportDoc.h"

#include "WhiteboxTestingPlatformView.h"
#include "TestingTaskView.h"
#include "TestingTaskConfigView.h"
#include "ReportView.h"
#include "WorkSheetDoc.h"
#include "WorkSheetView.h"
#include "TestUserWorkSheetView.h"
#include "TestUserReportComplateView.h"
#include "TestUserReportManualMakeView.h"
#include "TestUserReportNoFindStandardView.h"
#include "DevUserReportView.h"

#include "TestUserStandardThirdView.h"
#include "TestUserStandardUniteView.h"
#include "StandardErrorTypeEditView.h"
#include "AdminUserEditView.h"
#include "MsgShowView.h"
#include "UnitAutoReport.h"

#include "AutoStructDesignView.h"

CBusinessWorkPageWndManger::CBusinessWorkPageWndManger(void)
{
}

CBusinessWorkPageWndManger::~CBusinessWorkPageWndManger(void)
{

}

CMyDocTemplate::CMyDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
			   CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass)
			   : CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass)
{

}

BOOL CMyDocTemplate::OpenDocument(_tagWorkUiContext & UiContext,tstring & szTitle)
{
	CDocument* pDocument = CreateNewDocument();
	if (pDocument == NULL)
	{
		TRACE(traceAppMsg, 0, "CDocTemplate::CreateNewDocument returned NULL.\n");
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return NULL;
	}
	ASSERT_VALID(pDocument);

	BOOL bAutoDelete = pDocument->m_bAutoDelete;
	pDocument->m_bAutoDelete = FALSE;   // don't destroy if something goes wrong
	CFrameWnd* pFrame = CreateNewFrame(pDocument, NULL);
	CChildFrame * pChildFrame=(CChildFrame *)pFrame;
	pChildFrame->m_ProjectIndex=UiContext.index;
	//pChildFrame->m_ProjectIndex.pViewInterface=

	


	UiContext.pContext=pChildFrame;

	pDocument->m_bAutoDelete = bAutoDelete;
	if (pFrame == NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		delete pDocument;       // explicit delete on error
		return NULL;
	}
	ASSERT_VALID(pFrame);

	

	SetDefaultTitle(pDocument);

	// avoid creating temporary compound file when starting up invisible
	/*if (!bMakeVisible)
		pDocument->m_bEmbedded = TRUE;*/

	if (!pDocument->OnNewDocument())
	{
		// user has be alerted to what failed in OnNewDocument
		TRACE(traceAppMsg, 0, "CDocument::OnNewDocument returned FALSE.\n");
		pFrame->DestroyWindow();
		return FALSE;
	}


	

	if(szTitle.length())
	{
		tstring szDocTitle;
		szDocTitle+=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginUserType()+_T("-");
		szDocTitle+=_T("[")+theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()+_T("]");
		
		szDocTitle+=_T(" doc [")+szTitle+_T("]");
		//theApp.m_pMainWnd->SetWindowText(szDocTitle);

		pDocument->SetTitle(szTitle.c_str());
	}

	InitialUpdateFrame(pFrame, pDocument, TRUE);

	/*POSITION Pos = pDocument->GetFirstViewPosition();
	// Exists a view for that document type?
	CView *pView = ()pDocument->GetNextView(Pos);
	pChildFrame->m_ProjectIndex.pViewInterface=pDocument->GetFirstViewPosition()*/
	return TRUE;
}


//IMPLEMENT_DYNAMIC(CMyDocTemplate, CDocTemplate)
//IMPLEMENT_DYNAMIC(CMyDocTemplate, CDocTemplate)

BOOL CBusinessWorkPageWndManger::ShowWorkPage(TreeIndex * pPageIndex)
{
	
	//检查是否切换项目Tab
	//tstring szDocTitle;
	if(m_CurPageIndex.IndexList.size()==pPageIndex->IndexList.size())
	{
		for(unsigned int i=0;i<m_CurPageIndex.IndexList.size();i++)
		{
			if((m_CurPageIndex.IndexList[i]!=pPageIndex->IndexList[i]))
			{
				//有一个不等 则是不同项目
				
				((CMainFrame * )theApp.m_pMainWnd)->UpdateTabs();
				break;
			}
		}
		//return FALSE;
	}else
	{
		((CMainFrame * )theApp.m_pMainWnd)->UpdateTabs();

	}
	m_CurPageIndex=*pPageIndex;
	pPageIndex->bProjectActive=TRUE;

	/*if((m_CurPageIndex.szProject!=PageIndex->szProject)||
		(m_CurPageIndex.szChildProject!=PageIndex->szChildProject))
	{
		m_CurPageIndex=*PageIndex;
		((CMainFrame * )theApp.m_pMainWnd)->UpdateTabs();
		
	}*/

	//创建或者定位界面
	//查找页面是否已经打开
	for(unsigned int i=0;i<m_UiList.size();i++)
	{
		if(m_UiList[i].index.IndexList.size()==pPageIndex->IndexList.size())
		{
			BOOL bSame=TRUE;
			for(unsigned int n=0;n<pPageIndex->IndexList.size();n++)
			{
				if(m_UiList[i].index.IndexList[n]!=pPageIndex->IndexList[n])
				{
					bSame=FALSE;
				}
			}
			if(m_UiList[i].index.szPageName!=pPageIndex->szPageName)
			{
				bSame=FALSE;
			}
			if(bSame)
			{
				//定位到那个界面去
				CWnd *pWnd=(CWnd *)m_UiList[i].pContext;
				WINDOWPLACEMENT wpl;
				pWnd->GetWindowPlacement(&wpl);
				if( SW_SHOWMINIMIZED  == wpl.showCmd )// Iconized window must be restored
				{ 
					wpl.showCmd = SW_RESTORE;
					if( WPF_RESTORETOMAXIMIZED == wpl.flags )
						wpl.showCmd = SW_SHOWMAXIMIZED;

					pWnd->SetWindowPlacement(&wpl);
				}
				else
				{ 
					wpl.showCmd = SW_RESTORE; // Bring window to top
					pWnd->SetWindowPlacement(&wpl);
					pWnd->BringWindowToTop();
				}

				
				/*szDocTitle+=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginUserType()+_T("-");
				szDocTitle+=_T("[")+theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()+_T("]");

				szDocTitle+=_T(" doc [")+m_UiList[i].index.szPageName+_T("]");
				theApp.m_pMainWnd->SetWindowText(szDocTitle.c_str());*/

				return TRUE;
			}
		}
		
	}

	//没有定位到标签，则创建对应的业务界面
	_tagWorkUiContext UiContext;
	UiContext.index=*pPageIndex;

	//判断确定要创建的界面
	tstring szTitle;
	//StandardErrorTypeEditView
	if(pPageIndex->szPageName==TEST_REPORT_MAKE_WORKSPACE)
	{
		if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditTest())
		{
			szTitle=TEST_REPORT_MAKE_WORKSPACE_COMPLATE;
			m_pReportDocTpl1->OpenDocument(UiContext,szTitle);
			szTitle=TEST_REPORT_MAKE_WORKSPACE_MANUAL_MAKE;
			m_pReportDocTpl2->OpenDocument(UiContext,szTitle);
			szTitle=TEST_REPORT_MAKE_WORKSPACE_NOFINDSTANDARD;
			m_pReportDocTpl3->OpenDocument(UiContext,szTitle);
		}

		//if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditProject())
		{
			szTitle=TEST_REPORT_MAKE_WORKSPACE_DEVREPORT;
			m_pReportDocTpl4->OpenDocument(UiContext,szTitle);
		}
		

		

	}else if(pPageIndex->szPageName==TEST_WORKSHEET_EDIT_WORKSPACE)
	{
		szTitle=TEST_WORKSHEET_EDIT_WORKSPACE;
		m_pWorkSheepDocTpl->OpenDocument(UiContext,szTitle);
	}else if(pPageIndex->szPageName==TEST_PROJECTCONFIG_WORKSPACE)
	{
		//if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditTest())
		{
			szTitle=TEST_PROJECTCONFIG_WORKSPACE;
			m_pTestingTaskConfigDocTpl->OpenDocument(UiContext,szTitle);
		}
		
	}else if(pPageIndex->szPageName==TEST_STANDARD_UNITE_WORKSPACE)
	{
		szTitle=TEST_STANDARD_UNITE_WORKSPACE;
		m_pTestStandardUniteManagerTpl->OpenDocument(UiContext,szTitle);
	}else if(pPageIndex->szPageName==TEST_STANDARD_THIRD_WORKSPACE)
	{
		szTitle=TEST_STANDARD_THIRD_WORKSPACE;
		m_pTestStandardThirdManagerTpl->OpenDocument(UiContext,szTitle);
	}else if(pPageIndex->szPageName==TEST_STANDARD_ERROR_TYPE_WORKSPACE)
	{
		szTitle=TEST_STANDARD_ERROR_TYPE_WORKSPACE;
		m_pTestStandardErrorTypeManagerTpl->OpenDocument(UiContext,szTitle);
	}else if(pPageIndex->szPageName==ADMIN_USER_WORKSPACE)
	{
		szTitle=ADMIN_USER_WORKSPACE;
		m_pUserManagerTpl->OpenDocument(UiContext,szTitle);
	}else if(pPageIndex->szPageName==TEST_REPORT_MAKE_WORKSPACE_CODEVIEW)
	{
		szTitle=TEST_REPORT_MAKE_WORKSPACE_CODEVIEW;
		m_pCodeViewTpl->OpenDocument(UiContext,szTitle);
	}else if(pPageIndex->szPageName==TEST_REPORT_MAKE_WORKSPACE_UNITREPORT)
	{
		szTitle=TEST_REPORT_MAKE_WORKSPACE_UNITREPORT;
		m_pUnitReportDocTpl->OpenDocument(UiContext,szTitle);
	}else if(pPageIndex->szPageName==ADMIN_STRUCT_DESIGN_WORKSPACE)
	{
		szTitle=ADMIN_STRUCT_DESIGN_WORKSPACE;
		m_pStructDesignManagerTpl->OpenDocument(UiContext,szTitle);
	}else 
	{
		if(pPageIndex->szPageType==ADDR_MESSAGE)
		{
			szTitle=pPageIndex->szPageName;
			m_pMsgShowTpl->OpenDocument(UiContext,szTitle);
		}else
		{
			return FALSE;
		}

	}
	

	

	m_UiList.push_back(UiContext);
	
	
	
	return TRUE;
}

BOOL CBusinessWorkPageWndManger::init()
{
	m_pTestingTaskConfigDocTpl = new CMyDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CTestingTaskConfigView));
	if (!m_pTestingTaskConfigDocTpl)
		return FALSE;
	//AddDocTemplate(m_pTestingTaskConfigDocTpl);

	m_pReportDocTpl1 = new CMyDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CTestUserReportComplateView));

	if (!m_pReportDocTpl1)
		return FALSE;

	m_pReportDocTpl2 = new CMyDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CTestUserReportManualMakeView));

	if (!m_pReportDocTpl2)
		return FALSE;

	m_pReportDocTpl3 = new CMyDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CTestUserReportNoFindStandardView));

	if (!m_pReportDocTpl3)
		return FALSE;

	m_pReportDocTpl4 = new CMyDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CDevUserReportView));

	if (!m_pReportDocTpl4)
		return FALSE;

	m_pWorkSheepDocTpl = new CMyDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CTestUserWorkSheetView));
	if (!m_pWorkSheepDocTpl)
		return FALSE;

	//标准编辑区
	m_pTestStandardUniteManagerTpl = new CMyDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CTestUserStandardUniteView));
	if (!m_pTestStandardUniteManagerTpl)
		return FALSE;

	m_pTestStandardThirdManagerTpl = new CMyDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CTestUserStandardThirdView));
	if (!m_pTestStandardThirdManagerTpl)
		return FALSE;

	m_pTestStandardErrorTypeManagerTpl= new CMyDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CStandardErrorTypeEditView));

	if (!m_pTestStandardErrorTypeManagerTpl)
		return FALSE;

	m_pUserManagerTpl= new CMyDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CAdminUserEditView));

	if (!m_pUserManagerTpl)
		return FALSE;

	m_pCodeViewTpl= new CMyDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CCodeView));

	
	if (!m_pCodeViewTpl)
		return FALSE;

	m_pMsgShowTpl= new CMyDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CMsgShowView));


	if (!m_pMsgShowTpl)
		return FALSE;


	m_pUnitReportDocTpl= new CMyDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CUnitAutoReport));


	if (!m_pUnitReportDocTpl)
		return FALSE;

	m_pStructDesignManagerTpl= new CMyDocTemplate(IDR_WhiteboxTestingTYPE,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CAutoStructDesignView));


	if (!m_pStructDesignManagerTpl)
		return FALSE;

	

	return TRUE;
}

BOOL CBusinessWorkPageWndManger::CanTab(TreeIndex & PageIndex)
{

	if(m_CurPageIndex.IndexList.size()==PageIndex.IndexList.size())
	{
		for(unsigned int i=0;i<m_CurPageIndex.IndexList.size()-1;i++)
		{
			if((m_CurPageIndex.IndexList[i]!=PageIndex.IndexList[i]))
			{
				goto NotTab;
			}
		}
		//路径相同则可tab管理
		//
		if(PageIndex.bProjectActive==FALSE)
		{
			//刷到前台项目组
			PageIndex.pViewInterface->ProjectChange(TRUE);
			PageIndex.bProjectActive=TRUE;
		}
		return TRUE;
	}

NotTab:
	if(PageIndex.bProjectActive==TRUE)
	{
		//刷到后台项目组
		PageIndex.pViewInterface->ProjectChange(FALSE);
		PageIndex.bProjectActive=FALSE;
	}
	return FALSE;
}


