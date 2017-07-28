 #pragma once
#include "Serialize.h"

class Serialize__tagFileDirectoryRule : public Serialize_StructBase<_tagFileDirectoryRule,Serialize__tagFileDirectoryRule>
{
	public:
	typedef _tagFileDirectoryRule _MyObjectType;
 
	Serialize_BaseObject<tstring> RuleID; 
	Serialize_BaseObject<tstring> DirectoryName; 
	Serialize_BaseObject<tstring> FileDirectoryPath;

 	Serialize__tagFileDirectoryRule(){};
	~Serialize__tagFileDirectoryRule(){};
 	_Myt& operator=(_tagFileDirectoryRule & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.RuleID=RuleID; 
		m_Val.DirectoryName=DirectoryName; 
		m_Val.FileDirectoryPath=FileDirectoryPath;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		RuleID.init(this,_T("RuleID"),0,pOutObject); 
		DirectoryName.init(this,_T("DirectoryName"),0,pOutObject); 
		FileDirectoryPath.init(this,_T("FileDirectoryPath"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagFileDirectoryRule & _X)
	{
		RuleID=_X.RuleID; 
		DirectoryName=_X.DirectoryName; 
		FileDirectoryPath=_X.FileDirectoryPath;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("RuleID")))
		{
			*RetObj=&RuleID;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("DirectoryName")))
		{
			*RetObj=&DirectoryName;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("FileDirectoryPath")))
		{
			*RetObj=&FileDirectoryPath;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagFileDirectoryRule"),this);

		RuleID.Save(pStorageObject); 
		DirectoryName.Save(pStorageObject); 
		FileDirectoryPath.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagFileDirectoryRule"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&RuleID); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&DirectoryName); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&FileDirectoryPath);
		return TRUE;
	}
 

};
