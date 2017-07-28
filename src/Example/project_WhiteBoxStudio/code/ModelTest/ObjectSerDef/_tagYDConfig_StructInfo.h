 #pragma once
#include "Serialize.h"

class Serialize__tagYDConfig : public Serialize_StructBase<_tagYDConfig,Serialize__tagYDConfig>
{
	public:
	typedef _tagYDConfig _MyObjectType;
 
	Serialize_BaseObject<tstring> strRuleVer; 
	Serialize_BaseObject<tstring> strNetDomainName; 
	Serialize_BaseObject<int> nNetDomainPort; 
	Serialize_BaseObject<tstring> strWSDLUrl; 
	Serialize_BaseObject<tstring> strRunDirectory; 
	Serialize_BaseObject<tstring> strLocalSystemDirectory; 
	Serialize_BaseObject<int> nSoapTimeout; 
	Serialize_BaseObject<int> nCheckCycle; 
	Serialize_BaseObject<tstring> szDebugLevel;

	Serialize__tagYDConfig(){};
	~Serialize__tagYDConfig(){};
	_Myt& operator=(_tagYDConfig & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagYDConfig & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
