
// AutoStructDataDesign.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAutoStructDataDesignApp:
// �йش����ʵ�֣������ AutoStructDataDesign.cpp
//

class CAutoStructDataDesignApp : public CWinAppEx
{
public:
	CAutoStructDataDesignApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAutoStructDataDesignApp theApp;