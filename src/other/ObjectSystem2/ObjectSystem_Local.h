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
	BOOL GetUser(tstring & szUserName, tstring & szPassword, _tagUserMapSet &Set)
	{
		Set.szUserName = szUserName;
		Set.szPassword = szPassword;
		Set.szUserType = _T("管理员");
		
		return TRUE;
	};
};

template<typename ConfigT,typename FileSystemT, typename AuthT = DefAuth> 
class CObjectSystem_Local: public CObjectSystemInterface
{
public:
	typedef CObjectSystem_Local<ConfigT, FileSystemT> _Myt;

	unsigned int m_nCurSessionNum;
	CObjectSystem_Local(void) {
		m_nCurSessionNum = 0;
	};
	~CObjectSystem_Local(void) {};
	//tstring m_szRootPath;
	static _Myt & GetInstance() {
		
		static _Myt _self;
		return _self;
	}

	BOOL LogonInSystem(IN tstring & szUserName, IN tstring & szPassword, OUT tstring & szSession);
	BOOL LogonOutSystem();

	BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError);
	
	BOOL NeedNewObject(IN tstring & ObjectPath, OUT ObjectSystem::SYSTEMERROR * pError);

	BOOL BroadcastObjectEvent(IN tstring & szUser, IN tstring & szSession, IN ObjectSystem::ObjectSystemEvent & Event, OUT ObjectSystem::SYSTEMERROR * pError);

	BOOL RegistObjectEvent(IN tstring & szUser, IN tstring & szSession, IN ObjectSystemEvent & RegEvent, OUT ObjectSystem::SYSTEMERROR * pError);
	//更新对象到存储
	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object, ObjectSystem::SYSTEMERROR * pError);

	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,IN ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError);

	//获取目录信息
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT ObjectSystem::_tagDirectoryInfo & DirectoryInfo,OUT ObjectSystem::SYSTEMERROR * pError);

	//删除对象
	BOOL DeleteObject(IN tstring & ObjectOrDir, ObjectSystem::SYSTEMERROR * pError);

	//获取对象状态
	BOOL GetObjectState(IN tstring & ObjectPath,OUT ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError);
	

	BOOL ReleaseObjectState(IN tstring & ObjectOrDir,OUT ObjectSystem::SYSTEMERROR * pError);

	BOOL GetCurTime(SYSTEMTIME * npTime, SYSTEMTIME * nCurTime);

	void GetEventQueue(IN tstring & szUser, IN tstring & szSession, _tagCallParameter & RetPar);

	BOOL KeepAlived(IN tstring & szUser, IN tstring & szSession, IN OUT tstring & szKeepAlivedPar, OUT ObjectSystem::SYSTEMERROR * pError);

private:

	typedef struct _tagFileContext
	{ 
		FileSystemT	FileOperation;
		tstring					szData;
		__int64					nLastAccessTime;
		ObjectSystem::_tagObjectState			ObjectState;
	}FileContext,*PFileContext;

	typedef struct _tagUserSession
	{
		typedef vector<_tagObjectSystemEvent> EventQueueT;
		typedef map<tstring,_tagObjectSystemEvent,less<tstring>> EventSubscribeT;
		//Subscribe/Publish
		EventSubscribeT EventSubscribeMap;
		EventQueueT EventQueue;
		unsigned int nEventTypeMask;
		_tagKeepAlivedPar KeepAlived;
		tstring szKeepAlived;
	}UserSession,*PUserSession;
	typedef struct _tagUserContext
	{
		typedef map<tstring, _tagUserSession, less<tstring>> SessionT;
		SessionT	SessionMap;
		unsigned int nCurrentID;
		unsigned int nEventTypeMask;
	}UserContext, *PUserContext;

	map<tstring, PFileContext,less<tstring> > m_FileCacheMap;

	typedef map<tstring, UserContext, less<tstring>> UserContextMapT;
	UserContextMapT m_UserContextMap;
	//清理
	BOOL ClearDirCache(tstring & ObjectOrDirPath);

	//解锁对象
	BOOL ReleaseObjectLock(tstring & ObjectPath);

	std::queue<unsigned int> m_FreeSessionQueue;

	
};
