 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagProjectOwnUser_StructInfo.h"

Serialize__tagProjectOwnUser::_Myt& Serialize__tagProjectOwnUser::operator=(_tagProjectOwnUser & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagProjectOwnUser::GetData()
{
	m_Val.OwnUserMap=OwnUserMap;
}

BOOL Serialize__tagProjectOwnUser::Construct(StorageObjectInterface * pOutObject)
{
	OwnUserMap.init(this,_T("OwnUserMap"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagProjectOwnUser::SetData(_tagProjectOwnUser & _X)
{
	OwnUserMap=_X.OwnUserMap;
}

BOOL Serialize__tagProjectOwnUser::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("OwnUserMap")))
	{
		*RetObj=&OwnUserMap;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagProjectOwnUser::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagProjectOwnUser"),this);

	OwnUserMap.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagProjectOwnUser"),this);
	return TRUE;
}

BOOL Serialize__tagProjectOwnUser::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&OwnUserMap);
	return TRUE;
}




