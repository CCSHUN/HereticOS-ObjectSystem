 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagUserMapSet_StructInfo.h"

Serialize__tagUserMapSet::_Myt& Serialize__tagUserMapSet::operator=(_tagUserMapSet & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagUserMapSet::GetData()
{
	m_Val.szUserName=szUserName; 
	m_Val.szPassword=szPassword; 
	m_Val.szUserType=szUserType; 
	m_Val.szChildUserType=szChildUserType; 
	m_Val.szChildUserType1=szChildUserType1;
}

BOOL Serialize__tagUserMapSet::Construct(StorageObjectInterface * pOutObject)
{
	szUserName.init(this,_T("szUserName"),0,pOutObject); 
	szPassword.init(this,_T("szPassword"),0,pOutObject); 
	szUserType.init(this,_T("szUserType"),0,pOutObject); 
	szChildUserType.init(this,_T("szChildUserType"),0,pOutObject); 
	szChildUserType1.init(this,_T("szChildUserType1"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagUserMapSet::SetData(_tagUserMapSet & _X)
{
	szUserName=_X.szUserName; 
	szPassword=_X.szPassword; 
	szUserType=_X.szUserType; 
	szChildUserType=_X.szChildUserType; 
	szChildUserType1=_X.szChildUserType1;
}

BOOL Serialize__tagUserMapSet::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szUserName")))
	{
		*RetObj=&szUserName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szPassword")))
	{
		*RetObj=&szPassword;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szUserType")))
	{
		*RetObj=&szUserType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szChildUserType")))
	{
		*RetObj=&szChildUserType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szChildUserType1")))
	{
		*RetObj=&szChildUserType1;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagUserMapSet::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagUserMapSet"),this);

	szUserName.Save(pStorageObject); 
	szPassword.Save(pStorageObject); 
	szUserType.Save(pStorageObject); 
	szChildUserType.Save(pStorageObject); 
	szChildUserType1.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagUserMapSet"),this);
	return TRUE;
}

BOOL Serialize__tagUserMapSet::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szUserName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szPassword); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szUserType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szChildUserType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szChildUserType1);
	return TRUE;
}




