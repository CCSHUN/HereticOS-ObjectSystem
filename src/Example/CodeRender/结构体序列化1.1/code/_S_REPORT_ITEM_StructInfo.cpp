 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_S_REPORT_ITEM_StructInfo.h"

Serialize__S_REPORT_ITEM::_Myt& Serialize__S_REPORT_ITEM::operator=(_S_REPORT_ITEM & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__S_REPORT_ITEM::GetData()
{
	m_Val.szTestState=szTestState; 
	m_Val.szTestItemSource=szTestItemSource; 
	m_Val.szTestToolType=szTestToolType; 
	m_Val.szUniteStandardErrorNum=szUniteStandardErrorNum; 
	m_Val.szThirdStandardErrorNum=szThirdStandardErrorNum; 
	m_Val.szErrorCodeContent=szErrorCodeContent; 
	m_Val.szErrorCodePosition=szErrorCodePosition; 
	m_Val.szModule=szModule; 
	m_Val.szSuggest=szSuggest; 
	m_Val.szDesc=szDesc; 
	m_Val.szUniteSuggest=szUniteSuggest; 
	m_Val.szUniteDesc=szUniteDesc; 
	m_Val.szThirdSuggest=szThirdSuggest; 
	m_Val.szThirdDesc=szThirdDesc; 
	m_Val.szErrorType=szErrorType; 
	m_Val.szErrorWarning=szErrorWarning; 
	m_Val.szCreateTime=szCreateTime; 
	m_Val.szLastEditTime=szLastEditTime; 
	m_Val.szDevelopState=szDevelopState; 
	m_Val.szReport_log=szReport_log; 
	m_Val.szProcessUser=szProcessUser;
}

BOOL Serialize__S_REPORT_ITEM::Construct(StorageObjectInterface * pOutObject)
{
	szTestState.init(this,_T("szTestState"),0,pOutObject); 
	szTestItemSource.init(this,_T("szTestItemSource"),0,pOutObject); 
	szTestToolType.init(this,_T("szTestToolType"),0,pOutObject); 
	szUniteStandardErrorNum.init(this,_T("szUniteStandardErrorNum"),0,pOutObject); 
	szThirdStandardErrorNum.init(this,_T("szThirdStandardErrorNum"),0,pOutObject); 
	szErrorCodeContent.init(this,_T("szErrorCodeContent"),0,pOutObject); 
	szErrorCodePosition.init(this,_T("szErrorCodePosition"),0,pOutObject); 
	szModule.init(this,_T("szModule"),0,pOutObject); 
	szSuggest.init(this,_T("szSuggest"),0,pOutObject); 
	szDesc.init(this,_T("szDesc"),0,pOutObject); 
	szUniteSuggest.init(this,_T("szUniteSuggest"),0,pOutObject); 
	szUniteDesc.init(this,_T("szUniteDesc"),0,pOutObject); 
	szThirdSuggest.init(this,_T("szThirdSuggest"),0,pOutObject); 
	szThirdDesc.init(this,_T("szThirdDesc"),0,pOutObject); 
	szErrorType.init(this,_T("szErrorType"),0,pOutObject); 
	szErrorWarning.init(this,_T("szErrorWarning"),0,pOutObject); 
	szCreateTime.init(this,_T("szCreateTime"),0,pOutObject); 
	szLastEditTime.init(this,_T("szLastEditTime"),0,pOutObject); 
	szDevelopState.init(this,_T("szDevelopState"),0,pOutObject); 
	szReport_log.init(this,_T("szReport_log"),0,pOutObject); 
	szProcessUser.init(this,_T("szProcessUser"),0,pOutObject);
	return TRUE;
}

 void Serialize__S_REPORT_ITEM::SetData(_S_REPORT_ITEM & _X)
{
	szTestState=_X.szTestState; 
	szTestItemSource=_X.szTestItemSource; 
	szTestToolType=_X.szTestToolType; 
	szUniteStandardErrorNum=_X.szUniteStandardErrorNum; 
	szThirdStandardErrorNum=_X.szThirdStandardErrorNum; 
	szErrorCodeContent=_X.szErrorCodeContent; 
	szErrorCodePosition=_X.szErrorCodePosition; 
	szModule=_X.szModule; 
	szSuggest=_X.szSuggest; 
	szDesc=_X.szDesc; 
	szUniteSuggest=_X.szUniteSuggest; 
	szUniteDesc=_X.szUniteDesc; 
	szThirdSuggest=_X.szThirdSuggest; 
	szThirdDesc=_X.szThirdDesc; 
	szErrorType=_X.szErrorType; 
	szErrorWarning=_X.szErrorWarning; 
	szCreateTime=_X.szCreateTime; 
	szLastEditTime=_X.szLastEditTime; 
	szDevelopState=_X.szDevelopState; 
	szReport_log=_X.szReport_log; 
	szProcessUser=_X.szProcessUser;
}

BOOL Serialize__S_REPORT_ITEM::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szTestState")))
	{
		*RetObj=&szTestState;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szTestItemSource")))
	{
		*RetObj=&szTestItemSource;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szTestToolType")))
	{
		*RetObj=&szTestToolType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szUniteStandardErrorNum")))
	{
		*RetObj=&szUniteStandardErrorNum;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szThirdStandardErrorNum")))
	{
		*RetObj=&szThirdStandardErrorNum;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szErrorCodeContent")))
	{
		*RetObj=&szErrorCodeContent;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szErrorCodePosition")))
	{
		*RetObj=&szErrorCodePosition;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szModule")))
	{
		*RetObj=&szModule;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szSuggest")))
	{
		*RetObj=&szSuggest;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szDesc")))
	{
		*RetObj=&szDesc;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szUniteSuggest")))
	{
		*RetObj=&szUniteSuggest;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szUniteDesc")))
	{
		*RetObj=&szUniteDesc;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szThirdSuggest")))
	{
		*RetObj=&szThirdSuggest;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szThirdDesc")))
	{
		*RetObj=&szThirdDesc;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szErrorType")))
	{
		*RetObj=&szErrorType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szErrorWarning")))
	{
		*RetObj=&szErrorWarning;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szCreateTime")))
	{
		*RetObj=&szCreateTime;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szLastEditTime")))
	{
		*RetObj=&szLastEditTime;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szDevelopState")))
	{
		*RetObj=&szDevelopState;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szReport_log")))
	{
		*RetObj=&szReport_log;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szProcessUser")))
	{
		*RetObj=&szProcessUser;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__S_REPORT_ITEM::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_S_REPORT_ITEM"),this);

	szTestState.Save(pStorageObject); 
	szTestItemSource.Save(pStorageObject); 
	szTestToolType.Save(pStorageObject); 
	szUniteStandardErrorNum.Save(pStorageObject); 
	szThirdStandardErrorNum.Save(pStorageObject); 
	szErrorCodeContent.Save(pStorageObject); 
	szErrorCodePosition.Save(pStorageObject); 
	szModule.Save(pStorageObject); 
	szSuggest.Save(pStorageObject); 
	szDesc.Save(pStorageObject); 
	szUniteSuggest.Save(pStorageObject); 
	szUniteDesc.Save(pStorageObject); 
	szThirdSuggest.Save(pStorageObject); 
	szThirdDesc.Save(pStorageObject); 
	szErrorType.Save(pStorageObject); 
	szErrorWarning.Save(pStorageObject); 
	szCreateTime.Save(pStorageObject); 
	szLastEditTime.Save(pStorageObject); 
	szDevelopState.Save(pStorageObject); 
	szReport_log.Save(pStorageObject); 
	szProcessUser.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_S_REPORT_ITEM"),this);
	return TRUE;
}

BOOL Serialize__S_REPORT_ITEM::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szTestState); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szTestItemSource); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szTestToolType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szUniteStandardErrorNum); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szThirdStandardErrorNum); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szErrorCodeContent); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szErrorCodePosition); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szModule); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szSuggest); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szDesc); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szUniteSuggest); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szUniteDesc); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szThirdSuggest); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szThirdDesc); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szErrorType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szErrorWarning); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szCreateTime); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szLastEditTime); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szDevelopState); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szReport_log); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szProcessUser);
	return TRUE;
}




