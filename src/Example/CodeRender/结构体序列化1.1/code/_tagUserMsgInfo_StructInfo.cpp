 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagUserMsgInfo_StructInfo.h"

Serialize__tagUserMsgInfo::_Myt& Serialize__tagUserMsgInfo::operator=(_tagUserMsgInfo & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagUserMsgInfo::GetData()
{
	m_Val.szBeginMsgTime=szBeginMsgTime; 
	m_Val.szEndMsgTime=szEndMsgTime; 
	m_Val.nMsgNum=nMsgNum; 
	m_Val.szNewMsgIndex=szNewMsgIndex;
}

BOOL Serialize__tagUserMsgInfo::Construct(StorageObjectInterface * pOutObject)
{
	szBeginMsgTime.init(this,_T("szBeginMsgTime"),0,pOutObject); 
	szEndMsgTime.init(this,_T("szEndMsgTime"),0,pOutObject); 
	nMsgNum.init(this,_T("nMsgNum"),0,pOutObject); 
	szNewMsgIndex.init(this,_T("szNewMsgIndex"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagUserMsgInfo::SetData(_tagUserMsgInfo & _X)
{
	szBeginMsgTime=_X.szBeginMsgTime; 
	szEndMsgTime=_X.szEndMsgTime; 
	nMsgNum=_X.nMsgNum; 
	szNewMsgIndex=_X.szNewMsgIndex;
}

BOOL Serialize__tagUserMsgInfo::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szBeginMsgTime")))
	{
		*RetObj=&szBeginMsgTime;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szEndMsgTime")))
	{
		*RetObj=&szEndMsgTime;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nMsgNum")))
	{
		*RetObj=&nMsgNum;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szNewMsgIndex")))
	{
		*RetObj=&szNewMsgIndex;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagUserMsgInfo::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagUserMsgInfo"),this);

	szBeginMsgTime.Save(pStorageObject); 
	szEndMsgTime.Save(pStorageObject); 
	nMsgNum.Save(pStorageObject); 
	szNewMsgIndex.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagUserMsgInfo"),this);
	return TRUE;
}

BOOL Serialize__tagUserMsgInfo::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szBeginMsgTime); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szEndMsgTime); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nMsgNum); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szNewMsgIndex);
	return TRUE;
}




