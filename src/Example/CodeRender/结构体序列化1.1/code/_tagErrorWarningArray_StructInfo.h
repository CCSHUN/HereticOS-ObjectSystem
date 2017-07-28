 #pragma once
#include "Serialize.h"

class Serialize__tagErrorWarningArray : public Serialize_StructBase<_tagErrorWarningArray,Serialize__tagErrorWarningArray>
{
	public:
	typedef _tagErrorWarningArray _MyObjectType;
 
	Serialize_vector< Serialize__tagErrorWarningSet> WarningArray;
	Serialize__tagErrorWarningArray(){};
	~Serialize__tagErrorWarningArray(){};
	_Myt& operator=(_tagErrorWarningArray & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagErrorWarningArray & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
