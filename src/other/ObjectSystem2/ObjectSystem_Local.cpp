///////////////////////////////////////////////////////////////////////////////////
//	Copyright 2017 shushen,ye
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//	http://www.apache.org/licenses/LICENSE-2.0
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ObjectSystem_Local.h"



template<typename ConfigT, typename FileSystemT, typename ContainerT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT>::LogonOutSystem()
{
	return TRUE;
}

template<typename ConfigT, typename FileSystemT, typename ContainerT, typename AuthT>
void CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT>::GetEventQueue(IN  const TCHAR * szUser, IN  const TCHAR * szSession, _tagCallParameter & RetPar)
{
	UserContextMapT::iterator itUser = m_UserContextMap.find(szUser);

	if (itUser != m_UserContextMap.end())
	{
		UserContext::SessionT::iterator itSession = itUser->second.SessionMap.find(szSession);
		if (itSession != itUser->second.SessionMap.end())
		{
			//RetPar.el=itSession->second.EventQueue ;
			RetPar.el.resize(itSession->second.EventQueue.size());
			std::copy(itSession->second.EventQueue.begin(),
				itSession->second.EventQueue.end(),
				//itSession->second.EventQueue.begin()
				RetPar.el.begin()
			);
			//没有确认，后续再做吧
			itSession->second.EventQueue.clear();
		}
	}
	return ;
}

template<typename ConfigT, typename FileSystemT, typename ContainerT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT>::KeepAlived(IN const  TCHAR * szUser, IN  const TCHAR * szSession,IN OUT tstring & szKeepAlivedPar, OUT ObjectSystem::SYSTEMERROR * pError)
{
	UserContextMapT::iterator itUser = m_UserContextMap.find(szUser);

	if (itUser != m_UserContextMap.end())
	{
		UserContext::SessionT::iterator itSession = itUser->second.SessionMap.find(szSession);
		if (itSession != itUser->second.SessionMap.end())
		{
			szKeepAlivedPar = itSession->second.szKeepAlived;
			return TRUE;
		}
	}
	return FALSE;
}

template<typename ConfigT, typename FileSystemT, typename ContainerT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT>::GetCurTime(SYSTEMTIME * npTime, SYSTEMTIME * nCurTime)
{
	GetLocalTime(nCurTime);
	return TRUE;
}


template<typename ConfigT, typename FileSystemT, typename ContainerT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT>::NeedNewObject(IN  const TCHAR * ObjectPath, OUT ObjectSystem::SYSTEMERROR * pError)
{
	return TRUE;
}

template<typename ConfigT, typename FileSystemT, typename ContainerT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT>::RegistObjectEvent(IN  const TCHAR * szUser, IN  const TCHAR * szSession, IN ObjectSystemEvent & RegEvent, OUT ObjectSystem::SYSTEMERROR * pError)
{
	UserContextMapT::iterator itUser = m_UserContextMap.find(szUser);

	if (itUser != m_UserContextMap.end())
	{
		itUser->second.nEventTypeMask |= RegEvent.nEventType;
		UserContext::SessionT::iterator itSession = itUser->second.SessionMap.find(szSession);
		if(itSession != itUser->second.SessionMap.end())
		{
			itSession->second.nEventTypeMask |= RegEvent.nEventType;
			itSession->second.EventSubscribeMap[RegEvent.szObjectAddress] = RegEvent;
			return TRUE;
		}
	}
	*pError = Error_Logon_UserError;
	return FALSE;
}


template<typename ConfigT, typename FileSystemT, typename ContainerT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT>::GetObjectState(IN  const TCHAR * ObjectPath,OUT ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError)
{
	map<tstring, FileContext,less<tstring> >::iterator itObject;

	itObject=m_FileCacheMap.find(ObjectPath);
	if(itObject!=m_FileCacheMap.end())
	{
		ObjectState=itObject->second.ObjectState;
	}
	return FALSE;
}

template<typename ConfigT, typename FileSystemT, typename ContainerT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT>::UpDataObject(IN  const TCHAR * ObjectPath,IN  const TCHAR * Object,IN ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError)
{
	map<tstring, FileContext,less<tstring> >::iterator itObject;
	
	itObject=m_FileCacheMap.find(ObjectPath);
	//tstring ObjectAddr= ConfigT::GetInstance().strLocalSystemDirectory+ObjectPath;
	*pError= ObjectSystem::Error_No;
	if(itObject!=m_FileCacheMap.end())
	{
		//检查锁
		if(itObject->second.ObjectState.bLock&&itObject->second.ObjectState.szLockUser.length())
		{
			if(itObject->second.ObjectState.szLockUser!=ObjectState.szLockUser)
			{
				_DebugOutput(_T("UpDataObject"),_T("请求 Object=%s 请求用户=%s 对象已经锁定 当前锁定用户=%s"),
					ObjectPath.c_str(),ObjectState.szLockUser.c_str(),
					itObject->second.ObjectState.szLockUser.c_str());
				*pError=ObjectSystem::Error_ObjectAlreadyLock;
				return FALSE;
			}
		}
		itObject->second.szData=Object;
		
		itObject->second.FileOperation.ClearFile(ObjectPath);
		if(itObject->second.FileOperation.WriteObject(Object))
		{

			//释放对象锁
			itObject->second.ObjectState.szLockUser.clear();
			itObject->second.ObjectState.bLock=FALSE;
			_DebugOutput(_T("UpDataObject"),_T("释放对象锁 Object=%s 请求用户=%s "),
				ObjectPath.c_str(),ObjectState.szLockUser.c_str());
			return TRUE;
		}
	}
	else
	{
		FileContext Context;
		if(Context.FileOperation.OpenObjectFile(ObjectPath,TRUE))
		{
			
			if(Context.FileOperation.WriteObject(Object))
			{
				//保存到cache
				Context.szData=Object;
				Context.ObjectState.bLock=FALSE;
				Context.ObjectState.nLockTime=0;
				Context.ObjectState.szLockUser=_T("");
				Context.ObjectState.nType=ObjectSystem::Nonmoral;
				m_FileCacheMap[ObjectPath]=Context;
				return TRUE;
			}
			Context.FileOperation.CloseObject();
		}
		*pError=ObjectSystem::Error_Sys_OpenFileFail;
		return FALSE;
	}
	

	return FALSE;
}

//更新对象到存储


template<typename ConfigT, typename FileSystemT, typename ContainerT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT>::GetDirectoryInfo(IN const  TCHAR * DirectoryPath,IN  const TCHAR * szFinder,OUT ObjectSystem::_tagDirectoryInfo & DirectoryInfo,OUT ObjectSystem::SYSTEMERROR * pError)
{
	tstring_tmp ObjectAddr= (ConfigT::GetInstance().strLocalSystemDirectory+DirectoryPath).c_str();
	tstring_tmp strFinder = szFinder;
	if (ObjectAddr.at(ObjectAddr.length()-1) != '\\')
	{
		ObjectAddr += '\\';
	}
	FileSystemT::GetDirectoryInfo(ObjectAddr, strFinder,  DirectoryInfo, pError);

	return TRUE;
}

template<typename ConfigT, typename FileSystemT, typename ContainerT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT>::ReleaseObjectLock(const TCHAR * ObjectPath)
{
	return TRUE;
}

template<typename ConfigT, typename FileSystemT, typename ContainerT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT>::ReleaseObjectState(IN  const TCHAR * ObjectOrDir,OUT ObjectSystem::SYSTEMERROR * pError)
{
	map<tstring, FileContext,less<tstring> >::iterator itObject=m_FileCacheMap.begin();
	map<tstring, FileContext,less<tstring> >::iterator itOldObject=itObject;
	for(;itObject!=m_FileCacheMap.end();itObject++)
	{
		if(strstr_t(itObject->first.c_str(),ObjectOrDir))
		{
			//清理该cache

			itObject->second.ObjectState.bLock=FALSE;
			itObject->second.ObjectState.nType=ObjectSystem::Nonmoral;
			itObject->second.ObjectState.nLockTime=0;
			itObject->second.ObjectState.szLockUser.clear();
		}
	}
	return TRUE;
}

template<typename ConfigT, typename FileSystemT, typename ContainerT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT>::ClearDirCache(const TCHAR * ObjectOrDirPath)
{
	map<tstring, FileContext,less<tstring> >::iterator itObject=m_FileCacheMap.begin();
	map<tstring, FileContext,less<tstring> >::iterator itOldObject=itObject;
	for(;itObject!=m_FileCacheMap.end();itObject++)
	{
		if(strstr_t(itObject->first.c_str(),ObjectOrDirPath))
		{
			//清理该cache

			itObject=m_FileCacheMap.erase(itObject);
		}
	}
	return TRUE;
}
//删除对象
template<typename ConfigT, typename FileSystemT, typename ContainerT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT>::DeleteObject(IN  const TCHAR * ObjectOrDir, ObjectSystem::SYSTEMERROR * pError)
{
	
	ClearDirCache(ObjectOrDir);

	tstring ObjectAddr= ConfigT::GetInstance().strLocalSystemDirectory+ObjectOrDir;
	CObjectFileOperation del;
	del.DelObjectOrDir(ObjectAddr);

	return TRUE;
}