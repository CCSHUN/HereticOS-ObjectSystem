 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagNeedSlot_StructInfo.h"

Serialize__tagNeedSlot::_Myt& Serialize__tagNeedSlot::operator=(_tagNeedSlot & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagNeedSlot::GetData()
{
	m_Val.szUserSession=szUserSession;
}

BOOL Serialize__tagNeedSlot::Construct(StorageObjectInterface * pOutObject)
{
	szUserSession.init(this,_T("szUserSession"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagNeedSlot::SetData(_tagNeedSlot & _X)
{
	szUserSession=_X.szUserSession;
}

BOOL Serialize__tagNeedSlot::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szUserSession")))
	{
		*RetObj=&szUserSession;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagNeedSlot::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagNeedSlot"),this);

	szUserSession.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagNeedSlot"),this);
	return TRUE;
}

BOOL Serialize__tagNeedSlot::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szUserSession);
	return TRUE;
}




