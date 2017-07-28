#pragma once


//工具宏
#define HasLock(obj)  (obj.m_ObjectState.szLockUser==theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName())
#define IsCurUserLock(obj)	((obj.m_ObjectState.bLock)&&(obj.m_ObjectState.szLockUser==theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()))
#define IsCurUserAndUiLock(obj,uiName)	 ((obj.m_ObjectState.bLock)&&(obj.m_ObjectState.szLockUser==theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()+uiName))

#define LOGIN_TYPE_LOCAL				_T("本地对象存储系统")
#define LOGIN_TYPE_NET_SOAPSERVICE		_T("网络对象存储系统 Soap Web Services 方式")

class CAccessControl_Local
{
public:
	CAccessControl_Local(void);
	~CAccessControl_Local(void);
	BOOL LonginSystem(tstring & szLonginType,tstring & szUserName,tstring & szPassword);
	BOOL UpDataAccessControl();

	tstring GetLoginName() const;
	tstring GetLoginUserType() const;

	//允许编辑测试信息
	BOOL CanEditTest();
	//允许编辑研发报告
	//BOOL CanEditDevReport();
	//允许管理项目，如创建项目，项目归档，项目所在流程等
	BOOL CanMangerProject();

	BOOL CanEditProject(tstring & szProjectName);

	BOOL CanEditProject(_tagProjectState & tProjectState);

	BOOL GetCurTime(SYSTEMTIME & tm);
	tstring &	 GetCurTime();
private:
	tstring					m_szUserName;
	_tagUserMapSet			m_CurUser;
	_tagUserOwnProjectTab	m_CurUserOwnProjectList;
	SYSTEMTIME				m_ServerTime;
	__int64					m_BeginTickCount;
	tstring m_szCurTime;

};
