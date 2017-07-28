 #pragma once
#include "Serialize.h"

class Serialize__tagSendProcessInfoAuditMsg_ProcessInfo : public Serialize_StructBase<_tagSendProcessInfoAuditMsg_ProcessInfo,Serialize__tagSendProcessInfoAuditMsg_ProcessInfo>
{
	public:
	typedef _tagSendProcessInfoAuditMsg_ProcessInfo _MyObjectType;
 
	Serialize__tagProcessInfoAuditMsg ProcessInfo;
 	Serialize__tagSendProcessInfoAuditMsg_ProcessInfo(){};
	~Serialize__tagSendProcessInfoAuditMsg_ProcessInfo(){};
 	_Myt& operator=(_tagSendProcessInfoAuditMsg_ProcessInfo & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.ProcessInfo=ProcessInfo;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		ProcessInfo.init(this,_T("ProcessInfo"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagSendProcessInfoAuditMsg_ProcessInfo & _X)
	{
		ProcessInfo=_X.ProcessInfo;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ProcessInfo")))
		{
			*RetObj=&ProcessInfo;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagSendProcessInfoAuditMsg_ProcessInfo"),this);

		ProcessInfo.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagSendProcessInfoAuditMsg_ProcessInfo"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ProcessInfo);
		return TRUE;
	}
 

};
