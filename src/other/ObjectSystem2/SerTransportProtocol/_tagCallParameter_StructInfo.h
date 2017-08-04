 #pragma once

class Serialize__tagCallParameter : public Serialize_StructBase<_tagCallParameter,Serialize__tagCallParameter>
{
	public:
	typedef _tagCallParameter _MyObjectType;
 
	Serialize_BaseObject<tstring> su; 
	Serialize_BaseObject<tstring> ss; 
	Serialize_BaseObject<unsigned int> oc; 
	Serialize_BaseObject<BOOL> bcs; 
	Serialize_BaseObject<tstring> op; 
	Serialize_BaseObject<unsigned int> np; 
	Serialize_BaseObject<SER_TO_X<tstring ,Base64ZipString>> ob; 
	Serialize__tagObjectState Os; 
	Serialize_BaseObject<unsigned int> Err; 
	Serialize_BaseObject<tstring> sf; 
	Serialize__tagDirectoryInfo di; 
	Serialize_vector< Serialize__tagObjectSystemEvent> el; 
	Serialize_map<Serialize_BaseObject<tstring_tmp> ,Serialize__tagstrParameter ,less<tstring_tmp>> sp;

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
