 #pragma once

class Serialize__tagDirectoryInfoSet : public Serialize_StructBase<_tagDirectoryInfoSet,Serialize__tagDirectoryInfoSet>
{
	public:
	typedef _tagDirectoryInfoSet _MyObjectType;
 
	Serialize_BaseObject<tstring> ObjectName; 
	Serialize_BaseObject<unsigned int> ObjectType; 
	Serialize_BaseObject<tstring> OtherInfo;

	Serialize__tagDirectoryInfoSet(){};
	~Serialize__tagDirectoryInfoSet(){};
	_Myt& operator=(_tagDirectoryInfoSet & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagDirectoryInfoSet & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
