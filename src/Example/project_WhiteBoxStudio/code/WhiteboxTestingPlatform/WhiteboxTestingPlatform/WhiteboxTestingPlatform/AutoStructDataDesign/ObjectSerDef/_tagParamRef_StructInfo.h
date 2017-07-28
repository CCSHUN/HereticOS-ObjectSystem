 #pragma once

class Serialize__tagParamRef : public Serialize_StructBase<_tagParamRef,Serialize__tagParamRef>
{
	public:
	typedef _tagParamRef _MyObjectType;
 
	Serialize_BaseObject<IDType> nMacroID; 
	Serialize_BaseObject<IDType> nParamID;

	Serialize__tagParamRef(){};
	~Serialize__tagParamRef(){};
	_Myt& operator=(_tagParamRef & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagParamRef & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
