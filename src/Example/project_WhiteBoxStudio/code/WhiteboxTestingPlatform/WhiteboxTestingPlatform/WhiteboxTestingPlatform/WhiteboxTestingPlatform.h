
// WhiteboxTestingPlatform.h : WhiteboxTestingPlatform Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CWhiteboxTestingPlatformApp:
// �йش����ʵ�֣������ WhiteboxTestingPlatform.cpp
//
#include "BusinessWorkPageWndManger.h"
class CWhiteboxTestingPlatformApp : public CWinAppEx
{
public:
	//�����ռ�ҵ�������
	CBusinessWorkPageWndManger m_WorkSpaceWndManger;
	CWhiteboxTestingPlatformApp();

   GdiplusStartupInput		m_gdiplusStartupInput;
   ULONG_PTR				m_gdiplusToken;
// ��д
public:
	virtual BOOL InitInstance();

	void CreateNewView(CMultiDocTemplate  *pDocTpl);

// ʵ��
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
