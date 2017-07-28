 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagParamDef_StructInfo.h"

Serialize__tagParamDef::_Myt& Serialize__tagParamDef::operator=(_tagParamDef & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagParamDef::GetData()
{
	m_Val.nParamID=nParamID; 
	m_Val.szParamName=szParamName; 
	m_Val.szParamDesc=szParamDesc; 
	m_Val.szParamAttribute=szParamAttribute; 
	m_Val.szDefaultParam=szDefaultParam; 
	m_Val.szLastEditParamVal=szLastEditParamVal;
}

BOOL Serialize__tagParamDef::Construct(StorageObjectInterface * pOutObject)
{
	nParamID.init(this,_T("nParamID"),0,pOutObject); 
	szParamName.init(this,_T("szParamName"),0,pOutObject); 
	szParamDesc.init(this,_T("szParamDesc"),0,pOutObject); 
	szParamAttribute.init(this,_T("szParamAttribute"),0,pOutObject); 
	szDefaultParam.init(this,_T("szDefaultParam"),0,pOutObject); 
	szLastEditParamVal.init(this,_T("szLastEditParamVal"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagParamDef::SetData(_tagParamDef & _X)
{
	nParamID=_X.nParamID; 
	szParamName=_X.szParamName; 
	szParamDesc=_X.szParamDesc; 
	szParamAttribute=_X.szParamAttribute; 
	szDefaultParam=_X.szDefaultParam; 
	szLastEditParamVal=_X.szLastEditParamVal;
}

BOOL Serialize__tagParamDef::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nParamID")))
	{
		*RetObj=&nParamID;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szParamName")))
	{
		*RetObj=&szParamName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szParamDesc")))
	{
		*RetObj=&szParamDesc;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szParamAttribute")))
	{
		*RetObj=&szParamAttribute;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szDefaultParam")))
	{
		*RetObj=&szDefaultParam;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szLastEditParamVal")))
	{
		*RetObj=&szLastEditParamVal;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagParamDef::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagParamDef"),this);

	nParamID.Save(pStorageObject); 
	szParamName.Save(pStorageObject); 
	szParamDesc.Save(pStorageObject); 
	szParamAttribute.Save(pStorageObject); 
	szDefaultParam.Save(pStorageObject); 
	szLastEditParamVal.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagParamDef"),this);
	return TRUE;
}

BOOL Serialize__tagParamDef::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nParamID); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szParamName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szParamDesc); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szParamAttribute); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szDefaultParam); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szLastEditParamVal);
	return TRUE;
}




