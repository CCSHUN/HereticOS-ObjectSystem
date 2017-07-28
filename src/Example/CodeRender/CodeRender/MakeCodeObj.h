#pragma once

#include "GenerateCodeTree.h"



typedef struct _tagCodeRoutingNode
{
	string								ExpressionName;		//·�ɹ�����ʽ��
	string								TypeName;			//·�ɽڵ�����
	list<_tagCodeObjTree>::iterator		CurCodeObjTree;
	list<_tagCodeObjTree>::iterator		LastChildCodeNode;	//���һ��·�ɵ����Ӵ���ڵ�

}CodeRoutingNode,PCodeRoutingNode;

typedef struct _tagCodeRoutingContext
{
	list<CodeRoutingNode>				CodeRouting;
	string								ExpressionName;		//���ʽ��
	string								szMakeRst;			//make���
}CodeRoutingContext,*PCodeRoutingContext;

//·�����Ӱ󶨱����ڷ����㷨���ٴ�����
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
	//���ɴ���
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

	//make����
	BOOL GetCodeValByName(IN list<_tagCodeObjTree>::iterator & RootCodeObj,IN list<_tagCodeObjTree>::iterator & BeginCodeObj,IN string & CodeName,OUT list<_tagCodeObjTree>::iterator & RetCodeObj);
	BOOL GetCodeValByVal(IN list<_tagCodeObjTree>::iterator & RootCodeObj,IN list<_tagCodeObjTree>::iterator & BeginCodeObj,IN string & CodeVal,OUT list<_tagCodeObjTree>::iterator & RetCodeObj);
	BOOL GetRoutingNode(
		IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
		IN vector<string> &RoutingExpression,	//·�ɱ��ʽ
		IN list<_tagCodeObjTree>::iterator & RootCodeObj,	//���������
		IN BOOL bSearchExpression,		//�Ƿ��ѯ���ڵı��ʽ
		OUT BOOL & bFind,				//�Ƿ��ҵ�
		OUT list<_tagCodeObjTree>::iterator & RetCodeObj,	//��һ��ƥ�䵽�Ľڵ�
		OUT CodeRoutingContext & RoutingContext,	//�����ѯ���ʽ����·�ɻ���
		IN unsigned int nDepth	
		);
	BOOL GetRoutingNode_Real(
		IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
		IN vector<string> &RoutingExpression,	//·�ɱ��ʽ
		IN list<_tagCodeObjTree>::iterator & RootCodeObj,	//���������
		IN BOOL bSearchExpression,		//�Ƿ��ѯ���ڵı��ʽ
		OUT BOOL & bFind,				//�Ƿ��ҵ�
		OUT list<_tagCodeObjTree>::iterator & RetCodeObj,	//��һ��ƥ�䵽�Ľڵ�
		OUT CodeRoutingContext & RoutingContext,	//�����ѯ���ʽ����·�ɻ���
		IN unsigned int nDepth	
		);

	BOOL NextRoutingNode(
		IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
		IN OUT CodeRoutingContext & RoutingContext,
		OUT BOOL & bFind,
		OUT list<_tagCodeObjTree>::iterator & RetCodeObj,//ƥ�䵽�Ľڵ�
		IN unsigned int nDepth	
		);

	//·��ѭ��make���ʽִ��
	
	BOOL MakeCodeRouting_Real(
		IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
		IN string & LogHead,				//������־��ͷ
		IN list<_tagCodeObjTree>::iterator RootCodeObj,
		IN string & RoutingExpression,		//·�ɱ��ʽ
		IN ExpressionContext & BeginMake,
		IN ExpressionContext & ProcMake,
		IN ExpressionContext & EndMake,
		OUT BOOL & bMatched,	//�ǹ��ܹ�MAKE
		OUT vector<string>  & RetCode,
		OUT BOOL & bRouting,	//�Ƿ��ܹ�·��
		IN unsigned int nDepth,
		IN unsigned int nRootDepth,
		IN BOOL bOne		//ֻ��һ��ƥ��
		);

	
	BOOL MakeCodeRouting(
		IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
		IN string & LogHead,				//������־��ͷ
		IN list<_tagCodeObjTree>::iterator RootCodeObj,
		IN string & RoutingExpression,		//·�ɱ��ʽ
		IN ExpressionContext & BeginMake,
		IN ExpressionContext & ProcMake,
		IN ExpressionContext & EndMake,
		OUT BOOL & bMatched,
		OUT vector<string>  & RetCode,
		IN unsigned int nDepth,
		IN unsigned int nRootDepth,
		IN BOOL bOne		//ֻ��һ��ƥ��
		);

	//make ָ����codetree ��codetreeִ��make���ʽ
	BOOL MakeCode(
		IN list<_tagCodeObjTree>::iterator  & RootRootCodeObj,
		IN list<_tagCodeObjTree>::iterator  & OrgCodeObj,
		IN ExpressionContext & Context,
		OUT BOOL & bMatched,
		OUT vector<string> & RetCode,
		IN unsigned int nDepth,
		IN unsigned int nRootDepth);

	BOOL MakeCode(IN vector<string> & RetCode,IN CGenerateCodeTree * pCodeTree,IN CObjExpression * pObjExpression);

	//�� make;
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

	//·�ɽڵ����������㷨
	//��BindName�󶨵�BindToName
	BOOL BindRoutingName(string & BindToName,string & BindName);
	//�ַ�����ʽ�ı��ʽ
	BOOL GetAllRoutingNameFromRoutingBindTab(string & RoutingExpression,vector<string> & AllBindNameArray);
	//�ֶη�ʽ
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
