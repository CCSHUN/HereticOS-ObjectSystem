 #pragma once
#include "Serialize.h"

class Serialize__tagProcessNameFilter : public Serialize_StructBase<_tagProcessNameFilter,Serialize__tagProcessNameFilter>
{
	public:
	typedef _tagProcessNameFilter _MyObjectType;
 
	Serialize_BaseObject<tstring> RuleID; 
	Serialize_BaseObject<tstring> FilterRule; 
	Serialize_BaseObject<tstring> ProcessName;

 	Serialize__tagProcessNameFilter(){};
	~Serialize__tagProcessNameFilter(){};
 	_Myt& operator=(_tagProcessNameFilter & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.RuleID=RuleID; 
		m_Val.FilterRule=FilterRule; 
		m_Val.ProcessName=ProcessName;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		RuleID.init(this,_T("RuleID"),0,pOutObject); 
		FilterRule.init(this,_T("FilterRule"),0,pOutObject); 
		ProcessName.init(this,_T("ProcessName"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagProcessNameFilter & _X)
	{
		RuleID=_X.RuleID; 
		FilterRule=_X.FilterRule; 
		ProcessName=_X.ProcessName;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("RuleID")))
		{
			*RetObj=&RuleID;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("FilterRule")))
		{
			*RetObj=&FilterRule;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ProcessName")))
		{
			*RetObj=&ProcessName;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagProcessNameFilter"),this);

		RuleID.Save(pStorageObject); 
		FilterRule.Save(pStorageObject); 
		ProcessName.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagProcessNameFilter"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&RuleID); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&FilterRule); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ProcessName);
		return TRUE;
	}
 

};
