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
									  IN string & LogHead,			//������־��ͷ
									  IN string & BeginExpression,	//��ʼ�ָ������ʽ��
									  IN string & EndExpression,	//��ֹ�ָ������ʽ��
									  IN unsigned int  nParseBegin, //��������ʼλ��
									  IN unsigned int  nParseEnd, //��������ʼλ��
									  OUT unsigned int & nPackageBegin,
									  OUT unsigned int & nPackageEndBegin,
									  OUT unsigned int & nPackageEndEnd,
									  OUT BOOL & bMatched,		//�Ƿ�ƥ�䵽
									  IN unsigned int nDepth)
{
	CObjExpression::ParseRuleMapType::iterator itBeginContext,itEndContext;
	ExpressionContext BeginContext,EndContext;
	CodeObjTree BeginCodeObj,EndCodeObj;
	unsigned int nStackDepth=0;	//��ʼ����ջ��ȡ�
	bMatched=FALSE;
	BOOL bMatched1=FALSE;
	unsigned int  nWordPos=nParseBegin; //�ʷ��������ꡣ
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
					

					if((m_WordArray[BeginContext.nBeginPos].WordType==string("����"))) break;
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
							//û��ƥ�䵽��ͷ��β��
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
						DebugPrint(nDepth,"CalculatePackage %s ��û��ƥ�䵽β \r\n ",LogHead);
						return FALSE;
					}
				}

				

				DebugPrint(nDepth,"CalculatePackage %s ���쳣�жϽ��� \r\n ",LogHead.c_str());

				return TRUE;
			}
			else
			{
				DebugPrint(nDepth,"CalculatePackage %s ���쳣�жϽ��� \r\n ",LogHead.c_str());

				return TRUE;
			}
		}
	}
	else
	{
		DebugPrint(nDepth,"CalculatePackage ���ʽ����δ���� (%s %s) \r\n ",
			BeginExpression.c_str(),EndExpression.c_str());
	}
	return FALSE;
}

BOOL CGenerateCodeTree::WordMacth(
							  IN string & LogHead,				//������־��ͷ
							  vector<WordSet>	&  WordArray,	//���ʽ�ʱ�
							  IN unsigned int  nWordBegin,		//��������ʼλ��
							  IN unsigned int  nParseBegin,		//����Ŀ�괮��ʼλ��
							  IN BOOL bMatchCase,				//�Ƿ����Сд
							  OUT unsigned int  & nWordEndEnd,	//WORD��������һ����λ��
							  OUT unsigned int  & bMatched,		//��ʾ�Ƿ�ɹ�ƥ��
							  IN unsigned int nDepth)
{
	unsigned int nCommand=nWordBegin;
	bMatched=FALSE;
	string strMatch;
	for(;nCommand<WordArray.size();nCommand++)
	{
		if(WordArray[nCommand].WordVal!=string("\\"))
		{
			//����ϵͳͨ���
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
	CodeObjTree CodeObjTmp,CodeObjTmp1;
	if(nDepth>=0xf0000000) 
	{
		DebugPrint(nDepth,"Parse �������ջ���ʽ (%s) \r\n ",
			Context.name.c_str()
			);
		return FALSE;
	}

	//4�����ʽ�������������������
	//����ƥ�����������
	unsigned int nWordPos=Context.nBeginPos;
	CObjExpression::ParseRuleMapType::iterator itRuleContext,itRuleContext1,itRuleContext2,itRuleContext3;
	
	RetCodeObj.nBeginPos=Context.nBeginPos;
	RetCodeObj.nEndPos=Context.nBeginPos;

	/*
	if(Context.nBeginPos>=687)
		{
			if((string("������������")!=Context.name)
				&&(string("����������ʼ")!=Context.name))
			{
			DebugPrint(nDepth,"���ʽ (%s) %d \r\n ",
					Context.name.c_str(),bMatch
					);
			}
		}*/
	if(string("���������Ŀ")==Context.name)
	{
	
		DebugPrint(nDepth,"���ʽ (%s) %d \r\n ",
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


		if(Context.Array[iCommand].WordType==string("����")
			)
		{
			if((bLastMacthWord==TRUE))
			{
				//�﷨����
				DebugPrint(nDepth,"���ʽ (%s) ���ʽ���쳣λ��(%d %s) \r\n ",
				Context.name.c_str(),iCommand,
				Context.Array[iCommand].WordVal.c_str());

				bFailed=TRUE;
				break;
			}
			//�ϴα����ǵ�һ��ƥ�������һ�η���ƥ��
			bLastMacthWord=TRUE;
			bMatchTmp=bMatch;
			//�ҵ�Ҫƥ���������
			//���ñ��ʽ����
			if(
				(string("NULL")==Context.Array[iCommand].WordVal)
				&&(string("<")==Context.Array[iCommand+1].WordVal)
				&&(string(">")==Context.Array[iCommand+3].WordVal)
				)
			{
				//ƥ��ɹ��Ļ�����RetPocket���ӽڵ㣬ƥ�䲻�ɹ����������ڵ�
				//�����Ƿ�ƥ��ɹ������ı�����־λ
				//bFailNoChangeSucess=TRUE;
				//bFindKeyword=TRUE;
				if(FindRuleContext(itRuleContext,Context.Array[iCommand+2].WordVal,nDepth))
				{
					CurContext=itRuleContext->second;
					CurContext.nEndPos=Context.nEndPos;
					CurContext.nBeginPos=nWordPos;
					//����ʱ��ƥ��ɹ���־�������������ʽ����������
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
					//��������㣬����һ������
					
				}
				else
				{
					bFailed=TRUE;
					break;
				}
				iCommand+=4;
				//�������ĩβ��������һ������
				if(iCommand!=Context.nNumWord)
				{
					iCommand++;
					bLastMacthWord=FALSE;
				}
				
				continue;
			}

			if(
				(string("��")==Context.Array[iCommand].WordVal)
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
					//���������
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
							//ƥ������ʽ
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
								DebugPrint(nDepth,"���ʽ %s ��(%s,%s,%s)ƥ��ɹ�begin=%d end=%d endedd=%d \r\n ",
									Context.name.c_str(),
									Context.Array[iCommand+2].WordVal.c_str(),
									Context.Array[iCommand+4].WordVal.c_str(),
									Context.Array[iCommand+6].WordVal.c_str(),
									PacketContext.nBeginPos,PacketContext.nEndPos,WordPostmp);
							}
							else
							{
								DebugPrint(nDepth,"�����ʽ %s ƥ��ʧ�� \r\n ",PacketContext.name.c_str());
								
							}
						}
						else
						{
							//Ŀ�괮û��ƥ�䵽
							DebugPrint(nDepth,"���߽���ʽ %s ƥ��ʧ�� \r\n ",Context.name.c_str());
							bMatchTmp=bMatchPackage;
						}
						
					}
					else
					{
						//�����﷨��������
						bFailed=TRUE;
						break;
					}

				}
				else
				{
					//�����﷨��������
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

					ExpressionContext CycCtlContext;//ѭ�����Ʊ��ʽ
					CycCtlContext=itRuleContext1->second;
					CycCtlContext.nEndPos=Context.nEndPos;
					CycCtlContext.nBeginPos=nWordPos;

					
					for(;;)
					{
						//ƥ�������ʽʧ��
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
							//ѭ������
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
								//ѭ�����Ʊ��ʽƥ�����ǳɹ������ƥ��
								RetCodeObj.ChildObj.push_back(CodeObjTmp1);

								nWordPos+=CycCtlContext.nDestLen;
								CurContext.nBeginPos=nWordPos;
							}
							else
							{
								//ѭ�����Ʊ��ʽƥ������ʧ�����ʾ˳��ƥ����ֹ
								//RetCodeObj.ChildObj.push_back(CodeObjTmp1);

								bMatchTmp=TRUE;
								break;
							}
						}
						else
						{
							//ƥ��ʧ��
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
				(string("����")==Context.Array[iCommand].WordVal)
				||(string("������")==Context.Array[iCommand].WordVal)
				||(string("����")==Context.Array[iCommand].WordVal)
				||(string("������")==Context.Array[iCommand].WordVal)
				||(string("�ַ�����")==Context.Array[iCommand].WordVal)
				||(string("�ַ���")==Context.Array[iCommand].WordVal)
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

			
			//�û��Զ�����ʽ����
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


			//�쳣����ؼ���

			bFailed=TRUE;

			if(iCommand>Context.nNumWord)
			{
				DebugPrint(nDepth,"���ʽ %s �߽����ʧ�� \r\n  ",Context.name.c_str());
				break;
			}

			DebugPrint(nDepth,"���ʽ (%s) �޷�ƥ����ʽ λ��(%d %s) \r\n  ",
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
					//�Ѿ��ɹ��������ٴ�ƥ��
					bMatch=bMatchTmp;
					Context.nDestLen=nWordPos-Context.nBeginPos;
				}
			}
			
		}

		//���ż���
		if(Context.Array[iCommand].WordVal==COMMANDEND)
		{
			//��������
			//ƥ��ɹ�����
			if(bMatch)
			{
				DebugPrint(nDepth,"���ʽ (%s) λ�� %d %s �ɹ�ƥ����� \r\n ",
					Context.name.c_str(),nWordPos,Context.Array[iCommand].WordVal.c_str());
			}
			break;
		}
		else if(Context.Array[iCommand].WordType==string("������"))
		{
			if((bLastMacthWord==FALSE))
			{
				//�﷨����
				DebugPrint(nDepth,"���ʽ (%s) ����λ���쳣(%d %s) \r\n ",
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
					//���ʽƥ��ʧ��
					//DebugPrint(nDepth,"���ʽ %s ƥ��ʧ�� ",Context.name.c_str());
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
					//�ϴ��Ѿ��ɹ�������ƥ�����ı��ʽ
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
					//����ƥ���
					//ʧ�ܲ����Ӳ���
					bLastMacthWord=FALSE;
					iCommand+=1;
				}
				
				continue;
			}
			//������֧�ַ��� 
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
		DebugPrint(nDepth,"���ʽ (%s) bMatch=%d,len=%d pos=%d \r\n ",
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
		OutputDebugStringA("����������");
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
		AfxMessageBox("���ļ�ʧ��");
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