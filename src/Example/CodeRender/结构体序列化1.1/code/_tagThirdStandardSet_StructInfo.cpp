 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagThirdStandardSet_StructInfo.h"

Serialize__tagThirdStandardSet::_Myt& Serialize__tagThirdStandardSet::operator=(_tagThirdStandardSet & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagThirdStandardSet::GetData()
{
	m_Val.szUniteStandardErrorNum=szUniteStandardErrorNum; 
	m_Val.szThirdStandardErrorNum=szThirdStandardErrorNum; 
	m_Val.szThirdStandardErrorDesc=szThirdStandardErrorDesc; 
	m_Val.szErrorSuggest=szErrorSuggest; 
	m_Val.is_manual_check=is_manual_check; 
	m_Val.szManual_check_MethodSpecify=szManual_check_MethodSpecify; 
	m_Val.is_dealwith=is_dealwith; 
	m_Val.ToolType=ToolType;
}

BOOL Serialize__tagThirdStandardSet::Construct(StorageObjectInterface * pOutObject)
{
	szUniteStandardErrorNum.init(this,_T("szUniteStandardErrorNum"),0,pOutObject); 
	szThirdStandardErrorNum.init(this,_T("szThirdStandardErrorNum"),0,pOutObject); 
	szThirdStandardErrorDesc.init(this,_T("szThirdStandardErrorDesc"),0,pOutObject); 
	szErrorSuggest.init(this,_T("szErrorSuggest"),0,pOutObject); 
	is_manual_check.init(this,_T("is_manual_check"),0,pOutObject); 
	szManual_check_MethodSpecify.init(this,_T("szManual_check_MethodSpecify"),0,pOutObject); 
	is_dealwith.init(this,_T("is_dealwith"),0,pOutObject); 
	ToolType.init(this,_T("ToolType"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagThirdStandardSet::SetData(_tagThirdStandardSet & _X)
{
	szUniteStandardErrorNum=_X.szUniteStandardErrorNum; 
	szThirdStandardErrorNum=_X.szThirdStandardErrorNum; 
	szThirdStandardErrorDesc=_X.szThirdStandardErrorDesc; 
	szErrorSuggest=_X.szErrorSuggest; 
	is_manual_check=_X.is_manual_check; 
	szManual_check_MethodSpecify=_X.szManual_check_MethodSpecify; 
	is_dealwith=_X.is_dealwith; 
	ToolType=_X.ToolType;
}

BOOL Serialize__tagThirdStandardSet::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szUniteStandardErrorNum")))
	{
		*RetObj=&szUniteStandardErrorNum;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szThirdStandardErrorNum")))
	{
		*RetObj=&szThirdStandardErrorNum;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szThirdStandardErrorDesc")))
	{
		*RetObj=&szThirdStandardErrorDesc;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szErrorSuggest")))
	{
		*RetObj=&szErrorSuggest;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("is_manual_check")))
	{
		*RetObj=&is_manual_check;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szManual_check_MethodSpecify")))
	{
		*RetObj=&szManual_check_MethodSpecify;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("is_dealwith")))
	{
		*RetObj=&is_dealwith;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ToolType")))
	{
		*RetObj=&ToolType;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagThirdStandardSet::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagThirdStandardSet"),this);

	szUniteStandardErrorNum.Save(pStorageObject); 
	szThirdStandardErrorNum.Save(pStorageObject); 
	szThirdStandardErrorDesc.Save(pStorageObject); 
	szErrorSuggest.Save(pStorageObject); 
	is_manual_check.Save(pStorageObject); 
	szManual_check_MethodSpecify.Save(pStorageObject); 
	is_dealwith.Save(pStorageObject); 
	ToolType.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagThirdStandardSet"),this);
	return TRUE;
}

BOOL Serialize__tagThirdStandardSet::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szUniteStandardErrorNum); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szThirdStandardErrorNum); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szThirdStandardErrorDesc); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szErrorSuggest); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&is_manual_check); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szManual_check_MethodSpecify); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&is_dealwith); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ToolType);
	return TRUE;
}




