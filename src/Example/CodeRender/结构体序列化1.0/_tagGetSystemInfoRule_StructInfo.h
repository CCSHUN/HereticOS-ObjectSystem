 #pragma once
#include "Serialize.h"

class Serialize__tagGetSystemInfoRule : public Serialize_StructBase<_tagGetSystemInfoRule,Serialize__tagGetSystemInfoRule>
{
	public:
	typedef _tagGetSystemInfoRule _MyObjectType;
 
	Serialize_BaseObject<int> GetSystemInfoRule;
 	Serialize__tagGetSystemInfoRule(){};
	~Serialize__tagGetSystemInfoRule(){};
 	_Myt& operator=(_tagGetSystemInfoRule & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.GetSystemInfoRule=GetSystemInfoRule;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		GetSystemInfoRule.init(this,_T("GetSystemInfoRule"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagGetSystemInfoRule & _X)
	{
		GetSystemInfoRule=_X.GetSystemInfoRule;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("GetSystemInfoRule")))
		{
			*RetObj=&GetSystemInfoRule;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagGetSystemInfoRule"),this);

		GetSystemInfoRule.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagGetSystemInfoRule"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&GetSystemInfoRule);
		return TRUE;
	}
 

};
