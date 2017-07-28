 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagDirectoryInfoSoap_StructInfo.h"

Serialize__tagDirectoryInfoSoap::_Myt& Serialize__tagDirectoryInfoSoap::operator=(_tagDirectoryInfoSoap & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagDirectoryInfoSoap::GetData()
{
	m_Val.DirectoryInfoArray=DirectoryInfoArray;
}

BOOL Serialize__tagDirectoryInfoSoap::Construct(StorageObjectInterface * pOutObject)
{
	DirectoryInfoArray.init(this,_T("DirectoryInfoArray"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagDirectoryInfoSoap::SetData(_tagDirectoryInfoSoap & _X)
{
	DirectoryInfoArray=_X.DirectoryInfoArray;
}

BOOL Serialize__tagDirectoryInfoSoap::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("DirectoryInfoArray")))
	{
		*RetObj=&DirectoryInfoArray;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagDirectoryInfoSoap::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagDirectoryInfoSoap"),this);

	DirectoryInfoArray.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagDirectoryInfoSoap"),this);
	return TRUE;
}

BOOL Serialize__tagDirectoryInfoSoap::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&DirectoryInfoArray);
	return TRUE;
}




