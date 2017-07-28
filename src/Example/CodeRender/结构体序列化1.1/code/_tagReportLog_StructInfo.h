 #pragma once
#include "Serialize.h"

class Serialize__tagReportLog : public Serialize_StructBase<_tagReportLog,Serialize__tagReportLog>
{
	public:
	typedef _tagReportLog _MyObjectType;
 
	Serialize_BaseObject<tstring> szUserName; 
	Serialize_BaseObject<__int64> tmDate; 
	Serialize_BaseObject<SER_TO_X<tstring ,HexString>> szReport_log;

	Serialize__tagReportLog(){};
	~Serialize__tagReportLog(){};
	_Myt& operator=(_tagReportLog & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagReportLog & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
