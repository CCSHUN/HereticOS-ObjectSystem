 #pragma once
#include "Serialize.h"

class Serialize__tagTestHexString : public Serialize_StructBase<_tagTestHexString,Serialize__tagTestHexString>
{
	public:
	typedef _tagTestHexString _MyObjectType;
 
	Serialize_BaseObject<SER_TO_X<tstring ,HexString>> Test;
	Serialize__tagTestHexString(){};
	~Serialize__tagTestHexString(){};
	_Myt& operator=(_tagTestHexString & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagTestHexString & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
