#pragma once

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
		Nonmoral=1,					//默认方式
		AutoProlong=2,				//到期自动延迟锁，除非用户端应用停止响应
	};
	struct _tagObjectState 
	{
		BOOL	bLock;			//对象是否被锁。
		LockType	nType;		//锁的类型
		tstring szLockUser;		//当前获取锁的用户
		unsigned int nLockTime;	//锁定时间
	};

	//目录信息
	enum DirectoryObjectType
	{
		Directory=1,
		File=2,
	};

	struct _tagDirectoryInfoSet
	{
		tstring					ObjectName;		//对象名
		DirectoryObjectType		ObjectType;		//对象类型
		tstring					OtherInfo;		//对象其他信息
	};

	struct _tagDirectoryInfo
	{
		vector<_tagDirectoryInfoSet> DirectoryInfoArray;
	};
	enum SYSTEMERROR
	{
		Error_No=0,					//没有错误
		Error_Logon_PassWordError=1,		//密码错误
		Error_Logon_UserError=2,			//用户名错误
		Error_ObjectAlreadyLock=11,		//对象已经被锁
		Error_ObjectAlreadyExist=12,		//对象已经存在
		Error_ObjectNotExist=13,			//对象不存在
		Error_DirectoryAlreadyExist=21,	//对象已经存在
		Error_DirectoryNotExist=22,		//目录不存在
		Error_Sys_OpenFileFail=41,
	};

	CObjectSystemInterface(){};
	~CObjectSystemInterface(){};

	//////////////////////////////////////////对象基本操作///////////////////////////////////////

	//创建对象 可以是目录对象或者是文件对象
	virtual BOOL CreateObject(IN tstring & ObjectPath,DirectoryObjectType &ObjectType)
	{
		return TRUE;
	}
	//ObjectPath	对象地址
	//Object		返回的XML对象
	//ObjectState	输入申请该对象的锁定时间 0申请为不锁，返回该对象的锁定信息，如果对象已经被其他用户锁定，则返回其他用户的锁信息
	virtual BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//更新对象到存储
	virtual BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//更新对象到存储
	virtual BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,IN _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//获取目录信息
	virtual BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//获取目录信息
	virtual BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfoSoap & DirectoryInfo,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}
	//删除对象
	virtual BOOL DeleteObject(IN tstring & ObjectOrDir,SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//释放目录状态
	virtual BOOL ReleaseObjectState(IN tstring & ObjectOrDir,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}


	//////////////////////////////////////////对象系统登陆登出///////////////////////////////////////
	//登陆对象存储系统
	virtual BOOL LogonInSystem(IN tstring & szUserName,IN tstring & szPassword)
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
	virtual BOOL UpDataObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//获取对象锁信息
	virtual BOOL GetObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	virtual BOOL GetCurTime(SYSTEMTIME *  npTime,SYSTEMTIME * nCurTime)
	{
		return TRUE;
	}

	////////////////////////////////////////对象事物////////////////////////////////////////////////
	class ObjectEventProcessInterface
	{
	public: 
		ObjectEventProcessInterface(){};
		~ObjectEventProcessInterface(){};
		enum EventType
		{
			ObjectEvent_Updata=1,	//更新时触发
			ObjectEvent_Create=2,	//创建时触发
			ObjectEvent_Delete=3,	//删除时触发
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

	//////////////////////////////////////////对象基本操作///////////////////////////////////////

	//ObjectPath	对象地址
	//Object		返回的XML对象
	//ObjectState	输入申请该对象的锁定时间 0申请为不锁，返回该对象的锁定信息，如果对象已经被其他用户锁定，则返回其他用户的锁信息
	BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//更新对象到存储
	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,SYSTEMERROR * pError)
	{
		// 文件是否存在
		return TRUE;
	}

	//获取目录信息
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//删除对象
	BOOL DeleteObject(IN tstring & DirectoryPath,SYSTEMERROR * pError)
	{
		return TRUE;
	}


	//////////////////////////////////////////对象系统登陆登出///////////////////////////////////////
	//登陆对象存储系统
	BOOL LogonInSystem(IN tstring & szUserName,IN tstring & szPassword)
	{
		return TRUE;
	}

	//登出
	BOOL LogonOutSystem()
	{
		return TRUE;
	}

	//////////////////////////////////////////对象锁操作///////////////////////////////////////

	//更新对象锁信息
	BOOL UpDataObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
	{
		return TRUE;
	}

	//获取对象锁信息
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
// 声明一个对象

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

