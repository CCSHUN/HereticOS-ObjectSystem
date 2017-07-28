 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagObjectSystemEvent_StructInfo.h"

Serialize__tagObjectSystemEvent::_Myt& Serialize__tagObjectSystemEvent::operator=(_tagObjectSystemEvent & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagObjectSystemEvent::GetData()
{
	m_Val.szObjectAddress=szObjectAddress; 
	m_Val.nEventType=nEventType;
}

BOOL Serialize__tagObjectSystemEvent::Construct(StorageObjectInterface * pOutObject)
{
	szObjectAddress.init(this,_T("szObjectAddress"),0,pOutObject); 
	nEventType.init(this,_T("nEventType"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagObjectSystemEvent::SetData(_tagObjectSystemEvent & _X)
{
	szObjectAddress=_X.szObjectAddress; 
	nEventType=_X.nEventType;
}

BOOL Serialize__tagObjectSystemEvent::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szObjectAddress")))
	{
		*RetObj=&szObjectAddress;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nEventType")))
	{
		*RetObj=&nEventType;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagObjectSystemEvent::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagObjectSystemEvent"),this);

	szObjectAddress.Save(pStorageObject); 
	nEventType.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagObjectSystemEvent"),this);
	return TRUE;
}

BOOL Serialize__tagObjectSystemEvent::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szObjectAddress); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nEventType);
	return TRUE;
}




