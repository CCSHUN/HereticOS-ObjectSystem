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
//2005.4.16 智能指针重制list
#include "tool.hpp"
#include "yssmemory.hpp"
#include "SmartPoint.hpp"

template<class ValType,class PointT>
struct ListNode 
{
	
	//typedef typename RebindT1(PointT,_Myt) NodePointT;

	typedef ListNode<ValType, PointT> _Myt;
	typedef typename RebindValType<_Myt, typename PointT::MemMgrT>::other NodePointT;
	typedef typename RebindValType<NodePointT, typename PointT::MemMgrT>::other NodePointPointT;


	NodePointT Next;
	NodePointT Prev;
	ValType Val;
};

template<class ValType,class PointT =MemReMapPoint<ValType> >
class list : public PointT::MemMgrT
{
public:
	

	typedef  ListNode<ValType,PointT> NodeType;
	typedef	 typename NodeType::NodePointT NodePointT;
	typedef  list<ValType, PointT> _Myt;
	

	class iterator
	{
	public:
		iterator(){};
		~iterator(){};
		iterator(NodePointT & _X)
		{
			m_Ptr=_X;
		};
		typedef typename _Myt::iterator _Myt_iter;

		NodePointT m_Ptr;
		//强制类型装换
		operator  NodePointT &()
		{
			return m_Ptr;
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
			return &m_Ptr->Val;
		}
		ValType & operator*() 
		{
			return m_Ptr->Val;
		}
		_Myt_iter& operator++()
		{	// preincrement
			if(m_Ptr.IsVaild())
			{
				m_Ptr=m_Ptr->Next;
			}
			
			return (*this);
		}

		_Myt_iter & operator++(int)
		{	// preincrement
			//_Myt_iter tmp=*this;
			if(m_Ptr.IsVaild())
			{
				m_Ptr=m_Ptr->Next;
			}

			return *this;
		}

		_Myt_iter& operator--()
		{	// preincrement
			if(m_Ptr.IsVaild())
			{
				m_Ptr=m_Ptr->Prev;
			}

			return (*this);
		}

		_Myt_iter & operator--(int)
		{	// preincrement
			//_Myt_iter tmp=*this;
			if(m_Ptr.IsVaild())
			{
				m_Ptr=m_Ptr->Prev;
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
	
	
	list():m_head(m_head){
		if(!m_head)
		{
			m_nSize=0;
			m_head=m_last=NodePointT();
		}
	};

	~list(){/*clear();*/};

	iterator  begin()
	{
		return iterator(m_head);
	}
	//最末尾 无效元素
	iterator  end()
	{
		return iterator(NodePointT());
	}
	//为末尾的有效元素 end的前一个
	iterator back()
	{
		return iterator(m_last);
	}
	bool insert_itNext(iterator & itPos,const ValType & Val)
	{
		if(itPos==end()) return false;
		iterator itNew;
		bool bret = NewVirtualMemory(itNew, sizeof(NodeType));
		//CallConstruct(itNew->(),ValType);
		Yss_Construct<ValType>(&(((NodePointT &)itNew)->Val));
		//(&((NodePointT &)itNew)->Val)->ValType::ValType();

		((NodePointT &)itNew)->Val=Val;
		((NodePointT &)itNew)->Next=((NodePointT &)itPos)->Next;
		((NodePointT &)itNew)->Prev=itPos;
		if(((NodePointT &)itPos)->Next.IsVaild())
		{
			//非尾部
			((NodePointT &)itPos)->Next->Prev=itNew;
		}else
		{
			//尾部
			m_last=itNew;
		}
		((NodePointT &)itPos)->Next=itNew;
		m_nSize++;
		return bret;
	}
	bool insert_itPrev(iterator & itPos,const ValType & Val)
	{
		if(itPos==end()) return false;
		iterator itNew;
		bool bret = NewVirtualMemory(itNew, sizeof(NodeType));
		Yss_Construct<ValType>(&(((NodePointT &)itNew)->Val));
		((NodePointT &)itNew)->Val=Val;
		((NodePointT &)itNew)->Next=itPos;
		((NodePointT &)itNew)->Prev=((NodePointT &)itPos)->Prev;
		if(((NodePointT &)itPos)->Prev.IsVaild())
		{
			((NodePointT &)itPos)->Prev->Next=itNew;
		}else
		{
			m_head=itNew;
		}
		((NodePointT &)itPos)->Prev=itNew;
		m_nSize++;

		return bret;
	}

	bool push_begin(const ValType& Val)
	{
		bool bret;
		if(m_head.IsVaild())
		{
			bret=insert_itPrev(iterator(m_head),Val);
			//if(bret) m_head=m_head->Prev;
		}else
		{
			iterator itNew;
			bret = NewVirtualMemory(itNew, sizeof(NodeType));
			Yss_Construct<ValType>(&(((NodePointT &)itNew)->Val));
			((NodePointT &)itNew)->Val=Val;
			((NodePointT &)itNew)->Next=NodePointT();
			((NodePointT &)itNew)->Prev=NodePointT();
			if(bret) m_last=m_head=itNew;
			m_nSize++;
		}
		return bret;
	}
	/*bool push_begin(ValType Val)
	{
		ValType tmp=Val;
		//return push_begin(tmp);
	}*/

	bool push_begin(iterator & it)
	{
		return push_begin(*it);
	}

	bool push_back(const ValType & Val)
	{
		bool bret;
		if(m_last.IsVaild())
		{
			bret=insert_itNext(iterator(m_last),Val);
			//if(bret) m_last=m_last->Next;
		}else
		{
			bret=push_begin(Val);
		}
		return bret;
	}

	/*bool push_back(ValType Val)
	{
		ValType & tmp=Val;
		//return push_back(tmp);
	}*/

	bool push_back(iterator & it)
	{
		return push_begin(*it);
	}

	bool pop_begin()
	{
		return erase(iterator(m_head));
	}
	
	bool pop_back()
	{
		return erase(iterator(m_last));
	}

	bool clear()
	{
		if(m_nSize==0) return false;
		iterator it=begin();
		for(;it!=end();)
		{
			erase(it);
		}
		return false;
	}

	bool erase(IN OUT iterator & it)
	{
		if (m_nSize==0&&it.IsVaild()==false) 
		{
			YSS_ASSERT(1);
			return false;
		}
		
		m_nSize--;
		iterator itBack=NodePointT();
		
		bool bVaildPrev=((NodePointT &)it)->Prev.IsVaild();
		bool bVaildNext=((NodePointT &)it)->Next.IsVaild();
		if(bVaildPrev&&bVaildNext)
		{
			//非首节点
			((NodePointT &)it)->Prev->Next=((NodePointT &)it)->Next;
			((NodePointT &)it)->Next->Prev=((NodePointT &)it)->Prev;

			itBack=((NodePointT &)it)->Prev;
		}else if(bVaildNext==false
			&&bVaildPrev==true)
		{
			//尾节点
			m_last=((NodePointT &)it)->Prev;
			m_last->Next=NodePointT();
			itBack=m_last;
		}else if(bVaildNext==true
			&&bVaildPrev==false)
		{
			//首节点,将m_head置为下一个
			m_head=((NodePointT &)it)->Next;
			m_head->Prev=NodePointT();
			itBack=m_head;
		}else if(bVaildNext==false
			&&bVaildPrev==false)
		{
			//首节点,将m_head置为下一个
			itBack=m_head=m_last=NodePointT();
			//最后一个节点
		}
		//CallDestroy(((ValType*)it),ValType);
		//it->Val
		Yss_Destroy<ValType>(&(((NodePointT &)it)->Val));
		bool bret = DelVirtualMemory((NodePointT &)it);
		it=itBack;
		return bret;
	}

	__int64 size()
	{
		return m_nSize;
	}

	bool empty()
	{
		if (m_nSize)
		{
			return false;
		}
		return true;
	}
	
protected:
	
	
	
private:
	//链表头
	NodePointT m_head;
	//链表尾
	NodePointT m_last;
	__int64 m_nSize;
};
