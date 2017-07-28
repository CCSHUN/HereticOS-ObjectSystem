 #pragma once
#include "Serialize.h"

class Serialize__tagUnitReport : public Serialize_StructBase<_tagUnitReport,Serialize__tagUnitReport>
{
	public:
	typedef _tagUnitReport _MyObjectType;
 
	Serialize_BaseObject<tstring> szID; 
	Serialize_BaseObject<tstring> szInheritID; 
	Serialize_vector< Serialize__tagUnitReportSet> UnitReportArray;

	Serialize__tagUnitReport(){};
	~Serialize__tagUnitReport(){};
	_Myt& operator=(_tagUnitReport & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagUnitReport & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
