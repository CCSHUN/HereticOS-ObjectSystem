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

#pragma once

#include "ObjectSystem.h"
#include "ObjectFileOperation.h"
#define _DebugOutput
#define MAX_EVENT_COUNT_PRESESSION 32
#define MAX_SESSION_COUNT	10000
#define MAX_IOPS	10000
class DefAuth
{
public:
	DefAuth(void) {};
	~DefAuth(void) {};
	static DefAuth & GetInstance()
	{
		static DefAuth _self;
		return _self;
	};
	BOOL GetUser(const TCHAR * szUserName, const TCHAR * szPassword, _tagUserMapSet &Set)
	{
		Set.szUserName = szUserName;
		Set.szPassword = szPassword;
		Set.szUserType = _T("管理员");
		
		return TRUE;
	};
};
/*
template<typename _Ty>
vector<_Ty> & operator =(vector<_Ty> &dst, vector_freelist<_Ty> & src)
{
	dst.resize(src.size());
	memcpy(&dst[0], &src[0], src.size());
	return dst;
}
*/
template<typename ConfigT,typename FileSystemT, typename ContainerT, typename AuthT = DefAuth>
class CObjectSystem_Local: 
	public CObjectSystemInterface,
	public CSystemContainerObjectBase<CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT>, ContainerT>
{
public:
	typedef CObjectSystem_Local<ConfigT, FileSystemT, ContainerT, AuthT> _Myt;

	unsigned int m_nCurSessionNum;
	CObjectSystem_Local(void) {
		m_nCurSessionNum = 0;
	};
	~CObjectSystem_Local(void) {};
	//tstring m_szRootPath;
	/*
	static _Myt & GetInstance() {
		
		static _Myt _self;
		return _self;
	}
	*/
	Transport::TransportHandle ReBuildSession(IN Transport::TransportHandle hHandle, IN const TCHAR * szUserName, IN const TCHAR * szSession)
	{
		UserContextMapT::iterator itUser = m_UserContextMap.find(szUserName);
		Transport::TransportHandle OldHandle = NULL;
		if (itUser != m_UserContextMap.end())
		{
			UserContext::SessionT::iterator itSession = itUser->second.SessionMap.find(szSession);
			if (itSession != itUser->second.SessionMap.end())
			{
				OldHandle = itSession->second.hHandle;
				itSession->second.hHandle = hHandle;
				return OldHandle;
			}
		}
		return OldHandle;
	}
	template<typename StringT>
	BOOL LogonInSystem(IN  const TCHAR * szUserName, IN  const TCHAR * szPassword, OUT StringT & szSession)
	{

		_DebugOutput(_T("CObjectSystem_Local"), _T("LogonInSystem %s UserName=%s"), _T(""), szUserName);
		_tagUserMapSet Set;
		if (AuthT::GetInstance().GetUser(szUserName, szPassword, Set))
		{

			//map<tstring, int, less<tstring>>::iterator
			UserContextMapT::iterator itUser = m_UserContextMap.find(szUserName);

			if (itUser == m_UserContextMap.end())
			{
				UserContext uc;
				uc.nCurrentID = 0;
				uc.nEventTypeMask = 0;
				m_UserContextMap[szUserName] = uc;
				itUser = m_UserContextMap.find(szUserName);

			}

			_tagUserSession tmp;
			tmp.nEventTypeMask = 0;
			tmp.KeepAlived.nCyc = (1000 * MAX_SESSION_COUNT) / MAX_IOPS;
			++itUser->second.nCurrentID;
			unsigned int nNewSession = 0;
			if (m_FreeSessionQueue.size())
			{
				nNewSession = m_FreeSessionQueue.front();
				m_FreeSessionQueue.pop();
			}
			else
			{
				nNewSession = ++m_nCurSessionNum;
			}

			szSession = (const TCHAR *)CAutoVal(nNewSession);
			tmp.KeepAlived.nWndPos = nNewSession;
			tmp.KeepAlived.nWndLen = (1000) / MAX_IOPS;
			tmp.hHandle = NULL;
			itUser->second.SessionMap[szSession.c_str()] = tmp;

			return TRUE;
		}
		return FALSE;
	}

	BOOL LogonOutSystem();

	template<typename StringT, typename String1T>
	BOOL GetObject(IN  StringT& ObjectPath,OUT  String1T & Object,IN OUT ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError)
	{
		map<tstring, FileContext, less<tstring> >::iterator itObject;
		//if(strstr_t(ObjectPath.c_str(),_T("MachineCheckStandardLib")))
		{
			/*printf("MachineCheckStandardLib");
			for(unsigned int i=0;i<768;i++)
			{
			Object+=_T("1234");
			}
			OutputDebugString(_T("768"));
			return TRUE;*/
		}

		*pError = ObjectSystem::Error_No;
		itObject = m_FileCacheMap.find(ObjectPath.c_str());
		if (itObject != m_FileCacheMap.end())
		{
			Object = itObject->second.szData;
			if (itObject->second.ObjectState.szLockUser.length()
				&& itObject->second.ObjectState.bLock)
			{
				if (itObject->second.ObjectState.szLockUser ==
					ObjectState.szLockUser)
				{
					itObject->second.ObjectState = ObjectState;
					_DebugOutput(_T("GetObject"), _T("对象[%s]锁已更新 Object=%s 请求用户=%s 是否占用=%d"),
						itObject->second.ObjectState.szLockUser.c_str(),
						ObjectPath.c_str(), ObjectState.szLockUser.c_str(), ObjectState.bLock);
				}
				else
				{
					//对象已锁定 返回对象当前的锁
					ObjectState = itObject->second.ObjectState;
					_DebugOutput(_T("GetObject"), _T("对象[%s]已锁定，只读打开 Object=%s 请求用户=%s 是否占用=%d"),
						itObject->second.ObjectState.szLockUser.c_str(),
						ObjectPath.c_str(), ObjectState.szLockUser.c_str(), ObjectState.bLock);
					*pError = ObjectSystem::Error_ObjectAlreadyLock;
				}

			}
			else
			{

				//占用对象锁
				itObject->second.ObjectState = ObjectState;
				_DebugOutput(_T("GetObject"), _T("覆盖获取锁 Object=%s 请求用户=%s 是否占用=%d"),
					ObjectPath.c_str(), ObjectState.szLockUser.c_str(), ObjectState.bLock);
			}

		}
		else
		{
			FileContext Context;
			tstring_tmp ObjectAddr = ConfigT::GetInstance().strLocalSystemDirectory.c_str();
			ObjectAddr +=ObjectPath.c_str();
			if (Context.FileOperation.OpenObjectFile_OnlyOpen(ObjectAddr))
			{
				if (Context.FileOperation.ReadObject(Object))
				{
					Context.szData = Object;
					/*pContext->ObjectState.bLock=FALSE;
					pContext->ObjectState.nLockTime=0;
					pContext->ObjectState.szLockUser=_T("");
					pContext->ObjectState.nType=CObjectSystemInterface::Nonmoral;*/
					Context.ObjectState = ObjectState;

					m_FileCacheMap[ObjectPath.c_str()] = Context;
					if (Object.length() == 0)
					{
						*pError = ObjectSystem::Error_Sys_OpenFileFail;
						return FALSE;
					}


					//if(ObjectState.bLock)

					Context.ObjectState = ObjectState;
					_DebugOutput(_T("GetObject"), _T("覆盖锁 Object=%s 请求用户=%s 是否占用=%d"),
						ObjectPath.c_str(), ObjectState.szLockUser.c_str(), ObjectState.bLock);


					return TRUE;
				}
				Context.FileOperation.CloseObject();
			}

			*pError = ObjectSystem::Error_Sys_OpenFileFail;

			return FALSE;
		}

		return TRUE;
	};
	
	BOOL NeedNewObject(IN  const TCHAR * ObjectPath, OUT ObjectSystem::SYSTEMERROR * pError);

	template<typename StringT>
	BOOL BroadcastObjectEvent(IN  StringT & szUser, IN  StringT & szSession, IN ObjectSystem::ObjectSystemEvent & Event, OUT ObjectSystem::SYSTEMERROR * pError)
	{
		UserContextMapT::iterator itUser = m_UserContextMap.begin();
		for (; itUser != m_UserContextMap.end(); itUser++)
		{
			if (itUser->second.nEventTypeMask&Event.nEventType)
			{
				UserContext::SessionT::iterator itSession = itUser->second.SessionMap.begin();
				for (; itSession != itUser->second.SessionMap.end(); itSession++)
				{
					if (itSession->second.EventQueue.size() > MAX_EVENT_COUNT_PRESESSION)
					{
						//*pError = Error_Sys_Event_Too_Much;
						//return FALSE;
						continue;
					}
					else
					{
						if (itSession->second.nEventTypeMask&Event.nEventType)
						{
							_tagUserSession::EventSubscribeT::iterator itSubscribe = itSession->second.EventSubscribeMap.find(Event.szObjectAddress);
							if (itSubscribe != itSession->second.EventSubscribeMap.end())
							{

								itSession->second.EventQueue.push_back(Event);

							}
						}
					}

				}
			}
		}
		return TRUE;
	};

	BOOL RegistObjectEvent(IN  const TCHAR * szUser, IN  const TCHAR * szSession, IN ObjectSystemEvent & RegEvent, OUT ObjectSystem::SYSTEMERROR * pError);
	//更新对象到存储
	template<typename StringT, typename String1T >
	BOOL UpDataObject(StringT & ObjectPath,IN  String1T & Object, ObjectSystem::SYSTEMERROR * pError)
	{
		map<tstring, FileContext, less<tstring> >::iterator itObject;

		itObject = m_FileCacheMap.find(ObjectPath);
		if (itObject != m_FileCacheMap.end())
		{
			itObject->second.szData = Object;

			itObject->second.FileOperation.ClearFile(ObjectPath);
			if (itObject->second.FileOperation.WriteObject(Object))
			{

				//释放对象锁
				/*itObject->second->ObjectState.szLockUser.clear();
				itObject->second->ObjectState.bLock=FALSE;*/
				return TRUE;
			}
		}
		else
		{
			FileContext Context;// = new _tagFileContext;
			if (Context.FileOperation.OpenObjectFile(ObjectPath, TRUE))
			{

				if (Context.FileOperation.WriteObject(Object))
				{
					//保存到cache
					Context.szData = Object;
					m_FileCacheMap[ObjectPath] = Context;
					return TRUE;
				}
				Context.FileOperation.CloseObject();
			}
			return FALSE;
		}


		return FALSE;
	};

	BOOL UpDataObject(IN  const TCHAR * ObjectPath,IN  const TCHAR * Object,IN ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError);

	//获取目录信息
	BOOL GetDirectoryInfo(IN  const TCHAR * DirectoryPath,IN  const TCHAR * szFinder,OUT ObjectSystem::_tagDirectoryInfo & DirectoryInfo,OUT ObjectSystem::SYSTEMERROR * pError);

	//删除对象
	BOOL DeleteObject(IN  const TCHAR * ObjectOrDir, ObjectSystem::SYSTEMERROR * pError);

	//获取对象状态
	BOOL GetObjectState(IN  const TCHAR * ObjectPath,OUT ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError);
	

	BOOL ReleaseObjectState(IN  const TCHAR * ObjectOrDir,OUT ObjectSystem::SYSTEMERROR * pError);

	BOOL GetCurTime(SYSTEMTIME * npTime, SYSTEMTIME * nCurTime);

	void GetEventQueue(IN  const TCHAR * szUser, IN  const TCHAR * szSession, _tagCallParameter & RetPar);

	BOOL KeepAlived(IN  const TCHAR * szUser, IN  const TCHAR * szSession, IN OUT tstring & szKeepAlivedPar, OUT ObjectSystem::SYSTEMERROR * pError);
	
	template<typename TransportPushT>
	void Loop(TransportPushT & TransportPush)
	{
		//推送消息
		_tagCallParameter SendParameter;
		SYSTEMERROR Error;
		UserContextMapT::iterator itUser = m_UserContextMap.begin();
		for (; itUser != m_UserContextMap.end(); itUser++)
		{
			
			UserContext::SessionT::iterator itSession = itUser->second.SessionMap.begin();
			for (; itSession != itUser->second.SessionMap.end(); itSession++)
			{
				if (itSession->second.EventQueue.size())
				{
					if (TransportPush.CanPush(itSession->second.hHandle))
					{
						SendParameter.ss = itSession->first;
						SendParameter.su = itUser->first;
						SendParameter.oc = OBJECT_SYSTEM_OP_EVENT_PUSH;
						//RetParameter.sn = tagCallParameter.sn;
						SendParameter.el.resize(itSession->second.EventQueue.size());
						std::copy(itSession->second.EventQueue.begin(),
							itSession->second.EventQueue.end(),
							//itSession->second.EventQueue.begin()
							SendParameter.el.begin()
						);
						if (TransportPush.SendMsg(itSession->second.hHandle, SendParameter, Error))
						{
							itSession->second.EventQueue.clear();
						}
					}
					
				}
			}
			
		}
	}
private:

	typedef struct _tagFileContext
	{ 
		FileSystemT				FileOperation;
		tstring					szData;
		__int64					nLastAccessTime;
		ObjectSystem::_tagObjectState			ObjectState;
	}FileContext,*PFileContext;

	typedef struct _tagUserSession
	{
		typedef vector_freelist<_tagObjectSystemEvent> EventQueueT;
		typedef map_freelist<tstring,_tagObjectSystemEvent,less<tstring>> EventSubscribeT;
		//Subscribe/Publish
		EventSubscribeT EventSubscribeMap;
		EventQueueT EventQueue;
		unsigned int nEventTypeMask;
		_tagKeepAlivedPar KeepAlived;
		tstring szKeepAlived;
		Transport::TransportHandle hHandle;
	}UserSession,*PUserSession;
	typedef struct _tagUserContext
	{
		typedef map_freelist<tstring, _tagUserSession, less<tstring>> SessionT;
		SessionT	SessionMap;
		unsigned int nCurrentID;
		unsigned int nEventTypeMask;
	}UserContext, *PUserContext;

	map_freelist<tstring, FileContext,less<tstring> > m_FileCacheMap;

	typedef map_freelist<tstring, UserContext, less<tstring>> UserContextMapT;
	UserContextMapT m_UserContextMap;
	//清理
	BOOL ClearDirCache(const TCHAR * ObjectOrDirPath);

	//解锁对象
	BOOL ReleaseObjectLock(const TCHAR * ObjectPath);

	std::queue<unsigned int> m_FreeSessionQueue;

	
};
