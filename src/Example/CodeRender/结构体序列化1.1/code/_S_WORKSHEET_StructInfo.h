 #pragma once
#include "Serialize.h"

class Serialize__S_WORKSHEET : public Serialize_StructBase<_S_WORKSHEET,Serialize__S_WORKSHEET>
{
	public:
	typedef _S_WORKSHEET _MyObjectType;
 
	Serialize_BaseObject<tstring> szProjectNo; 
	Serialize_BaseObject<tstring> szModuleNo; 
	Serialize_BaseObject<tstring> szWorksheetNo; 
	Serialize_BaseObject<tstring> szApplyDate; 
	Serialize_BaseObject<tstring> szApplyMan; 
	Serialize_BaseObject<tstring> szResponsiblePerson; 
	Serialize_BaseObject<tstring> szDefaultDispatchUser; 
	Serialize_BaseObject<tstring> szCheckRange; 
	Serialize_BaseObject<int> nCheckType; 
	Serialize_BaseObject<tstring> szPreWorksheetNo; 
	Serialize_BaseObject<tstring> szSVNCodePath; 
	Serialize_BaseObject<tstring> szSourceList; 
	Serialize_BaseObject<tstring> szSuggest; 
	Serialize_BaseObject<int> nCheckResult; 
	Serialize_BaseObject<tstring> szFailReason; 
	Serialize_BaseObject<tstring> szSignatureMan; 
	Serialize_BaseObject<tstring> szSignatureDate;

	Serialize__S_WORKSHEET(){};
	~Serialize__S_WORKSHEET(){};
	_Myt& operator=(_S_WORKSHEET & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_S_WORKSHEET & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
