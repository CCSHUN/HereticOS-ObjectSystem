 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagUnitReportSet_StructInfo.h"

Serialize__tagUnitReportSet::_Myt& Serialize__tagUnitReportSet::operator=(_tagUnitReportSet & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagUnitReportSet::GetData()
{
	m_Val.nID=nID; 
	m_Val.szState=szState; 
	m_Val.szPrjName=szPrjName; 
	m_Val.szSysName=szSysName; 
	m_Val.szModuleName=szModuleName; 
	m_Val.szTesterName=szTesterName; 
	m_Val.szJudgeName=szJudgeName; 
	m_Val.szTestDate=szTestDate; 
	m_Val.szJudgeDate=szJudgeDate; 
	m_Val.szSug=szSug; 
	m_Val.nIVT=nIVT; 
	m_Val.nINVT=nINVT; 
	m_Val.nBT=nBT; 
	m_Val.nRCT=nRCT; 
	m_Val.nTCCDT=nTCCDT; 
	m_Val.fIVT=fIVT; 
	m_Val.fINVT=fINVT; 
	m_Val.fBT=fBT; 
	m_Val.fRCT=fRCT; 
	m_Val.fTCCDT=fTCCDT;
}

BOOL Serialize__tagUnitReportSet::Construct(StorageObjectInterface * pOutObject)
{
	nID.init(this,_T("nID"),0,pOutObject); 
	szState.init(this,_T("szState"),0,pOutObject); 
	szPrjName.init(this,_T("szPrjName"),0,pOutObject); 
	szSysName.init(this,_T("szSysName"),0,pOutObject); 
	szModuleName.init(this,_T("szModuleName"),0,pOutObject); 
	szTesterName.init(this,_T("szTesterName"),0,pOutObject); 
	szJudgeName.init(this,_T("szJudgeName"),0,pOutObject); 
	szTestDate.init(this,_T("szTestDate"),0,pOutObject); 
	szJudgeDate.init(this,_T("szJudgeDate"),0,pOutObject); 
	szSug.init(this,_T("szSug"),0,pOutObject); 
	nIVT.init(this,_T("nIVT"),0,pOutObject); 
	nINVT.init(this,_T("nINVT"),0,pOutObject); 
	nBT.init(this,_T("nBT"),0,pOutObject); 
	nRCT.init(this,_T("nRCT"),0,pOutObject); 
	nTCCDT.init(this,_T("nTCCDT"),0,pOutObject); 
	fIVT.init(this,_T("fIVT"),0,pOutObject); 
	fINVT.init(this,_T("fINVT"),0,pOutObject); 
	fBT.init(this,_T("fBT"),0,pOutObject); 
	fRCT.init(this,_T("fRCT"),0,pOutObject); 
	fTCCDT.init(this,_T("fTCCDT"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagUnitReportSet::SetData(_tagUnitReportSet & _X)
{
	nID=_X.nID; 
	szState=_X.szState; 
	szPrjName=_X.szPrjName; 
	szSysName=_X.szSysName; 
	szModuleName=_X.szModuleName; 
	szTesterName=_X.szTesterName; 
	szJudgeName=_X.szJudgeName; 
	szTestDate=_X.szTestDate; 
	szJudgeDate=_X.szJudgeDate; 
	szSug=_X.szSug; 
	nIVT=_X.nIVT; 
	nINVT=_X.nINVT; 
	nBT=_X.nBT; 
	nRCT=_X.nRCT; 
	nTCCDT=_X.nTCCDT; 
	fIVT=_X.fIVT; 
	fINVT=_X.fINVT; 
	fBT=_X.fBT; 
	fRCT=_X.fRCT; 
	fTCCDT=_X.fTCCDT;
}

BOOL Serialize__tagUnitReportSet::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nID")))
	{
		*RetObj=&nID;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szState")))
	{
		*RetObj=&szState;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szPrjName")))
	{
		*RetObj=&szPrjName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szSysName")))
	{
		*RetObj=&szSysName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szModuleName")))
	{
		*RetObj=&szModuleName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szTesterName")))
	{
		*RetObj=&szTesterName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szJudgeName")))
	{
		*RetObj=&szJudgeName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szTestDate")))
	{
		*RetObj=&szTestDate;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szJudgeDate")))
	{
		*RetObj=&szJudgeDate;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szSug")))
	{
		*RetObj=&szSug;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nIVT")))
	{
		*RetObj=&nIVT;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nINVT")))
	{
		*RetObj=&nINVT;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nBT")))
	{
		*RetObj=&nBT;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nRCT")))
	{
		*RetObj=&nRCT;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nTCCDT")))
	{
		*RetObj=&nTCCDT;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("fIVT")))
	{
		*RetObj=&fIVT;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("fINVT")))
	{
		*RetObj=&fINVT;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("fBT")))
	{
		*RetObj=&fBT;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("fRCT")))
	{
		*RetObj=&fRCT;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("fTCCDT")))
	{
		*RetObj=&fTCCDT;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagUnitReportSet::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagUnitReportSet"),this);

	nID.Save(pStorageObject); 
	szState.Save(pStorageObject); 
	szPrjName.Save(pStorageObject); 
	szSysName.Save(pStorageObject); 
	szModuleName.Save(pStorageObject); 
	szTesterName.Save(pStorageObject); 
	szJudgeName.Save(pStorageObject); 
	szTestDate.Save(pStorageObject); 
	szJudgeDate.Save(pStorageObject); 
	szSug.Save(pStorageObject); 
	nIVT.Save(pStorageObject); 
	nINVT.Save(pStorageObject); 
	nBT.Save(pStorageObject); 
	nRCT.Save(pStorageObject); 
	nTCCDT.Save(pStorageObject); 
	fIVT.Save(pStorageObject); 
	fINVT.Save(pStorageObject); 
	fBT.Save(pStorageObject); 
	fRCT.Save(pStorageObject); 
	fTCCDT.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagUnitReportSet"),this);
	return TRUE;
}

BOOL Serialize__tagUnitReportSet::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nID); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szState); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szPrjName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szSysName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szModuleName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szTesterName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szJudgeName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szTestDate); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szJudgeDate); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szSug); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nIVT); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nINVT); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nBT); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nRCT); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nTCCDT); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&fIVT); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&fINVT); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&fBT); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&fRCT); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&fTCCDT);
	return TRUE;
}




