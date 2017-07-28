 #pragma once
#include "Serialize.h"

class Serialize__tagYDConfig : public Serialize_StructBase<_tagYDConfig,Serialize__tagYDConfig>
{
	public:
	typedef _tagYDConfig _MyObjectType;
 
	Serialize_BaseObject<tstring> strRuleVer; 
	Serialize_BaseObject<tstring> strNetDomainName; 
	Serialize_BaseObject<int> nNetDomainPort; 
	Serialize_BaseObject<tstring> strWSDLUrl; 
	Serialize_BaseObject<tstring> strRunDirectory; 
	Serialize_BaseObject<int> nSoapTimeout; 
	Serialize_BaseObject<int> nCheckCycle;

 	Serialize__tagYDConfig(){};
	~Serialize__tagYDConfig(){};
 	_Myt& operator=(_tagYDConfig & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.strRuleVer=strRuleVer; 
		m_Val.strNetDomainName=strNetDomainName; 
		m_Val.nNetDomainPort=nNetDomainPort; 
		m_Val.strWSDLUrl=strWSDLUrl; 
		m_Val.strRunDirectory=strRunDirectory; 
		m_Val.nSoapTimeout=nSoapTimeout; 
		m_Val.nCheckCycle=nCheckCycle;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		strRuleVer.init(this,_T("strRuleVer"),0,pOutObject); 
		strNetDomainName.init(this,_T("strNetDomainName"),0,pOutObject); 
		nNetDomainPort.init(this,_T("nNetDomainPort"),0,pOutObject); 
		strWSDLUrl.init(this,_T("strWSDLUrl"),0,pOutObject); 
		strRunDirectory.init(this,_T("strRunDirectory"),0,pOutObject); 
		nSoapTimeout.init(this,_T("nSoapTimeout"),0,pOutObject); 
		nCheckCycle.init(this,_T("nCheckCycle"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagYDConfig & _X)
	{
		strRuleVer=_X.strRuleVer; 
		strNetDomainName=_X.strNetDomainName; 
		nNetDomainPort=_X.nNetDomainPort; 
		strWSDLUrl=_X.strWSDLUrl; 
		strRunDirectory=_X.strRunDirectory; 
		nSoapTimeout=_X.nSoapTimeout; 
		nCheckCycle=_X.nCheckCycle;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
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
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nSoapTimeout")))
		{
			*RetObj=&nSoapTimeout;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nCheckCycle")))
		{
			*RetObj=&nCheckCycle;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagYDConfig"),this);

		strRuleVer.Save(pStorageObject); 
		strNetDomainName.Save(pStorageObject); 
		nNetDomainPort.Save(pStorageObject); 
		strWSDLUrl.Save(pStorageObject); 
		strRunDirectory.Save(pStorageObject); 
		nSoapTimeout.Save(pStorageObject); 
		nCheckCycle.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagYDConfig"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&strRuleVer); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&strNetDomainName); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nNetDomainPort); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&strWSDLUrl); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&strRunDirectory); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nSoapTimeout); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nCheckCycle);
		return TRUE;
	}
 

};
