// ThreadBaseForWin32App.h: interface for the CThreadBaseForWin32App class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADBASEFORWIN32APP_H__CDA5E2B2_844F_4E03_B2A4_2BA8CF521817__INCLUDED_)
#define AFX_THREADBASEFORWIN32APP_H__CDA5E2B2_844F_4E03_B2A4_2BA8CF521817__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "StdAfx.h"
#define CThreadBase CThreadBaseForWin32App
//#define BOOL unsigned int
class CThreadBaseForWin32App  
{
public:
	BOOL SetLowIntegrity(char *pObjName);
	BOOL BuildAlowingSD(SECURITY_ATTRIBUTES *pObjectAttributes,ACCESS_MASK AccessMask,void * pObjName);
	BOOL Log( const char * line,...);
	CThreadBaseForWin32App();
	virtual ~CThreadBaseForWin32App();

};

#endif // !defined(AFX_THREADBASEFORWIN32APP_H__CDA5E2B2_844F_4E03_B2A4_2BA8CF521817__INCLUDED_)
