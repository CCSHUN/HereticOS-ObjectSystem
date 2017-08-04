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
//2005.4.16 ����ָ������map
#include "yssmemory.hpp"
#include "SmartPoint.hpp"

#define FALSE 0
#define TRUE 1
#define LH 1
#define EH 0
#define RH -1


//���ý�������

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

	ValType		Val;	//ֵ
	int nBf;        //����ƽ�����ӣ�-1��ʾ����������ȱ���������1
	//0��ʾ��������������������
	//1��ʾ����������ȱ���������1

	NodePointT Parent;	//���ڵ�
	NodePointT LChild;
	NodePointT RChild;
};

/*
template<typename ValType>
typedef struct AVLNode
{
	ValType Val;
	int nBf;        //����ƽ�����ӣ�-1��ʾ����������ȱ���������1
	//0��ʾ��������������������
	//1��ʾ����������ȱ���������1
	struct AVLNode *LChild;
	struct AVLNode *RChild;
}AVLNode,*AVLTree;*/

typedef int BOOL;

template<typename ValType,class PointT =MemReMapPoint<ValType> >
class AVLTree : public PointT::MemMgrT
{
public:
	//BindPoint
	//m_AVLTree(m_AVLTree) �������ڴ湹���Լ�
	AVLTree():m_AVLTree(m_AVLTree),m_nSize(m_nSize)
	{
		//��ֹ�����ڴ�����µ����¹���
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


	//���°�ڴ�������
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
		//����*pATΪ���Ķ�����������ת��������֮��pATָ���µ��������
		//����ת����֮ǰ���������ĸ����
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
		//����*pATΪ���Ķ�����������ת��������֮��pATָ���µ��������
		//����ת����֮ǰ���������ĸ����
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
		//����ָ��pAT��ָ���Ϊ���Ķ���������ƽ����ת����
		//���㷨����ʱָ��pATָ���µĽ��
		NodePointT lc = pAT->LChild;    //lcָ��*pAT�������������
		NodePointT rd;// = NULL;
		if(lc)
			switch(lc->nBf)     //���*pAT����������ƽ��ȣ�������Ӧƽ�⴦��
		{
			case LH:    //�½�������*pAT�����ӵ��������ϣ�Ҫ��������ת����
				pAT->nBf = lc->nBf = EH;
				R_Rotate(pAT);
				break;
			case RH:    //�½�������*pAT�����ӵ��������ϣ�Ҫ��˫��ת����
				rd = lc->RChild;
				switch(rd->nBf) //�޸�*pAT�������ӵ�ƽ������
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
				L_Rotate(pAT->LChild);  //��*pAT������������ƽ�⴦��
				R_Rotate(pAT);      //��*pAT����ƽ�⴦��
				break;
			case EH:
				//����ת
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
		//����ָ��pAT��ָ���Ϊ���Ķ���������ƽ����ת����
		//���㷨����ʱָ��pATָ���µĽ��
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
				//����ת
				pAT->nBf=RH;
				rc->nBf=LH;
				L_Rotate(pAT);
			default:
				break;
		}
	}
	//�ǵݹ�ö�����
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
			if(pMin != NodePointT()) //����������
			{
				//�ҵ����������滻�ĵ�
				//(*pAT)->Val = pMin->Val;
				if(pMin != pPos->RChild)
				{
					//NodePointT Parent = GetParent((*pAT)->RChild, pMin->Val);
					NodePointT Parent=pMin->Parent;
					//���丸�ڵ���ڵ����µ�����
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
			else //������������
			{
				//�Ҳ���ɾ���Ľ��
				pMin = pPos;

				if(pPos->LChild)
				{
					pPos->LChild->Parent=pPos->Parent;
				}
				

				//�����Լ��Ǹ��ڵ����һ����Ȼ����LChild�滻���ڵ��е��Լ�
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

		//���һ���ڵ�
		*pPoint=NodePointT();

		return FALSE;
	}
	BOOL InsertATNode(NodePointPointT  pAT, NodePointT & pOutNode,  const ValType & c,int & taller)
	{
		//����ƽ��Ķ�����pAT�в����ں�c��ͬ�Ĺؼ��ֽ�㣬
		//�����һ����cΪ����Ԫ�ص��½�㣬������1�����򷵻�0
		//��������ʹ����������ʧȥƽ�⣬����ƽ����ת����
		//static int taller = FALSE;  //��ӳpAT���Ƿ񳤸�
		if(!(*pAT))
		{
			//�����½�㣬�����ߣ�tallerΪTRUE;
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
				//Ӧ����*(*pAT)���������н�������
				if(!InsertATNode(NodePointPointT(&(*pAT)->RChild),pOutNode, c,taller))   //δ����
				{
					return FALSE;
				}
				(*pAT)->RChild->Parent=(*pAT);

				if(taller)  //�Ѳ��뵽��(*pAT)��������������
				{
					switch((*pAT)->nBf) //���*(*pAT)��ƽ������
					{
					case LH:    //ԭ�����������������ߣ������������ȸ�
						(*pAT)->nBf = EH;
						taller = FALSE;
						break;
					case EH:    //ԭ�����������ȸߣ�������������������1
						(*pAT)->nBf = RH;
						taller = TRUE;
						break;
					case RH:    //ԭ�����������������ߣ�����ƽ�⴦��
						RightBalance((*pAT));
						taller = FALSE;
						break;
					}
				}
			}else if(c < (*pAT)->Val)
			{
				//Ӧ����*pAT���������н�������
				
				if(!InsertATNode(NodePointPointT(&(*pAT)->LChild),pOutNode, c,taller))   //δ����
				{
					return 0;
				}
				(*pAT)->LChild->Parent=(*pAT);

				if(taller)  //�Ѳ��뵽��(*pAT)��������������
				{
					switch((*pAT)->nBf) //���*(*pAT)��ƽ������
					{
					case LH:    //ԭ�����������������ߣ�����ƽ�⴦��
						LeftBalance((*pAT));
						taller = FALSE;
						break;
					case EH:    //ԭ�����������ȸߣ�������������������1
						(*pAT)->nBf = LH;
						taller = TRUE;
						break;
					case RH:    //ԭ�����������������ߣ������������ȸ�
						(*pAT)->nBf = EH;
						taller = FALSE;
						break;
					}
				}
			}
			else
			{
				//�����Ѵ��ں�c��ͬ�ؼ��ֵĽ�㣬������
				taller = FALSE;
				return FALSE;

			}
		}
		return TRUE;
	}

	//��ɾ������
	BOOL LDelRevise(NodePointT & pAT,int & lower)
	{
		switch(pAT->nBf)
		{
		case LH:    //ԭ�����������������ߣ����ڵȸ�
			pAT->nBf = EH;
			lower = TRUE;
			break;
		case EH:    //ԭ�����������ȸߣ�������������������1
			pAT->nBf = RH;
			lower = FALSE;
			break;
		case RH:    //ԭ�����������������ߣ�������ƽ�⴦��
			RightBalance(pAT);
			//�������ƽ�����ӵ���ǰ������߶Ȳ���
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

	//��ȡ���ڵ����ָ��pAT->Parent->Parent-?��
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
	//����ɾ������
	
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
	//��ɾ������
	BOOL RDelRevise(NodePointT & pAT,int & lower)
	{
		switch(pAT->nBf)
		{
		case LH:    //ԭ�����������������ߣ�������ƽ�⴦��
			LeftBalance(pAT);
			//�������ƽ�����ӵ���ǰ������߶Ȳ���
			if(pAT->nBf==RH)
			{
				lower=FALSE;
			}else
			{
				lower = TRUE;
			}

			break;
		case EH:    //ԭ�����������ȸߣ�������������������1
			pAT->nBf = LH;
			lower = FALSE;
			break;
		case RH:    //ԭ�����������������ߣ������������ȸ�
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
		//����ƽ��Ķ�����pAT�д��ں�c��ͬ�Ĺؼ��ֽ�㣬
		//��ɾ��һ����cΪ����Ԫ�صĽ�㣬������1�����򷵻�0
		//����ɾ����ʹ����������ʧȥƽ�⣬����ƽ����ת����
		//static int lower = FALSE;   //��ӳ(*pAT)���Ƿ�䰫
		if(!(*pAT))     //��Ϊ�ջ��㲻���ڷ���0
			return 0;
		if((*pAT)->Val < c)
		{
			//���ڵ������
			//Ӧ����*(*pAT)���������н�������
			return DeleteNode(NodePointPointT(&(*pAT)->RChild), c,lower);
			
		}
		else if(c < (*pAT)->Val)
		{
			//Ӧ����*(*pAT)���������н�������
			return DeleteNode(NodePointPointT(&(*pAT)->LChild), c,lower); //δɾ��

		}
		else /*if(c > (*pAT)->Val)*/
		{
			//��ȵ����
			NodePointPointT ppNode;

			if((*pAT)->LChild||(*pAT)->RChild)
			{
				//ֻҪ��һ���ڵ����ɾ������
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
					//������ڵ��е��Լ�
					//�������ƽ��
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
		//����ƽ��Ķ�����pAT�д��ں�c��ͬ�Ĺؼ��ֽ�㣬
		//��ɾ��һ����cΪ����Ԫ�صĽ�㣬������1�����򷵻�0
		//����ɾ����ʹ����������ʧȥƽ�⣬����ƽ����ת����
		//static int lower = FALSE;   //��ӳ(*pAT)���Ƿ�䰫
		if(!(*pAT))     //��Ϊ�ջ��㲻���ڷ���0
			return 0;
		if(c == (*pAT)->Val)
		{
			NodePointPointT ppNode;
			NodePointPointT Parent=NodePointPointT();
			NodePointT tmpParent;
			if((*pAT)->LChild||(*pAT)->RChild)
			{
				//ֻҪ��һ���ڵ����ɾ������
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
					//�ж�����
					BOOL br;
					if((*Parent)) 
					{
						br=(*Parent)->LChild==(*ppNode)? FALSE:TRUE;
					}

					(*pAT)->Val = (*ppNode)->Val;
					if(!DeleteNode(ppNode,(*ppNode)->Val,lower)) return FALSE;

					//����Ҫɾ���Ľڵ�ĸ����е���
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

					//����Ҫɾ���Ľڵ�ĸ����е���
					if((*Parent)&&lower)   //���䰫
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
						//������ڵ㲻�Ǳ��ڵ㣬����Ҫ�������ڵ㣮
						LDelRevise((*pAT),lower);
					}

				}
			}else
			{
				NodePointT pDel=(*pAT);
				if((*pAT)->Parent)
				{
					//������ڵ��е��Լ�
					if((*pAT)->Parent->LChild==(*pAT))
					{
						(*pAT)->Parent->LChild=(*pAT)->LChild;
					}else
					{
						(*pAT)->Parent->RChild=(*pAT)->LChild;
					}
					//�������߶���Ϣ
					YSS_DELETE(NodeType,pDel);
				}else
				{
					YSS_DELETE(NodeType,(*pAT));
				}
				
				m_nSize--;
				lower=TRUE;
			}
			
			//����Ҫɾ���Ľ��
			//���������滻�Ľ��
			/*NodePointT pMin = FindMin((*pAT)->RChild);
			if(pMin != NULL) //����������
			{
				//�ҵ����������滻�ĵ�
				//Ч�ʽϵ��£�����Ӧ�ÿ��ǽ���ָ�롣

				(*pAT)->Val = pMin->Val;
				if(pMin != (*pAT)->RChild)
				{
					//NodePointT Parent = GetParent((*pAT)->RChild, pMin->Val);
					NodePointT Parent=pMin->Parent;
					//���丸�ڵ���ڵ����µ�����
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
			else //������������
			{
				//�Ҳ���ɾ���Ľ��
				pMin = (*pAT);

				if((*pAT)->LChild)
				{
					(*pAT)->LChild->Parent=(*pAT)->Parent;
				}

				//�����Լ��Ǹ��ڵ����һ����Ȼ����LChild�滻���ڵ��е��Լ�
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
					//���һ���ڵ�
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
			//Ӧ����*(*pAT)���������н�������
			if(!DeleteNode(NodePointPointT(&(*pAT)->LChild), c,lower)) //δɾ��
				return 0;

			if(lower)   //���䰫
			{
				LDelRevise((*pAT),lower);
			}

		}
		else /*if(c > (*pAT)->Val)*/
		{
			//���ڵ������
			//Ӧ����*(*pAT)���������н�������
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
		//����AT����С��Ԫ��
		NodePointT m=AT;
		while(m && m->LChild)
		{
			m = m->LChild;
		}
		return m;
	}
	inline static NodePointT FindMax(NodePointT & AT)
	{
		//����AT����С��Ԫ��
		NodePointT m=AT;
		while(m && m->RChild)
		{
			m = m->RChild;
		}
		return m;
	}

	inline static NodePointPointT FindMinPP(NodePointT & AT)
	{
		//����AT����С��Ԫ��
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
		//����AT����С��Ԫ��
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
				//������������תһ��
				//������������min
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
									//ֱ����ת,z�ҵ�Ŀ��ڵ�
									m_Ptr=m_Ptr->Parent;
									break;
								}else
								{
									//������Ѱ��
									m_Ptr=m_Ptr->Parent;
								}
								
							}else
							{
								//���󣬼�������
								m_Ptr=m_Ptr->Parent;
							}
						}else
						{
							//��·���߷��ء�End
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
				//������������תһ��
				//������������Max
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
									//ֱ����ת,�ҵ�Ŀ��ڵ�
									m_Ptr=m_Ptr->Parent;
									break;
								}else
								{
									//������Ѱ��
									m_Ptr=m_Ptr->Parent;
								}
							}else
							{
								//���󣬼�������
								m_Ptr=m_Ptr->Parent;
							}
						}else
						{
							//��·���߷��ء�End
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
	//��ĩβ ��ЧԪ��
	iterator  end()
	{
		return iterator(NodePointT());
	}
	//Ϊĩβ����ЧԪ�� end��ǰһ��
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
