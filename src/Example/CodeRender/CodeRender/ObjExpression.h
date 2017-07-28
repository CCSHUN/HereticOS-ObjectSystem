#pragma once


#include <vector>
#include <string>
#include <list>
#include <map>
using namespace std;

#include "Tokenizer.h"




/*
语言解析表达式规范
+  连接两个规则表达式名称，表示两个规则名指定的表达式按照先后顺序必须都匹配成功（形成多个代码对象）
|	 连接两个规则表达式名称，表示两个规则名指定的表达式只要有一个匹配成功则该表达式成功(只针对当前的一个代码对象)
=  包表达式声明定义
N<规则表达式名,循环控制达式名> 表示指定的规则表达式要做N次匹配,直到当前包结束或者没有匹配到循环控制达式时 ，循环控制达式不影响匹配结果
包<包起始规则表达式,包终止规则表达式,规则表达式名> 指定一个包的解析匹配规则
xxx<yyy>	表示一个语法匹配规则表达式名和表达式类型名 如 函数声明1<函数声明>=返回类型1+调用约定|NULL
NULL<规则表达式名> 表示表达式匹配失败也可返回成功（将填充默认值）
NULL_TRUE 特殊表达式，直接返回表达式匹配成功 用于解析预留接口
NULL_FALSE 特殊表达式，直接返回表达式匹配失败 用于解析预留接口
xxx(yyy)	表示一个词法匹配规则表达式名和表达式类型名 如 句尾1(句尾)=; 词内置类型匹配名有 词型，符号型，整型，浮点型，字符串型,字符型 暂时合并到表达式
ROOT<表达式名> 表示语义解析根入口
G(xxx)	表示一个表达式 G(表达式名1|表达式名2)	暂时不支持
WORD(xxx)	表匹配一个词 比如WORD(;)


比如定义C++ 类声明的解析规则
ROOT<类声明>
类声明<类声明>=类声明1<类声明>|类声明2<类声明>|类声明3<类声明>
类声明1<类声明>=NULL<类模板声明>+类头关键词+类名+NULL<继承类表>+包<类声明包开始,类声明包结束,类声明体>
类声明2<类声明>=NULL_FALSE
类声明3<类声明>=NULL_FALSE

类模板声明<类模板声明>=类模板声明1|类模板声明2
类模板声明1<类模板声明>=模板关键词+包<模板声明参数包开始,模板声明参数包结束,模板声明参数表>
类模板声明2<类模板声明>=NULL
模板声明参数包开始<模板声明参数包开始>=<
模板声明参数包结束<模板声明参数包结束>=>
模板声明参数表<模板声明参数表>=N<模板声明参数声明>+模板声明参数声明尾
模板声明参数声明<模板声明参数声明>=WORD(typename)+词型+WORD(,)
模板声明参数声明尾<模板声明参数声明尾>=WORD(typename)+词型+WORD(>)

类头关键字<类头关键字>=word(class)
类名<类名>=词型

继承类表=WORD(:)+N<继承类表参数>+继承类表参数结束
继承类表参数<继承类表参数>=word(public)+词型+word(,)
继承类表参数结束<继承类表参数结束>=word(public)+词型

类声明包开始<类声明包开始>=word({)
类声明包结束<类声明包结束>=word(})+word(;)

类声明体<类声明体>=N<类声明体内容>
类声明体内容1<类声明体内容>=word(public)+word(:)
类声明体内容2<类声明体内容>=word(protected)+word(:)
类声明体内容3<类声明体内容>=word(private)+word(:)
类声明体内容4<类声明体内容>=类声明体内容1|类声明体内容2|类声明体内容3

类声明体内容5<类声明体内容>=函数声明|函数定义
类声明体内容6<类声明体内容>=变量声明|变量声明表
类声明体内容7<类声明体内容>=NULL_FALSE
类声明体内容8<类声明体内容>=NULL_FALSE

类声明体内容<类声明体内容>=类声明体内容1|类声明体内容2|类声明体内容3|类声明体内容4|类声明体内容5|类声明体内容6|类声明体内容7|类声明体内容8

函数定义<函数定义>=NULL_FALSE
函数声明<函数声明>=函数返回型别+NULL<函数调用约定>+函数名+包<函数声明包开始,函数声明包结束,函数声明参数表>
函数返回型别<函数返回型别>=词型
函数调用约定<函数调用约定>=word(_stdcall)|word(__stdcall)
函数名<函数名>=词型
函数声明包开始<函数声明包开始>=WORD(()
函数声明包结束<函数声明包结束>=WORD())+WORD(;)
函数声明参数表<函数声明参数表>=N<函数声明参数声明>+函数声明参数声明尾
函数声明参数声明<函数声明参数声明>=词型+词型+word(,)
函数声明参数声明尾<函数声明参数声明尾>=词型+词型+word(\))

变量声明<变量声明>=词型+词型+word(;)
变量声明表<变量声明表>=N<变量声明表单元变量声明>+变量声明表单元变量声明尾
变量声明表单元变量声明<变量声明表单元变量声明>=词型+词型+word(,)
变量声明表单元变量声明尾<变量声明表单元变量声明尾>=词型+词型+word(;)
*/
class CGenerateCodeTree;
class CObjExpression;

typedef struct _tagExpressionContext
{
	string name;			//表达式名
	string nametype;		//表达式类型
	vector<WordSet> Array;	//表达式词法分析数组

	//词数;
	unsigned int nNumWord;
	//运行时状态
	//解析终止坐标 用于控制N<>的执行终止控制
	IN unsigned int nEndPos;
	//匹配解析到的目标串长度。
	OUT unsigned int nDestLen;
	//要匹配的目标串起始坐标
	IN unsigned int nBeginPos;

	//关联的codetree处理对象;
	CGenerateCodeTree * pCodeTree;
	//关联的表达式管理器对象
	CObjExpression * pObjExpression;
	unsigned int nExpressionEnv;
}ExpressionContext,*PExpressionContext;

#define COMMANDEND	"$ENDEND#"

template <typename ContainerType,typename ContainerItType>
BOOL FindIt(ContainerType & Container, ContainerItType & it)
{
	ContainerItType itPos=Container.begin();
	for(;itPos!=Container.end();itPos++)
	{
		if(itPos==it)
		{
			return TRUE;
		}
	}
	return FALSE;
}

class CObjExpression
{
public:
	
	//unsigned int m_iParse;
	void Clone(CObjExpression * pSrcObjExpression)
	{
		m_ExpEnvMap = pSrcObjExpression->m_ExpEnvMap;
		//m_RuleNameMap = pSrcObjExpression->m_RuleNameMap;
		ParseRuleMapType::iterator itPos = pSrcObjExpression->m_RuleNameMap.begin();
		for (; itPos!= pSrcObjExpression->m_RuleNameMap.end(); itPos++)
		{
			ExpressionContext Context = itPos->second;
			Context.pObjExpression = this;
			m_RuleNameMap[Context.name] = Context;
			//Context.
		}

	}
	typedef  map<string,ExpressionContext,less<string> > ParseRuleMapType;

	ParseRuleMapType m_RuleNameMap;
	vector<ExpressionContext> m_RootRuleName;
	struct _tagExpEnv
	{
		string szExpEnvPath;
	};
	map<unsigned int, _tagExpEnv, less<unsigned int>> m_ExpEnvMap;
	CObjExpression(void);
	~CObjExpression(void);
	BOOL AddExpression(const char * pExpressionFilePath, const char * pExpEnvPath);
	
	BOOL AddExpression(vector<string> & ExpressionArray, unsigned int nExpEnv);

	BOOL FindRuleContext(ParseRuleMapType::iterator & itRuleContext,string & RuleName,unsigned int nDepth);


	BOOL GetCommandTypeAndLen(
		IN ExpressionContext & Context,
		IN unsigned int nCommand,
		OUT string & Command,
		OUT unsigned int & nCommandLen,
		IN unsigned int nDepth
		);

private:

	BOOL ReadCommandLine(const char * pFilePath ,vector<char *> & pCommandArray,char ** pBuf);
	
	BOOL AddExpression(char ** pExpression, unsigned int nExpEnv);
};
