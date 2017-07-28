 #pragma once
#include "Serialize.h"

class Serialize__tagProcessInfoAuditFieldValveRule : public Serialize_StructBase<_tagProcessInfoAuditFieldValveRule,Serialize__tagProcessInfoAuditFieldValveRule>
{
	public:
	typedef _tagProcessInfoAuditFieldValveRule _MyObjectType;
 
	Serialize_BaseObject<tstring> RuleID; 
	Serialize_BaseObject<tstring> FiledName; 
	Serialize_BaseObject<tstring> ValveType; 
	Serialize_BaseObject<__int64> FiledValve;

 	Serialize__tagProcessInfoAuditFieldValveRule(){};
	~Serialize__tagProcessInfoAuditFieldValveRule(){};
 	_Myt& operator=(_tagProcessInfoAuditFieldValveRule & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.RuleID=RuleID; 
		m_Val.FiledName=FiledName; 
		m_Val.ValveType=ValveType; 
		m_Val.FiledValve=FiledValve;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		RuleID.init(this,_T("RuleID"),0,pOutObject); 
		FiledName.init(this,_T("FiledName"),0,pOutObject); 
		ValveType.init(this,_T("ValveType"),0,pOutObject); 
		FiledValve.init(this,_T("FiledValve"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagProcessInfoAuditFieldValveRule & _X)
	{
		RuleID=_X.RuleID; 
		FiledName=_X.FiledName; 
		ValveType=_X.ValveType; 
		FiledValve=_X.FiledValve;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("RuleID")))
		{
			*RetObj=&RuleID;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("FiledName")))
		{
			*RetObj=&FiledName;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ValveType")))
		{
			*RetObj=&ValveType;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("FiledValve")))
		{
			*RetObj=&FiledValve;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagProcessInfoAuditFieldValveRule"),this);

		RuleID.Save(pStorageObject); 
		FiledName.Save(pStorageObject); 
		ValveType.Save(pStorageObject); 
		FiledValve.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagProcessInfoAuditFieldValveRule"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&RuleID); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&FiledName); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ValveType); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&FiledValve);
		return TRUE;
	}
 

};
