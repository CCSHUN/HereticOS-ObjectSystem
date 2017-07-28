 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagMacroDef_StructInfo.h"

Serialize__tagMacroDef::_Myt& Serialize__tagMacroDef::operator=(_tagMacroDef & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagMacroDef::GetData()
{
	m_Val.nMacroID=nMacroID; 
	m_Val.szMacroName=szMacroName; 
	m_Val.szMacroDesc=szMacroDesc; 
	m_Val.szMacroType=szMacroType; 
	m_Val.MacroAttr=MacroAttr; 
	m_Val.ChildMacroIDArray=ChildMacroIDArray; 
	m_Val.tParamidRecover=tParamidRecover; 
	m_Val.ChildParArray=ChildParArray;
}

BOOL Serialize__tagMacroDef::Construct(StorageObjectInterface * pOutObject)
{
	nMacroID.init(this,_T("nMacroID"),0,pOutObject); 
	szMacroName.init(this,_T("szMacroName"),0,pOutObject); 
	szMacroDesc.init(this,_T("szMacroDesc"),0,pOutObject); 
	szMacroType.init(this,_T("szMacroType"),0,pOutObject); 
	MacroAttr.init(this,_T("MacroAttr"),0,pOutObject); 
	ChildMacroIDArray.init(this,_T("ChildMacroIDArray"),0,pOutObject); 
	tParamidRecover.init(this,_T("tParamidRecover"),0,pOutObject); 
	ChildParArray.init(this,_T("ChildParArray"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagMacroDef::SetData(_tagMacroDef & _X)
{
	nMacroID=_X.nMacroID; 
	szMacroName=_X.szMacroName; 
	szMacroDesc=_X.szMacroDesc; 
	szMacroType=_X.szMacroType; 
	MacroAttr=_X.MacroAttr; 
	ChildMacroIDArray=_X.ChildMacroIDArray; 
	tParamidRecover=_X.tParamidRecover; 
	ChildParArray=_X.ChildParArray;
}

BOOL Serialize__tagMacroDef::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nMacroID")))
	{
		*RetObj=&nMacroID;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szMacroName")))
	{
		*RetObj=&szMacroName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szMacroDesc")))
	{
		*RetObj=&szMacroDesc;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szMacroType")))
	{
		*RetObj=&szMacroType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("MacroAttr")))
	{
		*RetObj=&MacroAttr;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ChildMacroIDArray")))
	{
		*RetObj=&ChildMacroIDArray;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("tParamidRecover")))
	{
		*RetObj=&tParamidRecover;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ChildParArray")))
	{
		*RetObj=&ChildParArray;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagMacroDef::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagMacroDef"),this);

	nMacroID.Save(pStorageObject); 
	szMacroName.Save(pStorageObject); 
	szMacroDesc.Save(pStorageObject); 
	szMacroType.Save(pStorageObject); 
	MacroAttr.Save(pStorageObject); 
	ChildMacroIDArray.Save(pStorageObject); 
	tParamidRecover.Save(pStorageObject); 
	ChildParArray.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagMacroDef"),this);
	return TRUE;
}

BOOL Serialize__tagMacroDef::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nMacroID); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szMacroName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szMacroDesc); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szMacroType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&MacroAttr); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ChildMacroIDArray); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&tParamidRecover); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ChildParArray);
	return TRUE;
}




