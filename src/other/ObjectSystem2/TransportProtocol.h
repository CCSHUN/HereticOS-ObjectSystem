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
		Nonmoral = 1,					//Ĭ�Ϸ�ʽ
		AutoProlong = 2,				//�����Զ��ӳ����������û���Ӧ��ֹͣ��Ӧ
	};

	//Ŀ¼��Ϣ
	enum DirectoryObjectType
	{
		Directory = 1,
		File = 2,
	};

	enum SYSTEMERROR
	{
		Error_No = 0,					//û�д���
		Error_Logon_PassWordError = 1,		//�������
		Error_Logon_UserError = 2,			//�û�������
		Error_ObjectAlreadyLock = 11,		//�����Ѿ�����
		Error_ObjectAlreadyExist = 12,		//�����Ѿ�����
		Error_ObjectNotExist = 13,			//���󲻴���
		Error_DirectoryAlreadyExist = 21,	//�����Ѿ�����
		Error_DirectoryNotExist = 22,		//Ŀ¼������
		Error_Sys_OpenFileFail = 41,
		Error_Sys_Event_Too_Much=42,		//�¼�̫��
		Error_Sys_Transport_Fail=43,		//�����ж�
	};
	enum EventType
	{
		ObjectEvent_Updata = 1,	//����ʱ����
		ObjectEvent_Create = 2,	//����ʱ����
		ObjectEvent_Delete = 4,	//ɾ��ʱ����
		ObjectEvent_Get = 8,    //��ȡ�󴥷�
		ObjectEvent_NeedNew = 0x10,	//��Ҫ��ط���ˢ�±��ʱ����
	};

	typedef struct _tagDirectoryInfoSet
	{
		tstring					ObjectName;		//������
		unsigned int			ObjectType;		//��������
		tstring					OtherInfo;		//����������Ϣ
	}DirectoryInfoSet, *PDirectoryInfoSet;

	typedef struct _tagDirectoryInfo
	{
		vector<_tagDirectoryInfoSet> DirectoryInfoArray;
	}DirectoryInfo, *PDirectoryInfo;


	typedef struct _tagObjectState
	{
		BOOL	bLock;			//�����Ƿ�����
		unsigned int	nType;	//��������
		tstring szLockUser;		//��ǰ��ȡ�����û�
		unsigned int nLockTime;	//����ʱ��
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
		unsigned int nCyc;			//�������� ��λms, time_t time 1970��1��1��00:00:00��ʼ���������ģ�� nCyc�õ���ǰʱ��������������
		unsigned int nWndPos;       //���ʹ������� ms
		unsigned int nWndLen;		//���ڿ��
	}KeepAlivedPar,*PKeepAlivedPar;
	typedef struct _tagUserMapSet
	{
		tstring szUserName;
		tstring szPassword;
		tstring szUserType;			//�û����� �ݶ�Ϊ������Ա���з���Ա������Ա
		tstring szChildUserType;	//��ʱ���ã��Ժ�λϸ�ֺ���չ
		tstring szChildUserType1;	//��ʱ���ã��Ժ�λϸ�ֺ���չ
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



