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

#include "StdAfx.h"
#include "MakeCodeObj.h"
#include "Tokenizer.h"



BOOL CMakeCodeObj::BindObjExpressionMgr(CObjExpression * mgr)
{
	m_ObjExpressionMgr=mgr;
	return TRUE;
}
BOOL CMakeCodeObj::FindRuleContext(CObjExpression::ParseRuleMapType::iterator & itRuleContext,string & RuleName,unsigned int nDepth)
{

	return m_ObjExpressionMgr->FindRuleContext(itRuleContext,RuleName,nDepth);

}
BOOL CMakeCodeObj::GetSearchCodeToCodeObjTree(IN string & pFilePath,IN OUT CGenerateCodeTree &CodeTree)
{
	return CodeTree.GetSearchCodeToCodeObjTree(pFilePath);
}
BOOL CMakeCodeObj::GetCommandTypeAndLen(
										IN ExpressionContext & Context,
										IN unsigned int nCommand,
										OUT string & Command,
										OUT unsigned int & nCommandLen,
										IN unsigned int nDepth
										)
{
	nCommandLen=0;
	vector<string> RoutingExpressionArray;
	if(GetRoutingExpressionArray(Context,nCommand,RoutingExpressionArray,nCommandLen,nDepth))
	{
		if(nCommandLen)
		{
			Command="·���ͱ�";
			return TRUE;
		}

	}

	if(
		(string("MAKE_ADD")==Context.Array[nCommand].WordVal)
		&&(string("<")==Context.Array[nCommand+1].WordVal)
		&&(string(">")==Context.Array[nCommand+3].WordVal)
		)
	{
		nCommandLen=4;
		Command=string("MAKE_ADD");
		return TRUE;
	}

	if(
		(string("MAKE_TO")==Context.Array[nCommand].WordVal)
		&&(string("<")==Context.Array[nCommand+1].WordVal)
		&&(string(",")==Context.Array[nCommand+3].WordVal)
		&&(string(">")==Context.Array[nCommand+5].WordVal)
		)
	{
		nCommandLen=6;
		Command=string("MAKE_TO");
		return TRUE;
	}

	if(
		(string("MAKE_MAKECODE")==Context.Array[nCommand].WordVal)
		&&(string("<")==Context.Array[nCommand+1].WordVal)
		&&(string(",")==Context.Array[nCommand+3].WordVal)
		&&(string(">")==Context.Array[nCommand+5].WordVal)
		)
	{
		nCommandLen=6;
		Command=string("N");
		return TRUE;
	}
	if(
		(string("MAKE_ONE")==Context.Array[nCommand].WordVal)
		&&(string("<")==Context.Array[nCommand+1].WordVal)
		&&(string(",")==Context.Array[nCommand+3].WordVal)
		&&(string(">")==Context.Array[nCommand+5].WordVal)
		)
	{
		nCommandLen=6;
		Command=string("MAKE_ONE");
		return TRUE;
	}

	

	if(
		(string("MAKE_BIND_ROUTING")==Context.Array[nCommand].WordVal)
		&&(string("<")==Context.Array[nCommand+1].WordVal)
		&&(string(",")==Context.Array[nCommand+3].WordVal)
		&&(string(">")==Context.Array[nCommand+5].WordVal)
		)
	{
		nCommandLen=6;
		Command=string("MAKE_BIND_ROUTING");
		return TRUE;
	}

	if(
		(string("DEBUGOUT")==Context.Array[nCommand].WordVal)
		&&(string("<")==Context.Array[nCommand+1].WordVal)
		&&(string(">")==Context.Array[nCommand+3].WordVal)
		)
	{
		nCommandLen=4;
		Command=string("DEBUGOUT");
		return TRUE;
	}

	if(
		(string("IF")==Context.Array[nCommand].WordVal)
		&&(string("<")==Context.Array[nCommand+1].WordVal)
		&&(string(">")==Context.Array[nCommand+3].WordVal)
		)
	{
		nCommandLen=4;
		Command=string("IF");
		return TRUE;
	}

	if(
		(string("MAKE_N")==Context.Array[nCommand].WordVal)
		&&(string("<")==Context.Array[nCommand+1].WordVal)
		&&(string(",")==Context.Array[nCommand+3].WordVal)
		&&(string(",")==Context.Array[nCommand+5].WordVal)
		&&(string(",")==Context.Array[nCommand+7].WordVal)
		&&(string(">")==Context.Array[nCommand+9].WordVal)
		)
	{
		nCommandLen=10;
		Command=string("MAKE_N");
		return TRUE;
	}

	return m_ObjExpressionMgr->GetCommandTypeAndLen(Context,nCommand,Command,nCommandLen,nDepth);

}

BOOL CMakeCodeObj::GetCodeValByName(IN list<_tagCodeObjTree>::iterator & RootCodeObj,IN list<_tagCodeObjTree>::iterator & BeginCodeObj,IN string & CodeName,OUT list<_tagCodeObjTree>::iterator & RetCodeObj)
{
	RetCodeObj=BeginCodeObj;
	for(;RetCodeObj!=RootCodeObj->ChildObj.end();RetCodeObj++)
	{
		if(CodeName==RetCodeObj->ObjName)
		{
			return TRUE;
		}
	}
	return FALSE;
}


BOOL CMakeCodeObj::GetCodeValByVal(IN list<_tagCodeObjTree>::iterator & RootCodeObj,IN list<_tagCodeObjTree>::iterator & BeginCodeObj,IN string & CodeVal,OUT list<_tagCodeObjTree>::iterator & RetCodeObj)
{
	RetCodeObj=BeginCodeObj;
	for(;RetCodeObj!=RootCodeObj->ChildObj.end();RetCodeObj++)
	{
		if(CodeVal==RetCodeObj->ObjVal)
		{
			CodeVal=RetCodeObj->ObjVal;
			return TRUE;
		}
	}
	return FALSE;
}

/*
typedef struct _tagWordSet
{
string  WordType;
string	WordVal;
}WordSet,*PWordSet;*/
BOOL CMakeCodeObj::NextRoutingNode(
								   IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
								   IN OUT CodeRoutingContext & RoutingContext,
								   OUT BOOL & bFind,
								   OUT list<_tagCodeObjTree>::iterator & RetCodeObj,//ƥ�䵽�Ľڵ�
								   IN unsigned int nDepth	
								   )
{
	list<CodeRoutingNode>::iterator itHead,itCur,itTmp,itChild;//���ڵ㵱ǰ�ڵ�
	list<_tagCodeObjTree>::iterator RetCodeObjTmp;
	bFind=FALSE;
	itHead=RoutingContext.CodeRouting.begin();
	itCur=RoutingContext.CodeRouting.end();
	itCur--;
	/*
	itPar=itCur;

	if(itCur!=RoutingContext.CodeRouting.begin())
	{
	itPar--;
	}*/


	list<_tagCodeObjTree>::iterator CurRootCodeObj=itCur->LastChildCodeNode;
	list<_tagCodeObjTree>::iterator		LastChildCodeNode=CurRootCodeObj;

	itCur->LastChildCodeNode++;

	for(;;)
	{
		//�ӽڵ����������˷
		if(itCur->LastChildCodeNode==itCur->CurCodeObjTree->ChildObj.end())
		{
			//�ӽڵ��Ѿ�������ϣ���ʼ��һ�����ڵ�
			if(itCur==RoutingContext.CodeRouting.begin()) return TRUE;

			itCur--;
			itCur->LastChildCodeNode++;
			continue;
		}

		itTmp=RoutingContext.CodeRouting.end();
		itTmp--;
		if(itCur==itTmp)
		{
			//���Ľڵ����Ƿ���Ҷֵ
			if((itCur->ExpressionName==itCur->CurCodeObjTree->ObjVal))
			{
				//���һ���ڵ���Ҷ�ڵ㡣

				//û�и��ڵ㣬���޷��ٻ�˷��
				if(RoutingContext.CodeRouting.size()<=1) return FALSE;

				itTmp=itCur;
				itTmp--;
				if(itCur->ExpressionName==itTmp->CurCodeObjTree->ObjVal)
				{
					itCur->CurCodeObjTree=itTmp->CurCodeObjTree;
					itCur->LastChildCodeNode=itTmp->CurCodeObjTree->ChildObj.end();
					bFind=TRUE;
					break;
				}
			}
		}

		if(GetCodeValByName(itCur->CurCodeObjTree,itCur->LastChildCodeNode,itCur->ExpressionName,RetCodeObjTmp))
		{

		}else if(GetCodeValByVal(itCur->CurCodeObjTree,itCur->LastChildCodeNode,itCur->ExpressionName,RetCodeObjTmp))
		{

		}else
		{
			//û���ҵ�����
			//break;
			//goto faile;

			//���ϲ�ڵ�û�ҵ���˵���Ѿ���������
			if(itCur==RoutingContext.CodeRouting.begin()) return TRUE;
			itCur--;
			itCur->LastChildCodeNode++;
			continue;
		}
		itTmp=itCur;
		itTmp++;
		itCur->LastChildCodeNode=RetCodeObjTmp;

		if(itTmp!=RoutingContext.CodeRouting.end())
		{
			//���ǵײ�ڵ�
			//������ӽڵ�����Ҫ���ӽڵ�
			itTmp->CurCodeObjTree=itCur->LastChildCodeNode;
			itTmp->LastChildCodeNode=itTmp->CurCodeObjTree->ChildObj.begin();
			itCur++;
		}
		else
		{
			//�Ѿ��ҵ���ײ�ڵ�
			bFind=TRUE;
			RetCodeObj=RetCodeObjTmp;
			return TRUE;
		}

	}

	return FALSE;

}

BOOL CMakeCodeObj::GetRoutingExpressionArrayByExpression(string & RoutingExpression,OUT vector<string> &RoutingExpressionArray)
{
	CTokenizer Tokenizer(RoutingExpression);//=new CTokenizer(string(RoutingExpression));
	vector<WordSet> Array;
	BOOL bNextSearchWord=TRUE;
	unsigned int nCommandLen=0;
	if(Tokenizer.GetWordArray(Array))
	{
		if(Array.size()==0) return FALSE;

		for(unsigned int i=0;i<Array.size();i++)
		{
			if(bNextSearchWord)
			{
				if(Array[i].WordType!=string("����")) return FALSE;
				bNextSearchWord=FALSE;
				if(
					(Array[i].WordVal==string("O"))&&
					(0==i)
					)
				{
				}
				else
				{
					RoutingExpressionArray.push_back(string(Array[i].WordVal));

				}

			}else
			{
				if((Array[i].WordVal==string(".")))
				{
					bNextSearchWord=TRUE;
				}else
				{
					return FALSE;
				}

			}
		}
		if(RoutingExpressionArray.size())
		{
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

BOOL CMakeCodeObj::GetRoutingExpressionArray(IN ExpressionContext & Context,IN unsigned int nCommand, OUT vector<string> &RoutingExpression,OUT unsigned int & nCommandLen,IN unsigned int nDepth)
{
	BOOL bNextSearchWord=TRUE;
	nCommandLen=0;
	/*
	if((Context.Array[nCommand].WordVal==string(".")))
	{
	if(Context.Array[nCommand+1].WordType!=string("����"))
	{
	RoutingExpression.push_back(string(Context.Array[nCommand+1].WordVal));
	nCommandLen=1;
	return TRUE;
	}
	return FALSE;
	}*/

	for(unsigned int i=nCommand;i<=Context.nNumWord;i++)
	{
		if(bNextSearchWord)
		{
			if(Context.Array[i].WordType!=string("����")) return FALSE;
			bNextSearchWord=FALSE;
			if(
				(Context.Array[i].WordVal==string("O"))&&
				(nCommand==i)
				)
			{
			}
			else
			{
				RoutingExpression.push_back(string(Context.Array[i].WordVal));
			}

		}else
		{
			if((Context.Array[i].WordVal==string(COMMANDEND)))
			{
				if(i-nCommand<=1) return FALSE;

				nCommandLen=i-nCommand;
				return TRUE;
			}
			else if((Context.Array[i].WordVal==string(".")))
			{
				bNextSearchWord=TRUE;
			}else if((Context.Array[i].WordType==string("������")))
			{
				nCommandLen=i-nCommand;
				if(nCommandLen>1)
				{
					return TRUE;
				}
				return FALSE;
			}
			else
			{
				return FALSE;
			}

		}
	}
	return FALSE;
}
BOOL CMakeCodeObj::GetRoutingExpressionArray(IN string & RoutingExpressionName,OUT vector<string> &RoutingExpression,IN unsigned int nDepth)
{
	CObjExpression::ParseRuleMapType::iterator itRootRule;
	RoutingExpression.clear();
	BOOL bRst=FALSE;
	unsigned int nCommandLen=0;
	if(FindRuleContext(itRootRule,RoutingExpressionName,nDepth))
	{
		bRst= GetRoutingExpressionArray(itRootRule->second,0,RoutingExpression,nCommandLen,nDepth);
		if(bRst==FALSE)
		{
			DebugPrint(nDepth,"GetRoutingExpressionArray ���ʽ %s ���ʽ����ȷ \r\n ",RoutingExpressionName.c_str());
		}
	}

	return bRst;
}

string GetRoutingPath(IN vector<string> &RoutingExpression)
{
	vector<string>::iterator itPos=RoutingExpression.begin();
	string Ret;
	for(;itPos!=RoutingExpression.end();itPos++)
	{
		Ret+=*itPos;
		Ret+=".";
	}
	if(Ret.length())
	{
		Ret.erase(--Ret.end());
	}
	return Ret;
}

BOOL CMakeCodeObj::BindRoutingName(string & BindToName,string & BindName)
{
	BOOL bFind=FALSE;
	RoutingExpressionInfo Info;
	if((BindToName.length()==0)||
		(BindName.length()==0)
		)
	{
		return FALSE;
	}
	for(unsigned int i=0;i<m_RoutingMapTabArray.size();i++)
	{
		if(m_RoutingMapTabArray[i].RoutingExpression.RoutingExpression==BindToName)
		{
			vector<RoutingExpressionInfo>::iterator itFind=m_RoutingMapTabArray[i].RoutingExpressionBindList.begin();
			for (;itFind!=m_RoutingMapTabArray[i].RoutingExpressionBindList.end();itFind++)
			{
				if(itFind->RoutingExpression==BindName)
				{
					return FALSE;
				}
			}
			//û�ҵ�˵�����Բ���

			Info.RoutingExpression=BindName;
			if(GetRoutingExpressionArrayByExpression(Info.RoutingExpression,Info.RoutingExpressionNodeArray))
			{
				m_RoutingMapTabArray[i].RoutingExpressionBindList.push_back(Info);
				return TRUE;
			}
			return FALSE;
		}
	}
	//û�ҵ�˵��û�и���Ҫȫ������
	RoutingMapTab tab;
	tab.RoutingExpression.RoutingExpression=BindToName;
	if(GetRoutingExpressionArrayByExpression(tab.RoutingExpression.RoutingExpression,tab.RoutingExpression.RoutingExpressionNodeArray))
	{
		Info.RoutingExpression=BindName;
		if(GetRoutingExpressionArrayByExpression(Info.RoutingExpression,Info.RoutingExpressionNodeArray))
		{
			tab.RoutingExpressionBindList.push_back(Info);
			m_RoutingMapTabArray.push_back(tab);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CMakeCodeObj::FindAAndReplaseRouting(
					 IN vector<string> & Org,
					 IN vector<string> & Finder,
					 IN vector<string> & Replace,
					 OUT vector<string> & Out,
					 OUT string & Out1
					 )
{
	unsigned int nBegin=0,nOrgSize=Org.size(),nFinderSize=Finder.size();
	if(nOrgSize<nFinderSize) return FALSE;

	BOOL bFind=FALSE;
	for(unsigned int i=0;i<(nOrgSize-nFinderSize+1);)
	{
		if(Org[i]==Finder[0])
		{
			nBegin=i;
			//bFind=FALSE;
			unsigned int j=1;
			for(;j<Finder.size();j++)
			{
				if(Org[i+j]!=Finder[j])
				{
					//bFind=FALSE;
					break;
				}
			}
			if(j==Finder.size())
			{
				bFind=TRUE;
				Out.insert(Out.end(),Replace.begin(),Replace.end());
				i+=Finder.size();
				continue;
			}
			
		}else
		{
			Out.push_back(Org[i]);
		}

		i++;
	}
	if(bFind)
	{
		Out1=GetRoutingPath(Out);
		return TRUE;
	}
	return FALSE;
}

BOOL CMakeCodeObj::GetAllRoutingNameFromRoutingBindTab(string & RoutingExpression,vector<vector<string> > & AllBindNameArray)
{
	vector<string> RoutingExpressionArray;
	

	if(AutoGetRoutingExpressionArray(RoutingExpression,RoutingExpressionArray))
	{
		return GetAllRoutingNameFromRoutingBindTab(RoutingExpressionArray,AllBindNameArray);
	}

	return FALSE;
}


BOOL CMakeCodeObj::GetAllRoutingNameFromRoutingBindTab(vector<string> &RoutingExpression,vector<vector<string> > & AllBindNameArray)
{
	unsigned int nMapTabArraySize=m_RoutingMapTabArray.size();
	unsigned int nCurRoutingExpressionSize=0;
	vector<string> OutTmp;
	string szOutTmp;
	vector<vector<string> > AllBindNameArrayTmp;
	for(unsigned int i=0;i<nMapTabArraySize;i++)
	{
		//if(m_RoutingMapTabArray[i].RoutingExpression.RoutingExpressionNodeArray[s]
		for(unsigned int j=0 ;j<m_RoutingMapTabArray[i].RoutingExpressionBindList.size();j++)
		{
			szOutTmp.clear();
			OutTmp.clear();
			if(FindAAndReplaseRouting(RoutingExpression,
					 m_RoutingMapTabArray[i].RoutingExpression.RoutingExpressionNodeArray,
					 m_RoutingMapTabArray[i].RoutingExpressionBindList[j].RoutingExpressionNodeArray,
					 OutTmp,
					 szOutTmp))
			{
				AllBindNameArrayTmp.clear();
				if(GetAllRoutingNameFromRoutingBindTab(OutTmp,AllBindNameArrayTmp))
				{
					//�ݹ����µõ�·��
					AllBindNameArray.insert(AllBindNameArray.end(),
						AllBindNameArrayTmp.begin(),AllBindNameArrayTmp.end());
				}else
				{
					AllBindNameArray.push_back(OutTmp);
				}
			}else
			{
				break;
			}
		}
	}
	if(AllBindNameArray.size())
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CMakeCodeObj::AutoGetRoutingExpressionArray(string &RoutingExpression,vector<string> & RoutingExpressionArray)
{
	BOOL bGetRoutingExpression=FALSE;
	if(GetRoutingExpressionArray(RoutingExpression,RoutingExpressionArray,9))
	{
		//�Ǳ��ʽ��
		bGetRoutingExpression=TRUE;
	}else if(GetRoutingExpressionArrayByExpression(RoutingExpression,RoutingExpressionArray))
	{
		//ֱ���Ǳ��ʽ
		bGetRoutingExpression=TRUE;

	}
	return bGetRoutingExpression;
}

BOOL CMakeCodeObj::GetAllRoutingNameFromRoutingBindTab(string &RoutingExpression,vector<string> & AllBindNameArray)
{
	vector<string> RoutingExpressionArray;
	vector<vector<string> > AllBindNameArraytmp;

	if(AutoGetRoutingExpressionArray(RoutingExpression,RoutingExpressionArray))
	{
		if(GetAllRoutingNameFromRoutingBindTab(RoutingExpressionArray,AllBindNameArraytmp))
		{
			for(unsigned int i=0;i<AllBindNameArraytmp.size();i++)
			{
				AllBindNameArray.push_back(GetRoutingPath(AllBindNameArraytmp[i]));
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMakeCodeObj::GetRoutingNode(
								  IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
								  IN vector<string> &RoutingExpression,	//·�ɱ��ʽ
								  IN list<_tagCodeObjTree>::iterator & RootCodeObj,	//���������
								  IN BOOL bSearchExpression,		//�Ƿ��ѯ���ڵı��ʽ
								  OUT BOOL & bFind,				//�Ƿ��ҵ�
								  OUT list<_tagCodeObjTree>::iterator & RetCodeObj,	//��һ��ƥ�䵽�Ľڵ�
								  OUT CodeRoutingContext & RoutingContext,	//�����ѯ���ʽ����·�ɻ���
								  IN unsigned int nDepth	
								  )
{
	vector<vector<string> > BindRoutingExpressionArray;

	if(GetRoutingNode_Real(
		RootRootCodeObj,RoutingExpression,	//·�ɱ��ʽ
		RootCodeObj,		//���������
		bSearchExpression,	//�Ƿ��ѯ���ڵı��ʽ
		bFind,				//�Ƿ��ҵ�
		RetCodeObj,			//��һ��ƥ�䵽�Ľڵ�
		RoutingContext,		//�����ѯ���ʽ����·�ɻ���
		nDepth	))
	{
		if(bFind==FALSE)
		{
			if(GetAllRoutingNameFromRoutingBindTab(RoutingExpression,BindRoutingExpressionArray))
			{
				for(unsigned int i=0;i<BindRoutingExpressionArray.size();i++)
				{
					RoutingContext.CodeRouting.clear();
					if(GetRoutingNode_Real(
						RootRootCodeObj,BindRoutingExpressionArray[i],	//·�ɱ��ʽ
						RootCodeObj,			//���������
						bSearchExpression,		//�Ƿ��ѯ���ڵı��ʽ
						bFind,				//�Ƿ��ҵ�
						RetCodeObj,			//��һ��ƥ�䵽�Ľڵ�
						RoutingContext,		//�����ѯ���ʽ����·�ɻ���
						nDepth	))
					{
						if(bFind==FALSE)
						{
							//û���ҵ�������һ����������
							continue;
						}else
						{
							//���ƥ�䵽��һ�����ϵĽڵ��򷵻�
							return TRUE;
						}
					}else
					{
						return FALSE;
					}
				}
			}
		}
		return TRUE;
	}
	return FALSE;
	
}

BOOL CMakeCodeObj::GetRoutingNode_Real(
								  IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
								  IN vector<string> &RoutingExpression,	//·�ɱ��ʽ
								  IN list<_tagCodeObjTree>::iterator & RootCodeObj,	//���������
								  IN BOOL bSearchExpression,		//�Ƿ��ѯ���ڵı��ʽ
								  OUT BOOL & bFind,				//�Ƿ��ҵ�
								  OUT list<_tagCodeObjTree>::iterator & RetCodeObj,	//��һ��ƥ�䵽�Ľڵ�
								  OUT CodeRoutingContext & RoutingContext,	//�����ѯ���ʽ����·�ɻ���
								  IN unsigned int nDepth	
								  )
{	
	//�����������·��
	//ROOT
	vector<string> RoutingExpressionArray=RoutingExpression;
	list<_tagCodeObjTree>::iterator RoutingDst=RootCodeObj;



	if(RoutingExpressionArray.size()>=3)
	{
		if(RoutingExpressionArray[2]==string("������Ŀ1"))
		{
			DebugPrint(nDepth,"GetRoutingNode ·��(%s) (%s)  \r\n ",
				RootCodeObj->ObjName.c_str(),GetRoutingPath(RoutingExpressionArray).c_str()
				);
		}
	}
	if(RoutingExpressionArray[0]==string("ROOTROOT"))
	{
		RoutingDst=RootRootCodeObj;
		//RoutingExpressionArray1.insert(RoutingExpressionArray1.begin(),
		//	RoutingExpressionArray.begin()++,RoutingExpressionArray.end());
		RoutingExpressionArray.erase(RoutingExpressionArray.begin());
	}
	//PARENT


	string ErrNode;

	CObjExpression::ParseRuleMapType::iterator itRootRule,itRuleTmp;
	BOOL bNextSearchWord=TRUE;
	bFind=FALSE;
	list<_tagCodeObjTree>::iterator CurRootCodeObj=RoutingDst;
	list<_tagCodeObjTree>::iterator	LastChildCodeNode=RoutingDst;
	list<_tagCodeObjTree>::iterator	BeginCode;
	list<_tagCodeObjTree>::iterator RetCodeObjTmp;

	CodeRoutingNode CurCodeNode;

	int i=0;
	BeginCode=CurRootCodeObj->ChildObj.begin();
	//����ʧ�ܵ����
	int nMaxDepth=i;
	//�����ѯ
	BOOL bFindNeighbor=FALSE;
	//��ʱ���۵ĸ����� 
	unsigned int nParentBack=0;
	for(i=0;i<(int)RoutingExpressionArray.size();)
	{
		//if(bSearchExpression)
		for(unsigned int s=i;s<RoutingExpressionArray.size();)
		{
			i=s;
			if(RoutingExpressionArray[i]!=string("PARENT")) break;

			//�����PARENT
			//���ڵ�Ϸ���
			//if(CurRootCodeObj->ObjName!=string("ROOTROOT"))
			{
				CurRootCodeObj=CurRootCodeObj->parent;

				LastChildCodeNode=CurRootCodeObj;

				BeginCode=CurRootCodeObj->ChildObj.begin();

				//RoutingContext.CodeRouting.pop_back();
			}
			/*else
			{
			DebugPrint(nDepth,"MakeCode ���ʽ %s �Ѿ�·�ɵ����ڵ� \r\n ",GetRoutingPath(RoutingExpressionArray).c_str());
			}*/

			//
			//RoutingExpressionArray.erase(RoutingExpressionArray.begin());

			s++;
		}

		{
			//��ʱ��֧���ٶ�����ʽ
			//if(FindRuleContext(itRuleTmp,itRootRule->second.Array[i].WordVal,nDepth))
			{
				//ȥƥ����ʽ
				//do 
				//{

				if(i==(RoutingExpressionArray.size()-1))
				{
					//���Ľڵ����Ƿ���Ҷֵ
					if(RoutingExpressionArray[i]==string("PARENT"))
					{
						CurCodeNode.ExpressionName=string("PARENT");
						CurCodeNode.CurCodeObjTree=CurRootCodeObj;
						CurCodeNode.LastChildCodeNode=CurRootCodeObj->ChildObj.end();
						RoutingContext.CodeRouting.push_back(CurCodeNode);
						RetCodeObjTmp=CurRootCodeObj;
						bFind=TRUE;
						break;
					}
					if(RoutingExpressionArray[i]==CurRootCodeObj->ObjVal)
					{
						CurCodeNode.ExpressionName=RoutingExpressionArray[i];
						CurCodeNode.CurCodeObjTree=CurRootCodeObj;
						CurCodeNode.LastChildCodeNode=CurRootCodeObj->ChildObj.end();
						RoutingContext.CodeRouting.push_back(CurCodeNode);
						RetCodeObjTmp=CurRootCodeObj;
						bFind=TRUE;
						break;
					}
				}
				if(GetCodeValByName(CurRootCodeObj,BeginCode,RoutingExpressionArray[i],RetCodeObjTmp))
				{
					//CurRootCodeObj=&(*RetCodeObj);
					CurRootCodeObj=RetCodeObjTmp;
					BeginCode=CurRootCodeObj->ChildObj.begin();
					if(nMaxDepth<i) nMaxDepth=i;
				}else if(GetCodeValByVal(CurRootCodeObj,BeginCode,RoutingExpressionArray[i],RetCodeObjTmp))
				{
					//CurRootCodeObj=&(*RetCodeObj);

					CurRootCodeObj=RetCodeObjTmp;
					BeginCode=CurRootCodeObj->ChildObj.begin();
					if(nMaxDepth<i) nMaxDepth=i;
				}else
				{
					//û���ҵ�����
					//break;

					//��˷�ϲ�ڵ�
					nParentBack=0;
					if(RoutingContext.CodeRouting.size()==0) 
					{
						//û���ܹ��ɹ�·�ɵĽڵ�
						goto faile;
					}

					if(bFindNeighbor)
					{
						//�ϴ�û�����ϻ�˷
						RoutingContext.CodeRouting.back().LastChildCodeNode=RoutingContext.CodeRouting.back().CurCodeObjTree->ChildObj.end();
					}else
					{
						//���ǻ�˷��ѯ�����
						i--;
					}
					for(;;)
					{
						//��˷�ϲ�ڵ�
						if(i<0)
						{
							//���ڵ�û�ҵ�˵��������
							goto faile;
						}

						if(RoutingContext.CodeRouting.back().LastChildCodeNode==RoutingContext.CodeRouting.back().CurCodeObjTree->ChildObj.end())
						{

							bFindNeighbor=FALSE;


							if((i>0)&&(RoutingExpressionArray[i-1]==string("PARENT")))
							{
								//���ǰ����PARENT
								for(;(i>=1)&&(RoutingExpressionArray[i-1]==string("PARENT"));)
								{
									nParentBack++;
									i--;
									RoutingContext.CodeRouting.pop_back();
								}
								i-=nParentBack;
								if(i<0)
								{
									goto faile;
								}
							}
							else
							{
								i--;
								RoutingContext.CodeRouting.pop_back();
							}

						}

						if(i<0)
						{
							//���ڵ�û�ҵ�˵��������
							goto faile;
						}

						CurRootCodeObj=RoutingContext.CodeRouting.back().CurCodeObjTree;
						LastChildCodeNode=CurRootCodeObj;
						BeginCode=RoutingContext.CodeRouting.back().LastChildCodeNode;
						BeginCode++;



						if(BeginCode!=CurRootCodeObj->ChildObj.end())
						{
							//RoutingContext.CodeRouting.back().LastChildCodeNode++;
							bFindNeighbor=TRUE;
							break;
						}
						RoutingContext.CodeRouting.back().LastChildCodeNode=BeginCode;
						//������˷
					}
					//�ӻ�˷������·�ڵ㿪ʼ����
					continue;


					//bFind=FALSE;
					//break;
				}

				if(bFindNeighbor)
				{
					//����ǲ��ڽڵ�
					RoutingContext.CodeRouting.back().LastChildCodeNode=CurRootCodeObj;
				}
				else
				{
					//�ӽڵ��ѯ
					CurCodeNode.ExpressionName=RoutingExpressionArray[i];
					CurCodeNode.CurCodeObjTree=LastChildCodeNode;
					CurCodeNode.LastChildCodeNode=CurRootCodeObj;
					RoutingContext.CodeRouting.push_back(CurCodeNode);

				}
				LastChildCodeNode=CurRootCodeObj;
				bFindNeighbor=FALSE;
				bFind=TRUE;
				i++;
				//} while (false);

			}
			/*
			else
			{
			//ƥ�����ϴ�
			if(GetCodeValByName(CurRootCodeObj,itRootRule->second.Array[i].WordVal,RetCodeObj))
			{
			//CurRootCodeObj=&(*RetCodeObj);
			CurRootCodeObj=RetCodeObj;


			CurCodeNode.ExpressionName=itRootRule->second.Array[i].WordVal;
			CurCodeNode.CurCodeObjTree=CurRootCodeObj;
			CurCodeNode.LastChildCodeNode=CurRootCodeObj->ChildObj.end();
			RoutingContext.CodeRouting.push_back(Node);

			}else if(GetCodeValByVal(CurRootCodeObj,itRootRule->second.Array[i].WordVal,RetCodeObj))
			{
			//CurRootCodeObj=&(*RetCodeObj);
			CurRootCodeObj=RetCodeObj;
			}
			//ƥ�����ϵ�ֵ
			}

			//ƥ��·�ɱ��ʽ*/

		}

	}

	goto sucess;

faile:
	bFind=FALSE;

	DebugPrint(nDepth,"GetRoutingNode_Real ·��(%s) (%s) ʧ�� \r\n ",
		RootCodeObj->ObjName.c_str(),GetRoutingPath(RoutingExpressionArray).c_str()
		);
	return TRUE;

sucess:
	RetCodeObj=RetCodeObjTmp;
	return TRUE;
}



BOOL CMakeCodeObj::MakeCodeRouting(
										IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
										IN string & LogHead,				//������־��ͷ
										IN list<_tagCodeObjTree>::iterator RootCodeObj,
										IN string & RoutingExpression,		//·�ɱ��ʽ
										IN ExpressionContext & BeginMake,
										IN ExpressionContext & ProcMake,
										IN ExpressionContext & EndMake,
										OUT BOOL & bMatched,
										OUT vector<string> & RetCode,
										IN unsigned int nDepth,
										IN unsigned int nRootDepth,
										IN BOOL bOne
										)
{
	vector<string> BindRoutingExpressionArray;
	vector<string>  RetCodeTmp;
	BOOL bRouting=FALSE;
	BOOL bRet=MakeCodeRouting_Real(RootRootCodeObj, 
		LogHead,RootCodeObj,RoutingExpression,
		BeginMake,ProcMake,EndMake,bMatched,RetCodeTmp,bRouting,
		nDepth,nRootDepth,bOne);
	if(bRet==FALSE) goto fail2;
	
	if(bRouting)
	{
		if(bMatched)
		{
			if(RetCodeTmp.size()) 
			{
				RetCode.insert(RetCode.end(),RetCodeTmp.begin(),RetCodeTmp.end());
				RetCodeTmp.clear();
			}
		}
		//���·�ɵ��򷵻ؽ��
		return TRUE;
	}else
	{
		//����·�ɵ���ʼmap·�ɲ�ѯ
		RetCodeTmp.clear();
		if(GetAllRoutingNameFromRoutingBindTab(RoutingExpression,BindRoutingExpressionArray))
		{
			for(unsigned int i=0;i<BindRoutingExpressionArray.size();i++)
			{
				if(MakeCodeRouting_Real(RootRootCodeObj, 
					LogHead,RootCodeObj,BindRoutingExpressionArray[i],
					BeginMake,ProcMake,EndMake,bMatched,RetCodeTmp,bRouting,
					nDepth,nRootDepth,bOne))
				{
					if(bMatched)
					{
						if(RetCodeTmp.size()) 
						{
							RetCode.insert(RetCode.end(),RetCodeTmp.begin(),RetCodeTmp.end());
							RetCodeTmp.clear();
						}
						if(bOne)
						{
							return TRUE;
						}
					}

				}else
				{
					return FALSE;
				}

			}

			return TRUE;
		}
		//���ܱ�·��
		bMatched=FALSE;
		goto fail1;
	}

fail1:
	//����·�ɵ�Ŀ��
	DebugPrint(nDepth,"MakeCodeRouting ·��(%s)ʧ�� Make(%s,%s,%s) \r\n ",
		RoutingExpression.c_str(),BeginMake.name.c_str(),
		ProcMake.name.c_str(),EndMake.name.c_str()
		);
	return TRUE;

fail2:
	//�����﷨����
	return FALSE;
	
}
BOOL CMakeCodeObj::MakeCodeRouting_Real(
								   IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
								   IN string & LogHead,				//������־��ͷ
								   IN list<_tagCodeObjTree>::iterator RootCodeObj,
								   IN string & RoutingExpression,		//·�ɱ��ʽ
								   IN ExpressionContext & BeginMake,
								   IN ExpressionContext & ProcMake,
								   IN ExpressionContext & EndMake,
								   OUT BOOL & bMatched,
								   OUT vector<string> & RetCode,
								   OUT BOOL & bRouting,		//�Ƿ��ܹ�·�ɵ�
								   IN unsigned int nDepth,
								   IN unsigned int nRootDepth,
								   IN BOOL bOne
								   )
{
	BOOL bFind=FALSE;
	list<_tagCodeObjTree>::iterator  CodeObj;
	CodeRoutingContext Context;
	vector<string> RoutingExpressionArray;
	if(AutoGetRoutingExpressionArray(RoutingExpression,RoutingExpressionArray)==FALSE) return FALSE;
	BOOL bRet=GetRoutingNode_Real(RootRootCodeObj,RoutingExpressionArray,RootCodeObj,
		TRUE,bFind,CodeObj,Context,nDepth);
	if(bFind==FALSE) 
	{
		bRouting=FALSE;
		bMatched=FALSE;
		return TRUE;
	}
	CObjExpression::ParseRuleMapType::iterator ItMakeExpression;

	unsigned int nRootDepthMe;
	nRootDepthMe=RoutingExpressionArray.size();
	nRootDepthMe+=nRootDepth;
	vector<string>  RetCodeTmp;
	if(bRet)
	{
		bRouting=TRUE;
		if(bFind)
		{
			//make

			if(MakeCode(RootRootCodeObj,CodeObj,BeginMake,bMatched,RetCode,nDepth<<1,nRootDepthMe)==FALSE) goto failed;

			if(bMatched==FALSE)	goto failed1;

			if(bOne) 
			{
				DebugPrint(nDepth,"MakeCodeRouting_Real ·�� d=%d (%s) Make(%s,%s,%s)�ɹ� \r\n ",
					nRootDepthMe,RoutingExpression.c_str(),BeginMake.name.c_str(),
					ProcMake.name.c_str(),EndMake.name.c_str()
					);
				return TRUE;
			}

			int i=1;
			for(;;)
			{
				bRet=NextRoutingNode(RootRootCodeObj,Context,bFind,CodeObj,nDepth);

				if(bRet)
				{
					if (bFind)
					{
						//����make
						if(RetCodeTmp.size()) 
						{
							//���ϴεĽ�����뵽���
							RetCode.insert(RetCode.end(),RetCodeTmp.begin(),RetCodeTmp.end());
							RetCodeTmp.clear();
						}
						if(MakeCode(RootRootCodeObj,CodeObj,ProcMake,bMatched,RetCodeTmp,nDepth<<1,nRootDepthMe)==FALSE) goto failed;

						i++;
					}
					else
					{
						//��������
						if(i>1)
						{
							//RetCode.pop_back();
							if(MakeCode(RootRootCodeObj,CodeObj,EndMake,bMatched,RetCode,nDepth<<1,nRootDepthMe)==FALSE) goto failed;
						}
						break;
					}
				}else
				{
					break;
				}

			}
			DebugPrint(nDepth,"MakeCodeRouting_Real ·�� d=%d (%s) Make(%s,%s,%s)�ɹ� \r\n ",
				nRootDepthMe,RoutingExpression.c_str(),BeginMake.name.c_str(),
				ProcMake.name.c_str(),EndMake.name.c_str()
				);
			return TRUE;
		}else
		{
			goto failed1;
		}
	}
	/*
	else
		{
			bRouting=FALSE;
			bMatched=FALSE;
			return TRUE;
		}*/
	
failed:
	return FALSE;

failed1:
	DebugPrint(nDepth,"MakeCodeRouting_Real ·�� d=%d (%s=%s)�ɹ� Make(%s,%s,%s)ʧ�� \r\n ",
		nRootDepthMe,RoutingExpression.c_str(),GetRoutingPath(RoutingExpressionArray).c_str(),BeginMake.name.c_str(),
		ProcMake.name.c_str(),EndMake.name.c_str()
		);
	return TRUE;
}

BOOL CMakeCodeObj::SaveCodeToObj(IN ExpressionContext & Context, IN string & pObj,IN vector<string> & RetCode)
{
	string szFilePath = pObj;
	if (!CTokenizer::IsAbsolutePath(pObj.c_str()))
	{
		szFilePath = m_ObjExpressionMgr->m_ExpEnvMap[Context.nExpressionEnv].szExpEnvPath + pObj;
	}
	HANDLE hFile= CreateFile(szFilePath.c_str(),                // name of the write
		GENERIC_READ|GENERIC_WRITE,          // open for writing
		FILE_SHARE_WRITE|FILE_SHARE_READ,                      // do not share
		NULL,                   // default security
		CREATE_ALWAYS,          // overwrite existing
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template

	if (hFile == INVALID_HANDLE_VALUE) 
	{ 
		DWORD nError=GetLastError();
		AfxMessageBox("���ļ�ʧ��");
		return FALSE;
	}

	DWORD nLen=0;
	for(unsigned int i=0;i<RetCode.size();i++)
	{
		WriteFile(hFile," ",1,&nLen,NULL);
		WriteFile(hFile,RetCode[i].c_str(),RetCode[i].length(),&nLen,NULL);
	}

	CloseHandle(hFile);
	return TRUE;
}

/*
���ʽ����
���ʽΪ�棬����뷵�ظ��ϲ���ʽ
MAKE_N<����ڵ�,��һ������ڵ�MAKE,�м�Ĺ��̴���ڵ�MAKE,ĩβ�Ĵ���ڵ�MAKE> ������з��ϴ���ڵ���ʽ�Ĵ���ڵ㣬Ȼ���ɺ����MAKE���ʽ����
MAKE_ONE<����ڵ�,����ڵ�MAKE> ֻMAKE�����һ�����ϴ���ڵ���ʽ�Ĵ���ڵ� 
MAKE_ADD<MAKE���ʽ�ַ����ı��ʽ����>	��ӻ�������һ�����ʽ
WORD(x) �����ַ���������ַ�������"����Ҫ��ǰ���\
NOT<MAKE���ʽ> ���MAKE���ʽ�ɹ��򷵻ؼ٣�������������ִ�У�����MAKE���ʽ�Ľ����������������
IF<MAKE���ʽ> ���MAKE���ʽ�ɹ��򷵻��棬������������ִ�У�����MAKE���ʽ�Ľ����������������
DEBUGOUT<"�ַ���">	��ӡ�ַ���
DEBUGOUT<MAKE���ʽ> ��ӡMAKE���ʽ���ɵĽ������Ӱ��������ı��ʽ���״̬
MAKE_TO<MAKE���ʽ,����Ŀ�������> ���MAKE���ʽΪ�����������浽Ŀ�������ָ���Ķ�����ȥ
MAKE_MAKECODE<��Ҫ���������Դ����,����Դ����Ľű�����>  ���������һ��MAKE���ʽ���ص��ַ�����Ҳ����ֱ����һ�������ַ������ļ�·��
MAKE_CODE_TO<Դ����,����Դ�����MAKE���ʽ,�������> ����������ļ�·���ַ���������һ��MAKE���ʽ���,����Դ�����MAKE���ʽ �� Դ������������Ľ������ �������
MAKE_BIND_ROUTING<���󶨵���·�����ַ���,��Ҫӳ�䵽��·������ʵ·���ַ���>
+  ���ʽ������Ӳ����̿��� A+B ���AΪ����ִ��B��AB��Ϊ���򷵻���
&  ���ʽ������Ӳ����̿��� A&B ����Aִ���Ƿ�ɹ�������ִ��B, ABֻҪ��һ��Ϊ���򷵻���
#  ���ʽ������Ӳ����̿��� A#B ��+������ֻͬ�Ƿ��صĽ�������þ����ӣ����Ǵʵ��ں�
|  ���ʽ������Ӳ����̿��� A|B	���AΪ�棬��ִ��B������Bִ����һ�����ʽ�����AΪ�٣���ִ��B,���ؽ��ΪA��B,���صĴ�������ֵ���Ǹ����ʽMAKE���
*/

BOOL CMakeCodeObj::MakeCode(
							IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
							IN list<_tagCodeObjTree>::iterator  & OrgCodeObj,
							IN ExpressionContext & Context,
							OUT BOOL & bMatched,
							OUT vector<string> & RetCode,
							IN unsigned int nDepth,
							IN unsigned int nRootDepth)
{
	unsigned int iCommand=0;//���ʽͷ
	bMatched=FALSE;
	BOOL bFailed=FALSE; //ϵͳ�쳣�����������ʽ�쳣
	BOOL bMatch=FALSE;
	BOOL bMatchTmp=FALSE;
	BOOL bLastMacthWord=FALSE;
	Context.nDestLen=0;
	string strLastFalg="one";//���һ�α��ʽ����
	//BOOL bFailNoChangeSucess=FALSE;//ƥ�䲻�ı�ƥ��ɹ���־
	//BOOL bFindKeyword=FALSE;
	ExpressionContext CurContext;
	list<_tagCodeObjTree>::iterator CodeObjTmp;
	vector<string> MakeCodeTmp,MakeCodeTmp1,MakeCodeTmp2;
	//4�����ʽ�������������������
	//����ƥ�����������
	//unsigned int nWordPos=Context.nBeginPos;

	//����Make���ɴ�����
	CGenerateCodeTree CodeTree;
	ExpressionContext BeginMake;
	ExpressionContext ProcMake;
	ExpressionContext EndMake;

	CObjExpression::ParseRuleMapType::iterator itRuleContext,itRuleContext1,itRuleContext2,itRuleContext3,itRuleContext4;


	if(string("MAKE_�Ƿ����ַ����ͱ�char����")==Context.name.c_str())
	{
		//if(OrgCodeObj->ObjVal==string("MultiplyTransform"))
		{
			DebugPrint(nDepth,"���ʽ (%s) %d \r\n ",
				Context.name.c_str(),bMatch
				);
		}

	}

	for(;iCommand<Context.nNumWord+2;/*iCommand++*/)
	{
		//bFailNoChangeSucess=FALSE;

		//bFindKeyword=FALSE;
		//MakeCodeTmp.clear();
		CurContext.Array.clear();
		CurContext.name="";
		CurContext.nametype="";
		CurContext.nBeginPos=0;
		CurContext.nDestLen=0;
		CurContext.nEndPos=0;
		MakeCodeTmp1.clear();

		if(Context.Array[iCommand].WordType==string("����")
			)
		{
			if((bLastMacthWord==TRUE))
			{
				//�﷨����
				DebugPrint(nDepth,"���ʽ (%s) ���ʽ���쳣λ��(%d %s)\r\n  ",
					Context.name.c_str(),iCommand,
					Context.Array[iCommand].WordVal.c_str());

				bFailed=TRUE;
				break;
			}
			//�ϴα����ǵ�һ��ƥ�������һ�η���ƥ��
			bLastMacthWord=TRUE;
			bMatchTmp=FALSE;
			//�ҵ�Ҫƥ���������
			//���ñ��ʽ����

			if(
				(string("MAKE_N")==Context.Array[iCommand].WordVal)
				&&(string("<")==Context.Array[iCommand+1].WordVal)
				&&(string(",")==Context.Array[iCommand+3].WordVal)
				&&(string(",")==Context.Array[iCommand+5].WordVal)
				&&(string(",")==Context.Array[iCommand+7].WordVal)
				&&(string(">")==Context.Array[iCommand+9].WordVal)
				)
			{

				if(FindRuleContext(itRuleContext,Context.Array[iCommand+2].WordVal,nDepth)
					&&FindRuleContext(itRuleContext1,Context.Array[iCommand+4].WordVal,nDepth)
					&&FindRuleContext(itRuleContext2,Context.Array[iCommand+6].WordVal,nDepth)
					&&FindRuleContext(itRuleContext3,Context.Array[iCommand+8].WordVal,nDepth))
				{
					BeginMake=itRuleContext1->second;
					ProcMake=itRuleContext2->second;
					EndMake=itRuleContext3->second;

					BeginMake.pObjExpression=Context.pObjExpression;
					BeginMake.pCodeTree=Context.pCodeTree;
					ProcMake.pObjExpression=Context.pObjExpression;
					ProcMake.pCodeTree=Context.pCodeTree;
					EndMake.pObjExpression=Context.pObjExpression;
					EndMake.pCodeTree=Context.pCodeTree;

					if(MakeCodeRouting(
						RootRootCodeObj,
						Context.name,
						OrgCodeObj,
						Context.Array[iCommand+2].WordVal,
						BeginMake,
						ProcMake,
						EndMake,
						bMatchTmp,MakeCodeTmp1,nDepth,nRootDepth,FALSE)==FALSE)
					{
						bFailed=TRUE;
						break;
					}
					if (MakeCodeTmp1.size())
					{
						bMatchTmp=TRUE;
						if((string("#")==strLastFalg))
						{
							MakeCodeTmp.back()+=MakeCodeTmp1.front();
							if(MakeCodeTmp1.size()>1)
							{
								MakeCodeTmp.insert(MakeCodeTmp.end(),
									++MakeCodeTmp1.begin(),MakeCodeTmp1.end());
							}

						}else
						{
							MakeCodeTmp.insert(MakeCodeTmp.end(),
								MakeCodeTmp1.begin(),MakeCodeTmp1.end());
						}
					}
				}
				iCommand+=10;
				continue;
			}
			
			if(
				(string("MAKE_BIND_ROUTING")==Context.Array[iCommand].WordVal)
				&&(string("<")==Context.Array[iCommand+1].WordVal)
				&&(string(",")==Context.Array[iCommand+3].WordVal)
				&&(string(">")==Context.Array[iCommand+5].WordVal)
				)
			{
				bMatchTmp=TRUE;
				if(Context.Array[iCommand+2].WordType==string("�ַ�����")&&
					Context.Array[iCommand+4].WordType==string("�ַ�����"))
				{
					if(BindRoutingName(Context.Array[iCommand+2].WordVal,Context.Array[iCommand+4].WordVal)==FALSE)
					{

						break;
					}
				}else if(FindRuleContext(itRuleContext,Context.Array[iCommand+2].WordVal,nDepth)
					&&FindRuleContext(itRuleContext1,Context.Array[iCommand+4].WordVal,nDepth)
					)
				{
					bFailed=TRUE;
					break;
				}

				iCommand+=6;
				continue;

			}

			if(
				(string("MAKE_ONE")==Context.Array[iCommand].WordVal)
				&&(string("<")==Context.Array[iCommand+1].WordVal)
				&&(string(",")==Context.Array[iCommand+3].WordVal)
				&&(string(">")==Context.Array[iCommand+5].WordVal)
				)
			{

				if(FindRuleContext(itRuleContext,Context.Array[iCommand+2].WordVal,nDepth)
					&&FindRuleContext(itRuleContext1,Context.Array[iCommand+4].WordVal,nDepth)
					)
				{

					{

						BeginMake=itRuleContext1->second;
						ProcMake=itRuleContext1->second;
						EndMake=itRuleContext1->second;

						BeginMake.pObjExpression=Context.pObjExpression;
						BeginMake.pCodeTree=Context.pCodeTree;
						ProcMake.pObjExpression=Context.pObjExpression;
						ProcMake.pCodeTree=Context.pCodeTree;
						EndMake.pObjExpression=Context.pObjExpression;
						EndMake.pCodeTree=Context.pCodeTree;

						if(MakeCodeRouting(
							RootRootCodeObj,
							Context.name,
							OrgCodeObj,
							Context.Array[iCommand+2].WordVal,
							BeginMake,
							ProcMake,
							EndMake,
							bMatchTmp,MakeCodeTmp1,nDepth,nRootDepth,TRUE)==FALSE)
						{
							bFailed=TRUE;
							break;
						}
						if (MakeCodeTmp1.size())
						{
							bMatchTmp=TRUE;
							if((string("#")==strLastFalg))
							{
								MakeCodeTmp.back()+=MakeCodeTmp1.front();
								if(MakeCodeTmp1.size()>1)
								{
									MakeCodeTmp.insert(MakeCodeTmp.end(),
										++MakeCodeTmp1.begin(),MakeCodeTmp1.end());
								}

							}else
							{
								MakeCodeTmp.insert(MakeCodeTmp.end(),
									MakeCodeTmp1.begin(),MakeCodeTmp1.end());
							}
						}
					}
				}
				iCommand+=6;
				continue;
			}


			if(
				(string("MAKE_ADD")==Context.Array[iCommand].WordVal)
				&&(string("<")==Context.Array[iCommand+1].WordVal)
				&&(string(">")==Context.Array[iCommand+3].WordVal)
				)
			{

				if(FindRuleContext(itRuleContext,Context.Array[iCommand+2].WordVal,nDepth))
				{
					CurContext=itRuleContext->second;
					CurContext.nEndPos=Context.nEndPos;
					CurContext.pObjExpression=Context.pObjExpression;
					CurContext.pCodeTree=Context.pCodeTree;
					if(MakeCode(RootRootCodeObj,OrgCodeObj,CurContext,bMatchTmp,MakeCodeTmp1,nDepth<<1,nRootDepth)==FALSE)
					{
						bFailed=TRUE;
						break;
					}
					if(bMatchTmp)
					{
						//char * pAddArray[]={MakeCodeTmp1,NULL};
						vector<string> szExpression;
						szExpression.push_back(string(" "));
						for(int i=0;i<MakeCodeTmp1.size();i++)
						{
							szExpression[0]+=MakeCodeTmp1[i];
							szExpression[0]+=string(" ");
						}
						bMatchTmp=Context.pObjExpression->AddExpression(szExpression,Context.nExpressionEnv);
						if (bMatchTmp==FALSE)
						{
							DebugPrint(nDepth,"MAKE_ADD ���ʽ (%s) �쳣",
								MakeCodeTmp1[0].c_str());

							bFailed=TRUE;
							break;
						}
					}
					else
					{
						DebugPrint(nDepth,"MAKE_ADD ���ʽ (%s) makeʧ��",
							CurContext.name.c_str());

						bFailed=TRUE;
						break;
					}

				}
				iCommand+=4;
				continue;
			}

			if(
				(string("WORD")==Context.Array[iCommand].WordVal)
				&&(string("(")==Context.Array[iCommand+1].WordVal)
				)
			{
				/*
				if((string("NULL")==Context.Array[iCommand+2].WordVal))
								{
									DebugPrint(1,"sadas");
								}*/
				
				if((string("\\")==Context.Array[iCommand+2].WordVal))
				{
					if((string(")")==Context.Array[iCommand+4].WordVal))
					{
						string tmpWord;
						BOOL bMatchCtl=TRUE;
						switch(Context.Array[iCommand+3].WordVal[0])
						{
						case 't':
							tmpWord="\t";
							break;
						case 'r':
							tmpWord="\r";
							break;
						case 'b':
							tmpWord="\b";
							break;
						case 'n':
							tmpWord="\n";
							break;
						default:
							bMatchCtl=FALSE;
							break;
						}
						if(bMatchCtl==FALSE)
						{
							bFailed=TRUE;
							break;
						}

						if((string("#")==strLastFalg))
						{
							MakeCodeTmp.back()+=tmpWord;
						}else
						{
							MakeCodeTmp.push_back(tmpWord);
						}
						iCommand+=5;
						bMatchTmp=TRUE;
						continue;
					}
					else
					{
						bFailed=TRUE;
						break;
					}
				}else if((string(")")==Context.Array[iCommand+3].WordVal))
				{
					if((string("#")==strLastFalg))
					{
						if(MakeCodeTmp.size())
						{
							MakeCodeTmp.back()+=Context.Array[iCommand+2].WordVal;
						}else
						{
							MakeCodeTmp.push_back(Context.Array[iCommand+2].WordVal);
						}

					}else
					{
						MakeCodeTmp.push_back(Context.Array[iCommand+2].WordVal);
					}
					iCommand+=4;
					bMatchTmp=TRUE;
					continue;
				}else
				{
					bFailed=TRUE;
					break;
				}


			}

			if(
				(string("NOT")==Context.Array[iCommand].WordVal)
				&&(string("<")==Context.Array[iCommand+1].WordVal)
				&&(string(">")==Context.Array[iCommand+3].WordVal)
				)
			{

				if(FindRuleContext(itRuleContext,Context.Array[iCommand+2].WordVal,nDepth))
				{
					CurContext=itRuleContext->second;
					CurContext.nEndPos=Context.nEndPos;
					CurContext.pObjExpression=Context.pObjExpression;
					CurContext.pCodeTree=Context.pCodeTree;
					if(MakeCode(RootRootCodeObj,OrgCodeObj,CurContext,bMatchTmp,MakeCodeTmp1,nDepth<<1,nRootDepth)==FALSE)
					{
						bFailed=TRUE;
						break;
					}
					MakeCodeTmp1.clear();
					bMatchTmp = bMatchTmp ? FALSE : TRUE;


					iCommand+=4;
					continue;
				}
			}

			if(
				(string("IF")==Context.Array[iCommand].WordVal)
				&&(string("<")==Context.Array[iCommand+1].WordVal)
				&&(string(">")==Context.Array[iCommand+3].WordVal)
				)
			{

				if(FindRuleContext(itRuleContext,Context.Array[iCommand+2].WordVal,nDepth))
				{
					CurContext=itRuleContext->second;
					CurContext.nEndPos=Context.nEndPos;
					CurContext.pObjExpression=Context.pObjExpression;
					CurContext.pCodeTree=Context.pCodeTree;
					if(MakeCode(RootRootCodeObj,OrgCodeObj,CurContext,bMatchTmp,MakeCodeTmp1,nDepth<<1,nRootDepth)==FALSE)
					{
						bFailed=TRUE;
						break;
					}
					MakeCodeTmp1.clear();

					iCommand+=4;
					continue;
				}
			}


			if(
				(string("DEBUGOUT")==Context.Array[iCommand].WordVal)
				&&(string("<")==Context.Array[iCommand+1].WordVal)
				&&(string(">")==Context.Array[iCommand+3].WordVal)
				)
			{
				bMatchTmp=TRUE;
				string Rootpath;
				if(Context.Array[iCommand+2].WordVal==string("MAKE�������������⺯������111"))
				{
					DebugPrint(nDepth,"1234");
				}
				if(Context.Array[iCommand+2].WordType==string("�ַ�����"))
				{
					Context.pCodeTree->GetRoutingPath(OrgCodeObj,Rootpath);
					DebugPrint(nDepth,"==ROOTPATH(%s)==\r\nDEBUGOUT �ַ���(%s)\r\n ",
						Rootpath.c_str(),Context.Array[iCommand+2].WordVal.c_str());

				}else if(Context.Array[iCommand+2].WordType==string("����"))
				{
					if(FindRuleContext(itRuleContext,Context.Array[iCommand+2].WordVal,nDepth))
					{
						CurContext=itRuleContext->second;
						CurContext.nEndPos=Context.nEndPos;
						CurContext.pObjExpression=Context.pObjExpression;
						CurContext.pCodeTree=Context.pCodeTree;
						BOOL bDebugMatch=FALSE;
						if(MakeCode(RootRootCodeObj,OrgCodeObj,CurContext,bDebugMatch,MakeCodeTmp1,nDepth<<1,nRootDepth)==FALSE)
						{
							bFailed=TRUE;
							break;
						}
						//MakeCodeTmp1.clear();
						if(bDebugMatch)
						{
							string rst;
							for (unsigned int i=0;i<MakeCodeTmp1.size();i++)
							{
								rst+=MakeCodeTmp1[i];
								rst+=string(" ");
							}

							Context.pCodeTree->GetRoutingPath(OrgCodeObj,Rootpath);
							DebugPrint(nDepth,"==ROOTPATH(%s)==\r\nDEBUGOUT ���ʽ %s make���(%s)\r\n ",
								Rootpath.c_str(),Context.Array[iCommand+2].WordVal.c_str(),rst.c_str());
						}
					}
				}
				iCommand+=4;
				continue;
			}

			if(
				(string("MAKE_TO")==Context.Array[iCommand].WordVal)
				&&(string("<")==Context.Array[iCommand+1].WordVal)
				&&(string(",")==Context.Array[iCommand+3].WordVal)
				&&(string(">")==Context.Array[iCommand+5].WordVal)
				)
			{
				//�õ�codeobjtree

				MakeCodeTmp2.clear();
				MakeCodeTmp1.clear();

				//���ɴ��벢���浽Ŀ��
				if(FindRuleContext(itRuleContext,Context.Array[iCommand+2].WordVal,nDepth))
				{
					CurContext=itRuleContext->second;
					CurContext.nEndPos=Context.nEndPos;
					CurContext.pCodeTree=&CodeTree;
					CurContext.pObjExpression=m_ObjExpressionMgr;

					if(MakeCode(RootRootCodeObj,OrgCodeObj,CurContext,bMatchTmp,MakeCodeTmp1,nDepth<<1,nRootDepth)==FALSE)
					{
						bFailed=TRUE;
						break;
					}
					if(bMatchTmp)
					{
						if(Context.Array[iCommand+4].WordType==string("�ַ�����"))
						{
							SaveCodeToObj(Context,Context.Array[iCommand+4].WordVal,MakeCodeTmp1);
						}
						else if(Context.Array[iCommand+4].WordType==string("����"))
						{
							//�õ�Ŀ��·���ַ���
							if(FindRuleContext(itRuleContext,Context.Array[iCommand+4].WordVal,nDepth))
							{
								CurContext=itRuleContext->second;
								CurContext.nEndPos=Context.nEndPos;
								if(MakeCode(RootRootCodeObj,OrgCodeObj,CurContext,bMatchTmp,MakeCodeTmp2,nDepth<<1,nRootDepth)==FALSE)
								{
									bFailed=TRUE;
									break;
								}
								if(bMatchTmp)
								{	
									string szObj;
									for(unsigned int i=0;i<MakeCodeTmp2.size();i++)
									{
										szObj+=MakeCodeTmp2[i];
									}
									SaveCodeToObj(CurContext,szObj,MakeCodeTmp1);
								}else
								{
									DebugPrint(nDepth,"MakeCode MAKE_TO ·�����ʽ %s make ʧ�� \r\n ",
										Context.Array[iCommand+4].WordVal.c_str());
									bFailed=TRUE;
									break;
								}
							}
							else
							{
								DebugPrint(nDepth,"MakeCode MAKE_TO ·�����ʽ %s û���ҵ� \r\n ",
									Context.Array[iCommand+4].WordVal.c_str());
								bFailed=TRUE;
								break;
							}
						}

						if((string("#")==strLastFalg))
						{
							MakeCodeTmp.back()+=MakeCodeTmp1.front();
							if(MakeCodeTmp1.size()>1)
							{
								MakeCodeTmp.insert(MakeCodeTmp.end(),
									++MakeCodeTmp1.begin(),MakeCodeTmp1.end());
							}
						}else
						{
							MakeCodeTmp.insert(MakeCodeTmp.end(),
								MakeCodeTmp1.begin(),MakeCodeTmp1.end());
						}
					}else
					{
						DebugPrint(nDepth,"MakeCode MAKE_TO %s ·�����ʽ %s ���ɴ���ʧ��\r\n ",
							Context.Array[iCommand+2].WordVal.c_str(),Context.Array[iCommand+4].WordVal.c_str());
						bFailed=TRUE;
						break;
					}


					iCommand+=6;
					continue;
				}
			}

			if(
				(string("MAKE_MAKECODE")==Context.Array[iCommand].WordVal)
				&&(string("<")==Context.Array[iCommand+1].WordVal)
				&&(string(",")==Context.Array[iCommand+3].WordVal)
				&&(string(">")==Context.Array[iCommand+5].WordVal)
				)
			{
				//�õ�codeobjtree

				MakeCodeTmp2.clear();
				MakeCodeTmp1.clear();
				{
					string InCodeObj;
					string InMakeObj;
					if(Context.Array[iCommand+2].WordType==string("�ַ�����"))
					{
						InCodeObj=Context.Array[iCommand+2].WordVal;
					}
					else if(Context.Array[iCommand+2].WordType==string("����"))
					{
						//�õ�Ŀ��·���ַ���
						if(FindRuleContext(itRuleContext,Context.Array[iCommand+2].WordVal,nDepth))
						{
							CurContext=itRuleContext->second;
							CurContext.nEndPos=Context.nEndPos;
							MakeCodeTmp2.clear();
							if(MakeCode(RootRootCodeObj,OrgCodeObj,CurContext,bMatchTmp,MakeCodeTmp2,nDepth<<1,nRootDepth)==FALSE)
							{
								bFailed=TRUE;
								break;
							}
							if(bMatchTmp)
							{	
								for(unsigned int i=0;i<MakeCodeTmp2.size();i++)
								{
									InCodeObj+=MakeCodeTmp2[i];
								}
							}else
							{
								DebugPrint(nDepth,"MakeCode MAKE_MAKECODE �������·�����ʽ %s make ʧ��\r\n  ",
									Context.Array[iCommand+2].WordVal.c_str());
								bFailed=TRUE;
								break;
							}
						}
						else
						{
							DebugPrint(nDepth,"MakeCode MAKE_MAKECODE �������·�����ʽ %s û���ҵ�\r\n  ",
								Context.Array[iCommand+2].WordVal.c_str());
							bFailed=TRUE;
							break;
						}
					}

					if(Context.Array[iCommand+4].WordType==string("�ַ�����"))
					{
						InMakeObj=Context.Array[iCommand+4].WordVal;
					}
					else if(Context.Array[iCommand+4].WordType==string("����"))
					{
						//�õ�Ŀ��·���ַ���
						if(FindRuleContext(itRuleContext,Context.Array[iCommand+4].WordVal,nDepth))
						{
							CurContext=itRuleContext->second;
							CurContext.nEndPos=Context.nEndPos;
							MakeCodeTmp2.clear();
							bMatchTmp = FALSE;
							if(MakeCode(RootRootCodeObj,OrgCodeObj,CurContext,bMatchTmp,MakeCodeTmp2,nDepth<<1,nRootDepth)==FALSE)
							{
								bFailed=TRUE;
								break;
							}
							if(bMatchTmp)
							{	
								for(unsigned int i=0;i<MakeCodeTmp2.size();i++)
								{
									InMakeObj+=MakeCodeTmp2[i];
								}
							}else
							{
								DebugPrint(nDepth,"MakeCode MAKE_MAKECODE ����make·�����ʽ %s make ʧ��\r\n  ",
									Context.Array[iCommand+4].WordVal.c_str());
								bFailed=TRUE;
								break;
							}
						}
						else
						{
							DebugPrint(nDepth,"MakeCode MAKE_MAKECODE ����make·�����ʽ %s û���ҵ�\r\n  ",
								Context.Array[iCommand+4].WordVal.c_str());
							bFailed=TRUE;
							break;
						}
					}

					CObjExpression ExpressionObj;
					ExpressionObj.Clone(m_ObjExpressionMgr);
					string szEnvPath = CTokenizer::IsAbsolutePath(InMakeObj.c_str())? InMakeObj: m_ObjExpressionMgr->m_ExpEnvMap[Context.nExpressionEnv].szExpEnvPath+InMakeObj;
					CTokenizer::FilePathToDirPath(szEnvPath);
					if(ExpressionObj.AddExpression(InMakeObj.c_str(), szEnvPath.c_str())==FALSE)
					{
						DebugPrint(nDepth,"MakeCode MAKE_MAKECODE ����make AddExpressionʧ�� %s \r\n  ",
							InMakeObj.c_str());
						bFailed=TRUE;
						break;
					}

					CMakeCodeObj Make;
					Make.BindObjExpressionMgr(&ExpressionObj);

					CodeTree.m_RootCodeObjList.clear();
					CodeTree.BindObjExpressionMgr(&ExpressionObj);

					if(GetSearchCodeToCodeObjTree(InCodeObj,CodeTree)==FALSE)
					{
						DebugPrint(nDepth,"MakeCode MAKE_MAKECODE ���ʽ%s ����CodeTreeʧ��\r\n ",
							Context.name.c_str());
						bFailed=TRUE;
						break;
					}
					else
					{
						string codetree;
						CodeTree.PrintCodeTree(codetree,32);

						vector<string> code;
						if(Make.MakeCode(code,&CodeTree,&ExpressionObj)==FALSE)
						{
							bFailed=TRUE;
							break;
						}
						else
						{
							bMatchTmp=TRUE;
						}

					}
				}

				iCommand+=6;
				continue;

			}
			if(
				(string("MAKE_CODE_TO")==Context.Array[iCommand].WordVal)
				&&(string("<")==Context.Array[iCommand+1].WordVal)
				&&(string(",")==Context.Array[iCommand+3].WordVal)
				&&(string(",")==Context.Array[iCommand+5].WordVal)
				&&(string(">")==Context.Array[iCommand+7].WordVal)
				)
			{
				//�õ�codeobjtree

				MakeCodeTmp2.clear();
				MakeCodeTmp1.clear();
				{
					string InCodeObj;
					if(Context.Array[iCommand+2].WordType==string("�ַ�����"))
					{
						InCodeObj=Context.Array[iCommand+2].WordVal;
					}
					else if(Context.Array[iCommand+2].WordType==string("����"))
					{
						//�õ�Ŀ��·���ַ���
						if(FindRuleContext(itRuleContext,Context.Array[iCommand+2].WordVal,nDepth))
						{
							CurContext=itRuleContext->second;
							CurContext.nEndPos=Context.nEndPos;
							if(MakeCode(RootRootCodeObj,OrgCodeObj,CurContext,bMatchTmp,MakeCodeTmp2,nDepth<<1,nRootDepth)==FALSE)
							{
								bFailed=TRUE;
								break;
							}
							if(bMatchTmp)
							{	
								for(unsigned int i=0;i<MakeCodeTmp2.size();i++)
								{
									InCodeObj+=MakeCodeTmp2[i];
								}
							}else
							{
								DebugPrint(nDepth,"MakeCode MAKE_CODE_TO �������·�����ʽ %s make ʧ��\r\n  ",
									Context.Array[iCommand+2].WordVal.c_str());
								bFailed=TRUE;
								break;
							}
						}
						else
						{
							DebugPrint(nDepth,"MakeCode MAKE_CODE_TO �������·�����ʽ %s û���ҵ�\r\n  ",
								Context.Array[iCommand+2].WordVal.c_str());
							bFailed=TRUE;
							break;
						}
					}
					CodeTree.m_RootCodeObjList.clear();
					CodeTree.BindObjExpressionMgr(m_ObjExpressionMgr);
					if(GetSearchCodeToCodeObjTree(InCodeObj,CodeTree)==FALSE)
					{
						DebugPrint(nDepth,"MakeCode MAKE_CODE_TO ���ʽ%s ����CodeTreeʧ��\r\n ",
							Context.name.c_str());
						bFailed=TRUE;
						break;
					}
					else
					{
						string codetree;
						CodeTree.PrintCodeTree(codetree,25);
					}
				}

				//���ɴ��벢���浽Ŀ��
				if(FindRuleContext(itRuleContext,Context.Array[iCommand+4].WordVal,nDepth))
				{
					CurContext=itRuleContext->second;
					CurContext.nEndPos=Context.nEndPos;
					CurContext.pCodeTree=&CodeTree;
					CurContext.pObjExpression=m_ObjExpressionMgr;

					if(MakeCode(MakeCodeTmp1,CurContext,FALSE)==FALSE)
					{
						bFailed=TRUE;
						break;
					}else if(MakeCodeTmp1.size())
					{
						if(Context.Array[iCommand+6].WordType==string("�ַ�����"))
						{
							SaveCodeToObj(Context,Context.Array[iCommand+6].WordVal,MakeCodeTmp1);
						}
						else if(Context.Array[iCommand+6].WordType==string("����"))
						{
							//�õ�Ŀ��·���ַ���
							if(FindRuleContext(itRuleContext,Context.Array[iCommand+6].WordVal,nDepth))
							{
								CurContext=itRuleContext->second;
								CurContext.nEndPos=Context.nEndPos;
								if(MakeCode(RootRootCodeObj,OrgCodeObj,CurContext,bMatchTmp,MakeCodeTmp2,nDepth<<1,nRootDepth)==FALSE)
								{
									bFailed=TRUE;
									break;
								}
								if(bMatchTmp)
								{	
									string szObj;
									for(unsigned int i=0;i<MakeCodeTmp2.size();i++)
									{
										szObj+=MakeCodeTmp2[i];
									}
									SaveCodeToObj(CurContext,szObj,MakeCodeTmp1);
								}else
								{
									DebugPrint(nDepth,"MakeCode MAKE_TO ·�����ʽ %s make ʧ�� \r\n ",
										Context.Array[iCommand+6].WordVal.c_str());
									bFailed=TRUE;
									break;
								}
							}
							else
							{
								DebugPrint(nDepth,"MakeCode MAKE_TO ·�����ʽ %s û���ҵ� \r\n ",
									Context.Array[iCommand+6].WordVal.c_str());
								bFailed=TRUE;
								break;
							}
						}



						if((string("#")==strLastFalg))
						{
							MakeCodeTmp.back()+=MakeCodeTmp1.front();
							if(MakeCodeTmp1.size()>1)
							{
								MakeCodeTmp.insert(MakeCodeTmp.end(),
									++MakeCodeTmp1.begin(),MakeCodeTmp1.end());
							}
						}else
						{
							MakeCodeTmp.insert(MakeCodeTmp.end(),
								MakeCodeTmp1.begin(),MakeCodeTmp1.end());
						}
					}else
					{
						DebugPrint(nDepth,"MakeCode MAKE_TO ·�����ʽ %s ���ɴ���ʧ��\r\n ",
							Context.Array[iCommand+6].WordVal.c_str());
						bFailed=TRUE;
						break;
					}


					iCommand+=8;
					continue;
				}
			}
			//·�ɴ����ͱ�
			{
				unsigned int nCommandLen=0;
				vector<string> RoutingExpressionArray;
				if(GetRoutingExpressionArray(Context,iCommand,RoutingExpressionArray,nCommandLen,nDepth))
				{
					list<_tagCodeObjTree>::iterator  MakeDst=OrgCodeObj;

					if(bFailed) break;

					//make
					if(nCommandLen==0) continue;
					CodeRoutingContext CodeContext;
					if(GetRoutingNode(RootRootCodeObj,RoutingExpressionArray,MakeDst,FALSE,bMatchTmp,
						CodeObjTmp,CodeContext,nDepth)==FALSE)
					{
						bFailed=TRUE;
						break;
					}
					if (bMatchTmp)
					{
						/*
						if(CodeObjTmp->ObjVal==string("MultiplyTransform"))
						{
						DebugPrint(nDepth,"���ʽ (%s) %d \r\n ",
						Context.name.c_str(),bMatch
						);
						}*/

						if((string("#")==strLastFalg))
						{
							MakeCodeTmp.back()+=CodeObjTmp->ObjVal;
						}else
						{
							MakeCodeTmp.push_back(CodeObjTmp->ObjVal);
						}
					}
					iCommand+=nCommandLen;
					continue;
				}
			}

			//�û��Զ�����ʽ����
			if(FindRuleContext(itRuleContext,Context.Array[iCommand].WordVal,nDepth))
			{
				CurContext=itRuleContext->second;
				CurContext.nEndPos=Context.nEndPos;

				CurContext.pObjExpression=Context.pObjExpression;
				CurContext.pCodeTree=Context.pCodeTree;

				if(MakeCode(RootRootCodeObj,OrgCodeObj,CurContext,bMatchTmp,MakeCodeTmp1,nDepth<<1,nRootDepth)==FALSE)
				{
					bFailed=TRUE;
					break;
				}
				if(bMatchTmp)
				{
					if((string("#")==strLastFalg))
					{
						if(MakeCodeTmp1.size()) 
						{
							MakeCodeTmp.back()+=MakeCodeTmp1.front();
						}

						if(MakeCodeTmp1.size()>1)
						{
							MakeCodeTmp.insert(MakeCodeTmp.end(),
								++MakeCodeTmp1.begin(),MakeCodeTmp1.end());
						}
					}else
					{
						MakeCodeTmp.insert(MakeCodeTmp.end(),
							MakeCodeTmp1.begin(),MakeCodeTmp1.end());
					}
				}

				iCommand+=1;
				continue;
			}


			//�쳣����ؼ���

			bFailed=TRUE;

			if(iCommand>Context.nNumWord)
			{
				DebugPrint(nDepth,"MakeCode ���ʽ %s �߽����ʧ�� \r\n ",Context.name.c_str());
				break;
			}

			DebugPrint(nDepth,"MakeCode ���ʽ (%s) �쳣λ��(%d %s)\r\n  ",
				Context.name.c_str(),iCommand,
				Context.Array[iCommand].WordVal.c_str());

			break;

		}


		//��һ����δ�μӷ��ż���
		if(strLastFalg==string("one"))
		{
			bMatch=bMatchTmp;
		}else
		{
			if(
				(string("+")==strLastFalg)
				)
			{
				if(bMatchTmp==FALSE)
				{
					bMatch=bMatchTmp;
				}
			}

			if(
				(string("#")==strLastFalg)
				)
			{
				if(bMatchTmp==FALSE)
				{
					bMatch=bMatchTmp;
				}
			}

			if(
				(string("|")==strLastFalg)
				)
			{

				if(bMatchTmp)
				{

					bMatch=bMatchTmp;

				}
			}

			if(
				(string("&")==strLastFalg)
				)
			{

				if(!bMatch)
				{

					bMatch=bMatchTmp;

				}
			}
		}

		//���ż���
		// + |Ϊ�������ƴ���ϳ� &Ϊ����������ϲ���ֻ����һ��Ϊ������ʽΪ��
		if(Context.Array[iCommand].WordVal==COMMANDEND)
		{
			//��������
			//�����һ�η������������


			//ƥ��ɹ�����
			/*
			if(bMatch)
			{
			DebugPrint(nDepth,"Make ���ʽ (%s)  %s �ɹ�Make����\r\n ",
			Context.name.c_str(),Context.Array[iCommand].WordVal.c_str());
			}*/


			break;
		}
		else if(Context.Array[iCommand].WordType==string("������"))
		{
			if((bLastMacthWord==FALSE))
			{
				//�﷨����
				DebugPrint(nDepth,"Make ���ʽ (%s) �쳣����λ��(%d %s)\r\n  ",
					Context.name.c_str(),iCommand,
					Context.Array[iCommand].WordVal.c_str());

				bFailed=TRUE;
				break;
			}

			bLastMacthWord=FALSE;



			if(
				(string("+")==Context.Array[iCommand].WordVal)
				)
			{
				strLastFalg="+";
				if(bMatchTmp)
				{
					///bMatch=bMatchTmp;
				}
				else
				{
					//���ʽƥ��ʧ��
					//DebugPrint(nDepth,"���ʽ %s ƥ��ʧ�� \r\n ",Context.name.c_str());
					break;
				}
				iCommand+=1;
				continue;
			}

			//ƥ���������+
			if(
				(string("#")==Context.Array[iCommand].WordVal)
				)
			{
				strLastFalg="#";
				if(bMatchTmp)
				{
					///bMatch=bMatchTmp;
				}
				else
				{
					//���ʽƥ��ʧ��
					//DebugPrint(nDepth,"���ʽ %s ƥ��ʧ�� \r\n ",Context.name.c_str());
					break;
				}
				iCommand+=1;
				continue;
			}

			if(
				(string("|")==Context.Array[iCommand].WordVal)
				)
			{
				strLastFalg="|";
				if(bMatchTmp)
				{
					//�ϴ��Ѿ��ɹ��������ٴ�ƥ��
					bMatch=bMatchTmp;

					string szCommand;
					unsigned int nCommandLen=0;
					if(GetCommandTypeAndLen(Context,iCommand+1,szCommand,nCommandLen,nDepth))
					{
						iCommand+=nCommandLen;
						iCommand+=1;
						bLastMacthWord=TRUE;
					}
					else
					{
						bFailed=TRUE;
						break;
					}
				}
				else
				{
					//����ƥ���
					//ʧ�ܲ����Ӳ���
					iCommand+=1;
				}

				continue;
			}

			//ƥ��������� |
			if(
				(string("&")==Context.Array[iCommand].WordVal)
				)
			{
				strLastFalg="&";
				if(!bMatch)
				{
					//�ϴβ��ɹ���ı�ƥ���־
					bMatch=bMatchTmp;

				}

				iCommand+=1;
				continue;
			}
		}
	}


	bMatched=bMatch;

	if((!bFailed)&&(bMatched))
	{
		RetCode.insert(RetCode.end(),MakeCodeTmp.begin(),MakeCodeTmp.end());
	}
	DebugPrint(nDepth,"Make nRootDepth=%d ���ʽ (%s) bFailed=%x,bMatched=%x,iCommand=%d,Comnamd=%s \r\n ",
		nRootDepth,Context.name.c_str(),bFailed,bMatched,iCommand,Context.Array[iCommand].WordVal.c_str()
		);

	return !bFailed;
}
//

BOOL CMakeCodeObj::MakeCode(vector<string> & RetCode)
{
	ExpressionContext  Context;
	Context.pObjExpression=m_ObjExpressionMgr;
	return MakeCode(RetCode,Context,TRUE);
}

BOOL CMakeCodeObj::MakeCode(IN vector<string> & RetCode,IN CGenerateCodeTree * pCodeTree,IN CObjExpression * pObjExpression)
{
	ExpressionContext  Context,CurContext;
	BOOL bRet=FALSE;
	unsigned int i=0;
	list<_tagCodeObjTree>::iterator itRootRootCodeObj;//=pCodeTree->;


	BOOL bMatch=FALSE;
	Context.pObjExpression=pObjExpression;
	Context.pCodeTree=pCodeTree;

	if(Context.pCodeTree->m_RootCodeObjList.begin()->ChildObj.size()==0) return FALSE;

	//list<_tagCodeObjTree>::iterator itCodeObj=Context.pCodeTree->m_RootCodeObjList.begin()->ChildObj.begin();

	itRootRootCodeObj=Context.pCodeTree->m_RootCodeObjList.begin();

	for(;i<Context.pObjExpression->m_RootRuleName.size();i++)
	{
		BOOL bBreak=FALSE;
		if (Context.pObjExpression->m_RootRuleName[i].name!=string("ROOT_MAKE")) continue;

		if(Context.name.length())
		{
			bBreak=TRUE;
		}
		else
		{
			CurContext=Context.pObjExpression->m_RootRuleName[i];
		}
		bMatch=FALSE;

		CurContext.pObjExpression=pObjExpression;
		CurContext.pCodeTree=pCodeTree;
		CurContext.nBeginPos=0;
		CurContext.nEndPos=Context.pCodeTree->m_WordArray.size();

		bRet=MakeCode(itRootRootCodeObj,itRootRootCodeObj,CurContext,bMatch,RetCode,1,0);
		if(!bRet) break;


		if(bBreak)
			break;
	}

	return bRet;

}

BOOL CMakeCodeObj::MakeCode(vector<string> & RetCode,ExpressionContext & Context,IN BOOL bRootNoCode)
{
	BOOL bRet=FALSE;
	unsigned int i=0;
	list<_tagCodeObjTree>::iterator itRootRootCodeObj;
	ExpressionContext CurContext;

	BOOL bMatch=FALSE;

	if(!bRootNoCode)
	{
		if(Context.pCodeTree->m_RootCodeObjList.begin()->ChildObj.size()==0) return FALSE;

		//list<_tagCodeObjTree>::iterator itCodeObj=Context.pCodeTree->m_RootCodeObjList.begin()->ChildObj.begin();

		itRootRootCodeObj=Context.pCodeTree->m_RootCodeObjList.begin();

		Context.nBeginPos=0;
		Context.nEndPos=Context.pCodeTree->m_WordArray.size();
		return MakeCode(itRootRootCodeObj,itRootRootCodeObj,Context,bMatch,RetCode,1,0);

	}
	else
	{
		for(;i<Context.pObjExpression->m_RootRuleName.size();i++)
		{
			BOOL bBreak=FALSE;
			if (Context.pObjExpression->m_RootRuleName[i].name!=string("ROOT_MAKE")) continue;

			if(Context.name.length())
			{
				bBreak=TRUE;
			}
			else
			{
				CurContext=Context.pObjExpression->m_RootRuleName[i];
			}
			bMatch=FALSE;


			bRet=MakeCode(itRootRootCodeObj,itRootRootCodeObj,CurContext,bMatch,RetCode,1,0);
			if(!bRet) break;


			if(bBreak)
				break;
		}
	}

	return bRet;

}


CMakeCodeObj::CMakeCodeObj(void)
{
}

CMakeCodeObj::~CMakeCodeObj(void)
{
}
