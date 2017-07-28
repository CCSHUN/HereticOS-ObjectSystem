 #pragma once

class Serialize__tagFuncDef : public Serialize_StructBase<_tagFuncDef,Serialize__tagFuncDef>
{
	public:
	typedef _tagFuncDef _MyObjectType;
 
	Serialize_BaseObject<IDType> nFuncID; 
	Serialize_BaseObject<tstring> szFuncName; 
	Serialize_BaseObject<tstring> szFuncDesc; 
	Serialize_BaseObject<tstring> szFuncType; 
	Serialize_BaseObject<tstring> FuncAttr; 
	Serialize__tagIDRecover tParamidRecover; 
	Serialize_vector< Serialize__tagParamDef> m_ParamDefArray;

	Serialize__tagFuncDef(){};
	~Serialize__tagFuncDef(){};
	_Myt& operator=(_tagFuncDef & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagFuncDef & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
