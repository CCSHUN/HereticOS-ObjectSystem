 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_S_PROJECT_CONFIG_StructInfo.h"

Serialize__S_PROJECT_CONFIG::_Myt& Serialize__S_PROJECT_CONFIG::operator=(_S_PROJECT_CONFIG & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__S_PROJECT_CONFIG::GetData()
{
	m_Val.config_content=config_content;
}

BOOL Serialize__S_PROJECT_CONFIG::Construct(StorageObjectInterface * pOutObject)
{
	config_content.init(this,_T("config_content"),0,pOutObject);
	return TRUE;
}

 void Serialize__S_PROJECT_CONFIG::SetData(_S_PROJECT_CONFIG & _X)
{
	config_content=_X.config_content;
}

BOOL Serialize__S_PROJECT_CONFIG::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("config_content")))
	{
		*RetObj=&config_content;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__S_PROJECT_CONFIG::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_S_PROJECT_CONFIG"),this);

	config_content.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_S_PROJECT_CONFIG"),this);
	return TRUE;
}

BOOL Serialize__S_PROJECT_CONFIG::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&config_content);
	return TRUE;
}




