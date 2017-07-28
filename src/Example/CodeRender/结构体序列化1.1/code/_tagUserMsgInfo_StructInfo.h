 #pragma once
#include "Serialize.h"

class Serialize__tagUserMsgInfo : public Serialize_StructBase<_tagUserMsgInfo,Serialize__tagUserMsgInfo>
{
	public:
	typedef _tagUserMsgInfo _MyObjectType;
 
	Serialize_BaseObject<tstring> szBeginMsgTime; 
	Serialize_BaseObject<tstring> szEndMsgTime; 
	Serialize_BaseObject<unsigned int> nMsgNum; 
	Serialize_vector< Serialize_BaseObject<tstring>> szNewMsgIndex;

	Serialize__tagUserMsgInfo(){};
	~Serialize__tagUserMsgInfo(){};
	_Myt& operator=(_tagUserMsgInfo & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagUserMsgInfo & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
