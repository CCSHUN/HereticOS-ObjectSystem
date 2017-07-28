 #pragma once

class Serialize__tagTestSubObject : public Serialize_StructBase<_tagTestSubObject,Serialize__tagTestSubObject>
{
	public:
	typedef _tagTestSubObject _MyObjectType;
 
	Serialize_BaseObject<tstring> szSubObjectName; 
	Serialize_BaseObject<unsigned int> nSubObjectType; 
	Serialize_BaseObject<float> fSubObject; 
	Serialize_BaseObject<double> lfSubObject; 
	Serialize_BaseObject<int> iSubObject; 
	Serialize_BaseObject<BOOL> bSubVal; 
	Serialize_BaseObject<SER_TO_X<tstring ,Base64ZipString>> szSubVal;

	Serialize__tagTestSubObject(){};
	~Serialize__tagTestSubObject(){};
	_Myt& operator=(_tagTestSubObject & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagTestSubObject & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
