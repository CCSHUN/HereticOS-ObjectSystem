 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagTestObject_StructInfo.h"

Serialize__tagTestObject::_Myt& Serialize__tagTestObject::operator=(_tagTestObject & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagTestObject::GetData()
{
	m_Val.szObjectName=szObjectName; 
	m_Val.nObjectType=nObjectType; 
	memcpy(m_Val.tCharArray,(char*)tCharArray,sizeof(m_Val.tCharArray)); 
	memcpy(m_Val.tUintArray,(UINT*)tUintArray,sizeof(m_Val.tUintArray)); 
	m_Val.nVal=nVal; 
	m_Val.iVal=iVal; 
	m_Val.fVal=fVal; 
	m_Val.lfVal=lfVal; 
	m_Val.bVal=bVal; 
	m_Val.szVal=szVal; 
	m_Val.SubObject=SubObject; 
	m_Val.SubObjectArray=SubObjectArray; 
	m_Val.SubObjectMap=SubObjectMap;
}

BOOL Serialize__tagTestObject::Construct(StorageObjectInterface * pOutObject)
{
	szObjectName.init(this,_T("szObjectName"),0,pOutObject); 
	nObjectType.init(this,_T("nObjectType"),0,pOutObject); 
	tCharArray.init(this,_T("tCharArray"),0,pOutObject); 
	tUintArray.init(this,_T("tUintArray"),0,pOutObject); 
	nVal.init(this,_T("nVal"),0,pOutObject); 
	iVal.init(this,_T("iVal"),0,pOutObject); 
	fVal.init(this,_T("fVal"),0,pOutObject); 
	lfVal.init(this,_T("lfVal"),0,pOutObject); 
	bVal.init(this,_T("bVal"),0,pOutObject); 
	szVal.init(this,_T("szVal"),0,pOutObject); 
	SubObject.init(this,_T("SubObject"),0,pOutObject); 
	SubObjectArray.init(this,_T("SubObjectArray"),0,pOutObject); 
	SubObjectMap.init(this,_T("SubObjectMap"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagTestObject::SetData(_tagTestObject & _X)
{
	szObjectName=_X.szObjectName; 
	nObjectType=_X.nObjectType; 
	tCharArray=_X.tCharArray; 
	tUintArray=_X.tUintArray; 
	nVal=_X.nVal; 
	iVal=_X.iVal; 
	fVal=_X.fVal; 
	lfVal=_X.lfVal; 
	bVal=_X.bVal; 
	szVal=_X.szVal; 
	SubObject=_X.SubObject; 
	SubObjectArray=_X.SubObjectArray; 
	SubObjectMap=_X.SubObjectMap;
}

BOOL Serialize__tagTestObject::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szObjectName")))
	{
		*RetObj=&szObjectName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nObjectType")))
	{
		*RetObj=&nObjectType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("tCharArray")))
	{
		*RetObj=&tCharArray;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("tUintArray")))
	{
		*RetObj=&tUintArray;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nVal")))
	{
		*RetObj=&nVal;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("iVal")))
	{
		*RetObj=&iVal;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("fVal")))
	{
		*RetObj=&fVal;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("lfVal")))
	{
		*RetObj=&lfVal;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("bVal")))
	{
		*RetObj=&bVal;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szVal")))
	{
		*RetObj=&szVal;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("SubObject")))
	{
		*RetObj=&SubObject;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("SubObjectArray")))
	{
		*RetObj=&SubObjectArray;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("SubObjectMap")))
	{
		*RetObj=&SubObjectMap;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagTestObject::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagTestObject"),this);

	szObjectName.Save(pStorageObject); 
	nObjectType.Save(pStorageObject); 
	tCharArray.Save(pStorageObject); 
	tUintArray.Save(pStorageObject); 
	nVal.Save(pStorageObject); 
	iVal.Save(pStorageObject); 
	fVal.Save(pStorageObject); 
	lfVal.Save(pStorageObject); 
	bVal.Save(pStorageObject); 
	szVal.Save(pStorageObject); 
	SubObject.Save(pStorageObject); 
	SubObjectArray.Save(pStorageObject); 
	SubObjectMap.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagTestObject"),this);
	return TRUE;
}

BOOL Serialize__tagTestObject::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szObjectName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nObjectType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&tCharArray); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&tUintArray); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nVal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&iVal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&fVal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&lfVal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&bVal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szVal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&SubObject); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&SubObjectArray); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&SubObjectMap);
	return TRUE;
}




