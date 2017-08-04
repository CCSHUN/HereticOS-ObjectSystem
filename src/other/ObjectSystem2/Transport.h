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
#define _DebugOutput1 
//#define _DebugOutput1 printf_t
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
	BOOL CallInterfacePar(_tagCallParameter & tagCallParameter, _tagCallParameter & RetParameter, SYSTEMERROR & error)
	{
		return ServerTransportT::GetInstance().CallInterfacePar(tagCallParameter, RetParameter, error);
	}

	BOOL CallInterfaceStr(tstring & szInPar, tstring & szOutPar,SYSTEMERROR & error)
	{
		return ServerTransportT::GetInstance().CallInterfaceStr(szInPar, szOutPar, error);
	}
	
private:

};

namespace Transport
{

	template<typename TransportMiniT, bool bAutoLoop = false, bool bSerialize = true, int nName = 1>
	class Client
	{
	public:
		typedef Client<TransportMiniT, bAutoLoop, bSerialize,nName> _Myt;
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
		BOOL CallInterface(_tagCallParameter & tagCallParameter, _tagCallParameter & RetParameter)
		{
			BOOL bRet = FALSE;
			SYSTEMERROR error;
			RetParameter.Err = Error_Sys_Transport_Fail;
			if (bSerialize)
			{
				tstring szInPar, szOutPar;
				SerObjectToXmlBuffer(_tagCallParameter, tagCallParameter, szInPar);
				bRet = TransportMiniT::GetInstance().CallInterfaceStr(szInPar, szOutPar, error);
				if (bRet)
				{
					if (tagCallParameter.oc == OBJECT_SYSTEM_OP_GETOBJECT)_DebugOutput1(_T("Client GetObject %s %s\n"), tagCallParameter.op.c_str(), RetParameter.ob.c_str());
					SerTCHARXmlBufferToObject(_tagCallParameter, RetParameter, (szOutPar.c_str()));
				}
			}
			else
			{
				bRet = TransportMiniT::GetInstance().CallInterfacePar(tagCallParameter, RetParameter, error);
			}
			
			if (bRet)
			{
				
				if (error == Error_Sys_Transport_Fail) {
					RetParameter.bcs = FALSE;
				}

				ClientSessionT::iterator itSession = m_ClientSession.find(RetParameter.ss.c_str());
				if (itSession != m_ClientSession.end())
				{
					for (unsigned int i = 0; i<RetParameter.el.size(); i++)
					{
						itSession->second.EventQueue.push(RetParameter.el[i]);
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
		};
		
		//BOOL CallInterface(_tagCallParameter & tagCallParameter, _tagCallParameter & RetParameter,SYSTEMERROR & error)
		template<typename CallParameterT>
		BOOL CallInterfacePar(CallParameterT & tagCallParameter, CallParameterT & RetParameter,SYSTEMERROR&error)
		{
			BOOL bRet = TRUE;
			
			SYSTEMERROR		Error = Error_No;
			ObjectSystemEvent Event;
			Event.szObjectAddress = tagCallParameter.op;
			Event.nEventType = tagCallParameter.np;

			switch (tagCallParameter.oc)
			{
			case OBJECT_SYSTEM_OP_GETOBJECT:
			{
				RetParameter.bcs = ObjectSystemT::GetInstance().GetObject(tagCallParameter.op, RetParameter.ob, tagCallParameter.Os, &Error);
				if (RetParameter.bcs)
				{
					Event.nEventType = ObjectEvent_Get;
					if (RetParameter.bcs) ObjectSystemT::GetInstance().BroadcastObjectEvent(tagCallParameter.su, tagCallParameter.ss, Event, &Error);
				}
				_DebugOutput1(_T("Server GetObject %s %s\n"), tagCallParameter.op.c_str(), RetParameter.ob.c_str());
			}

			break;
			case OBJECT_SYSTEM_OP_UPDATAOBJECT:
				//ObjectState.szLockUser=szUserName;
				//RetParameter.bCallSuccess=gpObjectSystem->UpDataObject(tagCallParameter.ObjectPath,tagCallParameter.Object,ObjectState,&Error);
				RetParameter.bcs = ObjectSystemT::GetInstance().UpDataObject(tagCallParameter.op, tagCallParameter.ob, &Error);
				Event.nEventType = ObjectEvent_Updata;
				if (RetParameter.bcs) ObjectSystemT::GetInstance().BroadcastObjectEvent(tagCallParameter.su, tagCallParameter.ss, Event, &Error);
				break;
			case OBJECT_SYSTEM_OP_GETDIRECTORYINFO:
				RetParameter.bcs = ObjectSystemT::GetInstance().GetDirectoryInfo(tagCallParameter.op.c_str(), tagCallParameter.sf.c_str(), RetParameter.di, &Error);
				break;
			case OBJECT_SYSTEM_OP_DELETEOBJECT:
				RetParameter.bcs = ObjectSystemT::GetInstance().DeleteObject(tagCallParameter.op.c_str(), &Error);
				Event.nEventType = ObjectEvent_Delete;
				if (RetParameter.bcs) ObjectSystemT::GetInstance().BroadcastObjectEvent(tagCallParameter.su, tagCallParameter.ss, Event, &Error);
				break;
			case OBJECT_SYSTEM_OP_GETOBJECTSTATE:
				break;
			case OBJECT_SYSTEM_OP_UPDATAOBJECTSTATE:
				break;
			case OBJECT_SYSTEM_OP_LOGONINSYSTEM:
			{
				tstring_tmp szPassword = _T("");
				map<tstring_tmp, _tagstrParameter, less<tstring_tmp> >::iterator itFind = tagCallParameter.sp.find(_T("ps"));
				if (itFind != tagCallParameter.sp.end())
				{
					szPassword = itFind->second.szData.c_str();
				}
				RetParameter.bcs = ObjectSystemT::GetInstance().LogonInSystem(tagCallParameter.su.c_str(), szPassword.c_str(), tagCallParameter.ss);
			}
				
				break;
			case OBJECT_SYSTEM_OP_LOGONOUTSYSTEM:
				RetParameter.bcs = ObjectSystemT::GetInstance().LogonOutSystem();

				break;
			case OBJECT_SYSTEM_OP_GETCURTIME:
			{
				vector<unsigned char> npTime, nCurTime;

				CBase64Zip::Base64ZipUnCompress(tagCallParameter.sp[_T("npTime")].szData, npTime);
				CBase64Zip::Base64ZipUnCompress(tagCallParameter.sp[_T("nCurTime")].szData, nCurTime);
				RetParameter.bcs = ObjectSystemT::GetInstance().GetCurTime((SYSTEMTIME*)&npTime[0], (SYSTEMTIME*)&nCurTime[0]);
				CBase64Zip::Base64ZipCompress(&nCurTime[0], sizeof(SYSTEMTIME), RetParameter.sp[_T("nCurTime")].szData);

			}
			break;
			case OBJECT_SYSTEM_OP_RELEASEOBJSTATE:
				RetParameter.bcs = ObjectSystemT::GetInstance().ReleaseObjectState(tagCallParameter.op.c_str(), &Error);
				break;
			case OBJECT_SYSTEM_OP_REGIST_OBJEVENT:

				RetParameter.bcs = ObjectSystemT::GetInstance().RegistObjectEvent(tagCallParameter.su.c_str(), tagCallParameter.ss.c_str(), Event, &Error);
				break;
			case OBJECT_SYSTEM_OP_NEED_NEWOBJECT:
				RetParameter.bcs = ObjectSystemT::GetInstance().NeedNewObject(tagCallParameter.op.c_str(), &Error);
				Event.nEventType = ObjectEvent_NeedNew;
				if (RetParameter.bcs) ObjectSystemT::GetInstance().BroadcastObjectEvent(tagCallParameter.su, tagCallParameter.ss, Event, &Error);

				break;
			case OBJECT_SYSTEM_OP_KEEPALIVED:
			{
				_tagstrParameter strPar;
				if (ObjectSystemT::GetInstance().KeepAlived(tagCallParameter.su.c_str(), tagCallParameter.ss.c_str(), strPar.szData, &Error))
				{
					RetParameter.sp[_T("kpalv")] = strPar;
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
				RetParameter.ss = tagCallParameter.ss;
				ObjectSystemT::GetInstance().GetEventQueue(tagCallParameter.su.c_str(), tagCallParameter.ss.c_str(), RetParameter);
				if (RetParameter.el.size())
				{
					//printf_t(_T("111"));
				}
			}
			RetParameter.Err = (unsigned int)Error;
			return bRet;
		}

		template<typename StringT>
		BOOL CallInterfaceStr(StringT & szInPar, StringT & szOutPar, SYSTEMERROR & error)
		{
			//return LocalServerTansportT::GetInstance().CallInterface(szInPar, szOutPar);
			_tagCallParameter tagCallParameter, RetParameter;
			BOOL bRet = TRUE;
			SerTCHARXmlBufferToObject(_tagCallParameter, tagCallParameter, (szInPar.c_str()));
			bRet = CallInterfacePar( tagCallParameter,   RetParameter, error);

			SerObjectToXmlBuffer(_tagCallParameter, RetParameter, szOutPar);
			if(tagCallParameter.oc == OBJECT_SYSTEM_OP_GETOBJECT) _DebugOutput1(_T("RetPar %s %s\n"), tagCallParameter.op.c_str(), szOutPar.c_str());
			
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


};

#undef _DebugOutput