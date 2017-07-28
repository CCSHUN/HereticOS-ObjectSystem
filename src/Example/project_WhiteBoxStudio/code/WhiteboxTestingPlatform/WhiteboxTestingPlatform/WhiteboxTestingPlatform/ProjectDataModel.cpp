#include "StdAfx.h"
#include "ProjectDataModel.h"
#include "WhiteboxTestingPlatform.h"

#define WORKSHEET_NAME				_T("Worksheet")
#define TESTREPORT_NAME				_T("TestReport")
#define PROJECTSTATE_NAME			_T("ProjectState")
#define CHECKCFG_NAME				_T("CheckCfg")
#define USER_CHECKCFG_NAME			_T("_PrivateCfg")
#define UNITREPORT_NAME				_T("UnitReport")
#define THIRDSTANDARDLIB_NAME		_T("ThirdStandardlib")
#define YDSTANDARDLIB_NAME			_T("MachineCheckStandardLib")

CProjectDataModel::CProjectDataModel(void)
{
}

CProjectDataModel::~CProjectDataModel(void)
{
}

BOOL CProjectDataModel::GetProjectNameList(map<tstring,tstring,less<tstring> >  & ProjectList)
{
	tstring szPath = tstring(_T("WhiteBoxTestProject"));
	CObjectSystemInterface::_tagDirectoryInfo Info;
	CObjectSystemInterface::SYSTEMERROR error;
	tstring szFinder=_T("*");
	if(gpObjectSystem->GetDirectoryInfo(szPath,szFinder, Info, &error) == FALSE){
		return FALSE;
	}

	for(unsigned int i=0; i<Info.DirectoryInfoArray.size(); i++)
	{
		const TCHAR * szProjectName = Info.DirectoryInfoArray[i].ObjectName.c_str() + strlen_t(_T("Project_"));
		ProjectList[tstring(szProjectName)]=tstring(szProjectName);
	}
	return TRUE;
}

BOOL CProjectDataModel::NewSubProject(tstring szDirectoryName)
{
	tstring szPath = szDirectoryName+tstring(_T("\\Worksheet"));
	_S_WORKSHEET_Wrap		WorkSheet;
	WorkSheet.m_szAddr = szPath;
	BOOL bOk = WorkSheet.UpDataObject();
	if(bOk==FALSE) 
		return FALSE;

	szPath = szDirectoryName+tstring(_T("\\CheckCfg"));
	_S_PROJECT_CONFIG_Wrap ProjectConfig;
	ProjectConfig.m_szAddr = szPath;
	bOk = ProjectConfig.UpDataObject();
	if(bOk==FALSE) 
		return FALSE;

	szPath = szDirectoryName+tstring(_T("\\TestReport"));
	_S_REPORT_Wrap Report;
	Report.m_szAddr = szPath;
	bOk = Report.UpDataObject();
	if(bOk==FALSE) 
		return FALSE;

	szPath = szDirectoryName+_T("\\")+tstring(UNITREPORT_NAME);
	_tagUnitReport_Wrap UnitReports;
	UnitReports.m_szAddr = szPath;
	bOk = UnitReports.UpDataObject();
	if(bOk==FALSE) 
		return FALSE;


	szPath = szDirectoryName+tstring(_T("\\ProjectState"));
	_tagProjectState_Wrap state;
	state.m_szAddr = szPath;
	state.m_Data.szProjectState=PROJECT_STATE_NEW_OVER;
	bOk = state.UpDataObject();


	if(bOk==FALSE) 
		return FALSE;

	return TRUE;
}

BOOL CProjectDataModel::NewDirectory(tstring szDirectoryName)
{
	tstring szPath = szDirectoryName+tstring(_T("\\ChildTest_00000"));
	_S_WORKSHEET_Wrap		MachineCheck;

	MachineCheck.m_szAddr = szPath;
	BOOL bOk = MachineCheck.UpDataObject();
	if(bOk==FALSE) 
		return FALSE;

	return TRUE;
}

BOOL CProjectDataModel::NewProject(tstring szProjectName)
{
	tstring szPath = tstring(_T("WhiteBoxTestProject\\Project_"))+szProjectName+tstring(_T("\\ChildTest_00000"));
	_S_WORKSHEET_Wrap		MachineCheck;

	MachineCheck.m_szAddr = szPath;
	BOOL bOk = MachineCheck.UpDataObject();
	if(bOk==FALSE) 
		return FALSE;

	return TRUE;
}

BOOL CProjectDataModel::CreateLeafNode(CViewTree &TreeCtl, PDirectoryData pDirectoryData, const tstring &szPageName, const tstring &szPageID)
{
	TreeIndex *pIndex = new TreeIndex;
	/*for (unsigned int i=0; i<pDirectoryData->pIndex->IndexList.size(); i++){
		pIndex->IndexList.push_back(pDirectoryData->pIndex->IndexList[i]);
	}*/
	pIndex->IndexList=pDirectoryData->pIndex->IndexList;
	pIndex->IndexList.push_back(szPageID);
	tstring szAddr=theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectWholePath(pIndex);
	if(szAddr[szAddr.length()-1]=='\\')
	{
		//szAddr[szAddr.length()-1]=0;
		szAddr.erase(szAddr.length()-1);
	}

	m_TreeIndexMap[szAddr]=pIndex;
	

	pIndex->szPageName = szPageName;
	pIndex->szPageType=ADDR_PROJECT;
	pIndex->pSharedObject = pDirectoryData->pShareData;
	HTREEITEM hItem = TreeCtl.InsertItem(szPageName.c_str(), 2, 2, pDirectoryData->hParentItem);	
	TreeCtl.SetItemData(hItem, (DWORD_PTR)pIndex);

	return TRUE;
}


BOOL CProjectDataModel::GetNodeData(CViewTree & TreeCtl, const tstring &szParentDirectoryName,  PDirectoryData pDirectoryData)
{
	//get parent' path
	tstring sParentDirectoryPath = tstring(_T("WhiteBoxTestProject\\"));
	for (unsigned int i=0; i<pDirectoryData->pIndex->IndexList.size(); i++){
		sParentDirectoryPath += pDirectoryData->pIndex->IndexList[i] + tstring(_T("\\"));
	}

	//get directory' data
	tstring szPath = sParentDirectoryPath;
	CObjectSystemInterface::_tagDirectoryInfo Info;
	CObjectSystemInterface::SYSTEMERROR error;
	tstring szFinder=_T("*");

	if(gpObjectSystem->GetDirectoryInfo(szPath, szFinder, Info, &error) == FALSE){
		return FALSE;
	}

	for(unsigned int j=0; j<Info.DirectoryInfoArray.size(); j++){
		tstring sSubDirectoryName = Info.DirectoryInfoArray[j].ObjectName;
		if (!sSubDirectoryName.compare(_T("ChildTest_00000"))){
			continue;
		}

		if (!sSubDirectoryName.compare(WORKSHEET_NAME)){
			//节点是工作单不再暴露给研发,只给测试管理员用
			if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditTest())
			{
				CreateLeafNode(TreeCtl, pDirectoryData, tstring(TEST_WORKSHEET_EDIT_WORKSPACE), tstring(WORKSHEET_NAME));
			}
			
			continue;
		}else if (!sSubDirectoryName.compare(TESTREPORT_NAME)){
			//节点是报告工作区
			CreateLeafNode(TreeCtl, pDirectoryData, tstring(TEST_REPORT_MAKE_WORKSPACE), tstring(TESTREPORT_NAME));
			continue;
		}else if (!sSubDirectoryName.compare(CHECKCFG_NAME)){
			//节点是项目配置
			CreateLeafNode(TreeCtl, pDirectoryData, tstring(TEST_PROJECTCONFIG_WORKSPACE), tstring(CHECKCFG_NAME));
			continue;
		}else if (!sSubDirectoryName.compare(UNITREPORT_NAME)){
			//节点是项目配置
			CreateLeafNode(TreeCtl, pDirectoryData, tstring(TEST_REPORT_MAKE_WORKSPACE_UNITREPORT), tstring(UNITREPORT_NAME));
			continue;
		}

		//创建目录或子项, 然后遍历该节点
		CProjectSharedData *pShareData = NULL;
		DirectoryData Data;
		tstring sSubDirectoryName2;
		HTREEITEM hItem = NULL;
		if (sSubDirectoryName.find(_T("Directory_")) != -1){
			sSubDirectoryName2 = sSubDirectoryName.c_str() + strlen_t(_T("Directory_"));
			hItem = TreeCtl.InsertItem(sSubDirectoryName2.c_str(), 0, 0, pDirectoryData->hParentItem);	
		}else if (sSubDirectoryName.find(_T("ChildTest_")) != -1){
			sSubDirectoryName2 = sSubDirectoryName.c_str() + strlen_t(_T("ChildTest_"));

			tstring szIndex=GetProjectWholePath(pDirectoryData->pIndex)+sSubDirectoryName;
			if(m_IndexMap.find(tstring(szIndex))!=m_IndexMap.end())
			{
				pShareData=(CProjectSharedData *)m_IndexMap[tstring(szIndex)];
			}else
			{
				pShareData=new CProjectSharedData;
				m_IndexMap[tstring(szIndex)]=(void *)pShareData;
			}
			//pShareData = new CProjectSharedData;
			hItem = TreeCtl.InsertItem(sSubDirectoryName2.c_str(), 1, 1, pDirectoryData->hParentItem);	
		}

		if (hItem == NULL){
			continue;
		}
		
		TreeIndex *pIndex = new TreeIndex;
		/*for (unsigned int i=0; i<pDirectoryData->pIndex->IndexList.size(); i++){
			pIndex->IndexList.push_back(pDirectoryData->pIndex->IndexList[i]);
		}*/
		pIndex->IndexList=pDirectoryData->pIndex->IndexList;

		pIndex->IndexList.push_back(sSubDirectoryName);
		pIndex->szPageName = _T("");
		pIndex->szPageType=ADDR_PROJECT;
		pIndex->pSharedObject = pShareData;
		if (pShareData){
			pShareData->m_pTreeIndex = pIndex;
		}
		TreeCtl.SetItemData(hItem, (DWORD_PTR)pIndex);

		Data.hParentItem = hItem;
		Data.pIndex = pIndex;
		Data.pShareData = pShareData;
		GetNodeData(TreeCtl, sSubDirectoryName2, &Data);
		//TreeCtl.Expand(Data.hParentItem, TVE_EXPAND);
	}

	return TRUE;
}
BOOL CProjectDataModel::GoProjectPage(tstring & szAddr)
{
	TreeIndex * pindex;
	//CProjectSharedData * pShareData;
	if(m_TreeIndexMap.find(tstring(szAddr))!=m_TreeIndexMap.end())
	{
		pindex=(TreeIndex *)m_TreeIndexMap[tstring(szAddr)];
	}else
	{
		AfxMessageBox(_T("地址不可用"));
		return FALSE;
	}
	theApp.m_WorkSpaceWndManger.ShowWorkPage(pindex);
	return TRUE;
	/*if(hSelect)
	{
		pindex=(TreeIndex *)pTreeCtrl->GetItemData(hSelect);
		if(pindex)
		{
			theApp.m_WorkSpaceWndManger.ShowWorkPage(pindex);
			// 设置该项为选中状态 
			pTreeCtrl->SelectItem(hSelect);
		}
	}*/
}
BOOL CProjectDataModel::GetProjectTree(CViewTree & TreeCtl)
{
	TreeCtl.DeleteAllItems();

	HTREEITEM hRoot = TreeCtl.InsertItem(_T("所有项目"), 0, 0);
	TreeCtl.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	TreeCtl.Expand(hRoot, TVE_EXPAND);

	//check root dir
	tstring szPath = tstring(_T("WhiteBoxTestProject"));
	CObjectSystemInterface::_tagDirectoryInfo Info;
	CObjectSystemInterface::SYSTEMERROR error;
	tstring szFinder=_T("*");
	if(gpObjectSystem->GetDirectoryInfo(szPath,szFinder, Info, &error) == FALSE){
		return FALSE;
	}

	TreeIndex * pIndex;
	for(unsigned int i=0; i<Info.DirectoryInfoArray.size(); i++)
	{
		//create project
		const TCHAR * szProjectName = Info.DirectoryInfoArray[i].ObjectName.c_str() + strlen_t(_T("Project_"));
		if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditProject(tstring(szProjectName))==FALSE)
		{
			continue;
		}

		HTREEITEM hProject = TreeCtl.InsertItem(szProjectName, 0, 0, hRoot);

		pIndex = new TreeIndex;
		pIndex->IndexList.push_back(Info.DirectoryInfoArray[i].ObjectName);
		pIndex->szPageName = _T("");
		pIndex->szPageType=ADDR_PROJECT;
		pIndex->pSharedObject = NULL;
		TreeCtl.SetItemData(hProject, (DWORD_PTR)pIndex);

		DirectoryData DirData;
		DirData.hParentItem = hProject;
		DirData.pShareData = NULL;
		DirData.nType = 1;
		DirData.pIndex = pIndex;
		GetNodeData(TreeCtl, szProjectName,  &DirData);
		TreeCtl.Expand(DirData.hParentItem, TVE_EXPAND);
	}

	TreeCtl.Expand(hRoot, TVE_EXPAND);
	return TRUE;
}

BOOL CProjectDataModel::DelProject(tstring szProjectPath)
{
	tstring szPath = tstring(_T("WhiteBoxTestProject\\Project_")) + szProjectPath;
	CObjectSystemInterface::SYSTEMERROR Error;
	return gpObjectSystem->DeleteObject(szPath, &Error);
}

BOOL CProjectDataModel::DelSubProject(tstring szNodePath)
{
	tstring szPath = szNodePath;
	CObjectSystemInterface::SYSTEMERROR Error;
	return gpObjectSystem->DeleteObject(szPath, &Error);
}

BOOL CProjectDataModel::GetUserConfigByName(IN tstring &szProjectPath, OUT _tagProjectConfig &UserProjectConfig)
{
	_tagProjectConfig_Wrap cfg;
	cfg.m_szAddr = szProjectPath;
	cfg.m_szAddr += theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
	cfg.m_szAddr += USER_CHECKCFG_NAME;
	if(cfg.GetObject())
	{
		UserProjectConfig = cfg.m_Data;
		return TRUE;
	}
	return FALSE;
}
BOOL CProjectDataModel::GetUnitReport(IN tstring &szProjectPath, OUT _tagUnitReport_Wrap &UnitReport)
{
	//_tagUnitReport_Wrap UnitReoprt1;
	UnitReport.m_szAddr = szProjectPath+tstring(UNITREPORT_NAME);

	if(UnitReport.GetObject())
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CProjectDataModel::UpDataUnitReport(IN tstring &szProjectPath, OUT _tagUnitReport_Wrap &UnitReport)
{
	//_tagUnitReport_Wrap UnitReoprt1;
	UnitReport.m_szAddr = szProjectPath+tstring(UNITREPORT_NAME);

	if(UnitReport.UpDataObject())
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CProjectDataModel::GetConfigByName(IN tstring &szProjectPath, OUT _tagProjectConfig &ProjectConfig)
{
	_tagProjectConfig_Wrap cfg;
	cfg.m_szAddr = szProjectPath + CHECKCFG_NAME;
	if(cfg.GetObject())
	{
		ProjectConfig = cfg.m_Data;
		return TRUE;
	}
	return FALSE;
}

BOOL CProjectDataModel::UpdateUserConfigByName(IN tstring &szProjectPath, IN _tagProjectConfig &UserProjectConfig)
{
	_tagProjectConfig_Wrap cfg;
	cfg.m_szAddr = szProjectPath;
	cfg.m_szAddr += theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
	cfg.m_szAddr += USER_CHECKCFG_NAME;
	cfg.m_Data = UserProjectConfig;
	return cfg.UpDataObject();
}

BOOL CProjectDataModel::UpdateConfigByName(IN tstring &szProjectPath, IN _tagProjectConfig &ProjectConfig)
{
	_tagProjectConfig_Wrap cfg;
	cfg.m_szAddr = szProjectPath + CHECKCFG_NAME;
	cfg.m_Data = ProjectConfig;
	return cfg.UpDataObject();
}

BOOL CProjectDataModel::GetReportByName(IN tstring &szProjectPath, OUT _S_REPORT_Wrap &Report)
{
	Report.m_szAddr = szProjectPath + TESTREPORT_NAME;
	if(Report.GetObject())
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CProjectDataModel::UpdateReportByName(IN tstring &szProjectPath, IN _S_REPORT_Wrap &Report)
{
	Report.m_szAddr = szProjectPath + TESTREPORT_NAME;
	return Report.UpDataObject();
}

BOOL CProjectDataModel::GetWorkSheetByName(IN tstring &szProjectPath, OUT _S_WORKSHEET &WorkSheet)
{
	_S_WORKSHEET_Wrap worksheet;
	worksheet.m_szAddr = szProjectPath + WORKSHEET_NAME;
	if(worksheet.GetObject())
	{
		WorkSheet = worksheet.m_Data;
		return TRUE;
	}
	return FALSE;
}

BOOL CProjectDataModel::UpdateWorkSheetByName(IN tstring &szProjectPath, IN _S_WORKSHEET &WorkSheet)
{
	_S_WORKSHEET_Wrap worksheet;
	worksheet.m_szAddr = szProjectPath + WORKSHEET_NAME;
	worksheet.m_Data = WorkSheet;
	return worksheet.UpDataObject();
}


tstring CProjectDataModel::GetProjectWholePath(TreeIndex* pPath)
{
	tstring sDirectoryPath = tstring(_T("WhiteBoxTestProject\\"));
	for (unsigned int i=0; i<pPath->IndexList.size(); i++){
		sDirectoryPath += pPath->IndexList[i] + tstring(_T("\\"));
	}
	return sDirectoryPath;
}


BOOL CProjectDataModel::GetProjectStateByName(IN tstring &szProjectPath, OUT _tagProjectState_Wrap &ProjectState)
{
	ProjectState.m_szAddr = szProjectPath + PROJECTSTATE_NAME;
	return ProjectState.GetObject();

}
BOOL CProjectDataModel::UpdataProjectStateByName(IN tstring &szProjectPath, IN _tagProjectState_Wrap &ProjectState)
{

	ProjectState.m_szAddr = szProjectPath + PROJECTSTATE_NAME;
	return ProjectState.UpDataObject();
}

BOOL CProjectSharedData::ReGetObject()
{
	m_bGet=FALSE;
	return GetObject();
}

BOOL CProjectSharedData::GetObject()
{
	GetConfigObject();
	GetWorkSheetObject();
	GetReportObject();
	GetThirdStandardlibObject();
	GetYDStandardLibObject();
	GetStandardErrorTypeNameLib();
	GetStandardErrorWarningNameArray();
	GetProjectState();

	

	return TRUE;
}

BOOL CProjectSharedData::UpdataObject()
{
	return UpdataConfigObject() && UpdataReportObject() /* && UpdataThirdStandardlibObject() && UpdataYDStandardLibObject()*/;
}

BOOL CProjectSharedData::init()
{
	if(m_bGet==FALSE)
	{
		//代码定位结构

		
		//m_CodeViewTreeIndex.pSharedObject = m_pShareData;

		if(GetObject())
		{
			m_bGet=TRUE;
			return TRUE;
		}
	}
	return FALSE;
}

tstring CProjectSharedData::GetProjectName()
{
	return m_pTreeIndex->IndexList[0];
}

tstring CProjectSharedData::GetSubProjectName()
{
	return m_pTreeIndex->IndexList[m_pTreeIndex->IndexList.size()-1];
}



tstring CProjectSharedData::GetProjectWholePath()
{
	
	return CProjectDataModel::GetProjectWholePath(m_pTreeIndex);
}

tstring CProjectSharedData::GetSubProjectCodePath()
{
#define SOURCE_PATH_KEY _T("-setenv(SOURCE_PATH=")

	tstring sUserCfg = m_UserProjectConfig.CheckCfgStandard;
	int nPos = sUserCfg.find(SOURCE_PATH_KEY);
	if (nPos != -1){
		int nPos2 = sUserCfg.find(_T(")"), nPos+1);
		if (nPos2 != -1){
			return sUserCfg.substr(nPos+strlen_t(SOURCE_PATH_KEY), nPos2-nPos-strlen_t(SOURCE_PATH_KEY));
		}
	}
	return _T("");
}

BOOL CProjectSharedData::GetUnitReport()
{
	return theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetUnitReport(GetProjectWholePath(),m_UnitReport);
}

BOOL CProjectSharedData::UpDataUnitReport()
{
	return theApp.m_WorkSpaceWndManger.m_ProjectDataModel.UpDataUnitReport(GetProjectWholePath(),m_UnitReport);
}

BOOL CProjectSharedData::GetProjectState()
{
	tstring sDirectoryPath = GetProjectWholePath();
	return theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectStateByName(sDirectoryPath,m_ProjectState);

}
BOOL CProjectSharedData::UpdataProjectState()
{

	tstring sDirectoryPath = GetProjectWholePath();
	return theApp.m_WorkSpaceWndManger.m_ProjectDataModel.UpdataProjectStateByName(sDirectoryPath,m_ProjectState);
}


BOOL CProjectSharedData::GetConfigObject()
{
	tstring sDirectoryPath = GetProjectWholePath();

	return theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetConfigByName(sDirectoryPath, m_ProjectConfig) &&
		   theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetUserConfigByName(sDirectoryPath, m_UserProjectConfig);
}

BOOL CProjectSharedData::UpdataConfigObject()
{
	tstring sDirectoryPath = GetProjectWholePath();

	return theApp.m_WorkSpaceWndManger.m_ProjectDataModel.UpdateConfigByName(sDirectoryPath, m_ProjectConfig) &&
		   theApp.m_WorkSpaceWndManger.m_ProjectDataModel.UpdateUserConfigByName(sDirectoryPath, m_UserProjectConfig);
}

BOOL CProjectSharedData::GetWorkSheetObject()
{
	tstring sDirectoryPath = GetProjectWholePath();

	return theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetWorkSheetByName(sDirectoryPath, m_WorkSheet);
}

BOOL CProjectSharedData::UpdataWorkSheetObject()
{
	tstring sDirectoryPath = GetProjectWholePath();

	return theApp.m_WorkSpaceWndManger.m_ProjectDataModel.UpdateWorkSheetByName(sDirectoryPath, m_WorkSheet);
}

BOOL CProjectSharedData::GetReportObject()
{
	tstring sDirectoryPath = GetProjectWholePath();
	return theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetReportByName(sDirectoryPath, m_Report);
}

BOOL CProjectSharedData::UpdataReportObject()
{
	tstring sDirectoryPath = GetProjectWholePath();

	return theApp.m_WorkSpaceWndManger.m_ProjectDataModel.UpdateReportByName(sDirectoryPath, m_Report);
}

BOOL CProjectSharedData::GetThirdStandardlibObject()
{
	return theApp.m_WorkSpaceWndManger.m_StandardDataModel.GetThirdStandardByName(m_ProjectConfig.TestReportStandard, m_ThirdStandardlib);
}

BOOL CProjectSharedData::UpdataThirdStandardlibObject()
{
	return theApp.m_WorkSpaceWndManger.m_StandardDataModel.UpDataThirdStandardByName(m_ProjectConfig.TestReportStandard, m_ThirdStandardlib);
}

BOOL CProjectSharedData::GetYDStandardLibObject()
{
	return theApp.m_WorkSpaceWndManger.m_StandardDataModel.GetUniteStandardByName(m_ProjectConfig.TestReportStandard, m_YDStandardLib);
}

BOOL CProjectSharedData::UpdataYDStandardLibObject()
{
	return theApp.m_WorkSpaceWndManger.m_StandardDataModel.UpDataUniteStandardByName(m_ProjectConfig.TestReportStandard, m_YDStandardLib);
}

BOOL CProjectSharedData::GetStandardErrorTypeNameLib()
{
	return theApp.m_WorkSpaceWndManger.m_StandardDataModel.GetStandardErrorTypeNameLib(m_ProjectConfig.TestReportStandard, m_MachineCheckStandardTypeLib);
}

BOOL CProjectSharedData::UpdataStandardErrorTypeNameLib()
{
	return theApp.m_WorkSpaceWndManger.m_StandardDataModel.UpdataStandardErrorTypeNameLib(m_ProjectConfig.TestReportStandard, m_MachineCheckStandardTypeLib);
}

BOOL CProjectSharedData::GetStandardErrorWarningNameArray()
{
	return theApp.m_WorkSpaceWndManger.m_StandardDataModel.GetStandardErrorWarningNameArray(m_ProjectConfig.TestReportStandard, m_ErrorWarningArray);
}

BOOL CProjectSharedData::UpdataStandardErrorWarningNameArray()
{
	return theApp.m_WorkSpaceWndManger.m_StandardDataModel.UpdataStandardErrorWarningNameArray(m_ProjectConfig.TestReportStandard, m_ErrorWarningArray);
}
