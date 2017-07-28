 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagErrorWarningArray_StructInfo.h"

Serialize__tagErrorWarningArray::_Myt& Serialize__tagErrorWarningArray::operator=(_tagErrorWarningArray & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagErrorWarningArray::GetData()
{
	m_Val.WarningArray=WarningArray;
}

BOOL Serialize__tagErrorWarningArray::Construct(StorageObjectInterface * pOutObject)
{
	WarningArray.init(this,_T("WarningArray"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagErrorWarningArray::SetData(_tagErrorWarningArray & _X)
{
	WarningArray=_X.WarningArray;
}

BOOL Serialize__tagErrorWarningArray::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("WarningArray")))
	{
		*RetObj=&WarningArray;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagErrorWarningArray::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagErrorWarningArray"),this);

	WarningArray.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagErrorWarningArray"),this);
	return TRUE;
}

BOOL Serialize__tagErrorWarningArray::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&WarningArray);
	return TRUE;
}




