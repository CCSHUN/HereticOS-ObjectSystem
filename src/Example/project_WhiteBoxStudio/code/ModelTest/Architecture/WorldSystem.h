#pragma once


template<typename ServiceProvider_Type,typename ModuleMgr_Type,
typename ModuleEnumer,typename Config_Type,typename DebugToolType>
class CWorldSystem
{
private:
	ModuleEnumer			m_Enumer;
	ModuleMgr_Type			m_ModuleMgr;
	ServiceProvider_Type	m_ServiceProvider;

public:
	Config_Type				m_Config;
	DebugToolType			m_DebugTool;
	
	BOOL init()
	{
		//加载debugtool
		m_DebugTool.init(NULL);
		//加载配置
		m_Config.init(NULL);
		//注册逻辑模块
		for (int nIndex=0;;nIndex++)
		{
			ModuleContextForEnum Context;
			BOOL bGetInterface=m_Enumer.GetInterface(nIndex,&Context);
			if(bGetInterface)
			{
				switch(Context.eModuleType)
				{
				case LogicModule:
					{
						CModuleMgrForEnumer * pMgr=&m_ModuleMgr;
						pMgr->RegistLogicModule(
							Context.pModuleName,
							Context.eModulePhysicsType,
							(CModuleBaseInterface *)Context.pInterface);
					}
					
					break;
				case FunctionModule:
					break;
				}
				
			}else
			{
				break;
			}
		}
		//对接服务提供者和模块管理器
		m_ServiceProvider.init((CModuleMgrProcessMsgInterface*)&m_ModuleMgr);

		//初始化管理器。
		m_ModuleMgr.init();

		//运行服务提供者。
		m_ServiceProvider.Run();
		return TRUE;
	};

	BOOL close()
	{
		m_ServiceProvider.close();
		m_ModuleMgr.close();
		return TRUE;
	};

	CWorldSystem(void){};
	~CWorldSystem(void){};
};
