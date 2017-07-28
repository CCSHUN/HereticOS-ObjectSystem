 #pragma once
#include "Serialize.h"

class Serialize__tagProcessInfo : public Serialize_StructBase<_tagProcessInfo,Serialize__tagProcessInfo>
{
	public:
	typedef _tagProcessInfo _MyObjectType;
 
	Serialize__PROCESS_MEMORY_COUNTERS Meminfo; 
	Serialize_vector< Serialize__IO_COUNTERS> IOInfo; 
	Serialize_map<Serialize_BaseObject<unsigned int> ,Serialize__PROCESS_MEMORY_COUNTERS ,less<unsigned int>> MeminfoMap; 
	Serialize_BaseObjectBinaryArray<DWORD,256> nBuf; 
	Serialize_BaseObjectStringArray<TCHAR,128> szString; 
	Serialize_BaseObject<double> test111; 
	Serialize_vector< Serialize_BaseObject<tstring>> szTest; 
	Serialize_BaseObject<SER_TO_X<DWORD ,HexString>> Test; 
	Serialize_BaseObject<__int64> nTest1; 
	Serialize_BaseObject<SER_TO_X<__int64 ,HexString>> nTest2;

 	Serialize__tagProcessInfo(){};
	~Serialize__tagProcessInfo(){};
 	_Myt& operator=(_tagProcessInfo & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.Meminfo=Meminfo; 
		m_Val.IOInfo=IOInfo; 
		m_Val.MeminfoMap=MeminfoMap; 
		memcpy(m_Val.nBuf,(DWORD*)nBuf,sizeof(m_Val.nBuf)); 
		memcpy(m_Val.szString,(TCHAR*)szString,sizeof(m_Val.szString)); 
		m_Val.test111=test111; 
		m_Val.szTest=szTest; 
		m_Val.Test=Test; 
		m_Val.nTest1=nTest1; 
		m_Val.nTest2=nTest2;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		Meminfo.init(this,_T("Meminfo"),0,pOutObject); 
		IOInfo.init(this,_T("IOInfo"),0,pOutObject); 
		MeminfoMap.init(this,_T("MeminfoMap"),0,pOutObject); 
		nBuf.init(this,_T("nBuf"),0,pOutObject); 
		szString.init(this,_T("szString"),0,pOutObject); 
		test111.init(this,_T("test111"),0,pOutObject); 
		szTest.init(this,_T("szTest"),0,pOutObject); 
		Test.init(this,_T("Test"),0,pOutObject); 
		nTest1.init(this,_T("nTest1"),0,pOutObject); 
		nTest2.init(this,_T("nTest2"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagProcessInfo & _X)
	{
		Meminfo=_X.Meminfo; 
		IOInfo=_X.IOInfo; 
		MeminfoMap=_X.MeminfoMap; 
		nBuf=_X.nBuf; 
		szString=_X.szString; 
		test111=_X.test111; 
		szTest=_X.szTest; 
		Test=_X.Test; 
		nTest1=_X.nTest1; 
		nTest2=_X.nTest2;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Meminfo")))
		{
			*RetObj=&Meminfo;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("IOInfo")))
		{
			*RetObj=&IOInfo;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("MeminfoMap")))
		{
			*RetObj=&MeminfoMap;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nBuf")))
		{
			*RetObj=&nBuf;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szString")))
		{
			*RetObj=&szString;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("test111")))
		{
			*RetObj=&test111;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szTest")))
		{
			*RetObj=&szTest;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Test")))
		{
			*RetObj=&Test;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nTest1")))
		{
			*RetObj=&nTest1;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nTest2")))
		{
			*RetObj=&nTest2;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagProcessInfo"),this);

		Meminfo.Save(pStorageObject); 
		IOInfo.Save(pStorageObject); 
		MeminfoMap.Save(pStorageObject); 
		nBuf.Save(pStorageObject); 
		szString.Save(pStorageObject); 
		test111.Save(pStorageObject); 
		szTest.Save(pStorageObject); 
		Test.Save(pStorageObject); 
		nTest1.Save(pStorageObject); 
		nTest2.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagProcessInfo"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&Meminfo); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&IOInfo); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&MeminfoMap); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nBuf); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szString); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&test111); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szTest); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&Test); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nTest1); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nTest2);
		return TRUE;
	}
 

};
