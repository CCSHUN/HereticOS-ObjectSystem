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
		//����debugtool
		m_DebugTool.init(NULL);
		//��������
		m_Config.init(NULL);
		//ע���߼�ģ��
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
		//�Խӷ����ṩ�ߺ�ģ�������
		m_ServiceProvider.init((CModuleMgrProcessMsgInterface*)&m_ModuleMgr);

		//��ʼ����������
		m_ModuleMgr.init();

		//���з����ṩ�ߡ�
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
