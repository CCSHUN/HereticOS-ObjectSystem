 #pragma once
#include "Serialize.h"

class Serialize__tagServerInfoRule : public Serialize_StructBase<_tagServerInfoRule,Serialize__tagServerInfoRule>
{
	public:
	typedef _tagServerInfoRule _MyObjectType;
 
	Serialize__tagSystemInfoAuditRule SystemInfoAuditRule; 
	Serialize_vector< Serialize__tagSystemInfoAuditFieldValveRule> SystemInfoAuditFieldValveRule; 
	Serialize_vector< Serialize__tagProcessInfoAuditRule> ProcessInfoAuditRule; 
	Serialize_vector< Serialize__tagProcessInfoAuditFieldValveRule> ProcessInfoAuditFieldValveRule; 
	Serialize_vector< Serialize__tagProcessNameFilter> ProcessNameFilter; 
	Serialize_vector< Serialize__tagProcessExeMD5Filter> ProcessExeMD5Filter;

 	Serialize__tagServerInfoRule(){};
	~Serialize__tagServerInfoRule(){};
 	_Myt& operator=(_tagServerInfoRule & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.SystemInfoAuditRule=SystemInfoAuditRule; 
		m_Val.SystemInfoAuditFieldValveRule=SystemInfoAuditFieldValveRule; 
		m_Val.ProcessInfoAuditRule=ProcessInfoAuditRule; 
		m_Val.ProcessInfoAuditFieldValveRule=ProcessInfoAuditFieldValveRule; 
		m_Val.ProcessNameFilter=ProcessNameFilter; 
		m_Val.ProcessExeMD5Filter=ProcessExeMD5Filter;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		SystemInfoAuditRule.init(this,_T("SystemInfoAuditRule"),0,pOutObject); 
		SystemInfoAuditFieldValveRule.init(this,_T("SystemInfoAuditFieldValveRule"),0,pOutObject); 
		ProcessInfoAuditRule.init(this,_T("ProcessInfoAuditRule"),0,pOutObject); 
		ProcessInfoAuditFieldValveRule.init(this,_T("ProcessInfoAuditFieldValveRule"),0,pOutObject); 
		ProcessNameFilter.init(this,_T("ProcessNameFilter"),0,pOutObject); 
		ProcessExeMD5Filter.init(this,_T("ProcessExeMD5Filter"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagServerInfoRule & _X)
	{
		SystemInfoAuditRule=_X.SystemInfoAuditRule; 
		SystemInfoAuditFieldValveRule=_X.SystemInfoAuditFieldValveRule; 
		ProcessInfoAuditRule=_X.ProcessInfoAuditRule; 
		ProcessInfoAuditFieldValveRule=_X.ProcessInfoAuditFieldValveRule; 
		ProcessNameFilter=_X.ProcessNameFilter; 
		ProcessExeMD5Filter=_X.ProcessExeMD5Filter;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("SystemInfoAuditRule")))
		{
			*RetObj=&SystemInfoAuditRule;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("SystemInfoAuditFieldValveRule")))
		{
			*RetObj=&SystemInfoAuditFieldValveRule;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ProcessInfoAuditRule")))
		{
			*RetObj=&ProcessInfoAuditRule;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ProcessInfoAuditFieldValveRule")))
		{
			*RetObj=&ProcessInfoAuditFieldValveRule;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ProcessNameFilter")))
		{
			*RetObj=&ProcessNameFilter;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ProcessExeMD5Filter")))
		{
			*RetObj=&ProcessExeMD5Filter;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagServerInfoRule"),this);

		SystemInfoAuditRule.Save(pStorageObject); 
		SystemInfoAuditFieldValveRule.Save(pStorageObject); 
		ProcessInfoAuditRule.Save(pStorageObject); 
		ProcessInfoAuditFieldValveRule.Save(pStorageObject); 
		ProcessNameFilter.Save(pStorageObject); 
		ProcessExeMD5Filter.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagServerInfoRule"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&SystemInfoAuditRule); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&SystemInfoAuditFieldValveRule); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ProcessInfoAuditRule); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ProcessInfoAuditFieldValveRule); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ProcessNameFilter); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ProcessExeMD5Filter);
		return TRUE;
	}
 

};
