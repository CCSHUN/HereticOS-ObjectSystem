#pragma once

#include "GenerateCodeTree.h"



typedef struct _tagCodeRoutingNode
{
	string								ExpressionName;		//路由规则表达式名
	string								TypeName;			//路由节点类型
	list<_tagCodeObjTree>::iterator		CurCodeObjTree;
	list<_tagCodeObjTree>::iterator		LastChildCodeNode;	//最近一次路由到的子代码节点

}CodeRoutingNode,PCodeRoutingNode;

typedef struct _tagCodeRoutingContext
{
	list<CodeRoutingNode>				CodeRouting;
	string								ExpressionName;		//表达式名
	string								szMakeRst;			//make结果
}CodeRoutingContext,*PCodeRoutingContext;

//路由连接绑定表，用于泛型算法减少代码量
typedef struct _tagRoutingExpressionInfo
{
	string			RoutingExpression;
	vector<string>	RoutingExpressionNodeArray;
}RoutingExpressionInfo,*PRoutingExpressionInfo;

typedef struct _tagRoutingMapTab
{
	RoutingExpressionInfo RoutingExpression;
	vector<RoutingExpressionInfo> RoutingExpressionBindList;
}RoutingMapTab,*PRoutingMapTab;

class CMakeCodeObj
{
public:
	CMakeCodeObj(void);
	~CMakeCodeObj(void);

	BOOL BindObjExpressionMgr(CObjExpression * mgr);
	//生成代码
	BOOL MakeCode(OUT vector<string> & RetCode);

private:
	CObjExpression * m_ObjExpressionMgr;
	vector<RoutingMapTab> m_RoutingMapTabArray;
	string m_szCurrentMakePath;

	BOOL GetCommandTypeAndLen(
		IN ExpressionContext & Context,
		IN unsigned int nCommand,
		OUT string & Command,
		OUT unsigned int & nCommandLen,
		IN unsigned int nDepth
		);
	BOOL FindRuleContext(CObjExpression::ParseRuleMapType::iterator & itRuleContext,string & RuleName,unsigned int nDepth);

	//make引擎
	BOOL GetCodeValByName(IN list<_tagCodeObjTree>::iterator & RootCodeObj,IN list<_tagCodeObjTree>::iterator & BeginCodeObj,IN string & CodeName,OUT list<_tagCodeObjTree>::iterator & RetCodeObj);
	BOOL GetCodeValByVal(IN list<_tagCodeObjTree>::iterator & RootCodeObj,IN list<_tagCodeObjTree>::iterator & BeginCodeObj,IN string & CodeVal,OUT list<_tagCodeObjTree>::iterator & RetCodeObj);
	BOOL GetRoutingNode(
		IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
		IN vector<string> &RoutingExpression,	//路由表达式
		IN list<_tagCodeObjTree>::iterator & RootCodeObj,	//根代码对象
		IN BOOL bSearchExpression,		//是否查询存在的表达式
		OUT BOOL & bFind,				//是否找到
		OUT list<_tagCodeObjTree>::iterator & RetCodeObj,	//第一个匹配到的节点
		OUT CodeRoutingContext & RoutingContext,	//如果查询表达式则建立路由环境
		IN unsigned int nDepth	
		);
	BOOL GetRoutingNode_Real(
		IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
		IN vector<string> &RoutingExpression,	//路由表达式
		IN list<_tagCodeObjTree>::iterator & RootCodeObj,	//根代码对象
		IN BOOL bSearchExpression,		//是否查询存在的表达式
		OUT BOOL & bFind,				//是否找到
		OUT list<_tagCodeObjTree>::iterator & RetCodeObj,	//第一个匹配到的节点
		OUT CodeRoutingContext & RoutingContext,	//如果查询表达式则建立路由环境
		IN unsigned int nDepth	
		);

	BOOL NextRoutingNode(
		IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
		IN OUT CodeRoutingContext & RoutingContext,
		OUT BOOL & bFind,
		OUT list<_tagCodeObjTree>::iterator & RetCodeObj,//匹配到的节点
		IN unsigned int nDepth	
		);

	//路由循环make表达式执行
	
	BOOL MakeCodeRouting_Real(
		IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
		IN string & LogHead,				//错误日志标头
		IN list<_tagCodeObjTree>::iterator RootCodeObj,
		IN string & RoutingExpression,		//路由表达式
		IN ExpressionContext & BeginMake,
		IN ExpressionContext & ProcMake,
		IN ExpressionContext & EndMake,
		OUT BOOL & bMatched,	//是够能够MAKE
		OUT vector<string>  & RetCode,
		OUT BOOL & bRouting,	//是否能够路由
		IN unsigned int nDepth,
		IN unsigned int nRootDepth,
		IN BOOL bOne		//只做一次匹配
		);

	
	BOOL MakeCodeRouting(
		IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
		IN string & LogHead,				//错误日志标头
		IN list<_tagCodeObjTree>::iterator RootCodeObj,
		IN string & RoutingExpression,		//路由表达式
		IN ExpressionContext & BeginMake,
		IN ExpressionContext & ProcMake,
		IN ExpressionContext & EndMake,
		OUT BOOL & bMatched,
		OUT vector<string>  & RetCode,
		IN unsigned int nDepth,
		IN unsigned int nRootDepth,
		IN BOOL bOne		//只做一次匹配
		);

	//make 指定的codetree 对codetree执行make表达式
	BOOL MakeCode(
		IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
		IN list<_tagCodeObjTree>::iterator  & OrgCodeObj,
		IN ExpressionContext & Context,
		OUT BOOL & bMatched,
		OUT vector<string> & RetCode,
		IN unsigned int nDepth,
		IN unsigned int nRootDepth);

	BOOL MakeCode(IN vector<string> & RetCode,IN CGenerateCodeTree * pCodeTree,IN CObjExpression * pObjExpression);

	//根 make;
	BOOL MakeCode(vector<string> & RetCode,ExpressionContext & Context,IN BOOL bRootNoCode);
	BOOL GetSearchCodeToCodeObjTree(IN string & pFilePath,IN OUT CGenerateCodeTree &CodeTree);

	BOOL GetRoutingExpressionArray(IN ExpressionContext & Context,
		IN unsigned int nCommand,
		OUT vector<string> &RoutingExpression,
		OUT unsigned int & nCommandLen,
		IN unsigned int nDepth);

	BOOL GetRoutingExpressionArray(IN string & RoutingExpressionName,
		OUT vector<string> &RoutingExpression,
		IN unsigned int nDepth);

	BOOL GetRoutingExpressionArrayByExpression(string  & RoutingExpression,
		OUT vector<string> & RoutingExpressionArray);

	BOOL AutoGetRoutingExpressionArray(string &RoutingExpression,vector<string> & RoutingExpressionArray);

	BOOL SaveCodeToObj(IN ExpressionContext & Context, IN string & pObj,IN vector<string> & RetCode);

	//路由节点名绑定隐射算法
	//将BindName绑定到BindToName
	BOOL BindRoutingName(string & BindToName,string & BindName);
	//字符串方式的表达式
	BOOL GetAllRoutingNameFromRoutingBindTab(string & RoutingExpression,vector<string> & AllBindNameArray);
	//分段方式
	BOOL GetAllRoutingNameFromRoutingBindTab(vector<string> &RoutingExpression,vector<vector<string> > & AllBindNameArray);
	BOOL GetAllRoutingNameFromRoutingBindTab(string & RoutingExpression,
		vector<vector<string> > & AllBindNameArray);


	BOOL FindAAndReplaseRouting(
					 IN vector<string> & Org,
					 IN vector<string> & Finder,
					 IN vector<string> & Replace,
					 OUT vector<string> & Out,
					 OUT string & Out1
					 );
};
