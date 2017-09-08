#pragma once
//三层容器结构
// 全局静态容器-----用于设计期组件隔离
//		|-------ThreadLocal------用于线程间组件隔离，这一层可以选择没有，但是一些没有多线程安全的组件在多线程情况下会出现故障，线程隔离的组件在跨线程传递时，资源可能变得不可用，比如string的内存池
//					|-------动态运行时容器，建议线程内隔离组件使用，多容器使用时需要SwitchContainer.
//
#include <thread>
#include <mutex>
#define CONTAINER_NAME_DEFAULT 1
//#define CONTAINER_MODE_THREADLOCAL  true
#define CONTAINER_MODE_THREADLOCAL  false
class CSystemContainerObjectInterface
{
public:
	CSystemContainerObjectInterface() {
	};
	~CSystemContainerObjectInterface() {
	};
	virtual void ReleaseInstance(bool bDestruction = false) {}
private:

};


//#define SYSTEM_CONTAINER_MAX_COUNT 128*1024
template<int nContainerName= CONTAINER_NAME_DEFAULT,bool bThreadLocal= CONTAINER_MODE_THREADLOCAL>
class CSystemContainerMgr
{
public:
	unsigned int m_nCurrentContainer;
	unsigned int m_nLastCurrentContainer;
	void ** m_pCurrentObjectArray;

	/*
	volatile thread_local static unsigned int m_nThreadLocalCurrentContainer;
	volatile thread_local static unsigned int m_nThreadLocalLastCurrentContainer;
	volatile thread_local static void ** m_pThreadLocalCurrentObjectArray;
	*/

	unsigned int m_nLastNewContainer;
	unsigned int m_nLastNewType;
	typedef CSystemContainerMgr<nContainerName, bThreadLocal> _Mty;
	typedef std::vector<void*> ContainerObjectMapT;
	typedef std::unordered_map<unsigned int, ContainerObjectMapT> ContainerMapT;
	typedef std::unordered_map<unsigned int, CSystemContainerObjectInterface*> TypeMapT;
	std::mutex m_ThreadMutex;
	ContainerMapT m_ContainerMap;
	TypeMapT m_TypeMap;
	bool m_bRelease;

	static _Mty& GetInstance()
	{
		if (bThreadLocal)
		{
			thread_local static _Mty _self;
			return _self;
		}
		else
		{
			static _Mty _self;
			return _self;
		}

	}

	
	~CSystemContainerMgr() {};
	void init()
	{
		return;
	}
	unsigned int CreateContainer()
	{
		//m_ContainerMap[m_nLastNewContainer] = ContainerObjectMapT();
		//std::unique_lock<std::mutex> lk(m_ThreadMutex);
		m_ContainerMap.emplace(m_nLastNewContainer, (NULL, m_nLastNewType + 1));
		return m_nLastNewContainer++;
	}
	
	void DestroyContainer(unsigned int nObjectType, bool bDestruction = false)
	{
		//std::unique_lock<std::mutex> lk(m_ThreadMutex);
		for (int nContainer = 0; nContainer != m_nLastNewContainer; nContainer++)
		{
			if (SwitchContainer(nContainer))
			{
				TypeMapT::iterator itType = m_TypeMap.find(nObjectType);
				if (itType != m_TypeMap.end())
				{
					itType->second->ReleaseInstance(bDestruction);
					m_TypeMap.erase(itType);
				}
			}
		}
	}
	void DestroyContainer(bool bDestruction = false)
	{
		//std::unique_lock<std::mutex> lk(m_ThreadMutex);
		if (!m_bRelease)
		{
			for (int nContainer = 0; nContainer != m_nLastNewContainer; nContainer++)
			{
				if (SwitchContainer(nContainer))
				{
					for (int nObjectType = 0; nObjectType != m_nLastNewType; nObjectType++)
					{
						TypeMapT::iterator itType = m_TypeMap.find(nObjectType);
						if (itType != m_TypeMap.end())
						{
							itType->second->ReleaseInstance(bDestruction);
							//m_TypeMap.erase(itType);
						}
					}
				}
			}
		}

		m_bRelease = true;
	}
	template<typename ObjectT>
	ObjectT * * GetObjectRef(unsigned int nObjectType)
	{
		return  (ObjectT **)&m_pCurrentObjectArray[nObjectType];

	}
	bool SwitchContainer(unsigned int nContainer)
	{
		ContainerMapT::iterator itContainer = m_ContainerMap.find(nContainer);

		if (itContainer->second.size() < (m_nLastNewType + 1))
		{
			itContainer->second.resize(m_nLastNewType + 1);
		}
		if (itContainer->second.size())
		{

			m_pCurrentObjectArray = &itContainer->second[0];
			m_nLastCurrentContainer = m_nCurrentContainer;
			m_nCurrentContainer = nContainer;

			return true;
		}
		return false;
	}
	unsigned int CreateType(CSystemContainerObjectInterface * pInterface)
	{
		//std::unique_lock<std::mutex> lk(m_ThreadMutex);
		m_TypeMap[m_nLastNewType] = pInterface;
		SwitchContainer(m_nCurrentContainer);
		return m_nLastNewType++;
	}
	unsigned int GetCurrentContainer()
	{
		return  m_nCurrentContainer;
	}
	void PrintInfo()
	{

		printf("CurrentContainerInfo(this=%p %d %d TypeCount=%d pObjectArray=%p)\n============================================",
			this,
			m_nCurrentContainer,
			m_nLastCurrentContainer,
			m_nLastNewType,
			m_pCurrentObjectArray);
		for (int i = 0; i < m_nLastNewType; i++)
		{
			if(i%6==0) printf("\n");
			printf("%d=%p ", i, m_pCurrentObjectArray[i]);
		}
		printf("\n============================================\n\n");

	}
	CSystemContainerMgr() {
		m_nCurrentContainer = m_nLastNewContainer = m_nLastNewType = 0;
		m_bRelease = false;
		SwitchContainer(CreateContainer());
	};
private:

};

/*
template<int nName,bool bThreadLocal>
volatile thread_local unsigned int CSystemContainer< nName,bThreadLocal>::m_nThreadLocalCurrentContainer = 0;
template<int nName, bool bThreadLocal>
volatile thread_local unsigned int CSystemContainer< nName,bThreadLocal>::m_nThreadLocalLastCurrentContainer = 0;
template<int nName, bool bThreadLocal>
volatile thread_local void ** CSystemContainer< nName,bThreadLocal>::m_pThreadLocalCurrentObjectArray = NULL;
*/

#define CONTAINER_MAGIC 0xffffffff;

template<typename ObjectNameT, typename ContainerT>
class CSystemContainerObject : public   CSystemContainerObjectInterface
{
public:
	unsigned int m_nTypeIndex;
	CSystemContainerObject() {
		//m_nTypeIndex = 0xffffffff;

		m_nTypeIndex = ContainerT::SystemContainerMgrT::GetInstance().CreateType(this);
		printf("Container-%d-%d-%d CreateType %d %p \n", ContainerT::nContainerName,::GetCurrentThreadId(),
			ContainerT::SystemContainerMgrT::GetInstance().GetCurrentContainer(),
			m_nTypeIndex, this/*, typeid(ObjectNameT).name()*/);
	};
	typedef CSystemContainerObject<ObjectNameT, ContainerT> _Myt;
	~CSystemContainerObject() {};
	static ObjectNameT & GetInstance()
	{
		if (ContainerT::bThreadLocal)
		{
			thread_local static _Myt _self;
			//static _Myt _self;

			ObjectNameT * * pObject = ContainerT::SystemContainerMgrT::GetInstance().GetObjectRef<ObjectNameT>(_self.m_nTypeIndex);
			if (*pObject == NULL)
			{
				*pObject = NewObjectFormMemPool<ContainerT::SystemMemPoolT, ObjectNameT>();
				//_self.m_nTypeIndex = CSystemContainer<nName>::GetInstance().CreateType(&_self);
				//printf("aaaaa\n");
				
				printf("Container-%d-%d-%d CreateObject ThreadLocal %d %p \n", ContainerT::nContainerName, ::GetCurrentThreadId(),
					ContainerT::SystemContainerMgrT::GetInstance().GetCurrentContainer(),
					_self.m_nTypeIndex, *pObject);
					
					
				
			}

			if (*pObject == NULL)
			{
				//*pObject = (ObjectNameT*)1;
			}
			return (ObjectNameT &)**pObject;
		}
		else
		{
			static _Myt _self;
			ObjectNameT * * pObject = Container_DefaultT::SystemContainerMgrT::GetInstance().GetObjectRef<ObjectNameT>(_self.m_nTypeIndex);
			if (*pObject == NULL)
			{
				ObjectNameT * pObjectNew = NewObjectFormMemPool<ContainerT::SystemMemPoolT, ObjectNameT>();
				pObject = ContainerT::SystemContainerMgrT::GetInstance().GetObjectRef<ObjectNameT>(_self.m_nTypeIndex);
				*pObject = pObjectNew;
				//_self.m_nTypeIndex = CSystemContainer<nName>::GetInstance().CreateType(&_self);
				//typeid(ObjectNameT).name()
				
				printf("Container-%d-%d-%d CreateObject %d addr=%p pObj=%p \n", ContainerT::nContainerName, ::GetCurrentThreadId(),
					ContainerT::SystemContainerMgrT::GetInstance().GetCurrentContainer(),
					_self.m_nTypeIndex, pObject, *pObject);
					
			}

			if (*pObject == NULL)
			{
				//*pObject = (ObjectNameT*)1;
			}
			return (ObjectNameT &)**pObject;
		}
		
		
	}
	void ReleaseInstance(bool bDestruction)
	{
		if (bDestruction)
		{
			DeleteObjectFormMemPool<ContainerT::SystemMemPoolT, ObjectNameT, true>(&GetInstance());
		}
		else
		{
			DeleteObjectFormMemPool<ContainerT::SystemMemPoolT, ObjectNameT, false>(&GetInstance());
		}
	}

private:

};
//template<typename ObjectNameT, int nName, typename MemPoolT>
//CSystemContainerObject<ObjectNameT，nName, MemPoolT>::m_nTypeIndex = CONTAINER_MAGIC;

template<typename ObjectNameT, typename ContainerT>
class CSystemContainerObjectBase
{
public:
	CSystemContainerObjectBase() {};
	~CSystemContainerObjectBase() {};
	static ObjectNameT & GetInstance()
	{

		return CSystemContainerObject<ObjectNameT, ContainerT>::GetInstance();
	}

private:

};

template<typename _SystemMemPoolT, typename _MemPoolT, typename _MemPoolGCT, typename _MemPoolGCTmpT, int _nContainerName = CONTAINER_NAME_DEFAULT, bool _bThreadLocal = CONTAINER_MODE_THREADLOCAL>
class SystemContainer
{
public:
	//typedef  _nContainerName nContainerName;
	//typedef _bThreadLocal bThreadLocal;
	typedef SystemContainer<_SystemMemPoolT,  _MemPoolT,  _MemPoolGCT,  _MemPoolGCTmpT,  _nContainerName> _Myt;
	enum Config
	{
		nContainerName = _nContainerName,
		bThreadLocal = _bThreadLocal,
	};
	typedef CSystemContainerMgr<nContainerName, bThreadLocal> SystemContainerMgrT;
	typedef _MemPoolT MemPoolT;
	typedef _SystemMemPoolT SystemMemPoolT;
	typedef _MemPoolGCT MemPoolGCT;
	typedef _MemPoolGCTmpT MemPoolGCTmpT;
	SystemContainer() {};
	~SystemContainer() {};

private:

};

