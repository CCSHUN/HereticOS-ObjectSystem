 #pragma once
#include "Serialize.h"

class Serialize__tagObjectStateSoap : public Serialize_StructBase<_tagObjectStateSoap,Serialize__tagObjectStateSoap>
{
	public:
	typedef _tagObjectStateSoap _MyObjectType;
 
	Serialize_BaseObject<BOOL> bLock; 
	Serialize_BaseObject<unsigned int> nType; 
	Serialize_BaseObject<tstring> szLockUser; 
	Serialize_BaseObject<unsigned int> nLockTime;

	Serialize__tagObjectStateSoap(){};
	~Serialize__tagObjectStateSoap(){};
	_Myt& operator=(_tagObjectStateSoap & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagObjectStateSoap & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
