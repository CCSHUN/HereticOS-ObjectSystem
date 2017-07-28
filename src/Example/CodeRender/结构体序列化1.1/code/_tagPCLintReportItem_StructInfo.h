 #pragma once
#include "Serialize.h"

class Serialize__tagPCLintReportItem : public Serialize_StructBase<_tagPCLintReportItem,Serialize__tagPCLintReportItem>
{
	public:
	typedef _tagPCLintReportItem _MyObjectType;
 
	Serialize_BaseObject<tstring> filename; 
	Serialize_BaseObject<tstring> errorno; 
	Serialize_BaseObject<int> rowno; 
	Serialize_BaseObject<tstring> msgtxt;

	Serialize__tagPCLintReportItem(){};
	~Serialize__tagPCLintReportItem(){};
	_Myt& operator=(_tagPCLintReportItem & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagPCLintReportItem & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
