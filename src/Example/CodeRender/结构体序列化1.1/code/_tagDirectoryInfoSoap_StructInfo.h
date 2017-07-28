 #pragma once
#include "Serialize.h"

class Serialize__tagDirectoryInfoSoap : public Serialize_StructBase<_tagDirectoryInfoSoap,Serialize__tagDirectoryInfoSoap>
{
	public:
	typedef _tagDirectoryInfoSoap _MyObjectType;
 
	Serialize_vector< Serialize__tagDirectoryInfoSetSoap> DirectoryInfoArray;
	Serialize__tagDirectoryInfoSoap(){};
	~Serialize__tagDirectoryInfoSoap(){};
	_Myt& operator=(_tagDirectoryInfoSoap & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagDirectoryInfoSoap & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
