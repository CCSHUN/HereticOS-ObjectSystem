 #pragma once
#include "Serialize.h"

class Serialize__tagMachineCheckStandardSpecify : public Serialize_StructBase<_tagMachineCheckStandardSpecify,Serialize__tagMachineCheckStandardSpecify>
{
	public:
	typedef _tagMachineCheckStandardSpecify _MyObjectType;
 
	Serialize_BaseObject<tstring> szMachineCheckStandardSpecify;
	Serialize__tagMachineCheckStandardSpecify(){};
	~Serialize__tagMachineCheckStandardSpecify(){};
	_Myt& operator=(_tagMachineCheckStandardSpecify & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagMachineCheckStandardSpecify & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
