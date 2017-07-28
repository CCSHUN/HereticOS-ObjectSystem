#pragma once
#include "BaseFunctionTool.h"
#include "SerIni.h"


//#define AutoValParameter(par) CAutoVal(par)
//#define AutoValParameter(par,par1) AutoValParameter(par),AutoValParameter(par1)



//自动变量


enum ValType
{
	typeError=0,
	typeANSIString,
	typeUnicodeString,
	typeInt,
	typeUint,
	typeLong,
	typeUlong,

	typeLL,
	typeInt64,
	typeChar,
	typeUchar,
	typeFloat,
	typeDouble,
	typeShort,
	typeUshort,
	typeBOOL,
	typeboolen,
	typeDWORD,
};
//CMyString;
//VARTYPE
//类型转换向量表
typedef struct _tagTypeTransform
{
	ValType SrcValueType;

}TypeTransform;

class CAutoVal
{
public:
	ValType m_ValType;
	union UnioVal
	{
		int iVal;
		unsigned int uiVal;
		long lVal;
		unsigned long ulVal;
		__int64 i64Val;
		float fVal;
		double lfVal;
		char cVal;
		unsigned char ucVal;
		short sVal;
		unsigned short usVal;
		bool bVal;
#ifdef WIN32
		LONGLONG llVal;
		BOOL BVal;
		DWORD dwVal;
#endif
	}m_Val;
	//UnioVal m_Val;

	wstring m_UnicodeString;
	string m_ANSIString;

	CAutoVal(){m_ValType=typeError;};

	~CAutoVal(){};
	//拷贝构造
	CAutoVal(wstring & Val)
	{
		m_UnicodeString=Val;
		m_ValType=typeUnicodeString;
	}
	CAutoVal(string & Val)
	{
		m_ANSIString=Val;
		m_ValType=typeANSIString;
	}

	CAutoVal(const WCHAR * Val)
	{
		m_UnicodeString=Val;
		m_ValType=typeUnicodeString;
	}
	CAutoVal(const char * Val)
	{
		m_ANSIString=Val;
		m_ValType=typeANSIString;
	}
	
	
	CAutoVal(const unsigned int & Val)
	{
		m_Val.uiVal=Val;
		m_ValType=typeUint;
	}

	CAutoVal(const long & Val)
	{
		m_Val.lVal=Val;
		m_ValType=typeLong;
	}

	
	CAutoVal(const float & Val)
	{
		m_Val.fVal=Val;
		m_ValType=typeFloat;
	}
	CAutoVal(const double & Val)
	{
		m_Val.lfVal=Val;
		m_ValType=typeDouble;
	}
	CAutoVal(const bool & Val)
	{
		m_Val.bVal=Val;
		m_ValType=typeboolen;
	}

	CAutoVal(const unsigned long & Val)
	{
		m_Val.ulVal=Val;
		m_ValType=typeUlong;
	}
	CAutoVal(const int & Val)
	{
		m_Val.iVal=Val;
		m_ValType=typeInt;
	}


#ifdef WIN32
	/*CAutoVal(BOOL * Val)
	{
		m_Val.BVal=*Val;
		m_ValType=typeBOOL;
	}
	CAutoVal(DWORD * Val)
	{
		m_Val.dwVal=*Val;
		m_ValType=typeDWORD;
	}*/
	CAutoVal(const LONGLONG & Val)
	{
		m_Val.llVal=Val;
		m_ValType=typeLL;
	}

	CAutoVal(LPSTR Val)
	{
		m_ANSIString=Val;
		m_ValType=typeANSIString;
	}
	CAutoVal(LPWSTR Val)
	{
		m_UnicodeString=Val;
		m_ValType=typeUnicodeString;
	}
#else


#endif
	//类型转换
	operator string &()
	{
		
#define CASE_VAL(AutoType,Val,fmt) case AutoType: \
	sprintf_s(szVal,63,fmt,m_Val.Val);\
	m_ANSIString=szVal;\
		return m_ANSIString;\
		break;\


		char szVal[64]={0};

		switch (m_ValType)
		{
		case typeUnicodeString:
			return m_ANSIString;
			break;
		case typeANSIString:
			m_ANSIString=(char *)CMyString((WCHAR *)m_UnicodeString.c_str(),m_UnicodeString.length()*sizeof(WCHAR));
			return m_ANSIString;
		CASE_VAL(typeInt,iVal,"%d");
		CASE_VAL(typeUint,uiVal,"%u");
		CASE_VAL(typeLong,lVal,"%ld");
		CASE_VAL(typeUlong,ulVal,"%lu");


		CASE_VAL(typeInt64,i64Val,"%I64d");
		CASE_VAL(typeFloat,fVal,"%f");
		CASE_VAL(typeDouble,lfVal,"%lf");
		CASE_VAL(typeChar,cVal,"%c");
		CASE_VAL(typeUchar,ucVal,"%c");

		CASE_VAL(typeShort,sVal,"%hd");
		CASE_VAL(typeUshort,usVal,"%hu");
		CASE_VAL(typeLL,llVal,"%lld");
		//COMMON_TRANS(BOOL,typeBOOL,ucVal,"%c");
		CASE_VAL(typeDWORD,ucVal,"%lu");
		case typeboolen:
			{
				sprintf_s(szVal,63,"%s",m_Val.bVal==false?"false":"true");
			}
			break;
		case typeBOOL:
			{
				sprintf_s(szVal,63,"%s",m_Val.BVal==FALSE?"FALSE":"TRUE");
			}
			break;
		default:
			break;
		}
		m_ANSIString=szVal;
		return m_ANSIString;
	}

	operator wstring & ()
	{
#define WCASE_VAL(AutoType,Val,fmt) case AutoType: \
	swprintf_s(szVal,63,L##fmt,m_Val.Val);\
	m_UnicodeString=szVal; \
	return m_UnicodeString;\
	break;\


		WCHAR szVal[64]={0};

		switch (m_ValType)
		{
		case typeUnicodeString:
			return m_UnicodeString;
			break;
		case typeANSIString:
			m_UnicodeString=(WCHAR *)CMyString((char *)m_ANSIString.c_str(),m_ANSIString.length());
			return m_UnicodeString;
			break;
			WCASE_VAL(typeInt,iVal,"%d");
			WCASE_VAL(typeUint,uiVal,"%u");
			WCASE_VAL(typeLong,lVal,"%ld");
			WCASE_VAL(typeUlong,ulVal,"%lu");


			WCASE_VAL(typeInt64,i64Val,"%I64d");
			WCASE_VAL(typeFloat,fVal,"%f");
			WCASE_VAL(typeDouble,lfVal,"%lf");
			WCASE_VAL(typeChar,cVal,"%c");
			WCASE_VAL(typeUchar,ucVal,"%c");

			WCASE_VAL(typeShort,sVal,"%hd");
			WCASE_VAL(typeUshort,usVal,"%hu");
			WCASE_VAL(typeLL,llVal,"%lld");
			//COMMON_TRANS(BOOL,typeBOOL,ucVal,"%c");
			WCASE_VAL(typeDWORD,ucVal,"%lu");
		case typeboolen:
			{
				swprintf_s(szVal,63,L"%s",m_Val.bVal==false?L"false":L"true");
			}
			break;
		case typeBOOL:
			{
				swprintf_s(szVal,63,L"%s",m_Val.BVal==FALSE?L"FALSE":L"TRUE");
			}
			break;
		default:
			break;
		}
		m_UnicodeString=szVal;
		return m_UnicodeString;
	}

#define COMMON_TRANS(DstType,AutoType,Val,szFmt) \
	operator DstType () \
	{\
		if (m_ValType==AutoType)\
		{\
			return m_Val.Val;\
		}else if (m_ValType==typeANSIString)\
		{\
			sscanf_s(m_ANSIString.c_str(),szFmt,&m_Val.Val);\
		}else if (m_ValType==typeUnicodeString)\
		{\
			swscanf_s(m_UnicodeString.c_str(),L##szFmt,&m_Val.Val);\
		}else\
		{\
			CAutoVal tmp=(tstring)*this;\
			*this=tmp;\
			return (DstType)*this;\
		}\
		return m_Val.Val;\
	};\

	/*
	int iVal;
	unsigned int uiVal;
	long lVal;
	unsigned long ulVal;
	__int64 i64Val;
	float fVal;
	double eVal;
	char cVal;
	unsigned char ucVal;

	short sVal;
	unsigned short usVal;
	bool bVal;
	#ifdef WIN32
	LONGLONG llVal;
	BOOL BVal;
	DWORD dwVal;
	*/
	COMMON_TRANS(int,typeInt,iVal,"%d");
	COMMON_TRANS(unsigned int,typeUint,uiVal,"%u");
	COMMON_TRANS(long,typeLong,lVal,"%ld");
	COMMON_TRANS(unsigned long,typeUlong,ulVal,"%lu");


	COMMON_TRANS(__int64,typeInt64,i64Val,"%I64d");

	COMMON_TRANS(float,typeFloat,fVal,"%f");
	COMMON_TRANS(double,typeDouble,lfVal,"%lf");
	COMMON_TRANS(char,typeChar,cVal,"%c");
	COMMON_TRANS(unsigned char,typeUchar,ucVal,"%c");

	COMMON_TRANS(short,typeShort,sVal,"%hd");
	COMMON_TRANS(unsigned short,typeUshort,usVal,"%hu");
	//COMMON_TRANS(bool,typeDouble,"%lf");
	operator bool () 
	{
		if (m_ValType==typeboolen)
		{
			return m_Val.bVal;
		}else if (m_ValType==typeUnicodeString)
		{
			//sscanf(m_ANSIString,szFmt,&m_Val.Val);
			if(wstring(L"false")==m_UnicodeString)
			{
				return false;
			}else if(wstring(L"true")==m_UnicodeString)
			{
				return true;
			}
		}else if (m_ValType==typeANSIString)
		{
			if(string("false")==m_ANSIString)
			{
				return false;
			}else if(string("true")==m_ANSIString)
			{
				return true;
			}
		}
		*(unsigned int *)0=0;
		
		return false;
	};

	

#ifdef WIN32
	//COMMON_TRANS(LONGLONG,typeLL,llVal,"%ll");
	//COMMON_TRANS(BOOL,typeBOOL,ucVal,"%c");
	//COMMON_TRANS(DWORD,typeDWORD,dwVal,"%lu");

	/*operator BOOL () 
	{
		if (m_ValType==typeboolen)
		{
			return m_Val.bVal;
		}else if (m_ValType==typeUnicodeString)
		{
			//sscanf(m_ANSIString,szFmt,&m_Val.Val);
			if(wstring(L"FALSE")==m_UnicodeString)
			{
				return FALSE;
			}else if(wstring(L"TRUE")==m_UnicodeString)
			{
				return TRUE;
			}
		}else if (m_ValType==typeANSIString)
		{
			if(string("FALSE")==m_ANSIString)
			{
				return FALSE;
			}else if(string("TRUE")==m_ANSIString)
			{
				return TRUE;
			}
		}
		*(unsigned int *)0=0;

		return FALSE;
	};*/

#endif


protected:

	
private:
};



//自动参数列表



#define TemplateParameterBase(_t) typename _t
#define FunctionParameterBase(_t) _t _t##par
#define CodeParameterRender(_t)	par.push_back(_t##par);
#define DefineTemplateParameter(_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20)\
	template<AddCodeN(TemplateParameterBase,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20)>\
	vector<CAutoVal> operator()(\
	AddCodeN(FunctionParameterBase,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20))\
	{\
		vector<CAutoVal>   par;\
		par.clear();\
		Code(CodeParameterRender,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
		return par;\
	};\

#define AutoParameter(...) CAutoParameter()(__VA_ARGS__)
#define DefParameter(Name,...) CAutoParameter Name(__VA_ARGS__);

class CAutoParameter
{
public:
	CAutoParameter(){};
	~CAutoParameter(){};
	/*
	template<AddCodeN(TemplateParameterBase,16,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20)>
	void AutoValParameter(list<CAutoVal>  & par,
		AddCodeN(FunctionParameterBase,16,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20))
	{
		par.clear();
		Code(CodeParameterRender,16,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20)
	}
	*/
	//DefineTemplateParameter(1,T1);
	DefineTemplateParameter(1,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(2,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(3,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(4,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(5,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);

	DefineTemplateParameter(6,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(7,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(8,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(9,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(10,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);


	DefineTemplateParameter(11,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(12,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(13,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(14,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(15,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);


	DefineTemplateParameter(16,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(17,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(18,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(19,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(20,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);

/*
	template<typename T1,typename T2>
	list<CAutoVal> operator()(T1 t1,T2 t2)
	{
		list<CAutoVal>   par;
		par.push_back(t1);
		par.push_back(t2);
		return par;
	}
	*/
protected:

private:
};
