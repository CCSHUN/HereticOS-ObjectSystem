#include "StdAfx.h"
#include "ModuleManger.h"

CModuleManger::CModuleManger(void)
{
}

CModuleManger::~CModuleManger(void)
{
}

BOOL CModuleManger::FindFunctionHandle(char * pFunctionName,CFunctionModuleBase ** pFunction)
{
	return FindFunctionHandle(tstring((TCHAR*)CMyString(pFunctionName,strlen(pFunctionName))),pFunction);

}

BOOL CModuleManger::FindFunctionHandle(WCHAR * pFunctionName,CFunctionModuleBase ** pFunction)
{
	return FindFunctionHandle(tstring((TCHAR*)CMyString(pFunctionName,wcslen(pFunctionName))),pFunction);
}

BOOL CModuleManger::RegistFunctionModule(char * pFunctionName,ModulePhysicsType & eModulePhysicsType,CFunctionModuleBase * pFunction)
{
	return RegistFunctionModule(tstring((TCHAR*)CMyString(pFunctionName,strlen(pFunctionName))),
		eModulePhysicsType,pFunction);
}
BOOL CModuleManger::RegistFunctionModule(WCHAR * pFunctionName,ModulePhysicsType & eModulePhysicsType,CFunctionModuleBase * pFunction)
{
	return RegistFunctionModule(tstring((TCHAR*)CMyString(pFunctionName,wcslen(pFunctionName))),
		eModulePhysicsType,pFunction);
}



BOOL CModuleManger::init()
{
	//初始化功能模块
	for(int i=0;i<16;i++)
	{
		BOOL bOk=TRUE;
		ModuleListType::iterator itLogic=m_ModuleListMap.begin();
		for(;itLogic!=m_ModuleListMap.end();itLogic++)
		{
			if(itLogic->second.tagModuleState.bInitOk==0)
			{
				switch(itLogic->second.eModuleType)
				{
				case LogicModule:
					continue;
				case FunctionModule:
					{
						if(((CFunctionModuleBase*)itLogic->second.pInterface)->init(this))
						{
							itLogic->second.tagModuleState.bInitOk=1;
						}else
						{
							bOk=FALSE;
						}
					}
					break;
				default:
					return FALSE;
				}
				
			}
		}
		if(bOk)
		{
			break;
		}
	}

	//初始化逻辑模块
	for(int i=0;i<16;i++)
	{
		BOOL bOk=TRUE;
		ModuleListType::iterator itLogic=m_ModuleListMap.begin();
		for(;itLogic!=m_ModuleListMap.end();itLogic++)
		{
			if(itLogic->second.tagModuleState.bInitOk==0)
			{
				switch(itLogic->second.eModuleType)
				{
				case LogicModule:
					{
						if(((CModuleBaseInterface*)itLogic->second.pInterface)->init(this))
						{
							itLogic->second.tagModuleState.bInitOk=1;
						}else
						{
							bOk=FALSE;
						}
					}
					break;
				case FunctionModule:
					continue;
				default:
					return FALSE;
				}

			}
		}
		if(bOk)
		{
			break;
		}
	}
	return TRUE;
}
BOOL CModuleManger::close()
{
	//先关闭逻辑模块
	for(int i=0;i<16;i++)
	{
		BOOL bOk=TRUE;
		ModuleListType::iterator itLogic=m_ModuleListMap.begin();
		for(;itLogic!=m_ModuleListMap.end();itLogic++)
		{
			if(itLogic->second.tagModuleState.bCloseOk==0)
			{
				switch(itLogic->second.eModuleType)
				{
				case LogicModule:
					{
						if(((CModuleBaseInterface*)itLogic->second.pInterface)->close())
						{
							itLogic->second.tagModuleState.bCloseOk=1;
						}else
						{
							bOk=FALSE;
						}
					}
					break;
				case FunctionModule:
					continue;
				default:
					return FALSE;
				}

			}
		}
		if(bOk)
		{
			break;
		}
	}

	//再关闭功能模块
	for(int i=0;i<16;i++)
	{
		BOOL bOk=TRUE;
		ModuleListType::iterator itLogic=m_ModuleListMap.begin();
		for(;itLogic!=m_ModuleListMap.end();itLogic++)
		{
			if(itLogic->second.tagModuleState.bCloseOk==0)
			{
				switch(itLogic->second.eModuleType)
				{
				case LogicModule:
					continue;
				case FunctionModule:
					{
						if(((CFunctionModuleBase*)itLogic->second.pInterface)->close())
						{
							itLogic->second.tagModuleState.bCloseOk=1;
						}else
						{
							bOk=FALSE;
						}
					}
					break;
				default:
					return FALSE;
				}

			}
		}
		if(bOk)
		{
			break;
		}
	}
	return TRUE;
}

BOOL CModuleManger::RegistFunctionModule(tstring & FunctionName,ModulePhysicsType & eModulePhysicsType,CFunctionModuleBase * pFunction)
{
	ModuleContext Context;
	Context.eModulePhysicsType=eModulePhysicsType;
	Context.eModuleType=FunctionModule;
	Context.tagModuleState.bInitOk=0;
	Context.ModuleName=FunctionName;
	Context.pInterface=pFunction;
	m_ModuleListMap[Context.ModuleName]=Context;
	return TRUE;
}


BOOL CModuleManger::RegistLogicModule(char * pModuleName,ModulePhysicsType & eModulePhysicsType,CModuleBaseInterface * pLogicModule)
{
	ModuleContext Context;
	Context.eModulePhysicsType=eModulePhysicsType;
	Context.eModuleType=LogicModule;
	Context.tagModuleState.bInitOk=0;
	Context.ModuleName=(TCHAR*)CMyString(pModuleName,strlen(pModuleName));
	Context.pInterface=pLogicModule;
	m_ModuleListMap[Context.ModuleName]=Context;
	return TRUE;
}
BOOL CModuleManger::RegistMessageHandle(char * pMessageName,CModuleBaseInterface * pInterface,unsigned int nIndex)
{
	return RegistMessageHandle(tstring((TCHAR*)CMyString(pMessageName,strlen(pMessageName))),
		pInterface,nIndex);
}
BOOL CModuleManger::RegistMessageHandle(WCHAR * pMessageName,CModuleBaseInterface * pInterface,unsigned int nIndex)
{
	return RegistMessageHandle(tstring((TCHAR*)CMyString(pMessageName,wcslen(pMessageName))),
		pInterface,nIndex);
}
BOOL CModuleManger::SetMessageSender(CMessageSenderInterface * pSender)
{
	m_pSender=pSender;
	return TRUE;
}

BOOL CModuleManger::SendAuditMsg(void *pMsg,unsigned int nMsgLen,CModuleBaseInterface * pSender)
{
	BOOL bRet=m_pSender->SendAuditMsg(pMsg,nMsgLen);
	return bRet;
}

BOOL CModuleManger::ProcessMessage(char * MessageName,void *pMsg,unsigned int nMsgLen)
{
	return ProcessMessage(tstring((TCHAR*)CMyString(MessageName,strlen(MessageName))),
		pMsg,nMsgLen);
}
BOOL CModuleManger::ProcessMessage(WCHAR * MessageName,void *pMsg,unsigned int nMsgLen)
{
	return ProcessMessage(tstring((TCHAR*)CMyString(MessageName,wcslen(MessageName))),
		pMsg,nMsgLen);
}

BOOL CModuleManger::ProcessMessage(tstring & MessageName,void *pMsg,unsigned int nMsgLen)
{
	ProcessMsgListType::iterator itMap=m_ProcessMsgListMap.find(MessageName);
	if(itMap!=m_ProcessMsgListMap.end())
	{
		return itMap->second.pInterface->ProcessMessage(itMap->second.nIndex,pMsg,nMsgLen);
	}else
	{
		return FALSE;
	}

	return TRUE;
}


BOOL CModuleManger::RegistMessageHandle(tstring & MessageName,CModuleBaseInterface * pInterface,unsigned int nIndex)
{
	MsgHandleContext Context;
	//Context.nModulePhysicsType=LocalClass;
	Context.pInterface=pInterface;
	Context.nIndex=nIndex;
	m_ProcessMsgListMap[MessageName]=Context;
	return TRUE;
}

BOOL CModuleManger::FindFunctionHandle(tstring &pFunctionName,CFunctionModuleBase ** pFunction)
{
	ModuleListType::iterator itModule=m_ModuleListMap.find(pFunctionName);
	if(itModule!=m_ModuleListMap.end())
	{
		* pFunction=(CFunctionModuleBase *)itModule->second.pInterface;
		return TRUE;
	}
	return FALSE;
}
