 #pragma once

class Serialize__tagExp : public Serialize_StructBase<_tagExp,Serialize__tagExp>
{
	public:
	typedef _tagExp _MyObjectType;
 
	Serialize_BaseObject<tstring> szExpName; 
	Serialize_BaseObject<IDType> nExpID; 
	Serialize_BaseObject<tstring> szExpDesc; 
	Serialize_vector< Serialize_BaseObject<IDType>> FuncIDArray; 
	Serialize_map<Serialize_BaseObject<IDType> ,Serialize_vector< Serialize__tagParamDef> ,less<IDType>> m_ExpValMap;

	Serialize__tagExp(){};
	~Serialize__tagExp(){};
	_Myt& operator=(_tagExp & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagExp & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
