 #pragma once
#include "Serialize.h"

class Serialize__tagReportOutput : public Serialize_StructBase<_tagReportOutput,Serialize__tagReportOutput>
{
	public:
	typedef _tagReportOutput _MyObjectType;
 
	Serialize__tagReportOutput_Overall Overall; 
	Serialize_vector< Serialize__tagReportOutput_Summary> Summary; 
	Serialize_vector< Serialize__tagReportOutput_Detailed> Detailed;

	Serialize__tagReportOutput(){};
	~Serialize__tagReportOutput(){};
	_Myt& operator=(_tagReportOutput & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagReportOutput & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
