#include "stdafx.h"
#include "ObjectSystem_SoapService.h"
#include "ObjectSystem.h"

template<typename ContigT, typename FileSystemT>
CObjectSystem_SoapService<ContigT, FileSystemT>::CObjectSystem_SoapService(void)
{
}
template<typename ContigT, typename FileSystemT>
CObjectSystem_SoapService<ContigT, FileSystemT>::~CObjectSystem_SoapService(void)
{
}

template<typename ContigT, typename FileSystemT>
BOOL CObjectSystem_SoapService<ContigT, FileSystemT>::ReleaseObjectState(IN tstring & ObjectOrDir,OUT SYSTEMERROR * pError)
{

	return m_LocalObjectSystem.ReleaseObjectState(ObjectOrDir, pError);
}
#define USER_PATH		_T("UserInfo\\UserMap\\")

template<typename ContigT, typename FileSystemT>
BOOL CObjectSystem_SoapService<ContigT, FileSystemT>::GetUser(tstring & szUserName,_tagUserMapSet & UserSet)
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

template<typename ContigT, typename FileSystemT>
BOOL CObjectSystem_SoapService<ContigT, FileSystemT>::LogonInSystem(IN tstring & szUserName,IN tstring & szPassword)
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
template<typename ContigT, typename FileSystemT>
BOOL CObjectSystem_SoapService<ContigT, FileSystemT>::LogonOutSystem()
{
	return TRUE;
}

template<typename ContigT, typename FileSystemT>
BOOL CObjectSystem_SoapService<ContigT, FileSystemT>::GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
{
	return m_LocalObjectSystem.GetObject(ObjectPath,Object,ObjectState,pError);
}

template<typename ContigT, typename FileSystemT>
BOOL CObjectSystem_SoapService<ContigT, FileSystemT>::UpDataObject(IN tstring & ObjectPath,IN tstring & Object,IN _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
{
	return m_LocalObjectSystem.UpDataObject(ObjectPath,Object,ObjectState,pError);
}

//更新对象到存储
template<typename ContigT, typename FileSystemT>
BOOL CObjectSystem_SoapService<ContigT, FileSystemT>::UpDataObject(IN tstring & ObjectPath,IN tstring & Object,SYSTEMERROR * pError)
{
	return m_LocalObjectSystem.UpDataObject(ObjectPath,Object,pError);
}


//获取目录信息
template<typename ContigT, typename FileSystemT>
BOOL CObjectSystem_SoapService<ContigT, FileSystemT>::GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError)
{
	return m_LocalObjectSystem.GetDirectoryInfo(DirectoryPath,szFinder,DirectoryInfo,pError);
}

template<typename ContigT, typename FileSystemT>
BOOL CObjectSystem_SoapService<ContigT, FileSystemT>::GetCurTime(SYSTEMTIME * npTime,SYSTEMTIME * nCurTime)
{
	GetLocalTime(nCurTime);
	return TRUE;
}
//删除对象
template<typename ContigT, typename FileSystemT>
BOOL CObjectSystem_SoapService<ContigT, FileSystemT>::DeleteObject(IN tstring & ObjectOrDir,SYSTEMERROR * pError)
{
	return m_LocalObjectSystem.DeleteObject(ObjectOrDir,pError);
}

template<typename ContigT, typename FileSystemT>
BOOL CObjectSystem_SoapService<ContigT, FileSystemT>::UpDataObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
{
	return TRUE;
}

template<typename ContigT, typename FileSystemT>
BOOL CObjectSystem_SoapService<ContigT, FileSystemT>::GetObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
{
	return m_LocalObjectSystem.GetObjectState( ObjectPath,ObjectState,pError);
}