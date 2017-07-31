 #pragma once

class Serialize__tagCallParameterV2 : public Serialize_StructBase<_tagCallParameterV2,Serialize__tagCallParameterV2>
{
	public:
	typedef _tagCallParameterV2 _MyObjectType;
 
	Serialize_BaseObject<tstring> szUser; 
	Serialize_BaseObject<tstring> szSession; 
	Serialize_BaseObject<unsigned int> nOpCode; 
	Serialize_BaseObject<tstring> szPassword; 
	Serialize_BaseObject<BOOL> bCallSuccess; 
	Serialize_BaseObject<tstring> ObjectPath; 
	Serialize_BaseObject<unsigned int> nRegEventType; 
	Serialize_BaseObject<tstring> Object; 
	Serialize__tagObjectState tagObjectState; 
	Serialize_BaseObject<unsigned int> nError; 
	Serialize_BaseObject<tstring> szFinder; 
	Serialize__tagDirectoryInfo DirectoryInfo; 
	Serialize_vector< Serialize__tagObjectSystemEvent> EventList; 
	Serialize_map<Serialize_BaseObject<tstring> ,Serialize__tagstrParameter ,less<tstring>> strPar;

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
