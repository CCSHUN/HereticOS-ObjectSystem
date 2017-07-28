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

//�߼�ģ��ö�����ӿ� �ṩ������ϵͳ�Ľӿ�

class CModuleEnumerInterface
{
public:
	CModuleEnumerInterface(){};
	~CModuleEnumerInterface(){};
	virtual BOOL init(){return TRUE;};
	virtual BOOL close(){return TRUE;};
	//nIndex ��0��ʼ�����������ã�ֱ��ʧ��Ϊֹ���õ��Ľӿڴ���ģ������� 
	virtual BOOL GetInterface(IN unsigned int nIndex,OUT ModuleContextForEnum * pContext){return TRUE;};
protected:
	
private:
};



//�����ṩ���ṩ��ģ��������Ľӿ�
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
//�����ṩ��
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


//��ģ��ö�����Ľӿ�
class CModuleMgrForEnumer
{
public:
	CModuleMgrForEnumer(){};
	~CModuleMgrForEnumer(){};
	//ע���߼�ģ��
	virtual BOOL RegistLogicModule(char * pModuleName,ModulePhysicsType & eModulePhysicsType,CModuleBaseInterface * pLogicModule)
	{
		return TRUE;
	}
	//ע�Ṧ��ģ��
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

//�������ṩ�ߵĽӿ�
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

//���߼�ģ��ʹ�õĹ������ӿ�
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

//�߼�ģ��ͨ�ýӿ�
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


//�߼�ģ��ͨ�ýӿ�
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