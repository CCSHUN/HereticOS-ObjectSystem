
// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoStructDataDesign.h"
#include "DlgProxy.h"
#include "AutoStructDataDesignDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoStructDataDesignDlgAutoProxy

IMPLEMENT_DYNCREATE(CAutoStructDataDesignDlgAutoProxy, CCmdTarget)

CAutoStructDataDesignDlgAutoProxy::CAutoStructDataDesignDlgAutoProxy()
{
	EnableAutomation();
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CAutoStructDataDesignDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CAutoStructDataDesignDlg)))
		{
			m_pDialog = reinterpret_cast<CAutoStructDataDesignDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CAutoStructDataDesignDlgAutoProxy::~CAutoStructDataDesignDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	// 	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CAutoStructDataDesignDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CAutoStructDataDesignDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAutoStructDataDesignDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IAutoStructDataDesign 的支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {63A4B192-BE39-4A4A-8715-08899BC5F756}
static const IID IID_IAutoStructDataDesign =
{ 0x63A4B192, 0xBE39, 0x4A4A, { 0x87, 0x15, 0x8, 0x89, 0x9B, 0xC5, 0xF7, 0x56 } };

BEGIN_INTERFACE_MAP(CAutoStructDataDesignDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CAutoStructDataDesignDlgAutoProxy, IID_IAutoStructDataDesign, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {33378D5A-5F55-4986-9FC9-704A62084595}
IMPLEMENT_OLECREATE2(CAutoStructDataDesignDlgAutoProxy, "AutoStructDataDesign.Application", 0x33378d5a, 0x5f55, 0x4986, 0x9f, 0xc9, 0x70, 0x4a, 0x62, 0x8, 0x45, 0x95)


// CAutoStructDataDesignDlgAutoProxy 消息处理程序
