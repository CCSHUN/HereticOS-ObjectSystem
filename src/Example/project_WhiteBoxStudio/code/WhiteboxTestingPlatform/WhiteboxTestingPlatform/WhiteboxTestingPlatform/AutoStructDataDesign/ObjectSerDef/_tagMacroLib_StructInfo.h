 #pragma once

class Serialize__tagMacroLib : public Serialize_StructBase<_tagMacroLib,Serialize__tagMacroLib>
{
	public:
	typedef _tagMacroLib _MyObjectType;
 
	Serialize_BaseObject<tstring> szLibName; 
	Serialize__tagIDRecover tidRecover; 
	Serialize_map<Serialize_BaseObject<IDType> ,Serialize__tagMacroDef ,less<IDType>> libmap;

	Serialize__tagMacroLib(){};
	~Serialize__tagMacroLib(){};
	_Myt& operator=(_tagMacroLib & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagMacroLib & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
