 #pragma once
#include "Serialize.h"

class Serialize__tagDomainProcessRule : public Serialize_StructBase<_tagDomainProcessRule,Serialize__tagDomainProcessRule>
{
	public:
	typedef _tagDomainProcessRule _MyObjectType;
 
	Serialize_BaseObject<tstring> ProcessName; 
	Serialize_BaseObject<SER_TO_X<unsigned int ,HexString>> nDomainVal;

 	Serialize__tagDomainProcessRule(){};
	~Serialize__tagDomainProcessRule(){};
 	_Myt& operator=(_tagDomainProcessRule & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.ProcessName=ProcessName; 
		m_Val.nDomainVal=nDomainVal;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		ProcessName.init(this,_T("ProcessName"),0,pOutObject); 
		nDomainVal.init(this,_T("nDomainVal"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagDomainProcessRule & _X)
	{
		ProcessName=_X.ProcessName; 
		nDomainVal=_X.nDomainVal;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ProcessName")))
		{
			*RetObj=&ProcessName;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nDomainVal")))
		{
			*RetObj=&nDomainVal;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagDomainProcessRule"),this);

		ProcessName.Save(pStorageObject); 
		nDomainVal.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagDomainProcessRule"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ProcessName); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nDomainVal);
		return TRUE;
	}
 

};
