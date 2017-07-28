 #pragma once
#include "Serialize.h"

class Serialize__tagMachineCheckStandardTypeLib : public Serialize_StructBase<_tagMachineCheckStandardTypeLib,Serialize__tagMachineCheckStandardTypeLib>
{
	public:
	typedef _tagMachineCheckStandardTypeLib _MyObjectType;
 
	Serialize_map<Serialize_BaseObject<tstring> ,Serialize__tagMachineCheckStandardTypeSet ,less<tstring>> libmap;
	Serialize__tagMachineCheckStandardTypeLib(){};
	~Serialize__tagMachineCheckStandardTypeLib(){};
	_Myt& operator=(_tagMachineCheckStandardTypeLib & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagMachineCheckStandardTypeLib & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
