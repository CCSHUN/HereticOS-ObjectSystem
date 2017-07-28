 #pragma once
#include "Serialize.h"

class Serialize__tagProjectOwnUserSet : public Serialize_StructBase<_tagProjectOwnUserSet,Serialize__tagProjectOwnUserSet>
{
	public:
	typedef _tagProjectOwnUserSet _MyObjectType;
 
	Serialize_BaseObject<tstring> szUserName; 
	Serialize_BaseObject<tstring> szUserType;

	Serialize__tagProjectOwnUserSet(){};
	~Serialize__tagProjectOwnUserSet(){};
	_Myt& operator=(_tagProjectOwnUserSet & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagProjectOwnUserSet & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
