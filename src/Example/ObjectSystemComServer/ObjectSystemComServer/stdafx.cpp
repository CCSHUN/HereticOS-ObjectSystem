// stdafx.cpp : 只包括标准包含文件的源文件
// ObjectSystemComServer.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
#include "ObjectSystem_SoapService.h"
CObjectSystemInterface * gpObjectSystem;

CDebugFunctionModule gDebugTool;
CYDConfig	gConfig;
HINSTANCE ghInstance;
CObjectSystem_SoapService gSoapServic;
void initSys(HINSTANCE hInstance)
{
	ghInstance=hInstance;
	gpObjectSystem=&gSoapServic;
	gConfig.init(NULL);
}