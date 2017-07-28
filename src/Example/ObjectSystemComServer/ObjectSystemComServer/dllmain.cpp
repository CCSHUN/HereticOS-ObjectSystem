// dllmain.cpp : DllMain 的实现。

#include "stdafx.h"
#include "resource.h"
#include "ObjectSystemComServer_i.h"
#include "dllmain.h"
#include "ObjectSystem_SoapService.h"
CObjectSystemComServerModule _AtlModule;



// DLL 入口点
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	//gObjectSystem=&gSoapServic;
	initSys( hInstance);
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
