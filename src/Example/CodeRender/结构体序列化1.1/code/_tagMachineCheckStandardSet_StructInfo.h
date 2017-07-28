 #pragma once
#include "Serialize.h"

class Serialize__tagMachineCheckStandardSet : public Serialize_StructBase<_tagMachineCheckStandardSet,Serialize__tagMachineCheckStandardSet>
{
	public:
	typedef _tagMachineCheckStandardSet _MyObjectType;
 
	Serialize_BaseObject<tstring> szErrorNum; 
	Serialize_BaseObject<tstring> szErrorType; 
	Serialize_BaseObject<SER_TO_X<tstring ,HexString>> szDesc; 
	Serialize_BaseObject<tstring> szErrorWarning; 
	Serialize_BaseObject<tstring> szErrorTypeId; 
	Serialize_BaseObject<SER_TO_X<tstring ,HexString>> szErrorSuggest;

	Serialize__tagMachineCheckStandardSet(){};
	~Serialize__tagMachineCheckStandardSet(){};
	_Myt& operator=(_tagMachineCheckStandardSet & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagMachineCheckStandardSet & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
