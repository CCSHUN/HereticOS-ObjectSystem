#pragma once

class CCriticalSection
{
public:
	CRITICAL_SECTION m_CriticalSection;
	CCriticalSection()
	{
		InitializeCriticalSection(&m_CriticalSection);
	};
	~CCriticalSection()
	{
		DeleteCriticalSection(&m_CriticalSection);
	}
protected:
	
private:
	
};

//class CAutoStackLock
class CAutoStackLock
{
public:
	CAutoStackLock(CCriticalSection * lock,const TCHAR *pLockCaller){
		m_pLock=lock;
		m_szOwer=pLockCaller;
		::EnterCriticalSection(&m_pLock->m_CriticalSection);
		TCHAR szMsg[MAX_PATH];
		sprintf_s_t(szMsg,MAX_PATH-2,_T("EnterCriticalSection CallerThread=%d,Caller=%s"),GetCurrentThreadId(),m_szOwer.c_str());
		OutputDebugString(szMsg);
	};
	~CAutoStackLock(){
		::LeaveCriticalSection(&m_pLock->m_CriticalSection);
		TCHAR szMsg[MAX_PATH];
		sprintf_s_t(szMsg,MAX_PATH-2,_T("LeaveCriticalSection CallerThread=%d,Caller=%s"),GetCurrentThreadId(),m_szOwer.c_str());
		OutputDebugString(szMsg);

	};
protected:
	
private:
	tstring m_szOwer;
	CCriticalSection * m_pLock;
};
