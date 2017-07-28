
// WhiteboxTestingPlatform.h : WhiteboxTestingPlatform 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CWhiteboxTestingPlatformApp:
// 有关此类的实现，请参阅 WhiteboxTestingPlatform.cpp
//
#include "BusinessWorkPageWndManger.h"
class CWhiteboxTestingPlatformApp : public CWinAppEx
{
public:
	//工作空间业务管理器
	CBusinessWorkPageWndManger m_WorkSpaceWndManger;
	CWhiteboxTestingPlatformApp();

   GdiplusStartupInput		m_gdiplusStartupInput;
   ULONG_PTR				m_gdiplusToken;
// 重写
public:
	virtual BOOL InitInstance();

	void CreateNewView(CMultiDocTemplate  *pDocTpl);

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	//CMultiDocTemplate* m_pReportDocTpl;
	//CMultiDocTemplate* m_pTestingTaskConfigDocTpl;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	CString GetAppPath();

private:
	CString m_sAppPath;
};

extern CWhiteboxTestingPlatformApp theApp;
