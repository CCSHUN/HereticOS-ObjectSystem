 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagReportOutput_Summary_StructInfo.h"

Serialize__tagReportOutput_Summary::_Myt& Serialize__tagReportOutput_Summary::operator=(_tagReportOutput_Summary & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagReportOutput_Summary::GetData()
{
	m_Val.nCurPos=nCurPos; 
	m_Val.szDesc=szDesc; 
	m_Val.nErrorTotal=nErrorTotal; 
	m_Val.nComplateTotal=nComplateTotal; 
	m_Val.nManaualTotal=nManaualTotal; 
	m_Val.nIgnoreTotal=nIgnoreTotal; 
	m_Val.szErrorType=szErrorType; 
	m_Val.szWaringType=szWaringType; 
	m_Val.szUniteNum=szUniteNum;
}

BOOL Serialize__tagReportOutput_Summary::Construct(StorageObjectInterface * pOutObject)
{
	nCurPos.init(this,_T("nCurPos"),0,pOutObject); 
	szDesc.init(this,_T("szDesc"),0,pOutObject); 
	nErrorTotal.init(this,_T("nErrorTotal"),0,pOutObject); 
	nComplateTotal.init(this,_T("nComplateTotal"),0,pOutObject); 
	nManaualTotal.init(this,_T("nManaualTotal"),0,pOutObject); 
	nIgnoreTotal.init(this,_T("nIgnoreTotal"),0,pOutObject); 
	szErrorType.init(this,_T("szErrorType"),0,pOutObject); 
	szWaringType.init(this,_T("szWaringType"),0,pOutObject); 
	szUniteNum.init(this,_T("szUniteNum"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagReportOutput_Summary::SetData(_tagReportOutput_Summary & _X)
{
	nCurPos=_X.nCurPos; 
	szDesc=_X.szDesc; 
	nErrorTotal=_X.nErrorTotal; 
	nComplateTotal=_X.nComplateTotal; 
	nManaualTotal=_X.nManaualTotal; 
	nIgnoreTotal=_X.nIgnoreTotal; 
	szErrorType=_X.szErrorType; 
	szWaringType=_X.szWaringType; 
	szUniteNum=_X.szUniteNum;
}

BOOL Serialize__tagReportOutput_Summary::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nCurPos")))
	{
		*RetObj=&nCurPos;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szDesc")))
	{
		*RetObj=&szDesc;
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
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szErrorType")))
	{
		*RetObj=&szErrorType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szWaringType")))
	{
		*RetObj=&szWaringType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szUniteNum")))
	{
		*RetObj=&szUniteNum;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagReportOutput_Summary::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagReportOutput_Summary"),this);

	nCurPos.Save(pStorageObject); 
	szDesc.Save(pStorageObject); 
	nErrorTotal.Save(pStorageObject); 
	nComplateTotal.Save(pStorageObject); 
	nManaualTotal.Save(pStorageObject); 
	nIgnoreTotal.Save(pStorageObject); 
	szErrorType.Save(pStorageObject); 
	szWaringType.Save(pStorageObject); 
	szUniteNum.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagReportOutput_Summary"),this);
	return TRUE;
}

BOOL Serialize__tagReportOutput_Summary::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nCurPos); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szDesc); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nErrorTotal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nComplateTotal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nManaualTotal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nIgnoreTotal); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szErrorType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szWaringType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szUniteNum);
	return TRUE;
}




