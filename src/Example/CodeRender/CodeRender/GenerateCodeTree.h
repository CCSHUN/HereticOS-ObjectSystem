#pragma once

#include "ObjExpression.h"
#include "Tokenizer.h"

//代码对象描述包
typedef struct _tagCodeObjTree
{
	string ObjName;		//语法分析规则名
	string ObjType;		//对象类型名
	string ObjVal;		//语法分析得到的值

	//起始符号坐标
	unsigned int nBeginPos;
	//结束符号坐标
	unsigned int nEndPos;

	//_tagCodeObjTree * parent;
	list<_tagCodeObjTree>::iterator parent;
	list<_tagCodeObjTree>	ChildObj;//子对象列表
}CodeObjTree,*PCodeObjTree;

//包树
//typedef struct PPackage;


typedef struct _tagPocket
{
	_tagPocket *		parent;		//父包 0为root包
	vector<WordSet>		WordArray;	//包中的词数组

}Pocket,*PPocket;




class CGenerateCodeTree
{
public:
	//词数组
	
	vector<WordSet> m_WordArray;

	list<_tagCodeObjTree> m_RootCodeObjList;	//为树计算而做
	//CodeObjTree m_RootCodeObj;

	CGenerateCodeTree(void);
	~CGenerateCodeTree(void);
	BOOL BindObjExpressionMgr(CObjExpression * mgr);
	BOOL PrintCodeTree(OUT string & Code,unsigned int nMaxDepth);
	//解析命令生成代码树。
	BOOL ParseDestString(char * pCode);
	BOOL GetSearchCodeToCodeObjTree(IN string & pFilePath);
	BOOL GetRoutingPath(IN list<_tagCodeObjTree>::iterator  & OrgCodeObj,OUT string & RstPath);
private:
	
	CObjExpression * m_ObjExpressionMgr;

	BOOL GetCommandTypeAndLen(
		IN ExpressionContext & Context,
		IN unsigned int nCommand,
		OUT string & Command,
		OUT unsigned int & nCommandLen,
		IN unsigned int nDepth
		);
	BOOL FindRuleContext(CObjExpression::ParseRuleMapType::iterator & itRuleContext,string & RuleName,unsigned int nDepth);


	BOOL Parse(IN ExpressionContext & Context,OUT CodeObjTree & RetCodeObj,OUT BOOL & bMatched,IN unsigned int nDepth);
	BOOL CalculatePackage(
		IN string & LogHead,	
		IN string & BeginExpression,	//开始分隔符表达式名
		IN string & EndExpression,	//终止分隔符表达式名
		IN unsigned int  nParseBegin, //解析串起始位置
		IN unsigned int  nParseEnd,
		OUT unsigned int & nPackageBegin,
		OUT unsigned int & nPackageEndBegin,
		OUT unsigned int & nPackageEndEnd,
		OUT BOOL & bMatched,		//是否匹配到
		IN unsigned int nDepth);

	BOOL WordMacth(
		IN string & LogHead,				//错误日志标头
		vector<WordSet>	&  WordArray,	//表达式词表
		IN unsigned int  nWordBegin,		//解析串起始位置
		IN unsigned int  nParseBegin,		//解析目标串起始位置
		IN BOOL bMatchCase,				//是否检查大小写
		OUT unsigned int  & nWordEndEnd,	//WORD结束的下一个词位置
		OUT unsigned int  & bMatched,		//表示是否成功匹配
		IN unsigned int nDepth);

	BOOL PrintCodeTree(list<CodeObjTree>::iterator & itNode,string & szRet,unsigned int nDepth,unsigned int nMaxDepth);


	BOOL LinkCodeTreeParent();
	BOOL LinkCodeTreeParent(list<CodeObjTree>::iterator & itNode,list<CodeObjTree>::iterator & itParent);

	
};
