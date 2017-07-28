 #pragma once

class Serialize__tagObjectSystemEvent : public Serialize_StructBase<_tagObjectSystemEvent,Serialize__tagObjectSystemEvent>
{
	public:
	typedef _tagObjectSystemEvent _MyObjectType;
 
	Serialize_BaseObject<tstring> szObjectAddress; 
	Serialize_BaseObject<unsigned int> nEventType;

	Serialize__tagObjectSystemEvent(){};
	~Serialize__tagObjectSystemEvent(){};
	_Myt& operator=(_tagObjectSystemEvent & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagObjectSystemEvent & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
