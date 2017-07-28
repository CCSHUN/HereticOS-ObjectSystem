 #pragma once
#include "Serialize.h"

class Serialize__tagDirectoryInfoSetSoap : public Serialize_StructBase<_tagDirectoryInfoSetSoap,Serialize__tagDirectoryInfoSetSoap>
{
	public:
	typedef _tagDirectoryInfoSetSoap _MyObjectType;
 
	Serialize_BaseObject<tstring> ObjectName; 
	Serialize_BaseObject<unsigned int> ObjectType; 
	Serialize_BaseObject<tstring> OtherInfo;

	Serialize__tagDirectoryInfoSetSoap(){};
	~Serialize__tagDirectoryInfoSetSoap(){};
	_Myt& operator=(_tagDirectoryInfoSetSoap & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagDirectoryInfoSetSoap & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
