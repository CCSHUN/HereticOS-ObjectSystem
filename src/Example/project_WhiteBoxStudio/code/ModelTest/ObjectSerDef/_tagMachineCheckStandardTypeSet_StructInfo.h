 #pragma once
#include "Serialize.h"

class Serialize__tagMachineCheckStandardTypeSet : public Serialize_StructBase<_tagMachineCheckStandardTypeSet,Serialize__tagMachineCheckStandardTypeSet>
{
	public:
	typedef _tagMachineCheckStandardTypeSet _MyObjectType;
 
	Serialize_BaseObject<tstring> id; 
	Serialize_BaseObject<tstring> name; 
	Serialize_BaseObject<unsigned long> min_range; 
	Serialize_BaseObject<unsigned long> max_range; 
	Serialize_BaseObject<tstring> parent_id;

	Serialize__tagMachineCheckStandardTypeSet(){};
	~Serialize__tagMachineCheckStandardTypeSet(){};
	_Myt& operator=(_tagMachineCheckStandardTypeSet & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagMachineCheckStandardTypeSet & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
