 #pragma once
#include "Serialize.h"

class Serialize__S_PROJECT_CONFIG : public Serialize_StructBase<_S_PROJECT_CONFIG,Serialize__S_PROJECT_CONFIG>
{
	public:
	typedef _S_PROJECT_CONFIG _MyObjectType;
 
	Serialize_BaseObject<tstring> config_content;
	Serialize__S_PROJECT_CONFIG(){};
	~Serialize__S_PROJECT_CONFIG(){};
	_Myt& operator=(_S_PROJECT_CONFIG & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_S_PROJECT_CONFIG & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
