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

#define IN

#define OUT

#define LAB(x)	x  
#define LAB1(x) #x
#define LAB2(x) LAB1(x)

#define SERHEAD(_path,_name) LAB2(LAB(_path)LAB(_name)LAB(_StructInfo.h))
#define SERPROTO_HEAD(_name) LAB2(LAB(./SerTransportProtocol/)LAB(_name)LAB(_StructInfo.h))


//typedef string tstring;


namespace ObjectSystem
{
	enum LockType
	{
		Nonmoral = 1,					//默认方式
		AutoProlong = 2,				//到期自动延迟锁，除非用户端应用停止响应
	};

	//目录信息
	enum DirectoryObjectType
	{
		Directory = 1,
		File = 2,
	};

	enum SYSTEMERROR
	{
		Error_No = 0,					//没有错误
		Error_Logon_PassWordError = 1,		//密码错误
		Error_Logon_UserError = 2,			//用户名错误
		Error_ObjectAlreadyLock = 11,		//对象已经被锁
		Error_ObjectAlreadyExist = 12,		//对象已经存在
		Error_ObjectNotExist = 13,			//对象不存在
		Error_DirectoryAlreadyExist = 21,	//对象已经存在
		Error_DirectoryNotExist = 22,		//目录不存在
		Error_Sys_OpenFileFail = 41,
		Error_Sys_Event_Too_Much=42,		//事件太多
		Error_Sys_Transport_Fail=43,		//传输中断
	};
	enum EventType
	{
		ObjectEvent_Updata = 1,	//更新时触发
		ObjectEvent_Create = 2,	//创建时触发
		ObjectEvent_Delete = 4,	//删除时触发
		ObjectEvent_Get = 8,    //获取后触发
		ObjectEvent_NeedNew = 0x10,	//需要相关服务刷新变成时触发
	};

	typedef struct _tagDirectoryInfoSet
	{
		tstring					ObjectName;		//对象名
		unsigned int			ObjectType;		//对象类型
		tstring					OtherInfo;		//对象其他信息
	}DirectoryInfoSet, *PDirectoryInfoSet;

	typedef struct _tagDirectoryInfo
	{
		vector<_tagDirectoryInfoSet> DirectoryInfoArray;
	}DirectoryInfo, *PDirectoryInfo;


	typedef struct _tagObjectState
	{
		BOOL	bLock;			//对象是否被锁。
		unsigned int	nType;	//锁的类型
		tstring szLockUser;		//当前获取锁的用户
		unsigned int nLockTime;	//锁定时间
	}ObjectState, *PObjectState;



	typedef struct _tagstrParameter
	{
		SER_TO_X<tstring, Base64ZipString> szData;
	}strParameter, *PstrParameter;

	typedef struct _tagObjectSystemEvent
	{
		tstring szObjectAddress;
		unsigned int nEventType;
	}ObjectSystemEvent, *PObjectSystemEvent;

	typedef struct _tagCallParameter
	{
		tstring					su;//szUser
		tstring					ss;//szSession
		unsigned int			oc;//nOpcode
		BOOL					bcs; //bCallSucess;
		tstring 				op;	//ObjectPath
		unsigned int			np;//nPar
		SER_TO_X<tstring, Base64ZipString> 				ob;//Object
		_tagObjectState			Os;	//ObjectState
		unsigned int			Err;
		tstring					sf;				//szFinder
		_tagDirectoryInfo	di;
		vector<_tagObjectSystemEvent>	el;//EventList;
		map<tstring, _tagstrParameter, less<tstring> > sp;//strPar
	}CallParameter, *PCallParameter;

	typedef struct _tagCallParameterV2
	{
		tstring_tmp				szUser;
		tstring_tmp				szSession;
		unsigned int			nOpCode;
		tstring_tmp				szPassword;
		BOOL					bCallSuccess;
		tstring_tmp 			ObjectPath;
		unsigned int			nPar;
		tstring_tmp				Object;
		_tagObjectState			tagObjectState;
		unsigned int			nError;
		tstring_tmp				szFinder;
		_tagDirectoryInfo	DirectoryInfo;
		vector<_tagObjectSystemEvent>	EventList;
		map<tstring_tmp, _tagstrParameter, less<tstring_tmp> > strPar;
	}CallParameterV2, *PCallParameterV2;

	typedef struct _tagKeepAlivedPar
	{
		unsigned int nCyc;			//推送周期 单位ms, time_t time 1970年1月1日00:00:00开始至今的秒数模除 nCyc得到当前时间所处窗口坐标
		unsigned int nWndPos;       //推送窗口坐标 ms
		unsigned int nWndLen;		//窗口宽度
	}KeepAlivedPar,*PKeepAlivedPar;
	typedef struct _tagUserMapSet
	{
		tstring szUserName;
		tstring szPassword;
		tstring szUserType;			//用户类型 暂定为测试人员，研发人员，管理员
		tstring szChildUserType;	//暂时不用，以后定位细分后扩展
		tstring szChildUserType1;	//暂时不用，以后定位细分后扩展
	}UserMapSet, *PUserMapSet;


}
using namespace ObjectSystem;

//#include "ObjectSystem.h"

//#include "..\ObjectSerDef\_tagstrParameter_StructInfo.h"
//typedef  ObjectTypeWrap<_tagstrParameter,Serialize__tagstrParameter> _tagstrParameter_Wrap; 
#include SERPROTO_HEAD(_tagObjectSystemEvent)
MAKESTRUCTINFO(_tagObjectSystemEvent)

#include SERPROTO_HEAD(_tagstrParameter)
MAKESTRUCTINFO(_tagstrParameter)

//#include "..\ObjectSerDef\_tagObjectStateSoap_StructInfo.h"
#include SERPROTO_HEAD(_tagObjectState)
MAKESTRUCTINFO(_tagObjectState)

//#include "..\ObjectSerDef\_tagDirectoryInfoSetSoap_StructInfo.h"
#include SERPROTO_HEAD(_tagDirectoryInfoSet)
MAKESTRUCTINFO(_tagDirectoryInfoSet)

//#include "..\ObjectSerDef\_tagDirectoryInfoSoap_StructInfo.h"
#include SERPROTO_HEAD(_tagDirectoryInfo)
MAKESTRUCTINFO(_tagDirectoryInfo)

#include SERPROTO_HEAD(_tagKeepAlivedPar)
MAKESTRUCTINFO(_tagKeepAlivedPar)

//#include "..\ObjectSerDef\_tagCallParameter_StructInfo.h"
#include SERPROTO_HEAD(_tagCallParameter)
MAKESTRUCTINFO(_tagCallParameter)

#include SERPROTO_HEAD(_tagCallParameterV2)
MAKESTRUCTINFO(_tagCallParameterV2)



