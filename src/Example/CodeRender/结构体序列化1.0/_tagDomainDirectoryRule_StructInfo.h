 #pragma once
#include "Serialize.h"

class Serialize__tagDomainDirectoryRule : public Serialize_StructBase<_tagDomainDirectoryRule,Serialize__tagDomainDirectoryRule>
{
	public:
	typedef _tagDomainDirectoryRule _MyObjectType;
 
	Serialize_BaseObject<tstring> DirectoryName; 
	Serialize_BaseObject<SER_TO_X<unsigned int ,HexString>> nDomainVal;

 	Serialize__tagDomainDirectoryRule(){};
	~Serialize__tagDomainDirectoryRule(){};
 	_Myt& operator=(_tagDomainDirectoryRule & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.DirectoryName=DirectoryName; 
		m_Val.nDomainVal=nDomainVal;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		DirectoryName.init(this,_T("DirectoryName"),0,pOutObject); 
		nDomainVal.init(this,_T("nDomainVal"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagDomainDirectoryRule & _X)
	{
		DirectoryName=_X.DirectoryName; 
		nDomainVal=_X.nDomainVal;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("DirectoryName")))
		{
			*RetObj=&DirectoryName;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nDomainVal")))
		{
			*RetObj=&nDomainVal;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagDomainDirectoryRule"),this);

		DirectoryName.Save(pStorageObject); 
		nDomainVal.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagDomainDirectoryRule"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&DirectoryName); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nDomainVal);
		return TRUE;
	}
 

};
