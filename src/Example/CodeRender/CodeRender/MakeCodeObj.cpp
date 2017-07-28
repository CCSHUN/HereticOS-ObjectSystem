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
			Command="路由型别";
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
								   OUT list<_tagCodeObjTree>::iterator & RetCodeObj,//匹配到的节点
								   IN unsigned int nDepth	
								   )
{
	list<CodeRoutingNode>::iterator itHead,itCur,itTmp,itChild;//父节点当前节点
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
		//子节点查找完毕则回朔
		if(itCur->LastChildCodeNode==itCur->CurCodeObjTree->ChildObj.end())
		{
			//子节点已经遍历完毕，开始下一个父节点
			if(itCur==RoutingContext.CodeRouting.begin()) return TRUE;

			itCur--;
			itCur->LastChildCodeNode++;
			continue;
		}

		itTmp=RoutingContext.CodeRouting.end();
		itTmp--;
		if(itCur==itTmp)
		{
			//最后的节点检查是否是叶值
			if((itCur->ExpressionName==itCur->CurCodeObjTree->ObjVal))
			{
				//最后一个节点是叶节点。

				//没有父节点，则无法再回朔。
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
			//没有找到符号
			//break;
			//goto faile;

			//最上层节点没找到，说明已经正常结束
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
			//不是底层节点
			//如果有子节点则需要改子节点
			itTmp->CurCodeObjTree=itCur->LastChildCodeNode;
			itTmp->LastChildCodeNode=itTmp->CurCodeObjTree->ChildObj.begin();
			itCur++;
		}
		else
		{
			//已经找到最底层节点
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
				if(Array[i].WordType!=string("词型")) return FALSE;
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
	if(Context.Array[nCommand+1].WordType!=string("词型"))
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
			if(Context.Array[i].WordType!=string("词型")) return FALSE;
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
			}else if((Context.Array[i].WordType==string("符号型")))
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
			DebugPrint(nDepth,"GetRoutingExpressionArray 表达式 %s 表达式不正确 \r\n ",RoutingExpressionName.c_str());
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
			//没找到说明可以插入

			Info.RoutingExpression=BindName;
			if(GetRoutingExpressionArrayByExpression(Info.RoutingExpression,Info.RoutingExpressionNodeArray))
			{
				m_RoutingMapTabArray[i].RoutingExpressionBindList.push_back(Info);
				return TRUE;
			}
			return FALSE;
		}
	}
	//没找到说明没有根需要全部插入
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
					//递归重新得到路径
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
		//是表达式名
		bGetRoutingExpression=TRUE;
	}else if(GetRoutingExpressionArrayByExpression(RoutingExpression,RoutingExpressionArray))
	{
		//直接是表达式
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
								  IN vector<string> &RoutingExpression,	//路由表达式
								  IN list<_tagCodeObjTree>::iterator & RootCodeObj,	//根代码对象
								  IN BOOL bSearchExpression,		//是否查询存在的表达式
								  OUT BOOL & bFind,				//是否找到
								  OUT list<_tagCodeObjTree>::iterator & RetCodeObj,	//第一个匹配到的节点
								  OUT CodeRoutingContext & RoutingContext,	//如果查询表达式则建立路由环境
								  IN unsigned int nDepth	
								  )
{
	vector<vector<string> > BindRoutingExpressionArray;

	if(GetRoutingNode_Real(
		RootRootCodeObj,RoutingExpression,	//路由表达式
		RootCodeObj,		//根代码对象
		bSearchExpression,	//是否查询存在的表达式
		bFind,				//是否找到
		RetCodeObj,			//第一个匹配到的节点
		RoutingContext,		//如果查询表达式则建立路由环境
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
						RootRootCodeObj,BindRoutingExpressionArray[i],	//路由表达式
						RootCodeObj,			//根代码对象
						bSearchExpression,		//是否查询存在的表达式
						bFind,				//是否找到
						RetCodeObj,			//第一个匹配到的节点
						RoutingContext,		//如果查询表达式则建立路由环境
						nDepth	))
					{
						if(bFind==FALSE)
						{
							//没有找到则检查下一个隐射连接
							continue;
						}else
						{
							//如果匹配到第一个符合的节点则返回
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
								  IN vector<string> &RoutingExpression,	//路由表达式
								  IN list<_tagCodeObjTree>::iterator & RootCodeObj,	//根代码对象
								  IN BOOL bSearchExpression,		//是否查询存在的表达式
								  OUT BOOL & bFind,				//是否找到
								  OUT list<_tagCodeObjTree>::iterator & RetCodeObj,	//第一个匹配到的节点
								  OUT CodeRoutingContext & RoutingContext,	//如果查询表达式则建立路由环境
								  IN unsigned int nDepth	
								  )
{	
	//初步计算代码路径
	//ROOT
	vector<string> RoutingExpressionArray=RoutingExpression;
	list<_tagCodeObjTree>::iterator RoutingDst=RootCodeObj;



	if(RoutingExpressionArray.size()>=3)
	{
		if(RoutingExpressionArray[2]==string("变量数目1"))
		{
			DebugPrint(nDepth,"GetRoutingNode 路由(%s) (%s)  \r\n ",
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
	//查找失败的最深处
	int nMaxDepth=i;
	//邻域查询
	BOOL bFindNeighbor=FALSE;
	//临时积累的父数量 
	unsigned int nParentBack=0;
	for(i=0;i<(int)RoutingExpressionArray.size();)
	{
		//if(bSearchExpression)
		for(unsigned int s=i;s<RoutingExpressionArray.size();)
		{
			i=s;
			if(RoutingExpressionArray[i]!=string("PARENT")) break;

			//如果是PARENT
			//检查节点合法性
			//if(CurRootCodeObj->ObjName!=string("ROOTROOT"))
			{
				CurRootCodeObj=CurRootCodeObj->parent;

				LastChildCodeNode=CurRootCodeObj;

				BeginCode=CurRootCodeObj->ChildObj.begin();

				//RoutingContext.CodeRouting.pop_back();
			}
			/*else
			{
			DebugPrint(nDepth,"MakeCode 表达式 %s 已经路由到根节点 \r\n ",GetRoutingPath(RoutingExpressionArray).c_str());
			}*/

			//
			//RoutingExpressionArray.erase(RoutingExpressionArray.begin());

			s++;
		}

		{
			//暂时不支持再定义表达式
			//if(FindRuleContext(itRuleTmp,itRootRule->second.Array[i].WordVal,nDepth))
			{
				//去匹配表达式
				//do 
				//{

				if(i==(RoutingExpressionArray.size()-1))
				{
					//最后的节点检查是否是叶值
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
					//没有找到符号
					//break;

					//回朔上层节点
					nParentBack=0;
					if(RoutingContext.CodeRouting.size()==0) 
					{
						//没有能够成功路由的节点
						goto faile;
					}

					if(bFindNeighbor)
					{
						//上次没有向上回朔
						RoutingContext.CodeRouting.back().LastChildCodeNode=RoutingContext.CodeRouting.back().CurCodeObjTree->ChildObj.end();
					}else
					{
						//不是回朔查询结果则
						i--;
					}
					for(;;)
					{
						//回朔上层节点
						if(i<0)
						{
							//根节点没找到说明不存在
							goto faile;
						}

						if(RoutingContext.CodeRouting.back().LastChildCodeNode==RoutingContext.CodeRouting.back().CurCodeObjTree->ChildObj.end())
						{

							bFindNeighbor=FALSE;


							if((i>0)&&(RoutingExpressionArray[i-1]==string("PARENT")))
							{
								//如果前面是PARENT
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
							//根节点没找到说明不存在
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
						//继续回朔
					}
					//从回朔到的旁路节点开始搜索
					continue;


					//bFind=FALSE;
					//break;
				}

				if(bFindNeighbor)
				{
					//如果是查邻节点
					RoutingContext.CodeRouting.back().LastChildCodeNode=CurRootCodeObj;
				}
				else
				{
					//子节点查询
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
			//匹配树上词
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
			//匹配树上的值
			}

			//匹配路由表达式*/

		}

	}

	goto sucess;

faile:
	bFind=FALSE;

	DebugPrint(nDepth,"GetRoutingNode_Real 路由(%s) (%s) 失败 \r\n ",
		RootCodeObj->ObjName.c_str(),GetRoutingPath(RoutingExpressionArray).c_str()
		);
	return TRUE;

sucess:
	RetCodeObj=RetCodeObjTmp;
	return TRUE;
}



BOOL CMakeCodeObj::MakeCodeRouting(
										IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
										IN string & LogHead,				//错误日志标头
										IN list<_tagCodeObjTree>::iterator RootCodeObj,
										IN string & RoutingExpression,		//路由表达式
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
		//如果路由到则返回结果
		return TRUE;
	}else
	{
		//不能路由到则开始map路由查询
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
		//不能被路由
		bMatched=FALSE;
		goto fail1;
	}

fail1:
	//不能路由到目标
	DebugPrint(nDepth,"MakeCodeRouting 路由(%s)失败 Make(%s,%s,%s) \r\n ",
		RoutingExpression.c_str(),BeginMake.name.c_str(),
		ProcMake.name.c_str(),EndMake.name.c_str()
		);
	return TRUE;

fail2:
	//遇到语法错误
	return FALSE;
	
}
BOOL CMakeCodeObj::MakeCodeRouting_Real(
								   IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
								   IN string & LogHead,				//错误日志标头
								   IN list<_tagCodeObjTree>::iterator RootCodeObj,
								   IN string & RoutingExpression,		//路由表达式
								   IN ExpressionContext & BeginMake,
								   IN ExpressionContext & ProcMake,
								   IN ExpressionContext & EndMake,
								   OUT BOOL & bMatched,
								   OUT vector<string> & RetCode,
								   OUT BOOL & bRouting,		//是否能够路由到
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
				DebugPrint(nDepth,"MakeCodeRouting_Real 路由 d=%d (%s) Make(%s,%s,%s)成功 \r\n ",
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
						//调用make
						if(RetCodeTmp.size()) 
						{
							//将上次的结果加入到结果
							RetCode.insert(RetCode.end(),RetCodeTmp.begin(),RetCodeTmp.end());
							RetCodeTmp.clear();
						}
						if(MakeCode(RootRootCodeObj,CodeObj,ProcMake,bMatched,RetCodeTmp,nDepth<<1,nRootDepthMe)==FALSE) goto failed;

						i++;
					}
					else
					{
						//正常结束
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
			DebugPrint(nDepth,"MakeCodeRouting_Real 路由 d=%d (%s) Make(%s,%s,%s)成功 \r\n ",
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
	DebugPrint(nDepth,"MakeCodeRouting_Real 路由 d=%d (%s=%s)成功 Make(%s,%s,%s)失败 \r\n ",
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
		AfxMessageBox("打开文件失败");
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
表达式定义
表达式为真，则代码返回给上层表达式
MAKE_N<代码节点,第一个代码节点MAKE,中间的过程代码节点MAKE,末尾的代码节点MAKE> 穷举所有符合代码节点表达式的代码节点，然后交由后面的MAKE表达式处理
MAKE_ONE<代码节点,代码节点MAKE> 只MAKE处理第一个符合代码节点表达式的代码节点 
MAKE_ADD<MAKE表达式字符串的表达式名称>	添加或者设置一条表达式
WORD(x) 返回字符串，如果字符串中有"则需要在前面加\
NOT<MAKE表达式> 如果MAKE表达式成功则返回假，用于条件控制执行，并将MAKE表达式的结果抛弃不加入结果链
IF<MAKE表达式> 如果MAKE表达式成功则返回真，用于条件控制执行，并将MAKE表达式的结果抛弃不加入结果链
DEBUGOUT<"字符串">	打印字符串
DEBUGOUT<MAKE表达式> 打印MAKE表达式生成的结果，并影响参与计算的表达式真假状态
MAKE_TO<MAKE表达式,保存目标对象名> 如果MAKE表达式为真则将其结果保存到目标对象名指定的对象中去
MAKE_MAKECODE<需要解析处理的源对象,处理源对象的脚本对象>  对象可以是一个MAKE表达式返回的字符串，也可以直接是一个对象字符串如文件路径
MAKE_CODE_TO<源对象,处理源对象的MAKE表达式,输出对象> 对象可以是文件路径字符串或者是一个MAKE表达式结果,处理源对象的MAKE表达式 对 源对象分析处理后的结果存入 输出对象
MAKE_BIND_ROUTING<被绑定的虚路径名字符串,需要映射到虚路径的真实路径字符串>
+  表达式结果连接并流程控制 A+B 如果A为真则执行B，AB都为真则返回真
&  表达式结果连接并流程控制 A&B 不管A执行是否成功，都需执行B, AB只要有一个为真则返回真
#  表达式结果连接并流程控制 A#B 与+意义相同只是返回的结果不是用句连接，而是词的融合
|  表达式结果连接并流程控制 A|B	如果A为真，则不执行B，跳过B执行下一个表达式，如果A为假，则执行B,返回结果为A或B,返回的代码是真值的那个表达式MAKE结果
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
	unsigned int iCommand=0;//表达式头
	bMatched=FALSE;
	BOOL bFailed=FALSE; //系统异常，比如规则表达式异常
	BOOL bMatch=FALSE;
	BOOL bMatchTmp=FALSE;
	BOOL bLastMacthWord=FALSE;
	Context.nDestLen=0;
	string strLastFalg="one";//最后一次表达式符号
	//BOOL bFailNoChangeSucess=FALSE;//匹配不改变匹配成功标志
	//BOOL bFindKeyword=FALSE;
	ExpressionContext CurContext;
	list<_tagCodeObjTree>::iterator CodeObjTmp;
	vector<string> MakeCodeTmp,MakeCodeTmp1,MakeCodeTmp2;
	//4个表达式变量用于命令解析结算
	//本次匹配词数组坐标
	//unsigned int nWordPos=Context.nBeginPos;

	//用于Make生成代码树
	CGenerateCodeTree CodeTree;
	ExpressionContext BeginMake;
	ExpressionContext ProcMake;
	ExpressionContext EndMake;

	CObjExpression::ParseRuleMapType::iterator itRuleContext,itRuleContext1,itRuleContext2,itRuleContext3,itRuleContext4;


	if(string("MAKE_是否是字符串型别char数组")==Context.name.c_str())
	{
		//if(OrgCodeObj->ObjVal==string("MultiplyTransform"))
		{
			DebugPrint(nDepth,"表达式 (%s) %d \r\n ",
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

		if(Context.Array[iCommand].WordType==string("词型")
			)
		{
			if((bLastMacthWord==TRUE))
			{
				//语法错误
				DebugPrint(nDepth,"表达式 (%s) 表达式词异常位置(%d %s)\r\n  ",
					Context.name.c_str(),iCommand,
					Context.Array[iCommand].WordVal.c_str());

				bFailed=TRUE;
				break;
			}
			//上次必须是第一次匹配或者是一次符号匹配
			bLastMacthWord=TRUE;
			bMatchTmp=FALSE;
			//找到要匹配的上下文
			//内置表达式计算

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
				if(Context.Array[iCommand+2].WordType==string("字符串型")&&
					Context.Array[iCommand+4].WordType==string("字符串型"))
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
							DebugPrint(nDepth,"MAKE_ADD 表达式 (%s) 异常",
								MakeCodeTmp1[0].c_str());

							bFailed=TRUE;
							break;
						}
					}
					else
					{
						DebugPrint(nDepth,"MAKE_ADD 表达式 (%s) make失败",
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
				if(Context.Array[iCommand+2].WordVal==string("MAKE类声明基类虚拟函数声明111"))
				{
					DebugPrint(nDepth,"1234");
				}
				if(Context.Array[iCommand+2].WordType==string("字符串型"))
				{
					Context.pCodeTree->GetRoutingPath(OrgCodeObj,Rootpath);
					DebugPrint(nDepth,"==ROOTPATH(%s)==\r\nDEBUGOUT 字符串(%s)\r\n ",
						Rootpath.c_str(),Context.Array[iCommand+2].WordVal.c_str());

				}else if(Context.Array[iCommand+2].WordType==string("词型"))
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
							DebugPrint(nDepth,"==ROOTPATH(%s)==\r\nDEBUGOUT 表达式 %s make结果(%s)\r\n ",
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
				//得到codeobjtree

				MakeCodeTmp2.clear();
				MakeCodeTmp1.clear();

				//生成代码并保存到目标
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
						if(Context.Array[iCommand+4].WordType==string("字符串型"))
						{
							SaveCodeToObj(Context,Context.Array[iCommand+4].WordVal,MakeCodeTmp1);
						}
						else if(Context.Array[iCommand+4].WordType==string("词型"))
						{
							//得到目标路径字符串
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
									DebugPrint(nDepth,"MakeCode MAKE_TO 路径表达式 %s make 失败 \r\n ",
										Context.Array[iCommand+4].WordVal.c_str());
									bFailed=TRUE;
									break;
								}
							}
							else
							{
								DebugPrint(nDepth,"MakeCode MAKE_TO 路径表达式 %s 没有找到 \r\n ",
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
						DebugPrint(nDepth,"MakeCode MAKE_TO %s 路径表达式 %s 生成代码失败\r\n ",
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
				//得到codeobjtree

				MakeCodeTmp2.clear();
				MakeCodeTmp1.clear();
				{
					string InCodeObj;
					string InMakeObj;
					if(Context.Array[iCommand+2].WordType==string("字符串型"))
					{
						InCodeObj=Context.Array[iCommand+2].WordVal;
					}
					else if(Context.Array[iCommand+2].WordType==string("词型"))
					{
						//得到目标路径字符串
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
								DebugPrint(nDepth,"MakeCode MAKE_MAKECODE 输入代码路径表达式 %s make 失败\r\n  ",
									Context.Array[iCommand+2].WordVal.c_str());
								bFailed=TRUE;
								break;
							}
						}
						else
						{
							DebugPrint(nDepth,"MakeCode MAKE_MAKECODE 输入代码路径表达式 %s 没有找到\r\n  ",
								Context.Array[iCommand+2].WordVal.c_str());
							bFailed=TRUE;
							break;
						}
					}

					if(Context.Array[iCommand+4].WordType==string("字符串型"))
					{
						InMakeObj=Context.Array[iCommand+4].WordVal;
					}
					else if(Context.Array[iCommand+4].WordType==string("词型"))
					{
						//得到目标路径字符串
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
								DebugPrint(nDepth,"MakeCode MAKE_MAKECODE 输入make路径表达式 %s make 失败\r\n  ",
									Context.Array[iCommand+4].WordVal.c_str());
								bFailed=TRUE;
								break;
							}
						}
						else
						{
							DebugPrint(nDepth,"MakeCode MAKE_MAKECODE 输入make路径表达式 %s 没有找到\r\n  ",
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
						DebugPrint(nDepth,"MakeCode MAKE_MAKECODE 输入make AddExpression失败 %s \r\n  ",
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
						DebugPrint(nDepth,"MakeCode MAKE_MAKECODE 表达式%s 生成CodeTree失败\r\n ",
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
				//得到codeobjtree

				MakeCodeTmp2.clear();
				MakeCodeTmp1.clear();
				{
					string InCodeObj;
					if(Context.Array[iCommand+2].WordType==string("字符串型"))
					{
						InCodeObj=Context.Array[iCommand+2].WordVal;
					}
					else if(Context.Array[iCommand+2].WordType==string("词型"))
					{
						//得到目标路径字符串
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
								DebugPrint(nDepth,"MakeCode MAKE_CODE_TO 输入代码路径表达式 %s make 失败\r\n  ",
									Context.Array[iCommand+2].WordVal.c_str());
								bFailed=TRUE;
								break;
							}
						}
						else
						{
							DebugPrint(nDepth,"MakeCode MAKE_CODE_TO 输入代码路径表达式 %s 没有找到\r\n  ",
								Context.Array[iCommand+2].WordVal.c_str());
							bFailed=TRUE;
							break;
						}
					}
					CodeTree.m_RootCodeObjList.clear();
					CodeTree.BindObjExpressionMgr(m_ObjExpressionMgr);
					if(GetSearchCodeToCodeObjTree(InCodeObj,CodeTree)==FALSE)
					{
						DebugPrint(nDepth,"MakeCode MAKE_CODE_TO 表达式%s 生成CodeTree失败\r\n ",
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

				//生成代码并保存到目标
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
						if(Context.Array[iCommand+6].WordType==string("字符串型"))
						{
							SaveCodeToObj(Context,Context.Array[iCommand+6].WordVal,MakeCodeTmp1);
						}
						else if(Context.Array[iCommand+6].WordType==string("词型"))
						{
							//得到目标路径字符串
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
									DebugPrint(nDepth,"MakeCode MAKE_TO 路径表达式 %s make 失败 \r\n ",
										Context.Array[iCommand+6].WordVal.c_str());
									bFailed=TRUE;
									break;
								}
							}
							else
							{
								DebugPrint(nDepth,"MakeCode MAKE_TO 路径表达式 %s 没有找到 \r\n ",
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
						DebugPrint(nDepth,"MakeCode MAKE_TO 路径表达式 %s 生成代码失败\r\n ",
							Context.Array[iCommand+6].WordVal.c_str());
						bFailed=TRUE;
						break;
					}


					iCommand+=8;
					continue;
				}
			}
			//路由代码型别
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
						DebugPrint(nDepth,"表达式 (%s) %d \r\n ",
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

			//用户自定义表达式计算
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


			//异常规则关键字

			bFailed=TRUE;

			if(iCommand>Context.nNumWord)
			{
				DebugPrint(nDepth,"MakeCode 表达式 %s 边界对齐失败 \r\n ",Context.name.c_str());
				break;
			}

			DebugPrint(nDepth,"MakeCode 表达式 (%s) 异常位置(%d %s)\r\n  ",
				Context.name.c_str(),iCommand,
				Context.Array[iCommand].WordVal.c_str());

			break;

		}


		//第一次尚未参加符号计算
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

		//符号计算
		// + |为条件控制代码合成 &为无条件代码合并，只有有一个为真则表达式为真
		if(Context.Array[iCommand].WordVal==COMMANDEND)
		{
			//正常结束
			//与最后一次符号做结果计算


			//匹配成功结束
			/*
			if(bMatch)
			{
			DebugPrint(nDepth,"Make 表达式 (%s)  %s 成功Make结束\r\n ",
			Context.name.c_str(),Context.Array[iCommand].WordVal.c_str());
			}*/


			break;
		}
		else if(Context.Array[iCommand].WordType==string("符号型"))
		{
			if((bLastMacthWord==FALSE))
			{
				//语法错误
				DebugPrint(nDepth,"Make 表达式 (%s) 异常符号位置(%d %s)\r\n  ",
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
					//表达式匹配失败
					//DebugPrint(nDepth,"表达式 %s 匹配失败 \r\n ",Context.name.c_str());
					break;
				}
				iCommand+=1;
				continue;
			}

			//匹配计算类似+
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
					//表达式匹配失败
					//DebugPrint(nDepth,"表达式 %s 匹配失败 \r\n ",Context.name.c_str());
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
					//上次已经成功，无需再次匹配
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
					//继续匹配吧
					//失败不增加步进
					iCommand+=1;
				}

				continue;
			}

			//匹配计算类似 |
			if(
				(string("&")==Context.Array[iCommand].WordVal)
				)
			{
				strLastFalg="&";
				if(!bMatch)
				{
					//上次不成功则改变匹配标志
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
	DebugPrint(nDepth,"Make nRootDepth=%d 表达式 (%s) bFailed=%x,bMatched=%x,iCommand=%d,Comnamd=%s \r\n ",
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
