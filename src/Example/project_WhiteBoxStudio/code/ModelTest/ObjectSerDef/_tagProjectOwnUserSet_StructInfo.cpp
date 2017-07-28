 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagProjectOwnUserSet_StructInfo.h"

Serialize__tagProjectOwnUserSet::_Myt& Serialize__tagProjectOwnUserSet::operator=(_tagProjectOwnUserSet & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagProjectOwnUserSet::GetData()
{
	m_Val.szUserName=szUserName; 
	m_Val.szUserType=szUserType;
}

BOOL Serialize__tagProjectOwnUserSet::Construct(StorageObjectInterface * pOutObject)
{
	szUserName.init(this,_T("szUserName"),0,pOutObject); 
	szUserType.init(this,_T("szUserType"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagProjectOwnUserSet::SetData(_tagProjectOwnUserSet & _X)
{
	szUserName=_X.szUserName; 
	szUserType=_X.szUserType;
}

BOOL Serialize__tagProjectOwnUserSet::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szUserName")))
	{
		*RetObj=&szUserName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szUserType")))
	{
		*RetObj=&szUserType;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagProjectOwnUserSet::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagProjectOwnUserSet"),this);

	szUserName.Save(pStorageObject); 
	szUserType.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagProjectOwnUserSet"),this);
	return TRUE;
}

BOOL Serialize__tagProjectOwnUserSet::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szUserName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szUserType);
	return TRUE;
}




