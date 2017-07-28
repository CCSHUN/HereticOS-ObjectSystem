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

template<typename ValType, typename SerType, typename ObjectSystemClientT>
class ObjectTypeWrap;

#define MAKESTRUCTINFO(ObjectType)  TO_NET_OBJECT_TYPE(ObjectType) 
// 声明一个对象

//#define TO_NET_OBJECT_TYPE(ObjectType) \
//	typedef ObjectTypeWrap<ObjectType,Serialize_##ObjectType> ObjectType##_Wrap; \

#define TO_NET_OBJECT_TYPE(ObjectType) \
template<class _Client > \
using ObjectType##_Wrap = ObjectTypeWrap<ObjectType,Serialize_##ObjectType,_Client>; \






#include "TransportProtocol.h"
#include <functional>




template<typename ValType, typename SerType, typename ObjectSystemClientT>
class ObjectTypeWrap : public ValType
{
public:
	//ValType		m_Data;
	tstring		m_szAddr;
	tstring		m_szFinder;
	ObjectSystem::_tagObjectState m_ObjectState;

	ObjectSystem::SYSTEMERROR m_nCurError;

	ObjectTypeWrap()
	{
		m_ObjectState.bLock = FALSE;
		m_ObjectState.nLockTime = 0;
		m_ObjectState.nType = Nonmoral;
		m_ObjectState.szLockUser = _T("");
	}
	ObjectTypeWrap(tstring & szAddr)
	{
		m_ObjectState.bLock = FALSE;
		m_ObjectState.nLockTime = 0;
		m_ObjectState.nType = Nonmoral;
		m_ObjectState.szLockUser = _T("");
		m_szAddr = szAddr;
	}
	ObjectTypeWrap(TCHAR * szAddr)
	{
		m_ObjectState.bLock = FALSE;
		m_ObjectState.nLockTime = 0;
		m_ObjectState.nType = Nonmoral;
		m_ObjectState.szLockUser = _T("");
		m_szAddr = szAddr;
	}
	template<typename AddrStringT>
	ObjectTypeWrap(AddrStringT & szAddr,unsigned int nEventType, std::function<void(ObjectSystemEvent &)>  Lambda)
	{
		m_ObjectState.bLock = FALSE;
		m_ObjectState.nLockTime = 0;
		m_ObjectState.nType = Nonmoral;
		m_ObjectState.szLockUser = _T("");
		m_szAddr = szAddr;
		typename ObjectSystemClientT::Event(szAddr,nEventType, Lambda);
	}

	virtual ~ObjectTypeWrap() {};

	BOOL GetObject()
	{
		tstring Object;
		BOOL bRet = ObjectSystemClientT::GetInstance().GetObject(m_szAddr, Object, m_ObjectState, &m_nCurError);
		if (bRet)
		{
			ValType & Data = *static_cast<ValType*>(this);
			SerTCHARXmlBufferToObjectEx(ValType, SerType, Data, (Object.c_str()));
		}
		return bRet;

	}
	BOOL GetObject(ValType & RetObject)
	{
		tstring Object;
		BOOL bRet = ObjectSystemClientT::GetInstance().GetObject(m_szAddr, Object, m_ObjectState, &m_nCurError);
		if (bRet)
		{
			SerTCHARXmlBufferToObjectEx(ValType, SerType, RetObject, (Object.c_str()));
		}
		return bRet;

	}
	BOOL NeedNewObject()
	{
		return ObjectSystemClientT::GetInstance().NeedNewObject(m_szAddr, &m_nCurError);

	}
	BOOL UpDataObject(ValType & InObject)
	{
		tstring Object;
		SerObjectToXmlBufferEx(ValType, SerType, InObject, Object);
		return ObjectSystemClientT::GetInstance().UpDataObject(m_szAddr, Object, &m_nCurError);
	}

	BOOL UpDataObject()
	{
		tstring Object;
		ValType & Data = *static_cast<ValType*>(this);
		SerObjectToXmlBufferEx(ValType, SerType, Data, Object);
		return ObjectSystemClientT::GetInstance().UpDataObject(m_szAddr, Object, &m_nCurError);
	}


	BOOL GetDirectoryInfo(ObjectSystem::_tagDirectoryInfo & DirectoryInfo)
	{
		return ObjectSystemClientT::GetInstance().GetDirectoryInfo(m_szAddr, m_szFinder, DirectoryInfo, &m_nCurError);
	}


	BOOL DeleteObject()
	{
		return ObjectSystemClientT::GetInstance().DeleteObject(m_szAddr, &m_nCurError);
	}

};

//#include "stdafx.h"

/*
enum LockType
{
Nonmoral=1,					//默认方式
AutoProlong=2,				//到期自动延迟锁，除非用户端应用停止响应
};
*/


//定义SOAP 命令

#define OBJECT_SYSTEM_OP_GETOBJECT			1				//_T("GOB")
#define OBJECT_SYSTEM_OP_UPDATAOBJECT		2				//_T("UOB")
#define OBJECT_SYSTEM_OP_DELETEOBJECT		3				//_T("DOB")
#define OBJECT_SYSTEM_OP_GETDIRECTORYINFO	4				//_T("GDINFO")
#define OBJECT_SYSTEM_OP_LOGONINSYSTEM		5				//_T("LIS")
#define OBJECT_SYSTEM_OP_LOGONOUTSYSTEM		6				//_T("LOS")
#define OBJECT_SYSTEM_OP_GETOBJECTSTATE		7				//_T("GOBS")
#define OBJECT_SYSTEM_OP_UPDATAOBJECTSTATE	8				//_T("UOBS")
#define OBJECT_SYSTEM_OP_GETCURTIME			9				//_T("GTM")
#define OBJECT_SYSTEM_OP_RELEASEOBJSTATE			10				//_T("ROS")
#define OBJECT_SYSTEM_OP_REGIST_OBJEVENT			11				//_T("ROE")
#define OBJECT_SYSTEM_OP_NEED_NEWOBJECT			12				//_T("NNO")
#define OBJECT_SYSTEM_OP_KEEPALIVED			13				//_T("NNO")

static TCHAR * Object_OPTab[]=
{
	_T(""),_T("GetObject"),_T("UpdataObject"),_T("DeleteObject"),
	_T("GetDirectoryInfo"),_T("LogonIn"),_T("LogonOut"),_T("GetObjectState"),
	_T("UpdataObjectState"),_T("GetCurTime"),_T("ReleaseObjectState"),_T("RegistObjectEvent"),_T("NeedNewObject"),_T(""),
};

namespace ObjectSystem
{
	

}

class CObjectSystemInterface
{
public:
	

	CObjectSystemInterface(){};
	~CObjectSystemInterface(){};

	//////////////////////////////////////////对象基本操作///////////////////////////////////////

	//创建对象 可以是目录对象或者是文件对象
	virtual BOOL CreateObject(IN tstring & ObjectPath, ObjectSystem::DirectoryObjectType &ObjectType)
	{
		return TRUE;
	}
	//ObjectPath	对象地址
	//Object		返回的XML对象
	//ObjectState	输入申请该对象的锁定时间 0申请为不锁，返回该对象的锁定信息，如果对象已经被其他用户锁定，则返回其他用户的锁信息
	virtual BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError)
	{
		return TRUE;
	}

	virtual BOOL NeedNewObject(IN tstring & ObjectPath, OUT ObjectSystem::SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//更新对象到存储
	virtual BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,OUT ObjectSystem::SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//更新对象到存储
	virtual BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,IN ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//获取目录信息
	virtual BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT ObjectSystem::_tagDirectoryInfo & DirectoryInfo,OUT ObjectSystem::SYSTEMERROR * pError)
	{
		return TRUE;
	}

	
	//删除对象
	virtual BOOL DeleteObject(IN tstring & ObjectOrDir, ObjectSystem::SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//释放目录状态
	virtual BOOL ReleaseObjectState(IN tstring & ObjectOrDir,OUT ObjectSystem::SYSTEMERROR * pError)
	{
		return TRUE;
	}


	//////////////////////////////////////////对象系统登陆登出///////////////////////////////////////
	//登陆对象存储系统
	virtual BOOL LogonInSystem(IN tstring & szUserName,IN tstring & szPassword, OUT tstring & szSession)
	{
		return TRUE;
	}

	//登出
	virtual BOOL LogonOutSystem()
	{
		return TRUE;
	}

	//////////////////////////////////////////对象锁操作///////////////////////////////////////

	//更新对象锁信息
	virtual BOOL UpDataObjectState(IN tstring & ObjectPath,OUT ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//获取对象锁信息
	virtual BOOL GetObjectState(IN tstring & ObjectPath,OUT ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError)
	{
		return TRUE;
	}

	virtual BOOL GetCurTime(SYSTEMTIME *  npTime,SYSTEMTIME * nCurTime)
	{
		return TRUE;
	}

	
	////////////////////////////////////////对象事物////////////////////////////////////////////////
	/*
	class ObjectEventProcessInterface
	{
	public: 
		ObjectEventProcessInterface(){};
		~ObjectEventProcessInterface(){};
		

		virtual BOOL ObjectEventProcess(IN tstring & ObjectPath,IN ObjectSystem::EventType & nEvent)
		{
			return TRUE;
		}
	};


	*/
	//Client 使用的消息接口
	virtual void ObjectEventCallBack(ObjectSystemEvent & Event)
	{
		return;
	}
	
	//Client KeepAlived
	virtual BOOL KeepAlived()
	{
		return FALSE;
	}

	//Server 使用的消息接口
	virtual BOOL BroadcastObjectEvent(IN tstring & szUser,IN tstring & szSession, IN ObjectSystem::ObjectSystemEvent & nEvent, OUT ObjectSystem::SYSTEMERROR * pError)
	{
		return TRUE;
	}
	virtual BOOL RegistObjectEvent(IN tstring & szUser, IN tstring & szSession, IN ObjectSystemEvent & RegEvent, OUT ObjectSystem::SYSTEMERROR * pError)
	{
		return TRUE;
	}
protected:

private:
};




template<typename TransportT,int nName=1>
class CObjectSystem_Client :public CObjectSystemInterface
{
public:
	_tagKeepAlivedPar m_KeepAlived;
	CObjectSystem_Client(void)
	{
		m_szUserName = _T("");
		m_szConversation = _T("");
		m_KeepAlived.nCyc = 0;
	}

	~CObjectSystem_Client(void)
	{
	}

	typedef CObjectSystem_Client<TransportT, nName> _MyClientT;
	static _MyClientT & GetInstance()
	{
		static _MyClientT _slef;
		return _slef;
	}
	BOOL  GetCurTime(SYSTEMTIME * npTime, SYSTEMTIME * nCurTime)
	{

		_tagCallParameter Par, RetPar, Par1, RetPar2;
		tstring szTime;
		CBase64Zip::Base64ZipCompress((unsigned char *)npTime, sizeof(SYSTEMTIME), szTime);
		_tagstrParameter Var;
		Var.szData = szTime;
		Par.strPar[_T("npTime")] = Var;
		CBase64Zip::Base64ZipCompress((unsigned char *)nCurTime, sizeof(SYSTEMTIME), szTime);
		Var.szData = szTime;
		Par.strPar[_T("nCurTime")] = Var;

		tstring szCallParameter;
		Par1 = Par;

		BOOL bRet = TransportT::GetInstance().CallInterface(m_szUserName, m_szConversation, OBJECT_SYSTEM_OP_GETCURTIME, Par, RetPar);


		if (bRet)
		{
			vector<unsigned char> var;
			if (CBase64Zip::Base64ZipUnCompress(RetPar.strPar[_T("nCurTime")].szData, var))
			{
				*nCurTime = *(SYSTEMTIME *)&var[0];
			}
			return RetPar.bCallSuccess;
		}
		return FALSE;
	}

	BOOL LogonInSystem(IN tstring & szUserName, IN tstring & szPassword,OUT SYSTEMERROR * pError)
	{
		m_szUserName = szUserName;
		m_szConversation = szPassword;
		_tagCallParameter Par, RetPar;
		Par.szPassword = szPassword;
		BOOL bRet = TransportT::GetInstance().CallInterface(m_szUserName, m_szConversation, OBJECT_SYSTEM_OP_LOGONINSYSTEM, Par, RetPar);
		if (bRet)
		{
			m_szConversation = RetPar.szSession;
			TransportT::GetInstance().RegistClient(m_szConversation, this);
			return RetPar.bCallSuccess;
		}
		return FALSE;
	}

	BOOL ReleaseObjectState(IN tstring & ObjectOrDir, OUT SYSTEMERROR * pError)
	{

		_tagCallParameter Par, RetPar;
		Par.ObjectPath = ObjectOrDir;
		BOOL bRet = TransportT::GetInstance().CallInterface(m_szUserName, m_szConversation, OBJECT_SYSTEM_OP_RELEASEOBJSTATE, Par, RetPar);
		if (bRet)
		{
			*pError = (SYSTEMERROR)RetPar.nError;

			return RetPar.bCallSuccess;
		}
		return FALSE;
	}

	BOOL LogonOutSystem()
	{
		_tagCallParameter Par, RetPar;
		BOOL bRet = TransportT::GetInstance().CallInterface(m_szUserName, m_szConversation, OBJECT_SYSTEM_OP_LOGONOUTSYSTEM, Par, RetPar);
		if (bRet)
		{
			return RetPar.bCallSuccess;
		}
		return FALSE;
	}
	
	BOOL KeepAlived()
	{
		_tagCallParameter Par, RetPar;
		BOOL bRet = TransportT::GetInstance().CallInterface(m_szUserName, m_szConversation, OBJECT_SYSTEM_OP_KEEPALIVED, Par, RetPar);
		if (bRet)
		{
			map<tstring, _tagstrParameter, less<tstring> >::iterator itPar = RetPar.strPar.find(_T("kpalv"));
			if (itPar!= RetPar.strPar.end())
			{
				SerTCHARXmlBufferToObject(_tagKeepAlivedPar, m_KeepAlived, (itPar->second.szData.c_str()));
			}
			return RetPar.bCallSuccess;
		}
		return FALSE;
	}

	BOOL GetObject(IN tstring & ObjectPath, OUT tstring & Object, IN OUT _tagObjectState & ObjectState, OUT SYSTEMERROR * pError)
	{
		_tagCallParameter Par, RetPar;
		Par.ObjectPath = ObjectPath;
		Par.tagObjectState.bLock = ObjectState.bLock;
		Par.tagObjectState.nType = (unsigned int)ObjectState.nType;
		Par.tagObjectState.nLockTime = ObjectState.nLockTime;
		Par.tagObjectState.szLockUser = ObjectState.szLockUser;
		BOOL bRet = TransportT::GetInstance().CallInterface(m_szUserName, m_szConversation, OBJECT_SYSTEM_OP_GETOBJECT, Par, RetPar);
		if (bRet)
		{
			*pError = (SYSTEMERROR)RetPar.nError;
			ObjectState.bLock = RetPar.tagObjectState.bLock;
			ObjectState.nLockTime = RetPar.tagObjectState.nLockTime;
			ObjectState.nType = (LockType)RetPar.tagObjectState.nType;
			ObjectState.szLockUser = RetPar.tagObjectState.szLockUser;

			if (RetPar.bCallSuccess)
			{
				Object = RetPar.Object;
			}
			return RetPar.bCallSuccess;
		}
		return FALSE;
	}

	BOOL NeedNewObject(IN tstring & ObjectPath, OUT ObjectSystem::SYSTEMERROR * pError)
	{
		_tagCallParameter Par, RetPar;
		Par.ObjectPath = ObjectPath;
		Par.tagObjectState.bLock = FALSE;
		Par.tagObjectState.nType = Nonmoral;
		Par.tagObjectState.nLockTime = 0;
		Par.tagObjectState.szLockUser = m_szUserName;
		BOOL bRet = TransportT::GetInstance().CallInterface(m_szUserName, m_szConversation, OBJECT_SYSTEM_OP_NEED_NEWOBJECT, Par, RetPar);
		if (bRet)
		{
			*pError = (SYSTEMERROR)RetPar.nError;
			
			return RetPar.bCallSuccess;
		}
		return FALSE;
	}


	//更新对象到存储
	BOOL UpDataObject(IN tstring & ObjectPath, IN tstring & Object, SYSTEMERROR * pError)
	{
		_tagCallParameter Par, RetPar;
		Par.ObjectPath = ObjectPath;
		Par.Object = Object;
		BOOL bRet = TransportT::GetInstance().CallInterface(m_szUserName, m_szConversation, OBJECT_SYSTEM_OP_UPDATAOBJECT, Par, RetPar);
		if (bRet)
		{
			*pError = (SYSTEMERROR)RetPar.nError;
			return RetPar.bCallSuccess;
		}
		return FALSE;
	}


	//获取目录信息
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath, IN tstring & szFinder, OUT _tagDirectoryInfo & DirectoryInfo, OUT SYSTEMERROR * pError)
	{
		_tagCallParameter Par, RetPar;
		Par.ObjectPath = DirectoryPath;
		Par.szFinder = szFinder;
		BOOL bRet = TransportT::GetInstance().CallInterface(m_szUserName, m_szConversation, OBJECT_SYSTEM_OP_GETDIRECTORYINFO, Par, RetPar);
		if (bRet)
		{
			*pError = (SYSTEMERROR)RetPar.nError;
			_tagDirectoryInfoSet set;
			DirectoryInfo.DirectoryInfoArray.resize(RetPar.DirectoryInfo.DirectoryInfoArray.size());
			for (unsigned int i = 0; i<DirectoryInfo.DirectoryInfoArray.size(); i++)
			{
				DirectoryInfo.DirectoryInfoArray[i].ObjectName = RetPar.DirectoryInfo.DirectoryInfoArray[i].ObjectName;
				DirectoryInfo.DirectoryInfoArray[i].ObjectType = (DirectoryObjectType)RetPar.DirectoryInfo.DirectoryInfoArray[i].ObjectType;
				DirectoryInfo.DirectoryInfoArray[i].OtherInfo = RetPar.DirectoryInfo.DirectoryInfoArray[i].OtherInfo;
			}
			return RetPar.bCallSuccess;
		}
		return FALSE;
	}


	//删除对象
	BOOL DeleteObject(IN tstring & ObjectOrDir, SYSTEMERROR * pError)
	{
		_tagCallParameter Par, RetPar;
		Par.ObjectPath = ObjectOrDir;
		BOOL bRet = TransportT::GetInstance().CallInterface(m_szUserName, m_szConversation, OBJECT_SYSTEM_OP_DELETEOBJECT, Par, RetPar);
		if (bRet)
		{
			*pError = (SYSTEMERROR)RetPar.nError;
			return RetPar.bCallSuccess;
		}
		return FALSE;
	}

	

	class Event;
	struct _tagEventArray
	{
		unsigned int nEventTypeMask;
		vector<Event> EventArray;
	};
	map<tstring, _tagEventArray, less<tstring>> m_EventMap;

	class Event
	{
	public:
		Event() {};
		~Event() {};

		std::function<void(ObjectSystemEvent &)> m_LambdaFunction;
		EventType m_EventType;
		void RegistEvent(ObjectSystemEvent & RegEvent, std::function<void(ObjectSystemEvent &)>  Lambda) 
		{
			m_LambdaFunction = Lambda;
			m_EventType = (EventType)RegEvent.nEventType;
			//printf_t(_T("Lambda Size %d\n"), sizeof(Lambda));
			SYSTEMERROR Error;
			if (_MyClientT::GetInstance().m_EventMap.find(RegEvent.szObjectAddress) != _MyClientT::GetInstance().m_EventMap.end())
			{
				if (!(_MyClientT::GetInstance().m_EventMap[RegEvent.szObjectAddress].nEventTypeMask&RegEvent.nEventType))
				{
					RegEvent.nEventType |= _MyClientT::GetInstance().m_EventMap[RegEvent.szObjectAddress].nEventTypeMask;

					_MyClientT::GetInstance().RegistObjectEvent(RegEvent, &Error);
				}
				_MyClientT::GetInstance().m_EventMap[RegEvent.szObjectAddress].nEventTypeMask |= RegEvent.nEventType;
				_MyClientT::GetInstance().m_EventMap[RegEvent.szObjectAddress].EventArray.push_back(*this);
			}
			else
			{
				if (_MyClientT::GetInstance().RegistObjectEvent(RegEvent, &Error))
				{
					_tagEventArray Array;
					Array.nEventTypeMask = RegEvent.nEventType;
					Array.EventArray.push_back(*this);
					_MyClientT::GetInstance().m_EventMap[RegEvent.szObjectAddress] = Array;
				}

			}

		}
		Event(ObjectSystemEvent & RegEvent, std::function<void(ObjectSystemEvent &)>  Lambda) {
			RegistEvent(RegEvent,Lambda);
		};
		Event(tstring szObjectAddress,unsigned int nEventType, std::function<void(ObjectSystemEvent &)>  Lambda) {
			ObjectSystemEvent RegEvent;
			RegEvent.szObjectAddress = szObjectAddress;
			RegEvent.nEventType = nEventType;
			RegistEvent(RegEvent, Lambda);
		};
		Event(TCHAR* szObjectAddress, unsigned int nEventType, std::function<void(ObjectSystemEvent &)>  Lambda) {
			ObjectSystemEvent RegEvent;
			RegEvent.szObjectAddress = szObjectAddress;
			RegEvent.nEventType = nEventType;
			RegistEvent(RegEvent, Lambda);
		};
		static void SetEvent(ObjectSystemEvent & Event)
		{
			//LambdaFunction(Event);
			//tstring szObjectAddress = Event.szObjectAddress;
			//Event.szObjectAddress += _T("_EventMap");
			int nEventCount = _MyClientT::GetInstance().m_EventMap[Event.szObjectAddress].EventArray.size();
			for (int i=0; i<nEventCount;i++)
			{
				if (_MyClientT::GetInstance().m_EventMap[Event.szObjectAddress].EventArray[i].m_EventType&Event.nEventType)
				{
					_MyClientT::GetInstance().m_EventMap[Event.szObjectAddress].EventArray[i].m_LambdaFunction(Event);
				}
			}
		}
	private:

	};

	void ObjectEventCallBack(ObjectSystemEvent & Event)
	{
		Event::SetEvent(Event);
	}
	
	BOOL RegistObjectEvent(ObjectSystemEvent & RegEvent, OUT SYSTEMERROR * pError)
	{
		_tagCallParameter Par, RetPar;
		Par.ObjectPath = RegEvent.szObjectAddress;
		Par.nRegEventType = RegEvent.nEventType;
		//TransportT::GetInstance().RegistInterface(this);
		BOOL bRet = TransportT::GetInstance().CallInterface(m_szUserName, m_szConversation, OBJECT_SYSTEM_OP_REGIST_OBJEVENT, Par, RetPar);
		if (bRet)
		{
			*pError = (SYSTEMERROR)RetPar.nError;
			return RetPar.bCallSuccess;
		}
		return FALSE;
	}

	BOOL UpDataObjectState(IN tstring & ObjectPath, OUT _tagObjectState & ObjectState, OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}


	BOOL GetObjectState(IN tstring & ObjectPath, OUT _tagObjectState & ObjectState, OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}
	tstring & GetSession()
	{
		return m_szConversation;
	}
private:


	tstring m_szUserName;
	tstring m_szConversation;


};




/*
class ObjectType##_Wrap\
{\
public:\
	ObjectType	m_Data;\
	tstring		m_szAddr;\
	tstring		m_szFinder;\
	CObjectSystemInterface::_tagObjectState m_ObjectState;\
\
	CObjectSystemInterface::SYSTEMERROR m_nCurError;\
	ObjectType##_Wrap(){\
	m_ObjectState.bLock=FALSE;\
	m_ObjectState.nLockTime=0;\
	m_ObjectState.nType=CObjectSystemInterface::Nonmoral;\
	m_ObjectState.szLockUser=_T("");\
};\
	~ObjectType##_Wrap(){};\
	BOOL GetObject()\
	{\
		tstring Object;\
		BOOL bRet=gpObjectSystem->GetObject(m_szAddr,Object,m_ObjectState,&m_nCurError);\
		if(bRet)\
		{\
			SerTCHARXmlBufferToObject(ObjectType,m_Data,(Object.c_str()));\
		}\
		return bRet;\
\
	}\
\
	BOOL UpDataObject()\
	{\
		tstring Object;\
		SerObjectToXmlBuffer(ObjectType,m_Data,Object);\
		return gpObjectSystem->UpDataObject(m_szAddr,Object,&m_nCurError);\
	}\
\
	BOOL GetDirectoryInfo(CObjectSystemInterface::_tagDirectoryInfo & DirectoryInfo)\
	{\
		return gpObjectSystem->GetDirectoryInfo(m_szAddr,m_szFinder,DirectoryInfo,&m_nCurError);\
	}\
	BOOL DeleteObject()\
	{\
		return gpObjectSystem->DeleteObject(m_szAddr,&m_nCurError);\
	}\
};\
*/



/*
#define TO_NET_OBJECT_TYPE(ObjectType) \
class ObjectType##_Wrap\
{\
public:\
	ObjectType	m_Data;\
	tstring		m_szAddr;\
	CObjectSystem::SYSTEMERROR m_nCurError;\
	ObjectType##_Wrap(){};\
	~##ObjectType##_Wrap(){};\
	BOOL GetObject(IN OUT CObjectSystem::_tagObjectState & ObjectState)\
	{\
		tstring Object;\
		BOOL bRet=gpObjectSystem->GetObject(m_szAddr,Object,ObjectState,&m_nCurError);\
		if(bRet)\
		{\
			SerTCHARXmlBufferToObject(ObjectType,m_Data,(Object.c_str()));\
		}\
		return bRet;\
		\
	}\
	\
	BOOL UpDataObject()\
	{\
		tstring Object;\
		SerObjectToAnsiXmlBuffer(ObjectType,m_Data,Object);\
		return gpObjectSystem->UpDataObject(m_szAddr,Object,&m_nCurError);\
	}\
	\
	BOOL GetDirectoryInfo(CObjectSystem::_tagDirectoryInfo & DirectoryInfo)\
	{\
		return gpObjectSystem->GetDirectoryInfo(m_szAddr,DirectoryInfo,&m_nCurError);\
	}\
};\
*/

#include "Transport.h"