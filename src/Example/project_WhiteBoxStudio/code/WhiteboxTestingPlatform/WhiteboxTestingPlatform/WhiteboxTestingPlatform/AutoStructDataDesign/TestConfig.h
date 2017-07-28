#pragma once

typedef __int64 IDType;

typedef struct _tagIDRecover
{
	IDType nID;
	//ID�����б�
	list<IDType>	tIDRecover;
};
//��������
typedef struct _tagParamDef
{
	IDType  nParamID;
	tstring szParamName;
	tstring szParamDesc;
	tstring szParamAttribute;
	//Ĭ�ϲ���ֵ
	tstring szDefaultParam;
	//�༭�����ֵ
	tstring szLastEditParamVal;
}ParamDef,*PParamDef;

//����
typedef struct _tagFuncAttribute
{
	//BOOL bMacro;
}FuncAttribute,*PFuncAttribute;
//���̱��ʽ����
typedef struct _tagFuncDef
{
	IDType nFuncID;
	tstring szFuncName;
	tstring szFuncDesc;
	tstring szFuncType;
	tstring FuncAttr;
	_tagIDRecover tParamidRecover;
	vector<_tagParamDef> m_ParamDefArray;
	
	//vector<tstring> m_DefaultParam;
}FuncDef,*PFuncDef;

typedef struct _tagFuncLib
{
	tstring szLibName;
	_tagIDRecover tidRecover;
	map<tstring,_tagFuncDef,less<tstring> > m_FuncLib; 
}FuncLib;




//���ʽ
typedef struct _tagExp
{
	tstring szExpName;//���ʽ��
	IDType nExpID;
	tstring szExpDesc;
	//������ID�б�
	vector<IDType> FuncIDArray;
	// ������ID������ֵ��
	map<IDType,vector<_tagParamDef>,less<IDType>> m_ExpValMap;
}Exp,*PExp;

typedef struct _tagExpLib
{
	tstring szLibName;
	_tagIDRecover tidRecover;
	map<tstring,_tagExp,less<tstring>> m_ExpLib;
}ExpLib,*PExpLib;


#include "ObjectSerDef\_tagIDRecover_StructInfo.h"
MAKESTRUCTINFO(_tagIDRecover)

#include "ObjectSerDef\_tagParamDef_StructInfo.h"
MAKESTRUCTINFO(_tagParamDef)

#include "ObjectSerDef\_tagFuncDef_StructInfo.h"
MAKESTRUCTINFO(_tagFuncDef)

#include "ObjectSerDef\_tagFuncLib_StructInfo.h"
MAKESTRUCTINFO(_tagFuncLib)

#include "ObjectSerDef\_tagExp_StructInfo.h"
MAKESTRUCTINFO(_tagExp)

#include "ObjectSerDef\_tagExpLib_StructInfo.h"
MAKESTRUCTINFO(_tagExpLib)



//��������
//�����̲���
typedef struct _tagParamRef
{
	IDType  nMacroID;//��ID
	IDType  nParamID;//����ID
}ParamRef,*PParamRef;

typedef struct _tagRealParam
{
	IDType  nParamID;
	tstring szParamName;
	tstring szParamDesc;
	tstring szParamAttribute;
	//Ĭ�ϲ���ֵ
	tstring szDefaultParam;
}RealParam,*PRealParam;

//���������
typedef struct _tagMacroParamDef
{
	IDType  nParamID;
	tstring szParamType; //ʵ�� ������
	_tagParamRef RefPar;
	_tagRealParam realPar;
	//�༭�����ֵ
	tstring szLastEditParamVal;
}MacroParamDef,*PMacroParamDef;

//����
typedef struct _tagMacroAttribute
{
	BOOL bRootMacro; //�Ƿ�Ϊ���ꡣ��������в�����Ϊʵ�Σ�����Ϊ���ã��Ҳ������Ӻ�
}MacroAttribute,*PMacroAttribute;

//�궨��
typedef struct _tagMacroDef
{
	IDType nMacroID;
	tstring szMacroName;
	tstring szMacroDesc;
	tstring szMacroType; //�������� �������� �������� ϵͳ���� ��������
	_tagMacroAttribute MacroAttr;

	//�Ӻ��б� IDType 0�� m_ParMap[0]��ʾ���������
	vector<IDType> ChildMacroIDArray;
	_tagIDRecover tParamidRecover;
	vector<_tagMacroParamDef> ChildParArray;
	
}MacroDef,*PMacroDef;

typedef struct _tagMacroLib
{
	tstring szLibName;
	_tagIDRecover tidRecover;
	map<IDType,_tagMacroDef,less<IDType> > libmap;
}MacroLib,*PMacroLib;


#include "ObjectSerDef\_tagParamRef_StructInfo.h"
MAKESTRUCTINFO(_tagParamRef)
#include "ObjectSerDef\_tagRealParam_StructInfo.h"
MAKESTRUCTINFO(_tagRealParam)
#include "ObjectSerDef\_tagMacroParamDef_StructInfo.h"
MAKESTRUCTINFO(_tagMacroParamDef)

#include "ObjectSerDef\_tagMacroAttribute_StructInfo.h"
MAKESTRUCTINFO(_tagMacroAttribute)
#include "ObjectSerDef\_tagMacroDef_StructInfo.h"
MAKESTRUCTINFO(_tagMacroDef)
#include "ObjectSerDef\_tagMacroLib_StructInfo.h"
MAKESTRUCTINFO(_tagMacroLib)