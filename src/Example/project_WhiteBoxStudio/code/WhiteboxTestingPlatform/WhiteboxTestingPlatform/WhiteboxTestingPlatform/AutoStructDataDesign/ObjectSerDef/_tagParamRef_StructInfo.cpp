 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagParamRef_StructInfo.h"

Serialize__tagParamRef::_Myt& Serialize__tagParamRef::operator=(_tagParamRef & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagParamRef::GetData()
{
	m_Val.nMacroID=nMacroID; 
	m_Val.nParamID=nParamID;
}

BOOL Serialize__tagParamRef::Construct(StorageObjectInterface * pOutObject)
{
	nMacroID.init(this,_T("nMacroID"),0,pOutObject); 
	nParamID.init(this,_T("nParamID"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagParamRef::SetData(_tagParamRef & _X)
{
	nMacroID=_X.nMacroID; 
	nParamID=_X.nParamID;
}

BOOL Serialize__tagParamRef::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nMacroID")))
	{
		*RetObj=&nMacroID;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nParamID")))
	{
		*RetObj=&nParamID;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagParamRef::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagParamRef"),this);

	nMacroID.Save(pStorageObject); 
	nParamID.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagParamRef"),this);
	return TRUE;
}

BOOL Serialize__tagParamRef::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nMacroID); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nParamID);
	return TRUE;
}




