
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target IE 5.0 or later.
#endif


#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



//#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
//#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持


#include <afxsock.h>            // MFC 套接字扩展

#include <afxhtml.h>

//#define CWinAppEx CWinApp

#include <stdio.h>
#include <tchar.h>
#include "windows.h"
#include <string>
#include <vector>
#include <map>
#include <list>
using namespace std;

#pragma warning(disable: 4996)

#include "..\..\..\ModelTest\common\SerializeFunction\Serialize.h"
#include "..\..\..\ModelTest\commondef\DataModuleDef.h"

#include "BusinessWorkPageWndManger.h"


#include <afxdhtml.h>
//#define MAKESTRUCTINFO(_d) 

#include "TestConfig.h"
//#include "TestFrameData.h"



#include "YDConfig.h"
#include "DebugFunctionModule.h"
extern CYDConfig	gConfig;

extern  CDebugFunctionModule gDebugTool;
#define _DebugOutput gDebugTool.Log


#include "ObjectSystem_SoapClient.h"
extern  CObjectSystem_SoapClient gSoapObjectSystem;

#include "ObjectSystem_Local.h"
extern  CObjectSystem_Local gobjsys;

#pragma comment(lib,"gdiplus.lib")
#include <gdiplus.h>
using namespace Gdiplus;

#include "MainFrm.h"
#include <afxdhtml.h>
extern  CMainFrame * g_pOutWnd;

extern BOOL WndLog( const WCHAR * szHead,const WCHAR * line,... );
extern BOOL WndLog( const char * szHead,const char * line,... );


extern HINSTANCE ghInstance;

class CMyMDIChildWndEx : public CMDIChildWndEx
{
public:
	CMyMDIChildWndEx(){};
	~CMyMDIChildWndEx(){};
protected:
	
private:
};

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


