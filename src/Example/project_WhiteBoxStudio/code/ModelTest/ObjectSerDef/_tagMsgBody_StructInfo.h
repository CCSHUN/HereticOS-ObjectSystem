 #pragma once
#include "Serialize.h"

class Serialize__tagMsgBody : public Serialize_StructBase<_tagMsgBody,Serialize__tagMsgBody>
{
	public:
	typedef _tagMsgBody _MyObjectType;
 
	Serialize_BaseObject<tstring> szSenderUser; 
	Serialize_BaseObject<tstring> szSendDate; 
	Serialize_BaseObject<tstring> szTitle; 
	Serialize_vector< Serialize_BaseObject<tstring>> szRecvUserList; 
	Serialize_vector< Serialize__tagMsgData> tagMsgAppend; 
	Serialize__tagMsgData szMsgData;

	Serialize__tagMsgBody(){};
	~Serialize__tagMsgBody(){};
	_Myt& operator=(_tagMsgBody & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagMsgBody & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
