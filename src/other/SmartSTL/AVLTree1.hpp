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
//2005.4.16 智能指针重制map
#include "yssmemory.hpp"
#include "SmartPoint.hpp"

#define FALSE 0
#define TRUE 1
#define LH 1
#define EH 0
#define RH -1


//引用交换工具

/*
template<class ValType>
class ReferenceTool
{
public:
	typedef ReferenceTool<ValType> _Myt;
	ValType * m_Val;
	ValType * operator&() 
	{
		return &m_Val;
	}
	_Myt& operator=(const _Myt&  _X) 
	{
		m_Val=_X;
		return *this;
	}
	void Swap(const _Myt&  _X)
	{

	}
	ReferenceTool(){
		m_Val
	};
	~ReferenceTool(){};
protected:
	
private:
};*/


template<class ValType,class PointT>
struct AVLNode
{
	typedef AVLNode<ValType, PointT> _Myt;
#ifdef RealPoint
	typedef	 _Myt* NodePointT;
	typedef  _Myt** NodePointPointT;
#else
	typedef typename RebindValType<_Myt, typename PointT::MemMgrT>::other NodePointT;
	typedef typename RebindValType<NodePointT, typename PointT::MemMgrT>::other NodePointPointT;

#endif

	ValType		Val;	//值
	int nBf;        //结点的平衡因子，-1表示右子树的深度比左子树高1
	//0表示左子树与右子树深度相等
	//1表示左子树的深度比右子树高1

	NodePointT Parent;	//父节点
	NodePointT LChild;
	NodePointT RChild;
};

/*
template<typename ValType>
typedef struct AVLNode
{
	ValType Val;
	int nBf;        //结点的平衡因子，-1表示右子树的深度比左子树高1
	//0表示左子树与右子树深度相等
	//1表示左子树的深度比右子树高1
	struct AVLNode *LChild;
	struct AVLNode *RChild;
}AVLNode,*AVLTree;*/

typedef int BOOL;

template<typename ValType,class PointT =MemReMapPoint<ValType> >
class AVLTree : public PointT::MemMgrT
{
public:
	//BindPoint
	//m_AVLTree(m_AVLTree) 从自身内存构造自己
	AVLTree():m_AVLTree(m_AVLTree),m_nSize(m_nSize)
	{
		//防止共享内存情况下的重新构造
		/*
		
		if((!m_AVLTree)
#ifdef RealPoint
			||(m_AVLTree==NodePointPointT(0xcccccccc))
			||(m_AVLTree==NodePointPointT(0))
			||(m_AVLTree==NodePointPointT(0xffffffff))
#else
			||(m_AVLTree==(NodePointPointT::PointIndexType)0xcccccccc)
			||(m_AVLTree==(NodePointPointT::PointIndexType)0)
			||(m_AVLTree==(NodePointPointT::PointIndexType)0xffffffff)
#endif
			)
		*/
		{
			//NodePointPointT tmp;
			m_nSize=0;
			YSS_NEW(NodePointT,m_AVLTree);
			//m_AVLTree(()(NodePointT*)tmp);
		}
	};
	~AVLTree(){};


	//重新邦定内存管理对象
	template<class _OtherMemMgr> 
	struct RebindMemMgr 
	{	
		typedef AVLTree<ValType,_OtherMemMgr> other;
	};

	typedef  AVLNode<ValType,PointT> NodeType;

	typedef	 typename NodeType::NodePointT NodePointT;
	typedef	 typename NodeType::NodePointPointT NodePointPointT;

	typedef  AVLTree<ValType, PointT> _Myt;

	
private:
	NodePointPointT m_AVLTree;
	__int64 m_nSize;
	void R_Rotate(NodePointT & pAT)
	{
		//对以*pAT为根的二叉树作右旋转处理，处理之后pAT指向新的树根结点
		//即旋转处理之前的左子树的根结点
		NodePointT lc = pAT->LChild;
		pAT->LChild = lc->RChild;

		if(lc->RChild)
		{
			lc->RChild->Parent=pAT;
		}
		

		lc->RChild = pAT;

		lc->Parent=pAT->Parent;
		pAT->Parent=lc;

		
		pAT = lc;
		
	}

	void L_Rotate(NodePointT & pAT)
	{
		//对以*pAT为根的二叉树作左旋转处理，处理之后pAT指向新的树根结点
		//即旋转处理之前的右子树的根结点
		NodePointT rc = pAT->RChild;
		pAT->RChild = rc->LChild;
		if(rc->LChild)
		{
			rc->LChild->Parent=pAT;
		}
		

		rc->LChild = pAT;
		rc->Parent=pAT->Parent;
		pAT->Parent=rc;

		
		pAT = rc;
	}

	void LeftBalance(NodePointT & pAT)
	{
		//对以指针pAT所指结点为根的二叉树作左平衡旋转处理，
		//本算法结束时指针pAT指向新的结点
		NodePointT lc = pAT->LChild;    //lc指向*pAT的左子树根结点
		NodePointT rd;// = NULL;
		if(lc)
			switch(lc->nBf)     //检查*pAT的左子树的平衡度，并作相应平衡处理
		{
			case LH:    //新结点插入在*pAT的左孩子的左子树上，要作单右旋转处理
				pAT->nBf = lc->nBf = EH;
				R_Rotate(pAT);
				break;
			case RH:    //新结点插入在*pAT的左孩子的右子树上，要作双旋转处理
				rd = lc->RChild;
				switch(rd->nBf) //修改*pAT及其左孩子的平衡因子
				{
				case LH:
					pAT->nBf = RH;
					lc->nBf = EH;
					break;
				case EH:
					pAT->nBf = lc->nBf = EH;
					break;
				case RH:
					pAT->nBf = EH;
					lc->nBf = LH;
					break;
				default:;
				}
				rd->nBf = EH;
				L_Rotate(pAT->LChild);  //对*pAT的左子树作左平衡处理
				R_Rotate(pAT);      //对*pAT作右平衡处理
				break;
			case EH:
				//右旋转
				pAT->nBf=LH;
				lc->nBf=RH;
				R_Rotate(pAT);
				break;
			default:
				break;
		}
	}
	void RightBalance(NodePointT & pAT)
	{
		//对以指针pAT所指结点为根的二叉树作右平衡旋转处理，
		//本算法结束时指针pAT指向新的结点
		NodePointT rc = pAT->RChild;
		NodePointT rd ;
		if(rc)
			switch(rc->nBf)
		{
			case RH:
				pAT->nBf = rc->nBf = EH;
				L_Rotate(pAT);
				break;
			case LH:
				rd = rc->LChild;
				switch(rd->nBf)
				{
				case LH:
					pAT->nBf = EH;
					rc->nBf = RH;
					break;
				case EH:
					pAT->nBf = rc->nBf = EH;
					break;
				case RH:
					pAT->nBf = LH;
					rc->nBf = EH;
					break;
				}
				rd->nBf = EH;
				R_Rotate(pAT->RChild);
				L_Rotate(pAT);
				break;
			case EH:
				//左旋转
				pAT->nBf=RH;
				rc->nBf=LH;
				L_Rotate(pAT);
			default:
				break;
		}
	}
	//非递归枚举清除
	BOOL clear( NodePointPointT pPoint)
	{
		NodePointT pPos=*pPoint;
		int nBf=EH;
		do
		{
			if(!pPos)
			{
				break;
			}
			
			NodePointT pMin = FindMin(pPos->RChild);
			if(pMin != NodePointT()) //存在右子树
			{
				//找到可以用作替换的点
				//(*pAT)->Val = pMin->Val;
				if(pMin != pPos->RChild)
				{
					//NodePointT Parent = GetParent((*pAT)->RChild, pMin->Val);
					NodePointT Parent=pMin->Parent;
					//将其父节点左节点重新调整。
					Parent->LChild = pMin->RChild;
					if(Parent->LChild)
					{
						Parent->LChild->Parent=Parent;
					}
				}
				else
				{
					pPos->RChild = pMin->RChild;
					if(pMin->RChild)
					{
						pMin->RChild->Parent=pPos;
					}
				}
				
				YSS_DELETE(NodeType,pMin);
				m_nSize--;
			}
			else //不存在右子树
			{
				//找不到删除的结点
				pMin = pPos;

				if(pPos->LChild)
				{
					pPos->LChild->Parent=pPos->Parent;
				}
				

				//计算自己是父节点的哪一个，然后用LChild替换父节点中的自己
				if(pMin->Parent)
				{
					if(pMin->Parent->LChild==pMin)
					{
						pMin->Parent->LChild=pMin->LChild;
					}else
					{
						pMin->Parent->RChild=pMin->LChild;
					}
				}
				
				pPos=pMin->LChild;

				YSS_DELETE(NodeType,pMin);
				m_nSize--;
			}

		}while(true);

		//最后一个节点
		*pPoint=NodePointT();

		return FALSE;
	}
	BOOL InsertATNode(NodePointPointT  pAT, NodePointT & pOutNode,  const ValType & c,int & taller)
	{
		//若在平衡的二叉树pAT中不存在和c相同的关键字结点，
		//则插入一个以c为数据元素的新结点，并返回1，否则返回0
		//若因插入而使二叉排序树失去平衡，则作平衡旋转处理
		//static int taller = FALSE;  //反映pAT树是否长高
		if(!(*pAT))
		{
			//插入新结点，树长高，taller为TRUE;
			//pAT = (AVLTree)malloc(sizeof(AVLNode));

			/*g_MemoryMgr.NewMemory(pAT,sizeof(NodeType));
			Yss_Construct<NodeType>((NodeType *)pAT);*/

			NodePointT pNewNode;
			YSS_NEW(NodeType,pNewNode);
			*pAT=pNewNode;
			pOutNode=pNewNode;

			(*pAT)->Val = c;
			(*pAT)->LChild = (*pAT)->RChild = NodePointT();
			(*pAT)->nBf = EH;
			taller = TRUE;
			m_nSize++;
		}
		else
		{
			if((*pAT)->Val < c)
			{
				//应该在*(*pAT)的右子树中进行搜索
				if(!InsertATNode(NodePointPointT(&(*pAT)->RChild),pOutNode, c,taller))   //未插入
				{
					return FALSE;
				}
				(*pAT)->RChild->Parent=(*pAT);

				if(taller)  //已插入到树(*pAT)并且右子树长高
				{
					switch((*pAT)->nBf) //检查*(*pAT)的平衡因子
					{
					case LH:    //原本左子树比右子树高，现左右子树等高
						(*pAT)->nBf = EH;
						taller = FALSE;
						break;
					case EH:    //原本左右子树等高，现右子树比左子树高1
						(*pAT)->nBf = RH;
						taller = TRUE;
						break;
					case RH:    //原本右子树比左子树高，作右平衡处理
						RightBalance((*pAT));
						taller = FALSE;
						break;
					}
				}
			}else if(c < (*pAT)->Val)
			{
				//应该在*pAT的左子树中进行搜索
				
				if(!InsertATNode(NodePointPointT(&(*pAT)->LChild),pOutNode, c,taller))   //未插入
				{
					return 0;
				}
				(*pAT)->LChild->Parent=(*pAT);

				if(taller)  //已插入到树(*pAT)并且左子树长高
				{
					switch((*pAT)->nBf) //检查*(*pAT)的平衡因子
					{
					case LH:    //原本左子树比右子树高，作左平衡处理
						LeftBalance((*pAT));
						taller = FALSE;
						break;
					case EH:    //原本左右子树等高，现左子树比右子树高1
						(*pAT)->nBf = LH;
						taller = TRUE;
						break;
					case RH:    //原本右子树比左子树高，现左右子树等高
						(*pAT)->nBf = EH;
						taller = FALSE;
						break;
					}
				}
			}
			else
			{
				//树中已存在和c相同关键字的结点，不插入
				taller = FALSE;
				return FALSE;

			}
		}
		return TRUE;
	}

	//左删除调整
	BOOL LDelRevise(NodePointT & pAT,int & lower)
	{
		switch(pAT->nBf)
		{
		case LH:    //原本左子树比右子树高，现在等高
			pAT->nBf = EH;
			lower = TRUE;
			break;
		case EH:    //原本左右子树等高，现右子树比左子树高1
			pAT->nBf = RH;
			lower = FALSE;
			break;
		case RH:    //原本右子树比左子树高，则作右平衡处理
			RightBalance(pAT);
			//如果左右平衡因子调整前后倒置则高度不变
			if(pAT->nBf==LH)
			{
				lower=FALSE;
			}else
			{
				lower = TRUE;
			}
			
			break;
		}
		return TRUE;
	}

	//获取父节点归属指针pAT->Parent->Parent-?　
	void GetParentAscription(IN OUT NodePointPointT & RetNodePP,NodePointT & pAT)
	{
		if(pAT->Parent)
		{
			if(pAT->Parent->Parent)
			{
				RetNodePP=pAT->Parent->Parent->LChild==pAT->Parent? &(pAT->Parent->Parent->LChild):&(pAT->Parent->Parent->RChild);
			}else
			{
				RetNodePP=m_AVLTree;
			}
		}else
		{
			*RetNodePP=NodePointT();
		}
	}
	//反响删除调整
	
	void ReversedDelRevise(NodePointT & pAT,int & lower,BOOL br)
	{
		if(pAT)
		{
			
			NodePointT tmpParent;
			NodePointPointT Parent=&tmpParent;

			GetParentAscription(Parent,pAT);
			BOOL brt;
			

			if(br)
			{
				RDelRevise(pAT,lower);
			}else
			{
				LDelRevise(pAT,lower);
			}

			if(lower)
			{
				if((*Parent)) 
				{
					brt=(*Parent)->LChild==pAT? FALSE:TRUE;
					return ReversedDelRevise((*Parent),lower,brt);
				}
			}

		}else
		{
			return ;
		}
		return;
	}
	//右删除调整
	BOOL RDelRevise(NodePointT & pAT,int & lower)
	{
		switch(pAT->nBf)
		{
		case LH:    //原本左子树比右子树高，则作左平衡处理
			LeftBalance(pAT);
			//如果左右平衡因子调整前后倒置则高度不变
			if(pAT->nBf==RH)
			{
				lower=FALSE;
			}else
			{
				lower = TRUE;
			}

			break;
		case EH:    //原本左右子树等高，现左子树比右子树高1
			pAT->nBf = LH;
			lower = FALSE;
			break;
		case RH:    //原本右子树比左子树高，现左左子树等高
			pAT->nBf = EH;
			lower = TRUE;
			break;
		}
		return TRUE;
	}
	BOOL CheckHead()
	{
		if(m_AVLTree)
		{
			if (*m_AVLTree)
			{
				if((*m_AVLTree)->Parent)
				{
					return FALSE;
				}else
				{
					return TRUE;
				}
			}
		}
		return FALSE;
	}
	BOOL CheckSize()
	{
		iterator it=begin();
		int s=0;
		for(s=0;it!=end();it++)
		{
			s++;
		}
		if(s==m_nSize)
		{
			return TRUE;
		}
		return FALSE;
	}
	BOOL CheckBf(NodePointT pAT,NodePointT & BadNode,int & high)
	{
		int RHigh=0,LHigh=0;
		if(pAT->LChild)
		{
			if(CheckBf( pAT->LChild,BadNode,LHigh)==FALSE) return FALSE;

			LHigh+=1;
		}
		if(pAT->RChild)
		{
			if(CheckBf( pAT->RChild,BadNode,RHigh)==FALSE) return FALSE;

			RHigh+=1;
		}
		BadNode=pAT;
		if(RHigh>LHigh)
		{
			if(pAT->nBf!=RH) 
			{
				return FALSE;
			}
		}else if(RHigh<LHigh)
		{
			if(pAT->nBf!=LH) 
			{
				return FALSE;
			}
		}else
		{
			if(pAT->nBf!=EH) 
			{
				return FALSE;
			}
		}
		high=RHigh>LHigh?RHigh:LHigh;
		return TRUE;
	}

	BOOL DeleteNode(NodePointPointT pAT, const ValType & c,int & lower)
	{
		//若在平衡的二叉树pAT中存在和c相同的关键字结点，
		//则删除一个以c为数据元素的结点，并返回1，否则返回0
		//若因删除而使二叉排序树失去平衡，则作平衡旋转处理
		//static int lower = FALSE;   //反映(*pAT)树是否变矮
		if(!(*pAT))     //树为空或结点不存在返回0
			return 0;
		if((*pAT)->Val < c)
		{
			//大于的情况。
			//应该在*(*pAT)的右子树中进行搜索
			return DeleteNode(NodePointPointT(&(*pAT)->RChild), c,lower);
			
		}
		else if(c < (*pAT)->Val)
		{
			//应该在*(*pAT)的左子树中进行搜索
			return DeleteNode(NodePointPointT(&(*pAT)->LChild), c,lower); //未删除

		}
		else /*if(c > (*pAT)->Val)*/
		{
			//相等的情况
			NodePointPointT ppNode;

			if((*pAT)->LChild||(*pAT)->RChild)
			{
				//只要有一个节点就需删除调整
				if((*pAT)->nBf==RH)
				{
					ppNode=FindMinPP((*pAT)->RChild);

					(*pAT)->Val = (*ppNode)->Val;
					return DeleteNode(ppNode,(*ppNode)->Val,lower);


				}else
				{
					ppNode=FindMaxPP((*pAT)->LChild);


					(*pAT)->Val = (*ppNode)->Val;
					return DeleteNode(ppNode,(*ppNode)->Val,lower);

				}
			}else
			{
				NodePointT pDel=(*pAT);
				if((*pAT)->Parent)
				{
					//清除父节点中的自己
					//反向调整平衡
					NodePointT tmpParent;
					NodePointPointT Parent=&tmpParent;

					GetParentAscription(Parent,(*pAT));
					lower=TRUE;
					if((*pAT)->Parent->LChild==(*pAT))
					{
						(*pAT)->Parent->LChild=(*pAT)->LChild;
						ReversedDelRevise((*Parent),lower,FALSE);
					}else
					{
						(*pAT)->Parent->RChild=(*pAT)->LChild;
						ReversedDelRevise((*Parent),lower,TRUE);
					}

					YSS_DELETE(NodeType,pDel);
				}else
				{
					YSS_DELETE(NodeType,(*pAT));
				}

				m_nSize--;

			}
			
		}


		return TRUE;
	}

	BOOL DeleteNode1(NodePointPointT pAT, const ValType & c,int & lower)
	{
		//若在平衡的二叉树pAT中存在和c相同的关键字结点，
		//则删除一个以c为数据元素的结点，并返回1，否则返回0
		//若因删除而使二叉排序树失去平衡，则作平衡旋转处理
		//static int lower = FALSE;   //反映(*pAT)树是否变矮
		if(!(*pAT))     //树为空或结点不存在返回0
			return 0;
		if(c == (*pAT)->Val)
		{
			NodePointPointT ppNode;
			NodePointPointT Parent=NodePointPointT();
			NodePointT tmpParent;
			if((*pAT)->LChild||(*pAT)->RChild)
			{
				//只要有一个节点就需删除调整
				if((*pAT)->nBf==RH)
				{
					ppNode=FindMinPP((*pAT)->RChild);
					if((*ppNode)->Parent)
					{
						if((*ppNode)->Parent->Parent)
						{
							Parent=(*ppNode)->Parent->Parent->LChild==(*ppNode)->Parent? &((*ppNode)->Parent->Parent->LChild):&((*ppNode)->Parent->Parent->RChild);
						}else
						{
							tmpParent=(*ppNode)->Parent;
							Parent=&tmpParent;
						}
						
					}
					//Parent=(*ppNode)->Parent;
					//判断左右
					BOOL br;
					if((*Parent)) 
					{
						br=(*Parent)->LChild==(*ppNode)? FALSE:TRUE;
					}

					(*pAT)->Val = (*ppNode)->Val;
					if(!DeleteNode(ppNode,(*ppNode)->Val,lower)) return FALSE;

					//对需要删除的节点的父进行调整
					if((*Parent)&&lower)
					{
						if(br)
						{
							RDelRevise((*Parent),lower);
						}else
						{
							LDelRevise((*Parent),lower);
						}
					}

					if(lower&&((*Parent)!=(*pAT)))
					{

						RDelRevise((*pAT),lower);
					}
						
				
				}else
				{
					ppNode=FindMaxPP((*pAT)->LChild);
					if((*ppNode)->Parent)
					{
						if((*ppNode)->Parent->Parent)
						{
							Parent=(*ppNode)->Parent->Parent->LChild==(*ppNode)->Parent? &((*ppNode)->Parent->Parent->LChild):&((*ppNode)->Parent->Parent->RChild);
						}else
						{
							tmpParent=(*ppNode)->Parent;
							Parent=&tmpParent;
						}

					}
					//Parent=(*ppNode)->Parent;
					BOOL br;
					if((*Parent)) br=(*Parent)->LChild==(*ppNode)? FALSE:TRUE;

					(*pAT)->Val = (*ppNode)->Val;
					if(!DeleteNode(ppNode,(*ppNode)->Val,lower)) return FALSE;

					//对需要删除的节点的父进行调整
					if((*Parent)&&lower)   //树变矮
					{
						if(br)
						{
							RDelRevise((*Parent),lower);
						}else
						{
							LDelRevise((*Parent),lower);
						}
					}
					if(lower&&((*Parent)!=(*pAT)))
					{
						//如果父节点不是本节点，则需要调整本节点．
						LDelRevise((*pAT),lower);
					}

				}
			}else
			{
				NodePointT pDel=(*pAT);
				if((*pAT)->Parent)
				{
					//清除父节点中的自己
					if((*pAT)->Parent->LChild==(*pAT))
					{
						(*pAT)->Parent->LChild=(*pAT)->LChild;
					}else
					{
						(*pAT)->Parent->RChild=(*pAT)->LChild;
					}
					//调整父高度信息
					YSS_DELETE(NodeType,pDel);
				}else
				{
					YSS_DELETE(NodeType,(*pAT));
				}
				
				m_nSize--;
				lower=TRUE;
			}
			
			//存在要删除的结点
			//查找用作替换的结点
			/*NodePointT pMin = FindMin((*pAT)->RChild);
			if(pMin != NULL) //存在右子树
			{
				//找到可以用作替换的点
				//效率较低下，还是应该考虑交换指针。

				(*pAT)->Val = pMin->Val;
				if(pMin != (*pAT)->RChild)
				{
					//NodePointT Parent = GetParent((*pAT)->RChild, pMin->Val);
					NodePointT Parent=pMin->Parent;
					//将其父节点左节点重新调整。
					Parent->LChild = pMin->RChild;
					if(Parent->LChild)
					{
						Parent->LChild->Parent=Parent;
					}

				}
				else
				{
					(*pAT)->RChild = pMin->RChild;
					if(pMin->RChild)
					{
						pMin->RChild->Parent=(*pAT);
					}
				}

				/ *Yss_Destroy<ValType>(&pMin->Val);
				g_MemoryMgr.DelMemory(pMin);* /
				
				YSS_DELETE(NodeType,pMin);
				m_nSize--;
			}
			else //不存在右子树
			{
				//找不到删除的结点
				pMin = (*pAT);

				if((*pAT)->LChild)
				{
					(*pAT)->LChild->Parent=(*pAT)->Parent;
				}

				//计算自己是父节点的哪一个，然后用LChild替换父节点中的自己
				if(pMin->Parent)
				{
					if(pMin->Parent->LChild==pMin)
					{
						pMin->Parent->LChild=pMin->LChild;
					}else
					{
						pMin->Parent->RChild=pMin->LChild;
					}
				}else
				{
					//最后一个节点
					*pAT=NodePointT();
				}
				//(*pAT) = (*pAT)->LChild;
				
				/ *Yss_Destroy<NodeType>((NodeType*)pMin);
				g_MemoryMgr.DelMemory(pMin);* /
				
				YSS_DELETE(NodeType,pMin);
				m_nSize--;
			}
			lower = TRUE;*/
		}
		else if(c < (*pAT)->Val)
		{
			//应该在*(*pAT)的左子树中进行搜索
			if(!DeleteNode(NodePointPointT(&(*pAT)->LChild), c,lower)) //未删除
				return 0;

			if(lower)   //树变矮
			{
				LDelRevise((*pAT),lower);
			}

		}
		else /*if(c > (*pAT)->Val)*/
		{
			//大于的情况。
			//应该在*(*pAT)的右子树中进行搜索
			if(!DeleteNode(NodePointPointT(&(*pAT)->RChild), c,lower))
				return 0;
			if(lower)
			{
				RDelRevise((*pAT),lower);
			}
		}


		return TRUE;
	}
	inline static NodePointT FindMin(NodePointT & AT)
	{
		//查找AT中最小的元素
		NodePointT m=AT;
		while(m && m->LChild)
		{
			m = m->LChild;
		}
		return m;
	}
	inline static NodePointT FindMax(NodePointT & AT)
	{
		//查找AT中最小的元素
		NodePointT m=AT;
		while(m && m->RChild)
		{
			m = m->RChild;
		}
		return m;
	}

	inline static NodePointPointT FindMinPP(NodePointT & AT)
	{
		//查找AT中最小的元素
		NodePointT m=AT;
		NodePointPointT Ret=NodePointPointT(&AT);
		while(m && m->LChild)
		{
			Ret=NodePointPointT(&m->LChild);
			m = m->LChild;
		}
		return Ret;
	}
	inline static NodePointPointT FindMaxPP(NodePointT & AT)
	{
		//查找AT中最小的元素
		NodePointT m=AT;
		NodePointPointT Ret=NodePointPointT(&AT);
		while(m && m->RChild)
		{
			Ret=NodePointPointT(&m->RChild);
			m = m->RChild;
		}
		return Ret;
	}

	/*inline static NodePointT GetParent(NodePointT & AT, ValType & c)
	{
		if(!AT || AT->Val == c)
			return NodePointT();
		if((AT->LChild && AT->LChild->Val == c) ||
			(AT->RChild && AT->RChild->Val == c))
			return AT;
		else if((AT->LChild && c < AT->LChild->Val))
			return GetParent(AT->LChild, c);
		else
			return GetParent(AT->RChild, c);
	}*/
	inline static NodePointT find(NodePointPointT  AT, const ValType  &  c)
	{
		NodePointT pPos=*AT;
		do
		{
			if(!pPos)
			{
				return pPos;
			}else if(pPos->Val<c)
			{
				pPos=pPos->RChild;
			}else if(c<pPos->Val)
			{
				pPos=pPos->LChild;
			}else
			{
				return pPos;
			}
		}while(TRUE);
	}

	/*inline static NodePointPointT FindPP(NodePointPointT  AT, const ValType  &  c)
	{
		NodePointPointT pPos=AT;
		do
		{
			if(!pPos)
			{
				return pPos;
			}else if((*pPos)->Val==c)
			{
				return pPos;
			}else if((*pPos)->Val>c)
			{
				(*pPos)=(*pPos)->LChild;
			}else
			{
				(*pPos)=(*pPos)->RChild;
			}
		}while(TRUE);
	}*/

public:

	class iterator
	{
	public:
//#define IsVaild(Ptr) (Ptr!=NULL)
		iterator(){};
		~iterator(){};
		iterator(NodePointT & _X)
		{
			m_Ptr=_X;
		};
		typedef typename _Myt::iterator _Myt_iter;

		NodePointT m_Ptr;
		operator NodePointT &()
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
		{	
			add();
			return *this;
		}

		_Myt_iter& operator++(int)
		{	// preincrement
			add();
			return *this;
		}

		_Myt_iter& operator--()
		{	// preincrement
			Sub();
			return *this;
		}

		_Myt_iter& operator--(int)
		{	// preincrement
			Sub();
			return *this;
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
		/*bool IsVaild()
		{
			return m_Ptr.IsVaild();
		}*/
	protected:

	private:
		NodePointT & add()
		{
			if(m_Ptr!=NodePointT())
			{
				//右无则向上右转一次
				//右有则向右找min
				//m_Ptr=m_Ptr->Next;
				if(m_Ptr->RChild)
				{
					m_Ptr=_Myt::FindMin(m_Ptr->RChild);
				}else
				{
					do
					{
						if(m_Ptr->Parent)
						{
							if(m_Ptr->Parent->LChild)
							{

								
								if(m_Ptr->Parent->LChild==m_Ptr)
								{
									//直接右转,z找到目标节点
									m_Ptr=m_Ptr->Parent;
									break;
								}else
								{
									//继续上寻．
									m_Ptr=m_Ptr->Parent;
								}
								
							}else
							{
								//无左，继续上走
								m_Ptr=m_Ptr->Parent;
							}
						}else
						{
							//无路可走返回　End
							m_Ptr=NodePointT();
							break;
						}
					}while(true);

				}
				return m_Ptr;
			}
			return m_Ptr;
		}

		NodePointT & Sub()
		{
			if(m_Ptr!=NodePointT())
			{
				//左无则向左右转一次
				//左有则向左找Max
				//m_Ptr=m_Ptr->Next;
				if(m_Ptr->LChild)
				{
					m_Ptr=_Myt::FindMax(m_Ptr->LChild);
				}else
				{
					do
					{
						if(m_Ptr->Parent)
						{
							if(m_Ptr->Parent->RChild)
							{

								
								if(m_Ptr->Parent->RChild==m_Ptr)
								{
									//直接左转,找到目标节点
									m_Ptr=m_Ptr->Parent;
									break;
								}else
								{
									//继续上寻．
									m_Ptr=m_Ptr->Parent;
								}
							}else
							{
								//无左，继续上走
								m_Ptr=m_Ptr->Parent;
							}
						}else
						{
							//无路可走返回　End
							m_Ptr=NodePointT();
							break;
						}
					}while(true);
				}
				return m_Ptr;
			}
			return m_Ptr;
		}

	};

	iterator  begin()
	{
		return iterator(FindMin(*m_AVLTree));
	}
	//最末尾 无效元素
	iterator  end()
	{
		return iterator(NodePointT());
	}
	//为末尾的有效元素 end的前一个
	iterator back()
	{
		return iterator(FindMax(*m_AVLTree));
	}

	BOOL Insert(const ValType & c,iterator & RetNode)
	{
		int tall=FALSE;
		NodePointT pOutNode;

		BOOL bRet= InsertATNode(m_AVLTree,pOutNode,c,tall);
#ifdef _DBG
		if(CheckBf()==FALSE)
		{
			YSS_ASSERT(TRUE);
		}
		if (CheckSize()==FALSE)
		{
			YSS_ASSERT(TRUE);
		}
		if(CheckHead()==FALSE)
		{
			YSS_ASSERT(TRUE);
		}
#endif
		if(bRet) RetNode=pOutNode;
		return bRet;
	}

	BOOL Insert(const ValType & c)
	{
		int tall=FALSE;
		NodePointT pOutNode;

		BOOL bRet= InsertATNode(m_AVLTree,pOutNode,c,tall);
#ifdef _DBG
		if(CheckBf()==FALSE)
		{
			YSS_ASSERT(TRUE);
		}
		if (CheckSize()==FALSE)
		{
			YSS_ASSERT(TRUE);
		}
		if(CheckHead()==FALSE)
		{
			YSS_ASSERT(TRUE);
		}
#endif
		return bRet;
	}
	
	BOOL Delete(const ValType & c)
	{
		int lower=FALSE;
		BOOL bRet= DeleteNode(m_AVLTree, c,lower);
#ifdef _DBG
		if(CheckBf()==FALSE)
		{
			YSS_ASSERT(TRUE);
		}
		if (CheckSize()==FALSE)
		{
			YSS_ASSERT(TRUE);
		}
		if(CheckHead()==FALSE)
		{
			YSS_ASSERT(TRUE);
		}
#endif
		return bRet;
	}

	BOOL erase(const ValType & c)
	{
		return Delete(c);
	}

	BOOL erase(iterator & itPos)
	{
		return Delete(*itPos);
	}

	iterator find(const ValType & c)
	{
		return iterator(find(m_AVLTree,c));
	}
	
	BOOL clear()
	{
		//NodePointPointT pPos=FindMin(*m_AVLTree);
		return clear(m_AVLTree);

	}

	BOOL empty()
	{
		if(size()==0)
		{
			return TRUE;
		}
	}
	__int64 size()
	{
		return m_nSize;
	}

	BOOL CheckBf()
	{
		NodePointT BadNode;
		int high=0;
		if(*m_AVLTree)
		{
			return CheckBf(*m_AVLTree,BadNode,high);
		}
		return TRUE;
	}
	
protected:
	
private:
};
