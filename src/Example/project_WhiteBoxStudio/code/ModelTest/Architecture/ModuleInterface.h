#pragma once


class CModuleBaseInterface;
class CFunctionModuleBase;

enum ModulePhysicsType
{
	LocalClass,
	LocalDll,
	RemoteType1,
};

enum ModuleType
{
	LogicModule,
	FunctionModule,
};




typedef struct _tagModuleContextForEnum
{
	ModuleType			eModuleType;
	ModulePhysicsType	eModulePhysicsType;
	char *				pModuleName;
	void *				pInterface;
}ModuleContextForEnum;

/*
template<typename ServiceProvider_Type,typename ModuleMgr_Type>
class CWorldSystem
{
public:

	CWorldSystem(){};
	~CWorldSystem(){};
protected:

private:
};*/

//逻辑模块枚举器接口 提供给世界系统的接口

class CModuleEnumerInterface
{
public:
	CModuleEnumerInterface(){};
	~CModuleEnumerInterface(){};
	virtual BOOL init(){return TRUE;};
	virtual BOOL close(){return TRUE;};
	//nIndex 从0开始增长迭代调用，直到失败为止，得到的接口存入模块管理器 
	virtual BOOL GetInterface(IN unsigned int nIndex,OUT ModuleContextForEnum * pContext){return TRUE;};
protected:
	
private:
};



//服务提供者提供给模块管理器的接口
class CMessageSenderInterface
{
public:
	CMessageSenderInterface(){};
	~CMessageSenderInterface(){};
	virtual BOOL SendAuditMsg(void *pMsg,unsigned int nMsgLen)
	{
		return TRUE;
	}
protected:
private:
};

class CModuleMgrProcessMsgInterface;
//服务提供者
class CServiceProvideInterface :public CMessageSenderInterface
{
public:
	CServiceProvideInterface(){};
	~CServiceProvideInterface(){};
	virtual BOOL init(CModuleMgrProcessMsgInterface * pModuleMgr)
	{
		return TRUE;
	}

	virtual BOOL Run()
	{
		return TRUE;
	}

	virtual BOOL close()
	{
		return TRUE;
	}
protected:

private:
};


//给模块枚举器的接口
class CModuleMgrForEnumer
{
public:
	CModuleMgrForEnumer(){};
	~CModuleMgrForEnumer(){};
	//注册逻辑模块
	virtual BOOL RegistLogicModule(char * pModuleName,ModulePhysicsType & eModulePhysicsType,CModuleBaseInterface * pLogicModule)
	{
		return TRUE;
	}
	//注册功能模块
	virtual BOOL RegistFunctionModule(char * pFunctionName,ModulePhysicsType & eModulePhysicsType,CFunctionModuleBase * pFunction)
	{
		return TRUE;
	}

	virtual BOOL RegistFunctionModule(WCHAR * pFunctionName,ModulePhysicsType & eModulePhysicsType,CFunctionModuleBase * pFunction)
	{
		return TRUE;
	}

	virtual BOOL FindFunctionHandle(char * pFunctionName,CFunctionModuleBase ** pFunction)
	{
		return TRUE;
	}

	virtual BOOL FindFunctionHandle(WCHAR * pFunctionName,CFunctionModuleBase ** pFunction)
	{
		return TRUE;
	}
protected:
	
private:
};

//给服务提供者的接口
class CModuleMgrProcessMsgInterface
{
public:
	CModuleMgrProcessMsgInterface(){};
	~CModuleMgrProcessMsgInterface(){};
	virtual BOOL ProcessMessage(char * MessageName,void *pMsg,unsigned int nMsgLen)
	{
		return TRUE;
	}
	virtual BOOL ProcessMessage(WCHAR * MessageName,void *pMsg,unsigned int nMsgLen)
	{
		return TRUE;
	}

	virtual BOOL SetMessageSender(CMessageSenderInterface * pSender)
	{
		return TRUE;
	}
protected:	
private:
};

//给逻辑模块使用的管理器接口
class CModuleMgrInterface
{
public:
	CModuleMgrInterface(){};
	~CModuleMgrInterface(){};
	

	virtual BOOL RegistMessageHandle(char * pMessageName,CModuleBaseInterface * pInterface,unsigned int nIndex)
	{
		return TRUE;
	}
	virtual BOOL RegistMessageHandle(WCHAR * pMessageName,CModuleBaseInterface * pInterface,unsigned int nIndex)
	{
		return TRUE;
	}
	virtual BOOL SendAuditMsg(void *pMsg,unsigned int nMsgLen,CModuleBaseInterface * pSender)
	{
		return TRUE;
	}
protected:
	
private:
};

//逻辑模块通用接口
class CModuleBaseInterface
{
public:
	CModuleBaseInterface(){};
	~CModuleBaseInterface(){};
	CModuleMgrInterface * m_pMgr;
	virtual BOOL init(CModuleMgrInterface * pMgr)
	{
		return TRUE;
	}
	virtual BOOL close()
	{
		return TRUE;
	}
	virtual BOOL ProcessMessage(unsigned int nIndex,void * pMsg,unsigned int nLen)
	{
		return TRUE;
	}
protected:
	
private:
};


//逻辑模块通用接口
class CFunctionModuleBase
{
public:
	CFunctionModuleBase(){};
	~CFunctionModuleBase(){};
	void * m_pInterface;
	virtual BOOL init(CModuleMgrInterface * pMgr)
	{
		return TRUE;
	}
	virtual BOOL close()
	{
		return TRUE;
	}
	
protected:

private:
};