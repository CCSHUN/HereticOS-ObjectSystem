 #pragma once
#include "Serialize.h"

class Serialize__tagThirdStandardSet : public Serialize_StructBase<_tagThirdStandardSet,Serialize__tagThirdStandardSet>
{
	public:
	typedef _tagThirdStandardSet _MyObjectType;
 
	Serialize_BaseObject<tstring> szUniteStandardErrorNum; 
	Serialize_BaseObject<tstring> szThirdStandardErrorNum; 
	Serialize_BaseObject<SER_TO_X<tstring ,HexString>> szThirdStandardErrorDesc; 
	Serialize_BaseObject<SER_TO_X<tstring ,HexString>> szErrorSuggest; 
	Serialize_BaseObject<BOOL> is_manual_check; 
	Serialize_BaseObject<SER_TO_X<tstring ,HexString>> szManual_check_MethodSpecify; 
	Serialize_BaseObject<BOOL> is_dealwith; 
	Serialize_BaseObject<tstring> ToolType;

	Serialize__tagThirdStandardSet(){};
	~Serialize__tagThirdStandardSet(){};
	_Myt& operator=(_tagThirdStandardSet & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagThirdStandardSet & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
