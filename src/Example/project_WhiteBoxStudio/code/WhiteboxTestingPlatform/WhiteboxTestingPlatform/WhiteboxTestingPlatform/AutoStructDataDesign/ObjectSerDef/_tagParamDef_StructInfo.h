 #pragma once

class Serialize__tagParamDef : public Serialize_StructBase<_tagParamDef,Serialize__tagParamDef>
{
	public:
	typedef _tagParamDef _MyObjectType;
 
	Serialize_BaseObject<IDType> nParamID; 
	Serialize_BaseObject<tstring> szParamName; 
	Serialize_BaseObject<tstring> szParamDesc; 
	Serialize_BaseObject<tstring> szParamAttribute; 
	Serialize_BaseObject<tstring> szDefaultParam; 
	Serialize_BaseObject<tstring> szLastEditParamVal;

	Serialize__tagParamDef(){};
	~Serialize__tagParamDef(){};
	_Myt& operator=(_tagParamDef & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagParamDef & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
