 #pragma once
#include "Serialize.h"

class Serialize__tagProcessProtectRule : public Serialize_StructBase<_tagProcessProtectRule,Serialize__tagProcessProtectRule>
{
	public:
	typedef _tagProcessProtectRule _MyObjectType;
 
	Serialize_BaseObject<tstring> RuleID; 
	Serialize_BaseObject<tstring> ProcessName; 
	Serialize_BaseObject<tstring> DirectoryName;

 	Serialize__tagProcessProtectRule(){};
	~Serialize__tagProcessProtectRule(){};
 	_Myt& operator=(_tagProcessProtectRule & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.RuleID=RuleID; 
		m_Val.ProcessName=ProcessName; 
		m_Val.DirectoryName=DirectoryName;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		RuleID.init(this,_T("RuleID"),0,pOutObject); 
		ProcessName.init(this,_T("ProcessName"),0,pOutObject); 
		DirectoryName.init(this,_T("DirectoryName"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagProcessProtectRule & _X)
	{
		RuleID=_X.RuleID; 
		ProcessName=_X.ProcessName; 
		DirectoryName=_X.DirectoryName;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("RuleID")))
		{
			*RetObj=&RuleID;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ProcessName")))
		{
			*RetObj=&ProcessName;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("DirectoryName")))
		{
			*RetObj=&DirectoryName;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagProcessProtectRule"),this);

		RuleID.Save(pStorageObject); 
		ProcessName.Save(pStorageObject); 
		DirectoryName.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagProcessProtectRule"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&RuleID); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ProcessName); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&DirectoryName);
		return TRUE;
	}
 

};
