 #pragma once

class Serialize__tagMacroDef : public Serialize_StructBase<_tagMacroDef,Serialize__tagMacroDef>
{
	public:
	typedef _tagMacroDef _MyObjectType;
 
	Serialize_BaseObject<IDType> nMacroID; 
	Serialize_BaseObject<tstring> szMacroName; 
	Serialize_BaseObject<tstring> szMacroDesc; 
	Serialize_BaseObject<tstring> szMacroType; 
	Serialize__tagMacroAttribute MacroAttr; 
	Serialize_vector< Serialize_BaseObject<IDType>> ChildMacroIDArray; 
	Serialize__tagIDRecover tParamidRecover; 
	Serialize_vector< Serialize__tagMacroParamDef> ChildParArray;

	Serialize__tagMacroDef(){};
	~Serialize__tagMacroDef(){};
	_Myt& operator=(_tagMacroDef & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagMacroDef & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
