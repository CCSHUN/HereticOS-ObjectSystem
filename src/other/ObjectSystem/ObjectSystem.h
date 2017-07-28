#pragma once

//#include "stdafx.h"

/*
enum LockType
{
Nonmoral=1,					//Ĭ�Ϸ�ʽ
AutoProlong=2,				//�����Զ��ӳ����������û���Ӧ��ֹͣ��Ӧ
};
*/


//����SOAP ����

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

static TCHAR * Object_OPTab[]=
{
	_T(""),_T("GetObject"),_T("UpdataObject"),_T("DeleteObject"),
	_T("GetDirectoryInfo"),_T("LogonIn"),_T("LogonOut"),_T("GetObjectState"),
	_T("UpdataObjectState"),_T("GetCurTime"),_T("ReleaseObjectState"),_T(""),
};

struct _tagDirectoryInfoSoap;

class CObjectSystemInterface
{
public:
	enum LockType
	{
		Nonmoral=1,					//Ĭ�Ϸ�ʽ
		AutoProlong=2,				//�����Զ��ӳ����������û���Ӧ��ֹͣ��Ӧ
	};
	struct _tagObjectState 
	{
		BOOL	bLock;			//�����Ƿ�����
		LockType	nType;		//��������
		tstring szLockUser;		//��ǰ��ȡ�����û�
		unsigned int nLockTime;	//����ʱ��
	};

	//Ŀ¼��Ϣ
	enum DirectoryObjectType
	{
		Directory=1,
		File=2,
	};

	struct _tagDirectoryInfoSet
	{
		tstring					ObjectName;		//������
		DirectoryObjectType		ObjectType;		//��������
		tstring					OtherInfo;		//����������Ϣ
	};

	struct _tagDirectoryInfo
	{
		vector<_tagDirectoryInfoSet> DirectoryInfoArray;
	};
	enum SYSTEMERROR
	{
		Error_No=0,					//û�д���
		Error_Logon_PassWordError=1,		//�������
		Error_Logon_UserError=2,			//�û�������
		Error_ObjectAlreadyLock=11,		//�����Ѿ�����
		Error_ObjectAlreadyExist=12,		//�����Ѿ�����
		Error_ObjectNotExist=13,			//���󲻴���
		Error_DirectoryAlreadyExist=21,	//�����Ѿ�����
		Error_DirectoryNotExist=22,		//Ŀ¼������
		Error_Sys_OpenFileFail=41,
	};

	CObjectSystemInterface(){};
	~CObjectSystemInterface(){};

	//////////////////////////////////////////�����������///////////////////////////////////////

	//�������� ������Ŀ¼����������ļ�����
	virtual BOOL CreateObject(IN tstring & ObjectPath,DirectoryObjectType &ObjectType)
	{
		return TRUE;
	}
	//ObjectPath	�����ַ
	//Object		���ص�XML����
	//ObjectState	��������ö��������ʱ�� 0����Ϊ���������ظö����������Ϣ����������Ѿ��������û��������򷵻������û�������Ϣ
	virtual BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//���¶��󵽴洢
	virtual BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//���¶��󵽴洢
	virtual BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,IN _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//��ȡĿ¼��Ϣ
	virtual BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//��ȡĿ¼��Ϣ
	virtual BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfoSoap & DirectoryInfo,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}
	//ɾ������
	virtual BOOL DeleteObject(IN tstring & ObjectOrDir,SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//�ͷ�Ŀ¼״̬
	virtual BOOL ReleaseObjectState(IN tstring & ObjectOrDir,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}


	//////////////////////////////////////////����ϵͳ��½�ǳ�///////////////////////////////////////
	//��½����洢ϵͳ
	virtual BOOL LogonInSystem(IN tstring & szUserName,IN tstring & szPassword)
	{
		return TRUE;
	}

	//�ǳ�
	virtual BOOL LogonOutSystem()
	{
		return TRUE;
	}

	//////////////////////////////////////////����������///////////////////////////////////////

	//���¶�������Ϣ
	virtual BOOL UpDataObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//��ȡ��������Ϣ
	virtual BOOL GetObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	virtual BOOL GetCurTime(SYSTEMTIME *  npTime,SYSTEMTIME * nCurTime)
	{
		return TRUE;
	}

	////////////////////////////////////////��������////////////////////////////////////////////////
	class ObjectEventProcessInterface
	{
	public: 
		ObjectEventProcessInterface(){};
		~ObjectEventProcessInterface(){};
		enum EventType
		{
			ObjectEvent_Updata=1,	//����ʱ����
			ObjectEvent_Create=2,	//����ʱ����
			ObjectEvent_Delete=3,	//ɾ��ʱ����
		};

		virtual BOOL ObjectEventProcess(IN tstring & ObjectPath,IN EventType & nEvent)
		{
			return TRUE;
		}
	};

	virtual BOOL RegistObjectEvent(IN tstring & ObjectPath,IN ObjectEventProcessInterface::EventType & nEvent,IN ObjectEventProcessInterface  * pEventInterface,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}
protected:

private:
};

//extern CObjectSystem * gpObjectSystem;

extern CObjectSystemInterface * gpObjectSystem;
/*

class CObjectSystem_Local : public CObjectSystem
{
public:

	CObjectSystem_Local(){};
	~CObjectSystem_Local(){};

	//////////////////////////////////////////�����������///////////////////////////////////////

	//ObjectPath	�����ַ
	//Object		���ص�XML����
	//ObjectState	��������ö��������ʱ�� 0����Ϊ���������ظö����������Ϣ����������Ѿ��������û��������򷵻������û�������Ϣ
	BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//���¶��󵽴洢
	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,SYSTEMERROR * pError)
	{
		// �ļ��Ƿ����
		return TRUE;
	}

	//��ȡĿ¼��Ϣ
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//ɾ������
	BOOL DeleteObject(IN tstring & DirectoryPath,SYSTEMERROR * pError)
	{
		return TRUE;
	}


	//////////////////////////////////////////����ϵͳ��½�ǳ�///////////////////////////////////////
	//��½����洢ϵͳ
	BOOL LogonInSystem(IN tstring & szUserName,IN tstring & szPassword)
	{
		return TRUE;
	}

	//�ǳ�
	BOOL LogonOutSystem()
	{
		return TRUE;
	}

	//////////////////////////////////////////����������///////////////////////////////////////

	//���¶�������Ϣ
	BOOL UpDataObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//��ȡ��������Ϣ
	BOOL GetObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}


	BOOL RegistObjectEvent(IN tstring & ObjectPath,IN ObjectEventProcessInterface::EventType & nEvent,IN ObjectEventProcessInterface  * pEventInterface,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}
protected:

private:
};
*/


//_S_REPORT
//CObjectSystemInterface::_tagObjectState m_ObjectState;


template<class ValType,class SerType>
class ObjectTypeWrap
{
public:
	ValType		m_Data;
	tstring		m_szAddr;
	tstring		m_szFinder;
	CObjectSystemInterface::_tagObjectState m_ObjectState;

	CObjectSystemInterface::SYSTEMERROR m_nCurError;

	ObjectTypeWrap()
	{
		m_ObjectState.bLock=FALSE;
		m_ObjectState.nLockTime=0;
		m_ObjectState.nType=CObjectSystemInterface::Nonmoral;
		m_ObjectState.szLockUser=_T("");
	}


	virtual ~ObjectTypeWrap(){};

	
	BOOL GetObject()
	{
		tstring Object;
		BOOL bRet=gpObjectSystem->GetObject(m_szAddr,Object,m_ObjectState,&m_nCurError);
		if(bRet)
		{
			SerTCHARXmlBufferToObjectEx(ValType,SerType,m_Data,(Object.c_str()));
		}
		return bRet;

	}
	
	BOOL UpDataObject()
	{
		tstring Object;
		SerObjectToXmlBufferEx(ValType,SerType,m_Data,Object);
		return gpObjectSystem->UpDataObject(m_szAddr,Object,&m_nCurError);
	}

	
	BOOL GetDirectoryInfo(CObjectSystemInterface::_tagDirectoryInfo & DirectoryInfo)
	{
		return gpObjectSystem->GetDirectoryInfo(m_szAddr,m_szFinder,DirectoryInfo,&m_nCurError);
	}


	BOOL DeleteObject()
	{
		return gpObjectSystem->DeleteObject(m_szAddr,&m_nCurError);
	}
	
};



#define MAKESTRUCTINFO(ObjectType)  TO_NET_OBJECT_TYPE(ObjectType) 
// ����һ������

#define TO_NET_OBJECT_TYPE(ObjectType) \
	typedef ObjectTypeWrap<ObjectType,Serialize_##ObjectType> ObjectType##_Wrap; \


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

