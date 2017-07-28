 #pragma once

class Serialize__tagBulletinBoard : public Serialize_StructBase<_tagBulletinBoard,Serialize__tagBulletinBoard>
{
	public:
	typedef _tagBulletinBoard _MyObjectType;
 
	Serialize_BaseObject<unsigned int> nMaxFlowerSlotCount; 
	Serialize_BaseObject<unsigned int> nGameMode; 
	Serialize_BaseObject<unsigned int> nTransportWaitTime;

	Serialize__tagBulletinBoard(){};
	~Serialize__tagBulletinBoard(){};
	_Myt& operator=(_tagBulletinBoard & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagBulletinBoard & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
