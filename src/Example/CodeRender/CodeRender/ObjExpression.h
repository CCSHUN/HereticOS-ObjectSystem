#pragma once


#include <vector>
#include <string>
#include <list>
#include <map>
using namespace std;

#include "Tokenizer.h"




/*
���Խ������ʽ�淶
+  ��������������ʽ���ƣ���ʾ����������ָ���ı��ʽ�����Ⱥ�˳����붼ƥ��ɹ����γɶ���������
|	 ��������������ʽ���ƣ���ʾ����������ָ���ı��ʽֻҪ��һ��ƥ��ɹ���ñ��ʽ�ɹ�(ֻ��Ե�ǰ��һ���������)
=  �����ʽ��������
N<������ʽ��,ѭ�����ƴ�ʽ��> ��ʾָ���Ĺ�����ʽҪ��N��ƥ��,ֱ����ǰ����������û��ƥ�䵽ѭ�����ƴ�ʽʱ ��ѭ�����ƴ�ʽ��Ӱ��ƥ����
��<����ʼ������ʽ,����ֹ������ʽ,������ʽ��> ָ��һ�����Ľ���ƥ�����
xxx<yyy>	��ʾһ���﷨ƥ�������ʽ���ͱ��ʽ������ �� ��������1<��������>=��������1+����Լ��|NULL
NULL<������ʽ��> ��ʾ���ʽƥ��ʧ��Ҳ�ɷ��سɹ��������Ĭ��ֵ��
NULL_TRUE ������ʽ��ֱ�ӷ��ر��ʽƥ��ɹ� ���ڽ���Ԥ���ӿ�
NULL_FALSE ������ʽ��ֱ�ӷ��ر��ʽƥ��ʧ�� ���ڽ���Ԥ���ӿ�
xxx(yyy)	��ʾһ���ʷ�ƥ�������ʽ���ͱ��ʽ������ �� ��β1(��β)=; ����������ƥ������ ���ͣ������ͣ����ͣ������ͣ��ַ�����,�ַ��� ��ʱ�ϲ������ʽ
ROOT<���ʽ��> ��ʾ������������
G(xxx)	��ʾһ�����ʽ G(���ʽ��1|���ʽ��2)	��ʱ��֧��
WORD(xxx)	��ƥ��һ���� ����WORD(;)


���綨��C++ �������Ľ�������
ROOT<������>
������<������>=������1<������>|������2<������>|������3<������>
������1<������>=NULL<��ģ������>+��ͷ�ؼ���+����+NULL<�̳����>+��<����������ʼ,������������,��������>
������2<������>=NULL_FALSE
������3<������>=NULL_FALSE

��ģ������<��ģ������>=��ģ������1|��ģ������2
��ģ������1<��ģ������>=ģ��ؼ���+��<ģ��������������ʼ,ģ����������������,ģ������������>
��ģ������2<��ģ������>=NULL
ģ��������������ʼ<ģ��������������ʼ>=<
ģ����������������<ģ����������������>=>
ģ������������<ģ������������>=N<ģ��������������>+ģ��������������β
ģ��������������<ģ��������������>=WORD(typename)+����+WORD(,)
ģ��������������β<ģ��������������β>=WORD(typename)+����+WORD(>)

��ͷ�ؼ���<��ͷ�ؼ���>=word(class)
����<����>=����

�̳����=WORD(:)+N<�̳�������>+�̳�����������
�̳�������<�̳�������>=word(public)+����+word(,)
�̳�����������<�̳�����������>=word(public)+����

����������ʼ<����������ʼ>=word({)
������������<������������>=word(})+word(;)

��������<��������>=N<������������>
������������1<������������>=word(public)+word(:)
������������2<������������>=word(protected)+word(:)
������������3<������������>=word(private)+word(:)
������������4<������������>=������������1|������������2|������������3

������������5<������������>=��������|��������
������������6<������������>=��������|����������
������������7<������������>=NULL_FALSE
������������8<������������>=NULL_FALSE

������������<������������>=������������1|������������2|������������3|������������4|������������5|������������6|������������7|������������8

��������<��������>=NULL_FALSE
��������<��������>=���������ͱ�+NULL<��������Լ��>+������+��<������������ʼ,��������������,��������������>
���������ͱ�<���������ͱ�>=����
��������Լ��<��������Լ��>=word(_stdcall)|word(__stdcall)
������<������>=����
������������ʼ<������������ʼ>=WORD(()
��������������<��������������>=WORD())+WORD(;)
��������������<��������������>=N<����������������>+����������������β
����������������<����������������>=����+����+word(,)
����������������β<����������������β>=����+����+word(\))

��������<��������>=����+����+word(;)
����������<����������>=N<����������Ԫ��������>+����������Ԫ��������β
����������Ԫ��������<����������Ԫ��������>=����+����+word(,)
����������Ԫ��������β<����������Ԫ��������β>=����+����+word(;)
*/
class CGenerateCodeTree;
class CObjExpression;

typedef struct _tagExpressionContext
{
	string name;			//���ʽ��
	string nametype;		//���ʽ����
	vector<WordSet> Array;	//���ʽ�ʷ���������

	//����;
	unsigned int nNumWord;
	//����ʱ״̬
	//������ֹ���� ���ڿ���N<>��ִ����ֹ����
	IN unsigned int nEndPos;
	//ƥ���������Ŀ�괮���ȡ�
	OUT unsigned int nDestLen;
	//Ҫƥ���Ŀ�괮��ʼ����
	IN unsigned int nBeginPos;

	//������codetree�������;
	CGenerateCodeTree * pCodeTree;
	//�����ı��ʽ����������
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
