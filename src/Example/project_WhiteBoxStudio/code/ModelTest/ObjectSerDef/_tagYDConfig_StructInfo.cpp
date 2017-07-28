 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagYDConfig_StructInfo.h"

Serialize__tagYDConfig::_Myt& Serialize__tagYDConfig::operator=(_tagYDConfig & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagYDConfig::GetData()
{
	m_Val.strRuleVer=strRuleVer; 
	m_Val.strNetDomainName=strNetDomainName; 
	m_Val.nNetDomainPort=nNetDomainPort; 
	m_Val.strWSDLUrl=strWSDLUrl; 
	m_Val.strRunDirectory=strRunDirectory; 
	m_Val.strLocalSystemDirectory=strLocalSystemDirectory; 
	m_Val.nSoapTimeout=nSoapTimeout; 
	m_Val.nCheckCycle=nCheckCycle; 
	m_Val.szDebugLevel=szDebugLevel;
}

BOOL Serialize__tagYDConfig::Construct(StorageObjectInterface * pOutObject)
{
	strRuleVer.init(this,_T("strRuleVer"),0,pOutObject); 
	strNetDomainName.init(this,_T("strNetDomainName"),0,pOutObject); 
	nNetDomainPort.init(this,_T("nNetDomainPort"),0,pOutObject); 
	strWSDLUrl.init(this,_T("strWSDLUrl"),0,pOutObject); 
	strRunDirectory.init(this,_T("strRunDirectory"),0,pOutObject); 
	strLocalSystemDirectory.init(this,_T("strLocalSystemDirectory"),0,pOutObject); 
	nSoapTimeout.init(this,_T("nSoapTimeout"),0,pOutObject); 
	nCheckCycle.init(this,_T("nCheckCycle"),0,pOutObject); 
	szDebugLevel.init(this,_T("szDebugLevel"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagYDConfig::SetData(_tagYDConfig & _X)
{
	strRuleVer=_X.strRuleVer; 
	strNetDomainName=_X.strNetDomainName; 
	nNetDomainPort=_X.nNetDomainPort; 
	strWSDLUrl=_X.strWSDLUrl; 
	strRunDirectory=_X.strRunDirectory; 
	strLocalSystemDirectory=_X.strLocalSystemDirectory; 
	nSoapTimeout=_X.nSoapTimeout; 
	nCheckCycle=_X.nCheckCycle; 
	szDebugLevel=_X.szDebugLevel;
}

BOOL Serialize__tagYDConfig::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("strRuleVer")))
	{
		*RetObj=&strRuleVer;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("strNetDomainName")))
	{
		*RetObj=&strNetDomainName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nNetDomainPort")))
	{
		*RetObj=&nNetDomainPort;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("strWSDLUrl")))
	{
		*RetObj=&strWSDLUrl;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("strRunDirectory")))
	{
		*RetObj=&strRunDirectory;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("strLocalSystemDirectory")))
	{
		*RetObj=&strLocalSystemDirectory;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nSoapTimeout")))
	{
		*RetObj=&nSoapTimeout;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nCheckCycle")))
	{
		*RetObj=&nCheckCycle;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szDebugLevel")))
	{
		*RetObj=&szDebugLevel;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagYDConfig::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagYDConfig"),this);

	strRuleVer.Save(pStorageObject); 
	strNetDomainName.Save(pStorageObject); 
	nNetDomainPort.Save(pStorageObject); 
	strWSDLUrl.Save(pStorageObject); 
	strRunDirectory.Save(pStorageObject); 
	strLocalSystemDirectory.Save(pStorageObject); 
	nSoapTimeout.Save(pStorageObject); 
	nCheckCycle.Save(pStorageObject); 
	szDebugLevel.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagYDConfig"),this);
	return TRUE;
}

BOOL Serialize__tagYDConfig::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&strRuleVer); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&strNetDomainName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nNetDomainPort); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&strWSDLUrl); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&strRunDirectory); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&strLocalSystemDirectory); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nSoapTimeout); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nCheckCycle); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szDebugLevel);
	return TRUE;
}




