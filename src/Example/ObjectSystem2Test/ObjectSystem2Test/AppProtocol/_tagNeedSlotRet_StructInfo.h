 #pragma once

class Serialize__tagNeedSlotRet : public Serialize_StructBase<_tagNeedSlotRet,Serialize__tagNeedSlotRet>
{
	public:
	typedef _tagNeedSlotRet _MyObjectType;
 
	Serialize_BaseObject<int> nNewSlot;
	Serialize__tagNeedSlotRet(){};
	~Serialize__tagNeedSlotRet(){};
	_Myt& operator=(_tagNeedSlotRet & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagNeedSlotRet & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
