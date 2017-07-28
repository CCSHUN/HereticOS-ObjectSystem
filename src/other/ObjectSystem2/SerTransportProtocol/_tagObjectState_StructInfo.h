 #pragma once

class Serialize__tagObjectState : public Serialize_StructBase<_tagObjectState,Serialize__tagObjectState>
{
	public:
	typedef _tagObjectState _MyObjectType;
 
	Serialize_BaseObject<BOOL> bLock; 
	Serialize_BaseObject<unsigned int> nType; 
	Serialize_BaseObject<tstring> szLockUser; 
	Serialize_BaseObject<unsigned int> nLockTime;

	Serialize__tagObjectState(){};
	~Serialize__tagObjectState(){};
	_Myt& operator=(_tagObjectState & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagObjectState & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
