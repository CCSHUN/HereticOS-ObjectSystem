 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagErrorWarningSet_StructInfo.h"

Serialize__tagErrorWarningSet::_Myt& Serialize__tagErrorWarningSet::operator=(_tagErrorWarningSet & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagErrorWarningSet::GetData()
{
	m_Val.szErrorWarningName=szErrorWarningName; 
	m_Val.szErrorWarningDesc=szErrorWarningDesc;
}

BOOL Serialize__tagErrorWarningSet::Construct(StorageObjectInterface * pOutObject)
{
	szErrorWarningName.init(this,_T("szErrorWarningName"),0,pOutObject); 
	szErrorWarningDesc.init(this,_T("szErrorWarningDesc"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagErrorWarningSet::SetData(_tagErrorWarningSet & _X)
{
	szErrorWarningName=_X.szErrorWarningName; 
	szErrorWarningDesc=_X.szErrorWarningDesc;
}

BOOL Serialize__tagErrorWarningSet::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szErrorWarningName")))
	{
		*RetObj=&szErrorWarningName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szErrorWarningDesc")))
	{
		*RetObj=&szErrorWarningDesc;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagErrorWarningSet::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagErrorWarningSet"),this);

	szErrorWarningName.Save(pStorageObject); 
	szErrorWarningDesc.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagErrorWarningSet"),this);
	return TRUE;
}

BOOL Serialize__tagErrorWarningSet::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szErrorWarningName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szErrorWarningDesc);
	return TRUE;
}




