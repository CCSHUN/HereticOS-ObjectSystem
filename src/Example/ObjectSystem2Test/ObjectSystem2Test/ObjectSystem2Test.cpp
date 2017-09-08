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

// ObjectSystem2Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define LAB(x)	x  
#define LAB1(x) #x
#define LAB2(x) LAB1(x)

#define KEEPALIVED_MODE	FALSE
#define HAS_FILE_SYSTEM



//#define KEEPALIVED_MODE	FALSE
/*
#define SEROBJ_HEAD(_name) "../../../other/ObjectSystem2/ObjectSystem_"##_name##".cpp"
#define T1(_name) LAB(p)LAB(_name)
#define SERHEAD(_path,_name) LAB2(LAB(../../../other/ObjectSystem2/ObjectSystem)LAB(_name)LAB(.cpp))
#define SEROBJ_HEAD1(_name) HEAD(_name)
*/

//#define ss #include "../../../other/ObjectSystem2/ObjectSystem_Local.cpp"

#include "../../../other/ObjectSystem2/ObjectSystem.h"
#include "../../../other/ObjectSystem2/TransportMiniUDP.h"
#include "../../../other/ObjectSystem2/ObjectSystem_Local.cpp"
#include "../../../other/ObjectSystem2/ObjectFileOperation.h"


#ifdef HAS_FILE_SYSTEM
typedef CObjectFileOperation_Nop FileSystem_T;
#else
typedef CObjectFileOperation FileSystem_T;
#endif 


class ObjectSystem2Config
{
public:
	ObjectSystem2Config() {};
	~ObjectSystem2Config() {};
	typedef ObjectSystem2Config _Myt;
	static _Myt & GetInstance()
	{
		static ObjectSystem2Config _self;
		return _self;
	}
	tstring strLocalSystemDirectory;
private:

};

#include <functional>

class Event;

map<tstring, Event, less<tstring>> g_EventMap;

class Event
{
public:
	Event() {};
	~Event() {};
	
	std::function<void(ObjectSystemEvent &)> LambdaFunction;
	Event(ObjectSystemEvent & RegEvent, std::function<void(ObjectSystemEvent &)>  Lambda) {
		LambdaFunction = Lambda;
		printf_t(_T("Lambda Size %d\n"), sizeof(Lambda));
		g_EventMap[RegEvent.szObjectAddress] = *this;
	};
	void SetEvent(ObjectSystemEvent & Event)
	{
		LambdaFunction(Event);
		tstring szObjectAddress = Event.szObjectAddress;
		Event.szObjectAddress += _T("_EventMap");
		g_EventMap[szObjectAddress].LambdaFunction(Event);
	}
private:

};



void TestEvent()
{
	ObjectSystemEvent reg;
	reg.szObjectAddress = _T("tesssssss");
	reg.nEventType = EventType::ObjectEvent_Get;
	tstring Str1 = _T("123");
	tstring Str2 = _T("456");

	Event e(reg, [Str1, Str2](ObjectSystemEvent & Event) {
		printf_t(_T("Event=(%s %d)  s1=%s s2=%s\n"), Event.szObjectAddress.c_str(), Event.nEventType, Str1.c_str(),Str2.c_str());
	});
	e.SetEvent(reg);
	printf_t(_T("=============TestEvent End============\n"));
}
void TestEvent2()
{
	ObjectSystemEvent reg;
	reg.szObjectAddress = _T("tesssssss");
	reg.nEventType = EventType::ObjectEvent_Get;
	g_EventMap[reg.szObjectAddress].SetEvent(reg);
	printf_t(_T("=============TestEvent2 End============\n"));
}
//CObjectSystem_Local<ObjectSystem2Config, CObjectFileOperation> g_localObjectSystem;
template<typename _ContainerT>
struct ObjectSystemContianer
{
	typedef _ContainerT ContainerT;
	typedef CObjectSystem_Local<ObjectSystem2Config, FileSystem_T, ContainerT, DefAuth> LocalObjectServerT;
	typedef Transport::Client<TransportMiniDirectCall<Transport::Server< LocalObjectServerT, ContainerT>>, ContainerT, false, false > 			LocalTransport1T;
	typedef Transport::Client<TransportMiniDirectCall<Transport::Server< LocalObjectServerT, ContainerT>>, ContainerT>				LocalTransport2T;
	typedef CObjectSystem_Client<LocalTransport1T, ContainerT> LocalClient1T;
	typedef CObjectSystem_Client<LocalTransport2T, ContainerT> LocalClient2T;

	//TransportMini
	//typename Transport::Server<LocalObjectServerT>
	typedef TransportMini::TransportMiniUDPServer<Transport::Server<LocalObjectServerT, ContainerT, false>, ContainerT, 8484, 'yssy'> UDPServerTransportT;
	typedef Transport::Client<TransportMini::TransportMiniUDPClient<ContainerT, 8484, 'yssy'>, ContainerT> UDPClientTransport1T;
	typedef Transport::Client<TransportMini::TransportMiniUDPClient<ContainerT, 8484, 'yssy'>, ContainerT > UDPClientTransport2T;
	typedef CObjectSystem_Client<UDPClientTransport1T, ContainerT> UDPClient1T;
	typedef CObjectSystem_Client<UDPClientTransport2T, ContainerT> UDPClient2T;
};


void BigString(tstring & szStr, int nLen)
{
	for (int i = 0; i < nLen; i++) szStr += ('a' + rand() % 25);
}
unsigned int g_nClient1Log = 0;
unsigned int g_nClient2Log = 0;

#define Object1Path _T("Test\\Object1")
#define Object2Path _T("Test\\Object2")


void ObjectSystemTestInit()
{
	tstring szSession;
	SYSTEMERROR error;
	//CObjectSystem_Local<ObjectSystem2Config, CObjectFileOperation>::GetInstance().LogonInSystem(tstring(_T("Test")), tstring(_T("123")), szSession);
	ObjectSystemContianer<Container_DefaultT>::LocalClient1T & LocalClient1 = ObjectSystemContianer<Container_DefaultT>::LocalClient1T::GetInstance();
	printf_t(_T("LocalClient1.LogonInSystem %s %d\n"),
	LocalClient1.LogonInSystem(tstring_tmp(_T("Test")), tstring_tmp(_T("123")), &error) ? _T("Ok") : _T("Fail"), error);

	ObjectSystemContianer<Container_DefaultT>::LocalClient2T & LocalClient2 = ObjectSystemContianer<Container_DefaultT>::LocalClient2T::GetInstance();
	printf_t(_T("LocalClient2.LogonInSystem %s %d\n"),
	LocalClient2.LogonInSystem(tstring_tmp(_T("Test")), tstring_tmp(_T("123")), &error) ? _T("Ok") : _T("Fail"), error);

	_tagObjectState state;
	tstring_tmp szState;
	state.szLockUser = _T("LocalClient1-init");
	SerObjectToXmlBuffer(_tagObjectState, state, szState);
	
	printf_t(_T("LocalClient1.UpDataObject %s %d\n"),
		LocalClient1.UpDataObject(tstring_tmp(Object1Path), szState, &error) ? _T("Ok") : _T("Fail"), error);


	state.szLockUser = _T("LocalClient2-init");
	SerObjectToXmlBuffer(_tagObjectState, state, szState);
	printf_t(_T("LocalClient1.UpDataObject %s %d\n"),
		LocalClient2.UpDataObject(tstring_tmp(Object2Path), szState, &error) ? _T("Ok") : _T("Fail"), error);

	ObjectSystemEvent  RegEvent;

	tstring szEventName = _T("Client1Event");

	RegEvent.nEventType = ObjectEvent_Updata;
	RegEvent.szObjectAddress = Object2Path;
	//Client1注册Object2更新事件
	ObjectSystemContianer<Container_DefaultT>::LocalClient1T::Event(RegEvent, [szEventName](ObjectSystemEvent & Event) {
		printf_t(_T("LocalClient1T Updata Event=(%s %d)  szEventName=%s\n"), Event.szObjectAddress.c_str(), Event.nEventType, szEventName.c_str());
		tstring szObject;
		_tagObjectState state;
		SYSTEMERROR error;
		BOOL bRet = ObjectSystemContianer<Container_DefaultT>::LocalClient1T::GetInstance().GetObject(Event.szObjectAddress, szObject, state, &error);
		if (bRet)
		{
			SerTCHARXmlBufferToObject(_tagObjectState, state, (szObject.c_str()));
		}
		printf_t(_T("LocalClient1.GetObject %s %s %d\n"), bRet ? _T("Ok") : _T("Fail"), state.szLockUser.c_str(), error);
		return bRet;

	});

	//Client2注册Object1更新事件
	szEventName = _T("Client2Event");
	RegEvent.szObjectAddress = Object1Path;
	ObjectSystemContianer<Container_DefaultT>::LocalClient2T::Event(RegEvent, [szEventName](ObjectSystemEvent & Event) {
		printf_t(_T("LocalClient2T Updata Event=(%s %d)  szEventName=%s\n"), Event.szObjectAddress.c_str(), Event.nEventType, szEventName.c_str());
		tstring szObject;
		_tagObjectState state;
		SYSTEMERROR error;
		BOOL bRet = ObjectSystemContianer<Container_DefaultT>::LocalClient2T::GetInstance().GetObject(Event.szObjectAddress, szObject, state, &error);
		if (bRet)
		{
			SerTCHARXmlBufferToObject(_tagObjectState, state, (szObject.c_str()));
		}
		printf_t(_T("LocalClient2.GetObject %s %s %d\n"), bRet ? _T("Ok") : _T("Fail"), state.szLockUser.c_str(), error);
		return bRet;
	});

	szEventName = _T("Client1Event");
	RegEvent.nEventType = ObjectEvent_NeedNew;
	RegEvent.szObjectAddress = Object1Path;
	//Client1注册Object1需求事件
	ObjectSystemContianer<Container_DefaultT>::LocalClient1T::Event(RegEvent, [szEventName](ObjectSystemEvent & Event) {
		printf_t(_T("LocalClient1T NeedNew Event=(%s %d)  szEventName=%s\n"), Event.szObjectAddress.c_str(), Event.nEventType, szEventName.c_str());

		_tagObjectState state;
		tstring_tmp szState;
		state.szLockUser = _T("LocalClient1-");
		state.szLockUser+=(tstring)CAutoVal(++g_nClient1Log);
		SerObjectToXmlBuffer(_tagObjectState, state, szState);
		SYSTEMERROR error;
		printf_t(_T("LocalClient1.UpDataObject %s %d\n"),
			ObjectSystemContianer<Container_DefaultT>::LocalClient1T::GetInstance().UpDataObject(tstring_tmp(Object1Path), szState, &error) ? _T("Ok") : _T("Fail"), error);

	});

	szEventName = _T("Client2Event");
	//Client2注册Object2需求事件
	RegEvent.szObjectAddress = Object2Path;
	ObjectSystemContianer<Container_DefaultT>::LocalClient2T::Event(RegEvent, [szEventName](ObjectSystemEvent & Event) {
		printf_t(_T("LocalClient2T NeedNew Event=(%s %d)  szEventName=%s\n"), Event.szObjectAddress.c_str(), Event.nEventType, szEventName.c_str());

		_tagObjectState state;
		tstring_tmp szState;
		state.szLockUser = _T("LocalClient2-");
		state.szLockUser += (tstring)CAutoVal(++g_nClient2Log);
		SerObjectToXmlBuffer(_tagObjectState, state, szState);
		SYSTEMERROR error;
		printf_t(_T("LocalClient2.UpDataObject %s %d\n"),
			ObjectSystemContianer<Container_DefaultT>::LocalClient2T::GetInstance().UpDataObject(tstring_tmp(Object2Path), szState, &error) ? _T("Ok") : _T("Fail"), error);
	});


}


template<typename Client1T,typename Client2T>
void ObjectSystemTestMiniInit()
{
	tstring szSession;
	SYSTEMERROR error= Error_No;
	//CObjectSystem_Local<ObjectSystem2Config, CObjectFileOperation>::GetInstance().LogonInSystem(tstring(_T("Test")), tstring(_T("123")), szSession);
	Client1T & Client1 = Client1T::GetInstance();
	printf_t(_T("Client1.LogonInSystem %s %d\n"),
		Client1.LogonInSystem(tstring(_T("Test")), tstring(_T("123")), &error) ? _T("Ok") : _T("Fail"), error);

	Client2T & Client2 = Client2T::GetInstance();
	printf_t(_T("Client2.LogonInSystem %s %d\n"),
		Client2.LogonInSystem(tstring(_T("Test")), tstring(_T("123")), &error) ? _T("Ok") : _T("Fail"), error);

	_tagObjectState_Wrap<Client1T> state1(Object1Path);
	state1.szLockUser = _T("Client1-init");

	printf_t(_T("Client1.UpDataObject %s %d\n"),
		state1.UpDataObject() ? _T("Ok") : _T("Fail"), error);


	_tagObjectState_Wrap<Client2T> state2(Object2Path);
	state1.szLockUser = _T("Client2-init");
	printf_t(_T("Client2.UpDataObject %s %d\n"),
		state2.UpDataObject() ? _T("Ok") : _T("Fail"), error);


	tstring szEventName = _T("Client1Event-Updata");
	//Client1注册Object2更新事件
	
	

	_tagObjectState_Wrap<Client1T>(Object2Path, ObjectEvent_Updata,[szEventName](ObjectSystemEvent & Event) {
		printf_t(_T("Object2 Updata Client1 Event=(%s %d)  szEventName=%s\n"), Event.szObjectAddress.c_str(), Event.nEventType, szEventName.c_str());
		_tagObjectState_Wrap<Client1T> state_wrap1(Event.szObjectAddress);
		BOOL bRet = state_wrap1.GetObject();
		
		if (state_wrap1.szLockUser.length() > 128)
		{
			printf_t(_T("Client1.GetObject Object2 %s BigString(%d) %d\n"), bRet ? _T("Ok") : _T("Fail"), state_wrap1.szLockUser.length(), state_wrap1.m_nCurError);
		}
		else
		{
			printf_t(_T("Client1.GetObject Object2 %s %s %d\n"), bRet ? _T("Ok") : _T("Fail"), state_wrap1.szLockUser.c_str(), state_wrap1.m_nCurError);
		}
		//return bRet;

	});

	//Client2注册Object1更新事件
	szEventName = _T("Client2Event-Updata");
	_tagObjectState_Wrap<Client2T>(Object1Path, ObjectEvent_Updata, [szEventName](ObjectSystemEvent & Event) {
		printf_t(_T("Object1 Updata Client2 Event=(%s %d)  szEventName=%s\n"), Event.szObjectAddress.c_str(), Event.nEventType, szEventName.c_str());
		_tagObjectState_Wrap<Client2T> state_wrap2(Event.szObjectAddress);
		//_tagObjectState tmp;
		BOOL bRet = state_wrap2.GetObject();

		if (state_wrap2.szLockUser.length() > 128)
		{
			printf_t(_T("Client2.GetObject Object1 %s BigString(%d) %d\n"), bRet ? _T("Ok") : _T("Fail"), state_wrap2.szLockUser.length(), state_wrap2.m_nCurError);
		}
		else
		{
			printf_t(_T("Client2.GetObject Object1 %s %s %d\n"), bRet ? _T("Ok") : _T("Fail"), state_wrap2.szLockUser.c_str(), state_wrap2.m_nCurError);
		}
		
		return bRet;
	});

	szEventName = _T("Client1Event-NeedNew");
	//Client1注册Object1需求事件
	_tagObjectState_Wrap<Client1T>(Object1Path, ObjectEvent_NeedNew, [szEventName](ObjectSystemEvent & Event) {
		printf_t(_T("Client1 NeedNew Object1 Event=(%s %d)  szEventName=%s\n"), Event.szObjectAddress.c_str(), Event.nEventType, szEventName.c_str());

		_tagObjectState_Wrap<Client1T> state_wrap1(Event.szObjectAddress); 
		state_wrap1.szLockUser = _T("Client1-");
		state_wrap1.szLockUser += (tstring)CAutoVal(g_nClient1Log);
		g_nClient1Log++;
		printf_t(_T("Client1.UpDataObject Object1 %s %d\n"),
			state_wrap1.UpDataObject() ? _T("Ok") : _T("Fail"), state_wrap1.m_nCurError);

	});

	szEventName = _T("Client2Event-NeedNew");
	//Client2注册Object2需求事件
	_tagObjectState_Wrap<Client2T>(Object2Path, ObjectEvent_NeedNew, [szEventName](ObjectSystemEvent & Event) {
		printf_t(_T("Client2 NeedNew Object2 Event=(%s %d)  szEventName=%s\n"), Event.szObjectAddress.c_str(), Event.nEventType, szEventName.c_str());
		_tagObjectState_Wrap<Client2T> state_wrap2(Event.szObjectAddress);
		state_wrap2.szLockUser = _T("Client2-");
		state_wrap2.szLockUser += (tstring)CAutoVal(g_nClient2Log);
		BigString(state_wrap2.szLockUser, 200 * 1024);
		g_nClient2Log++;
		printf_t(_T("Client2.UpDataObject Object2 %s %d\n"),
			state_wrap2.UpDataObject() ? _T("Ok") : _T("Fail"), state_wrap2.m_nCurError);
	});


}
template<typename ClientT>
void ClientNeed(TCHAR * pClientName, TCHAR * pObjectPath,int nCount)
{
	SYSTEMERROR error=Error_No;
	//printf("(%s)", typeid(ClientT).name());
	printf_t(_T("(%s-%d)"), pClientName, nCount);
	printf_t(_T("NeedNewObject %s %s err=%d\n"),
		pObjectPath, ClientT::GetInstance().NeedNewObject(tstring(pObjectPath), &error) ? _T("Ok") : _T("Fail"), error);
}
void ObjectSystemTest()
{
	//ObjectSystemTestInit();
	ObjectSystemTestMiniInit<ObjectSystemContianer<Container_DefaultT>::LocalClient1T, ObjectSystemContianer<Container_DefaultT>::LocalClient2T>();
	for (int i=0;;i++)
	{
		Sleep(1000);
		ObjectSystemContianer<Container_DefaultT>::LocalTransport1T::GetInstance().Loop(KEEPALIVED_MODE);
		Sleep(1000);
		ClientNeed<ObjectSystemContianer<Container_DefaultT>::LocalClient1T>(_T("LocalClient1T"),Object1Path,i);
		Sleep(1000);
		ClientNeed<ObjectSystemContianer<Container_DefaultT>::LocalClient2T>(_T("LocalClient2T"), Object2Path,i);
	}
}
template<typename ObjectContainerT>
void UDPObjectSystemTest(BOOL bHasSever=TRUE)
{
	//ObjectSystemTestInit();
	BOOL bOk = TRUE;
	if (bHasSever)
	{
		bOk = ObjectContainerT::UDPServerTransportT::GetInstance().init();
	}
	if(bOk)
	{
		if (ObjectContainerT::UDPClientTransport1T::TransportMiniT::GetInstance().init()&& ObjectContainerT::UDPClientTransport2T::TransportMiniT::GetInstance().init())
		{
			ObjectSystemTestMiniInit<ObjectContainerT::UDPClient1T, ObjectContainerT::UDPClient2T>();
			for (int i = 0;; i++)
			{
				Sleep(1000);
				ObjectContainerT::UDPClientTransport1T::GetInstance().Loop(KEEPALIVED_MODE);
				ObjectContainerT::UDPClientTransport2T::GetInstance().Loop(KEEPALIVED_MODE);
				Sleep(1000);
				ClientNeed<ObjectContainerT::UDPClient1T>(_T("LocalClient1T"), Object1Path, i);
				Sleep(1000);
				ClientNeed<ObjectContainerT::UDPClient2T>(_T("LocalClient2T"), Object2Path, i);
			}
			
		}
		printf_t(_T("UDPClientTransport1T init fail...\n"));
		
	}
	else
	{
		printf_t(_T("UDPServerTransportT init fail...\n"));
	}
	
	
}
void TestZip()
{
	string szData = "1234";
	string szOutData;
	vector<u_char> OutData;
	CBase64Zip::Base64ZipCompress((unsigned char *)szData.c_str(), szData.length() * sizeof(TCHAR), szOutData);
	CBase64Zip::Base64ZipUnCompress(szOutData, OutData);
}

template<typename ObjectSystemContainerT,typename ClientT,bool bTestSer=false>
void TestPerformance(int nCount=1,int nContainerCount=1)
{
	tstring szObjectPathBase = _T("Test\\Object");
	
	SYSTEMERROR error=Error_No;
	//ClientT & Client1 = ClientT::GetInstance();
	
	//TestZip();
	_tagObjectState_Wrap<ClientT> state_wrap(Object1Path);
	tstring szState;
	tstring ssAddr = Object1Path;
	_tagObjectState state, state1;
	state.szLockUser = _T("Client1-init");
	SerObjectToXmlBuffer(_tagObjectState, state, szState);
	state_wrap.szLockUser = _T("Client1-init");
	__int64 nSucessCount, nLastSucessCount, nErrorCount, nUsedTime, nLastUsedTime, nTempTime, nTempErrTime, nErrorUsedTime, nLastTick, nLastErrorTick;
	nLastErrorTick = nTempTime = nTempErrTime = nLastSucessCount = nLastUsedTime = nUsedTime = nLastTick = nErrorUsedTime = nSucessCount = nErrorCount = 0;
	int nIndex = 0;
	int nBeginContainer = 0;
	for(int j=1;j<nContainerCount;j++) nBeginContainer= ObjectSystemContainerT::ContainerT::SystemContainerMgrT::GetInstance().CreateContainer();

	nBeginContainer -= (nContainerCount-1);

	printf_t(_T("Client1.LogonInSystem %s %d\n"),
		ClientT::GetInstance().LogonInSystem(tstring(_T("Test")), tstring(_T("123")), &error) ? _T("Ok") : _T("Fail"), error);

	for (int nCurrentContainer = nBeginContainer,s=0;; )
	{
		
		nLastTick = ::GetTickCount64();
		nLastSucessCount = nSucessCount;
		for (int i = 0; i < 1000; i++)
		{
			nLastErrorTick = ::GetTickCount64();
			nTempErrTime = 0;
			/**/
			if (bTestSer)
			{
				//_tagCallParameterV2 Par,RetPar;
				_tagCallParameter Par, RetPar;
				Par.ob = szState;
				tstring_tmp szPar,OutPar;
				//SerObjectToXmlBuffer(_tagObjectState, state, szState);
				SerObjectToXmlBuffer(_tagCallParameter, Par, szPar);
				//OutPar = szPar;
				//SerTCHARXmlBufferToObject(_tagCallParameter, RetPar, (OutPar.c_str()));
				GCContainer<MemoryMgr__StaticGC_Tmp>::GetInstance().ReleaseGC(MEMGC_CLIENT_LEVEL);
				nSucessCount++;
			}
			else
			{
				if(nCount!=1)state_wrap.m_szAddr = szObjectPathBase + (tstring&)CAutoVal(nIndex%nCount);
				//if (state_wrap.UpDataObject())
				if(ClientT::GetInstance().UpDataObject(state_wrap.m_szAddr, szState, &error))
				{
					nSucessCount++;
					/*
					if (state_wrap.GetObject(state1))
					{
						if (state_wrap.szLockUser == state1.szLockUser)
						{
							nSucessCount++;
						}
					}
					*/
				}
				else
				{
					nErrorCount++;
					nErrorUsedTime += ::GetTickCount64() - nLastErrorTick;
					nTempErrTime += ::GetTickCount64() - nLastErrorTick;
				}
			}
			nIndex++;
		}
		nTempTime = ::GetTickCount64() - nLastTick;
		nUsedTime += nTempTime;
		//MemoryMgr__StaticGC_Tmp::GetInstance().DelGc(FALSE);
		//MemoryMgr__StaticGC::GetInstance().DelGc(FALSE);
		if (nUsedTime - nLastUsedTime > 3000)
		{
			

			printf_t(_T("Container-%d QPS(数量=%llu 用时=%llu 速率=%llu)  瞬时QPS(数量=%llu 用时=%llu 速率=%llu) Error(数量=%llu 用时=%llu 速率=%llu)\n"),
				nCurrentContainer,nSucessCount, nUsedTime - nErrorUsedTime, ((1000*nSucessCount) / (nUsedTime - nErrorUsedTime)),
				nSucessCount - nLastSucessCount, (nTempTime - nTempErrTime), ((1000*(nSucessCount - nLastSucessCount)) / (nTempTime - nTempErrTime)),
				nErrorCount, nErrorUsedTime, (1000*nErrorCount) / (nErrorUsedTime? nErrorUsedTime:(nErrorUsedTime+1)));
			
			nLastUsedTime = nUsedTime;
			
			nCurrentContainer = nBeginContainer + (s % nContainerCount);
			ObjectSystemContainerT::ContainerT::SystemContainerMgrT::GetInstance().SwitchContainer(nCurrentContainer);
			//printf_t(_T("Entry Container-%d\n"), nCurrentContainer);

			s++;
			
		}
		
	}

}
#include "RotationalFlowers.h"
int InputTestObjectCount()
{
	int nRet = 0;
	printf_t(_T("请输入样本数量:\n"));
	scanf_t(_T("%u"), &nRet);
	return nRet;
}

int InputTestContainerCount()
{
	int nRet = 0;
	printf_t(_T("请输入容器数量:\n"));
	scanf_t(_T("%u"), &nRet);
	return nRet;
}

int _tmain(int argc, _TCHAR* argv[])
{
	BOOL bMatch = FALSE;
	if (argc > 1)
	{
		
		if (argv[1] == tstring(_T("-s")))
		{
			printf_t(_T("Server mode entry...\n"));
			ObjectSystemContianer<Container_DefaultT>::UDPServerTransportT::GetInstance().init();
			for (;;)
			{
				Sleep(3000);
				printf_t(_T("===========================================================\n"));
				printf_t(MemoryMgr_FreeList1T::GetInstance().PrintMemPoolInfo(_T("MemoryMgr_FreeList1T")));
				//printf_t(MemoryMgr__StaticGC::GetInstance().PrintMemPoolInfo(_T("MemoryMgr__StaticGC")));
				printf_t(MemoryMgr__StaticGC_Tmp::GetInstance().PrintMemPoolInfo(_T("MemoryMgr__StaticGC_Tmp")));
				printf_t(_T("===========================================================\n\n\n"));
			}
			bMatch = TRUE;
		}
		else if (argv[1] == tstring(_T("-c")))
		{
			printf_t(_T("Client mode entry...\n"));
			UDPObjectSystemTest<ObjectSystemContianer<Container_DefaultT>>(FALSE);
			bMatch = TRUE;
		}
		else if (argv[1] == tstring(_T("-gcu")))
		{
			printf_t(_T("Game User mode entry...\n"));
			GameEntry();
			bMatch = TRUE;
		}
		else if (argv[1] == tstring(_T("-gcm")))
		{
			printf_t(_T("Game Master mode entry...\n"));
			GameEntry(TRUE);
			bMatch = TRUE;
		}
		else if (argv[1] == tstring(_T("-gs")))
		{
			printf_t(_T("Game Server mode entry...\n"));
			GameServerEntry();
			bMatch = TRUE;
		}
		else if (argv[1] == tstring(_T("-tu")))
		{
			if (ObjectSystemContianer<Container_DefaultT>::UDPClientTransport1T::TransportMiniT::GetInstance().init())
			{
				TestPerformance<ObjectSystemContianer<Container_DefaultT>, ObjectSystemContianer<Container_DefaultT>::UDPClient1T>(InputTestObjectCount(), InputTestContainerCount());
			}
			
			bMatch = TRUE;
		}
		else if (argv[1] == tstring(_T("-tl1")))
		{
			TestPerformance<ObjectSystemContianer<Container_DefaultT>, ObjectSystemContianer<Container_DefaultT>::LocalClient1T>(InputTestObjectCount(), InputTestContainerCount());
			bMatch = TRUE;
		}
		else if (argv[1] == tstring(_T("-tl2")))
		{
			TestPerformance<ObjectSystemContianer<Container_DefaultT>, ObjectSystemContianer<Container_DefaultT>::LocalClient2T>(InputTestObjectCount(), InputTestContainerCount());
			bMatch = TRUE;
		}
		else if (argv[1] == tstring(_T("-tls")))
		{
			TestPerformance<ObjectSystemContianer<Container_DefaultT>,ObjectSystemContianer<Container_DefaultT>::LocalClient1T,true>(InputTestObjectCount(), InputTestContainerCount());
			bMatch = TRUE;
		}
		
	}
	if (!bMatch)
	{
		UDPObjectSystemTest<ObjectSystemContianer<Container_DefaultT>>();
	}
	//ObjectSystemTest();
	for (;;)
	{
		::Sleep(100);
	}
	//tstring szSession;
	//CObjectSystem_Local<ObjectSystem2Config, CObjectFileOperation>::GetInstance().LogonInSystem((_T("Test")), (_T("123")), szSession);
	ObjectSystemContianer<Container_DefaultT>::LocalClient1T & LocalClient = ObjectSystemContianer<Container_DefaultT>::LocalClient1T::GetInstance();
	return 0;
}

/*
int main()
{
	//printf_t(_T("p_Local %s"), T1(_Local));
	//TestEvent();
	//TestEvent2();
	UDPObjectSystemTest();
	//ObjectSystemTest();
	for (;;)
	{
		::Sleep(100);
	}
	tstring szSession;
	CObjectSystem_Local<ObjectSystem2Config, CObjectFileOperation>::GetInstance().LogonInSystem(tstring(_T("Test")), tstring(_T("123") ), szSession);
	LocalClient1T & LocalClient= LocalClient1T::GetInstance();
	
    return 0;
}

*/