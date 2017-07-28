 #pragma once
#include "Serialize.h"

class Serialize__tagLogonRet : public Serialize_StructBase<_tagLogonRet,Serialize__tagLogonRet>
{
	public:
	typedef _tagLogonRet _MyObjectType;
 
	Serialize_BaseObject<tstring> result; 
	Serialize_ObjectMapContainer<Serialize__tagLogonRetInfo ,Serialize_MapContainerSet> values;

 	Serialize__tagLogonRet(){};
	~Serialize__tagLogonRet(){};
 	_Myt& operator=(_tagLogonRet & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.result=result; 
		m_Val.values=values;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		result.init(this,_T("result"),0,pOutObject); 
		values.init(this,_T("values"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagLogonRet & _X)
	{
		result=_X.result; 
		values=_X.values;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("result")))
		{
			*RetObj=&result;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("values")))
		{
			*RetObj=&values;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagLogonRet"),this);

		result.Save(pStorageObject); 
		values.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagLogonRet"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&result); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&values);
		return TRUE;
	}
 

};
