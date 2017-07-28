 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagFuncDef_StructInfo.h"

Serialize__tagFuncDef::_Myt& Serialize__tagFuncDef::operator=(_tagFuncDef & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagFuncDef::GetData()
{
	m_Val.nFuncID=nFuncID; 
	m_Val.szFuncName=szFuncName; 
	m_Val.szFuncDesc=szFuncDesc; 
	m_Val.szFuncType=szFuncType; 
	m_Val.FuncAttr=FuncAttr; 
	m_Val.tParamidRecover=tParamidRecover; 
	m_Val.m_ParamDefArray=m_ParamDefArray;
}

BOOL Serialize__tagFuncDef::Construct(StorageObjectInterface * pOutObject)
{
	nFuncID.init(this,_T("nFuncID"),0,pOutObject); 
	szFuncName.init(this,_T("szFuncName"),0,pOutObject); 
	szFuncDesc.init(this,_T("szFuncDesc"),0,pOutObject); 
	szFuncType.init(this,_T("szFuncType"),0,pOutObject); 
	FuncAttr.init(this,_T("FuncAttr"),0,pOutObject); 
	tParamidRecover.init(this,_T("tParamidRecover"),0,pOutObject); 
	m_ParamDefArray.init(this,_T("m_ParamDefArray"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagFuncDef::SetData(_tagFuncDef & _X)
{
	nFuncID=_X.nFuncID; 
	szFuncName=_X.szFuncName; 
	szFuncDesc=_X.szFuncDesc; 
	szFuncType=_X.szFuncType; 
	FuncAttr=_X.FuncAttr; 
	tParamidRecover=_X.tParamidRecover; 
	m_ParamDefArray=_X.m_ParamDefArray;
}

BOOL Serialize__tagFuncDef::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nFuncID")))
	{
		*RetObj=&nFuncID;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szFuncName")))
	{
		*RetObj=&szFuncName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szFuncDesc")))
	{
		*RetObj=&szFuncDesc;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szFuncType")))
	{
		*RetObj=&szFuncType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("FuncAttr")))
	{
		*RetObj=&FuncAttr;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("tParamidRecover")))
	{
		*RetObj=&tParamidRecover;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("m_ParamDefArray")))
	{
		*RetObj=&m_ParamDefArray;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagFuncDef::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagFuncDef"),this);

	nFuncID.Save(pStorageObject); 
	szFuncName.Save(pStorageObject); 
	szFuncDesc.Save(pStorageObject); 
	szFuncType.Save(pStorageObject); 
	FuncAttr.Save(pStorageObject); 
	tParamidRecover.Save(pStorageObject); 
	m_ParamDefArray.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagFuncDef"),this);
	return TRUE;
}

BOOL Serialize__tagFuncDef::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nFuncID); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szFuncName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szFuncDesc); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szFuncType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&FuncAttr); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&tParamidRecover); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&m_ParamDefArray);
	return TRUE;
}




