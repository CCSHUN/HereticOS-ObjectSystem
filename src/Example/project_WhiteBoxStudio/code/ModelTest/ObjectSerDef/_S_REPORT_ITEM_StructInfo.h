 #pragma once
#include "Serialize.h"

class Serialize__S_REPORT_ITEM : public Serialize_StructBase<_S_REPORT_ITEM,Serialize__S_REPORT_ITEM>
{
	public:
	typedef _S_REPORT_ITEM _MyObjectType;
 
	Serialize_BaseObject<tstring> szTestState; 
	Serialize_BaseObject<tstring> szTestItemSource; 
	Serialize_BaseObject<tstring> szTestToolType; 
	Serialize_BaseObject<tstring> szUniteStandardErrorNum; 
	Serialize_BaseObject<tstring> szThirdStandardErrorNum; 
	Serialize_BaseObject<SER_TO_X<tstring ,Base64ZipString>> szErrorCodeContent; 
	Serialize_BaseObject<SER_TO_X<tstring ,Base64ZipString>> szErrorCodePosition; 
	Serialize_BaseObject<SER_TO_X<tstring ,Base64ZipString>> szModule; 
	Serialize_BaseObject<SER_TO_X<tstring ,Base64ZipString>> szSuggest; 
	Serialize_BaseObject<SER_TO_X<tstring ,Base64ZipString>> szDesc; 
	Serialize_BaseObject<SER_TO_X<tstring ,Base64ZipString>> szUniteSuggest; 
	Serialize_BaseObject<SER_TO_X<tstring ,Base64ZipString>> szUniteDesc; 
	Serialize_BaseObject<SER_TO_X<tstring ,Base64ZipString>> szThirdSuggest; 
	Serialize_BaseObject<SER_TO_X<tstring ,Base64ZipString>> szThirdDesc; 
	Serialize_BaseObject<tstring> szErrorType; 
	Serialize_BaseObject<tstring> szErrorWarning; 
	Serialize_BaseObject<tstring> szCreateTime; 
	Serialize_BaseObject<tstring> szLastEditTime; 
	Serialize_BaseObject<tstring> szDevelopState; 
	Serialize_vector< Serialize__tagReportLog> szReport_log; 
	Serialize_BaseObject<tstring> szProcessUser;

	Serialize__S_REPORT_ITEM(){};
	~Serialize__S_REPORT_ITEM(){};
	_Myt& operator=(_S_REPORT_ITEM & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_S_REPORT_ITEM & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
