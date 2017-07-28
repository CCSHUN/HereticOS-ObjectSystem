#pragma once

#ifndef _LINUX_
class CCriticalSectionStack
{
public:
	typedef CRITICAL_SECTION SpinLockT;
	volatile SpinLockT m_CriticalSection;
	CCriticalSectionStack()
	{
		InitializeCriticalSection((LPCRITICAL_SECTION)&m_CriticalSection);
	};
	~CCriticalSectionStack()
	{
		DeleteCriticalSection((LPCRITICAL_SECTION)&m_CriticalSection);
	} 


protected:
	
private:
	
};

//class CAutoStackLock
class CAutoStackLock
{
public:
	void Lock(volatile CCriticalSectionStack * lock, const TCHAR *pLockCaller = NULL)
	{
		m_pLock=lock;
		if(m_pLock==NULL) return;
		
#ifdef _DEBUG
		if(pLockCaller)
		{
			m_szOwer=pLockCaller;
			
			TCHAR szMsg[MAX_PATH];
			sprintf_s_t(szMsg,MAX_PATH-2,_T("CAutoStackLock %x EnterBegin (LockCount=%d,ReCount=%d owntid=%d) CallerThread=%d,Caller=%s"),
				m_pLock,
				m_pLock->m_CriticalSection.LockCount,
				m_pLock->m_CriticalSection.RecursionCount,
				m_pLock->m_CriticalSection.OwningThread,
				GetCurrentThreadId(),
				m_szOwer.c_str());

			OutputDebugString(szMsg);

		}
#endif
		::EnterCriticalSection((LPCRITICAL_SECTION)&m_pLock->m_CriticalSection);

#ifdef _DEBUG
		if(pLockCaller)
		{
			m_szOwer=pLockCaller;

			TCHAR szMsg[MAX_PATH];
			sprintf_s_t(szMsg,MAX_PATH-2,_T("CAutoStackLock %x EnterEnd (LockCount=%d,ReCount=%d owntid=%d) CallerThread=%d,Caller=%s"),
				m_pLock,
				m_pLock->m_CriticalSection.LockCount,
				m_pLock->m_CriticalSection.RecursionCount,
				m_pLock->m_CriticalSection.OwningThread,
				GetCurrentThreadId(),
				m_szOwer.c_str());

			OutputDebugString(szMsg);

		}
#endif

	};

	BOOL TryLock(volatile CCriticalSectionStack * lock,const TCHAR *pLockCaller=NULL)
	{
		
		BOOL bTryLock = FALSE;
		m_pLock = lock;

#ifdef _DEBUG
		if(pLockCaller)
		{
			m_szOwer=pLockCaller;

			TCHAR szMsg[MAX_PATH];
			sprintf_s_t(szMsg,MAX_PATH-2,_T("CAutoStackLock %x TryEnterBegin (LockCount=%d,ReCount=%d owntid=%d) CallerThread=%d,Caller=%s"),
				m_pLock,
				m_pLock->m_CriticalSection.LockCount,
				m_pLock->m_CriticalSection.RecursionCount,
				m_pLock->m_CriticalSection.OwningThread,
				GetCurrentThreadId(),
				m_szOwer.c_str());

			OutputDebugString(szMsg);

		}
#endif
		bTryLock = ::TryEnterCriticalSection((LPCRITICAL_SECTION)&m_pLock->m_CriticalSection);

#ifdef _DEBUG
		if(pLockCaller)
		{
			m_szOwer=pLockCaller;

			TCHAR szMsg[MAX_PATH];
			sprintf_s_t(szMsg,MAX_PATH-2,_T("CAutoStackLock %x TryEnterEnd (LockCount=%d,ReCount=%d owntid=%d) CallerThread=%d,Caller=%s"),
				m_pLock,
				m_pLock->m_CriticalSection.LockCount,
				m_pLock->m_CriticalSection.RecursionCount,
				m_pLock->m_CriticalSection.OwningThread,
				GetCurrentThreadId(),
				m_szOwer.c_str());

			OutputDebugString(szMsg);

		}
#endif
		if (bTryLock==FALSE) m_pLock = NULL;
		return bTryLock;

	};

	void UnLock()
	{
		try
		{
#ifdef _DEBUG
			if(m_pLock&&m_szOwer.length())
			{
				TCHAR szMsg[MAX_PATH];
				sprintf_s_t(szMsg,MAX_PATH-2,_T("CAutoStackLock %x LeaveBegin (LockCount=%d,ReCount=%d owntid=%d) CallerThread=%d,Caller=%s"),
					m_pLock,
					m_pLock->m_CriticalSection.LockCount,
					m_pLock->m_CriticalSection.RecursionCount,
					m_pLock->m_CriticalSection.OwningThread,
					GetCurrentThreadId(),m_szOwer.c_str());

				OutputDebugString(szMsg);

			}
#endif

			if(m_pLock) 
			{
				::LeaveCriticalSection((LPCRITICAL_SECTION)&m_pLock->m_CriticalSection);

#ifdef _DEBUG
				if(m_szOwer.length())
				{
					TCHAR szMsg[MAX_PATH];
					sprintf_s_t(szMsg,MAX_PATH-2,_T("CAutoStackLock %x LeaveEnd (LockCount=%d,ReCount=%d owntid=%d) CallerThread=%d,Caller=%s"),
						m_pLock,
						m_pLock->m_CriticalSection.LockCount,
						m_pLock->m_CriticalSection.RecursionCount,
						m_pLock->m_CriticalSection.OwningThread,
						GetCurrentThreadId(),m_szOwer.c_str());

					OutputDebugString(szMsg);

				}
#endif
				m_pLock=NULL;
			}
		}
		catch (...)
		{
#ifdef _DEBUG
			OutputDebugString(_T("CAutoStackLock UnLock Exception"));
#endif
		}

	};

	CAutoStackLock(){
		m_pLock=NULL;
	};

	CAutoStackLock(volatile CCriticalSectionStack * lock){
		Lock(lock,NULL);
	};

	CAutoStackLock(volatile CCriticalSectionStack * lock, const TCHAR *pLockCaller){
		Lock(lock,pLockCaller);
	};
	~CAutoStackLock(){
		if(m_pLock) UnLock();
	};
protected:
	
private:
	tstring m_szOwer;
	volatile CCriticalSectionStack * m_pLock;
};

#endif
