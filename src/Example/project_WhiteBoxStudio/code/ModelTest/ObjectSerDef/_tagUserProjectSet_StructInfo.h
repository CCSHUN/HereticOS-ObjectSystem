 #pragma once
#include "Serialize.h"

class Serialize__tagUserProjectSet : public Serialize_StructBase<_tagUserProjectSet,Serialize__tagUserProjectSet>
{
	public:
	typedef _tagUserProjectSet _MyObjectType;
 
	Serialize_BaseObject<tstring> szUserName; 
	Serialize_BaseObject<tstring> szProjectName;

	Serialize__tagUserProjectSet(){};
	~Serialize__tagUserProjectSet(){};
	_Myt& operator=(_tagUserProjectSet & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagUserProjectSet & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
