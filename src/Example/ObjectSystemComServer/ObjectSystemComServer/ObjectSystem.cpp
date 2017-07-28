// ObjectSystem.cpp : CObjectSystem 的实现

#include "stdafx.h"
#include "ObjectSystem.h"

#include <windows.h>
#include <atlstr.h>
#include <string>
using namespace std;
// CObjectSystem
//unsigned


STDMETHODIMP CObjectSystem::CallInterface(BSTR szUserName, BSTR szConversation, int nOpCode, BSTR szCallParameter, BSTR* szRetXml)
{
	// TODO: 在此添加实现代码
	wstring szRet;
	wstring strUserName(szUserName);
	wstring strConversation(szConversation);
	wstring strCallParameter(szCallParameter);

	/*szRet=strUserName+L"##"+strConversation+L"##";
	OutputDebugStringW(szRet.c_str());
	*szRetXml=CComBSTR(szRet.c_str());
	return S_OK;*/

	WCHAR szOpCode[64];
	if(nOpCode<sizeof(Object_OPTab))
	{
		sprintf_s_t(szOpCode,64,_T("OpCode=%s,"),Object_OPTab[nOpCode]);
	}
	
	szRet=strUserName+L"##"+strConversation+L"##"+szOpCode;
	OutputDebugStringW(szRet.c_str());
	//*szRetXml=CComBSTR(szRet.c_str());
	//return S_OK;

	_tagCallParameter tagCallParameter;
	SerTCHARXmlBufferToObject(_tagCallParameter,tagCallParameter,(strCallParameter.c_str()))

	_tagCallParameter RetParameter;

	CObjectSystemInterface::_tagObjectState ObjectState;
	ObjectState.bLock=tagCallParameter.tagObjectState.bLock;
	ObjectState.nLockTime=tagCallParameter.tagObjectState.nLockTime;
	ObjectState.nType=(CObjectSystemInterface::LockType)tagCallParameter.tagObjectState.nType;
	ObjectState.szLockUser=tagCallParameter.tagObjectState.szLockUser;
	CObjectSystemInterface::SYSTEMERROR		Error=CObjectSystemInterface::Error_No;


	switch(nOpCode)
	{
	case OBJECT_SYSTEM_OP_GETOBJECT:
		{
			if(RetParameter.bCallSuccess=gpObjectSystem->GetObject(tagCallParameter.ObjectPath,RetParameter.Object,ObjectState,&Error))
			{
				RetParameter.tagObjectState.bLock=ObjectState.bLock;
				RetParameter.tagObjectState.nLockTime=ObjectState.nLockTime;
				RetParameter.tagObjectState.nType=(unsigned int)ObjectState.nType;
				RetParameter.tagObjectState.szLockUser=ObjectState.szLockUser;
			}
		}
		
		break;
	case OBJECT_SYSTEM_OP_UPDATAOBJECT:
		//ObjectState.szLockUser=szUserName;
		//RetParameter.bCallSuccess=gpObjectSystem->UpDataObject(tagCallParameter.ObjectPath,tagCallParameter.Object,ObjectState,&Error);
		RetParameter.bCallSuccess=gpObjectSystem->UpDataObject(tagCallParameter.ObjectPath,tagCallParameter.Object,&Error);
		break;
	case OBJECT_SYSTEM_OP_GETDIRECTORYINFO:
		RetParameter.bCallSuccess=gpObjectSystem->GetDirectoryInfo(tagCallParameter.ObjectPath,tagCallParameter.szFinder,RetParameter.DirectoryInfo,&Error);
		break;
	case OBJECT_SYSTEM_OP_DELETEOBJECT:
		RetParameter.bCallSuccess=gpObjectSystem->DeleteObject(tagCallParameter.ObjectPath,&Error);
		break;
	case OBJECT_SYSTEM_OP_GETOBJECTSTATE:
		break;
	case OBJECT_SYSTEM_OP_UPDATAOBJECTSTATE:
		break;
	case OBJECT_SYSTEM_OP_LOGONINSYSTEM:
		RetParameter.bCallSuccess=gpObjectSystem->LogonInSystem(strUserName,tagCallParameter.szPassword);
		break;
	case OBJECT_SYSTEM_OP_LOGONOUTSYSTEM:
		RetParameter.bCallSuccess=gpObjectSystem->LogonOutSystem();

		break;
	case OBJECT_SYSTEM_OP_GETCURTIME:
		{
			vector<unsigned char> npTime,nCurTime;
			 
			CBase64Zip::Base64ZipUnCompress(tagCallParameter.strPar[_T("npTime")].szVar,npTime);
			CBase64Zip::Base64ZipUnCompress(tagCallParameter.strPar[_T("nCurTime")].szVar,nCurTime);
			RetParameter.bCallSuccess=gpObjectSystem->GetCurTime((SYSTEMTIME*)&npTime[0],(SYSTEMTIME*)&nCurTime[0]);
			CBase64Zip::Base64ZipCompress(&nCurTime[0],sizeof(SYSTEMTIME),RetParameter.strPar[_T("nCurTime")].szVar);

		}
		break;
	case OBJECT_SYSTEM_OP_RELEASEOBJSTATE:
		RetParameter.bCallSuccess=gpObjectSystem->ReleaseObjectState(tagCallParameter.ObjectPath,&Error);
		break;
	default:
		OutputDebugString(_T("错误的命令"));
		break;
	}

	RetParameter.nError=(unsigned int)Error;

	SerObjectToXmlBuffer(_tagCallParameter,RetParameter,szRet);
	sprintf_s_t(szOpCode,64,_T("nRet=%d,bRet=%d"),szRet.length(),RetParameter.bCallSuccess);
	OutputDebugString(szOpCode);

	*szRetXml=::SysAllocString(szRet.c_str());
	return S_OK;
}
