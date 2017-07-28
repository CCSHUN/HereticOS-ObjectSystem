 #pragma once
#include "Serialize.h"

class Serialize__tagSendSystemInfoAuditMsgInterface : public Serialize_StructBase<_tagSendSystemInfoAuditMsgInterface,Serialize__tagSendSystemInfoAuditMsgInterface>
{
	public:
	typedef _tagSendSystemInfoAuditMsgInterface _MyObjectType;
 
	Serialize__tagSendSystemInfoAuditMsg SendSystemInfoAuditMsg;
 	Serialize__tagSendSystemInfoAuditMsgInterface(){};
	~Serialize__tagSendSystemInfoAuditMsgInterface(){};
 	_Myt& operator=(_tagSendSystemInfoAuditMsgInterface & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.SendSystemInfoAuditMsg=SendSystemInfoAuditMsg;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		SendSystemInfoAuditMsg.init(this,_T("SendSystemInfoAuditMsg"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagSendSystemInfoAuditMsgInterface & _X)
	{
		SendSystemInfoAuditMsg=_X.SendSystemInfoAuditMsg;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("SendSystemInfoAuditMsg")))
		{
			*RetObj=&SendSystemInfoAuditMsg;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagSendSystemInfoAuditMsgInterface"),this);

		SendSystemInfoAuditMsg.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagSendSystemInfoAuditMsgInterface"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&SendSystemInfoAuditMsg);
		return TRUE;
	}
 

};
