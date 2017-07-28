 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagPCLintReportItem_StructInfo.h"

Serialize__tagPCLintReportItem::_Myt& Serialize__tagPCLintReportItem::operator=(_tagPCLintReportItem & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagPCLintReportItem::GetData()
{
	m_Val.filename=filename; 
	m_Val.errorno=errorno; 
	m_Val.rowno=rowno; 
	m_Val.msgtxt=msgtxt;
}

BOOL Serialize__tagPCLintReportItem::Construct(StorageObjectInterface * pOutObject)
{
	filename.init(this,_T("filename"),0,pOutObject); 
	errorno.init(this,_T("errorno"),0,pOutObject); 
	rowno.init(this,_T("rowno"),0,pOutObject); 
	msgtxt.init(this,_T("msgtxt"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagPCLintReportItem::SetData(_tagPCLintReportItem & _X)
{
	filename=_X.filename; 
	errorno=_X.errorno; 
	rowno=_X.rowno; 
	msgtxt=_X.msgtxt;
}

BOOL Serialize__tagPCLintReportItem::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("filename")))
	{
		*RetObj=&filename;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("errorno")))
	{
		*RetObj=&errorno;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("rowno")))
	{
		*RetObj=&rowno;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("msgtxt")))
	{
		*RetObj=&msgtxt;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagPCLintReportItem::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagPCLintReportItem"),this);

	filename.Save(pStorageObject); 
	errorno.Save(pStorageObject); 
	rowno.Save(pStorageObject); 
	msgtxt.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagPCLintReportItem"),this);
	return TRUE;
}

BOOL Serialize__tagPCLintReportItem::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&filename); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&errorno); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&rowno); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&msgtxt);
	return TRUE;
}




