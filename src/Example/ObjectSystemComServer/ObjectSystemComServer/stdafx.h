// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯��������ʽ��

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>

using namespace ATL;



#include <stdio.h>


#include <stdio.h>
#include <tchar.h>
#include "windows.h"
#include <string>
#include <vector>
#include <map>
#include <list>
using namespace std;

#pragma warning(disable: 4996)



#include "Serialize.h"
#include "DataModuleDef.h"
#include "FunctionModule/YDConfig.h"
#include "FunctionModule/DebugFunctionModule.h"
extern CYDConfig	gConfig;

extern  CDebugFunctionModule gDebugTool;

extern HINSTANCE ghInstance;

#define _DebugOutput gDebugTool.Log

#define WndLog
//#include "ObjectSystem_SoapService.h"
#include "ObjectSystem.h"

extern CObjectSystemInterface * gpObjectSystem;
extern void initSys(HINSTANCE hInstance);