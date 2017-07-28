///////////////////////////////////////////////////////////////////////////////////
//	Copyright 2017 shushen,ye
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//	http://www.apache.org/licenses/LICENSE-2.0
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
///////////////////////////////////////////////////////////////////////////////////

// CodeRender.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "CodeRender.h"
#include "CodeRenderDlg.h"
#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCodeRenderApp

BEGIN_MESSAGE_MAP(CCodeRenderApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCodeRenderApp 构造

CCodeRenderApp::CCodeRenderApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CCodeRenderApp 对象

CCodeRenderApp theApp;


// CCodeRenderApp 初始化
/*
#include <string>
using namespace std;*/
/*
template<typename _Typen>
void Print(string & type,_Typen n)
{
	type= type_info(_Typen).name();
}
*/
/*

template<typename ssss>
class tesy2
{
public:
	//typedef ssss::_MyValType  _MyValType1;
	typename ssss::_MyValType val;
	tesy2(){};
	~tesy2(){};
protected:

private:
};

class test1 : public tesy2<test1>
{
public:
	typedef int _MyValType;
	test1(){};
	~test1(){};
	void Try() {puts("haha!");}
protected:
	
private:
};*/


BOOL CCodeRenderApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	//typedef test1::_MyValType _MyValType;
	//_MyValType a=1;
	//test1::_MyValType s=2;

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	 

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CCodeRenderDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
