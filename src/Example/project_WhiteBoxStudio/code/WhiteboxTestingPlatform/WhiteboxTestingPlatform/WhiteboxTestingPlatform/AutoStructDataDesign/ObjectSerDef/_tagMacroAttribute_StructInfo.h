 #pragma once

class Serialize__tagMacroAttribute : public Serialize_StructBase<_tagMacroAttribute,Serialize__tagMacroAttribute>
{
	public:
	typedef _tagMacroAttribute _MyObjectType;
 
	Serialize_BaseObject<BOOL> bRootMacro;
	Serialize__tagMacroAttribute(){};
	~Serialize__tagMacroAttribute(){};
	_Myt& operator=(_tagMacroAttribute & _X);
	void GetData();
	BOOL Construct(StorageObjectInterface * pOutObject);
	void SetData(_tagMacroAttribute & _X);
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj);
	BOOL Save(StorageObjectInterface * pStorageObject);
	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap);


};
