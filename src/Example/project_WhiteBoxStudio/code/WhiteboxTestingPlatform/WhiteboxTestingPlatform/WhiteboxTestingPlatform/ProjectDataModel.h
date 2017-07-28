#pragma once

#include "ViewTree.h"
#include "UiStructDef.h"

class CProjectSharedData;
typedef struct _tagDirectoryData{
	HTREEITEM hParentItem;
	CProjectSharedData *pShareData;
	int nType;										//父节点的类型 1 项目目录 2 逻辑目录 3 子项目目录
	TreeIndex *pIndex;							//父节点的Index数据
}DirectoryData, *PDirectoryData;


#define PROJECT_STATE_NEW_OVER		_T("新建")
#define PROJECT_STATE_TEST_OVER		_T("测试已提交")
#define PROJECT_STATE_DEV_OVER		_T("研发已提交")
#define PROJECT_STATE_FILE_OVER		_T("已归档")

class CProjectDataModel
{
public:
	CProjectDataModel(void);
	~CProjectDataModel(void);
	BOOL GoProjectPage(tstring & szAddr);

	BOOL CreateLeafNode(CViewTree &TreeCtl, PDirectoryData pDirectoryData, const tstring &szPageName, const tstring &szPageID);
	BOOL GetNodeData(CViewTree & TreeCtl, const tstring &szParentDirectoryName,  PDirectoryData pDirectoryData);
	BOOL GetProjectTree(CViewTree & TreeCtl);
	BOOL GetProjectNameList(map<tstring,tstring,less<tstring> >  & ProjectList);

	BOOL NewProject(tstring szProjectName);
	BOOL NewDirectory(tstring szDirectoryName);
	BOOL NewSubProject(tstring szDirectoryName);
	BOOL DelProject(tstring szProjectName);
	BOOL DelSubProject(tstring szNodePath);

	BOOL GetConfigByName(IN tstring &szProjectName, OUT _tagProjectConfig &ProjectConfig);
	BOOL UpdateConfigByName(IN tstring &szProjectName, IN _tagProjectConfig &ProjectConfig);

	BOOL GetUserConfigByName(IN tstring &szProjectName, OUT _tagProjectConfig &UserProjectConfig);
	BOOL UpdateUserConfigByName(IN tstring &szProjectName, IN _tagProjectConfig &UserProjectConfig);

	BOOL GetReportByName(IN tstring &szProjectName, OUT _S_REPORT_Wrap &Report);
	BOOL UpdateReportByName(IN tstring &szProjectName, IN _S_REPORT_Wrap &Report);

	BOOL GetWorkSheetByName(IN tstring &szProjectName, OUT _S_WORKSHEET &WorkSheet);
	BOOL UpdateWorkSheetByName(IN tstring &szProjectName, IN _S_WORKSHEET &WorkSheet);

	//BOOL GetProjectStateByName(IN tstring & sz);
	BOOL GetProjectStateByName(IN tstring &szProjectName, OUT _tagProjectState_Wrap &ProjectState);
	BOOL UpdataProjectStateByName(IN tstring &szProjectName, IN _tagProjectState_Wrap &ProjectState);
	//获取项目目录
	static tstring GetProjectWholePath(TreeIndex* pPath);

	BOOL GetUnitReport(IN tstring &szProjectPath, OUT _tagUnitReport_Wrap &UnitReport);

	BOOL UpDataUnitReport(IN tstring &szProjectPath, OUT _tagUnitReport_Wrap &UnitReport);
protected:
	map<tstring,void * ,less<tstring> > m_IndexMap;
	map<tstring,void * ,less<tstring> > m_TreeIndexMap;

};

class CProjectSharedData :public CUiSharedData
{
public:
	_tagProjectConfig m_ProjectConfig;
	_tagProjectConfig m_UserProjectConfig;
	_S_REPORT_Wrap m_Report;
	_tagProjectState_Wrap m_ProjectState;
	_tagThirdStandardlib m_ThirdStandardlib;
	_tagMachineCheckStandardLib m_YDStandardLib;
	_S_WORKSHEET m_WorkSheet;

	TreeIndex *m_pTreeIndex;
	BOOL m_bIsHopeUpdataReportUi;

	_tagErrorWarningArray m_ErrorWarningArray;
	_tagMachineCheckStandardTypeLib m_MachineCheckStandardTypeLib;

	_tagUnitReport_Wrap m_UnitReport;

	//tstring m_szProjectName;
	//tstring m_szSubProjectName;

	BOOL m_bManualReportSaved;

	BOOL m_bComplateReportUpdated;
	BOOL m_bManualReportUpdated;
	BOOL m_bNofindReportUpdated;

	//是否需要重新获取报表数据
	BOOL m_bNeedGetReport;

	//存放临时索引
	unsigned int m_nReportIndex;
	CViewInterfaceForWorkPageManager * m_pCodeViewCtl;

	CProjectSharedData(){m_bGet=FALSE; m_bManualReportSaved=m_bComplateReportUpdated=m_bManualReportUpdated=m_bNofindReportUpdated=FALSE;};
	~CProjectSharedData(){};
	BOOL ReGetObject();
	BOOL GetObject();
	BOOL UpdataObject();

	//TreeIndex  m_CodeViewTreeIndex;
	BOOL init();

	tstring GetProjectName();
	tstring GetSubProjectName();
	//项目在服务器上的绝对存储路径
	tstring GetProjectWholePath();	
	
	//测试子项目的代码路径，也就是在用户私有配置中的SOURCE_PATH字段
	tstring GetSubProjectCodePath();

	BOOL GetConfigObject();
	BOOL UpdataConfigObject();
	BOOL GetReportObject();
	BOOL UpdataReportObject();
	BOOL GetWorkSheetObject();
	BOOL UpdataWorkSheetObject();

	BOOL GetThirdStandardlibObject();
	BOOL UpdataThirdStandardlibObject();
	BOOL GetYDStandardLibObject();
	BOOL UpdataYDStandardLibObject();

	BOOL GetStandardErrorTypeNameLib();
	BOOL UpdataStandardErrorTypeNameLib();
	BOOL GetStandardErrorWarningNameArray();
	BOOL UpdataStandardErrorWarningNameArray();

	BOOL GetProjectState();
	BOOL UpdataProjectState();

	//
	BOOL GetUnitReport();
	BOOL UpDataUnitReport();

protected:
	BOOL m_bGet;
	
private:
};