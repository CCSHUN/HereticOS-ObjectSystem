 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagMangerBroadcast_StructInfo.h"

Serialize__tagMangerBroadcast::_Myt& Serialize__tagMangerBroadcast::operator=(_tagMangerBroadcast & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagMangerBroadcast::GetData()
{
	m_Val.nMsgType=nMsgType; 
	m_Val.szMsg=szMsg;
}

BOOL Serialize__tagMangerBroadcast::Construct(StorageObjectInterface * pOutObject)
{
	nMsgType.init(this,_T("nMsgType"),0,pOutObject); 
	szMsg.init(this,_T("szMsg"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagMangerBroadcast::SetData(_tagMangerBroadcast & _X)
{
	nMsgType=_X.nMsgType; 
	szMsg=_X.szMsg;
}

BOOL Serialize__tagMangerBroadcast::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nMsgType")))
	{
		*RetObj=&nMsgType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szMsg")))
	{
		*RetObj=&szMsg;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagMangerBroadcast::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagMangerBroadcast"),this);

	nMsgType.Save(pStorageObject); 
	szMsg.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagMangerBroadcast"),this);
	return TRUE;
}

BOOL Serialize__tagMangerBroadcast::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nMsgType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szMsg);
	return TRUE;
}




