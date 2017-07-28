 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagstrParameter_StructInfo.h"

Serialize__tagstrParameter::_Myt& Serialize__tagstrParameter::operator=(_tagstrParameter & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagstrParameter::GetData()
{
	m_Val.szData=szData;
}

BOOL Serialize__tagstrParameter::Construct(StorageObjectInterface * pOutObject)
{
	szData.init(this,_T("szData"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagstrParameter::SetData(_tagstrParameter & _X)
{
	szData=_X.szData;
}

BOOL Serialize__tagstrParameter::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szData")))
	{
		*RetObj=&szData;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagstrParameter::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagstrParameter"),this);

	szData.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagstrParameter"),this);
	return TRUE;
}

BOOL Serialize__tagstrParameter::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szData);
	return TRUE;
}




