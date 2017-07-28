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
#include "GenerateCodeTree.h"

CGenerateCodeTree::CGenerateCodeTree(void)
{
}

CGenerateCodeTree::~CGenerateCodeTree(void)
{
}
BOOL CGenerateCodeTree::BindObjExpressionMgr(CObjExpression * mgr)
{
	m_ObjExpressionMgr=mgr;
	return TRUE;
}
BOOL CGenerateCodeTree::FindRuleContext(CObjExpression::ParseRuleMapType::iterator & itRuleContext,string & RuleName,unsigned int nDepth)
{
	
	return m_ObjExpressionMgr->FindRuleContext(itRuleContext,RuleName,nDepth);

}

BOOL CGenerateCodeTree::GetCommandTypeAndLen(
	IN ExpressionContext & Context,
	IN unsigned int nCommand,
	OUT string & Command,
	OUT unsigned int & nCommandLen,
	IN unsigned int nDepth
	)
{
	return m_ObjExpressionMgr->GetCommandTypeAndLen(Context,nCommand,Command,nCommandLen,nDepth);

}
BOOL CGenerateCodeTree::CalculatePackage(
									  IN string & LogHead,			//错误日志标头
									  IN string & BeginExpression,	//开始分隔符表达式名
									  IN string & EndExpression,	//终止分隔符表达式名
									  IN unsigned int  nParseBegin, //解析串起始位置
									  IN unsigned int  nParseEnd, //解析串起始位置
									  OUT unsigned int & nPackageBegin,
									  OUT unsigned int & nPackageEndBegin,
									  OUT unsigned int & nPackageEndEnd,
									  OUT BOOL & bMatched,		//是否匹配到
									  IN unsigned int nDepth)
{
	CObjExpression::ParseRuleMapType::iterator itBeginContext,itEndContext;
	ExpressionContext BeginContext,EndContext;
	CodeObjTree BeginCodeObj,EndCodeObj;
	unsigned int nStackDepth=0;	//起始串堆栈深度。
	bMatched=FALSE;
	BOOL bMatched1=FALSE;
	unsigned int  nWordPos=nParseBegin; //词法解析坐标。
	if(FindRuleContext(itBeginContext,BeginExpression,nDepth))
	{
		if(FindRuleContext(itEndContext,EndExpression,nDepth))
		{
			BeginContext=itBeginContext->second;
			EndContext=itEndContext->second;

			BeginContext.nDestLen=0;
			BeginContext.nBeginPos=nParseBegin;
			BeginContext.nEndPos = nParseEnd;
			EndContext.nEndPos = nParseEnd;
			if(Parse(BeginContext,BeginCodeObj,bMatched1,nDepth)==FALSE)
			{
				return FALSE;
			}
			if(bMatched1)
			{
				nStackDepth++;
				
				BeginContext.nBeginPos+=BeginContext.nDestLen;
				BeginContext.nDestLen=0;
				EndContext.nBeginPos=BeginContext.nBeginPos;
				
				nPackageBegin=BeginContext.nBeginPos;

				for(;(nStackDepth!=0);)
				{
					BeginContext.nDestLen=0;
					EndContext.nBeginPos=BeginContext.nBeginPos;
					

					if((m_WordArray[BeginContext.nBeginPos].WordType==string("结束"))) break;
					if(Parse(BeginContext,BeginCodeObj,bMatched1,nDepth)==FALSE)
					{
						return FALSE;
					}

					if(bMatched1)
					{
						nStackDepth++;
						BeginContext.nBeginPos+=BeginContext.nDestLen;
						
					}else 
					{
						if(Parse(EndContext,EndCodeObj,bMatched1,nDepth)==FALSE)
						{
							return FALSE;
						}
						if(bMatched1)
						{
							nStackDepth--;
							nPackageEndBegin=EndContext.nBeginPos;
							BeginContext.nBeginPos+=EndContext.nDestLen;
							nPackageEndEnd=BeginContext.nBeginPos;
						}
						else
						{
							//没有匹配到包头包尾则
							BeginContext.nBeginPos++;
						}
						
					}
					if(nStackDepth==0)
					{
						bMatched=TRUE;
						return TRUE;
					}

					if(BeginContext.nBeginPos>=m_WordArray.size()) 
					{
						DebugPrint(nDepth,"CalculatePackage %s 包没有匹配到尾 \r\n ",LogHead);
						return FALSE;
					}
				}

				

				DebugPrint(nDepth,"CalculatePackage %s 包异常中断结束 \r\n ",LogHead.c_str());

				return TRUE;
			}
			else
			{
				DebugPrint(nDepth,"CalculatePackage %s 包异常中断结束 \r\n ",LogHead.c_str());

				return TRUE;
			}
		}
	}
	else
	{
		DebugPrint(nDepth,"CalculatePackage 表达式符号未定义 (%s %s) \r\n ",
			BeginExpression.c_str(),EndExpression.c_str());
	}
	return FALSE;
}

BOOL CGenerateCodeTree::WordMacth(
							  IN string & LogHead,				//错误日志标头
							  vector<WordSet>	&  WordArray,	//表达式词表
							  IN unsigned int  nWordBegin,		//解析串起始位置
							  IN unsigned int  nParseBegin,		//解析目标串起始位置
							  IN BOOL bMatchCase,				//是否检查大小写
							  OUT unsigned int  & nWordEndEnd,	//WORD结束的下一个词位置
							  OUT unsigned int  & bMatched,		//表示是否成功匹配
							  IN unsigned int nDepth)
{
	unsigned int nCommand=nWordBegin;
	bMatched=FALSE;
	string strMatch;
	for(;nCommand<WordArray.size();nCommand++)
	{
		if(WordArray[nCommand].WordVal!=string("\\"))
		{
			//过滤系统通配符
			strMatch+=WordArray[nCommand].WordVal;
		}
		if(WordArray[nCommand].WordVal==string(")"))
		{
			if(WordArray[nCommand-1].WordVal!=string("\\"))
			{
				nWordEndEnd=nCommand+1;
				if(bMatchCase)
				{
					//strcmp(strMatch.c_str(),)
				}
				return TRUE;
			}
		}
	}
	return TRUE;
}

BOOL CGenerateCodeTree::Parse(IN ExpressionContext & Context,OUT CodeObjTree & RetCodeObj,OUT BOOL & bMatched,
						   IN unsigned int nDepth)
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
	CodeObjTree CodeObjTmp,CodeObjTmp1;
	if(nDepth>=0xf0000000) 
	{
		DebugPrint(nDepth,"Parse 超过最大栈表达式 (%s) \r\n ",
			Context.name.c_str()
			);
		return FALSE;
	}

	//4个表达式变量用于命令解析结算
	//本次匹配词数组坐标
	unsigned int nWordPos=Context.nBeginPos;
	CObjExpression::ParseRuleMapType::iterator itRuleContext,itRuleContext1,itRuleContext2,itRuleContext3;
	
	RetCodeObj.nBeginPos=Context.nBeginPos;
	RetCodeObj.nEndPos=Context.nBeginPos;

	/*
	if(Context.nBeginPos>=687)
		{
			if((string("类声明包结束")!=Context.name)
				&&(string("类声明包开始")!=Context.name))
			{
			DebugPrint(nDepth,"表达式 (%s) %d \r\n ",
					Context.name.c_str(),bMatch
					);
			}
		}*/
	if(string("数组变量数目")==Context.name)
	{
	
		DebugPrint(nDepth,"表达式 (%s) %d \r\n ",
		Context.name.c_str(),bMatch
		);
	}

	for(;iCommand<Context.nNumWord+2;/*iCommand++*/)
	{
		//bFailNoChangeSucess=FALSE;
		
		//bFindKeyword=FALSE;
		CodeObjTmp.ChildObj.clear();
		CodeObjTmp.ObjName="";
		CodeObjTmp.ObjType="";
		CodeObjTmp.ObjVal="";
		CurContext.Array.clear();
		CurContext.name="";
		CurContext.nametype="";
		CurContext.nBeginPos=0;
		CurContext.nDestLen=0;
		CurContext.nEndPos=0;


		if(Context.Array[iCommand].WordType==string("词型")
			)
		{
			if((bLastMacthWord==TRUE))
			{
				//语法错误
				DebugPrint(nDepth,"表达式 (%s) 表达式词异常位置(%d %s) \r\n ",
				Context.name.c_str(),iCommand,
				Context.Array[iCommand].WordVal.c_str());

				bFailed=TRUE;
				break;
			}
			//上次必须是第一次匹配或者是一次符号匹配
			bLastMacthWord=TRUE;
			bMatchTmp=bMatch;
			//找到要匹配的上下文
			//内置表达式计算
			if(
				(string("NULL")==Context.Array[iCommand].WordVal)
				&&(string("<")==Context.Array[iCommand+1].WordVal)
				&&(string(">")==Context.Array[iCommand+3].WordVal)
				)
			{
				//匹配成功的话增加RetPocket树子节点，匹配不成功则不增加树节点
				//无论是否匹配成功都不改变结果标志位
				//bFailNoChangeSucess=TRUE;
				//bFindKeyword=TRUE;
				if(FindRuleContext(itRuleContext,Context.Array[iCommand+2].WordVal,nDepth))
				{
					CurContext=itRuleContext->second;
					CurContext.nEndPos=Context.nEndPos;
					CurContext.nBeginPos=nWordPos;
					//用临时的匹配成功标志不参与其他表达式计算结果计算
					BOOL bMatchNULL;
					if(Parse(CurContext,CodeObjTmp,bMatchNULL,nDepth<<1)==FALSE)
					{
						bFailed=TRUE;
						break;
					}
					//if(bMatchNULL)
					{
						CodeObjTmp.ObjName=CurContext.name;
						CodeObjTmp.ObjType=CurContext.nametype;
						RetCodeObj.ChildObj.push_back(CodeObjTmp);
						nWordPos+=CurContext.nDestLen;
					}
					//
					//bMatchTmp=TRUE;
					//不参与计算，跳过一个符号
					
				}
				else
				{
					bFailed=TRUE;
					break;
				}
				iCommand+=4;
				//如果不是末尾则，则跳过一个符号
				if(iCommand!=Context.nNumWord)
				{
					iCommand++;
					bLastMacthWord=FALSE;
				}
				
				continue;
			}

			if(
				(string("包")==Context.Array[iCommand].WordVal)
				&&(string("<")==Context.Array[iCommand+1].WordVal)
				&&(string(",")==Context.Array[iCommand+3].WordVal)
				&&(string(",")==Context.Array[iCommand+5].WordVal)
				&&(string(">")==Context.Array[iCommand+7].WordVal)
				)
			{
				if(
					FindRuleContext(itRuleContext,Context.Array[iCommand+2].WordVal,nDepth)
					&&FindRuleContext(itRuleContext1,Context.Array[iCommand+4].WordVal,nDepth)
					&&FindRuleContext(itRuleContext2,Context.Array[iCommand+6].WordVal,nDepth))
				{
					//计算包区间
					ExpressionContext PacketContext;
					PacketContext=itRuleContext2->second;
					unsigned int nPackageBegin=0,nPackageLen=0;
					unsigned int WordPostmp=0;
					BOOL bMatchPackage=FALSE;
					if(CalculatePackage(Context.name,itRuleContext->second.name,
						itRuleContext1->second.name, nWordPos, Context.nEndPos,PacketContext.nBeginPos,
						PacketContext.nEndPos,WordPostmp,bMatchPackage,nDepth)
						)
					{
						if(bMatchPackage)
						{
							//匹配包表达式
							PacketContext.nDestLen=0;
							if(Parse(PacketContext,CodeObjTmp,bMatchTmp,nDepth<<1)==FALSE)
							{
								bFailed=TRUE;
								break;
							}
							if(bMatchTmp)
							{
								RetCodeObj.ChildObj.push_back(CodeObjTmp);
								nWordPos=WordPostmp;
								DebugPrint(nDepth,"表达式 %s 包(%s,%s,%s)匹配成功begin=%d end=%d endedd=%d \r\n ",
									Context.name.c_str(),
									Context.Array[iCommand+2].WordVal.c_str(),
									Context.Array[iCommand+4].WordVal.c_str(),
									Context.Array[iCommand+6].WordVal.c_str(),
									PacketContext.nBeginPos,PacketContext.nEndPos,WordPostmp);
							}
							else
							{
								DebugPrint(nDepth,"包表达式 %s 匹配失败 \r\n ",PacketContext.name.c_str());
								
							}
						}
						else
						{
							//目标串没有匹配到
							DebugPrint(nDepth,"包边界表达式 %s 匹配失败 \r\n ",Context.name.c_str());
							bMatchTmp=bMatchPackage;
						}
						
					}
					else
					{
						//规则语法出现问题
						bFailed=TRUE;
						break;
					}

				}
				else
				{
					//规则语法出现问题
					bFailed=TRUE;
					break;
				}
				iCommand+=8;
				continue;
			}

			if(
				(string("N")==Context.Array[iCommand].WordVal)
				&&(string("<")==Context.Array[iCommand+1].WordVal)
				&&(string(",")==Context.Array[iCommand+3].WordVal)
				&&(string(">")==Context.Array[iCommand+5].WordVal)
				)
			{
				if(FindRuleContext(itRuleContext,Context.Array[iCommand+2].WordVal,nDepth)
					&&FindRuleContext(itRuleContext1,Context.Array[iCommand+4].WordVal,nDepth))
				{
					CurContext=itRuleContext->second;
					CurContext.nEndPos=Context.nEndPos;
					CurContext.nBeginPos=nWordPos;

					ExpressionContext CycCtlContext;//循环控制表达式
					CycCtlContext=itRuleContext1->second;
					CycCtlContext.nEndPos=Context.nEndPos;
					CycCtlContext.nBeginPos=nWordPos;

					
					for(;;)
					{
						//匹配规则表达式失败
						CodeObjTmp.ChildObj.clear();
						CodeObjTmp.ObjName.clear();
						CodeObjTmp.ObjType.clear();
						CodeObjTmp.ObjVal.clear();

						CodeObjTmp1.ChildObj.clear();
						CodeObjTmp1.ObjName.clear();
						CodeObjTmp1.ObjType.clear();
						CodeObjTmp1.ObjVal.clear();

						if(CurContext.nBeginPos>=CurContext.nEndPos)
						{
							//循环结束
							break;
						}
						if(Parse(CurContext,CodeObjTmp,bMatchTmp,nDepth)==FALSE)
						{
							bFailed=TRUE;
							break;
						}
						if(bMatchTmp)
						{
							RetCodeObj.ChildObj.push_back(CodeObjTmp);
							nWordPos+=CurContext.nDestLen;
							CurContext.nBeginPos=nWordPos;

							CycCtlContext.nBeginPos=nWordPos;
							BOOL bMatchCycCtl;
							if(Parse(CycCtlContext,CodeObjTmp1,bMatchCycCtl,nDepth)==FALSE)
							{
								bFailed=TRUE;
								break;
							}
							if(bMatchCycCtl)
							{
								//循环控制表达式匹配若是成功则继续匹配
								RetCodeObj.ChildObj.push_back(CodeObjTmp1);

								nWordPos+=CycCtlContext.nDestLen;
								CurContext.nBeginPos=nWordPos;
							}
							else
							{
								//循环控制表达式匹配若是失败则表示顺利匹配终止
								//RetCodeObj.ChildObj.push_back(CodeObjTmp1);

								bMatchTmp=TRUE;
								break;
							}
						}
						else
						{
							//匹配失败
							bMatchTmp=FALSE;
							break;
						}
						
					}
				}
				else
				{
					bFailed=TRUE;
					break;
				}
				iCommand+=6;
				continue;
			}

			if(
				(string("NULL_TRUE")==Context.Array[iCommand].WordVal)
				)
			{
				bMatchTmp=TRUE;
				iCommand+=1;
				continue;
			}

			if(
				(string("NULL_FALSE")==Context.Array[iCommand].WordVal)
				)
			{
				bMatchTmp=FALSE;
				iCommand+=1;
				continue;
			}

			if(
				(string("WORD")==Context.Array[iCommand].WordVal)
				&&(string("(")==Context.Array[iCommand+1].WordVal)
				&&(string(")")==Context.Array[iCommand+3].WordVal)
				)
			{
				bMatchTmp=FALSE;
				if(nWordPos>Context.nEndPos)
				{
					bMatchTmp=FALSE;
					break;
				}
				if(m_WordArray[nWordPos].WordVal==Context.Array[iCommand+2].WordVal)
				{
					bMatchTmp=TRUE;
					RetCodeObj.ObjName=CurContext.name;
					RetCodeObj.ObjType=CurContext.nametype;
					if(RetCodeObj.ObjVal.length())
					{
						RetCodeObj.ObjVal+=string(" ")+Context.Array[iCommand+2].WordVal;
					}
					else
					{
						RetCodeObj.ObjVal=Context.Array[iCommand+2].WordVal;
					}
					//RetCodeObj.ChildObj.push_back(CodeObjTmp);

					nWordPos++;
				}
				iCommand+=4;
				continue;
			}

			if(
				(string("word")==Context.Array[iCommand].WordVal)
				&&(string("(")==Context.Array[iCommand+1].WordVal)
				&&(string(")")==Context.Array[iCommand+3].WordVal)
				)
			{
				bMatchTmp=FALSE;
				if(nWordPos>Context.nEndPos)
				{
					bMatchTmp=FALSE;
					break;
				}
				if(stricmp(m_WordArray[nWordPos].WordVal.c_str(),
					Context.Array[iCommand+2].WordVal.c_str())==0)
				{
					bMatchTmp=TRUE;

					RetCodeObj.ObjName=CurContext.name;
					RetCodeObj.ObjType=CurContext.nametype;

					if(RetCodeObj.ObjVal.length())
					{
						RetCodeObj.ObjVal+=string(" ")+Context.Array[iCommand+2].WordVal;
					}
					else
					{
						RetCodeObj.ObjVal=Context.Array[iCommand+2].WordVal;
					}
					//RetCodeObj.ChildObj.push_back(CodeObjTmp);

					nWordPos++;
					//Context.nDestLen++;
				}
				iCommand+=4;
				continue;
			}

			if(
				(string("词型")==Context.Array[iCommand].WordVal)
				||(string("符号型")==Context.Array[iCommand].WordVal)
				||(string("整型")==Context.Array[iCommand].WordVal)
				||(string("浮点型")==Context.Array[iCommand].WordVal)
				||(string("字符串型")==Context.Array[iCommand].WordVal)
				||(string("字符型")==Context.Array[iCommand].WordVal)
				)
			{
				bMatchTmp=FALSE;
				if(nWordPos>Context.nEndPos)
				{
					bMatchTmp=FALSE;
					break;
				}

				if(m_WordArray[nWordPos].WordType==
					Context.Array[iCommand].WordVal)
				{
					bMatchTmp=TRUE;

					RetCodeObj.ObjName=CurContext.name;
					RetCodeObj.ObjType=CurContext.nametype;
					//RetCodeObj.ObjVal=m_WordArray[nWordPos].WordVal;

					if(RetCodeObj.ObjVal.length())
					{
						RetCodeObj.ObjVal+=string(" ")+m_WordArray[nWordPos].WordVal;
					}
					else
					{
						RetCodeObj.ObjVal=m_WordArray[nWordPos].WordVal;
					}

					//RetCodeObj.ChildObj.push_back(CodeObjTmp);

					nWordPos++;
					//Context.nDestLen++;
				}
				iCommand+=1;
				continue;
			}

			
			//用户自定义表达式计算
			if(FindRuleContext(itRuleContext,Context.Array[iCommand].WordVal,nDepth))
			{
				bMatchTmp=FALSE;
				CurContext=itRuleContext->second;
				CurContext.nBeginPos=nWordPos;
				CurContext.nEndPos=Context.nEndPos;
				if(Parse(CurContext,CodeObjTmp,
					bMatchTmp,nDepth<<1)==FALSE)
				{
					bFailed=TRUE;
					break;
				}
				if(bMatchTmp)
				{
					RetCodeObj.ChildObj.push_back(CodeObjTmp);
					nWordPos+=CurContext.nDestLen;
				}
				iCommand+=1;
				continue;
			}


			//异常规则关键字

			bFailed=TRUE;

			if(iCommand>Context.nNumWord)
			{
				DebugPrint(nDepth,"表达式 %s 边界对齐失败 \r\n  ",Context.name.c_str());
				break;
			}

			DebugPrint(nDepth,"表达式 (%s) 无法匹配表达式 位置(%d %s) \r\n  ",
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
					break;
				}
			}

			if(
				(string("|")==strLastFalg)
				)
			{
				strLastFalg="|";
				if(bMatchTmp)
				{
					//已经成功，无需再次匹配
					bMatch=bMatchTmp;
					Context.nDestLen=nWordPos-Context.nBeginPos;
				}
			}
			
		}

		//符号计算
		if(Context.Array[iCommand].WordVal==COMMANDEND)
		{
			//正常结束
			//匹配成功结束
			if(bMatch)
			{
				DebugPrint(nDepth,"表达式 (%s) 位置 %d %s 成功匹配结束 \r\n ",
					Context.name.c_str(),nWordPos,Context.Array[iCommand].WordVal.c_str());
			}
			break;
		}
		else if(Context.Array[iCommand].WordType==string("符号型"))
		{
			if((bLastMacthWord==FALSE))
			{
				//语法错误
				DebugPrint(nDepth,"表达式 (%s) 符号位置异常(%d %s) \r\n ",
				Context.name.c_str(),iCommand,
				Context.Array[iCommand].WordVal.c_str());

				bFailed=TRUE;
				break;
			}

			//bLastMacthWord=FALSE;

			

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
					//DebugPrint(nDepth,"表达式 %s 匹配失败 ",Context.name.c_str());
					break;
				}
				bLastMacthWord=FALSE;

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
					//上次已经成功，无需匹配后面的表达式
					 bMatch=bMatchTmp;
					 //
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
					 
					 //Context.nDestLen=nWordPos-Context.nBeginPos;
					 //break;
				}
				else
				{
					//继续匹配吧
					//失败不增加步进
					bLastMacthWord=FALSE;
					iCommand+=1;
				}
				
				continue;
			}
			//其他不支持符号 
			break;
		}
	}

	
	bMatched=bMatch;
	Context.nDestLen=nWordPos-Context.nBeginPos;

	if((!bFailed)&&(bMatched))
	{
		RetCodeObj.ObjName=Context.name;
		RetCodeObj.ObjType=Context.nametype;
		RetCodeObj.nBeginPos=Context.nBeginPos;
		RetCodeObj.nEndPos=nWordPos;
		DebugPrint(nDepth,"表达式 (%s) bMatch=%d,len=%d pos=%d \r\n ",
			Context.name.c_str(),bMatch,Context.nDestLen,nWordPos
			);
	}
	

	return !bFailed;
}

BOOL CGenerateCodeTree::ParseDestString(char * pCode)
{
	string code=pCode;
	CTokenizer word(code);
	CodeObjTree RootCodeObj;
	if(word.GetWordArray(m_WordArray)&&m_ObjExpressionMgr->m_RootRuleName.size())
	{
		unsigned int i=0;
		for(;i<m_ObjExpressionMgr->m_RootRuleName.size();i++)
		{
			if (m_ObjExpressionMgr->m_RootRuleName[i].name!=string("ROOT")) continue;
			
			RootCodeObj.ChildObj.clear();
			ExpressionContext Context;
			Context=m_ObjExpressionMgr->m_RootRuleName[i];
			Context.nBeginPos=0;
			Context.nEndPos=m_WordArray.size();
			BOOL bMatch;
			if(Parse(Context,RootCodeObj,bMatch,1)) 
			{
				m_RootCodeObjList.push_back(RootCodeObj);
				LinkCodeTreeParent();

				if(bMatch) return TRUE;
			}
		}
		
		return FALSE;
	}
	return FALSE;
}




BOOL CGenerateCodeTree::LinkCodeTreeParent(list<CodeObjTree>::iterator & itNode,list<CodeObjTree>::iterator & itParent)
{
	list<CodeObjTree>::iterator poschild=itNode->ChildObj.begin();
	itNode->parent=itParent;
	for(;poschild!=itNode->ChildObj.end();poschild++)
	{
		LinkCodeTreeParent(poschild,itNode);
	}

	return TRUE;
}
BOOL CGenerateCodeTree::GetRoutingPath(IN list<_tagCodeObjTree>::iterator  & OrgCodeObj,OUT string & RstPath)
{
	list<_tagCodeObjTree>::iterator itPos=OrgCodeObj;
	list<string> PathArray;
	list<string>::iterator itArray;//=PathArray
	RstPath.clear();

	for(;itPos->ObjName!=string("ROOTROOT");itPos=itPos->parent)
	{
		PathArray.push_front(itPos->ObjName);
	}
	PathArray.push_front(string("ROOTROOT"));
	itArray=PathArray.begin();
	for(;itArray!=PathArray.end();itArray++)
	{
		RstPath+=*itArray;
		RstPath+=string(".");
	}

	if(RstPath.length())
	{
		RstPath.erase(--RstPath.end());
	}
	return TRUE;
}



BOOL CGenerateCodeTree::LinkCodeTreeParent()
{
	list<_tagCodeObjTree>::iterator itPos=m_RootCodeObjList.begin()->ChildObj.begin();
	list<_tagCodeObjTree>::iterator  itRoot=m_RootCodeObjList.begin();
	for(itPos=m_RootCodeObjList.begin()->ChildObj.begin();itPos!=m_RootCodeObjList.begin()->ChildObj.end();itPos++)
	{
		LinkCodeTreeParent(itPos,itRoot);
	}
	return TRUE;
}
BOOL CGenerateCodeTree::PrintCodeTree(list<CodeObjTree>::iterator & itNode,string & szRet,unsigned int nDepth,unsigned int nMaxDepth)
{

	if(nDepth>nMaxDepth) 
	{
		OutputDebugStringA("超过最大深度");
		return FALSE;
	}
	char szHead[128]={0};
	string tmp;
	memset(szHead,'\t',nDepth);
	sprintf(szHead+strlen(szHead),"(%d-%d) ",itNode->nBeginPos,itNode->nEndPos);
	tmp+=szHead;
	tmp+=itNode->ObjName+string("(")+itNode->ObjType+string(",")+itNode->ObjVal+string(")")+string("\r\n");
	szRet+=tmp;
	OutputDebugStringA(tmp.c_str());
	list<CodeObjTree>::iterator poschild=itNode->ChildObj.begin();
	for(;poschild!=itNode->ChildObj.end();poschild++)
	{
		PrintCodeTree(poschild,szRet,nDepth+1,nMaxDepth);
	}
	tmp=szHead;
	tmp+=itNode->ObjName+string("(")+itNode->ObjType+string(",")+itNode->ObjVal+string(")")+string(" End\r\n");
	szRet+=tmp;
	OutputDebugStringA(tmp.c_str());
	return TRUE;
}

BOOL CGenerateCodeTree::PrintCodeTree(OUT string & Code,unsigned int nMaxDepth)
{
	list<_tagCodeObjTree>::iterator itPos=m_RootCodeObjList.begin();
	//for(itPos=m_RootCodeObjList.begin()->ChildObj.begin();itPos!=m_RootCodeObjList.begin()->ChildObj.end();itPos++)
	//{
		PrintCodeTree(itPos,Code,1,nMaxDepth);
	//}
	return TRUE;
}


BOOL CGenerateCodeTree::GetSearchCodeToCodeObjTree(IN string & pFilePath)
{
	HANDLE hFile= CreateFile(pFilePath.c_str(),                // name of the write
		GENERIC_READ,          // open for writing
		FILE_SHARE_WRITE|FILE_SHARE_READ,                      // do not share
		NULL,                   // default security
		OPEN_EXISTING,          // overwrite existing
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template

	if (hFile == INVALID_HANDLE_VALUE) 
	{ 
		DWORD nError=GetLastError();
		AfxMessageBox("打开文件失败");
		return FALSE;
	}


	LARGE_INTEGER size;
	GetFileSizeEx(hFile,&size);
	char * pBuf=new char[size.LowPart+64];
	memset(pBuf,0,size.LowPart+64);

	if(ReadFile(hFile,pBuf,size.LowPart,&size.LowPart,NULL))
	{
		string code=pBuf;
		CTokenizer word(code);
		
		if(word.GetWordArray(m_WordArray)&&m_ObjExpressionMgr->m_RootRuleName.size())
		{
			unsigned int i=0;
			ExpressionContext Context;
			Context=m_ObjExpressionMgr->m_RootRuleName[i];
			Context.nBeginPos=0;
			Context.nEndPos = m_WordArray.size();
			CodeObjTree  RetRootCodeObj;

			RetRootCodeObj.ObjName=string("ROOTROOT");
			RetRootCodeObj.ObjType=string("ROOTROOT");
			RetRootCodeObj.nBeginPos=0;
			RetRootCodeObj.nEndPos=m_WordArray.size();

			m_RootCodeObjList.push_back(RetRootCodeObj);

			list<_tagCodeObjTree>::iterator itRoot=m_RootCodeObjList.begin();
			for(;;)
			{
				for(i=0;i<m_ObjExpressionMgr->m_RootRuleName.size();i++)
				{
					if (m_ObjExpressionMgr->m_RootRuleName[i].name!=string("ROOT")) continue;
					
					RetRootCodeObj.ChildObj.clear();
					
					BOOL bMatch;
					if(Parse(Context,RetRootCodeObj,bMatch,1)) 
					{
		
						if(bMatch)
						{
							itRoot->ChildObj.push_back(RetRootCodeObj);
							Context.nBeginPos=RetRootCodeObj.nEndPos;
						}
						else
						{
							Context.nBeginPos++;
							if (Context.nBeginPos == 0x58)
							{
								AfxMessageBox("a");
							}
						}
						if(Context.nBeginPos>=m_WordArray.size())
						{
							if(itRoot->ChildObj.size())
							{
								goto sucess;
							}
							else
							{
								goto failed;
							}
						}
					}
					else
					{
						goto failed;
					}

				}
			}
			
			goto failed;
		}
		goto failed;
	}


failed:
	CloseHandle(hFile);
	delete [] pBuf;
	return FALSE;

sucess:
	CloseHandle(hFile);
	delete [] pBuf;

	LinkCodeTreeParent();
	return TRUE;
}