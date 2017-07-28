 #pragma once
#include "Serialize.h"

class Serialize__tagUserOwnProjectTab : public Serialize_StructBase<_tagUserOwnProjectTab,Serialize__tagUserOwnProjectTab>
{
	public:
	typedef _tagUserOwnProjectTab _MyObjectType;
 
	Serialize_map<Serialize_BaseObject<tstring> ,Serialize__tagUserProjectSet ,less<tstring>> OwnProjectArray;
	Serialize__tagUserOwnProjectTab(){};
	~Serialize__tagUserOwnProjectTab(){};
	_Myt& operator=(_tagUserOwnProjectTab & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagUserOwnProjectTab & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
