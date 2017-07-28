 #pragma once

class Serialize__tagRealParam : public Serialize_StructBase<_tagRealParam,Serialize__tagRealParam>
{
	public:
	typedef _tagRealParam _MyObjectType;
 
	Serialize_BaseObject<IDType> nParamID; 
	Serialize_BaseObject<tstring> szParamName; 
	Serialize_BaseObject<tstring> szParamDesc; 
	Serialize_BaseObject<tstring> szParamAttribute; 
	Serialize_BaseObject<tstring> szDefaultParam;

	Serialize__tagRealParam(){};
	~Serialize__tagRealParam(){};
	_Myt& operator=(_tagRealParam & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagRealParam & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
