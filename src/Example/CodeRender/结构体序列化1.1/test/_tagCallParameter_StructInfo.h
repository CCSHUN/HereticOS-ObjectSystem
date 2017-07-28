 #pragma once

class Serialize__tagCallParameter : public Serialize_StructBase<_tagCallParameter,Serialize__tagCallParameter>
{
	public:
	typedef _tagCallParameter _MyObjectType;
 
	Serialize_BaseObject<tstring> szPassword; 
	Serialize_BaseObject<BOOL> bCallSuccess; 
	Serialize_BaseObject<tstring> ObjectPath; 
	Serialize_BaseObject<SER_TO_X<tstring ,Base64ZipString>> Object; 
	Serialize__tagObjectState tagObjectState; 
	Serialize_BaseObject<unsigned int> nError; 
	Serialize_BaseObject<tstring> szFinder; 
	Serialize__tagDirectoryInfo DirectoryInfo; 
	Serialize_map<Serialize_BaseObject<tstring> ,Serialize__tagstrParameter ,less<tstring>> strPar;

	Serialize__tagCallParameter(){};
	~Serialize__tagCallParameter(){};
	_Myt& operator=(_tagCallParameter & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagCallParameter & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
