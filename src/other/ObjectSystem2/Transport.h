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
#include <queue>
//#define _DebugOutput
#define _DebugOutput printf_t
template<typename ServerTransportT>
class TransportMiniDirectCall
{
public:
	TransportMiniDirectCall() {};
	~TransportMiniDirectCall() {};
	typedef TransportMiniDirectCall<ServerTransportT> _Myt;
	static _Myt & GetInstance()
	{
		static _Myt _self;
		return _self;
	}
	BOOL CallInterface(tstring & szInPar, tstring & szOutPar,SYSTEMERROR & error)
	{
		return ServerTransportT::GetInstance().CallInterface(szInPar, szOutPar, error);
	}
private:

};

class Transport
{
public:
	Transport() {};
	~Transport() {};

	template<typename TransportMiniT, bool bAutoLoop = false, int nName = 1>
	class Client
	{
	public:
		typedef Client<TransportMiniT, bAutoLoop,nName> _Myt;
		typedef TransportMiniT TransportMiniT;
		struct ClientSession
		{
			std::queue<_tagObjectSystemEvent> EventQueue;
			CObjectSystemInterface * pClientInterface;
		};
		typedef map<tstring, ClientSession, less<tstring>> ClientSessionT;
		ClientSessionT m_ClientSession;

		Client() {};
		~Client() {};
		static _Myt & GetInstance()
		{
			static _Myt _self;
			return _self;
		}
		BOOL CallInterface(tstring & szUserName, tstring & szConversation, int nOpCode, _tagCallParameter & tagCallParameter, _tagCallParameter & RetParameter)
		{
			tstring szInPar,szOutPar;
			tagCallParameter.nOpCode = nOpCode;
			tagCallParameter.szUser = szUserName;
			tagCallParameter.szSession = szConversation;

			SerObjectToXmlBuffer(_tagCallParameter, tagCallParameter, szInPar);
			
			SYSTEMERROR error;
			RetParameter.nError = Error_Sys_Transport_Fail;
			BOOL bRet=TransportMiniT::GetInstance().CallInterface(szInPar, szOutPar, error);
			if (bRet)
			{
				
				SerTCHARXmlBufferToObject(_tagCallParameter , RetParameter, (szOutPar.c_str()));
				if (error == Error_Sys_Transport_Fail) {
					RetParameter.bCallSuccess = FALSE;
				}

				ClientSessionT::iterator itSession = m_ClientSession.find(RetParameter.szSession);
				if (itSession != m_ClientSession.end())
				{
					for (unsigned int i = 0; i<RetParameter.EventList.size(); i++)
					{
						itSession->second.EventQueue.push(RetParameter.EventList[i]);
					}
				}
			}
			return bRet;
		}

		BOOL RegistClient(tstring szSession,CObjectSystemInterface * pInterface)
		{
			ClientSession Session;
			Session.pClientInterface = pInterface;
			m_ClientSession[szSession] = Session;
			return TRUE;
		}

		void Loop(BOOL bKeepAlived=FALSE)
		{
			
			ClientSessionT::iterator itSession = m_ClientSession.begin();
			for (; itSession!= m_ClientSession.end(); itSession++)
			{
				if (bKeepAlived)
				{
					itSession->second.pClientInterface->KeepAlived();
				}
				for (; itSession->second.EventQueue.size();)
				{
					_tagObjectSystemEvent Event = itSession->second.EventQueue.front();
					itSession->second.EventQueue.pop();
					itSession->second.pClientInterface->ObjectEventCallBack(Event);
				}
					
			}
			
		}
	private:

	};

	template<typename ObjectSystemT, bool bAutoLoop = false, int nName = 1>
	class Server
	{
	public:
		typedef Server<ObjectSystemT, bAutoLoop,nName> _Myt;
		Server() {};
		~Server() {};
		static _Myt & GetInstance()
		{
			static _Myt _self;
			return _self;
		}
		
		BOOL CallInterface(tstring & szInPar, tstring & szOutPar, SYSTEMERROR & error)
		{
			//return LocalServerTansportT::GetInstance().CallInterface(szInPar, szOutPar);
			_tagCallParameter tagCallParameter, RetParameter;
			BOOL bRet = TRUE;
			SerTCHARXmlBufferToObject(_tagCallParameter, tagCallParameter, (szInPar.c_str()));
			_tagObjectState ObjectState;
			ObjectState.bLock = tagCallParameter.tagObjectState.bLock;
			ObjectState.nLockTime = tagCallParameter.tagObjectState.nLockTime;
			ObjectState.nType = tagCallParameter.tagObjectState.nType;
			ObjectState.szLockUser = tagCallParameter.tagObjectState.szLockUser;
			SYSTEMERROR		Error = Error_No;
			ObjectSystemEvent Event;
			Event.szObjectAddress = tagCallParameter.ObjectPath;
			Event.nEventType = tagCallParameter.nRegEventType;

			switch (tagCallParameter.nOpCode)
			{
			case OBJECT_SYSTEM_OP_GETOBJECT:
			{
				RetParameter.bCallSuccess = ObjectSystemT::GetInstance().GetObject(tagCallParameter.ObjectPath, RetParameter.Object, tagCallParameter.tagObjectState, &Error);
				if (RetParameter.bCallSuccess)
				{
					Event.nEventType = ObjectEvent_Get;
					if (RetParameter.bCallSuccess) ObjectSystemT::GetInstance().BroadcastObjectEvent(tagCallParameter.szUser, tagCallParameter.szSession, Event, &Error);
				}
			}

			break;
			case OBJECT_SYSTEM_OP_UPDATAOBJECT:
				//ObjectState.szLockUser=szUserName;
				//RetParameter.bCallSuccess=gpObjectSystem->UpDataObject(tagCallParameter.ObjectPath,tagCallParameter.Object,ObjectState,&Error);
				RetParameter.bCallSuccess = ObjectSystemT::GetInstance().UpDataObject(tagCallParameter.ObjectPath, tagCallParameter.Object, &Error);
				Event.nEventType = ObjectEvent_Updata;
				if (RetParameter.bCallSuccess) ObjectSystemT::GetInstance().BroadcastObjectEvent(tagCallParameter.szUser, tagCallParameter.szSession, Event, &Error);
				break;
			case OBJECT_SYSTEM_OP_GETDIRECTORYINFO:
				RetParameter.bCallSuccess = ObjectSystemT::GetInstance().GetDirectoryInfo(tagCallParameter.ObjectPath, tagCallParameter.szFinder, RetParameter.DirectoryInfo, &Error);
				break;
			case OBJECT_SYSTEM_OP_DELETEOBJECT:
				RetParameter.bCallSuccess = ObjectSystemT::GetInstance().DeleteObject(tagCallParameter.ObjectPath, &Error);
				Event.nEventType = ObjectEvent_Delete;
				if (RetParameter.bCallSuccess) ObjectSystemT::GetInstance().BroadcastObjectEvent(tagCallParameter.szUser, tagCallParameter.szSession, Event, &Error);
				break;
			case OBJECT_SYSTEM_OP_GETOBJECTSTATE:
				break;
			case OBJECT_SYSTEM_OP_UPDATAOBJECTSTATE:
				break;
			case OBJECT_SYSTEM_OP_LOGONINSYSTEM:
				RetParameter.bCallSuccess = ObjectSystemT::GetInstance().LogonInSystem(tagCallParameter.szUser, tagCallParameter.szPassword, tagCallParameter.szSession);
				break;
			case OBJECT_SYSTEM_OP_LOGONOUTSYSTEM:
				RetParameter.bCallSuccess = ObjectSystemT::GetInstance().LogonOutSystem();

				break;
			case OBJECT_SYSTEM_OP_GETCURTIME:
			{
				vector<unsigned char> npTime, nCurTime;

				CBase64Zip::Base64ZipUnCompress(tagCallParameter.strPar[_T("npTime")].szData, npTime);
				CBase64Zip::Base64ZipUnCompress(tagCallParameter.strPar[_T("nCurTime")].szData, nCurTime);
				RetParameter.bCallSuccess = ObjectSystemT::GetInstance().GetCurTime((SYSTEMTIME*)&npTime[0], (SYSTEMTIME*)&nCurTime[0]);
				CBase64Zip::Base64ZipCompress(&nCurTime[0], sizeof(SYSTEMTIME), RetParameter.strPar[_T("nCurTime")].szData);

			}
			break;
			case OBJECT_SYSTEM_OP_RELEASEOBJSTATE:
				RetParameter.bCallSuccess = ObjectSystemT::GetInstance().ReleaseObjectState(tagCallParameter.ObjectPath, &Error);
				break;
			case OBJECT_SYSTEM_OP_REGIST_OBJEVENT:
				
				RetParameter.bCallSuccess = ObjectSystemT::GetInstance().RegistObjectEvent(tagCallParameter.szUser, tagCallParameter.szSession, Event, &Error);
				break;
			case OBJECT_SYSTEM_OP_NEED_NEWOBJECT:
				RetParameter.bCallSuccess = ObjectSystemT::GetInstance().NeedNewObject(tagCallParameter.ObjectPath, &Error);
				Event.nEventType = ObjectEvent_NeedNew;
				if(RetParameter.bCallSuccess) ObjectSystemT::GetInstance().BroadcastObjectEvent(tagCallParameter.szUser, tagCallParameter.szSession,Event, &Error);

				break;
			case OBJECT_SYSTEM_OP_KEEPALIVED:
				{
					_tagstrParameter strPar;
					if (ObjectSystemT::GetInstance().KeepAlived(tagCallParameter.szUser, tagCallParameter.szSession, strPar.szData, &Error))
					{
						RetParameter.strPar[_T("kpalv")] = strPar;
					}
				}
				
				break;
			default:
				bRet = FALSE;
				_DebugOutput(_T("´íÎóµÄÃüÁî"));
				break;
			}
			if (bRet)
			{
				RetParameter.szSession = tagCallParameter.szSession;
				ObjectSystemT::GetInstance().GetEventQueue(tagCallParameter.szUser, tagCallParameter.szSession, RetParameter);
				if (RetParameter.EventList.size())
				{
					//printf_t(_T("111"));
				}
			}
			RetParameter.nError = (unsigned int)Error;

			SerObjectToXmlBuffer(_tagCallParameter, RetParameter, szOutPar);
			/*
			if (tagCallParameter.nOpCode == OBJECT_SYSTEM_OP_GETOBJECT)
			{
				_DebugOutput(_T("op=%d %s %s Data=%s \n\n"), tagCallParameter.nOpCode, tagCallParameter.ObjectPath.c_str(),
					 bRet ? _T("ok") : _T("fail"), szOutPar.c_str());
			}
			*/
			return bRet;
			
		}
		void Loop()
		{

		}
	private:

	};

private:

};

#undef _DebugOutput