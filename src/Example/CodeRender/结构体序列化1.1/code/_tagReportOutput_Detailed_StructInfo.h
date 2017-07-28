 #pragma once
#include "Serialize.h"

class Serialize__tagReportOutput_Detailed : public Serialize_StructBase<_tagReportOutput_Detailed,Serialize__tagReportOutput_Detailed>
{
	public:
	typedef _tagReportOutput_Detailed _MyObjectType;
 
	Serialize_BaseObject<SER_TO_X<tstring ,XmlString>> szDetailed;
	Serialize__tagReportOutput_Detailed(){};
	~Serialize__tagReportOutput_Detailed(){};
	_Myt& operator=(_tagReportOutput_Detailed & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagReportOutput_Detailed & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
