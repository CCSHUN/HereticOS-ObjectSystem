 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagTestSubObject_StructInfo.h"

Serialize__tagTestSubObject::_Myt& Serialize__tagTestSubObject::operator=(_tagTestSubObject & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagTestSubObject::GetData()
{
	m_Val.szSubObjectName=szSubObjectName; 
	m_Val.nSubObjectType=nSubObjectType; 
	m_Val.fSubObject=fSubObject; 
	m_Val.lfSubObject=lfSubObject; 
	m_Val.iSubObject=iSubObject; 
	m_Val.bSubVal=bSubVal; 
	m_Val.szSubVal=szSubVal;
}

BOOL Serialize__tagTestSubObject::Construct(StorageObjectInterface * pOutObject)
{
	szSubObjectName.init(this,_T("szSubObjectName"),0,pOutObject); 
	nSubObjectType.init(this,_T("nSubObjectType"),0,pOutObject); 
	fSubObject.init(this,_T("fSubObject"),0,pOutObject); 
	lfSubObject.init(this,_T("lfSubObject"),0,pOutObject); 
	iSubObject.init(this,_T("iSubObject"),0,pOutObject); 
	bSubVal.init(this,_T("bSubVal"),0,pOutObject); 
	szSubVal.init(this,_T("szSubVal"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagTestSubObject::SetData(_tagTestSubObject & _X)
{
	szSubObjectName=_X.szSubObjectName; 
	nSubObjectType=_X.nSubObjectType; 
	fSubObject=_X.fSubObject; 
	lfSubObject=_X.lfSubObject; 
	iSubObject=_X.iSubObject; 
	bSubVal=_X.bSubVal; 
	szSubVal=_X.szSubVal;
}

BOOL Serialize__tagTestSubObject::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szSubObjectName")))
	{
		*RetObj=&szSubObjectName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nSubObjectType")))
	{
		*RetObj=&nSubObjectType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("fSubObject")))
	{
		*RetObj=&fSubObject;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("lfSubObject")))
	{
		*RetObj=&lfSubObject;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("iSubObject")))
	{
		*RetObj=&iSubObject;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("bSubVal")))
	{
		*RetObj=&bSubVal;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szSubVal")))
	{
		*RetObj=&szSubVal;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagTestSubObject::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagTestSubObject"),this);

	szSubObjectName.Save(pStorageObject); 
	nSubObjectType.Save(pStorageObject); 
	fSubObject.Save(pStorageObject); 
	lfSubObject.Save(pStorageObject); 
	iSubObject.Save(pStorageObject); 
	bSubVal.Save(pStorageObject); 
	szSubVal.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagTestSubObject"),this);
	return TRUE;
}

BOOL Serialize__tagTestSubObject::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szSubObjectName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nSubObjectType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&fSubObject); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&lfSubObject); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&iSubObject); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&bSubVal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szSubVal);
	return TRUE;
}




