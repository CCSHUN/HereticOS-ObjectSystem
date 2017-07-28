 #pragma once

class Serialize__tagFuncLib : public Serialize_StructBase<_tagFuncLib,Serialize__tagFuncLib>
{
	public:
	typedef _tagFuncLib _MyObjectType;
 
	Serialize_BaseObject<tstring> szLibName; 
	Serialize__tagIDRecover tidRecover; 
	Serialize_map<Serialize_BaseObject<tstring> ,Serialize__tagFuncDef ,less<tstring>> m_FuncLib;

	Serialize__tagFuncLib(){};
	~Serialize__tagFuncLib(){};
	_Myt& operator=(_tagFuncLib & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagFuncLib & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
