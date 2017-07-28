 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagMachineCheckStandardTypeLib_StructInfo.h"

Serialize__tagMachineCheckStandardTypeLib::_Myt& Serialize__tagMachineCheckStandardTypeLib::operator=(_tagMachineCheckStandardTypeLib & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagMachineCheckStandardTypeLib::GetData()
{
	m_Val.libmap=libmap;
}

BOOL Serialize__tagMachineCheckStandardTypeLib::Construct(StorageObjectInterface * pOutObject)
{
	libmap.init(this,_T("libmap"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagMachineCheckStandardTypeLib::SetData(_tagMachineCheckStandardTypeLib & _X)
{
	libmap=_X.libmap;
}

BOOL Serialize__tagMachineCheckStandardTypeLib::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("libmap")))
	{
		*RetObj=&libmap;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagMachineCheckStandardTypeLib::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagMachineCheckStandardTypeLib"),this);

	libmap.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagMachineCheckStandardTypeLib"),this);
	return TRUE;
}

BOOL Serialize__tagMachineCheckStandardTypeLib::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&libmap);
	return TRUE;
}




