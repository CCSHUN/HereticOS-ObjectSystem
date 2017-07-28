 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagReportLog_StructInfo.h"

Serialize__tagReportLog::_Myt& Serialize__tagReportLog::operator=(_tagReportLog & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagReportLog::GetData()
{
	m_Val.szUserName=szUserName; 
	m_Val.tmDate=tmDate; 
	m_Val.szReport_log=szReport_log;
}

BOOL Serialize__tagReportLog::Construct(StorageObjectInterface * pOutObject)
{
	szUserName.init(this,_T("szUserName"),0,pOutObject); 
	tmDate.init(this,_T("tmDate"),0,pOutObject); 
	szReport_log.init(this,_T("szReport_log"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagReportLog::SetData(_tagReportLog & _X)
{
	szUserName=_X.szUserName; 
	tmDate=_X.tmDate; 
	szReport_log=_X.szReport_log;
}

BOOL Serialize__tagReportLog::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szUserName")))
	{
		*RetObj=&szUserName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("tmDate")))
	{
		*RetObj=&tmDate;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szReport_log")))
	{
		*RetObj=&szReport_log;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagReportLog::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagReportLog"),this);

	szUserName.Save(pStorageObject); 
	tmDate.Save(pStorageObject); 
	szReport_log.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagReportLog"),this);
	return TRUE;
}

BOOL Serialize__tagReportLog::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szUserName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&tmDate); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szReport_log);
	return TRUE;
}




