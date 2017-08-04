 #pragma once

class Serialize__tagCallParameterV2 : public Serialize_StructBase<_tagCallParameterV2,Serialize__tagCallParameterV2>
{
	public:
	typedef _tagCallParameterV2 _MyObjectType;
 
	Serialize_BaseObject<tstring_tmp> szUser; 
	Serialize_BaseObject<tstring_tmp> szSession; 
	Serialize_BaseObject<unsigned int> nOpCode; 
	Serialize_BaseObject<tstring_tmp> szPassword; 
	Serialize_BaseObject<BOOL> bCallSuccess; 
	Serialize_BaseObject<tstring_tmp> ObjectPath; 
	Serialize_BaseObject<unsigned int> nPar; 
	Serialize_BaseObject<tstring_tmp> Object; 
	Serialize__tagObjectState tagObjectState; 
	Serialize_BaseObject<unsigned int> nError; 
	Serialize_BaseObject<tstring_tmp> szFinder; 
	Serialize__tagDirectoryInfo DirectoryInfo; 
	Serialize_vector< Serialize__tagObjectSystemEvent> EventList; 
	Serialize_map<Serialize_BaseObject<tstring_tmp> ,Serialize__tagstrParameter ,less<tstring_tmp>> strPar;

	Serialize__tagCallParameterV2(){};
	~Serialize__tagCallParameterV2(){};
	_Myt& operator=(_tagCallParameterV2 & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagCallParameterV2 & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
