 #pragma once
#include "Serialize.h"

class Serialize__tagReportOutput_Summary : public Serialize_StructBase<_tagReportOutput_Summary,Serialize__tagReportOutput_Summary>
{
	public:
	typedef _tagReportOutput_Summary _MyObjectType;
 
	Serialize_BaseObject<unsigned int> nCurPos; 
	Serialize_BaseObject<SER_TO_X<tstring ,XmlString>> szDesc; 
	Serialize_BaseObject<unsigned int> nErrorTotal; 
	Serialize_BaseObject<unsigned int> nComplateTotal; 
	Serialize_BaseObject<unsigned int> nManaualTotal; 
	Serialize_BaseObject<unsigned int> nIgnoreTotal; 
	Serialize_BaseObject<tstring> szErrorType; 
	Serialize_BaseObject<tstring> szWaringType; 
	Serialize_BaseObject<tstring> szUniteNum;

	Serialize__tagReportOutput_Summary(){};
	~Serialize__tagReportOutput_Summary(){};
	_Myt& operator=(_tagReportOutput_Summary & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagReportOutput_Summary & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
