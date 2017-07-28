#pragma once

typedef __int64 IDType;

typedef struct _tagIDRecover
{
	IDType nID;
	//ID回收列表
	list<IDType>	tIDRecover;
};
//参数定义
typedef struct _tagParamDef
{
	IDType  nParamID;
	tstring szParamName;
	tstring szParamDesc;
	tstring szParamAttribute;
	//默认参数值
	tstring szDefaultParam;
	//编辑后的数值
	tstring szLastEditParamVal;
}ParamDef,*PParamDef;

//属性
typedef struct _tagFuncAttribute
{
	//BOOL bMacro;
}FuncAttribute,*PFuncAttribute;
//过程表达式定义
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




//表达式
typedef struct _tagExp
{
	tstring szExpName;//表达式名
	IDType nExpID;
	tstring szExpDesc;
	//过程名ID列表
	vector<IDType> FuncIDArray;
	// 过程名ID　参数值表
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



//参数定义
//引用刑参数
typedef struct _tagParamRef
{
	IDType  nMacroID;//宏ID
	IDType  nParamID;//参数ID
}ParamRef,*PParamRef;

typedef struct _tagRealParam
{
	IDType  nParamID;
	tstring szParamName;
	tstring szParamDesc;
	tstring szParamAttribute;
	//默认参数值
	tstring szDefaultParam;
}RealParam,*PRealParam;

//宏参数定义
typedef struct _tagMacroParamDef
{
	IDType  nParamID;
	tstring szParamType; //实参 引用型
	_tagParamRef RefPar;
	_tagRealParam realPar;
	//编辑后的数值
	tstring szLastEditParamVal;
}MacroParamDef,*PMacroParamDef;

//属性
typedef struct _tagMacroAttribute
{
	BOOL bRootMacro; //是否为根宏。根宏的所有参数都为实参，不能为引用，且不能有子宏
}MacroAttribute,*PMacroAttribute;

//宏定义
typedef struct _tagMacroDef
{
	IDType nMacroID;
	tstring szMacroName;
	tstring szMacroDesc;
	tstring szMacroType; //驱动用例 场景用例 期望评估 系统配置 测试用例
	_tagMacroAttribute MacroAttr;

	//子宏列表 IDType 0则 m_ParMap[0]表示自身参数表
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