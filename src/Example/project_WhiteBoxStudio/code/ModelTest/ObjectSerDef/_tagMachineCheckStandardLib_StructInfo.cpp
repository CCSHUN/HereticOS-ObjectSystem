 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagMachineCheckStandardLib_StructInfo.h"

Serialize__tagMachineCheckStandardLib::_Myt& Serialize__tagMachineCheckStandardLib::operator=(_tagMachineCheckStandardLib & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagMachineCheckStandardLib::GetData()
{
	m_Val.libmap=libmap;
}

BOOL Serialize__tagMachineCheckStandardLib::Construct(StorageObjectInterface * pOutObject)
{
	libmap.init(this,_T("libmap"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagMachineCheckStandardLib::SetData(_tagMachineCheckStandardLib & _X)
{
	libmap=_X.libmap;
}

BOOL Serialize__tagMachineCheckStandardLib::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("libmap")))
	{
		*RetObj=&libmap;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagMachineCheckStandardLib::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagMachineCheckStandardLib"),this);

	libmap.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagMachineCheckStandardLib"),this);
	return TRUE;
}

BOOL Serialize__tagMachineCheckStandardLib::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&libmap);
	return TRUE;
}




