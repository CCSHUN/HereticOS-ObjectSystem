 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagThirdStandardlib_StructInfo.h"

Serialize__tagThirdStandardlib::_Myt& Serialize__tagThirdStandardlib::operator=(_tagThirdStandardlib & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagThirdStandardlib::GetData()
{
	m_Val.libmap=libmap;
}

BOOL Serialize__tagThirdStandardlib::Construct(StorageObjectInterface * pOutObject)
{
	libmap.init(this,_T("libmap"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagThirdStandardlib::SetData(_tagThirdStandardlib & _X)
{
	libmap=_X.libmap;
}

BOOL Serialize__tagThirdStandardlib::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("libmap")))
	{
		*RetObj=&libmap;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagThirdStandardlib::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagThirdStandardlib"),this);

	libmap.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagThirdStandardlib"),this);
	return TRUE;
}

BOOL Serialize__tagThirdStandardlib::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&libmap);
	return TRUE;
}




