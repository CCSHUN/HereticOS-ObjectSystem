 #pragma once

class Serialize__tagFlowerSlot : public Serialize_StructBase<_tagFlowerSlot,Serialize__tagFlowerSlot>
{
	public:
	typedef _tagFlowerSlot _MyObjectType;
 
	Serialize_BaseObject<BOOL> bOwn; 
	Serialize_BaseObject<unsigned int> nFlowerTransportCount; 
	Serialize_BaseObject<tstring> szLastLog;

	Serialize__tagFlowerSlot(){};
	~Serialize__tagFlowerSlot(){};
	_Myt& operator=(_tagFlowerSlot & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagFlowerSlot & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
