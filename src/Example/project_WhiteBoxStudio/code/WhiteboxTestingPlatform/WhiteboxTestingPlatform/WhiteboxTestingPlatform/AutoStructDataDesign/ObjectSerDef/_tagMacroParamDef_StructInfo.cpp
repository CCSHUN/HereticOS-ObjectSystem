 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagMacroParamDef_StructInfo.h"

Serialize__tagMacroParamDef::_Myt& Serialize__tagMacroParamDef::operator=(_tagMacroParamDef & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagMacroParamDef::GetData()
{
	m_Val.nParamID=nParamID; 
	m_Val.szParamType=szParamType; 
	m_Val.RefPar=RefPar; 
	m_Val.realPar=realPar; 
	m_Val.szLastEditParamVal=szLastEditParamVal;
}

BOOL Serialize__tagMacroParamDef::Construct(StorageObjectInterface * pOutObject)
{
	nParamID.init(this,_T("nParamID"),0,pOutObject); 
	szParamType.init(this,_T("szParamType"),0,pOutObject); 
	RefPar.init(this,_T("RefPar"),0,pOutObject); 
	realPar.init(this,_T("realPar"),0,pOutObject); 
	szLastEditParamVal.init(this,_T("szLastEditParamVal"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagMacroParamDef::SetData(_tagMacroParamDef & _X)
{
	nParamID=_X.nParamID; 
	szParamType=_X.szParamType; 
	RefPar=_X.RefPar; 
	realPar=_X.realPar; 
	szLastEditParamVal=_X.szLastEditParamVal;
}

BOOL Serialize__tagMacroParamDef::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nParamID")))
	{
		*RetObj=&nParamID;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szParamType")))
	{
		*RetObj=&szParamType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("RefPar")))
	{
		*RetObj=&RefPar;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("realPar")))
	{
		*RetObj=&realPar;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szLastEditParamVal")))
	{
		*RetObj=&szLastEditParamVal;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagMacroParamDef::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagMacroParamDef"),this);

	nParamID.Save(pStorageObject); 
	szParamType.Save(pStorageObject); 
	RefPar.Save(pStorageObject); 
	realPar.Save(pStorageObject); 
	szLastEditParamVal.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagMacroParamDef"),this);
	return TRUE;
}

BOOL Serialize__tagMacroParamDef::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nParamID); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szParamType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&RefPar); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&realPar); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szLastEditParamVal);
	return TRUE;
}




