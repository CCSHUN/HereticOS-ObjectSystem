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
#define _DebugOutput

template<typename ConfigT, typename FileSystemT,typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::LogonInSystem(IN tstring & szUserName, IN tstring & szPassword,OUT tstring & szSession)
{

	_DebugOutput(_T("CObjectSystem_Local"), _T("LogonInSystem %s UserName=%s"),_T(""), szUserName.c_str());
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
		
		szSession = CAutoVal(nNewSession);
		tmp.KeepAlived.nWndPos = nNewSession;
		tmp.KeepAlived.nWndLen = (1000) / MAX_IOPS;
		itUser->second.SessionMap[szSession] = tmp;

		return TRUE;
	}
	return FALSE;
}

template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::LogonOutSystem()
{
	return TRUE;
}

template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError)
{
	map<tstring, PFileContext,less<tstring> >::iterator itObject;
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

	*pError= ObjectSystem::Error_No;
	itObject=m_FileCacheMap.find(ObjectPath);
	if(itObject!=m_FileCacheMap.end())
	{
		Object=itObject->second->szData;
		if(itObject->second->ObjectState.szLockUser.length()
			&&itObject->second->ObjectState.bLock)
		{
			if(itObject->second->ObjectState.szLockUser==
				ObjectState.szLockUser)
			{
				itObject->second->ObjectState=ObjectState;
				_DebugOutput(_T("GetObject"),_T("����[%s]���Ѹ��� Object=%s �����û�=%s �Ƿ�ռ��=%d"),
					itObject->second->ObjectState.szLockUser.c_str(),
					ObjectPath.c_str(),ObjectState.szLockUser.c_str(),ObjectState.bLock);
			}else
			{
				//���������� ���ض���ǰ����
				ObjectState=itObject->second->ObjectState;
				_DebugOutput(_T("GetObject"),_T("����[%s]��������ֻ���� Object=%s �����û�=%s �Ƿ�ռ��=%d"),
					itObject->second->ObjectState.szLockUser.c_str(),
					ObjectPath.c_str(),ObjectState.szLockUser.c_str(),ObjectState.bLock);
				*pError= ObjectSystem::Error_ObjectAlreadyLock;
			}
			
		}else
		{

			//ռ�ö�����
			itObject->second->ObjectState=ObjectState;
			_DebugOutput(_T("GetObject"),_T("���ǻ�ȡ�� Object=%s �����û�=%s �Ƿ�ռ��=%d"),
				ObjectPath.c_str(),ObjectState.szLockUser.c_str(),ObjectState.bLock);
		}

	}else
	{
		PFileContext pContext=new _tagFileContext;
		tstring ObjectAddr=ConfigT::GetInstance().strLocalSystemDirectory+ObjectPath;
		if(pContext->FileOperation.OpenObjectFile_OnlyOpen(ObjectAddr))
		{
			if(pContext->FileOperation.ReadObject(Object))
			{
				pContext->szData=Object;
				/*pContext->ObjectState.bLock=FALSE;
				pContext->ObjectState.nLockTime=0;
				pContext->ObjectState.szLockUser=_T("");
				pContext->ObjectState.nType=CObjectSystemInterface::Nonmoral;*/
				pContext->ObjectState=ObjectState;

				m_FileCacheMap[ObjectPath]=pContext;
				if(Object.length()==0)
				{
					*pError=ObjectSystem::Error_Sys_OpenFileFail;
					return FALSE;
				}

				
				//if(ObjectState.bLock)
				
				pContext->ObjectState=ObjectState;
				_DebugOutput(_T("GetObject"),_T("������ Object=%s �����û�=%s �Ƿ�ռ��=%d"),
					ObjectPath.c_str(),ObjectState.szLockUser.c_str(),ObjectState.bLock);
				
				
				return TRUE;
			}
			pContext->FileOperation.CloseObject();
		}
		delete pContext;

		*pError=ObjectSystem::Error_Sys_OpenFileFail;

		return FALSE;
	}

	return TRUE;
}
template<typename ConfigT, typename FileSystemT, typename AuthT>
void CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::GetEventQueue(IN tstring & szUser, IN tstring & szSession, _tagCallParameter & RetPar)
{
	UserContextMapT::iterator itUser = m_UserContextMap.find(szUser);

	if (itUser != m_UserContextMap.end())
	{
		UserContext::SessionT::iterator itSession = itUser->second.SessionMap.find(szSession);
		if (itSession != itUser->second.SessionMap.end())
		{
			RetPar.EventList=itSession->second.EventQueue ;

			//û��ȷ�ϣ�����������
			itSession->second.EventQueue.clear();
		}
	}
	return ;
}

template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::KeepAlived(IN tstring & szUser, IN tstring & szSession,IN OUT tstring & szKeepAlivedPar, OUT ObjectSystem::SYSTEMERROR * pError)
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

template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::GetCurTime(SYSTEMTIME * npTime, SYSTEMTIME * nCurTime)
{
	GetLocalTime(nCurTime);
	return TRUE;
}



template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::BroadcastObjectEvent(IN tstring & szUser, IN tstring & szSession, IN ObjectSystem::ObjectSystemEvent & Event, OUT ObjectSystem::SYSTEMERROR * pError)
{
	UserContextMapT::iterator itUser = m_UserContextMap.begin();
	for (;itUser!= m_UserContextMap.end();itUser++)
	{
		if (itUser->second.nEventTypeMask&Event.nEventType)
		{
			UserContext::SessionT::iterator itSession = itUser->second.SessionMap.begin();
			for (; itSession!= itUser->second.SessionMap.end(); itSession++)
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
}

template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::NeedNewObject(IN tstring & ObjectPath, OUT ObjectSystem::SYSTEMERROR * pError)
{
	return TRUE;
}

template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::RegistObjectEvent(IN tstring & szUser, IN tstring & szSession, IN ObjectSystemEvent & RegEvent, OUT ObjectSystem::SYSTEMERROR * pError)
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


template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::GetObjectState(IN tstring & ObjectPath,OUT ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError)
{
	map<tstring, PFileContext,less<tstring> >::iterator itObject;

	itObject=m_FileCacheMap.find(ObjectPath);
	if(itObject!=m_FileCacheMap.end())
	{
		ObjectState=itObject->second->ObjectState;
	}
	return FALSE;
}

template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::UpDataObject(IN tstring & ObjectPath,IN tstring & Object,IN ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError)
{
	map<tstring, PFileContext,less<tstring> >::iterator itObject;
	
	itObject=m_FileCacheMap.find(ObjectPath);
	tstring ObjectAddr= ConfigT::GetInstance().strLocalSystemDirectory+ObjectPath;
	*pError= ObjectSystem::Error_No;
	if(itObject!=m_FileCacheMap.end())
	{
		//�����
		if(itObject->second->ObjectState.bLock&&itObject->second->ObjectState.szLockUser.length())
		{
			if(itObject->second->ObjectState.szLockUser!=ObjectState.szLockUser)
			{
				_DebugOutput(_T("UpDataObject"),_T("���� Object=%s �����û�=%s �����Ѿ����� ��ǰ�����û�=%s"),
					ObjectPath.c_str(),ObjectState.szLockUser.c_str(),
					itObject->second->ObjectState.szLockUser.c_str());
				*pError=ObjectSystem::Error_ObjectAlreadyLock;
				return FALSE;
			}
		}
		itObject->second->szData=Object;
		
		itObject->second->FileOperation.ClearFile(ObjectAddr);
		if(itObject->second->FileOperation.WriteObject(Object))
		{

			//�ͷŶ�����
			itObject->second->ObjectState.szLockUser.clear();
			itObject->second->ObjectState.bLock=FALSE;
			_DebugOutput(_T("UpDataObject"),_T("�ͷŶ����� Object=%s �����û�=%s "),
				ObjectPath.c_str(),ObjectState.szLockUser.c_str());
			return TRUE;
		}
	}
	else
	{
		PFileContext pContext=new _tagFileContext;
		if(pContext->FileOperation.OpenObjectFile(ObjectAddr,TRUE))
		{
			
			if(pContext->FileOperation.WriteObject(Object))
			{
				//���浽cache
				pContext->szData=Object;
				pContext->ObjectState.bLock=FALSE;
				pContext->ObjectState.nLockTime=0;
				pContext->ObjectState.szLockUser=_T("");
				pContext->ObjectState.nType=ObjectSystem::Nonmoral;
				m_FileCacheMap[ObjectPath]=pContext;
				return TRUE;
			}
			pContext->FileOperation.CloseObject();
		}
		delete pContext;
		*pError=ObjectSystem::Error_Sys_OpenFileFail;
		return FALSE;
	}
	

	return FALSE;
}

//���¶��󵽴洢
template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::UpDataObject(IN tstring & ObjectPath,IN tstring & Object, ObjectSystem::SYSTEMERROR * pError)
{
	map<tstring, PFileContext,less<tstring> >::iterator itObject;
	
	itObject=m_FileCacheMap.find(ObjectPath);
	tstring ObjectAddr= ConfigT::GetInstance().strLocalSystemDirectory+ObjectPath;
	if(itObject!=m_FileCacheMap.end())
	{
		itObject->second->szData=Object;
		
		itObject->second->FileOperation.ClearFile(ObjectAddr);
		if(itObject->second->FileOperation.WriteObject(Object))
		{

			//�ͷŶ�����
			/*itObject->second->ObjectState.szLockUser.clear();
			itObject->second->ObjectState.bLock=FALSE;*/
			return TRUE;
		}
	}
	else
	{
		PFileContext pContext=new _tagFileContext;
		if(pContext->FileOperation.OpenObjectFile(ObjectAddr,TRUE))
		{
			
			if(pContext->FileOperation.WriteObject(Object))
			{
				//���浽cache
				pContext->szData=Object;
				m_FileCacheMap[ObjectPath]=pContext;
				return TRUE;
			}
			pContext->FileOperation.CloseObject();
		}
		delete pContext;
		return FALSE;
	}
	

	return FALSE;
}


template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT ObjectSystem::_tagDirectoryInfo & DirectoryInfo,OUT ObjectSystem::SYSTEMERROR * pError)
{
	tstring ObjectAddr= ConfigT::GetInstance().strLocalSystemDirectory+DirectoryPath;
	if (ObjectAddr.at(ObjectAddr.length()-1) != '\\')
	{
		ObjectAddr += '\\';
	}
	FileSystemT::GetDirectoryInfo(ObjectAddr, szFinder,  DirectoryInfo, pError);

	return TRUE;
}

template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::ReleaseObjectLock(tstring & ObjectPath)
{
	return TRUE;
}

template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::ReleaseObjectState(IN tstring & ObjectOrDir,OUT ObjectSystem::SYSTEMERROR * pError)
{
	map<tstring, PFileContext,less<tstring> >::iterator itObject=m_FileCacheMap.begin();
	map<tstring, PFileContext,less<tstring> >::iterator itOldObject=itObject;
	for(;itObject!=m_FileCacheMap.end();itObject++)
	{
		if(strstr_t(itObject->first.c_str(),ObjectOrDir.c_str()))
		{
			//�����cache

			itObject->second->ObjectState.bLock=FALSE;
			itObject->second->ObjectState.nType=ObjectSystem::Nonmoral;
			itObject->second->ObjectState.nLockTime=0;
			itObject->second->ObjectState.szLockUser.clear();
		}
	}
	return TRUE;
}

template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::ClearDirCache(tstring & ObjectOrDirPath)
{
	map<tstring, PFileContext,less<tstring> >::iterator itObject=m_FileCacheMap.begin();
	map<tstring, PFileContext,less<tstring> >::iterator itOldObject=itObject;
	for(;itObject!=m_FileCacheMap.end();itObject++)
	{
		if(strstr_t(itObject->first.c_str(),ObjectOrDirPath.c_str()))
		{
			//�����cache

			delete itObject->second;
			m_FileCacheMap.erase(itObject);
			if(m_FileCacheMap.size()==0)
			{
				return TRUE;
			}
			itObject=m_FileCacheMap.begin();
		}
	}
	return TRUE;
}
//ɾ������
template<typename ConfigT, typename FileSystemT, typename AuthT>
BOOL CObjectSystem_Local<ConfigT, FileSystemT, AuthT>::DeleteObject(IN tstring & ObjectOrDir, ObjectSystem::SYSTEMERROR * pError)
{
	
	ClearDirCache(ObjectOrDir);

	tstring ObjectAddr= ConfigT::GetInstance().strLocalSystemDirectory+ObjectOrDir;
	CObjectFileOperation del;
	del.DelObjectOrDir(ObjectAddr);

	return TRUE;
}