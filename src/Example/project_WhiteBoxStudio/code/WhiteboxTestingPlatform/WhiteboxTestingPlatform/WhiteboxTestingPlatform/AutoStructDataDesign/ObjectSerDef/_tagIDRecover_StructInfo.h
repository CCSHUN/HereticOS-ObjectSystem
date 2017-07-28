 #pragma once

class Serialize__tagIDRecover : public Serialize_StructBase<_tagIDRecover,Serialize__tagIDRecover>
{
	public:
	typedef _tagIDRecover _MyObjectType;
 
	Serialize_BaseObject<IDType> nID; 
	Serialize_list< Serialize_BaseObject<IDType>> tIDRecover;

	Serialize__tagIDRecover(){};
	~Serialize__tagIDRecover(){};
	_Myt& operator=(_tagIDRecover & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagIDRecover & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
