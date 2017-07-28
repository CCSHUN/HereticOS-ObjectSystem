#pragma once
#pragma warning(disable:4996)

#include <map>
#include <string>
#include <vector>
#include <list>
using namespace std;

#ifdef _UNICODE
typedef wstring tstring;
#define sprintf_s_t swprintf_s
#define strcpy_t wcscpy
#define strcat_t wcscat
#define strlen_t wcslen 
#define atoi_t	_wtoi
#define atoi64_t	_wtoi64
#define itoa_t		_itow
#define i64toa_t		_i64tow
#define ui64toa_t		_ui64tow
#define sscanf_t		
#define strstr_t			wcsstr
#define strrchr_t			wcsrchr
#define stricmp_t		wcsicmp
#define atol_t			_wtol
#define strcmp_t	wcscmp
#else
typedef string tstring;
#define sprintf_s_t sprintf_s
#define strcpy_t strcpy
#define strcat_t strcat
#define strlen_t strlen
#define atoi_t	atoi
#define atoi64_t	_atoi64
#define itoa_t		_itoa
#define i64toa_t		_i64toa
#define ui64toa_t		_ui64toa
#define strstr_t		strstr
#define strrchr_t			strrchr
#define stricmp_t	stricmp
#define atol_t			atol
#define strcmp_t	strcmp
#endif





class CMyString
{
public:
	typedef enum
	{
		Ansi,
		Unicode,
	}StringType;

	StringType m_type;
	void * m_pStr;

	StringType m_reftype;
	void * m_refStr;
	int m_nRefBufLen;

	CMyString()
	{
		m_pStr=NULL;
		
	};
	~CMyString()
	{
		if(m_pStr)
		{
			delete m_pStr;
		}
	}
	CMyString(char * pStr,int nRefBufLen)
	{
		m_refStr=pStr;
		m_reftype=Ansi;
		m_nRefBufLen=nRefBufLen;
		m_pStr=NULL;
	}
	CMyString(WCHAR * pStr,int nRefBufLen)
	{
		m_refStr=pStr;
		m_reftype=Unicode;
		m_nRefBufLen=nRefBufLen;
		m_pStr=NULL;
	}

	CMyString(CMyString & pStr)
	{
		m_refStr=pStr.m_refStr;
		m_reftype=pStr.m_reftype;
		m_nRefBufLen=pStr.m_nRefBufLen;
		m_pStr=NULL;
	}

	CMyString & freeme()
	{
		if(m_pStr)
		{
			delete m_pStr;
			m_pStr=NULL;
		}
		return *this;
	}
	operator char *()
	{
		if(m_reftype==Ansi)
		{
			return (char *)m_refStr;
		}
		else
		{
			if(m_pStr)
			{
				return (char *) m_pStr;
			}
			else
			{
				m_pStr=new BYTE[m_nRefBufLen+2];
				memset(m_pStr,0,m_nRefBufLen+2);
				m_type=Ansi;
				setlocale(LC_CTYPE,"");
				m_nRefBufLen=wcstombs((char *)m_pStr,(wchar_t *)m_refStr,m_nRefBufLen);

				return (char *) m_pStr;
			}
		}
	}
	operator wchar_t *()
	{
		if(m_reftype==Unicode)
		{
			return (wchar_t *)m_refStr;
		}
		else
		{
			if(m_pStr)
			{
				return (wchar_t *) m_pStr;
			}
			else
			{
				m_pStr=new BYTE[m_nRefBufLen*2+2];
				memset(m_pStr,0,m_nRefBufLen*2+2);
				m_type=Unicode;
				setlocale(LC_CTYPE,"");
				m_nRefBufLen=mbstowcs((wchar_t *)m_pStr,(char *)m_refStr,m_nRefBufLen)*sizeof(wchar_t);
				return (wchar_t *) m_pStr;
			}
		}
	}
protected:

private:
};


template<typename ValType>
ValType AtoVal(TCHAR * pszVal,unsigned int nBit,ValType)
{
	ValType RstVal=0;
	ValType CurVal=0;
	for(int pos=0;pszVal[pos];pos++)
	{
		if(pszVal[pos]>='0'&&pszVal[pos]<='9')
		{
			CurVal=pszVal[pos]-'0';
		}else if((pszVal[pos]|0x20)>='a'&&(pszVal[pos]|0x20)<='z')
		{
			CurVal=(pszVal[pos]|0x20)-'a'+10;
		}

		RstVal=RstVal*nBit+CurVal;
	}
	return RstVal;
}

static void EncodeHex(BYTE * pData,unsigned int nLen,tstring & szOut)
{
	TCHAR *pHexTab=_T("0123456789ABCDEF");
	TCHAR * pOut=new TCHAR[nLen*2+1];
	for(unsigned int i=0;i<nLen;i++)
	{
		pOut[2*i]=pHexTab[((pData[i]&0xf0)>>4)];
		pOut[2*i+1]=pHexTab[pData[i]&0xf];
		pOut[2*i+2]=0;
	}
	szOut=pOut;
	delete pOut;
}

static BOOL DecodeHex(TCHAR * pData,BYTE * pOutData,IN unsigned int  nOutDataLen)
{
	BYTE nLow,nHigh;
	unsigned int nCount=nOutDataLen/sizeof(TCHAR);
	for(unsigned int i=0;pData[i]!=0;i+=2)
	{
		if((pData[i]>='0')&&(pData[i]<='9'))
		{
			nHigh=pData[i]-'0';
		}else if(((pData[i]|0x20)>='a')&&((pData[i]|0x20)<='z'))
		{
			nHigh=(pData[i]|0x20)-'a'+10;
		}else
		{
			return FALSE;
		}

		if((pData[i+1]>='0')&&(pData[i+1]<='9'))
		{
			nLow=pData[i+1]-'0';
		}else if(((pData[i+1]|0x20)>='a')&&((pData[i+1]|0x20)<='z'))
		{
			nLow=(pData[i+1]|0x20)-'a'+10;
		}else
		{
			return FALSE;
		}

		pOutData[i/2]=nLow|((nHigh&0xf)<<4);
		if(2*nCount<i)
		{
			return FALSE;
		}
	}
	return TRUE;
}

class CBase64Zip
{
private:
	CBase64Zip(){};
	~CBase64Zip(){};

public:
	static BOOL Base64ZipCompress(IN unsigned char * pBuf,IN unsigned long nLen,OUT string & szOutData);
	static BOOL Base64ZipCompress(IN unsigned char * pBuf,IN unsigned long nLen,OUT wstring & szOutData);

	static BOOL Base64ZipUnCompress(IN string & inBuf,OUT vector<unsigned char> & OutBuf);
	static BOOL Base64ZipUnCompress(IN wstring & inBuf,OUT vector<unsigned char> & OutBuf);
	
private:
};

#define TimeUsedBegin(TimeName) DWORD TimeName=GetTickCount();
#define TimeUsedEnd(TimeName) TimeName=GetTickCount()-TimeName;


class CXmlString
{
public:
	CXmlString(){};
	static BOOL GetXMLStringFromtstring(OUT tstring & XmlString,IN tstring &SrcString );
	static BOOL GetStringFromXMLString(OUT tstring & String,IN tstring &XMLString );

	~CXmlString(){};
protected:
	
private:
};