#pragma once

#include "ProjectDataModel.h"
#include "StandardDataModel.h"
#include "UiTypeNameDef.h"
#include "UiStructDef.h"
#include "UserDataModel.h"
#include "AccessControl_Local.h"
#include "MsgDataModule.h"


class CMyDocTemplate :public CMultiDocTemplate
{
	//DECLARE_DYNAMIC(CMyDocTemplate)
public:

	//CMyDocTemplate(){};
	virtual ~CMyDocTemplate(){};
	CMyDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
		CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);
	
	BOOL OpenDocument(_tagWorkUiContext & UiContext,tstring & szTitle);
protected:

private:
};


class CBusinessWorkPageWndManger
{
public:
	CUserDataModel		m_UserDataModel;
	CStandardDataModel m_StandardDataModel;
	CProjectDataModel m_ProjectDataModel;
	CMsgDataModule		m_MsgDataModule;
	TreeIndex m_CurPageIndex;

	CAccessControl_Local m_AccessDataModel;
	//索引到指定业务窗口
	BOOL ShowWorkPage(TreeIndex * PageIndex);
	BOOL CanTab(TreeIndex & PageIndex);
	BOOL init();
	CBusinessWorkPageWndManger(void);
	~CBusinessWorkPageWndManger(void);
	

protected:

	
	CMyDocTemplate * m_pTestingTaskConfigDocTpl ;

	CMyDocTemplate * m_pReportDocTpl1 ;
	CMyDocTemplate * m_pReportDocTpl2 ;
	CMyDocTemplate * m_pReportDocTpl3 ;
	CMyDocTemplate * m_pReportDocTpl4 ;

	CMyDocTemplate * m_pUnitReportDocTpl ;


	CMyDocTemplate * m_pWorkSheepDocTpl ;

	CMyDocTemplate * m_pTestStandardUniteManagerTpl ;
	CMyDocTemplate * m_pTestStandardThirdManagerTpl ;
	CMyDocTemplate * m_pTestStandardErrorTypeManagerTpl ;

	//CMyDocTemplate * m_pTestingTaskConfigDocTpl ;
	//CMyDocTemplate * m_pTestingTaskConfigDocTpl ;

	CMyDocTemplate * m_pUserManagerTpl ;
	CMyDocTemplate * m_pStructDesignManagerTpl ;

	CMyDocTemplate * m_pCodeViewTpl;
	CMyDocTemplate * m_pMsgShowTpl;

	
	vector<_tagWorkUiContext> m_UiList;
};
