 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagMsgBody_StructInfo.h"

Serialize__tagMsgBody::_Myt& Serialize__tagMsgBody::operator=(_tagMsgBody & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagMsgBody::GetData()
{
	m_Val.szSenderUser=szSenderUser; 
	m_Val.szSendDate=szSendDate; 
	m_Val.szTitle=szTitle; 
	m_Val.szRecvUserList=szRecvUserList; 
	m_Val.tagMsgAppend=tagMsgAppend; 
	m_Val.szMsgData=szMsgData;
}

BOOL Serialize__tagMsgBody::Construct(StorageObjectInterface * pOutObject)
{
	szSenderUser.init(this,_T("szSenderUser"),0,pOutObject); 
	szSendDate.init(this,_T("szSendDate"),0,pOutObject); 
	szTitle.init(this,_T("szTitle"),0,pOutObject); 
	szRecvUserList.init(this,_T("szRecvUserList"),0,pOutObject); 
	tagMsgAppend.init(this,_T("tagMsgAppend"),0,pOutObject); 
	szMsgData.init(this,_T("szMsgData"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagMsgBody::SetData(_tagMsgBody & _X)
{
	szSenderUser=_X.szSenderUser; 
	szSendDate=_X.szSendDate; 
	szTitle=_X.szTitle; 
	szRecvUserList=_X.szRecvUserList; 
	tagMsgAppend=_X.tagMsgAppend; 
	szMsgData=_X.szMsgData;
}

BOOL Serialize__tagMsgBody::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szSenderUser")))
	{
		*RetObj=&szSenderUser;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szSendDate")))
	{
		*RetObj=&szSendDate;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szTitle")))
	{
		*RetObj=&szTitle;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szRecvUserList")))
	{
		*RetObj=&szRecvUserList;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("tagMsgAppend")))
	{
		*RetObj=&tagMsgAppend;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szMsgData")))
	{
		*RetObj=&szMsgData;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagMsgBody::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagMsgBody"),this);

	szSenderUser.Save(pStorageObject); 
	szSendDate.Save(pStorageObject); 
	szTitle.Save(pStorageObject); 
	szRecvUserList.Save(pStorageObject); 
	tagMsgAppend.Save(pStorageObject); 
	szMsgData.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagMsgBody"),this);
	return TRUE;
}

BOOL Serialize__tagMsgBody::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szSenderUser); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szSendDate); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szTitle); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szRecvUserList); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&tagMsgAppend); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szMsgData);
	return TRUE;
}




