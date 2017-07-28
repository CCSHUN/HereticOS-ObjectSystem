 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagMacroAttribute_StructInfo.h"

Serialize__tagMacroAttribute::_Myt& Serialize__tagMacroAttribute::operator=(_tagMacroAttribute & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagMacroAttribute::GetData()
{
	m_Val.bRootMacro=bRootMacro;
}

BOOL Serialize__tagMacroAttribute::Construct(StorageObjectInterface * pOutObject)
{
	bRootMacro.init(this,_T("bRootMacro"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagMacroAttribute::SetData(_tagMacroAttribute & _X)
{
	bRootMacro=_X.bRootMacro;
}

BOOL Serialize__tagMacroAttribute::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("bRootMacro")))
	{
		*RetObj=&bRootMacro;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagMacroAttribute::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagMacroAttribute"),this);

	bRootMacro.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagMacroAttribute"),this);
	return TRUE;
}

BOOL Serialize__tagMacroAttribute::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&bRootMacro);
	return TRUE;
}




