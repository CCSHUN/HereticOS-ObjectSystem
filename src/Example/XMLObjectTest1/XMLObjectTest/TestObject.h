#pragma once

#define MAKESTRUCTINFO(_name)

struct _tagTestSubObject
{
	tstring								szSubObjectName;		//������
	unsigned int						nSubObjectType;			//��������
	float								fSubObject;				//�������
	double								lfSubObject;			//�������
	int									iSubObject;				//�������
	BOOL								bSubVal;
	SER_TO_X<tstring,Base64ZipString>	szSubVal;				//����ַ�����XML��Ӧ��base64zipת��
};





struct _tagTestObject
{
	tstring								szObjectName;		//������
	unsigned int						nObjectType;		//��������
	char								tCharArray[256];	//tCharArray
	UINT								tUintArray[256];	//tUintArray
	unsigned int						nVal;		
	int									iVal;
	float								fVal;				//����ֵ
	double								lfVal;				//����ֵ
	BOOL								bVal;				
	SER_TO_X<tstring,Base64ZipString>	szVal;				//����ַ�����XML��Ӧ��base64zipת��
	_tagTestSubObject					SubObject;
	vector<_tagTestSubObject>			SubObjectArray;		//�Ӷ�������
	map<tstring,_tagTestSubObject,less<tstring> > SubObjectMap;	//map��������
};





#include ".\ObjectSerDef\_tagTestSubObject_StructInfo.h"
MAKESTRUCTINFO(_tagTestSubObject)

#include ".\ObjectSerDef\_tagTestObject_StructInfo.h" 
MAKESTRUCTINFO(_tagTestObject)
