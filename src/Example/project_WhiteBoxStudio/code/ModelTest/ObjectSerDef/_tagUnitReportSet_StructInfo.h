 #pragma once
#include "Serialize.h"

class Serialize__tagUnitReportSet : public Serialize_StructBase<_tagUnitReportSet,Serialize__tagUnitReportSet>
{
	public:
	typedef _tagUnitReportSet _MyObjectType;
 
	Serialize_BaseObject<int> nID; 
	Serialize_BaseObject<tstring> szState; 
	Serialize_BaseObject<tstring> szPrjName; 
	Serialize_BaseObject<tstring> szSysName; 
	Serialize_BaseObject<tstring> szModuleName; 
	Serialize_BaseObject<tstring> szTesterName; 
	Serialize_BaseObject<tstring> szJudgeName; 
	Serialize_BaseObject<tstring> szTestDate; 
	Serialize_BaseObject<tstring> szJudgeDate; 
	Serialize_BaseObject<tstring> szSug; 
	Serialize_BaseObject<int> nIVT; 
	Serialize_BaseObject<int> nINVT; 
	Serialize_BaseObject<int> nBT; 
	Serialize_BaseObject<int> nRCT; 
	Serialize_BaseObject<int> nTCCDT; 
	Serialize_BaseObject<double> fIVT; 
	Serialize_BaseObject<double> fINVT; 
	Serialize_BaseObject<double> fBT; 
	Serialize_BaseObject<double> fRCT; 
	Serialize_BaseObject<double> fTCCDT;

	Serialize__tagUnitReportSet(){};
	~Serialize__tagUnitReportSet(){};
	_Myt& operator=(_tagUnitReportSet & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagUnitReportSet & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
