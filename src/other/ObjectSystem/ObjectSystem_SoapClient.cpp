#include "stdafx.h"
#include "ObjectSystem_SoapClient.h"
//#include "DataModuleDef.h"


CObjectSystem_SoapClient::CObjectSystem_SoapClient(void)
{
	m_szUserName=_T("");
	m_szConversation=_T("");
}

CObjectSystem_SoapClient::~CObjectSystem_SoapClient(void)
{
}

BOOL  CObjectSystem_SoapClient::GetCurTime(SYSTEMTIME * npTime,SYSTEMTIME * nCurTime)
{
	
	_tagCallParameter Par,RetPar,Par1,RetPar2;
	tstring szTime;
	CBase64Zip::Base64ZipCompress((unsigned char *)npTime,sizeof(SYSTEMTIME),szTime);
	_tagstrParameter Var;
	Var.szVar=szTime;
	Par.strPar[_T("npTime")]=Var;
	CBase64Zip::Base64ZipCompress((unsigned char *)nCurTime,sizeof(SYSTEMTIME),szTime);
	Var.szVar=szTime;
	Par.strPar[_T("nCurTime")]=Var;

	tstring szCallParameter;
	Par1=Par;

	BOOL bRet=m_SoapOperation.CallInterface(m_szUserName,m_szConversation,OBJECT_SYSTEM_OP_GETCURTIME,Par,RetPar);

	
	if(bRet)
	{
		vector<unsigned char> var;
		if(CBase64Zip::Base64ZipUnCompress(RetPar.strPar[_T("nCurTime")].szVar,var))
		{
			*nCurTime=*(SYSTEMTIME *)&var[0];
		}
		return RetPar.bCallSuccess;
	}
	return FALSE;
}

BOOL CObjectSystem_SoapClient::LogonInSystem(IN tstring & szUserName,IN tstring & szPassword)
{
	m_szUserName=szUserName;
	m_szConversation=szPassword;
	_tagCallParameter Par,RetPar;
	Par.szPassword=szPassword;
	BOOL bRet=m_SoapOperation.CallInterface(m_szUserName,m_szConversation,OBJECT_SYSTEM_OP_LOGONINSYSTEM,Par,RetPar);
	if(bRet)
	{
		return RetPar.bCallSuccess;
	}
	return FALSE;
}

BOOL CObjectSystem_SoapClient::ReleaseObjectState(IN tstring & ObjectOrDir,OUT SYSTEMERROR * pError)
{

	_tagCallParameter Par,RetPar;
	Par.ObjectPath=ObjectOrDir;
	BOOL bRet=m_SoapOperation.CallInterface(m_szUserName,m_szConversation,OBJECT_SYSTEM_OP_RELEASEOBJSTATE,Par,RetPar);
	if(bRet)
	{
		*pError=(SYSTEMERROR)RetPar.nError;

		return RetPar.bCallSuccess;
	}
	return FALSE;
}

BOOL CObjectSystem_SoapClient::LogonOutSystem()
{
	_tagCallParameter Par,RetPar;
	BOOL bRet=m_SoapOperation.CallInterface(m_szUserName,m_szConversation,OBJECT_SYSTEM_OP_LOGONOUTSYSTEM,Par,RetPar);
	if(bRet)
	{
		return RetPar.bCallSuccess;
	}
	return FALSE;
}


BOOL CObjectSystem_SoapClient::GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
{
	_tagCallParameter Par,RetPar;
	Par.ObjectPath=ObjectPath;
	Par.tagObjectState.bLock=ObjectState.bLock;
	Par.tagObjectState.nType=(unsigned int)ObjectState.nType;
	Par.tagObjectState.nLockTime=ObjectState.nLockTime;
	Par.tagObjectState.szLockUser=ObjectState.szLockUser;
	BOOL bRet=m_SoapOperation.CallInterface(m_szUserName,m_szConversation,OBJECT_SYSTEM_OP_GETOBJECT,Par,RetPar);
	if(bRet)
	{
		*pError=(SYSTEMERROR)RetPar.nError;
		ObjectState.bLock=RetPar.tagObjectState.bLock;
		ObjectState.nLockTime=RetPar.tagObjectState.nLockTime;
		ObjectState.nType=(LockType)RetPar.tagObjectState.nType;
		ObjectState.szLockUser=RetPar.tagObjectState.szLockUser;

		if(RetPar.bCallSuccess)
		{
			Object=RetPar.Object;
		}
		return RetPar.bCallSuccess;
	}
	return FALSE;
}


//更新对象到存储
BOOL CObjectSystem_SoapClient::UpDataObject(IN tstring & ObjectPath,IN tstring & Object,SYSTEMERROR * pError)
{
	_tagCallParameter Par,RetPar;
	Par.ObjectPath=ObjectPath;
	Par.Object=Object;
	BOOL bRet=m_SoapOperation.CallInterface(m_szUserName,m_szConversation,OBJECT_SYSTEM_OP_UPDATAOBJECT,Par,RetPar);
	if(bRet)
	{
		*pError=(SYSTEMERROR)RetPar.nError;
		return RetPar.bCallSuccess;
	}
	return FALSE;
}


//获取目录信息
BOOL CObjectSystem_SoapClient::GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError)
{
	_tagCallParameter Par,RetPar;
	Par.ObjectPath=DirectoryPath;
	Par.szFinder=szFinder;
	BOOL bRet=m_SoapOperation.CallInterface(m_szUserName,m_szConversation,OBJECT_SYSTEM_OP_GETDIRECTORYINFO,Par,RetPar);
	if(bRet)
	{
		*pError=(SYSTEMERROR)RetPar.nError;
		_tagDirectoryInfoSet set;
		DirectoryInfo.DirectoryInfoArray.resize(RetPar.DirectoryInfo.DirectoryInfoArray.size());
		for(unsigned int i=0;i<DirectoryInfo.DirectoryInfoArray.size();i++)
		{
			DirectoryInfo.DirectoryInfoArray[i].ObjectName=RetPar.DirectoryInfo.DirectoryInfoArray[i].ObjectName;
			DirectoryInfo.DirectoryInfoArray[i].ObjectType=(DirectoryObjectType)RetPar.DirectoryInfo.DirectoryInfoArray[i].ObjectType;
			DirectoryInfo.DirectoryInfoArray[i].OtherInfo=RetPar.DirectoryInfo.DirectoryInfoArray[i].OtherInfo;
		}
		return RetPar.bCallSuccess;
	}
	return FALSE;
}


//删除对象
BOOL CObjectSystem_SoapClient::DeleteObject(IN tstring & ObjectOrDir,SYSTEMERROR * pError)
{
	_tagCallParameter Par,RetPar;
	Par.ObjectPath=ObjectOrDir;
	BOOL bRet=m_SoapOperation.CallInterface(m_szUserName,m_szConversation,OBJECT_SYSTEM_OP_DELETEOBJECT,Par,RetPar);
	if(bRet)
	{
		*pError=(SYSTEMERROR)RetPar.nError;
		return RetPar.bCallSuccess;
	}
	return FALSE;
}


BOOL CObjectSystem_SoapClient::UpDataObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
{
	return TRUE;
}


BOOL CObjectSystem_SoapClient::GetObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
{
	return TRUE;
}