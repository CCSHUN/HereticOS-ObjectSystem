 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagProjectState_StructInfo.h"

Serialize__tagProjectState::_Myt& Serialize__tagProjectState::operator=(_tagProjectState & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagProjectState::GetData()
{
	m_Val.szProjectState=szProjectState;
}

BOOL Serialize__tagProjectState::Construct(StorageObjectInterface * pOutObject)
{
	szProjectState.init(this,_T("szProjectState"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagProjectState::SetData(_tagProjectState & _X)
{
	szProjectState=_X.szProjectState;
}

BOOL Serialize__tagProjectState::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szProjectState")))
	{
		*RetObj=&szProjectState;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagProjectState::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagProjectState"),this);

	szProjectState.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagProjectState"),this);
	return TRUE;
}

BOOL Serialize__tagProjectState::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szProjectState);
	return TRUE;
}




