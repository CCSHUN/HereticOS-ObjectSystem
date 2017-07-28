 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagMsgData_StructInfo.h"

Serialize__tagMsgData::_Myt& Serialize__tagMsgData::operator=(_tagMsgData & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagMsgData::GetData()
{
	m_Val.szType=szType; 
	m_Val.szData=szData;
}

BOOL Serialize__tagMsgData::Construct(StorageObjectInterface * pOutObject)
{
	szType.init(this,_T("szType"),0,pOutObject); 
	szData.init(this,_T("szData"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagMsgData::SetData(_tagMsgData & _X)
{
	szType=_X.szType; 
	szData=_X.szData;
}

BOOL Serialize__tagMsgData::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szType")))
	{
		*RetObj=&szType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szData")))
	{
		*RetObj=&szData;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagMsgData::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagMsgData"),this);

	szType.Save(pStorageObject); 
	szData.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagMsgData"),this);
	return TRUE;
}

BOOL Serialize__tagMsgData::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szData);
	return TRUE;
}




