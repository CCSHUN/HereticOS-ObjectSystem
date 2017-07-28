 #pragma once
#include "Serialize.h"

class Serialize__tagMachineCheckStandardLib : public Serialize_StructBase<_tagMachineCheckStandardLib,Serialize__tagMachineCheckStandardLib>
{
	public:
	typedef _tagMachineCheckStandardLib _MyObjectType;
 
	Serialize_map<Serialize_BaseObject<tstring> ,Serialize__tagMachineCheckStandardSet ,less<tstring>> libmap;
	Serialize__tagMachineCheckStandardLib(){};
	~Serialize__tagMachineCheckStandardLib(){};
	_Myt& operator=(_tagMachineCheckStandardLib & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagMachineCheckStandardLib & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
