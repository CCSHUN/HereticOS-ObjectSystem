#pragma once

#include "ModuleInterface.h"
#include "BaseFunctionTool.h"

typedef struct _tagModuleState
{
	unsigned int bInitOk:1;
	unsigned int bRun:1;
	unsigned int bCloseOk:1;
}ModuleState;

typedef struct _tagMsgHandleContext
{
	//ModulePhysicsType		nModulePhysicsType;
	void *					pContext;
	CModuleBaseInterface *	pInterface;
	unsigned int nIndex;
}MsgHandleContext;

typedef struct _tagModuleContext
{
	ModuleType			eModuleType;
	ModulePhysicsType	eModulePhysicsType;
	ModuleState			tagModuleState;
	tstring				ModuleName;
	void *				pInterface;
}ModuleContext;

class CModuleManger :public CModuleMgrInterface,
	public CModuleMgrProcessMsgInterface,
	public CModuleMgrForEnumer
{
public:

	//给模块枚举器使用的接口
	BOOL RegistLogicModule(char * pModuleName,ModulePhysicsType & eModulePhysicsType,CModuleBaseInterface * pLogicModule);
	BOOL RegistFunctionModule(char * pFunctionName,ModulePhysicsType & eModulePhysicsType,CFunctionModuleBase * pFunction);
	BOOL RegistFunctionModule(WCHAR * pFunctionName,ModulePhysicsType & eModulePhysicsType,CFunctionModuleBase * pFunction);

	BOOL FindFunctionHandle(char * pFunctionName,CFunctionModuleBase ** pFunction);
	BOOL FindFunctionHandle(WCHAR * pFunctionName,CFunctionModuleBase ** pFunction);

	typedef map<tstring,_tagModuleContext,less<tstring>> ModuleListType;
	ModuleListType m_ModuleListMap;

	//给模块的接口
	
	BOOL RegistMessageHandle(char * pMessageName,CModuleBaseInterface * pInterface,unsigned int nIndex);
	BOOL RegistMessageHandle(WCHAR * pMessageName,CModuleBaseInterface * pInterface,unsigned int nIndex);

	BOOL SendAuditMsg(void *pMsg,unsigned int nMsgLen,CModuleBaseInterface * pSender);
	
	//给服务提供者得的接口
	
	BOOL ProcessMessage(char * MessageName,void *pMsg,unsigned int nMsgLen);
	BOOL ProcessMessage(WCHAR * MessageName,void *pMsg,unsigned int nMsgLen);

	CMessageSenderInterface * m_pSender;
	BOOL SetMessageSender(CMessageSenderInterface * pSender);



	CModuleManger(void);
	~CModuleManger(void);

	//自身接口
	BOOL init();
	BOOL close();

	


private:
	typedef map<tstring,MsgHandleContext,less<tstring> > ProcessMsgListType;
	ProcessMsgListType m_ProcessMsgListMap;
	BOOL ProcessMessage(tstring & MessageName,void *pMsg,unsigned int nMsgLen);
	BOOL RegistFunctionModule(tstring & FunctionName,ModulePhysicsType & eModulePhysicsType,CFunctionModuleBase * pFunction);
	BOOL RegistMessageHandle(tstring & MessageName,CModuleBaseInterface * pInterface,unsigned int nIndex);
	BOOL FindFunctionHandle(tstring &pFunctionName,CFunctionModuleBase ** pFunction);

};
