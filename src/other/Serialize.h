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

//结构体信息记录
//作者：叶树深 2010.6.10
//序列化库工具宏

#pragma once
#include "windows.h"

#include <vector>
#include <string>
#include <list>
#include <map>

#include "AutoVar.h"

using namespace std;

//序列化对象声明
#define Ser_Def(_type,objname) Serialize_##_type objname;
//序列化到指定的对象

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
使用方法

要序列化的目标都存放在结构体声明中

本序列化支持的基本序列化型别 stl::vector stl::map （vector map只支持基本应用方法，容器元素类型可支持嵌套基本的支持类型，如vector嵌套map）stl::string char数组型 double型 4字节整型，64位需要写类型特化模板
单变量类型默认用4字节int型序列化，如果有自定义的4字节整型需要添加修改脚本中 MAKE_是否是数值内存型别


1. 结构体子元素完整序列化
当需要序列化结构体中的所有子元素时，在一头文件中定义好结构体然后MAKESTRUCTINFO 指定好需呀序列化的结构体

2. 单值变量序列化 支持的类型都在 MAKE_是否是数值型别 中定义

3. 对象部分序列化，比如值是单值变量，我需要为这个值制作特殊的序列化方法时，比如序列化到16进制字符串保存加载
这样，原则上按照单值序列化制作，在脚本的  MAKE_是否是数值对象型别 中添加自己定义的类型，然后为这个类型写一个特化的序列化模板
如 template<>
class Serialize_BaseObject<string>

4. 数组序列化，数组序列化不支持对象或结构体数组，只支持基本单值类型的数组序列化（MAKE_是否是数值内存型别 中定义的型别）


*/
/*
typedef struct _tagStructInfoSet
{
	_tagStructInfoSet * pStructAddr;		//类型信息地址
	unsigned int		nFieldOffset;		//字段偏移	
	char	*			pFeildFunctionName;	//建议功能类型
	char	*			pFeildTypeName;		//字段类型名
	char	*			pFeildName;			//字段名
	unsigned	int		nNum;				//如果是数组，则是数组声明的数量，如果不是则是1
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
//序列化对象支持的字符类型
typedef enum
{
	Ansi,
	Unicode,
	UTF8,
}CharacterType;

//序列化保存结果类型
typedef enum
{
	DecString,		//十进制字符串
	BinString,		//二进制字符串
	HexString,		//十六进制字符串
	Base64String,	//Base64字符串
	Base64ZipString,//Base64 Zip 字符串
	XmlString,		//XML String
}SerDstType;


#include "BaseFunctionTool.h"
#include "SerializeInterface.h"
#include "StorageObject.h"
#include "BaseObjectSerialize.h"
#include "InterlayerContainer.h"
