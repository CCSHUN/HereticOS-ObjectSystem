 #pragma once
#include "Serialize.h"

class Serialize__tagProjectState : public Serialize_StructBase<_tagProjectState,Serialize__tagProjectState>
{
	public:
	typedef _tagProjectState _MyObjectType;
 
	Serialize_BaseObject<tstring> szProjectState;
	Serialize__tagProjectState(){};
	~Serialize__tagProjectState(){};
	_Myt& operator=(_tagProjectState & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagProjectState & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
