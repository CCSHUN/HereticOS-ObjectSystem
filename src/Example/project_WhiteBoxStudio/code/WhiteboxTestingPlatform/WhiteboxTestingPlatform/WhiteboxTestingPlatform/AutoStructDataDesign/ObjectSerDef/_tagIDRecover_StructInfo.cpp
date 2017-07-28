 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagIDRecover_StructInfo.h"

Serialize__tagIDRecover::_Myt& Serialize__tagIDRecover::operator=(_tagIDRecover & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagIDRecover::GetData()
{
	m_Val.nID=nID; 
	m_Val.tIDRecover=tIDRecover;
}

BOOL Serialize__tagIDRecover::Construct(StorageObjectInterface * pOutObject)
{
	nID.init(this,_T("nID"),0,pOutObject); 
	tIDRecover.init(this,_T("tIDRecover"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagIDRecover::SetData(_tagIDRecover & _X)
{
	nID=_X.nID; 
	tIDRecover=_X.tIDRecover;
}

BOOL Serialize__tagIDRecover::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nID")))
	{
		*RetObj=&nID;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("tIDRecover")))
	{
		*RetObj=&tIDRecover;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagIDRecover::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagIDRecover"),this);

	nID.Save(pStorageObject); 
	tIDRecover.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagIDRecover"),this);
	return TRUE;
}

BOOL Serialize__tagIDRecover::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nID); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&tIDRecover);
	return TRUE;
}




