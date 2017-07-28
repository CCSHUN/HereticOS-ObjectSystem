 #pragma once

class Serialize__tagDirectoryInfo : public Serialize_StructBase<_tagDirectoryInfo,Serialize__tagDirectoryInfo>
{
	public:
	typedef _tagDirectoryInfo _MyObjectType;
 
	Serialize_vector< Serialize__tagDirectoryInfoSet> DirectoryInfoArray;
	Serialize__tagDirectoryInfo(){};
	~Serialize__tagDirectoryInfo(){};
	_Myt& operator=(_tagDirectoryInfo & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagDirectoryInfo & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
