// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// ObjectSystemComServer.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

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