 #pragma once
#include "Serialize.h"

class Serialize__tagSafeLevelInfoAttributes : public Serialize_StructBase<_tagSafeLevelInfoAttributes,Serialize__tagSafeLevelInfoAttributes>
{
	public:
	typedef _tagSafeLevelInfoAttributes _MyObjectType;
 
	Serialize_BaseObject<tstring> type; 
	Serialize_BaseObject<tstring> Id;

 	Serialize__tagSafeLevelInfoAttributes(){};
	~Serialize__tagSafeLevelInfoAttributes(){};
 	_Myt& operator=(_tagSafeLevelInfoAttributes & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.type=type; 
		m_Val.Id=Id;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		type.init(this,_T("type"),0,pOutObject); 
		Id.init(this,_T("Id"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagSafeLevelInfoAttributes & _X)
	{
		type=_X.type; 
		Id=_X.Id;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("type")))
		{
			*RetObj=&type;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Id")))
		{
			*RetObj=&Id;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagSafeLevelInfoAttributes"),this);

		type.Save(pStorageObject); 
		Id.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagSafeLevelInfoAttributes"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&type); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&Id);
		return TRUE;
	}
 

};
