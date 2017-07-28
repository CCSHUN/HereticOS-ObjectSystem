 #pragma once

class Serialize__tagMangerBroadcast : public Serialize_StructBase<_tagMangerBroadcast,Serialize__tagMangerBroadcast>
{
	public:
	typedef _tagMangerBroadcast _MyObjectType;
 
	Serialize_BaseObject<unsigned int> nMsgType; 
	Serialize_BaseObject<tstring> szMsg;

	Serialize__tagMangerBroadcast(){};
	~Serialize__tagMangerBroadcast(){};
	_Myt& operator=(_tagMangerBroadcast & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagMangerBroadcast & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
