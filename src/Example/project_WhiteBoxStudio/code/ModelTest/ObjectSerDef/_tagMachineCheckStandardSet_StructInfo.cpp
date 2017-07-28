 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagMachineCheckStandardSet_StructInfo.h"

Serialize__tagMachineCheckStandardSet::_Myt& Serialize__tagMachineCheckStandardSet::operator=(_tagMachineCheckStandardSet & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagMachineCheckStandardSet::GetData()
{
	m_Val.szErrorNum=szErrorNum; 
	m_Val.szErrorType=szErrorType; 
	m_Val.szDesc=szDesc; 
	m_Val.szErrorWarning=szErrorWarning; 
	m_Val.szErrorTypeId=szErrorTypeId; 
	m_Val.szErrorSuggest=szErrorSuggest;
}

BOOL Serialize__tagMachineCheckStandardSet::Construct(StorageObjectInterface * pOutObject)
{
	szErrorNum.init(this,_T("szErrorNum"),0,pOutObject); 
	szErrorType.init(this,_T("szErrorType"),0,pOutObject); 
	szDesc.init(this,_T("szDesc"),0,pOutObject); 
	szErrorWarning.init(this,_T("szErrorWarning"),0,pOutObject); 
	szErrorTypeId.init(this,_T("szErrorTypeId"),0,pOutObject); 
	szErrorSuggest.init(this,_T("szErrorSuggest"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagMachineCheckStandardSet::SetData(_tagMachineCheckStandardSet & _X)
{
	szErrorNum=_X.szErrorNum; 
	szErrorType=_X.szErrorType; 
	szDesc=_X.szDesc; 
	szErrorWarning=_X.szErrorWarning; 
	szErrorTypeId=_X.szErrorTypeId; 
	szErrorSuggest=_X.szErrorSuggest;
}

BOOL Serialize__tagMachineCheckStandardSet::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szErrorNum")))
	{
		*RetObj=&szErrorNum;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szErrorType")))
	{
		*RetObj=&szErrorType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szDesc")))
	{
		*RetObj=&szDesc;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szErrorWarning")))
	{
		*RetObj=&szErrorWarning;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szErrorTypeId")))
	{
		*RetObj=&szErrorTypeId;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szErrorSuggest")))
	{
		*RetObj=&szErrorSuggest;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagMachineCheckStandardSet::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagMachineCheckStandardSet"),this);

	szErrorNum.Save(pStorageObject); 
	szErrorType.Save(pStorageObject); 
	szDesc.Save(pStorageObject); 
	szErrorWarning.Save(pStorageObject); 
	szErrorTypeId.Save(pStorageObject); 
	szErrorSuggest.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagMachineCheckStandardSet"),this);
	return TRUE;
}

BOOL Serialize__tagMachineCheckStandardSet::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szErrorNum); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szErrorType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szDesc); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szErrorWarning); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szErrorTypeId); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szErrorSuggest);
	return TRUE;
}




