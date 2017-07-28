 #pragma once

class Serialize__tagMacroParamDef : public Serialize_StructBase<_tagMacroParamDef,Serialize__tagMacroParamDef>
{
	public:
	typedef _tagMacroParamDef _MyObjectType;
 
	Serialize_BaseObject<IDType> nParamID; 
	Serialize_BaseObject<tstring> szParamType; 
	Serialize__tagParamRef RefPar; 
	Serialize__tagRealParam realPar; 
	Serialize_BaseObject<tstring> szLastEditParamVal;

	Serialize__tagMacroParamDef(){};
	~Serialize__tagMacroParamDef(){};
	_Myt& operator=(_tagMacroParamDef & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagMacroParamDef & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
