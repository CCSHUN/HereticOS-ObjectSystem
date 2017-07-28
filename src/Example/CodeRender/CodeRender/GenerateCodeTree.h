#pragma once

#include "ObjExpression.h"
#include "Tokenizer.h"

//�������������
typedef struct _tagCodeObjTree
{
	string ObjName;		//�﷨����������
	string ObjType;		//����������
	string ObjVal;		//�﷨�����õ���ֵ

	//��ʼ��������
	unsigned int nBeginPos;
	//������������
	unsigned int nEndPos;

	//_tagCodeObjTree * parent;
	list<_tagCodeObjTree>::iterator parent;
	list<_tagCodeObjTree>	ChildObj;//�Ӷ����б�
}CodeObjTree,*PCodeObjTree;

//����
//typedef struct PPackage;


typedef struct _tagPocket
{
	_tagPocket *		parent;		//���� 0Ϊroot��
	vector<WordSet>		WordArray;	//���еĴ�����

}Pocket,*PPocket;




class CGenerateCodeTree
{
public:
	//������
	
	vector<WordSet> m_WordArray;

	list<_tagCodeObjTree> m_RootCodeObjList;	//Ϊ���������
	//CodeObjTree m_RootCodeObj;

	CGenerateCodeTree(void);
	~CGenerateCodeTree(void);
	BOOL BindObjExpressionMgr(CObjExpression * mgr);
	BOOL PrintCodeTree(OUT string & Code,unsigned int nMaxDepth);
	//�����������ɴ�������
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
		IN string & BeginExpression,	//��ʼ�ָ������ʽ��
		IN string & EndExpression,	//��ֹ�ָ������ʽ��
		IN unsigned int  nParseBegin, //��������ʼλ��
		IN unsigned int  nParseEnd,
		OUT unsigned int & nPackageBegin,
		OUT unsigned int & nPackageEndBegin,
		OUT unsigned int & nPackageEndEnd,
		OUT BOOL & bMatched,		//�Ƿ�ƥ�䵽
		IN unsigned int nDepth);

	BOOL WordMacth(
		IN string & LogHead,				//������־��ͷ
		vector<WordSet>	&  WordArray,	//���ʽ�ʱ�
		IN unsigned int  nWordBegin,		//��������ʼλ��
		IN unsigned int  nParseBegin,		//����Ŀ�괮��ʼλ��
		IN BOOL bMatchCase,				//�Ƿ����Сд
		OUT unsigned int  & nWordEndEnd,	//WORD��������һ����λ��
		OUT unsigned int  & bMatched,		//��ʾ�Ƿ�ɹ�ƥ��
		IN unsigned int nDepth);

	BOOL PrintCodeTree(list<CodeObjTree>::iterator & itNode,string & szRet,unsigned int nDepth,unsigned int nMaxDepth);


	BOOL LinkCodeTreeParent();
	BOOL LinkCodeTreeParent(list<CodeObjTree>::iterator & itNode,list<CodeObjTree>::iterator & itParent);

	
};
