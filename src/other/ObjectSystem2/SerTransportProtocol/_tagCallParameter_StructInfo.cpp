 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagCallParameter_StructInfo.h"

Serialize__tagCallParameter::_Myt& Serialize__tagCallParameter::operator=(_tagCallParameter & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagCallParameter::GetData()
{
	m_Val.su=su; 
	m_Val.ss=ss; 
	m_Val.oc=oc; 
	m_Val.bcs=bcs; 
	m_Val.op=op; 
	m_Val.np=np; 
	m_Val.ob=ob; 
	m_Val.Os=Os; 
	m_Val.Err=Err; 
	m_Val.sf=sf; 
	m_Val.di=di; 
	m_Val.el=el; 
	m_Val.sp=sp;
}

BOOL Serialize__tagCallParameter::Construct(StorageObjectInterface * pOutObject)
{
	su.init(this,_T("su"),0,pOutObject); 
	ss.init(this,_T("ss"),0,pOutObject); 
	oc.init(this,_T("oc"),0,pOutObject); 
	bcs.init(this,_T("bcs"),0,pOutObject); 
	op.init(this,_T("op"),0,pOutObject); 
	np.init(this,_T("np"),0,pOutObject); 
	ob.init(this,_T("ob"),0,pOutObject); 
	Os.init(this,_T("Os"),0,pOutObject); 
	Err.init(this,_T("Err"),0,pOutObject); 
	sf.init(this,_T("sf"),0,pOutObject); 
	di.init(this,_T("di"),0,pOutObject); 
	el.init(this,_T("el"),0,pOutObject); 
	sp.init(this,_T("sp"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagCallParameter::SetData(_tagCallParameter & _X)
{
	su=_X.su; 
	ss=_X.ss; 
	oc=_X.oc; 
	bcs=_X.bcs; 
	op=_X.op; 
	np=_X.np; 
	ob=_X.ob; 
	Os=_X.Os; 
	Err=_X.Err; 
	sf=_X.sf; 
	di=_X.di; 
	el=_X.el; 
	sp=_X.sp;
}

BOOL Serialize__tagCallParameter::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("su")))
	{
		*RetObj=&su;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ss")))
	{
		*RetObj=&ss;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("oc")))
	{
		*RetObj=&oc;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("bcs")))
	{
		*RetObj=&bcs;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("op")))
	{
		*RetObj=&op;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("np")))
	{
		*RetObj=&np;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ob")))
	{
		*RetObj=&ob;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Os")))
	{
		*RetObj=&Os;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Err")))
	{
		*RetObj=&Err;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("sf")))
	{
		*RetObj=&sf;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("di")))
	{
		*RetObj=&di;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("el")))
	{
		*RetObj=&el;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("sp")))
	{
		*RetObj=&sp;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagCallParameter::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagCallParameter"),this);

	su.Save(pStorageObject); 
	ss.Save(pStorageObject); 
	oc.Save(pStorageObject); 
	bcs.Save(pStorageObject); 
	op.Save(pStorageObject); 
	np.Save(pStorageObject); 
	ob.Save(pStorageObject); 
	Os.Save(pStorageObject); 
	Err.Save(pStorageObject); 
	sf.Save(pStorageObject); 
	di.Save(pStorageObject); 
	el.Save(pStorageObject); 
	sp.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagCallParameter"),this);
	return TRUE;
}

BOOL Serialize__tagCallParameter::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&su); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ss); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&oc); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&bcs); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&op); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&np); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ob); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&Os); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&Err); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&sf); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&di); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&el); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&sp);
	return TRUE;
}




