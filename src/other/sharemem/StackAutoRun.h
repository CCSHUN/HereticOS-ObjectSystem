// StackAutoRun.h: interface for the CStackAutoRun class.
// 作者：叶树深 时间：2010.3.29
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACKAUTORUN_H__3AF741F9_9B7D_4D4E_8393_11F98BF617FA__INCLUDED_)
#define AFX_STACKAUTORUN_H__3AF741F9_9B7D_4D4E_8393_11F98BF617FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "StdAfx.h"

template <class _Function>
class CStackAutoRun  
{
public:
	_Function * m_pFunc;
	CStackAutoRun(_Function * Func)
	{
		m_pFunc=Func;
		m_pFunc->begin();
	};
	~CStackAutoRun()
	{
		m_pFunc->end();
	};

};

class LockFunc
{
public:
	CRITICAL_SECTION m_lock;
	LockFunc()
	{
		::InitializeCriticalSection(&m_lock);
	};
	/*
	init()
		{
			::InitializeCriticalSection(&m_lock);
		}*/


	BOOL begin()
	{
		//_DebugOutput("LockFunc EnterCriticalSection 0x%x",&m_lock);
		EnterCriticalSection(&m_lock);
		return TRUE;
	}

	BOOL end()
	{
		//_DebugOutput("LockFunc LeaveCriticalSection 0x%x",&m_lock);
		LeaveCriticalSection(&m_lock);
		return TRUE;
	}

	
	~LockFunc(){};
protected:
	
private:
};

typedef CStackAutoRun<LockFunc> CStackAutoLock;
	
#endif // !defined(AFX_STACKAUTORUN_H__3AF741F9_9B7D_4D4E_8393_11F98BF617FA__INCLUDED_)
