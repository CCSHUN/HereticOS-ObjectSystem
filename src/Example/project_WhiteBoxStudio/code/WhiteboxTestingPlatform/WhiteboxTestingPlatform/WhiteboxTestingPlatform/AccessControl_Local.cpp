#include "StdAfx.h"
#include "AccessControl_Local.h"
#include "WhiteboxTestingPlatform.h"
CAccessControl_Local::CAccessControl_Local(void)
{
}

CAccessControl_Local::~CAccessControl_Local(void)
{
}

BOOL CAccessControl_Local::UpDataAccessControl()
{
	BOOL bRet=theApp.m_WorkSpaceWndManger.m_UserDataModel.GetUser(m_szUserName,m_CurUser);
	if(bRet)
	{
		bRet=theApp.m_WorkSpaceWndManger.m_UserDataModel.GetUserProject(m_szUserName,m_CurUserOwnProjectList);
		map<tstring,tstring,less<tstring> > CurProjectList;
		theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectNameList(CurProjectList);
		map<tstring,_tagUserProjectSet,less<tstring> >::iterator itOwn=m_CurUserOwnProjectList.OwnProjectArray.begin();
		unsigned int nSize=m_CurUserOwnProjectList.OwnProjectArray.size();

		for(;itOwn!=m_CurUserOwnProjectList.OwnProjectArray.end();itOwn++)
		{
			if(CurProjectList.find(itOwn->second.szProjectName)==CurProjectList.end())
			{
				m_CurUserOwnProjectList.OwnProjectArray.erase(itOwn);
				itOwn=m_CurUserOwnProjectList.OwnProjectArray.begin();
				if(m_CurUserOwnProjectList.OwnProjectArray.size()==0)
				{
					break;
				}
			}
		}

		if(nSize!=m_CurUserOwnProjectList.OwnProjectArray.size())
		{
			//用户拥有项目有变更
			theApp.m_WorkSpaceWndManger.m_UserDataModel.UpDataUserProject(m_szUserName,m_CurUserOwnProjectList);
		}
	}
	return bRet;
}

/*"新建"，完成报表后为"测试已提交"，研发处理结束后为"研发已提交" 管理员"归档"*/

BOOL CAccessControl_Local::CanEditProject(_tagProjectState & tProjectState)
{
	if(m_CurUser.szUserType==USER_TYPE_DEVELOP)
	{
		if(tProjectState.szProjectState==PROJECT_STATE_NEW_OVER)
		{

		}else if(tProjectState.szProjectState==PROJECT_STATE_TEST_OVER)
		{
			return TRUE;
		}else if(tProjectState.szProjectState==PROJECT_STATE_DEV_OVER)
		{
	
		}else if(tProjectState.szProjectState==PROJECT_STATE_FILE_OVER)
		{

		}
	}else if(m_CurUser.szUserType==USER_TYPE_TESTER)
	{
		if(tProjectState.szProjectState==PROJECT_STATE_NEW_OVER)
		{
			return TRUE;
		}else if(tProjectState.szProjectState==PROJECT_STATE_TEST_OVER)
		{
			return TRUE;
		}else if(tProjectState.szProjectState==PROJECT_STATE_DEV_OVER)
		{
			//return TRUE;
		}else if(tProjectState.szProjectState==PROJECT_STATE_FILE_OVER)
		{

		}
	}else if(m_CurUser.szUserType==USER_TYPE_ADMIN)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CAccessControl_Local::CanEditTest()
{
	if(m_CurUser.szUserType==USER_TYPE_DEVELOP)
	{
		return FALSE;
	}else if(m_CurUser.szUserType==USER_TYPE_TESTER)
	{
		return TRUE;
	}else if(m_CurUser.szUserType==USER_TYPE_ADMIN)
	{
		return TRUE;
	}
	return FALSE;
}

//允许管理项目，如创建项目，项目归档，项目所在流程等
BOOL CAccessControl_Local::CanMangerProject()
{
	if(m_CurUser.szUserType==USER_TYPE_DEVELOP)
	{
		return FALSE;
	}else if(m_CurUser.szUserType==USER_TYPE_TESTER)
	{
		return FALSE;
	}else if(m_CurUser.szUserType==_T("管理员"))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CAccessControl_Local::CanEditProject(tstring & szProjectName)
{

	map<tstring,_tagUserProjectSet,less<tstring> >::iterator itFind=m_CurUserOwnProjectList.OwnProjectArray.find(szProjectName);
	if(itFind!=m_CurUserOwnProjectList.OwnProjectArray.end())
	{
		return TRUE;
	}
	return FALSE;
}
tstring CAccessControl_Local::GetLoginName() const
{
	return m_szUserName;
}

tstring CAccessControl_Local::GetLoginUserType() const
{
	return m_CurUser.szUserType;
}

tstring	 & CAccessControl_Local::GetCurTime()
{
	SYSTEMTIME tm;
	if(GetCurTime(tm))
	{
		TCHAR szTime[33];
		sprintf_s_t(szTime,32,_T("%d-%d-%d %d:%d:%d"),
			tm.wYear,tm.wMonth,tm.wDay,
			tm.wHour,tm.wMinute,tm.wSecond);
		m_szCurTime=szTime;
		return m_szCurTime;
	}
	m_szCurTime=_T("TimeError");
	return m_szCurTime;
}
BOOL CAccessControl_Local::GetCurTime(SYSTEMTIME & tm)
{
	CTime time(m_ServerTime.wYear,m_ServerTime.wMonth,m_ServerTime.wDay,
		m_ServerTime.wHour,
		m_ServerTime.wMinute,m_ServerTime.wSecond,-1);
	int nspsec=(GetTickCount()-m_BeginTickCount)/1000;

	int nSec=nspsec%60;
	CTimeSpan sp((nspsec/(3600*24)),(nspsec/3600)%24,(nspsec/60)%60,nspsec%60);
	time+=sp;
	tm.wDay=time.GetDay();
	tm.wYear=time.GetYear();
	tm.wMonth=time.GetMonth();
	tm.wHour=time.GetHour();
	tm.wMinute=time.GetMinute();
	tm.wSecond=time.GetSecond();

	return TRUE;
}
BOOL CAccessControl_Local::LonginSystem(tstring & szLonginType,tstring & szUserName,tstring & szPassword)
{
	if(szLonginType==LOGIN_TYPE_LOCAL)
	{
		gpObjectSystem=&gobjsys;
		m_szUserName=szUserName;
		return TRUE;
	}else if(szLonginType==LOGIN_TYPE_NET_SOAPSERVICE)
	{
		gpObjectSystem=&gSoapObjectSystem;
		if(gpObjectSystem->LogonInSystem(szUserName,szPassword))
		{
			m_szUserName=szUserName;
			BOOL bRet= UpDataAccessControl();
			if(bRet)
			{
				SYSTEMTIME npTime;
				bRet=gpObjectSystem->GetCurTime(&npTime,&m_ServerTime);
				m_BeginTickCount=GetTickCount();
			}
			return bRet;
		}
	}
	return FALSE;
}
