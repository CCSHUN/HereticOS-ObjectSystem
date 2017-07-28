 #pragma once
#include "Serialize.h"

class Serialize__tagDomainRule : public Serialize_StructBase<_tagDomainRule,Serialize__tagDomainRule>
{
	public:
	typedef _tagDomainRule _MyObjectType;
 
	Serialize_BaseObject<SER_TO_X<unsigned int ,HexString>> nMaskVal; 
	Serialize_vector< Serialize__tagDomainProcessRule> ProcessRule; 
	Serialize_vector< Serialize__tagDomainDirectoryRule> DirectoryRule;

 	Serialize__tagDomainRule(){};
	~Serialize__tagDomainRule(){};
 	_Myt& operator=(_tagDomainRule & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.nMaskVal=nMaskVal; 
		m_Val.ProcessRule=ProcessRule; 
		m_Val.DirectoryRule=DirectoryRule;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		nMaskVal.init(this,_T("nMaskVal"),0,pOutObject); 
		ProcessRule.init(this,_T("ProcessRule"),0,pOutObject); 
		DirectoryRule.init(this,_T("DirectoryRule"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagDomainRule & _X)
	{
		nMaskVal=_X.nMaskVal; 
		ProcessRule=_X.ProcessRule; 
		DirectoryRule=_X.DirectoryRule;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nMaskVal")))
		{
			*RetObj=&nMaskVal;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ProcessRule")))
		{
			*RetObj=&ProcessRule;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("DirectoryRule")))
		{
			*RetObj=&DirectoryRule;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagDomainRule"),this);

		nMaskVal.Save(pStorageObject); 
		ProcessRule.Save(pStorageObject); 
		DirectoryRule.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagDomainRule"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nMaskVal); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ProcessRule); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&DirectoryRule);
		return TRUE;
	}
 

};
