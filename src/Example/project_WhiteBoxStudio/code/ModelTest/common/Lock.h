#pragma once
#include <assert.h>

#define MUTEX_STRING  _T("KcgServerLoader.Rule")

//ServerFunction::CMutex g_Mutex(MUTEX_STRING);
//ServerFunction::CLockMutex lock(g_Mutex);

namespace ServerFunction
{
	class CCriticalSec : public CRITICAL_SECTION
	{
	public:
		CCriticalSec()
		{
			::InitializeCriticalSection(this);
		}
		explicit CCriticalSec(DWORD dwSpinCount)
		{
			::InitializeCriticalSectionAndSpinCount(this, dwSpinCount);
		}
		~CCriticalSec()
		{
			::DeleteCriticalSection(this);
		}
	};

	//用于锁定及解锁Critical Section。
	//由这样一个对象在析构时释放资源是C++中常用的技巧，这样的代码更易维护，并对异常处
	//理透明。
	class CInProcessLock
	{
		LPCRITICAL_SECTION m_pCS;
	public:
		explicit CInProcessLock(LPCRITICAL_SECTION pCS)
		{
			::EnterCriticalSection(m_pCS = pCS);
		}
		~CInProcessLock()
		{
			::LeaveCriticalSection(m_pCS);
		}
	};

	class CMutex
	{
	public:
		CMutex()
		{ 
			m_hMutex = NULL; 
		};
		CMutex(LPCTSTR mutexName)
		{ 
			Build(mutexName); 
		}
		~CMutex()
		{
			if (m_hMutex != NULL)
			{
				CloseHandle(m_hMutex);
				m_hMutex = NULL;
			}
		}

		void Build(LPCTSTR mutexName)
		{
			m_hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, mutexName);
			if (m_hMutex == NULL)
				m_hMutex = CreateMutex(NULL, FALSE, mutexName);
		}
		operator HANDLE ()
		{
			return m_hMutex;
		}

	private:
		HANDLE m_hMutex;
	};

	//访问互斥器
	class CLockMutex
	{
		HANDLE m_hMutex;
	public:
		CLockMutex(HANDLE hMutex)
		{
			assert(hMutex != NULL);
			::WaitForSingleObject(m_hMutex = hMutex, INFINITE);
		}
		~CLockMutex()
		{
			::ReleaseMutex(m_hMutex);
		}
	};

}