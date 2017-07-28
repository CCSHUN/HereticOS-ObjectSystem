//************************************************************************ 
// 公司: 2012-2015, Arcadia Soft.
// 文件名: Sexp.h
// 作者: 叶树深 
// 版本: 1.0 
// 日期: 2015/05/08
// 功能描述: 
// 其他备注:
// 维护历史:
//************************************************************************ 


#pragma once
#include "BaseFunctionTool.h"
//#include "AutoVar.h"

#include "TextParse.h"

//#include <algorithm>

class CAutoVal;

static TCHAR * szBreak[]={
	_T(" "),_T("\r"),_T("\n"),_T("\t"),NULL
};
static TCHAR * szStackBegin[]={
	_T("("),_T("（"),
	NULL
};

static TCHAR * szStackEnd[]={
	_T(")"),_T("）"),
	NULL
};

static TCHAR * szWordEnd[]={
	_T(")"),_T("）"),_T(" "),_T("\r"),_T("\n"),_T("\t"),NULL 
};

static TCHAR * pFuntionText[]={
	_T("list"), _T("program"), _T("ListObjTest"),
	_T("setv"), _T("get2v"), _T("ListObjRef"),
	_T("refs"), _T("code"), _T("bp"),
	_T("ListFuse"), _T("seta"), _T("LessThan"),
	_T("REM"), _T("Add"), _T("Mul"),
	_T("Mod"), _T("return"), _T("setref"),
	_T("BackQuote"), _T("RefLisp"), _T("MakeNameAtom"),
	_T("DebugLisp"), _T("BackQuote_Stack"), _T("StackRefLisp"),
	_T("StackRefLispGetVal"), _T("setq"), _T("setg"),
	_T("sets"), _T("eq"), _T("cond"),
	_T("atom"), _T("car"), _T("cdr"),
	_T("quote"), _T("cons"), NULL
};

static TCHAR * szPrefix[]={
	_T(","),_T("`"),_T("'"),_T("@"),_T(";"),_T("$"),NULL 
};

enum SymType
{
	SymType_StackBegin=0x0,	//栈起始
	SymType_StackEnd ,		//栈结束
	SymType_Break ,			//换行空格制表
	SymType_Keyword ,		//保留关键字
	SymType_Prefix,			//前缀
	SymType_Word,			//单词
};
enum MatchType
{
	err=0,			
	all=0x1,		//全部匹配，长度相同\0结束
	part=0x2,		//串中存在
	begin=0x4,		//串首存在
	begin_all=0x8,	//串首存在，之后必须是\r \n \t 或者)隔断
	MinPart=0x10,
	none = MatchType::all | MatchType::part | MatchType::begin | MatchType::begin_all,		//找到即可
};

typedef struct _tagSymTypeTab
{
	SymType nType;
	TCHAR ** pTab;
	unsigned int nMatchType;
}SymTypeTab,*PSymTypeTab;

static SymTypeTab SymTab[]={
	{ SymType_StackBegin, szStackBegin, MatchType::all | MatchType::begin | MatchType::begin_all },
	{ SymType_StackEnd, szStackEnd, MatchType::all | MatchType::begin | MatchType::begin_all },
	{ SymType_Break, szBreak, MatchType::all | MatchType::begin | MatchType::begin_all },
	{ SymType_Keyword, pFuntionText, MatchType::all | MatchType::begin_all },
	{ SymType_Prefix, szPrefix, MatchType::begin },
	{(SymType)NULL,NULL,NULL}
};

typedef struct _tagWordBaseInfo
{
	SymType szWordType;
	tstring szWord; 
	unsigned int	nOffset;
	unsigned int	nLine;
}WordBaseInfo,*PWordBaseInfo;

template<typename ContainerT>
class CSexp
{
public:
	CSexp(){};
	~CSexp(){};
	typedef CSexp<ContainerT> _Myt;
	enum StackErrorType
	{
		NoError=1,
		LeftLose,			//左丢失
		RightLose,			//右丢失
		StructError,		//结构化错误，比如没有以(开始
	};
	enum StackType
	{
		StackType_None=1,			//
		StackType_Normal,			//（）
		StackType_Val,				//VAL
		StackType_Prefix,			//前缀
		StackType_Rem,				//REM ;;;
		StackType_String,			//""
	};
	struct SExpTree
	{
		unsigned int		nStackDepth;	//栈深度
		StackErrorType		nStackError;	//栈错误类型
		StackType			tStackType;
		unsigned int		nBeginPos;
		unsigned int		nEndPos;
		unsigned int		nBeginLine;
		unsigned int		nEndLine;
		CAutoVal			Val;
		vector<SExpTree>	ValList;
	};
	SExpTree	m_Node;
	wstring		m_szExp;
	ContainerT	m_Container;

	
	TCHAR * FindInTab(TCHAR * pPos,TCHAR ** pFinderTab,MatchType & mt=begin_all,BOOL bIgnoreCase=TRUE)
	{
		tstring szSrc=pPos;
		TCHAR * pszSrc=szSrc.c_str();
		BOOL bMatch=FALSE;
		if(bIgnoreCase)
		{
			strlwr_s_t((TCHAR *)szSrc.c_str(),szSrc.length());
		}

		for(unsigned int i=0;pFinderTab[i]!=NULL;i++)
		{
			WCHAR * pDst=wcsstr(pszSrc,pFinderTab[i]);
			if(pDst==NULL)
			{
				continue;
			}else if(pDst!=pszSrc)
			{
				switch(mt)
				{
				case all:
				case begin:
				case begin_all:
					break; 
				case part:
					return pDst; 
				default:
					return NULL;
				}

			}else
			{
				BOOL bAll=(wcslen(pszSrc)==wcslen(pFinderTab[i]))?TRUE:FALSE;
				switch(mt)
				{
				case all:
					if(bAll==TRUE) return pDst;
					break;
				case begin:
					return pDst; 
				case begin_all:
					if(
						(pszSrc[wcslen(pFinderTab[i])]=='\r')||
						(pszSrc[wcslen(pFinderTab[i])]=='\n')||
						(pszSrc[wcslen(pFinderTab[i])]=='\t')||
						(pszSrc[wcslen(pFinderTab[i])]==')')
						)
					{
						return pDst;
					}
					break;
				case part: 
					return pDst; 
				default:
					return NULL;
				}
			}
		}
		return NULL;
	}

	TCHAR * FindInTabOutMt(TCHAR * pCode,TCHAR ** pFinderTab,IN MatchType mt,OUT MatchType & omt,OUT unsigned int & nOffset,BOOL bIgnoreCase=TRUE)
	{
		tstring szSrc=pCode;
		TCHAR * pszSrc=(TCHAR *)szSrc.c_str();
		BOOL bMatch=FALSE;
		nOffset=0;
		TCHAR * pszMinPart=NULL;
		unsigned int nMinPartOffset=szSrc.length();
		if(bIgnoreCase)
		{
			//std::transform(szSrc.begin(),szSrc.end(),tolower);
			//tolower()
			strlwr_s_t((TCHAR *)szSrc.c_str(),szSrc.length());
		}

		omt=err;
		for(unsigned int i=0;pFinderTab[i]!=NULL;i++)
		{
			TCHAR * pDst=strstr_t(pszSrc,pFinderTab[i]);
			
			if(pDst==NULL)
			{
				continue;
			}else if(pDst!=pszSrc)
			{
				if(mt&MinPart)
				{
					if(nMinPartOffset>(pDst-pszSrc))
					{
						nOffset=pDst-pszSrc;
						pszMinPart=pFinderTab[i];
						nMinPartOffset=(pDst-pszSrc);
						omt=MinPart; 
					}
					
					continue;
				}else
				{
					omt=part; 
				}
				
				
			}else
			{
				omt = (strlen_t(pszSrc) == strlen_t(pFinderTab[i])) ? all : MatchType::begin;

				if(
					(pszSrc[strlen_t(pFinderTab[i])]=='\r')||
					(pszSrc[strlen_t(pFinderTab[i])]=='\n')||
					(pszSrc[strlen_t(pFinderTab[i])]=='\t')||
					(pszSrc[strlen_t(pFinderTab[i])]==')')
					)
				{
					omt=begin_all;
				} 
				//break;
			}

			if(mt&omt)
			{
				nOffset=pDst-pszSrc;
				return pFinderTab[i];
			} 

			
		}

		return pszMinPart;
	}
	BOOL GetWord(TCHAR * pCode,OUT SymType & OutSymType,OUT tstring & szOutWord)
	{
		TCHAR * pRet=NULL;
		MatchType omt=err;
		unsigned int nOffset=0;
		TCHAR szWord[1024]={0};
		if(pCode[0]==0) return FALSE;
		for(unsigned int i=0;SymTab[i].pTab;i++)
		{
			omt=err;
			pRet=FindInTabOutMt(pCode,SymTab[i].pTab,(MatchType)SymTab[i].nMatchType,omt,nOffset,FALSE);
			
			if(pRet) {
				OutSymType=SymTab[i].nType;
				szOutWord=pRet;
				return TRUE;
			}
		}

		if(pRet==NULL)
		{
			omt=err;
			OutSymType=SymType_Word;
  
			//找单词结尾
			pRet=FindInTabOutMt(pCode,szWordEnd,MinPart,omt,nOffset,FALSE);
			if(pRet)
			{
				memcpy(szWord,pCode,nOffset*sizeof(TCHAR));
				szOutWord=szWord;
				return TRUE;
			}else
			{
				szOutWord=pCode;
				return TRUE;
			}
			

		}
		return FALSE;
	}
	BOOL GetWordArray(TCHAR * pCode,vector<_tagWordBaseInfo> & szWordArray)
	{
		_tagWordBaseInfo set;
		TCHAR * pPos=pCode;
		unsigned int nLine=0;
		for(;;)
		{
			if(GetWord(pPos,set.szWordType,set.szWord))
			{
				
				set.nOffset=pPos-pCode;
				set.nLine=nLine;
				pPos+=set.szWord.length();
				szWordArray.push_back(set);
				if((set.szWordType==SymType_Break)&&(set.szWord==_T("\n")))
				{
					nLine++;
				}
			}else
			{
				return szWordArray.size()==0?FALSE:TRUE;
			}
		}
		return FALSE;
	}


	CSexp(vector<_tagWordBaseInfo> & szWordArray,unsigned int & i,unsigned int & nLine,SExpTree & TreeNode,unsigned int nDepth=0)
	{
		BOOL bBeginFail=TRUE;
		BOOL bEndFail=TRUE;
		TreeNode.tStackType=StackType_None;
		TreeNode.nStackError=StructError;


		TreeNode.nBeginPos=szWordArray[i].nOffset;
		TreeNode.nEndPos=szWordArray[i].nOffset;//+szWordArray[i].szWord.length();
		TreeNode.nEndLine=nLine;
		TreeNode.nStackDepth=nDepth;
		if(szWordArray[i].szWordType==SymType_StackBegin)
		{
			bBeginFail=FALSE;
			TreeNode.tStackType=StackType_Normal;
			TreeNode.nStackError=NoError;
			TreeNode.nBeginLine=nLine;
			i++;
		}

		 

		for(;i<szWordArray.size();)
		{
			if(szWordArray[i].szWordType==SymType_StackBegin)
			{
				if(bBeginFail) TreeNode.nStackError=LeftLose; 
				unsigned int nNewDepth=nDepth+1;
				SExpTree NewNode;
				CSexp(szWordArray,i,nLine,NewNode,nNewDepth);
				if((!bBeginFail)&&(NewNode.nStackError!=NoError)) TreeNode.nStackError=StructError; 
				TreeNode.ValList.push_back(NewNode);
				TreeNode.nEndLine=nLine;
				TreeNode.nEndPos=NewNode.nEndPos;
				continue;
				
			}else if(szWordArray[i].szWordType==SymType_StackEnd)
			{
				TreeNode.tStackType=StackType_Normal;
				if(bBeginFail) TreeNode.nStackError=LeftLose; 

				TreeNode.nEndPos=szWordArray[i].nOffset;//+szWordArray[i].szWord.length();
				TreeNode.nEndLine=nLine;
				bEndFail=FALSE;
				i++;
				return;
			}else if(szWordArray[i].szWordType==SymType_Word)
			{
				SExpTree NewNode;
				NewNode.Val=szWordArray[i].szWord;
				NewNode.tStackType=StackType_Val;
				NewNode.nBeginPos=szWordArray[i].nOffset;
				NewNode.nEndPos=szWordArray[i].nOffset+szWordArray[i].szWord.length();
				NewNode.nBeginLine=nLine;
				NewNode.nEndLine=nLine;

				NewNode.nStackDepth=nDepth;
				NewNode.nStackError=NoError;

				TreeNode.ValList.push_back(NewNode);
			}else if(szWordArray[i].szWordType==SymType_Keyword)
			{
				SExpTree NewNode;
				NewNode.Val=szWordArray[i].szWord;
				NewNode.tStackType=StackType_Val;
				NewNode.nBeginPos=szWordArray[i].nOffset;
				NewNode.nEndPos=szWordArray[i].nOffset+szWordArray[i].szWord.length();
				NewNode.nBeginLine=nLine;
				NewNode.nEndLine=nLine;

				NewNode.nStackDepth=nDepth;
				NewNode.nStackError=NoError;

				TreeNode.ValList.push_back(NewNode);

			}else if(szWordArray[i].szWordType==SymType_Prefix)
			{
				SExpTree NewNode;
				NewNode.Val=szWordArray[i].szWord;
				NewNode.tStackType=StackType_Prefix;
				NewNode.nBeginPos=szWordArray[i].nOffset;
				NewNode.nEndPos=szWordArray[i].nOffset+szWordArray[i].szWord.length();
				NewNode.nBeginLine=nLine;
				NewNode.nEndLine=nLine;

				NewNode.nStackDepth=nDepth;
				NewNode.nStackError=NoError;

				TreeNode.ValList.push_back(NewNode);

			}else if(szWordArray[i].szWordType==SymType_Break)
			{
				//过滤掉
				if(szWordArray[i].szWord==_T("\n"))
				{
					nLine++;
				}
			}

			i++;
		}

		if(bEndFail)
		{
			TreeNode.tStackType=StackType_Normal;
			TreeNode.nStackError=RightLose;
		}
		return;
	}
	

	
	CSexp(wstring & szExp)
	{
		m_szExp = wstring((WCHAR*)CMyString(szExp));
		m_Node.tStackType=StackType_None;
		vector<_tagWordBaseInfo>  szWordArray;
		if(GetWordArray((TCHAR *)szExp.c_str(),szWordArray))
		{
			

			unsigned int nIndex=0,nLine=0;
			
			m_Node.tStackType=StackType_Normal;
			m_Node.nStackError=NoError;
			m_Node.nBeginLine=nLine;
			m_Node.nBeginPos=0;
			BOOL bError=FALSE;

			CSexp(szWordArray,nIndex,nLine,m_Node);
			/*if(nIndex<szWordArray.size())
			{
				m_Node.nStackError=LeftLose;
			}*/
			/*for(;;)
			{
				SExpTree _tmpTree,_tmpTree1;
				
				CSexp(szWordArray,nIndex,nLine,_tmpTree);
				if(nIndex<szWordArray.size())
				{
					bError=TRUE;
					if(_tmpTree.nStackError==NoError) 
					{
						m_Node.nStackError=LeftLose;
						m_Node.ValList.push_back(_tmpTree);
						m_Node.nEndLine=nLine;
						m_Node.nEndPos=_tmpTree.nEndPos;
					}else if(_tmpTree.nStackError==LeftLose)
					{
						
						
							_tmpTree1=m_Node;
						
						
						m_Node.ValList.clear();
						m_Node.ValList.push_back(_tmpTree1);
						m_Node.tStackType=StackType_Normal; 
						//m_Node.nBeginLine=nLine;
						m_Node.nStackError=LeftLose;
						m_Node.nEndPos=_tmpTree.nEndPos;
						m_Node.nEndLine=nLine; 
						
					}else if(_tmpTree.nStackError==RightLose)
					{ 
						m_Node.nStackError=RightLose;
						m_Node.ValList.push_back(_tmpTree);
						m_Node.nEndLine=nLine;
						m_Node.nEndPos=_tmpTree.nEndPos;
					}
					
					
				}else
				{
					if(bError==FALSE) 
					{
						m_Node=_tmpTree; 
					}else if(_tmpTree.nStackError==LeftLose)
					{
						
						_tmpTree1=m_Node;
						

						m_Node.ValList.clear();
						m_Node.ValList.push_back(_tmpTree1);
						m_Node.tStackType=StackType_Normal; 
						//m_Node.nBeginLine=nLine;
						m_Node.nStackError=LeftLose;
						m_Node.nEndPos=_tmpTree.nEndPos;
						m_Node.nEndLine=nLine; 

					}else if(_tmpTree.nStackError==RightLose)
					{
						m_Node.nStackError=RightLose;
						m_Node.ValList.push_back(_tmpTree);
						m_Node.nEndLine=nLine;
						m_Node.nEndPos=_tmpTree.nEndPos;
					}else if(_tmpTree.nStackError==NoError) 
					{
						m_Node.nStackError=LeftLose;
						m_Node.ValList.push_back(_tmpTree);
						m_Node.nEndLine=nLine;
						m_Node.nEndPos=_tmpTree.nEndPos;
					}

					break;
				}
			}*/
			
		}
	}

	SExpTree* GetStackByPos(SExpTree* pPos,unsigned int nCurPos)
	{
		for(unsigned int i=0;i<pPos->ValList.size();i++)
		{
			if((nCurPos>pPos->ValList[i].nBeginPos)&&(nCurPos<=pPos->ValList[i].nEndPos))
			{
				if(pPos->ValList[i].ValList.size()==0)
				{
					if(pPos->ValList[i].tStackType==StackType_Normal)
					{
						return &pPos->ValList[i];
					}
					return pPos;
				}else
				{
					return GetStackByPos(&pPos->ValList[i],nCurPos);
				}
			}
		}
		return pPos;
	}

	SExpTree* GetStackByPos(unsigned int nCurPos)
	{
		return GetStackByPos(&m_Node,nCurPos);
	}

	CSexp(string & szExp)
	{
		wstring wszExps=wstring((WCHAR*)CMyString(szExp));
		CSexp((wstring &)wszExps);	
	}
	
	BOOL GetContainer(SExpTree & TreeNode,ContainerT & Node)
	{
		if(TreeNode.nStackError!=NoError) return FALSE;
		if(TreeNode.tStackType==StackType_Normal)
		{
			ContainerT NewNode;
			BOOL bPrefix=FALSE;
			tstring szPrefix;
			for(unsigned int i=0;i<TreeNode.ValList.size();i++)
			{
				NewNode.clear();
				if(TreeNode.ValList[i].tStackType==StackType_Val)
				{
					if(bPrefix)
					{
						CAutoVal aVal(tstring(szPrefix+(tstring)TreeNode.ValList[i].Val));
						Node.push_back(aVal);
						bPrefix=FALSE;
						szPrefix.clear();

					}else
					{
						Node.push_back(TreeNode.ValList[i].Val);
					}
					
				}else if(TreeNode.ValList[i].tStackType==StackType_Prefix)
				{
					if(bPrefix==TRUE) {
						szPrefix+=(tstring)TreeNode.ValList[i].Val;
					}else
					{
						bPrefix=TRUE;
						szPrefix.clear();
					}
					
				}else if(TreeNode.ValList[i].tStackType==StackType_Normal)
				{
					if(GetContainer(TreeNode.ValList[i],NewNode))
					{
						Node.push_back(NewNode);
					}else
					{
						return FALSE;
					}
				}
				
			}
		}else if(TreeNode.tStackType==StackType_Val)
		{
			Node.push_back(TreeNode.Val);
		}
		return TRUE;
		
	}

	operator ContainerT& ()
	{
		if(GetContainer(m_Node,m_Container)==FALSE)
		{
			m_Container.clear();
		}
		return m_Container;
	}
protected:
	
private:
};