 #pragma once

class Serialize__tagTestObject : public Serialize_StructBase<_tagTestObject,Serialize__tagTestObject>
{
	public:
	typedef _tagTestObject _MyObjectType;
 
	Serialize_BaseObject<tstring> szObjectName; 
	Serialize_BaseObject<unsigned int> nObjectType; 
	Serialize_BaseObjectBinaryArray<char,256> tCharArray; 
	Serialize_BaseObjectBinaryArray<UINT,256> tUintArray; 
	Serialize_BaseObject<unsigned int> nVal; 
	Serialize_BaseObject<int> iVal; 
	Serialize_BaseObject<float> fVal; 
	Serialize_BaseObject<double> lfVal; 
	Serialize_BaseObject<BOOL> bVal; 
	Serialize_BaseObject<SER_TO_X<tstring ,Base64ZipString>> szVal; 
	Serialize__tagTestSubObject SubObject; 
	Serialize_vector< Serialize__tagTestSubObject> SubObjectArray; 
	Serialize_map<Serialize_BaseObject<tstring> ,Serialize__tagTestSubObject ,less<tstring>> SubObjectMap;

	Serialize__tagTestObject(){};
	~Serialize__tagTestObject(){};
	_Myt& operator=(_tagTestObject & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagTestObject & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
