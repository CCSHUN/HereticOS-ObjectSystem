 #pragma once

class Serialize__tagExpLib : public Serialize_StructBase<_tagExpLib,Serialize__tagExpLib>
{
	public:
	typedef _tagExpLib _MyObjectType;
 
	Serialize_BaseObject<tstring> szLibName; 
	Serialize__tagIDRecover tidRecover; 
	Serialize_map<Serialize_BaseObject<tstring> ,Serialize__tagExp ,less<tstring>> m_ExpLib;

	Serialize__tagExpLib(){};
	~Serialize__tagExpLib(){};
	_Myt& operator=(_tagExpLib & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagExpLib & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
