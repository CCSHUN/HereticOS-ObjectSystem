 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagNeedSlotRet_StructInfo.h"

Serialize__tagNeedSlotRet::_Myt& Serialize__tagNeedSlotRet::operator=(_tagNeedSlotRet & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagNeedSlotRet::GetData()
{
	m_Val.nNewSlot=nNewSlot;
}

BOOL Serialize__tagNeedSlotRet::Construct(StorageObjectInterface * pOutObject)
{
	nNewSlot.init(this,_T("nNewSlot"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagNeedSlotRet::SetData(_tagNeedSlotRet & _X)
{
	nNewSlot=_X.nNewSlot;
}

BOOL Serialize__tagNeedSlotRet::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nNewSlot")))
	{
		*RetObj=&nNewSlot;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagNeedSlotRet::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagNeedSlotRet"),this);

	nNewSlot.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagNeedSlotRet"),this);
	return TRUE;
}

BOOL Serialize__tagNeedSlotRet::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nNewSlot);
	return TRUE;
}




