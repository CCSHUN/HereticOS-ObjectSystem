#ifndef _SERINI_H_
#define _SERINI_H_
#include "stdafx.h"
#include "windows.h"
//作者:叶树深2010.04.12 
#pragma warning(disable:4786 4005 4003 4002 4996)
//#pragma warning(once:4786 4003)  
#include <list>
#include <string>
#include <vector>
#define printf
using namespace std;

#define ROOT ROOT
//配置序列化

//序列化对象,提供最终序列化到的类型
class CSerializationObject
{
public:
	CSerializationObject(){};
	~CSerializationObject(){};
protected:
	
private:
};


struct ValueAddressBase
{
	char * m_ValName;
	unsigned int m_index;
};

struct ValueAddress : public ValueAddressBase
{
	typedef list<ValueAddressBase> ParentNameType;
	char * m_pszFile;
	 
	list<ValueAddressBase> m_pParentNameList;
	
};
class ValueDescBase : public ValueAddress
{
public:
	//ValueAddress m_addr;
	char * m_ValType;
	unsigned int m_nValSize;
	ValueDescBase(){};
	~ValueDescBase(){};
protected:
	
private:
};
template<typename _ValType>
class ValueDesc : public ValueDescBase
{
public:
	
	//_ValType m_Val;
	//_ValType m_DefaultVal;
	
	ValueDesc(){};
	~ValueDesc(){};
protected:
	
private:
};

template<typename _ValType>
class ValueDesc1 : public ValueDescBase
{
public:
	
	_ValType m_Val;
	_ValType m_DefaultVal;
	
	ValueDesc1(){};
	~ValueDesc1(){};
protected:
	
private:
};


#define MyObjectName(_ObjectName) _ObjectName##Object
#define MyObject(_ObjectName,_DataType,_Data) \
class MyObjectName(_ObjectName) \
{\
public:\
	 _DataType m_Data;\
	MyObjectName(_ObjectName)(){m_Data=_Data;};\
	~MyObjectName(_ObjectName)(){};\
protected:\
	\
private:\
};\


 #define ToStringObject(_data)  MyObject(_data,char*,#_data )

class CSerializationIniObject : public CSerializationObject
{
public:
	char * m_pszIniFile;
	CSerializationIniObject()
	{
		//m_pszIniFile=_FileName().m_pFileName;
	};
	CSerializationIniObject(char * pIniFile)
	{
		//m_pszIniFile=pIniFile;
	};

	bool init(string szIniFile)
	{
		//m_pszIniFile=szIniFile;
		return TRUE;
	}
	
	/*
	BOOL SerializationIntType(char * pszMainKey,char * pszSubKey,void * pData,DWORD nSize)
		{
			char hextab[16]={'0',
				'1','2','3','4',
				'5','6','7','8',
				'9','a','b','c',
				'd','e','f'
			};
	
			char * tmpbuf= new char[nSize*2+2];
			for(int i=0;i<nSize;i++)
			{
				tmpbuf[2*i]=hextab[pData[i]&0xf];
				tmpbuf[2*i+1]=hextab[pData[i]&0xf>>4];
			}
			tmpbuf[nSize*2+1]=0;
			return WritePrivateProfileString(pszMainKey,pszSubKey,tmpbuf,lpFilePath);
		}*/
	template<typename _Type>
	bool GetName(_Type & Val,string & szName)
	{
		char cpBuf[16] = {0};
		
		if(Val.m_pParentNameList.size()==0)
		{
			return FALSE;
		}
		ValueAddress::ParentNameType::iterator it=Val.m_pParentNameList.begin();
		//it++;
		ltoa(it->m_index,cpBuf,10);
		szName+=it->m_ValName;
		szName+="_";
		szName+=cpBuf;

		it++;
		for(;it!=Val.m_pParentNameList.end();it++)
		{
			ltoa(it->m_index,cpBuf,10);
			szName+="_";
			szName+=it->m_ValName;
			szName+="_";
			szName+=cpBuf;
		}

		//ltoa(Val.m_index,cpBuf,10);
		szName+="_";
		szName+=Val.m_ValName;
		//szName+="_";
		//szName+=cpBuf;
		return true;
	}
	template<typename _Type>
	bool GetMainKey(_Type & Val,string & szName)
	{
		ValueAddress::ParentNameType::iterator it=Val.m_pParentNameList.begin();
		szName+=it->m_ValName;
		return true;
	}


	template<typename _Type>
	BOOL clear(_Type & Val)
	{
		if(strlen(Val.m_ValName)==0)
		{
			FILE *fp=fopen(Val.m_pszFile,"w+");
			if(fp)/*以写的方式打开已经存的文件相当于是清空。*/
			{
				fclose(fp);
			}
			return TRUE;
		}
		return WritePrivateProfileStringA(Val.m_ValName,NULL,NULL,Val.m_pszFile);
	}

	//型别序列化
	BOOL Serialization(ValueDesc1<int> & Val)
	{
		char cpBuf[16] = {0};
		
		ltoa(Val.m_Val,cpBuf,10);
		//得到主键
		string szMainKey;
		GetMainKey(Val,szMainKey);
		string szName;
		GetName(Val,szName);
		return WritePrivateProfileStringA(szMainKey.c_str(),szName.c_str(),cpBuf,Val.m_pszFile);
	}

	BOOL Serialization(ValueDesc1<char *> & Val)
	{
		string szMainKey;
		GetMainKey(Val,szMainKey);
		string szName;
		GetName(Val,szName);
		return WritePrivateProfileStringA(szMainKey.c_str(),szName.c_str(),Val.m_Val,Val.m_pszFile);
	}


	BOOL GetData(ValueDesc1<int> & Val)
	{
		string szMainKey;
		GetMainKey(Val,szMainKey);
		if(szMainKey.length()==0)
		{
			szMainKey="NOFIND";
		}
		string szName;
		GetName(Val,szName);
		if(szName.length()==0)
		{
			szName="NOFIND";
		}

		Val.m_Val= GetPrivateProfileIntA(szMainKey.c_str(),szName.c_str(),Val.m_DefaultVal,Val.m_pszFile);
		return TRUE;
	}

	bool GetData(ValueDesc1<char *> & Val)
	{
		string szMainKey;
		GetMainKey(Val,szMainKey);
		if(szMainKey.length()==0)
		{
			szMainKey="NOFIND";
		}
		string szName;
		GetName(Val,szName);
		if(szName.length()==0)
		{
			szName="NOFIND";
		}
		GetPrivateProfileStringA(szMainKey.c_str(),szName.c_str(),Val.m_DefaultVal,Val.m_Val,Val.m_nValSize,Val.m_pszFile);
		return TRUE;
	}

	
	~CSerializationIniObject(){};
protected:
	
private:
};


//编译时参数固化


//MyTypeSerializationObjectinc(CSerializationIniObject,asd)

//MyTypeSerializationObjectinc(CSerializationIniObject,asd1)

//#define MyTypeSerializationObject(_Func,_FileName) CSerialization##_Func##_FileName##Object
//序列化方法
//==泛型型别序列化

//基本型别到序列化型别的变化
//#define StructureSerializationFunctiomClassCodeBase(_Field)  ##_Field
//#define StructureSerializationFunctiomClassCode1(_Field1) StructureSerializationFunctiomClassCopyCode1(_Field1),StructureSerializationFunctiomClassCopyCode1(_Field1)



//#define StructureSerializationFunctiomClassCode(_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10)
#define StructureConstructCodeBase(_Field)  sc.##_Field.m_nParentPos=(unsigned int)&(sc.##_Field)-(unsigned int)&sc; \
	sc.##_Field.m_pszFile=sc.m_pszFile;\
	sc.##_Field.m_ValName=#_Field; \

  
	
//宏参数展开
#define AddCode(_CodeBase,_Code1,_Code2) _Code1,_CodeBase(_Code2)
#define AddCode1(_CodeBase,_Code1) _CodeBase(_Code1)
#define AddCode2(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode1(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code2)\


#define AddCode3(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode2(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code3)\



#define AddCode4(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode3(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code4)\



#define AddCode5(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode4(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code5)\



#define AddCode6(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode5(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code6)\


#define AddCode7(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode6(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code7)\


#define AddCode8(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode7(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code8)\


#define AddCode9(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode8(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code9)\


#define AddCode10(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode9(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code10)\


#define AddCode11(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode10(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code11)\


#define AddCode12(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode11(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code12)\


#define AddCode13(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode12(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code13)\


#define AddCode14(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode13(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code14)\


#define AddCode15(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode14(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code15)\


#define AddCode16(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode15(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code16)\


#define AddCode17(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode16(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code17)\


#define AddCode18(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode17(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code18)\


#define AddCode19(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode18(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code19)\


#define AddCode20(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode(_CodeBase,AddCode19(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20),\
	_Code20)\


#define AddCodeN(_CodeBase,N,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20) \
	AddCode##N(_CodeBase,_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12,_Code13,_Code14,_Code15,_Code16,_Code17,_Code18,_Code19,_Code20)



#define StructureCopyCodeBase(_Field)  Dst.##_Field=Org.##_Field;

#define StructureResetBase(_Field) sc.##_Field.Reset();

#define Code1(_CodeBase,_Field1) _CodeBase(_Field1)
#define Code2(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code1(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field2)\

#define Code3(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code2(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field3)\
	
#define Code4(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code3(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field4)\

#define Code5(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code4(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field5)\
	
#define Code6(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code5(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field6)\

#define Code7(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code6(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field7)\
	
#define Code8(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code7(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field8)\

#define Code9(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code8(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field9)\
	
#define Code10(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code9(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field10)\

#define Code11(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code10(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field11)\
	
#define Code12(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code11(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field12)\

#define Code13(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code12(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field13)\
	
#define Code14(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code13(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field14)\

#define Code15(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code14(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field15)\
	

#define Code16(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code15(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field16)\
	
#define Code17(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code16(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field17)\


#define Code18(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code17(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field18)\

#define Code19(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code18(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field19)\

#define Code20(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code19(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	_CodeBase(_Field20)\

#define Code(_CodeBase,_num,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	Code##_num(_CodeBase,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20)


#define VAR_DEF_COPYCODE_CHAR(_Field,_Len,_Default) { StructureCopyCodeBase(_Field) };
#define VAR_DEF_COPYCODE1_CHAR(_Field,_Len,_Default) { strcpy(Dst.##_Field,(char *)Org.##_Field); };
#define VAR_DEF_CONSTRUCT_INIOBJ_CHAR(_Field,_Len,_Default) StructureConstructCodeBase(_Field,_Len,_Default) sc.##_Field.m_DefaultVal=_Default;\
	sc.##_Field.m_nValSize=_Len;\


#define VAR_DEF_COPYCODE_INT(_Field,_Len,_Default) {StructureCopyCodeBase(_Field)}
#define VAR_DEF_COPYCODE1_INT(_Field,_Len,_Default) {StructureCopyCodeBase(_Field)}
#define VAR_DEF_CONSTRUCT_INIOBJ_INT(_Field,_Len,_Default) {StructureConstructCodeBase(_Field)}; sc.##_Field.m_DefaultVal=_Default; \
sc.##_Field.m_nValSize=_Len;\

#define VAR_DEF_COPYCODE_UINT(_Field,_Len,_Default) {StructureCopyCodeBase(_Field)}
#define VAR_DEF_COPYCODE1_UINT(_Field,_Len,_Default) {StructureCopyCodeBase(_Field)}
#define VAR_DEF_CONSTRUCT_INIOBJ_UINT(_Field,_Len,_Default) {StructureConstructCodeBase(_Field)}; sc.##_Field.m_DefaultVal=_Default; \
	sc.##_Field.m_nValSize=_Len;\


#define VAR_DEF_COPYCODE_UCHAR(_Field,_Len,_Default) {StructureCopyCodeBase(_Field)}
#define VAR_DEF_COPYCODE1_UCHAR(_Field,_Len,_Default) {StructureCopyCodeBase(_Field)}
#define VAR_DEF_CONSTRUCT_INIOBJ_UCHAR(_Field,_Len,_Default) {StructureConstructCodeBase(_Field)}; sc.##_Field.m_DefaultVal=_Default; \
sc.##_Field.m_nValSize=_Len;\

#define VAR_DEF_COPYCODE_LONG(_Field,_Len,_Default) {StructureCopyCodeBase(_Field)}
#define VAR_DEF_COPYCODE1_LONG(_Field,_Len,_Default) {StructureCopyCodeBase(_Field)}
#define VAR_DEF_CONSTRUCT_INIOBJ_LONG(_Field,_Len,_Default) {StructureConstructCodeBase(_Field)}; sc.##_Field.m_DefaultVal=_Default; \
sc.##_Field.m_nValSize=_Len;\

#define VAR_DEF_COPYCODE_ULONG(_Field,_Len,_Default) {StructureCopyCodeBase(_Field)}
#define VAR_DEF_COPYCODE1_ULONG(_Field,_Len,_Default) {StructureCopyCodeBase(_Field)}
#define VAR_DEF_CONSTRUCT_INIOBJ_ULONG(_Field,_Len,_Default) {StructureConstructCodeBase(_Field)}; sc.##_Field.m_DefaultVal=_Default; \
sc.##_Field.m_nValSize=_Len;\

#define VAR_DEF_COPYCODE_USHORT(_Field,_Len,_Default) {StructureCopyCodeBase(_Field)}
#define VAR_DEF_COPYCODE1_USHORT(_Field,_Len,_Default) {StructureCopyCodeBase(_Field)}
#define VAR_DEF_CONSTRUCT_INIOBJ_USHORT(_Field,_Len,_Default) {StructureConstructCodeBase(_Field)}; sc.##_Field.m_DefaultVal=_Default; \
sc.##_Field.m_nValSize=_Len;\

#define VAR_DEF_COPYCODE__SHORT(_Field,_Len,_Default) {StructureCopyCodeBase(_Field)}
#define VAR_DEF_COPYCODE1__SHORT(_Field,_Len,_Default) {StructureCopyCodeBase(_Field)}
#define VAR_DEF_CONSTRUCT_INIOBJ__SHORT(_Field,_Len,_Default) {StructureConstructCodeBase(_Field)}; sc.##_Field.m_DefaultVal=_Default; \
	sc.##_Field.m_nValSize=_Len;\


#define VAR_DEF_COPYCODE_STRUCT(_Field,_Len,_Default) StructureCopyCodeBase(_Field)
#define VAR_DEF_COPYCODE1_STRUCT(_Field,_Len,_Default) StructureCopyCodeBase(_Field)
#define VAR_DEF_CONSTRUCT_INIOBJ_STRUCT(_Field,_Len,_Default) StructureConstructCodeBase(_Field) 
//#define _STRUCT(_Field,_Len,_Default) _STRUCT(_Field,_Len,_Default)

//#define AddCode3(_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12) AddCode(AddCode2(_Code1,_Code2),_Code2)
//#define AddCode3(_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12) AddCode(AddCode2(_Code1,_Code2),_Code2)
//#define AddCode3(_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12) AddCode(AddCode2(_Code1,_Code2),_Code2)
//#define AddCode3(_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12) AddCode(AddCode2(_Code1,_Code2),_Code2)
//#define AddCode3(_Code1,_Code2,_Code3,_Code4,_Code5,_Code6,_Code7,_Code8,_Code9,_Code10,_Code11,_Code12) AddCode(AddCode2(_Code1,_Code2),_Code2)
 
#define StructureSerializationFunctiomClassName(_BaseStructureType) CStructureSerializationFunction##_BaseStructureType
#define StructureSerializationFunctiomClassName1(_MainType,_SubType) CStructureSerializationFunction##_SubType
#define StructureSerializationFunctiomClassName2(_MainType,_SubType) _SubType##Serialization
#define StructureSerializationFunctiomClassName3(_MainType,_SubType) _SubType

#define StructureSerializationFunctiomClass(_BaseStructureType,_FileName,_FieldName) StructureSerializationFunctiomClassName(_BaseStructureType)##<_BaseStructureType,\
_BaseStructureType##Serialization##<CSerializationIniObject,_FileName>  ,_FileName , _FieldName>

#define StructureSerializationFunctiomClass1(_BaseStructureType,_FileName,_FieldName) StructureSerializationFunctiomClassName1##_BaseStructureType<StructureSerializationFunctiomClassName3##_BaseStructureType,\
StructureSerializationFunctiomClassName2##_BaseStructureType##<CSerializationIniObject,_FileName>  ,_FileName , _FieldName>


//MakeStructureSerializationFunctiomClass(Code1(StructureCopyCodeBase,a),Code1(StructureConstructCodeBase,a),test1,data,ConfigIni)
//MakeStructureSerializationFunctiomClass(Code2(StructureCopyCodeBase,data,s),Code2(StructureConstructCodeBase,data,s),test2,NODEF,ConfigIni)

//template<typename _SerializationStructureType,typename _BaseStructureType,typename _FileName>
#define VAR_DEF_COPYCODE(_MainType,_SubType)	 VAR_DEF_COPYCODE##_MainType
#define VAR_DEF_COPYCODE1(_MainType,_SubType)	 VAR_DEF_COPYCODE##_MainType
#define VAR_DEF_CONSTRUCT_INIOBJ(_MainType,_SubType)	 VAR_DEF_CONSTRUCT_INIOBJ##_MainType
#define _VAR_DEF_COPYCODE(_TypeName,_Field,_Len,_Default) VAR_DEF_COPYCODE##_TypeName(_Field,_Len,_Default)
#define _VAR_DEF_COPYCODE1(_TypeName,_Field,_Len,_Default) VAR_DEF_COPYCODE1##_TypeName(_Field,_Len,_Default)
#define _VAR_DEF_CONSTRUCT_INIOBJ(_TypeName,_Field,_Len,_Default) VAR_DEF_CONSTRUCT_INIOBJ##_TypeName(_Field,_Len,_Default)
#define COPYCODEBase(_Field) _VAR_DEF_COPYCODE##_Field 
#define COPYCODE1Base(_Field) _VAR_DEF_COPYCODE1##_Field
#define CONSTRUCTBase(_Field) _VAR_DEF_CONSTRUCT_INIOBJ##_Field 

//普通结构定义
#define VAR_DEF(_MainType,_SubType) _SubType VAR_DEF##_MainType
#define VAR_DEF_STRUCT(_Field,_Len,_Default) _Field; 
#define VAR_DEF_UINT(_Field,_Len,_Default)  unsigned int _Field; 
#define VAR_DEF_ULONG(_Field,_Len,_Default) unsigned long _Field; 
#define VAR_DEF_UCHAR(_Field,_Len,_Default) unsigned char _Field; 
#define VAR_DEF_INT(_Field,_Len,_Default) int _Field; 
#define VAR_DEF_LONG(_Field,_Len,_Default) long _Field; 
#define VAR_DEF__SHORT(_Field,_Len,_Default) short _Field; 
#define VAR_DEF_USHORT(_Field,_Len,_Default) unsigned short _Field; 
#define VAR_DEF_CHAR(_Field,_Len,_Default) char _Field##[##_Len##]; 
#define _VAR_DEF(_TypeName,_Field,_Len,_Default) VAR_DEF##_TypeName(_Field,_Len,_Default)
#define VarBase(_Field) _VAR_DEF##_Field

//序列化结构定义
#define VAR_SER_DEF(_MainType,_SubType) VAR_SER_DEF##_MainType
#define VAR_SER_DEF_STRUCT_MAINTYPE(_MainType,_SubType) _MainType
#define VAR_SER_DEF_STRUCT_SUBTYPE(_MainType,_SubType) _SubType
#define VAR_SER_DEF_STRUCT_SUBTYPE1(_TypeName) VAR_SER_DEF_STRUCT_SUBTYPE##_TypeName
#define VAR_SER_DEF_STRUCT_SUBTYPESER(_MainType,_SubType) _SubType##Serialization
#define VAR_SER_DEF_STRUCT(_TypeName,_Field,_Len,_Default)  ToStringObject(_Field) \
CSerializationType<_SerObjType,VAR_SER_DEF_STRUCT_SUBTYPESER##_TypeName##<CSerializationIniObject,_FileNameType > ,\
StructureSerializationFunctiomClass1( _TypeName ,_FileNameType,MyObjectName(_Field) ),VAR_SER_DEF_STRUCT_SUBTYPE##_TypeName > _Field; \


#define VAR_SER_DEF_UCHAR(_TypeName,_Field,_Len,_Default) CSerializationType<_SerObjType,int,int,int> _Field;
#define VAR_SER_DEF_UINT(_TypeName,_Field,_Len,_Default) CSerializationType<_SerObjType,int,int,int> _Field;
#define VAR_SER_DEF_ULONG(_TypeName,_Field,_Len,_Default) CSerializationType<_SerObjType,int,int,int> _Field; 
#define VAR_SER_DEF_INT(_TypeName,_Field,_Len,_Default) CSerializationType<_SerObjType,int,int,int> _Field; 
#define VAR_SER_DEF_LONG(_TypeName,_Field,_Len,_Default) CSerializationType<_SerObjType,int,int,int> _Field; 
#define VAR_SER_DEF_USHORT(_TypeName,_Field,_Len,_Default) CSerializationType<_SerObjType,int,int,int> _Field; 
#define VAR_SER_DEF__SHORT(_TypeName,_Field,_Len,_Default) CSerializationType<_SerObjType,int,int,int> _Field; 
#define VAR_SER_DEF_CHAR(_TypeName,_Field,_Len,_Default) CSerializationType<_SerObjType,char*,char*,char*> _Field; 
#define _VAR_SER_DEF(_TypeName,_Field,_Len,_Default) VAR_SER_DEF##_TypeName(_TypeName,_Field,_Len,_Default)
#define VarSerBase(_Field) _VAR_SER_DEF##_Field

/*
CSerializationType<_SerObjType,test3Serialization<CSerializationIniObject,_FileNameType > ,StructureSerializationFunctiomClass(test3,_FileNameType,MyObjectName(data) ),test3> data;

*/
#define DefineStructure(_BaseStructureType,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) struct _BaseStructureType \
{\
    Code(VarBase,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20)\
}; \
	template<typename _SerObjType,typename _FileNameType> \
	struct _BaseStructureType##Serialization \
{\
	Code(VarSerBase,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20)\
};\

#define DefineStructureNoBase(_BaseStructureType,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
template<typename _SerObjType,typename _FileNameType> \
struct _BaseStructureType##Serialization \
{\
	Code(VarSerBase,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20)\
};\

#define MakeSerializationStructure(_BaseStructureType,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
DefineStructure(_BaseStructureType,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
MakeStructureSerializationFunctiomClass(\
Code(COPYCODEBase,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20),\
Code(COPYCODE1Base,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20),\
Code(CONSTRUCTBase,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20),\
_BaseStructureType,(_BaseStructureType##Serialization<CSerializationIniObject##,##_FileName >) ) \

#define MakeSerializationStructureNoBase(_BaseStructureType,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	DefineStructureNoBase(_BaseStructureType,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	MakeStructureSerializationFunctiomClass(\
	Code(COPYCODEBase,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20),\
	Code(COPYCODE1Base,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20),\
	Code(CONSTRUCTBase,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20),\
	_BaseStructureType,(_BaseStructureType##Serialization<CSerializationIniObject##,##_FileName >) ) \



//编译时定义
#define DEFINISERCLASS(_BaseType,_FileName,_FieldName) ToStringObject(_BaseType##_##_FieldName) CSerializationType<CSerializationIniObject,_BaseType##Serialization<CSerializationIniObject,_FileName >,StructureSerializationFunctiomClass(_BaseType,_FileName,MyObjectName(_BaseType##_##_FieldName)),_BaseType> _FieldName;
#define DEFINISERCLASSFUC(_BaseType,_FileName,_FieldName) CSerializationType<CSerializationIniObject,_BaseType##Serialization<CSerializationIniObject,_FileName >,StructureSerializationFunctiomClass(_BaseType,_FileName,MyObjectName(_FieldName)),_BaseType> _FieldName;

//运行时定义
#define DEFINISERCLASSRUNING(_BaseType,_FileName,_FieldName) CSerializationType<CSerializationIniObject,_BaseType##Serialization<CSerializationIniObject,_FileName >,StructureSerializationFunctiomClass(_BaseType,_FileName,_FieldName),_BaseType>
//#define DEFINISERCLASSFUCRUNING(_BaseType,_FileName,_FieldName) CSerializationType<CSerializationIniObject,_BaseType##Serialization<CSerializationIniObject,_FileName >,StructureSerializationFunctiomClass(_BaseType,_FileName,_FieldName),_BaseType>;

	//sc.m_ValueInfo.m_ValName=#_FieldName;
//sc.m_pszFile=FileName().m_Data; \
//		sc.m_ValName=FieldName().m_Data; 		_ConstructCode



#define MakeStructureSerializationFunctiomClass(_CopyCode,_CopyCode1,_ConstructCode,_BaseStructureType,_SerializationStructureType) \
template<typename BaseStructureType,typename SerializationStructureType,typename FileName,typename FieldName> \
class StructureSerializationFunctiomClassName(_BaseStructureType) \
{\
public:\
	bool copy(SerializationStructureType & Dst,BaseStructureType & Org)\
	{\
	printf("copy1(SerializationStructureType & Dst,_BaseStructureType & Org)\n");\
	_CopyCode\
	return true;\
	};\
	bool copy(BaseStructureType & Dst,SerializationStructureType & Org)\
	{\
	printf("copy2(_BaseStructureType & Dst,SerializationStructureType & Org)\n" );\
	_CopyCode1\
	return true;\
	};\
	template<typename _SerializationType> \
	bool StructureConstructInit(_SerializationType & sc) \
	{ \
		sc.m_pszFile=FileName().m_Data; \
		sc.m_ValName=FieldName().m_Data; \
		_ConstructCode \
		return true;\
	}\
	template<typename _SerializationType> \
	bool Reset(_SerializationType & sc)\
	{\
		return true;\
	}\
	StructureSerializationFunctiomClassName(_BaseStructureType)(){};\
	~StructureSerializationFunctiomClassName(_BaseStructureType)(){};\
protected:\
	\
private:\
};\



class CSerializationTypeBase
{
public:
	//CSerializationTypeBase * m_pParent;
	ValueDescBase * m_pValueInfo;
	int m_nParentPos;
	bool GetParentList()
	{
		CSerializationTypeBase * p=Parent(); 
		m_pValueInfo->m_pParentNameList.clear();
		//ValueAddressBase addrbase;
		
		//
		for(;p!=NULL;p=p->Parent())
		{
			//char * pN
			//addrbase=(ValueAddressBase)p->m_pValueInfo;
			m_pValueInfo->m_pParentNameList.push_front(*((ValueAddressBase*)p->m_pValueInfo));
		}
		//加入根节点
		/*
		if((p!=this)&&(p->m_nParentPos==0))
				{
					m_pValueInfo->m_pParentNameList.push_front(*((ValueAddressBase*)p->m_pValueInfo));
				}*/
		
		return true;
	}
	CSerializationTypeBase * Parent()
	{
		if(m_nParentPos==0)
		{
			return NULL;
		}
		return (CSerializationTypeBase * )((unsigned int)this-m_nParentPos);
	}

	
	/*
	bool SetParent(CSerializationTypeBase * pParent)
		{
			m_pParent=pParent;
		}*/
	
	
	CSerializationTypeBase(){};
	~CSerializationTypeBase(){};
protected:
	
private:
};

#define PVal(_p)			((_MySecondType*)(_p))		
#define PValInfo(_p)		((ValueDesc<_MySecondType>*)(_p))
#define Val(_p)				(*((_MySecondType*)(_p)))		
#define ValInfo(_p)			(*((ValueDesc<_MySecondType>*)(_p)))

#define PVal1(_p)				((_MySecondType*)(_p))		
#define PValInfo1(_p)			((ValueDesc1<_MySecondType>*)(_p))
#define Val1(_p)				(*((_MySecondType*)(_p)))		
#define ValInfo1(_p)			(*((ValueDesc1<_MySecondType>*)(_p)))

#define PVal1_t(_t,_p)				((_t*)(_p))		
#define PValInfo1_t(_t,_p)			((ValueDesc1<_t>*)(_p))
#define Val1_t(_t,_p)				(*((_t*)(_p)))		
#define ValInfo1_t(_t,_p)			(*((ValueDesc1<_t>*)(_p)))



template<typename _SerializationObject,typename _SerializationType,typename _StructureSerializationFunctiom,typename _BaseType>
class CSerializationType :public CSerializationTypeBase,public ValueDesc<_SerializationType>,public _SerializationType
{
public:
	typedef _SerializationObject _MyFirstType;
	typedef _SerializationType _MySecondType;
	typedef _StructureSerializationFunctiom _MyThirdType;
	typedef _BaseType _MyFourthType;
	
	typedef CSerializationType<_MyFirstType,_MySecondType,_MyThirdType,_MyFourthType> _Myt;

	
	bool Reset()
	{
		_MyThirdType().Reset(*this);
		return true;
	}
	

	CSerializationType()
	{
		//初始化时序列化
		//m_Data=(_MySecondType)*this;
		m_nParentPos=0;
		//m_Data.m_pParent=this;
		m_pValueInfo=((ValueDesc<_MySecondType> *)this);
		m_pValueInfo->m_index=1;
		m_bIsAlreadyRead=false;
		m_ValName="ROOT";
		_MyThirdType().StructureConstructInit(*this);

		m_count.m_nParentPos=(unsigned int)&m_count-(unsigned int )this;
		*((ValueAddress*)PValInfo1_t(int,&m_count))=(ValueAddress)ValInfo(this);
		PValInfo1_t(int,&m_count)->m_ValName="@number";
		PValInfo1_t(int,&m_count)->m_DefaultVal=0;

		m_bArray=true;
		//构造自己
		//StructureConstructInit(this);
	};
	CSerializationType(_Myt const & obj)
	{
		//初始化时序列化
		//m_Data=(_MySecondType)*this;
		//m_Data=obj.m_Data;
		
		//重新构造父
		if(((CSerializationTypeBase *)&obj)->Parent())
		{
			m_nParentPos=(unsigned int)this-(unsigned int)(((CSerializationTypeBase *)&obj)->Parent());
		}
		else
		{
			m_nParentPos=0;
		}
		_MyThirdType().StructureConstructInit(*this);

		
		m_pValueInfo=((ValueDesc<_MySecondType> *)this);
		m_bIsAlreadyRead=false;
		m_index=((ValueDesc<_MySecondType> *)&obj)->m_index;
		

		m_count.m_nParentPos=(unsigned int)&m_count-(unsigned int )this;
		*((ValueAddress*)PValInfo1_t(int,&m_count))=(ValueAddress)ValInfo(this);
		PValInfo1_t(int,&m_count)->m_ValName="@number";
		PValInfo1_t(int,&m_count)->m_DefaultVal=0;

		m_bArray=obj.m_bArray;

		//m_ValueInfo=obj.m_ValueInfo;
		((ValueDesc<_MySecondType> *)this)->m_ValName=((ValueDesc<_MySecondType> *)&obj)->m_ValName;
		//m_MytData=obj.m_MytData;
	};
	bool ConstructNoCopy(_Myt const & obj)
	{
		//重新构造父
		if(((CSerializationTypeBase *)&obj)->Parent())
		{
			m_nParentPos=(unsigned int)this-(unsigned int)(((CSerializationTypeBase *)&obj)->Parent());
		}
		else
		{
			m_nParentPos=0;
		}
		_MyThirdType().StructureConstructInit(*this);
		
		
		m_pValueInfo=((ValueDesc<_MySecondType> *)this);
		m_bIsAlreadyRead=false;
		
		
		m_count.m_nParentPos=(unsigned int)&m_count-(unsigned int )this;
		*((ValueAddress*)PValInfo1_t(int,&m_count))=(ValueAddress)ValInfo(this);
		PValInfo1_t(int,&m_count)->m_ValName="@number";
		PValInfo1_t(int,&m_count)->m_DefaultVal=0;
		
		//m_bArray=obj.m_bArray;
		return true;
	}
	~CSerializationType(){};
private:
	//反序列化结构体数组
	bool init()
	{
		if(m_bIsAlreadyRead)
		{
			return true; 
		}
		if(m_bArray==true)
		{
			//反序列化结构体数组
			_Myt tmp;
			_MyFourthType tmp1;
			tmp.ConstructNoCopy(*this);
			tmp.m_bArray=false;
			//tmp.m_ValueInfo.m_addr.m_pParentNameList.push_back(m_ValueInfo.m_ValName);

			unsigned int Num=Count();
			if(Num==0)
			{
				PValInfo(&tmp)->m_index=1;
				//tmp.m_ValueInfo.m_index=1;
				tmp.Reset();
				tmp1=(_MyFourthType)tmp;
				
				m_MytData.push_back(tmp);
			}
			for(int i=1;i<=Num;i++)
			{
				PValInfo(&tmp)->m_index=i;
				tmp.Reset();
				tmp1=(_MyFourthType)tmp;
				
				m_MytData.push_back(tmp);
			}
		}
		
		m_bIsAlreadyRead=true;
		return true;
	}
public:


	
	bool m_bIsAlreadyRead;
	bool m_bArray;

	_MyFourthType m_Data;
	//结构构造实现，用于初始化结构关系图，以及初始化结构信息数据
	/*
	bool StructureConstructInit(_StructureConstructType & sc)
		{
			sc.init(this);
		}*/
	
	vector<_Myt> m_MytData;
	
	CSerializationType<_MyFirstType,int,int,int> m_count;

	//ValueDesc<_MySecondType> m_ValueInfo;
	//结构体型别反序列化
	_Myt & operator[](unsigned int _pos)
	{
		if(m_bArray)
		{
			init();
			if(Count()<=_pos)
			{
				return *this;
			}
			return m_MytData[_pos]; 
		}
		return *this;
		//sprintf("%s_%d",m_ValueInfo.m_ValName,m_ValueInfo.m_addr.m_index);
		
	}
	

	//反序列化
	operator _MySecondType()
	{
		init();
		if(m_bArray)
		{
			return (_MySecondType)m_MytData[0]; 
		}
		return *((_MySecondType*)this); 
	}

	operator _MyFourthType()
	{
		init();
		if(m_bArray)
		{
			_MyThirdType().copy(m_MytData[0].m_Data,*((_MySecondType*)&m_MytData[0]) );
			return m_MytData[0].m_Data; 
		}
		_MyThirdType().copy(m_Data,*((_MySecondType*)this));
		return m_Data; 
	}

	/*
	unsigned int MytDataCount()
		{
			if(m_bIsAlreadyRead)
			{
				return m_MytData.size();
			}
			return m_count;
		}*/
	

	unsigned int Count()
	{
		/*
		if(m_bIsAlreadyRead)
				{
					return m_MytData.size();
				}*/
		
		return m_count;
	}
	/*
	_Myt& operator=(_MySecondType _X) 
		{
			printf("CSerializationType =(_BaseType _X) 无特例化\r\n");
			m_Data=_X;
			//序列化
			return *this;
		}*/
	

	//基本结构体型别序列化
	_Myt& operator=(_MyFourthType & _X) 
	{
		init();
		if(Count()==0)
		{
			clear();
		}
		if(m_bArray)
		{
			_MyThirdType().copy(*((_MySecondType*)&m_MytData[0]),_X);
		}
		else
		{
			_MyThirdType().copy(*((_MySecondType*)this),_X);
		}
		m_count=1;
		return *this;
	}

	
	
	_Myt& operator=(_Myt const & _X) 
	{
		if(Count()==0)
		{
			clear();
		}
		if (m_bArray)
		{
			*((ValueDesc<_MySecondType> *)&m_MytData[0])=*((ValueDesc<_MySecondType> *)&_X);
			//m_MytData[0].m_ValueInfo=_X.m_ValueInfo;
		}
		else
		{
			*((ValueDesc<_MySecondType> *)&m_MytData[0])=(ValueDesc<_MySecondType>)_X;
		}
		m_count=1;
		return *this;
	}
	
	
	
	_Myt& operator+=(_MyFourthType & _X)
	{
		if(m_bArray)
		{
			_Myt tmp;
			
			tmp.m_bArray=false;
			
			((ValueDesc<_MySecondType> *)&tmp)->m_index=Count()+1;
			tmp.ConstructNoCopy(*this);

			_MyThirdType().copy(Val(&tmp),_X);
			m_count=Count()+1;
			if(m_count==1)
			{
				m_MytData.clear();
			}
			m_MytData.push_back(tmp);
			
		}
		return *this;
	}


	
	//数组型别归零
	BOOL clear()
	{
		if((m_nParentPos==0)&&(m_bArray==true))
		{
			m_count.m_bIsAlreadyRead=false;
			GetParentList();
			_MyFirstType().clear(*((ValueDesc<_MySecondType> *)this));
			m_MytData.clear();
			m_bIsAlreadyRead=false;
			
		}
		init();
		return TRUE;
	}
	

	
protected:
	

};

//== int型序列化

template<>
class CSerializationType<CSerializationIniObject,int,int,int> :public CSerializationTypeBase,public ValueDesc1<int>
{
public:
	typedef CSerializationType<CSerializationIniObject,int,int,int> _Myt;
	typedef CSerializationIniObject _MyFirstType;
	typedef int _MySecondType;
	bool m_bIsAlreadyRead;
	

	bool Reset()
	{
		m_pParentNameList.clear();
		m_bIsAlreadyRead=false;
		return true;
	}

	//_MySecondType m_Data;
	

	//ValueDesc1<_MySecondType> m_ValueInfo;
	
	
	bool init()
	{
		if(m_bIsAlreadyRead==true)
		{
			return true; 
		}
		m_bIsAlreadyRead=true;
		GetParentList();
		_MyFirstType().GetData(ValInfo1(this));
		//m_Data=m_Val;
		return true;
	}

	//反序列化
	operator _MySecondType()
	{
		init();
		return m_Val; 
		
	}

	
	
	_Myt& operator=(_MySecondType _X) 
	{
		init();
		m_Val=_X;
		//序列化
		_MyFirstType().Serialization(ValInfo1(this));
		return *this;
	}
	
	/*
	_Myt& operator=(_Myt const & _X) 
		{
			*this=Val1(&_X);
			return *this;
		}*/
	

	CSerializationType()
	{
		//初始化时序列化
		//m_Data=(_MySecondType)*this;
		m_pValueInfo=PValInfo1(this);
		m_bIsAlreadyRead=false;
		m_nParentPos=NULL;
	};
	//拷贝构造
	/*
	CSerializationType(_Myt & obj)
		{
			//初始化时序列化
			//m_Data=(_MySecondType)*this;
			m_Data=obj.m_Data;
			//m_MytData=obj.m_MytData;
			m_nParentPos=obj.m_nParentPos;
			m_pValueInfo=obj.m_pValueInfo;
			m_bIsAlreadyRead=obj.m_bIsAlreadyRead;
		};*/
	

	~CSerializationType(){};
protected:
	
private:
};


template<>
class CSerializationType<CSerializationIniObject,char *,char *,char *> :public CSerializationTypeBase,public ValueDesc1<char *>
{
public:
	typedef CSerializationType<CSerializationIniObject,char *,char *,char *> _Myt;
	typedef CSerializationIniObject _MyFirstType;
	typedef char * _MySecondType;
	bool m_bIsAlreadyRead;
	
	
	bool Reset()
	{
		m_pParentNameList.clear();
		m_bIsAlreadyRead=false;
		return true;
	}
	
	//string m_Data;
	
	
	//ValueDesc1<_MySecondType> m_ValueInfo;
	
	
	bool init()
	{
		if(m_bIsAlreadyRead==true)
		{
			return true; 
		}
		m_bIsAlreadyRead=true;
		GetParentList();
		if(m_Val==NULL)
		{
			m_Val=new char[m_nValSize];
		}
		_MyFirstType().GetData(ValInfo1(this));
		//m_Data=m_ValueInfo.m_Val;
		return true;
	}
	
	//反序列化
	operator _MySecondType()
	{
		init();
		return (_MySecondType)m_Val; 
		
	}
	
	
	
	_Myt& operator=(_MySecondType _X) 
	{
		init();
		//m_Data=_X;
		strcpy(m_Val,_X);
		//序列化
		_MyFirstType().Serialization(ValInfo1(this));
		return *this;
	}
	

	
	
	CSerializationType()
	{
		//初始化时序列化
		//m_Data=(_MySecondType)*this;
		
		m_pValueInfo=PValInfo1(this);
		m_Val=NULL;
		m_bIsAlreadyRead=false;
		m_nParentPos=NULL;
	};
	//拷贝构造
	/*
	CSerializationType(_Myt & obj)
		{
			//初始化时序列化
			//m_Data=(_MySecondType)*this;
			m_Data=obj.m_Data;
			//m_MytData=obj.m_MytData;
			m_nParentPos=obj.m_nParentPos;
			m_pValueInfo=obj.m_pValueInfo;
			m_bIsAlreadyRead=obj.m_bIsAlreadyRead;
		};*/
	
	
	~CSerializationType()
	{
		if(m_Val)
		{
			delete m_Val;
		}
	};
protected:
	
private:
};

#endif