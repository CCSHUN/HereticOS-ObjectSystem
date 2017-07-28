 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagMacroLib_StructInfo.h"

Serialize__tagMacroLib::_Myt& Serialize__tagMacroLib::operator=(_tagMacroLib & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagMacroLib::GetData()
{
	m_Val.szLibName=szLibName; 
	m_Val.tidRecover=tidRecover; 
	m_Val.libmap=libmap;
}

BOOL Serialize__tagMacroLib::Construct(StorageObjectInterface * pOutObject)
{
	szLibName.init(this,_T("szLibName"),0,pOutObject); 
	tidRecover.init(this,_T("tidRecover"),0,pOutObject); 
	libmap.init(this,_T("libmap"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagMacroLib::SetData(_tagMacroLib & _X)
{
	szLibName=_X.szLibName; 
	tidRecover=_X.tidRecover; 
	libmap=_X.libmap;
}

BOOL Serialize__tagMacroLib::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szLibName")))
	{
		*RetObj=&szLibName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("tidRecover")))
	{
		*RetObj=&tidRecover;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("libmap")))
	{
		*RetObj=&libmap;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagMacroLib::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagMacroLib"),this);

	szLibName.Save(pStorageObject); 
	tidRecover.Save(pStorageObject); 
	libmap.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagMacroLib"),this);
	return TRUE;
}

BOOL Serialize__tagMacroLib::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szLibName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&tidRecover); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&libmap);
	return TRUE;
}




