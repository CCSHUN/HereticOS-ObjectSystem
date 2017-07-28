 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_S_WORKSHEET_StructInfo.h"

Serialize__S_WORKSHEET::_Myt& Serialize__S_WORKSHEET::operator=(_S_WORKSHEET & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__S_WORKSHEET::GetData()
{
	m_Val.szProjectNo=szProjectNo; 
	m_Val.szModuleNo=szModuleNo; 
	m_Val.szWorksheetNo=szWorksheetNo; 
	m_Val.szApplyDate=szApplyDate; 
	m_Val.szApplyMan=szApplyMan; 
	m_Val.szResponsiblePerson=szResponsiblePerson; 
	m_Val.szDefaultDispatchUser=szDefaultDispatchUser; 
	m_Val.szCheckRange=szCheckRange; 
	m_Val.nCheckType=nCheckType; 
	m_Val.szPreWorksheetNo=szPreWorksheetNo; 
	m_Val.szSVNCodePath=szSVNCodePath; 
	m_Val.szSourceList=szSourceList; 
	m_Val.szSuggest=szSuggest; 
	m_Val.nCheckResult=nCheckResult; 
	m_Val.szFailReason=szFailReason; 
	m_Val.szSignatureMan=szSignatureMan; 
	m_Val.szSignatureDate=szSignatureDate;
}

BOOL Serialize__S_WORKSHEET::Construct(StorageObjectInterface * pOutObject)
{
	szProjectNo.init(this,_T("szProjectNo"),0,pOutObject); 
	szModuleNo.init(this,_T("szModuleNo"),0,pOutObject); 
	szWorksheetNo.init(this,_T("szWorksheetNo"),0,pOutObject); 
	szApplyDate.init(this,_T("szApplyDate"),0,pOutObject); 
	szApplyMan.init(this,_T("szApplyMan"),0,pOutObject); 
	szResponsiblePerson.init(this,_T("szResponsiblePerson"),0,pOutObject); 
	szDefaultDispatchUser.init(this,_T("szDefaultDispatchUser"),0,pOutObject); 
	szCheckRange.init(this,_T("szCheckRange"),0,pOutObject); 
	nCheckType.init(this,_T("nCheckType"),0,pOutObject); 
	szPreWorksheetNo.init(this,_T("szPreWorksheetNo"),0,pOutObject); 
	szSVNCodePath.init(this,_T("szSVNCodePath"),0,pOutObject); 
	szSourceList.init(this,_T("szSourceList"),0,pOutObject); 
	szSuggest.init(this,_T("szSuggest"),0,pOutObject); 
	nCheckResult.init(this,_T("nCheckResult"),0,pOutObject); 
	szFailReason.init(this,_T("szFailReason"),0,pOutObject); 
	szSignatureMan.init(this,_T("szSignatureMan"),0,pOutObject); 
	szSignatureDate.init(this,_T("szSignatureDate"),0,pOutObject);
	return TRUE;
}

 void Serialize__S_WORKSHEET::SetData(_S_WORKSHEET & _X)
{
	szProjectNo=_X.szProjectNo; 
	szModuleNo=_X.szModuleNo; 
	szWorksheetNo=_X.szWorksheetNo; 
	szApplyDate=_X.szApplyDate; 
	szApplyMan=_X.szApplyMan; 
	szResponsiblePerson=_X.szResponsiblePerson; 
	szDefaultDispatchUser=_X.szDefaultDispatchUser; 
	szCheckRange=_X.szCheckRange; 
	nCheckType=_X.nCheckType; 
	szPreWorksheetNo=_X.szPreWorksheetNo; 
	szSVNCodePath=_X.szSVNCodePath; 
	szSourceList=_X.szSourceList; 
	szSuggest=_X.szSuggest; 
	nCheckResult=_X.nCheckResult; 
	szFailReason=_X.szFailReason; 
	szSignatureMan=_X.szSignatureMan; 
	szSignatureDate=_X.szSignatureDate;
}

BOOL Serialize__S_WORKSHEET::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szProjectNo")))
	{
		*RetObj=&szProjectNo;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szModuleNo")))
	{
		*RetObj=&szModuleNo;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szWorksheetNo")))
	{
		*RetObj=&szWorksheetNo;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szApplyDate")))
	{
		*RetObj=&szApplyDate;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szApplyMan")))
	{
		*RetObj=&szApplyMan;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szResponsiblePerson")))
	{
		*RetObj=&szResponsiblePerson;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szDefaultDispatchUser")))
	{
		*RetObj=&szDefaultDispatchUser;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szCheckRange")))
	{
		*RetObj=&szCheckRange;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nCheckType")))
	{
		*RetObj=&nCheckType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szPreWorksheetNo")))
	{
		*RetObj=&szPreWorksheetNo;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szSVNCodePath")))
	{
		*RetObj=&szSVNCodePath;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szSourceList")))
	{
		*RetObj=&szSourceList;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szSuggest")))
	{
		*RetObj=&szSuggest;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nCheckResult")))
	{
		*RetObj=&nCheckResult;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szFailReason")))
	{
		*RetObj=&szFailReason;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szSignatureMan")))
	{
		*RetObj=&szSignatureMan;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szSignatureDate")))
	{
		*RetObj=&szSignatureDate;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__S_WORKSHEET::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_S_WORKSHEET"),this);

	szProjectNo.Save(pStorageObject); 
	szModuleNo.Save(pStorageObject); 
	szWorksheetNo.Save(pStorageObject); 
	szApplyDate.Save(pStorageObject); 
	szApplyMan.Save(pStorageObject); 
	szResponsiblePerson.Save(pStorageObject); 
	szDefaultDispatchUser.Save(pStorageObject); 
	szCheckRange.Save(pStorageObject); 
	nCheckType.Save(pStorageObject); 
	szPreWorksheetNo.Save(pStorageObject); 
	szSVNCodePath.Save(pStorageObject); 
	szSourceList.Save(pStorageObject); 
	szSuggest.Save(pStorageObject); 
	nCheckResult.Save(pStorageObject); 
	szFailReason.Save(pStorageObject); 
	szSignatureMan.Save(pStorageObject); 
	szSignatureDate.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_S_WORKSHEET"),this);
	return TRUE;
}

BOOL Serialize__S_WORKSHEET::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szProjectNo); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szModuleNo); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szWorksheetNo); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szApplyDate); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szApplyMan); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szResponsiblePerson); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szDefaultDispatchUser); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szCheckRange); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nCheckType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szPreWorksheetNo); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szSVNCodePath); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szSourceList); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szSuggest); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nCheckResult); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szFailReason); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szSignatureMan); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szSignatureDate);
	return TRUE;
}




