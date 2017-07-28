 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagExpLib_StructInfo.h"

Serialize__tagExpLib::_Myt& Serialize__tagExpLib::operator=(_tagExpLib & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagExpLib::GetData()
{
	m_Val.szLibName=szLibName; 
	m_Val.tidRecover=tidRecover; 
	m_Val.m_ExpLib=m_ExpLib;
}

BOOL Serialize__tagExpLib::Construct(StorageObjectInterface * pOutObject)
{
	szLibName.init(this,_T("szLibName"),0,pOutObject); 
	tidRecover.init(this,_T("tidRecover"),0,pOutObject); 
	m_ExpLib.init(this,_T("m_ExpLib"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagExpLib::SetData(_tagExpLib & _X)
{
	szLibName=_X.szLibName; 
	tidRecover=_X.tidRecover; 
	m_ExpLib=_X.m_ExpLib;
}

BOOL Serialize__tagExpLib::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szLibName")))
	{
		*RetObj=&szLibName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("tidRecover")))
	{
		*RetObj=&tidRecover;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("m_ExpLib")))
	{
		*RetObj=&m_ExpLib;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagExpLib::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagExpLib"),this);

	szLibName.Save(pStorageObject); 
	tidRecover.Save(pStorageObject); 
	m_ExpLib.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagExpLib"),this);
	return TRUE;
}

BOOL Serialize__tagExpLib::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szLibName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&tidRecover); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&m_ExpLib);
	return TRUE;
}




