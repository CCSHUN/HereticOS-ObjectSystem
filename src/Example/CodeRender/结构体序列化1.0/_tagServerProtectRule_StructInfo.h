 #pragma once
#include "Serialize.h"

class Serialize__tagServerProtectRule : public Serialize_StructBase<_tagServerProtectRule,Serialize__tagServerProtectRule>
{
	public:
	typedef _tagServerProtectRule _MyObjectType;
 
	Serialize_vector< Serialize__tagProcessProtectRule> ProcessProtectRule; 
	Serialize_vector< Serialize__tagFileDirectoryRule> FileDirectoryRule;

 	Serialize__tagServerProtectRule(){};
	~Serialize__tagServerProtectRule(){};
 	_Myt& operator=(_tagServerProtectRule & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.ProcessProtectRule=ProcessProtectRule; 
		m_Val.FileDirectoryRule=FileDirectoryRule;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		ProcessProtectRule.init(this,_T("ProcessProtectRule"),0,pOutObject); 
		FileDirectoryRule.init(this,_T("FileDirectoryRule"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagServerProtectRule & _X)
	{
		ProcessProtectRule=_X.ProcessProtectRule; 
		FileDirectoryRule=_X.FileDirectoryRule;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ProcessProtectRule")))
		{
			*RetObj=&ProcessProtectRule;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("FileDirectoryRule")))
		{
			*RetObj=&FileDirectoryRule;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagServerProtectRule"),this);

		ProcessProtectRule.Save(pStorageObject); 
		FileDirectoryRule.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagServerProtectRule"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ProcessProtectRule); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&FileDirectoryRule);
		return TRUE;
	}
 

};
