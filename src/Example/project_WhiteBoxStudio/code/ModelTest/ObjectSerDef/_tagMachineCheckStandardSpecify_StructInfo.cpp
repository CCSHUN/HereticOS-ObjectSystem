 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagMachineCheckStandardSpecify_StructInfo.h"

Serialize__tagMachineCheckStandardSpecify::_Myt& Serialize__tagMachineCheckStandardSpecify::operator=(_tagMachineCheckStandardSpecify & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagMachineCheckStandardSpecify::GetData()
{
	m_Val.szMachineCheckStandardSpecify=szMachineCheckStandardSpecify;
}

BOOL Serialize__tagMachineCheckStandardSpecify::Construct(StorageObjectInterface * pOutObject)
{
	szMachineCheckStandardSpecify.init(this,_T("szMachineCheckStandardSpecify"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagMachineCheckStandardSpecify::SetData(_tagMachineCheckStandardSpecify & _X)
{
	szMachineCheckStandardSpecify=_X.szMachineCheckStandardSpecify;
}

BOOL Serialize__tagMachineCheckStandardSpecify::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szMachineCheckStandardSpecify")))
	{
		*RetObj=&szMachineCheckStandardSpecify;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagMachineCheckStandardSpecify::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagMachineCheckStandardSpecify"),this);

	szMachineCheckStandardSpecify.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagMachineCheckStandardSpecify"),this);
	return TRUE;
}

BOOL Serialize__tagMachineCheckStandardSpecify::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szMachineCheckStandardSpecify);
	return TRUE;
}




