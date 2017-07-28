 #pragma once
#include "Serialize.h"

class Serialize__tagGetServerProtectRule : public Serialize_StructBase<_tagGetServerProtectRule,Serialize__tagGetServerProtectRule>
{
	public:
	typedef _tagGetServerProtectRule _MyObjectType;
 
	Serialize_BaseObject<int> GetServerProtectRule;
 	Serialize__tagGetServerProtectRule(){};
	~Serialize__tagGetServerProtectRule(){};
 	_Myt& operator=(_tagGetServerProtectRule & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.GetServerProtectRule=GetServerProtectRule;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		GetServerProtectRule.init(this,_T("GetServerProtectRule"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagGetServerProtectRule & _X)
	{
		GetServerProtectRule=_X.GetServerProtectRule;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("GetServerProtectRule")))
		{
			*RetObj=&GetServerProtectRule;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagGetServerProtectRule"),this);

		GetServerProtectRule.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagGetServerProtectRule"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&GetServerProtectRule);
		return TRUE;
	}
 

};
