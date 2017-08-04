///////////////////////////////////////////////////////////////////////////////////
//	Copyright 2017 shushen,ye
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//	http://www.apache.org/licenses/LICENSE-2.0
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
///////////////////////////////////////////////////////////////////////////////////

#pragma once
//2005.4.16 ����ָ��
#include "yssmemory.hpp"

template<typename PointInterfaceT,int nMemMgrType>
class DefMemMgr
{
public:
	DefMemMgr(){};
	~DefMemMgr(){};
	//ȫ��GCģʽʱ��ʼ��gc
	void * NewGc()
	{
		return NULL;
	}
	//ȫ��GCģʽʱ�ͷ�gc
	void DelGc(bool bRealClear)
	{
		return ;
	}


	bool NewVirtualMemory(IN OUT PointInterfaceT & pMem, __int64  nLen)
	{
		return g_pMemoryMgr[nMemMgrType]->NewVirtualMemory(pMem, nLen);
	}

	bool DelVirtualMemory(PointInterfaceT & pMem)
	{
		return g_pMemoryMgr[nMemMgrType]->DelVirtualMemory(pMem);
	}

	static void * MapGetAddr(IN PointInterfaceT * pMem)
	{
		return g_pMemoryMgr[nMemMgrType]->MapGetAddr(pMem);
	}

	//������ָ��ת��Ϊ����ָ��
	static bool GetVPFromRealAddr(IN OUT PointInterfaceT * pMem, IN void * pAddr)
	{
		return g_pMemoryMgr[nMemMgrType]->GetVPFromRealAddr(pMem, pAddr);
	}

protected:
	
private:
};




template <class ValType, typename MemMgr = DefMemMgr<PointInterfaceForMemoryMgr<IndexType>, MEMMGR_TYPE_DEF> >
class MemReMapPoint:public PointInterfaceForMemoryMgr<IndexType>
{
public:

	//���° �ڴ�������

	typedef ValType ValTypeT;
	typedef MemMgr MemMgrT;
	typedef MemReMapPoint<ValType,MemMgr> _Myt;
	
	//typedef PointInterfaceForMemoryMgr<IndexType>::PointIndexType PointIndexType;
	typedef ValType ValT;

	//���¶���ģ������
	//DefRebindT1(MemReMapPoint)

	MemReMapPoint(){m_nIndex=-1;};

	MemReMapPoint(const PointIndexType & PointVal){m_nIndex=PointVal;};
	MemReMapPoint(ValType * pData){ MemMgr::GetVPFromRealAddr(this, (void *)pData); };
	
	~MemReMapPoint(){};

	/*_Myt& operator=(ValType * _X) 
	{
		g_MemoryMgr.GetVPFromRealAddr(this,(void *)_X);
		return *this;
	}*/

	_Myt& operator=(const _Myt & _X) 
	{
		m_nIndex=_X.m_nIndex;
		return *this;
	}
	/*_Myt& operator=(_Myt  _X) 
	{
		m_nIndex=_X.m_nIndex;
		return *this;
	}*/
	bool operator==(const PointIndexType & PointVal)
	{
		if(m_nIndex==PointVal)
		{
			return true;
		}
		return false;
	}

	bool operator==(_Myt & _X)
	{
		if(m_nIndex==_X.m_nIndex)
		{
			return true;
		}
		return false;
	}

	operator ValT * ()
	{
		return address();
	}

	ValT * operator->() 
	{
		return address();
	}
	ValT & operator*() 
	{
		return *(ValT*)address();
	}

	//����ָ�������������vector�Ŀ���ָ�����������������֮���ָ�����

	_Myt& operator++()
	{	// preincrement
		m_nIndex+=sizeof(ValT);
		return (*this);
	}

	_Myt operator++(int)
	{	// preincrement
		_Myt tmp=*this;
		++*this;
		return tmp;

	}

	_Myt& operator--()
	{	// preincrement
		m_nIndex-=sizeof(ValT);

		return (*this);
	}


	_Myt operator--(int)
	{	// preincrement
		_Myt tmp=*this;
		--*this;

		return tmp;
	}

	_Myt & operator-=(int nOffset)
	{	
		m_nIndex-=(nOffset*sizeof(ValT));
		return (*this);
	}

	_Myt & operator+=(int nOffset)
	{	
		m_nIndex+=(nOffset*sizeof(ValT));
		return (*this);
	}
	
	//�Ƿ���Ч
	bool IsVaild()
	{
		if(m_nIndex==-1)
		{
			return false;
		}
		return true;
	}

	/*static bool NewMemory(IN OUT PointInterfaceForMemoryMgr<IndexType> & pMem,__int64  nLen)
	{
		return MemMgr::NewMemory( pMem,  nLen);
	}

	static bool DelMemory(PointInterfaceForMemoryMgr<IndexType> & pMem)
	{
		return MemMgr::DelMemory( pMem);
	}*/

protected:

private:

	//���ض��������ַ
	ValType * address()
	{
		if(m_nIndex==-1)
		{
			return NULL;
		}else
		{	
			return (ValType *) MemMgr::MapGetAddr(this);
		}
		
	}
};


template<class ValType>
bool operator<(const MemReMapPoint<ValType> & lift, const MemReMapPoint<ValType> & right) 
{
	return lift.m_nIndex<right.m_nIndex;
}


template<typename _OtherMemMgr, typename ValType>
struct RebindMemMgr
{
	typedef MemReMapPoint<ValType, _OtherMemMgr> other;
};

template<typename _OtherValType, typename MemMgr>
struct RebindValType
{
	typedef MemReMapPoint<_OtherValType, MemMgr> other;
};

