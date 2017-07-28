 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagReportOutput_StructInfo.h"

Serialize__tagReportOutput::_Myt& Serialize__tagReportOutput::operator=(_tagReportOutput & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagReportOutput::GetData()
{
	m_Val.Overall=Overall; 
	m_Val.Summary=Summary; 
	m_Val.Detailed=Detailed;
}

BOOL Serialize__tagReportOutput::Construct(StorageObjectInterface * pOutObject)
{
	Overall.init(this,_T("Overall"),0,pOutObject); 
	Summary.init(this,_T("Summary"),0,pOutObject); 
	Detailed.init(this,_T("Detailed"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagReportOutput::SetData(_tagReportOutput & _X)
{
	Overall=_X.Overall; 
	Summary=_X.Summary; 
	Detailed=_X.Detailed;
}

BOOL Serialize__tagReportOutput::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Overall")))
	{
		*RetObj=&Overall;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Summary")))
	{
		*RetObj=&Summary;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Detailed")))
	{
		*RetObj=&Detailed;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagReportOutput::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagReportOutput"),this);

	Overall.Save(pStorageObject); 
	Summary.Save(pStorageObject); 
	Detailed.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagReportOutput"),this);
	return TRUE;
}

BOOL Serialize__tagReportOutput::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&Overall); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&Summary); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&Detailed);
	return TRUE;
}




