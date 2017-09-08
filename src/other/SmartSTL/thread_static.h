#pragma once
#include "../BaseFunctionTool.h"
#include "StateList.h"

class ThreadLocalStaticObjectImpl :  public TransferListNoHead<ThreadLocalStaticObjectImpl, 1>::_NodeBase
{
public:
	ThreadLocalStaticObjectImpl() {};
	~ThreadLocalStaticObjectImpl() {};
	virtual void ThreadInit() {};
private:

};


extern TransferList<ThreadLocalStaticObjectImpl, 1> g_ThreadLocalObjectList;

template<typename _ObjectT>
class ThreadLocalStaticObject : public ThreadLocalStaticObjectImpl
{
public:
	typedef _ObjectT ObjectT;
	thread_local static ObjectT * m_pThreadLocalObject;

	ThreadLocalStaticObject() { 
		Error(_T("ThreadLocalStaticObject Thread construct %u ThreadLocalObj=%p name=%s \n"), GetCurrentThreadId(), this, typeid(m_pThreadLocalObject).name());
		g_ThreadLocalObjectList.AddNode(0, this);
	};
	~ThreadLocalStaticObject() {};
	void ThreadInit() {
		m_pThreadLocalObject = new ObjectT;
		Error(_T("ThreadLocalStaticObject Thread New %u ThreadLocalObj=%p name=%s \n"), GetCurrentThreadId(), this, typeid(m_pThreadLocalObject).name());
		if (pPrev)
		{
			pPrev->ThreadInit();
		}
	};
	static void Init()
	{
		if(g_ThreadLocalObjectList.m_NodeArray[0]) g_ThreadLocalObjectList.m_NodeArray[0]->ThreadInit();
	}
	operator ObjectT&()
	{
		return *m_pThreadLocalObject;
	}
	operator ObjectT*()
	{
		return m_pThreadLocalObject;
	}
	
	ObjectT* operator ->()
	{
		return m_pThreadLocalObject;
	}
	/*
	
	ObjectT* operator ()()
	{
		return m_pThreadLocalObject;
	}
	*/
	ObjectT& operator ()()
	{
		return *m_pThreadLocalObject;
	}
	
private:

};

template<typename ObjectT>
thread_local ObjectT* ThreadLocalStaticObject<ObjectT>::m_pThreadLocalObject = NULL;