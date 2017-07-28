 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagProjectConfig_StructInfo.h"

Serialize__tagProjectConfig::_Myt& Serialize__tagProjectConfig::operator=(_tagProjectConfig & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagProjectConfig::GetData()
{
	m_Val.WorksheetStandard=WorksheetStandard; 
	m_Val.CheckCfgStandard=CheckCfgStandard; 
	m_Val.TestReportStandard=TestReportStandard;
}

BOOL Serialize__tagProjectConfig::Construct(StorageObjectInterface * pOutObject)
{
	WorksheetStandard.init(this,_T("WorksheetStandard"),0,pOutObject); 
	CheckCfgStandard.init(this,_T("CheckCfgStandard"),0,pOutObject); 
	TestReportStandard.init(this,_T("TestReportStandard"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagProjectConfig::SetData(_tagProjectConfig & _X)
{
	WorksheetStandard=_X.WorksheetStandard; 
	CheckCfgStandard=_X.CheckCfgStandard; 
	TestReportStandard=_X.TestReportStandard;
}

BOOL Serialize__tagProjectConfig::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("WorksheetStandard")))
	{
		*RetObj=&WorksheetStandard;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("CheckCfgStandard")))
	{
		*RetObj=&CheckCfgStandard;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("TestReportStandard")))
	{
		*RetObj=&TestReportStandard;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagProjectConfig::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagProjectConfig"),this);

	WorksheetStandard.Save(pStorageObject); 
	CheckCfgStandard.Save(pStorageObject); 
	TestReportStandard.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagProjectConfig"),this);
	return TRUE;
}

BOOL Serialize__tagProjectConfig::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&WorksheetStandard); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&CheckCfgStandard); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&TestReportStandard);
	return TRUE;
}




