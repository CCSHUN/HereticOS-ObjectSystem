 #pragma once
#include "Serialize.h"

class Serialize__tagProjectOwnUser : public Serialize_StructBase<_tagProjectOwnUser,Serialize__tagProjectOwnUser>
{
	public:
	typedef _tagProjectOwnUser _MyObjectType;
 
	Serialize_map<Serialize_BaseObject<tstring> ,Serialize__tagProjectOwnUserSet ,less<tstring>> OwnUserMap;
	Serialize__tagProjectOwnUser(){};
	~Serialize__tagProjectOwnUser(){};
	_Myt& operator=(_tagProjectOwnUser & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagProjectOwnUser & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
