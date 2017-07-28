 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagFlowerSlot_StructInfo.h"

Serialize__tagFlowerSlot::_Myt& Serialize__tagFlowerSlot::operator=(_tagFlowerSlot & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagFlowerSlot::GetData()
{
	m_Val.bOwn=bOwn; 
	m_Val.nFlowerTransportCount=nFlowerTransportCount; 
	m_Val.szLastLog=szLastLog;
}

BOOL Serialize__tagFlowerSlot::Construct(StorageObjectInterface * pOutObject)
{
	bOwn.init(this,_T("bOwn"),0,pOutObject); 
	nFlowerTransportCount.init(this,_T("nFlowerTransportCount"),0,pOutObject); 
	szLastLog.init(this,_T("szLastLog"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagFlowerSlot::SetData(_tagFlowerSlot & _X)
{
	bOwn=_X.bOwn; 
	nFlowerTransportCount=_X.nFlowerTransportCount; 
	szLastLog=_X.szLastLog;
}

BOOL Serialize__tagFlowerSlot::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("bOwn")))
	{
		*RetObj=&bOwn;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nFlowerTransportCount")))
	{
		*RetObj=&nFlowerTransportCount;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szLastLog")))
	{
		*RetObj=&szLastLog;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagFlowerSlot::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagFlowerSlot"),this);

	bOwn.Save(pStorageObject); 
	nFlowerTransportCount.Save(pStorageObject); 
	szLastLog.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagFlowerSlot"),this);
	return TRUE;
}

BOOL Serialize__tagFlowerSlot::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&bOwn); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nFlowerTransportCount); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szLastLog);
	return TRUE;
}




