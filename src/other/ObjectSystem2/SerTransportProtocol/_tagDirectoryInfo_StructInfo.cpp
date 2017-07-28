 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagDirectoryInfo_StructInfo.h"

Serialize__tagDirectoryInfo::_Myt& Serialize__tagDirectoryInfo::operator=(_tagDirectoryInfo & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagDirectoryInfo::GetData()
{
	m_Val.DirectoryInfoArray=DirectoryInfoArray;
}

BOOL Serialize__tagDirectoryInfo::Construct(StorageObjectInterface * pOutObject)
{
	DirectoryInfoArray.init(this,_T("DirectoryInfoArray"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagDirectoryInfo::SetData(_tagDirectoryInfo & _X)
{
	DirectoryInfoArray=_X.DirectoryInfoArray;
}

BOOL Serialize__tagDirectoryInfo::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("DirectoryInfoArray")))
	{
		*RetObj=&DirectoryInfoArray;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagDirectoryInfo::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagDirectoryInfo"),this);

	DirectoryInfoArray.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagDirectoryInfo"),this);
	return TRUE;
}

BOOL Serialize__tagDirectoryInfo::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&DirectoryInfoArray);
	return TRUE;
}




