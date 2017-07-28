 #pragma once
#include "Serialize.h"

class Serialize__tagSendProtectProcessInfoAuditMsgInterface : public Serialize_StructBase<_tagSendProtectProcessInfoAuditMsgInterface,Serialize__tagSendProtectProcessInfoAuditMsgInterface>
{
	public:
	typedef _tagSendProtectProcessInfoAuditMsgInterface _MyObjectType;
 
	Serialize__tagSendProcessInfoAuditMsg_ProcessInfo SendProtectProcessInfoAuditMsg;
 	Serialize__tagSendProtectProcessInfoAuditMsgInterface(){};
	~Serialize__tagSendProtectProcessInfoAuditMsgInterface(){};
 	_Myt& operator=(_tagSendProtectProcessInfoAuditMsgInterface & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.SendProtectProcessInfoAuditMsg=SendProtectProcessInfoAuditMsg;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		SendProtectProcessInfoAuditMsg.init(this,_T("SendProtectProcessInfoAuditMsg"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagSendProtectProcessInfoAuditMsgInterface & _X)
	{
		SendProtectProcessInfoAuditMsg=_X.SendProtectProcessInfoAuditMsg;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("SendProtectProcessInfoAuditMsg")))
		{
			*RetObj=&SendProtectProcessInfoAuditMsg;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagSendProtectProcessInfoAuditMsgInterface"),this);

		SendProtectProcessInfoAuditMsg.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagSendProtectProcessInfoAuditMsgInterface"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&SendProtectProcessInfoAuditMsg);
		return TRUE;
	}
 

};
