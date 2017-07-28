 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagDirectoryInfoSetSoap_StructInfo.h"

Serialize__tagDirectoryInfoSetSoap::_Myt& Serialize__tagDirectoryInfoSetSoap::operator=(_tagDirectoryInfoSetSoap & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagDirectoryInfoSetSoap::GetData()
{
	m_Val.ObjectName=ObjectName; 
	m_Val.ObjectType=ObjectType; 
	m_Val.OtherInfo=OtherInfo;
}

BOOL Serialize__tagDirectoryInfoSetSoap::Construct(StorageObjectInterface * pOutObject)
{
	ObjectName.init(this,_T("ObjectName"),0,pOutObject); 
	ObjectType.init(this,_T("ObjectType"),0,pOutObject); 
	OtherInfo.init(this,_T("OtherInfo"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagDirectoryInfoSetSoap::SetData(_tagDirectoryInfoSetSoap & _X)
{
	ObjectName=_X.ObjectName; 
	ObjectType=_X.ObjectType; 
	OtherInfo=_X.OtherInfo;
}

BOOL Serialize__tagDirectoryInfoSetSoap::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ObjectName")))
	{
		*RetObj=&ObjectName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ObjectType")))
	{
		*RetObj=&ObjectType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("OtherInfo")))
	{
		*RetObj=&OtherInfo;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagDirectoryInfoSetSoap::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagDirectoryInfoSetSoap"),this);

	ObjectName.Save(pStorageObject); 
	ObjectType.Save(pStorageObject); 
	OtherInfo.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagDirectoryInfoSetSoap"),this);
	return TRUE;
}

BOOL Serialize__tagDirectoryInfoSetSoap::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ObjectName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ObjectType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&OtherInfo);
	return TRUE;
}




