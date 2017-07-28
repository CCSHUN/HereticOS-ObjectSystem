 #pragma once
#include "Serialize.h"

class Serialize__tagUserMapSet : public Serialize_StructBase<_tagUserMapSet,Serialize__tagUserMapSet>
{
	public:
	typedef _tagUserMapSet _MyObjectType;
 
	Serialize_BaseObject<tstring> szUserName; 
	Serialize_BaseObject<tstring> szPassword; 
	Serialize_BaseObject<tstring> szUserType; 
	Serialize_BaseObject<tstring> szChildUserType; 
	Serialize_BaseObject<tstring> szChildUserType1;

	Serialize__tagUserMapSet(){};
	~Serialize__tagUserMapSet(){};
	_Myt& operator=(_tagUserMapSet & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagUserMapSet & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
