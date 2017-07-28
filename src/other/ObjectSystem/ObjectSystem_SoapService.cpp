#include "stdafx.h"
#include "ObjectSystem_SoapService.h"
#include "ObjectSystem.h"


CObjectSystem_SoapService::CObjectSystem_SoapService(void)
{
}

CObjectSystem_SoapService::~CObjectSystem_SoapService(void)
{
}
BOOL CObjectSystem_SoapService::ReleaseObjectState(IN tstring & ObjectOrDir,OUT SYSTEMERROR * pError)
{

	return m_LocalObjectSystem.ReleaseObjectState(ObjectOrDir, pError);
}
#define USER_PATH		_T("UserInfo\\UserMap\\")
BOOL CObjectSystem_SoapService::GetUser(tstring & szUserName,_tagUserMapSet & UserSet)
{
	tstring szPath;
	szPath=USER_PATH+szUserName;
	_tagUserMapSet_Wrap lib1;
	lib1.m_szAddr=szPath;
	if(lib1.GetObject())
	{
		UserSet=lib1.m_Data;
		return TRUE;
	}else
	{
		return FALSE;
	}
}


BOOL CObjectSystem_SoapService::LogonInSystem(IN tstring & szUserName,IN tstring & szPassword)
{
	
	_DebugOutput(_T("CObjectSystem_SoapService"),_T("LogonInSystem %s UserName=%s"),gConfig.m_Config.strLocalSystemDirectory.c_str(),szUserName.c_str());
	_tagUserMapSet Set;
	if(GetUser(szUserName,Set))
	{
		if(Set.szPassword==szPassword)
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CObjectSystem_SoapService::LogonOutSystem()
{
	return TRUE;
}


BOOL CObjectSystem_SoapService::GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
{
	return m_LocalObjectSystem.GetObject(ObjectPath,Object,ObjectState,pError);
}

BOOL CObjectSystem_SoapService::UpDataObject(IN tstring & ObjectPath,IN tstring & Object,IN _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
{
	return m_LocalObjectSystem.UpDataObject(ObjectPath,Object,ObjectState,pError);
}

//更新对象到存储
BOOL CObjectSystem_SoapService::UpDataObject(IN tstring & ObjectPath,IN tstring & Object,SYSTEMERROR * pError)
{
	return m_LocalObjectSystem.UpDataObject(ObjectPath,Object,pError);
}

BOOL CObjectSystem_SoapService::GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfoSoap & DirectoryInfo,OUT SYSTEMERROR * pError)
{
	return m_LocalObjectSystem.GetDirectoryInfo(DirectoryPath,szFinder,DirectoryInfo,pError);
}
//获取目录信息
BOOL CObjectSystem_SoapService::GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError)
{
	return m_LocalObjectSystem.GetDirectoryInfo(DirectoryPath,szFinder,DirectoryInfo,pError);
}

BOOL CObjectSystem_SoapService::GetCurTime(SYSTEMTIME * npTime,SYSTEMTIME * nCurTime)
{
	GetLocalTime(nCurTime);
	return TRUE;
}
//删除对象
BOOL CObjectSystem_SoapService::DeleteObject(IN tstring & ObjectOrDir,SYSTEMERROR * pError)
{
	return m_LocalObjectSystem.DeleteObject(ObjectOrDir,pError);
}


BOOL CObjectSystem_SoapService::UpDataObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
{
	return TRUE;
}


BOOL CObjectSystem_SoapService::GetObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
{
	return m_LocalObjectSystem.GetObjectState( ObjectPath,ObjectState,pError);
}