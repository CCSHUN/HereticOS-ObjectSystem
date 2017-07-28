///////////////////////////////////////////////////////////////////////////////////
//	Copyright 2017 shushen,ye
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//	http://www.apache.org/licenses/LICENSE-2.0
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
///////////////////////////////////////////////////////////////////////////////////

//�ṹ����Ϣ��¼
//���ߣ�Ҷ���� 2010.6.10
//���л��⹤�ߺ�

#pragma once
#include "windows.h"

#include <vector>
#include <string>
#include <list>
#include <map>

#include "AutoVar.h"

using namespace std;

//���л���������
#define Ser_Def(_type,objname) Serialize_##_type objname;
//���л���ָ���Ķ���

#define Ser(_type,objname,StorageObject)  Ser_Def(_type,objname)\
	objname.init(NULL,_T(#_type),0,&StorageObject);\


#define SerObjectToAnsiXmlFileEx(Type,SerType,object,FilePath) {\
	SerType data;\
	XMLStorageObject XmlFile;\
	XmlFile.init(tstring(FilePath),ToFile,Ansi);\
	data.init(NULL,_T(#object),0,&XmlFile);\
	data=object;\
	data.Save(&XmlFile);}\

#define SerObjectToAnsiXmlBufferEx(Type,SerType,object,stringBuf) {\
	SerType data;\
	XMLStorageObject XmlFile;\
	XmlFile.init(tstring(_T("")),ToBuffer,Ansi);\
	data.init(NULL,_T(#object),0,&XmlFile);\
	data=object;\
	data.Save(&XmlFile);\
	stringBuf=(char *)CMyString((TCHAR *)XmlFile.m_XmlBuffer.c_str(),\
	XmlFile.m_XmlBuffer.length()*sizeof(TCHAR));\
}\

#define SerObjectToUnicodeXmlBufferEx(Type,SerType,object,stringBuf) {\
	SerType data;\
	XMLStorageObject XmlFile;\
	XmlFile.init(tstring(_T("")),ToBuffer,Unicode);\
	data.init(NULL,_T(#object),0,&XmlFile);\
	data=object;\
	data.Save(&XmlFile);\
	stringBuf=(WCHAR *)CMyString((TCHAR *)XmlFile.m_XmlBuffer.c_str(),\
	XmlFile.m_XmlBuffer.length()*sizeof(TCHAR));\
}\





#define SerObjectToAnsiXmlFile(Type,object,FilePath) SerObjectToAnsiXmlFileEx(Type,Serialize_##Type,object,FilePath)
#define SerObjectToAnsiXmlBuffer(Type,object,stringBuf)  SerObjectToAnsiXmlBufferEx(Type,Serialize_##Type,object,stringBuf) 
#define SerObjectToUnicodeXmlBuffer(Type,object,stringBuf) SerObjectToUnicodeXmlBufferEx(Type,Serialize_##Type,object,stringBuf) 

#ifdef _UNICODE

#define SerObjectToXmlBuffer SerObjectToUnicodeXmlBuffer
#define SerObjectToXmlBufferEx SerObjectToUnicodeXmlBufferEx 
#else

#define SerObjectToXmlBuffer SerObjectToAnsiXmlBuffer
#define SerObjectToXmlBufferEx SerObjectToAnsiXmlBufferEx 
#endif


#define SerTCHARXmlBufferToObjectEx(Type,SerType,object,XmlBufer) {\
	SerType data;\
	XMLStorageObject XmlFile;\
	XmlFile.init(tstring((TCHAR *)XmlBufer),ToBuffer,Ansi);\
	data.init(NULL,_T(#object),0,&XmlFile);\
	if(data.Load(&XmlFile)){object=data;}\
	object=data;}\

#define SerAnsiFileToObjectEx(Type,SerType,object,FilePath) {\
	SerType data;\
	XMLStorageObject XmlFile;\
	XmlFile.init(tstring((TCHAR *)FilePath),ToFile,Ansi);\
	data.init(NULL,_T(#object),0,&XmlFile);\
	if(data.Load(&XmlFile)){object=data;}\
	}\


#define SerTCHARXmlBufferToObject(Type,object,XmlBufer) SerTCHARXmlBufferToObjectEx(Type,Serialize_##Type,object,XmlBufer) 
#define SerAnsiFileToObject(Type,object,FilePath)  SerAnsiFileToObjectEx(Type,Serialize_##Type,object,FilePath) 


/*
ʹ�÷���

Ҫ���л���Ŀ�궼����ڽṹ��������

�����л�֧�ֵĻ������л��ͱ� stl::vector stl::map ��vector mapֻ֧�ֻ���Ӧ�÷���������Ԫ�����Ϳ�֧��Ƕ�׻�����֧�����ͣ���vectorǶ��map��stl::string char������ double�� 4�ֽ����ͣ�64λ��Ҫд�����ػ�ģ��
����������Ĭ����4�ֽ�int�����л���������Զ����4�ֽ�������Ҫ����޸Ľű��� MAKE_�Ƿ�����ֵ�ڴ��ͱ�


1. �ṹ����Ԫ���������л�
����Ҫ���л��ṹ���е�������Ԫ��ʱ����һͷ�ļ��ж���ýṹ��Ȼ��MAKESTRUCTINFO ָ������ѽ���л��Ľṹ��

2. ��ֵ�������л� ֧�ֵ����Ͷ��� MAKE_�Ƿ�����ֵ�ͱ� �ж���

3. ���󲿷����л�������ֵ�ǵ�ֵ����������ҪΪ���ֵ������������л�����ʱ���������л���16�����ַ����������
������ԭ���ϰ��յ�ֵ���л��������ڽű���  MAKE_�Ƿ�����ֵ�����ͱ� ������Լ���������ͣ�Ȼ��Ϊ�������дһ���ػ������л�ģ��
�� template<>
class Serialize_BaseObject<string>

4. �������л����������л���֧�ֶ����ṹ�����飬ֻ֧�ֻ�����ֵ���͵��������л���MAKE_�Ƿ�����ֵ�ڴ��ͱ� �ж�����ͱ�


*/
/*
typedef struct _tagStructInfoSet
{
	_tagStructInfoSet * pStructAddr;		//������Ϣ��ַ
	unsigned int		nFieldOffset;		//�ֶ�ƫ��	
	char	*			pFeildFunctionName;	//���鹦������
	char	*			pFeildTypeName;		//�ֶ�������
	char	*			pFeildName;			//�ֶ���
	unsigned	int		nNum;				//��������飬�������������������������������1
}StructInfoSet,*PStructInfoSet;

#define OffsetField(StructName,FieldName) ((unsigned int)(&((StructName*)0)->FieldName))


StructInfoSet g_StructInfo__PROCESS_MEMORY_COUNTERS[]={
	{NULL,		OffsetField(_PROCESS_MEMORY_COUNTERS,cb),		"DWORD",		"cb",		0} ,
	{NULL,		OffsetField(_PROCESS_MEMORY_COUNTERS,PageFaultCount),		"DWORD",		"PageFaultCount",		0} ,
	{NULL,		OffsetField(_PROCESS_MEMORY_COUNTERS,PeakWorkingSetSize),		"SIZE_T",		"PeakWorkingSetSize",		0} ,
	{NULL,		OffsetField(_PROCESS_MEMORY_COUNTERS,WorkingSetSize),		"SIZE_T",		"WorkingSetSize",		0} ,
	{NULL,		OffsetField(_PROCESS_MEMORY_COUNTERS,QuotaPeakPagedPoolUsage),		"SIZE_T",		"QuotaPeakPagedPoolUsage",		0} ,
	{NULL,		OffsetField(_PROCESS_MEMORY_COUNTERS,QuotaPagedPoolUsage),		"SIZE_T",		"QuotaPagedPoolUsage",		0} ,
	{NULL,		OffsetField(_PROCESS_MEMORY_COUNTERS,QuotaPeakNonPagedPoolUsage),		"SIZE_T",		"QuotaPeakNonPagedPoolUsage",		0} ,
	{NULL,		OffsetField(_PROCESS_MEMORY_COUNTERS,QuotaNonPagedPoolUsage),		"SIZE_T",		"QuotaNonPagedPoolUsage",		0} ,
	{NULL,		OffsetField(_PROCESS_MEMORY_COUNTERS,PagefileUsage),		"SIZE_T",		"PagefileUsage",		0} ,
	{NULL,		OffsetField(_PROCESS_MEMORY_COUNTERS,PeakPagefileUsage),		"SIZE_T",		"PeakPagefileUsage",		0},
	{NULL,0,NULL,NULL,0}
};

StructInfoSet g_StructInfo__IO_COUNTERS[]={
	{NULL,		OffsetField(_IO_COUNTERS,ReadOperationCount),		"ULONGLONG",		"ReadOperationCount",		0} ,
	{NULL,		OffsetField(_IO_COUNTERS,WriteOperationCount),		"ULONGLONG",		"WriteOperationCount",		0} ,
	{NULL,		OffsetField(_IO_COUNTERS,OtherOperationCount),		"ULONGLONG",		"OtherOperationCount",		0} ,
	{NULL,		OffsetField(_IO_COUNTERS,ReadTransferCount),		"ULONGLONG",		"ReadTransferCount",		0} ,
	{NULL,		OffsetField(_IO_COUNTERS,WriteTransferCount),		"ULONGLONG",		"WriteTransferCount",		0} ,
	{NULL,		OffsetField(_IO_COUNTERS,OtherTransferCount),		"ULONGLONG",		"OtherTransferCount",		0},
	{NULL,0,NULL,NULL,0}
};




StructInfoSet g_StructInfo__tagProcessInfo[]={
	{g_StructInfo__PROCESS_MEMORY_COUNTERS,		OffsetField(_tagProcessInfo,Meminfo),		"_PROCESS_MEMORY_COUNTERS",		"Meminfo",		0} ,
	{g_StructInfo__IO_COUNTERS,		OffsetField(_tagProcessInfo,IOInfo),		"_IO_COUNTERS",		"IOInfo",		0},
	{NULL,0,NULL,NULL,0}
};
*/


/*
typedef struct _tagFieldAttributes
{
	char * pFieldAttributeName;
	char * pFieldAttributeVal;
}FieldFieldAttributes,*PFieldFieldAttributes;
*/
//���л�����֧�ֵ��ַ�����
typedef enum
{
	Ansi,
	Unicode,
	UTF8,
}CharacterType;

//���л�����������
typedef enum
{
	DecString,		//ʮ�����ַ���
	BinString,		//�������ַ���
	HexString,		//ʮ�������ַ���
	Base64String,	//Base64�ַ���
	Base64ZipString,//Base64 Zip �ַ���
	XmlString,		//XML String
}SerDstType;


#include "BaseFunctionTool.h"
#include "SerializeInterface.h"
#include "StorageObject.h"
#include "BaseObjectSerialize.h"
#include "InterlayerContainer.h"
