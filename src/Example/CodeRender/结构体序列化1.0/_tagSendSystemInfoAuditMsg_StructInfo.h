 #pragma once
#include "Serialize.h"

class Serialize__tagSendSystemInfoAuditMsg : public Serialize_StructBase<_tagSendSystemInfoAuditMsg,Serialize__tagSendSystemInfoAuditMsg>
{
	public:
	typedef _tagSendSystemInfoAuditMsg _MyObjectType;
 
	Serialize__tagSystemInfoAuditMsg SystemInfo;
 	Serialize__tagSendSystemInfoAuditMsg(){};
	~Serialize__tagSendSystemInfoAuditMsg(){};
 	_Myt& operator=(_tagSendSystemInfoAuditMsg & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.SystemInfo=SystemInfo;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		SystemInfo.init(this,_T("SystemInfo"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagSendSystemInfoAuditMsg & _X)
	{
		SystemInfo=_X.SystemInfo;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("SystemInfo")))
		{
			*RetObj=&SystemInfo;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagSendSystemInfoAuditMsg"),this);

		SystemInfo.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagSendSystemInfoAuditMsg"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&SystemInfo);
		return TRUE;
	}
 

};
