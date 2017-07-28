 #pragma once

class Serialize__tagKeepAlivedPar : public Serialize_StructBase<_tagKeepAlivedPar,Serialize__tagKeepAlivedPar>
{
	public:
	typedef _tagKeepAlivedPar _MyObjectType;
 
	Serialize_BaseObject<unsigned int> nCyc; 
	Serialize_BaseObject<unsigned int> nWndPos; 
	Serialize_BaseObject<unsigned int> nWndLen;

	Serialize__tagKeepAlivedPar(){};
	~Serialize__tagKeepAlivedPar(){};
	_Myt& operator=(_tagKeepAlivedPar & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagKeepAlivedPar & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
