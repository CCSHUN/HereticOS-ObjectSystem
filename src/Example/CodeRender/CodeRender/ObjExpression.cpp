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
#include "ObjExpression.h"
#include "Tokenizer.h"
#include <algorithm>


CObjExpression::CObjExpression(void)
{
	//m_iParse=0;
}

CObjExpression::~CObjExpression(void)
{
}

BOOL CObjExpression::ReadCommandLine(const char * pFilePath ,vector<char *> & pCommandArray,char ** pBuf)
{
	HANDLE hFile= CreateFile(pFilePath,                // name of the write
		GENERIC_READ,          // open for writing
		FILE_SHARE_WRITE|FILE_SHARE_READ,                      // do not share
		NULL,                   // default security
		OPEN_EXISTING,          // overwrite existing
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template

	if (hFile == INVALID_HANDLE_VALUE) 
	{ 
		DWORD nError=GetLastError();
		//AfxMessageBox("���ļ�ʧ��");
		return FALSE;
	}


	LARGE_INTEGER size;
	GetFileSizeEx(hFile,&size);
	*pBuf=new char[size.LowPart];

	char * pStr=*pBuf;
	if(ReadFile(hFile,pStr,size.LowPart,&size.LowPart,NULL))
	{
		unsigned int pos=0;
		for(;pos<size.LowPart;pos++)
		{
			if(((*pBuf)[pos]=='\r')&&((*pBuf)[pos+1]=='\n'))
			{
				(*pBuf)[pos]=0;
				if(pStr[0]!=0)
				{
					pCommandArray.push_back(pStr);
				}
				pStr=*pBuf+pos+2;
			}
		}

		pCommandArray.push_back((char *)NULL);
	}

	CloseHandle(hFile);

	return TRUE;
}

BOOL CObjExpression::AddExpression(const char * pExpressionFilePath,const char * pExpEnvPath )
{
	vector<char *>  pCommandArray;
	char * pBuf;
	BOOL bReadFile=TRUE;
	string szCurrentPath = pExpressionFilePath;
	bReadFile=ReadCommandLine(pExpressionFilePath,pCommandArray,&pBuf);
	
	if(bReadFile==FALSE)
	{
		//DebugPrint(1,"AddExpression �ļ��򿪴���(%s) \r\n ",pExpressionFilePath);

		szCurrentPath = pExpEnvPath;
		szCurrentPath += pExpressionFilePath;
		bReadFile = ReadCommandLine(szCurrentPath.c_str(), pCommandArray, &pBuf);

		if (bReadFile == FALSE)
		{
			DebugPrint(1, "AddExpression ExpEnvPath �ļ��򿪴���(%s) \r\n ", szCurrentPath.c_str());

			return FALSE;
		}
		
	}
	
	if (!CTokenizer::FilePathToDirPath(szCurrentPath))
	{
		DebugPrint(1, "AddExpression ExpEnvPath (%s) ·���Ƿ�\r\n ", szCurrentPath.c_str());
	}
	unsigned int nExpressionEnv = m_ExpEnvMap.size() + 1;
	_tagExpEnv Env;
	Env.szExpEnvPath = pExpEnvPath;
	m_ExpEnvMap[nExpressionEnv] = Env;

	BOOL bRet =AddExpression(&pCommandArray[0], nExpressionEnv);
	delete [] pBuf;
	DebugPrint(1, "AddExpression File (%s) (%s) %s\r\n ",
		szCurrentPath.c_str(),
		pExpressionFilePath,
		bRet?"OK...":"FALSE...");
	return bRet;
}

BOOL CObjExpression::AddExpression(vector<string> & ExpressionArray, unsigned int nExpEnv)
{
	if (ExpressionArray.size()==0) return FALSE;
	
	vector<char *> CharExpressionArray;
	vector<string>::iterator itPos=ExpressionArray.begin();
	for(;itPos!=ExpressionArray.end();itPos++)
	{
		CharExpressionArray.push_back((char *)itPos->c_str());
	}
	CharExpressionArray.push_back(NULL);
	return AddExpression(&CharExpressionArray[0], nExpEnv);
}



BOOL CObjExpression::AddExpression(char ** pExpression, unsigned int nExpEnv)
{
	char * pExpressionType=pExpression[0];
	int i=0;
	
	
	for(i=0;pExpression[i]!=NULL;i++)
	{
		pExpressionType=pExpression[i];
		CTokenizer * pTokenizer=new CTokenizer(string(pExpressionType));
		ExpressionContext Context;
		Context.nExpressionEnv = nExpEnv;
		Context.pObjExpression = this;
		vector<WordSet> Array;
		if(pTokenizer->GetWordArray(Array))
		{
			if(Array.size()==0) 
			{
				delete pTokenizer;
				continue;
			}
			if(Array.size()<6)
			{
				if((Array[0].WordVal==string("/"))
					&&(Array[1].WordVal==string("/")))
				{
					delete pTokenizer;
					continue;
				}

				if(Array[0].WordVal==string("MAKEINCLUDE")
					&&Array[1].WordVal==string("="))
				{
					if(AddExpression(Array[2].WordVal.c_str(), m_ExpEnvMap[nExpEnv].szExpEnvPath.c_str()))
					{
						delete pTokenizer;
						continue;
					}
					else
					{
						DebugPrint(1,"MAKEINCLUDE ��ӱ��ʽʧ�� (%s) \r\n ",Array[2].WordVal.c_str());
						return FALSE;
					}
				}

				DebugPrint(1,"AddExpression ���ʽ�﷨���� (%s) \r\n ",pExpressionType);

				return FALSE;
			}
			
			if(
				(Array[0].WordType==string("����"))
				&&(Array[2].WordType==string("����"))
				&&(Array[1].WordType==string("������"))
				&&(Array[1].WordVal==string("<"))
				&&(Array[3].WordType==string("������"))
				&&(Array[3].WordVal==string(">"))
				&&(Array[4].WordVal==string("="))
				&&(
				(Array[5].WordType==string("����"))||
				(Array[5].WordVal==string("."))
				)
				)
			{
				Context.name=Array[0].WordVal;
				Context.nametype=Array[2].WordVal;
				//Context.Array.insert(Context.Array.begin(),Array.size()-5,Array[5]);
				
				//std::copy(s.begin(),s.end(),s1.begin());
				//std::copy(Array.begin()+4,Array.end()-1,Context.Array.begin());
				Context.nNumWord=0;
				for(unsigned int s=5;s<Array.size();s++)
				{
					Context.Array.push_back(Array[s]);
					Context.nNumWord++;
				}

				WordSet tmp;
				tmp.WordVal=COMMANDEND;
				tmp.WordType="END";
				Context.Array.push_back(tmp);Context.Array.push_back(tmp);Context.Array.push_back(tmp);Context.Array.push_back(tmp);
				Context.Array.push_back(tmp);Context.Array.push_back(tmp);Context.Array.push_back(tmp);Context.Array.push_back(tmp);
				Context.Array.push_back(tmp);Context.Array.push_back(tmp);Context.Array.push_back(tmp);Context.Array.push_back(tmp);
				Context.Array.push_back(tmp);Context.Array.push_back(tmp);Context.Array.push_back(tmp);Context.Array.push_back(tmp);

				if(Context.name==string("ROOT"))
				{
					m_RootRuleName.push_back(Context);
				}
				else if(Context.name==string("ROOT_MAKE"))
				{
					m_RootRuleName.push_back(Context);
				}else
				{
					m_RuleNameMap[Context.name]=Context;
				}
				
			}
			else
			{
				//����ע��
				if((Array[0].WordVal==string("/"))
					&&(Array[1].WordVal==string("/")))
				{
					continue;
				}
				if(Array[0].WordVal==string("MAKEINCLUDE")
					&&Array[1].WordVal==string("="))
				{
					if(AddExpression(Array[2].WordVal.c_str(), m_ExpEnvMap[nExpEnv].szExpEnvPath.c_str()))
					{
						continue;
					}
					else
					{
						DebugPrint(1,"MAKEINCLUDE ��ӱ��ʽʧ�� (%s) \r\n ",Array[2].WordVal.c_str());
						return FALSE;
					}
				}
				//���Ǳ�׼���ʽ�ͱ�
				DebugPrint(1,"���ʽ�﷨���� (%s) \r\n ",pExpressionType);
				delete pTokenizer;
				return FALSE;
			}
			
		}
		delete pTokenizer;
	}
	return TRUE;
}
//���ùؼ��ֱ�
/*
���Խ������ʽ�淶
+  ��������������ʽ���ƣ���ʾ����������ָ���ı��ʽ�����Ⱥ�˳����붼ƥ��ɹ����γɶ���������
|	 ��������������ʽ���ƣ���ʾ����������ָ���ı��ʽֻҪ��һ��ƥ��ɹ���ñ��ʽ�ɹ�(ֻ��Ե�ǰ��һ���������)
=  �����ʽ��������
N<������ʽ��> ��ʾָ���Ĺ�����ʽҪ��N��ƥ��,ֱ����ǰ������ ��ƥ�䷵��״̬�����������
��<����ʼ������ʽ,����ֹ������ʽ,������ʽ��> ָ��һ�����Ľ���ƥ�����
xxx<yyy>	��ʾһ���﷨ƥ�������ʽ���ͱ��ʽ������ �� ��������1<��������>=��������1+����Լ��|NULL
NULL<������ʽ��> ��ʾ���ʽƥ��ʧ��Ҳ�ɷ��سɹ��������Ĭ��ֵ��
NULL_TRUE ������ʽ��ֱ�ӷ��ر��ʽƥ��ɹ� ���ڽ���Ԥ���ӿ�
NULL_FALSE ������ʽ��ֱ�ӷ��ر��ʽƥ��ʧ�� ���ڽ���Ԥ���ӿ�
xxx(yyy)	��ʾһ���ʷ�ƥ�������ʽ���ͱ��ʽ������ �� ��β1(��β)=; ����������ƥ������ ���ͣ������ͣ����ͣ������ͣ��ַ�����,�ַ��� ��ʱ�ϲ������ʽ
ROOT<���ʽ��> ��ʾ������������
G(xxx)	��ʾһ�����ʽ G(���ʽ��1|���ʽ��2)	��ʱ��֧��
WORD(xxx)	��ƥ��һ���� ����WORD(;)
*/
char * pKeywordTab[]=
{
	"NULL<","N<","NULL_TRUE","NULL_FALSE","WORD(","word(",
	"����","������","����","������","�ַ�����","�ַ���",
	NULL
};

BOOL CObjExpression::FindRuleContext(ParseRuleMapType::iterator & itRuleContext,string & RuleName,unsigned int nDepth)
{
	itRuleContext=m_RuleNameMap.find(RuleName);
	if(itRuleContext!=m_RuleNameMap.end())
	{
		return TRUE;
	}

	DebugPrint(nDepth,"���ʽ����δ���� (%s)\r\n ",RuleName.c_str());
	return FALSE;
	
}

BOOL CObjExpression::GetCommandTypeAndLen(
	IN ExpressionContext & Context,
	IN unsigned int nCommand,
	OUT string & Command,
	OUT unsigned int & nCommandLen,
	IN unsigned int nDepth
	)
{
	if(
		(string("NULL")==Context.Array[nCommand].WordVal)
		&&(string("<")==Context.Array[nCommand+1].WordVal)
		&&(string(">")==Context.Array[nCommand+3].WordVal)
		)
	{
		
		nCommandLen=4;
		Command=string("NULL");
		return TRUE;
	}

	if(
		(string("��")==Context.Array[nCommand].WordVal)
		&&(string("<")==Context.Array[nCommand+1].WordVal)
		&&(string(",")==Context.Array[nCommand+3].WordVal)
		&&(string(",")==Context.Array[nCommand+5].WordVal)
		&&(string(">")==Context.Array[nCommand+7].WordVal)
		)
	{
		
		nCommandLen=8;
		Command=string("��");
		return TRUE;
	}

	if(
		(string("N")==Context.Array[nCommand].WordVal)
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
				(string("NOT")==Context.Array[nCommand].WordVal)
				&&(string("<")==Context.Array[nCommand+1].WordVal)
				&&(string(">")==Context.Array[nCommand+3].WordVal)
				)
	{
		nCommandLen=4;
		Command=string("NOT");
		return TRUE;
	}
	if(
				(string("MAKE_CODE_TO")==Context.Array[nCommand].WordVal)
				&&(string("<")==Context.Array[nCommand+1].WordVal)
				&&(string(",")==Context.Array[nCommand+3].WordVal)
				&&(string(",")==Context.Array[nCommand+5].WordVal)
				&&(string(">")==Context.Array[nCommand+7].WordVal)
				)
	{
		
		nCommandLen=8;
		Command=string("MAKE_CODE_TO");
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
	}
	if(
		(string("NULL_TRUE")==Context.Array[nCommand].WordVal)
		)
	{
		nCommandLen=1;
		Command=string("NULL_TRUE");
		return TRUE;
	}

	if(
		(string("NULL_FALSE")==Context.Array[nCommand].WordVal)
		)
	{
	
		nCommandLen=1;
		Command=string("NULL_FALSE");
		return TRUE;

	}

	if(
		(string("WORD")==Context.Array[nCommand].WordVal)
		&&(string("(")==Context.Array[nCommand+1].WordVal)
		&&(string(")")==Context.Array[nCommand+3].WordVal)
		)
	{
		
		nCommandLen=4;
		Command=string("WORD");
		return TRUE;

	}

	if(
		(string("WORD")==Context.Array[nCommand].WordVal)
		&&(string("(")==Context.Array[nCommand+1].WordVal)
		)
	{
		
		if((Context.Array[nCommand+2].WordType==string("\\")))
		{
			if((Context.Array[nCommand+4].WordType==string(")")))
			{
				nCommandLen=5;
				Command=string("WORD");
				return TRUE;
			}
		}
		return FALSE;

	}

	if(
		(string("word")==Context.Array[nCommand].WordVal)
		&&(string("(")==Context.Array[nCommand+1].WordVal)
		&&(string(")")==Context.Array[nCommand+3].WordVal)
		)
	{
		
		nCommandLen=4;
		Command=string("word");
		return TRUE;

	}

	if(
		(string("����")==Context.Array[nCommand].WordVal)
		||(string("������")==Context.Array[nCommand].WordVal)
		||(string("����")==Context.Array[nCommand].WordVal)
		||(string("������")==Context.Array[nCommand].WordVal)
		||(string("�ַ�����")==Context.Array[nCommand].WordVal)
		||(string("�ַ���")==Context.Array[nCommand].WordVal)
		)
	{
		
		nCommandLen=1;
		Command=Context.Array[nCommand].WordVal;
		return TRUE;
	}

	//
	

	ParseRuleMapType::iterator itRuleContext;
	if(FindRuleContext(itRuleContext,Context.Array[nCommand].WordVal,nDepth))
	{
		Command="���ʽ�ͱ�";
		nCommandLen=1;
		return TRUE;
	}
	return FALSE;
}
