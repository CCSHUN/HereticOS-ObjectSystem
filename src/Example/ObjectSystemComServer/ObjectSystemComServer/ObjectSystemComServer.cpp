// ObjectSystemComServer.cpp : DLL ������ʵ�֡�


#include "stdafx.h"
#include "resource.h"
#include "ObjectSystemComServer_i.h"
#include "dllmain.h"
//#include "ObjectSystemComServer_i.h"
#include "ObjectSystem.h"

//CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ObjectSystem, CObjectSystem)
END_OBJECT_MAP()

// ����ȷ�� DLL �Ƿ���� OLE ж��
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}


// ����һ���๤���Դ������������͵Ķ���
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - ������ӵ�ϵͳע���
STDAPI DllRegisterServer(void)
{
    // ע��������Ϳ�����Ϳ��е����нӿ�
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - �����ϵͳע������Ƴ�
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}

// DllInstall - ���û����߰��������ϵͳע��������/ɾ��
//              �	
STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
    HRESULT hr = E_FAIL;
    static const wchar_t szUserSwitch[] = _T("user");

    if (pszCmdLine != NULL)
    {
    	if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
    	{
    		AtlSetPerUserRegistration(true);
    	}
    }

    if (bInstall)
    {	
    	hr = DllRegisterServer();
    	if (FAILED(hr))
    	{	
    		DllUnregisterServer();
    	}
    }
    else
    {
    	hr = DllUnregisterServer();
    }

    return hr;
}


