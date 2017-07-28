 #pragma once

class Serialize__tagstrParameter : public Serialize_StructBase<_tagstrParameter,Serialize__tagstrParameter>
{
	public:
	typedef _tagstrParameter _MyObjectType;
 
	Serialize_BaseObject<SER_TO_X<tstring ,Base64ZipString>> szVar;
	Serialize__tagstrParameter(){};
	~Serialize__tagstrParameter(){};
	_Myt& operator=(_tagstrParameter & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagstrParameter & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
