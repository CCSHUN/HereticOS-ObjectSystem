 #pragma once
#include "Serialize.h"

class Serialize__tagGetUpdataInterface : public Serialize_StructBase<_tagGetUpdataInterface,Serialize__tagGetUpdataInterface>
{
	public:
	typedef _tagGetUpdataInterface _MyObjectType;
 
	Serialize_BaseObject<tstring> IsNeedUpDataRule;
 	Serialize__tagGetUpdataInterface(){};
	~Serialize__tagGetUpdataInterface(){};
 	_Myt& operator=(_tagGetUpdataInterface & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.IsNeedUpDataRule=IsNeedUpDataRule;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		IsNeedUpDataRule.init(this,_T("IsNeedUpDataRule"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagGetUpdataInterface & _X)
	{
		IsNeedUpDataRule=_X.IsNeedUpDataRule;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("IsNeedUpDataRule")))
		{
			*RetObj=&IsNeedUpDataRule;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagGetUpdataInterface"),this);

		IsNeedUpDataRule.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagGetUpdataInterface"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&IsNeedUpDataRule);
		return TRUE;
	}
 

};
