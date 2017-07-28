 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagExp_StructInfo.h"

Serialize__tagExp::_Myt& Serialize__tagExp::operator=(_tagExp & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagExp::GetData()
{
	m_Val.szExpName=szExpName; 
	m_Val.nExpID=nExpID; 
	m_Val.szExpDesc=szExpDesc; 
	m_Val.FuncIDArray=FuncIDArray; 
	m_Val.m_ExpValMap=m_ExpValMap;
}

BOOL Serialize__tagExp::Construct(StorageObjectInterface * pOutObject)
{
	szExpName.init(this,_T("szExpName"),0,pOutObject); 
	nExpID.init(this,_T("nExpID"),0,pOutObject); 
	szExpDesc.init(this,_T("szExpDesc"),0,pOutObject); 
	FuncIDArray.init(this,_T("FuncIDArray"),0,pOutObject); 
	m_ExpValMap.init(this,_T("m_ExpValMap"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagExp::SetData(_tagExp & _X)
{
	szExpName=_X.szExpName; 
	nExpID=_X.nExpID; 
	szExpDesc=_X.szExpDesc; 
	FuncIDArray=_X.FuncIDArray; 
	m_ExpValMap=_X.m_ExpValMap;
}

BOOL Serialize__tagExp::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szExpName")))
	{
		*RetObj=&szExpName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nExpID")))
	{
		*RetObj=&nExpID;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szExpDesc")))
	{
		*RetObj=&szExpDesc;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("FuncIDArray")))
	{
		*RetObj=&FuncIDArray;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("m_ExpValMap")))
	{
		*RetObj=&m_ExpValMap;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagExp::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagExp"),this);

	szExpName.Save(pStorageObject); 
	nExpID.Save(pStorageObject); 
	szExpDesc.Save(pStorageObject); 
	FuncIDArray.Save(pStorageObject); 
	m_ExpValMap.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagExp"),this);
	return TRUE;
}

BOOL Serialize__tagExp::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szExpName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nExpID); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szExpDesc); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&FuncIDArray); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&m_ExpValMap);
	return TRUE;
}




