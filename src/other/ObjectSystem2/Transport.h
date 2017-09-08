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

#define MSG_PUSH_CHANNEL 1  //PUSH 模式通讯通道
#define PRE_TRANSOPRT_CHANNEL_COUNT_LOG2 4 //16个
#define PRE_TRANSOPRT_CHANNEL_COUNT 1<<PRE_TRANSOPRT_CHANNEL_COUNT_LOG2 //16个
//#define _DebugOutput1 printf_t




namespace Transport
{
	typedef void * TransportHandle;
	template<typename TransportMiniT, typename ContainerT, bool bAutoLoop = false, bool bSerialize = true>
	class Client :public CSystemContainerObjectBase<Client<TransportMiniT, ContainerT, bAutoLoop, bSerialize>, ContainerT>
	{
	public:
		typedef Client<TransportMiniT, ContainerT, bAutoLoop, bSerialize> _Myt;
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
		/*
		static _Myt & GetInstance()
		{
			static _Myt _self;
			return _self;
		}
		*/
		BOOL CallInterface(_tagCallParameter & cp, _tagCallParameter & rp)
		{
			BOOL bRet = FALSE;
			SYSTEMERROR error;
			rp.Err = Error_Sys_Transport_Fail;
			if (bSerialize)
			{
				tstring szInPar, szOutPar;
				SerObjectToXmlBuffer(_tagCallParameter, cp, szInPar);
				bRet = TransportMiniT::GetInstance().CallInterfaceStr(szInPar, szOutPar, error);
				if (bRet)
				{
					if (cp.oc == OBJECT_SYSTEM_OP_GETOBJECT)_DebugOutput1(_T("Client GetObject %s %s\n"), cp.op.c_str(), rp.ob.c_str());
					SerTCHARXmlBufferToObject(_tagCallParameter, rp, (szOutPar.c_str()));
				}
			}
			else
			{
				bRet = TransportMiniT::GetInstance().CallInterfacePar(cp, rp, error);
			}
			
			if (bRet)
			{
				
				if (error == Error_Sys_Transport_Fail) {
					rp.bcs = FALSE;
				}

				ClientSessionT::iterator itSession = m_ClientSession.find(rp.ss.c_str());
				if (itSession != m_ClientSession.end())
				{
					for (unsigned int i = 0; i<rp.el.size(); i++)
					{
						itSession->second.EventQueue.push(rp.el[i]);
					}
				}
			}
			GCContainer<MemoryMgr__StaticGC_Tmp>::GetInstance().ReleaseGC(MEMGC_CLIENT_LEVEL);
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
			tstring szPushMsg;
			_tagCallParameter rp;
			//接收推送
			TransportMiniT::GetInstance().RecvAllMsg();
			GCContainer<MemoryMgr__StaticGC_Tmp>::GetInstance().ReleaseGC(MEMGC_CLIENT_LEVEL);
			for (;;)
			{
				GCContainer<MemoryMgr__StaticGC_Tmp>::GetInstance().ReleaseGC(MEMGC_CLIENT_LEVEL);
				if (TransportMiniT::GetInstance().RecvMsg(MSG_PUSH_CHANNEL, szPushMsg))
				{
					SerTCHARXmlBufferToObject(_tagCallParameter, rp, (szPushMsg.c_str()));
					ClientSessionT::iterator itSession = m_ClientSession.find(rp.ss.c_str());
					if (itSession != m_ClientSession.end())
					{
						for (unsigned int i = 0; i<rp.el.size(); i++)
						{
							itSession->second.EventQueue.push(rp.el[i]);
						}
					}
				}
				else
				{
					break;
				}
			}
			
			//推送消息
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

	template<typename ObjectSystemT, typename ContainerT,bool bAutoLoop = false>
	class Server :public CSystemContainerObjectBase<Server<ObjectSystemT, ContainerT, bAutoLoop>, ContainerT>
	{
	public:
		typedef Server<ObjectSystemT, ContainerT, bAutoLoop> _Myt;
		Server() {};
		~Server() {};
		/*
		static _Myt & GetInstance()
		{
			static _Myt _self;
			return _self;
		};
		*/
		template<typename TransportMiniT>
		class TransportPushWrap :public CSystemContainerObjectBase<TransportPushWrap<TransportMiniT>, ContainerT>
		{
		public:
			TransportPushWrap() {};
			~TransportPushWrap() {};
			typedef TransportPushWrap<TransportMiniT> _Myt;
			/*
			static _Myt & GetInstance()
			{
				static _Myt _self;
				return _self;
			}*/

			BOOL SendMsg(TransportHandle & hTransport, _tagCallParameter & rp, SYSTEMERROR&error)
			{
				tstring szOutPar;
				BOOL bRet = TRUE;
				BOOL bCanRecv, bCanSend;
				if (TransportMiniT::GetInstance().CanSend(bCanSend))
				{
					if (bCanSend)
					{
						SerObjectToXmlBuffer(_tagCallParameter, rp, szOutPar);
						return TransportMiniT::GetInstance().SendMsg(hTransport, (const u_char *)szOutPar.c_str(), (szOutPar.size() + 1) * sizeof(TCHAR), error, MSG_PUSH_CHANNEL);
					}
					
				}
				return FALSE;
			}
			BOOL CanPush(TransportHandle & hTransport)
			{
				return TransportMiniT::GetInstance().CanPush(hTransport);
			}
		private:

		};
		template<typename TransportMiniT>
		void Loop(TransportMiniT * pTransport)
		{
			//推送消息
			ObjectSystemT::GetInstance().Loop(TransportPushWrap<TransportMiniT>::GetInstance());
		}
		//BOOL CallInterface(_tagCallParameter & tagCallParameter, _tagCallParameter & RetParameter,SYSTEMERROR & error)
		template<typename TransportMiniT,typename CallParameterT>
		BOOL CallInterfacePar(TransportHandle hTransport,CallParameterT & tagCallParameter, CallParameterT & RetParameter,SYSTEMERROR&error)
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

				RetParameter.bcs =  ObjectSystemT::GetInstance().RegistObjectEvent(tagCallParameter.su.c_str(), tagCallParameter.ss.c_str(), Event, &Error);
				break;
			
			default:
				bRet = FALSE;
				_DebugOutput(_T("错误的命令"));
				break;
			}
			if (bRet)
			{
				RetParameter.ss = tagCallParameter.ss;
				RetParameter.oc = tagCallParameter.oc;
				//RetParameter.sn = tagCallParameter.sn;
				ObjectSystemT::GetInstance().GetEventQueue(tagCallParameter.su.c_str(), tagCallParameter.ss.c_str(), RetParameter);
				if (hTransport)
				{
					TransportMiniT::GetInstance().ClearSession(
						ObjectSystemT::GetInstance().ReBuildSession(
							hTransport,tagCallParameter.su.c_str(), tagCallParameter.ss.c_str())
					);
				}
			}
			RetParameter.Err = (unsigned int)Error;
			return bRet;
		}

		template<typename TransportMiniT,typename StringT>
		BOOL CallInterfaceStr(IN Transport::TransportHandle hHandle, StringT & szInPar, StringT & szOutPar, SYSTEMERROR & error)
		{
			//return LocalServerTansportT::GetInstance().CallInterface(szInPar, szOutPar);
			_tagCallParameter cp, rp;
			BOOL bRet = TRUE;
			SerTCHARXmlBufferToObject(_tagCallParameter, cp, (szInPar.c_str()));
			bRet = CallInterfacePar<TransportMiniT>(hHandle, cp,   rp, error);

			SerObjectToXmlBuffer(_tagCallParameter, rp, szOutPar);
			if(cp.oc == OBJECT_SYSTEM_OP_GETOBJECT) _DebugOutput1(_T("RetPar %s %s\n"), cp.op.c_str(), szOutPar.c_str());
			
			/*
			if (tagCallParameter.nOpCode == OBJECT_SYSTEM_OP_GETOBJECT)
			{
				_DebugOutput(_T("op=%d %s %s Data=%s \n\n"), tagCallParameter.nOpCode, tagCallParameter.ObjectPath.c_str(),
					 bRet ? _T("ok") : _T("fail"), szOutPar.c_str());
			}
			*/
			GCContainer<MemoryMgr__StaticGC_Tmp>::GetInstance().ReleaseGC(MEMGC_SERVER_LEVEL);
			return bRet;
			
		}
		
	private:

	};


};



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
		return ServerTransportT::GetInstance().CallInterfacePar<_Myt>(NULL, tagCallParameter, RetParameter, error);
	}

	BOOL CallInterfaceStr(tstring & szInPar, tstring & szOutPar, SYSTEMERROR & error)
	{
		return ServerTransportT::GetInstance().CallInterfaceStr<_Myt>(NULL, szInPar, szOutPar, error);
	}
	void ClearSession(Transport::TransportHandle hHandle)
	{
	}
	BOOL RecvAllMsg(BOOL bBlock = FALSE)
	{
		BOOL bRet = FALSE;
		return bRet;
	}
	BOOL RecvMsg(unsigned int nChannelNoOffset, tstring & szOutPar, BOOL bRecvNew = FALSE;)
	{
		BOOL bRet = FALSE;

		return bRet;
	}

private:

};


#undef _DebugOutput