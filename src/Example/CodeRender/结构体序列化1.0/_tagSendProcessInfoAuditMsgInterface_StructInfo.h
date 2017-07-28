 #pragma once
#include "Serialize.h"

class Serialize__tagSendProcessInfoAuditMsgInterface : public Serialize_StructBase<_tagSendProcessInfoAuditMsgInterface,Serialize__tagSendProcessInfoAuditMsgInterface>
{
	public:
	typedef _tagSendProcessInfoAuditMsgInterface _MyObjectType;
 
	Serialize__tagSendProcessInfoAuditMsg_ProcessInfo SendProcessInfoAuditMsg;
 	Serialize__tagSendProcessInfoAuditMsgInterface(){};
	~Serialize__tagSendProcessInfoAuditMsgInterface(){};
 	_Myt& operator=(_tagSendProcessInfoAuditMsgInterface & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.SendProcessInfoAuditMsg=SendProcessInfoAuditMsg;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		SendProcessInfoAuditMsg.init(this,_T("SendProcessInfoAuditMsg"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagSendProcessInfoAuditMsgInterface & _X)
	{
		SendProcessInfoAuditMsg=_X.SendProcessInfoAuditMsg;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("SendProcessInfoAuditMsg")))
		{
			*RetObj=&SendProcessInfoAuditMsg;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagSendProcessInfoAuditMsgInterface"),this);

		SendProcessInfoAuditMsg.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagSendProcessInfoAuditMsgInterface"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&SendProcessInfoAuditMsg);
		return TRUE;
	}
 

};
