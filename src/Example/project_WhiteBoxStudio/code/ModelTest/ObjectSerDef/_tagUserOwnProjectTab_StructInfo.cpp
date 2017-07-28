 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagUserOwnProjectTab_StructInfo.h"

Serialize__tagUserOwnProjectTab::_Myt& Serialize__tagUserOwnProjectTab::operator=(_tagUserOwnProjectTab & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagUserOwnProjectTab::GetData()
{
	m_Val.OwnProjectArray=OwnProjectArray;
}

BOOL Serialize__tagUserOwnProjectTab::Construct(StorageObjectInterface * pOutObject)
{
	OwnProjectArray.init(this,_T("OwnProjectArray"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagUserOwnProjectTab::SetData(_tagUserOwnProjectTab & _X)
{
	OwnProjectArray=_X.OwnProjectArray;
}

BOOL Serialize__tagUserOwnProjectTab::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("OwnProjectArray")))
	{
		*RetObj=&OwnProjectArray;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagUserOwnProjectTab::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagUserOwnProjectTab"),this);

	OwnProjectArray.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagUserOwnProjectTab"),this);
	return TRUE;
}

BOOL Serialize__tagUserOwnProjectTab::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&OwnProjectArray);
	return TRUE;
}




