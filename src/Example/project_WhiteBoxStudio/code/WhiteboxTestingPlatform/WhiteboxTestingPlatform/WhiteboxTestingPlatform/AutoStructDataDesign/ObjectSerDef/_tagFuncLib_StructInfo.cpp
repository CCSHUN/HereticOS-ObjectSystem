 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagFuncLib_StructInfo.h"

Serialize__tagFuncLib::_Myt& Serialize__tagFuncLib::operator=(_tagFuncLib & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagFuncLib::GetData()
{
	m_Val.szLibName=szLibName; 
	m_Val.tidRecover=tidRecover; 
	m_Val.m_FuncLib=m_FuncLib;
}

BOOL Serialize__tagFuncLib::Construct(StorageObjectInterface * pOutObject)
{
	szLibName.init(this,_T("szLibName"),0,pOutObject); 
	tidRecover.init(this,_T("tidRecover"),0,pOutObject); 
	m_FuncLib.init(this,_T("m_FuncLib"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagFuncLib::SetData(_tagFuncLib & _X)
{
	szLibName=_X.szLibName; 
	tidRecover=_X.tidRecover; 
	m_FuncLib=_X.m_FuncLib;
}

BOOL Serialize__tagFuncLib::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szLibName")))
	{
		*RetObj=&szLibName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("tidRecover")))
	{
		*RetObj=&tidRecover;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("m_FuncLib")))
	{
		*RetObj=&m_FuncLib;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagFuncLib::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagFuncLib"),this);

	szLibName.Save(pStorageObject); 
	tidRecover.Save(pStorageObject); 
	m_FuncLib.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagFuncLib"),this);
	return TRUE;
}

BOOL Serialize__tagFuncLib::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szLibName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&tidRecover); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&m_FuncLib);
	return TRUE;
}




