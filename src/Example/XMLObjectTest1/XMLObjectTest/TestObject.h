#pragma once

#define MAKESTRUCTINFO(_name)

struct _tagTestSubObject
{
	tstring								szSubObjectName;		//对象名
	unsigned int						nSubObjectType;			//对象类型
	float								fSubObject;				//浮点对象
	double								lfSubObject;			//浮点对象
	int									iSubObject;				//浮点对象
	BOOL								bSubVal;
	SER_TO_X<tstring,Base64ZipString>	szSubVal;				//如果字符串是XML则应用base64zip转码
};





struct _tagTestObject
{
	tstring								szObjectName;		//对象名
	unsigned int						nObjectType;		//对象类型
	char								tCharArray[256];	//tCharArray
	UINT								tUintArray[256];	//tUintArray
	unsigned int						nVal;		
	int									iVal;
	float								fVal;				//浮点值
	double								lfVal;				//浮点值
	BOOL								bVal;				
	SER_TO_X<tstring,Base64ZipString>	szVal;				//如果字符串是XML则应用base64zip转码
	_tagTestSubObject					SubObject;
	vector<_tagTestSubObject>			SubObjectArray;		//子对象容器
	map<tstring,_tagTestSubObject,less<tstring> > SubObjectMap;	//map容器对象
};





#include ".\ObjectSerDef\_tagTestSubObject_StructInfo.h"
MAKESTRUCTINFO(_tagTestSubObject)

#include ".\ObjectSerDef\_tagTestObject_StructInfo.h" 
MAKESTRUCTINFO(_tagTestObject)
