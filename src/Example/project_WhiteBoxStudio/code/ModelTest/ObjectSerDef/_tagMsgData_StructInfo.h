 #pragma once
#include "Serialize.h"

class Serialize__tagMsgData : public Serialize_StructBase<_tagMsgData,Serialize__tagMsgData>
{
	public:
	typedef _tagMsgData _MyObjectType;
 
	Serialize_BaseObject<tstring> szType; 
	Serialize_BaseObject<tstring> szData;

	Serialize__tagMsgData(){};
	~Serialize__tagMsgData(){};
	_Myt& operator=(_tagMsgData & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagMsgData & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
