#include "stdafx.h"
#include "SoapOperation.h"
#include "atlcomcli.h"
#import "msxml4.dll" 

#ifdef X86FOR64SYS
#import "C:\Program Files (x86)\Common Files\MSSoap\Binaries\mssoap30.dll" exclude("IStream", "IErrorInfo", "ISequentialStream", "_LARGE_INTEGER",   "_ULARGE_INTEGER", "tagSTATSTG", "_FILETIME")
#else
#import "C:\Program Files\Common Files\MSSoap\Binaries\mssoap30.dll" exclude("IStream", "IErrorInfo", "ISequentialStream", "_LARGE_INTEGER",   "_ULARGE_INTEGER", "tagSTATSTG", "_FILETIME")
#endif

using namespace MSXML2;
using namespace MSSOAPLib30; 


#pragma comment(lib, "Ws2_32.lib")
/*
LPCTSTR BASE_SOAP_ACTION_URI = _T("http://conTest.yidong.net/services/connTest");
LPCTSTR WRAPPER_ELEMENT_NAMESPACE = _T("http://tempuri.org/Calc/message/");
*/

LPCTSTR BASE_SOAP_ACTION_URI = _T("http://tempuri.org/ObjectSystem/action/ObjectSystem.");
LPCTSTR WRAPPER_ELEMENT_NAMESPACE = _T("http://tempuri.org/ObjectSystem/message/");


CSoapOperation::CSoapOperation(void)
{
}

CSoapOperation::~CSoapOperation(void)
{
}
//sprintf_s_t()

BOOL CSoapOperation::CallInterface(tstring & szUserName,tstring & szConversation,int nOpCode,_tagCallParameter & tagCallParameter,_tagCallParameter & RetParameter)
{

	HRESULT hr;
	TimeUsedBegin(nUsedTime);
	::CoInitialize(NULL);

	tstring szObjPath;
	if((nOpCode==OBJECT_SYSTEM_OP_UPDATAOBJECT)||(nOpCode==OBJECT_SYSTEM_OP_GETOBJECT)||(nOpCode==OBJECT_SYSTEM_OP_GETDIRECTORYINFO))
	{
		szObjPath=tagCallParameter.ObjectPath;
	}

	try
	{

		ISoapSerializerPtr pSerializer;
		ISoapReaderPtr pReader;
		ISoapConnectorPtr pConnector;

		hr = pConnector.CreateInstance(__uuidof(HttpConnector30));
		if(FAILED(hr))
		{
			//DisplayHResult(_T("Cannot create SoapClient."), hr);
			_DebugOutput(_T("CYD_SoapServoce"),_T("CallInterface Cannot create SoapClient."));
			return FALSE;
		}

		pConnector->Property["EndPointURL"] = _variant_t(gConfig.m_Config.strWSDLUrl.c_str());


		tstring SoapAction=tstring(BASE_SOAP_ACTION_URI) + _T("CallInterface");
		pConnector->Property["SoapAction"] = _variant_t(SoapAction.c_str());
		pConnector->Property["Timeout"]=gConfig.m_Config.nSoapTimeout;

		//pConnector->Connect();
		//pConnector->Property["ServerHTTPRequest"]=1;

		pConnector->BeginMessage();

		hr = pSerializer.CreateInstance(__uuidof(SoapSerializer30));
		pSerializer->Init((IUnknown*)pConnector->InputStream);

		pSerializer->StartEnvelope("","", "");
		pSerializer->StartBody("STANDARD");
		pSerializer->StartElement("CallInterface", WRAPPER_ELEMENT_NAMESPACE, "", "");

		pSerializer->StartElement("szUserName", "", "", "");
		pSerializer->WriteString(_bstr_t(szUserName.c_str()));
		pSerializer->EndElement();


		
		pSerializer->StartElement("szConversation", "", "", "");
		pSerializer->WriteString(_bstr_t(szConversation.c_str()));
		pSerializer->EndElement();

		pSerializer->StartElement("nOpCode", "", "", "");

		TCHAR szOpCode[8]={0};
		itoa_t(nOpCode,szOpCode,10);
		pSerializer->WriteString(_bstr_t(szOpCode));
		pSerializer->EndElement();

		tstring  szCallParameter;
		SerObjectToXmlBuffer(_tagCallParameter,tagCallParameter,szCallParameter)
		pSerializer->StartElement("szCallParameter", "", "", "");
		pSerializer->WriteString(_bstr_t(szCallParameter.c_str()));
		pSerializer->EndElement();

		pSerializer->EndElement();
		pSerializer->EndBody();
		pSerializer->EndEnvelope();


		pConnector->EndMessage();

		pReader.CreateInstance(__uuidof(SoapReader30));
		pReader->Load((IUnknown*)pConnector->OutputStream, "");

		if(pReader->Fault != NULL)
		{
			//MessageBox(pReader->FaultString->text, NULL, MB_ICONEXCLAMATION);
			tstring szError(pReader->FaultString->text);
			TimeUsedEnd(nUsedTime);
			_DebugOutput(_T("ObjectSystem_SoapClient"),_T("CallInterface Path=[%s] op=%s pReader->Fault,%s"),szObjPath.c_str(),Object_OPTab[nOpCode],szError.c_str());
			WndLog(_T("ObjectSystem_SoapClient"),_T("CallInterface Path=[%s] op=%s pReader->Fault,%s"),szObjPath.c_str(),Object_OPTab[nOpCode],szError.c_str());
			//tstring szErr1=_T("CallInterface pReader->Fault")+szError;
			//
			return FALSE;
		}
		else
		{
			//m_ResultCtl.SetWindowText(pReader->RpcResult->text);
			//AfxMessageBox(pReader->RpcResult->text);
			//LPCTSTR pText=(LPCTSTR)pReader->RpcResult->text;
			tstring szRetXml=pReader->RpcResult->text;
			RetParameter.bCallSuccess=FALSE;
			unsigned int nl=szRetXml.length();
			SerTCHARXmlBufferToObject(_tagCallParameter,RetParameter,(szRetXml.c_str()))
			TimeUsedEnd(nUsedTime);
			WndLog(_T("ObjectSystem_SoapClient"),_T("CallInterface Path=[%s] op=%s  OK Ret=%d,Err=%d(用时%d　ms)"),
				szObjPath.c_str(),Object_OPTab[nOpCode],RetParameter.bCallSuccess,RetParameter.nError,nUsedTime);
			if(gConfig.m_Config.szDebugLevel==_T("高"))
			{
				if((RetParameter.nError!=CObjectSystemInterface::Error_No)
					&&(RetParameter.nError!=CObjectSystemInterface::Error_ObjectAlreadyLock)
					)
				{
					TCHAR szMsg[4096];
					sprintf_s_t(szMsg,4096,_T("操作失败 Path=[%s] op=%s  OK Ret=%d,Err=%d(用时%d　ms)"),
						szObjPath.c_str(),Object_OPTab[nOpCode],
						RetParameter.bCallSuccess,RetParameter.nError,nUsedTime);
					//::AfxMessageBox(szMsg);
				}
			}
			return TRUE;
		}

	}
	catch(_com_error x)
	{
		//MessageBox(CString("ERROR: ") + (wchar_t*)x.Description(), NULL, MB_ICONEXCLAMATION);
		TCHAR * pInfo=(TCHAR *)x.ErrorMessage();
		//_bstr_t s=x.Description();
		//pInfo=(TCHAR *)s;
		_DebugOutput(_T("ObjectSystem_SoapClient"),_T("CallInterface Path=[%s] op=%s ERROR info: %s"),szObjPath.c_str(),Object_OPTab[nOpCode],(wchar_t*)x.Description());
		WndLog(_T("ObjectSystem_SoapClient"),_T("CallInterface Path=[%s] op=%s ERROR info: %s"),szObjPath.c_str(),Object_OPTab[nOpCode],(wchar_t*)x.Description());
		return FALSE;
	}


}
