 #pragma once
#include "Serialize.h"

class Serialize__tagErrorWarningSet : public Serialize_StructBase<_tagErrorWarningSet,Serialize__tagErrorWarningSet>
{
	public:
	typedef _tagErrorWarningSet _MyObjectType;
 
	Serialize_BaseObject<SER_TO_X<tstring ,HexString>> szErrorWarningName; 
	Serialize_BaseObject<SER_TO_X<tstring ,HexString>> szErrorWarningDesc;

	Serialize__tagErrorWarningSet(){};
	~Serialize__tagErrorWarningSet(){};
	_Myt& operator=(_tagErrorWarningSet & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagErrorWarningSet & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
