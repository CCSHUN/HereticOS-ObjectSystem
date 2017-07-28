#pragma once

#include "ViewTree.h"
#include "UiStructDef.h"

class CProjectSharedData;
typedef struct _tagDirectoryData{
	HTREEITEM hParentItem;
	CProjectSharedData *pShareData;
	int nType;										//���ڵ������ 1 ��ĿĿ¼ 2 �߼�Ŀ¼ 3 ����ĿĿ¼
	TreeIndex *pIndex;							//���ڵ��Index����
}DirectoryData, *PDirectoryData;


#define PROJECT_STATE_NEW_OVER		_T("�½�")
#define PROJECT_STATE_TEST_OVER		_T("�������ύ")
#define PROJECT_STATE_DEV_OVER		_T("�з����ύ")
#define PROJECT_STATE_FILE_OVER		_T("�ѹ鵵")

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
	//��ȡ��ĿĿ¼
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

	//�Ƿ���Ҫ���»�ȡ��������
	BOOL m_bNeedGetReport;

	//�����ʱ����
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
	//��Ŀ�ڷ������ϵľ��Դ洢·��
	tstring GetProjectWholePath();	
	
	//��������Ŀ�Ĵ���·����Ҳ�������û�˽�������е�SOURCE_PATH�ֶ�
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