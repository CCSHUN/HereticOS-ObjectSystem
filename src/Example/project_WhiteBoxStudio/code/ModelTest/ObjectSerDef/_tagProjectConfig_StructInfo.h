 #pragma once
#include "Serialize.h"

class Serialize__tagProjectConfig : public Serialize_StructBase<_tagProjectConfig,Serialize__tagProjectConfig>
{
	public:
	typedef _tagProjectConfig _MyObjectType;
 
	Serialize_BaseObject<tstring> WorksheetStandard; 
	Serialize_BaseObject<SER_TO_X<tstring ,HexString>> CheckCfgStandard; 
	Serialize_BaseObject<tstring> TestReportStandard;

	Serialize__tagProjectConfig(){};
	~Serialize__tagProjectConfig(){};
	_Myt& operator=(_tagProjectConfig & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagProjectConfig & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
