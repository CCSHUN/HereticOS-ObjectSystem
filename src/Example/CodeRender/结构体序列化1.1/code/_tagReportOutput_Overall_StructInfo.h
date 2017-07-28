 #pragma once
#include "Serialize.h"

class Serialize__tagReportOutput_Overall : public Serialize_StructBase<_tagReportOutput_Overall,Serialize__tagReportOutput_Overall>
{
	public:
	typedef _tagReportOutput_Overall _MyObjectType;
 
	Serialize_BaseObject<unsigned int> nDescTotal; 
	Serialize_BaseObject<unsigned int> nErrorTotal; 
	Serialize_BaseObject<unsigned int> nComplateTotal; 
	Serialize_BaseObject<unsigned int> nManaualTotal; 
	Serialize_BaseObject<unsigned int> nIgnoreTotal;

	Serialize__tagReportOutput_Overall(){};
	~Serialize__tagReportOutput_Overall(){};
	_Myt& operator=(_tagReportOutput_Overall & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagReportOutput_Overall & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
