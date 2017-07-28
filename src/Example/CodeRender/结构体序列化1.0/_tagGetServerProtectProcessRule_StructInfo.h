 #pragma once
#include "Serialize.h"

class Serialize__tagGetServerProtectProcessRule : public Serialize_StructBase<_tagGetServerProtectProcessRule,Serialize__tagGetServerProtectProcessRule>
{
	public:
	typedef _tagGetServerProtectProcessRule _MyObjectType;
 
	Serialize_BaseObject<int> GetServerProtectProcessRule;
 	Serialize__tagGetServerProtectProcessRule(){};
	~Serialize__tagGetServerProtectProcessRule(){};
 	_Myt& operator=(_tagGetServerProtectProcessRule & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.GetServerProtectProcessRule=GetServerProtectProcessRule;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		GetServerProtectProcessRule.init(this,_T("GetServerProtectProcessRule"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagGetServerProtectProcessRule & _X)
	{
		GetServerProtectProcessRule=_X.GetServerProtectProcessRule;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("GetServerProtectProcessRule")))
		{
			*RetObj=&GetServerProtectProcessRule;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagGetServerProtectProcessRule"),this);

		GetServerProtectProcessRule.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagGetServerProtectProcessRule"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&GetServerProtectProcessRule);
		return TRUE;
	}
 

};
