 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagReportOutput_Overall_StructInfo.h"

Serialize__tagReportOutput_Overall::_Myt& Serialize__tagReportOutput_Overall::operator=(_tagReportOutput_Overall & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagReportOutput_Overall::GetData()
{
	m_Val.nDescTotal=nDescTotal; 
	m_Val.nErrorTotal=nErrorTotal; 
	m_Val.nComplateTotal=nComplateTotal; 
	m_Val.nManaualTotal=nManaualTotal; 
	m_Val.nIgnoreTotal=nIgnoreTotal;
}

BOOL Serialize__tagReportOutput_Overall::Construct(StorageObjectInterface * pOutObject)
{
	nDescTotal.init(this,_T("nDescTotal"),0,pOutObject); 
	nErrorTotal.init(this,_T("nErrorTotal"),0,pOutObject); 
	nComplateTotal.init(this,_T("nComplateTotal"),0,pOutObject); 
	nManaualTotal.init(this,_T("nManaualTotal"),0,pOutObject); 
	nIgnoreTotal.init(this,_T("nIgnoreTotal"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagReportOutput_Overall::SetData(_tagReportOutput_Overall & _X)
{
	nDescTotal=_X.nDescTotal; 
	nErrorTotal=_X.nErrorTotal; 
	nComplateTotal=_X.nComplateTotal; 
	nManaualTotal=_X.nManaualTotal; 
	nIgnoreTotal=_X.nIgnoreTotal;
}

BOOL Serialize__tagReportOutput_Overall::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nDescTotal")))
	{
		*RetObj=&nDescTotal;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nErrorTotal")))
	{
		*RetObj=&nErrorTotal;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nComplateTotal")))
	{
		*RetObj=&nComplateTotal;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nManaualTotal")))
	{
		*RetObj=&nManaualTotal;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nIgnoreTotal")))
	{
		*RetObj=&nIgnoreTotal;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagReportOutput_Overall::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagReportOutput_Overall"),this);

	nDescTotal.Save(pStorageObject); 
	nErrorTotal.Save(pStorageObject); 
	nComplateTotal.Save(pStorageObject); 
	nManaualTotal.Save(pStorageObject); 
	nIgnoreTotal.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagReportOutput_Overall"),this);
	return TRUE;
}

BOOL Serialize__tagReportOutput_Overall::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nDescTotal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nErrorTotal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nComplateTotal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nManaualTotal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nIgnoreTotal);
	return TRUE;
}




