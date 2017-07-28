 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagReportOutput_Detailed_StructInfo.h"

Serialize__tagReportOutput_Detailed::_Myt& Serialize__tagReportOutput_Detailed::operator=(_tagReportOutput_Detailed & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagReportOutput_Detailed::GetData()
{
	m_Val.szDetailed=szDetailed;
}

BOOL Serialize__tagReportOutput_Detailed::Construct(StorageObjectInterface * pOutObject)
{
	szDetailed.init(this,_T("szDetailed"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagReportOutput_Detailed::SetData(_tagReportOutput_Detailed & _X)
{
	szDetailed=_X.szDetailed;
}

BOOL Serialize__tagReportOutput_Detailed::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szDetailed")))
	{
		*RetObj=&szDetailed;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagReportOutput_Detailed::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagReportOutput_Detailed"),this);

	szDetailed.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagReportOutput_Detailed"),this);
	return TRUE;
}

BOOL Serialize__tagReportOutput_Detailed::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szDetailed);
	return TRUE;
}




