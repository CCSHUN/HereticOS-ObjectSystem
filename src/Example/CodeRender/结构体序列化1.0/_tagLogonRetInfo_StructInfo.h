 #pragma once
#include "Serialize.h"

class Serialize__tagLogonRetInfo : public Serialize_StructBase<_tagLogonRetInfo,Serialize__tagLogonRetInfo>
{
	public:
	typedef _tagLogonRetInfo _MyObjectType;
 
	Serialize_BaseObject<tstring> ftpPwd; 
	Serialize_BaseObject<DWORD> result; 
	Serialize_BaseObject<BOOL> isCheckCert; 
	Serialize_BaseObject<BOOL> isImportCert; 
	Serialize_BaseObject<__int64> fileUploadMaxSize; 
	Serialize_BaseObjectStringArray<TCHAR,64> ftpUser; 
	Serialize_vector< Serialize__tagSafeLevelInfo> safelevelList; 
	Serialize_BaseObject<tstring> userType; 
	Serialize_BaseObject<tstring> ftpServer; 
	Serialize_BaseObject<tstring> userId; 
	Serialize_BaseObject<tstring> md5Pwd; 
	Serialize_BaseObject<USHORT> ftpPort; 
	Serialize_BaseObject<tstring> userSafelevelId; 
	Serialize_BaseObject<tstring> priDeptId; 
	Serialize_BaseObject<BOOL> isForceLogin; 
	Serialize_BaseObject<tstring> loginName;

 	Serialize__tagLogonRetInfo(){};
	~Serialize__tagLogonRetInfo(){};
 	_Myt& operator=(_tagLogonRetInfo & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.ftpPwd=ftpPwd; 
		m_Val.result=result; 
		m_Val.isCheckCert=isCheckCert; 
		m_Val.isImportCert=isImportCert; 
		m_Val.fileUploadMaxSize=fileUploadMaxSize; 
		memcpy(m_Val.ftpUser,(TCHAR*)ftpUser,sizeof(m_Val.ftpUser)); 
		m_Val.safelevelList=safelevelList; 
		m_Val.userType=userType; 
		m_Val.ftpServer=ftpServer; 
		m_Val.userId=userId; 
		m_Val.md5Pwd=md5Pwd; 
		m_Val.ftpPort=ftpPort; 
		m_Val.userSafelevelId=userSafelevelId; 
		m_Val.priDeptId=priDeptId; 
		m_Val.isForceLogin=isForceLogin; 
		m_Val.loginName=loginName;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		ftpPwd.init(this,_T("ftpPwd"),0,pOutObject); 
		result.init(this,_T("result"),0,pOutObject); 
		isCheckCert.init(this,_T("isCheckCert"),0,pOutObject); 
		isImportCert.init(this,_T("isImportCert"),0,pOutObject); 
		fileUploadMaxSize.init(this,_T("fileUploadMaxSize"),0,pOutObject); 
		ftpUser.init(this,_T("ftpUser"),0,pOutObject); 
		safelevelList.init(this,_T("safelevelList"),0,pOutObject); 
		userType.init(this,_T("userType"),0,pOutObject); 
		ftpServer.init(this,_T("ftpServer"),0,pOutObject); 
		userId.init(this,_T("userId"),0,pOutObject); 
		md5Pwd.init(this,_T("md5Pwd"),0,pOutObject); 
		ftpPort.init(this,_T("ftpPort"),0,pOutObject); 
		userSafelevelId.init(this,_T("userSafelevelId"),0,pOutObject); 
		priDeptId.init(this,_T("priDeptId"),0,pOutObject); 
		isForceLogin.init(this,_T("isForceLogin"),0,pOutObject); 
		loginName.init(this,_T("loginName"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagLogonRetInfo & _X)
	{
		ftpPwd=_X.ftpPwd; 
		result=_X.result; 
		isCheckCert=_X.isCheckCert; 
		isImportCert=_X.isImportCert; 
		fileUploadMaxSize=_X.fileUploadMaxSize; 
		ftpUser=_X.ftpUser; 
		safelevelList=_X.safelevelList; 
		userType=_X.userType; 
		ftpServer=_X.ftpServer; 
		userId=_X.userId; 
		md5Pwd=_X.md5Pwd; 
		ftpPort=_X.ftpPort; 
		userSafelevelId=_X.userSafelevelId; 
		priDeptId=_X.priDeptId; 
		isForceLogin=_X.isForceLogin; 
		loginName=_X.loginName;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ftpPwd")))
		{
			*RetObj=&ftpPwd;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("result")))
		{
			*RetObj=&result;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("isCheckCert")))
		{
			*RetObj=&isCheckCert;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("isImportCert")))
		{
			*RetObj=&isImportCert;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("fileUploadMaxSize")))
		{
			*RetObj=&fileUploadMaxSize;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ftpUser")))
		{
			*RetObj=&ftpUser;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("safelevelList")))
		{
			*RetObj=&safelevelList;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("userType")))
		{
			*RetObj=&userType;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ftpServer")))
		{
			*RetObj=&ftpServer;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("userId")))
		{
			*RetObj=&userId;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("md5Pwd")))
		{
			*RetObj=&md5Pwd;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ftpPort")))
		{
			*RetObj=&ftpPort;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("userSafelevelId")))
		{
			*RetObj=&userSafelevelId;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("priDeptId")))
		{
			*RetObj=&priDeptId;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("isForceLogin")))
		{
			*RetObj=&isForceLogin;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("loginName")))
		{
			*RetObj=&loginName;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagLogonRetInfo"),this);

		ftpPwd.Save(pStorageObject); 
		result.Save(pStorageObject); 
		isCheckCert.Save(pStorageObject); 
		isImportCert.Save(pStorageObject); 
		fileUploadMaxSize.Save(pStorageObject); 
		ftpUser.Save(pStorageObject); 
		safelevelList.Save(pStorageObject); 
		userType.Save(pStorageObject); 
		ftpServer.Save(pStorageObject); 
		userId.Save(pStorageObject); 
		md5Pwd.Save(pStorageObject); 
		ftpPort.Save(pStorageObject); 
		userSafelevelId.Save(pStorageObject); 
		priDeptId.Save(pStorageObject); 
		isForceLogin.Save(pStorageObject); 
		loginName.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagLogonRetInfo"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ftpPwd); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&result); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&isCheckCert); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&isImportCert); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&fileUploadMaxSize); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ftpUser); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&safelevelList); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&userType); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ftpServer); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&userId); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&md5Pwd); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ftpPort); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&userSafelevelId); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&priDeptId); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&isForceLogin); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&loginName);
		return TRUE;
	}
 

};
