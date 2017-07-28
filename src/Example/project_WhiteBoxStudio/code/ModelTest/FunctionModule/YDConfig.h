#pragma once


/*
typedef struct _tagYDConfig
{
	tstring strRuleVer;
	//域用于测试连接计算得到本地ip
	tstring strNetDomainName;
	int		nNetDomainPort;

	tstring strWSDLUrl;
	tstring strRunDirectory;
	int		nSoapTimeout;
	int		nCheckCycle;
}YDConfig;*/

//#include "ObjectSerDef/_tagYDConfig_StructInfo.h"

#include "DataModuleDef.h"
#include "ModuleInterface.h"

class CYDConfig : public CFunctionModuleBase
{
private:
	BOOL GetLocalDir(tstring & szRunPath);

public:
	YDConfig m_Config;
	CYDConfig(void);
	~CYDConfig(void);

	

	BOOL init(CModuleMgrInterface * pMgr)
	{
		m_Config.strRuleVer=_T("123");
		m_Config.strNetDomainName=_T("127.0.0.1");
		//m_Config.strWSDLUrl=_T("http://192.168.1.92/ServerAudit/OutPut/Calc.WSDL");
		m_Config.strWSDLUrl=_T("http://localhost/MSSoapSamples30/ObjectSystem/ObjectSystem.WSDL");

		//m_Config.strWSDLUrl=_T("http://localhost:8080/ProcessProtect/services/connTest");
		m_Config.nSoapTimeout=5000;
		m_Config.nCheckCycle=10*1000;
		m_Config.nNetDomainPort=80;
		//GetLocalAuditDir(m_Config.strRunDirectory);
		//m_Config.strRunDirectory=GetLocalAuditDir();
		
		tstring szConfigFilePath;
		GetLocalDir(szConfigFilePath);
		OutputDebugString(_T("YDConfig.xml=====>"));
		OutputDebugString(szConfigFilePath.c_str());
		OutputDebugString(_T("YDConfig.xml<====="));

		//m_Config.strRunDirectory+tstring(_T("\\YDConfig.xml"));
		//m_Config.strRunDirectory=szFile;
		SerAnsiFileToObject(_tagYDConfig,m_Config,szConfigFilePath.c_str());
		//GetLocalAuditDir(m_Config.strRunDirectory);

		//_DebugOutput("YDConfig","%s %s %d",m_Config.strNetDomainName,m_Config.strWSDLUrl)
		m_Config.strRunDirectory=szConfigFilePath;
		SerObjectToAnsiXmlFile(_tagYDConfig,m_Config,szConfigFilePath);
		return TRUE;
	}
	BOOL Save()
	{
		
		tstring szConfigFilePath;
		GetLocalDir(szConfigFilePath);
		SerObjectToAnsiXmlFile(_tagYDConfig,m_Config,szConfigFilePath);
		return TRUE;
	}
	BOOL close()
	{
		//tstring szConfigFilePath=m_Config.strRunDirectory+tstring(_T("\\YDConfig.xml"));
		//SerObjectToAnsiXmlFile(_tagYDConfig,m_Config,m_Config.strRunDirectory);
		Save();
		return TRUE;
	}
};
