 #pragma once
#include "Serialize.h"

class Serialize__S_REPORT : public Serialize_StructBase<_S_REPORT,Serialize__S_REPORT>
{
	public:
	typedef _S_REPORT _MyObjectType;
 
	Serialize_BaseObject<tstring> szName; 
	Serialize_BaseObject<unsigned long> nTotalErrorCount; 
	Serialize_BaseObject<unsigned long> nErrorCount_1; 
	Serialize_BaseObject<unsigned long> nErrorCount_2; 
	Serialize_BaseObject<unsigned long> nErrorCount_3; 
	Serialize_vector< Serialize__S_REPORT_ITEM> items;

	Serialize__S_REPORT(){};
	~Serialize__S_REPORT(){};
	_Myt& operator=(_S_REPORT & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_S_REPORT & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
