
// CodeRender.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCodeRenderApp:
// �йش����ʵ�֣������ CodeRender.cpp
//

class CCodeRenderApp : public CWinAppEx
{
public:
	CCodeRenderApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCodeRenderApp theApp;