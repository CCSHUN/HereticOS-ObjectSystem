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
//最小保留尺寸 push时发生分配
#define VECTOR_MIN_MEMSIZE 8
//512k以上内存才考虑回收内存
#define VECTOR_MAX_MEMSIZE 1*1024*512

template<class ValType,class PointT =MemReMapPoint<ValType> >
class vector : public PointT::MemMgrT
{
	typedef vector<ValType,PointT> _Myt;
public:
	//防止m_ArrayHead初始化构造，重新初始化共享内存
	vector():m_ArrayHead(m_ArrayHead),m_nSize(m_nSize),m_nMaxSize(m_nMaxSize){
		if((!m_ArrayHead)
#ifdef RealPoint
			||(m_ArrayHead==NodePointPointT(0xcccccccc)
			||(m_ArrayHead==NodePointPointT(0)
			||(m_ArrayHead==NodePointPointT(0xffffffff)
#else
			||(m_ArrayHead==(NodePointPointT::PointIndexType)0xcccccccc)
			||(m_ArrayHead==(NodePointPointT::PointIndexType)0xffffffff)
#endif
			)
		{
			m_nSize=0;
			m_nMaxSize=0;
			m_ArrayHead=NodePointT();
		}
	};
	~vector(){};

	typedef  ValType NodeType;
#ifdef RealPoint
	typedef	 NodeType* NodePointT;
	typedef  NodeType** NodePointPointT;
#else
	//typedef typename RebindT1(PointT,NodeType) NodePointT;
	//typedef typename RebindT1(PointT,NodePointT) NodePointPointT;
	/*typedef typename PointT::RebindValType<NodeType>::other NodePointT;
	typedef typename PointT::RebindValType<NodePointT>::other NodePointPointT;*/

	typedef typename RebindValType<NodeType, typename PointT::MemMgrT>::other NodePointT;
	typedef typename RebindValType<NodePointT, typename PointT::MemMgrT>::other NodePointPointT;

#endif

	typedef  vector<ValType, PointT> _Myt;
	class iterator
	{
	public:
		NodePointT m_Ptr;
		_Myt * m_pVector;

		iterator(){};
		~iterator(){};
		iterator(NodePointT & _X,_Myt * pVector)
		{
			m_Ptr=_X;
			m_pVector=pVector;
		};
		typedef typename _Myt::iterator _Myt_iter;

		
		operator NodePointT &()
		{
			return m_Ptr;
		}

		operator ValType *()
		{
			return (ValType *)m_Ptr;
		}



		_Myt_iter& operator=(_Myt_iter & _X) 
		{
			m_Ptr=_X.m_Ptr;
			return *this;
		}

		_Myt_iter& operator=(NodePointT & _X) 
		{
			m_Ptr=_X;
			return *this;
		}

		ValType * operator->() 
		{
			return (ValType *)m_Ptr;
		}
		ValType & operator*() 
		{
			return *m_Ptr;
		}

		_Myt_iter& operator++()
		{	// preincrement
			m_Ptr++;
			NodePointT tmpMax=m_pVector->m_ArrayHead;
			tmpMax+=m_pVector->m_nSize-1;

			if((tmpMax<m_Ptr)||(m_pVector->m_nSize==0))
			{
				m_Ptr=NodePointT();
			}
			return (*this);
		}

		_Myt_iter operator++(int)
		{	// preincrement
			_Myt_iter tmp=*this;
			++*this;
			return tmp;

		}

		_Myt_iter& operator--()
		{	// preincrement
			m_Ptr--;
			NodePointT tmpMin=m_pVector->m_ArrayHead;

			if((m_Ptr<tmpMin)||(m_pVector->m_nSize==0))
			{
				m_Ptr=NodePointT();
			}

			return (*this);
		}


		_Myt_iter operator--(int)
		{	// preincrement
			_Myt_iter tmp=*this;
			--*this;
			
			return tmp;
		}

		_Myt_iter & operator-=(int nOffset)
		{	// preincrement
			//_Myt_iter tmp=*this;
			ValType * p=m_Ptr;
			p-=nOffset;
			if((m_Ptr<p)&&
				(p<(m_pVector->m_ArrayHead+m_pVector->m_nSize))
				)
			{
				m_Ptr=p;
			}else
			{
				m_Ptr=NodePointT();
			}
			return (*this);
		}

		_Myt_iter & operator+=(int nOffset)
		{	// preincrement
			//_Myt_iter tmp=*this;
			ValType * p=m_Ptr;
			p+=nOffset;
			if((m_Ptr<p)&&
				(p<(m_pVector->m_ArrayHead+m_pVector->m_nSize))
				)
			{
				m_Ptr=p;
			}else
			{
				m_Ptr=NodePointT();
			}
			return (*this);
		}


		bool operator==(_Myt_iter & _X)
		{
			if(m_Ptr==_X.m_Ptr)
			{
				return true;
			}
			return false;
		}

		bool operator!=(_Myt_iter & _X)
		{
			if(m_Ptr==_X.m_Ptr)
			{
				return false;
			}
			return true;
		}

		bool operator==(NodePointT & _X)
		{
			if(m_Ptr==_X)
			{
				return true;
			}
			return false;
		}
		bool IsVaild()
		{
			return m_Ptr.IsVaild();
		}
	protected:

	private:

	};

	ValType& operator[](const __int64 & nPos)
	{
		return ((ValType*)m_ArrayHead)[nPos];
	}


	iterator begin()
	{
		if(m_nSize)
		{
			return iterator(NodePointT(&(((ValType*)m_ArrayHead)[0])),this);
		}else
		{
			return iterator(NodePointT(),this);
		}
	}

	iterator end()
	{
		return iterator(NodePointT(),this);
	}
	iterator back()
	{
		if(m_nSize)
		{
			return iterator(NodePointT(&(((ValType*)m_ArrayHead)[m_nSize-1])),this);
		}else
		{
			return iterator(NodePointT(),this);
		}
		
	}

	void push_back(const NodeType & val)
	{
		if(m_nSize+1>=m_nMaxSize)
		{
			reserve(m_nSize*2);
		}
		Yss_Construct<NodeType>((NodeType*)m_ArrayHead+m_nSize);
		((NodeType*)m_ArrayHead)[m_nSize]=val;
		m_nSize++;
	}

	void pop_back()
	{
		Yss_Destroy<NodeType>((NodeType*)m_ArrayHead+m_nSize-1);
		m_nSize--;
		RetrieveMem();
	}

	//效率很低的
	iterator erase(iterator & _Where)
	{
		iterator itPos= _Where;itPos++;
		iterator itPrev= _Where;
		for(;itPos!=end();itPos++)
		{
			*itPrev=*itPos;
		}
		pop_back();
	}
	void clear()
	{
		for(int nPos=0;nPos<m_nSize;nPos++)
		{
			Yss_Destroy<NodeType>((NodeType*)m_ArrayHead+nPos);
		}
		m_nSize=0;
		YSS_FREE(m_ArrayHead);
		m_nMaxSize=0;
	}

	//重设
	void resize(__int64 nSize)
	{
		if(nSize>m_nMaxSize)
		{
			reserve(nSize*2);
			for(int nPos=m_nSize;nPos<nSize;nPos++)
			{
				Yss_Construct<NodeType>((NodeType*)m_ArrayHead+nPos);
			}
		}else if(nSize>m_nSize)
		{
			for(int nPos=m_nSize;nPos<nSize;nPos++)
			{
				Yss_Construct<NodeType>((NodeType*)m_ArrayHead+nPos);
			}
		}else
		{
			for(int nPos=nSize;nPos<m_nSize;nPos++)
			{
				Yss_Destroy<NodeType>((NodeType*)m_ArrayHead+nPos);
			}
		}

		m_nSize=nSize;
	}
	//保留分配的内存空间尺寸
	void reserve(__int64 nSize)
	{
		NodePointT pNew;
		if(nSize<VECTOR_MIN_MEMSIZE) 
		{
			nSize=VECTOR_MIN_MEMSIZE;
		}
		YSS_MALLOC(nSize*sizeof(NodeType),pNew);
		//构造拷贝对象
		for(int nPos=0;nPos<m_nSize;nPos++)
		{
			//构造新内存上的对象
			Yss_Construct<NodeType>((NodeType*)pNew+nPos);
			((NodeType*)pNew)[nPos]=((NodeType*)m_ArrayHead)[nPos];
			//析构老内存上的对象
			Yss_Destroy<NodeType>((NodeType*)pNew+nPos);
		}
		if(m_ArrayHead)
		{
			YSS_FREE(m_ArrayHead);
		}
		
		m_ArrayHead=pNew;
		m_nMaxSize=nSize;
	}
	__int64 size()
	{
		return m_nSize;
	}
protected:
	
private:
	NodePointT m_ArrayHead;
	__int64 m_nSize;
	__int64 m_nMaxSize;

	//回收内存
	void RetrieveMem()
	{
		if(
			((m_nSize*sizeof(NodeType)*8)<m_nMaxSize*sizeof(NodeType))&&
			((m_nMaxSize*sizeof(NodeType))>VECTOR_MAX_MEMSIZE)
			)
		{
			reserve(m_nSize*2);
		}
	}
};