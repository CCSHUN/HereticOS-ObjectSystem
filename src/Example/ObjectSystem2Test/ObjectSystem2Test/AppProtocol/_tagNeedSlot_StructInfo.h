 #pragma once

class Serialize__tagNeedSlot : public Serialize_StructBase<_tagNeedSlot,Serialize__tagNeedSlot>
{
	public:
	typedef _tagNeedSlot _MyObjectType;
 
	Serialize_BaseObject<tstring> szUserSession;
	Serialize__tagNeedSlot(){};
	~Serialize__tagNeedSlot(){};
	_Myt& operator=(_tagNeedSlot & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagNeedSlot & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
