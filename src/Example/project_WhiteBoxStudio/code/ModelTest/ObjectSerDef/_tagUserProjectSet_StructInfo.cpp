 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagUserProjectSet_StructInfo.h"

Serialize__tagUserProjectSet::_Myt& Serialize__tagUserProjectSet::operator=(_tagUserProjectSet & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagUserProjectSet::GetData()
{
	m_Val.szUserName=szUserName; 
	m_Val.szProjectName=szProjectName;
}

BOOL Serialize__tagUserProjectSet::Construct(StorageObjectInterface * pOutObject)
{
	szUserName.init(this,_T("szUserName"),0,pOutObject); 
	szProjectName.init(this,_T("szProjectName"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagUserProjectSet::SetData(_tagUserProjectSet & _X)
{
	szUserName=_X.szUserName; 
	szProjectName=_X.szProjectName;
}

BOOL Serialize__tagUserProjectSet::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szUserName")))
	{
		*RetObj=&szUserName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szProjectName")))
	{
		*RetObj=&szProjectName;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagUserProjectSet::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagUserProjectSet"),this);

	szUserName.Save(pStorageObject); 
	szProjectName.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagUserProjectSet"),this);
	return TRUE;
}

BOOL Serialize__tagUserProjectSet::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szUserName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szProjectName);
	return TRUE;
}




