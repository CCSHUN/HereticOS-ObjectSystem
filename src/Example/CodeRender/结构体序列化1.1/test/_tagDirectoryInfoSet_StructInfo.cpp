 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagDirectoryInfoSet_StructInfo.h"

Serialize__tagDirectoryInfoSet::_Myt& Serialize__tagDirectoryInfoSet::operator=(_tagDirectoryInfoSet & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagDirectoryInfoSet::GetData()
{
	m_Val.ObjectName=ObjectName; 
	m_Val.ObjectType=ObjectType; 
	m_Val.OtherInfo=OtherInfo;
}

BOOL Serialize__tagDirectoryInfoSet::Construct(StorageObjectInterface * pOutObject)
{
	ObjectName.init(this,_T("ObjectName"),0,pOutObject); 
	ObjectType.init(this,_T("ObjectType"),0,pOutObject); 
	OtherInfo.init(this,_T("OtherInfo"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagDirectoryInfoSet::SetData(_tagDirectoryInfoSet & _X)
{
	ObjectName=_X.ObjectName; 
	ObjectType=_X.ObjectType; 
	OtherInfo=_X.OtherInfo;
}

BOOL Serialize__tagDirectoryInfoSet::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
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

BOOL Serialize__tagDirectoryInfoSet::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagDirectoryInfoSet"),this);

	ObjectName.Save(pStorageObject); 
	ObjectType.Save(pStorageObject); 
	OtherInfo.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagDirectoryInfoSet"),this);
	return TRUE;
}

BOOL Serialize__tagDirectoryInfoSet::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ObjectName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ObjectType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&OtherInfo);
	return TRUE;
}




