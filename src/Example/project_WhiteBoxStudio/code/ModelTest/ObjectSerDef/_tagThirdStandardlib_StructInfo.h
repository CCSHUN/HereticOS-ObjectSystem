 #pragma once
#include "Serialize.h"

class Serialize__tagThirdStandardlib : public Serialize_StructBase<_tagThirdStandardlib,Serialize__tagThirdStandardlib>
{
	public:
	typedef _tagThirdStandardlib _MyObjectType;
 
	Serialize_map<Serialize_BaseObject<tstring> ,Serialize__tagThirdStandardSet ,less<tstring>> libmap;
	Serialize__tagThirdStandardlib(){};
	~Serialize__tagThirdStandardlib(){};
	_Myt& operator=(_tagThirdStandardlib & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagThirdStandardlib & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
