// Base64.h: interface for the Base64 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE64_H__21BC1BF0_E577_11D1_868E_0060083663C0__INCLUDED_)
#define AFX_BASE64_H__21BC1BF0_E577_11D1_868E_0060083663C0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

template<typename CharT>
class Base64  
{
	typedef Base64<CharT> _Myt;
	char EncodeTable[64];
	char DecodeTable[128];
struct Bytes4
{
	unsigned a:6;
	unsigned b:6;
	unsigned c:6;
	unsigned d:6;
};
struct Bytes3
{
	char a;
	char b;
	char c;
};

union Data
{
	 struct  Bytes4 B4;
	 struct  Bytes3 B3;
};


public:
	Base64();
	static _Myt & GetInstance()
	{
		static _Myt _self;
		return _self;
	}
	
    void Base64DeCode(const CharT *src,int ssize,unsigned char *dst,int &dsize);
	
	void Base64EnCode(unsigned char * src,int ssize, CharT *dst,int &dsize);

	template<typename StringT>
	void Base64EnCode(unsigned char * src, int ssize, StringT & szOut)
	{
		int poss, posd, padding;
		union Data D;

		poss = 0; posd = 0, padding = 0;
		for (; poss<ssize; )
		{
			if ((ssize - poss) >= 3) /*处理多于等于3个的*/
			{
				D.B3.a = src[poss++];
				D.B3.b = src[poss++];
				D.B3.c = src[poss++];
			}
			else   /*处理还剩字符少与3个的(末尾)*/
			{
				if (ssize - poss>0)/*还有可输入字符*/
				{
					D.B3.a = src[poss++];
					D.B3.b = D.B3.c = 0;
					padding = 2;
				}
				if (ssize - poss>0)
				{
					D.B3.b = src[poss++];
					padding = 1;
				}
			}

			szOut += (CharT)EncodeTable[D.B4.a];
			szOut += (CharT)EncodeTable[D.B4.b];
			szOut += (CharT)EncodeTable[D.B4.c];
			szOut += (CharT)EncodeTable[D.B4.d];
		}

		for (; padding > 0; padding--)
		{
			szOut += CharT('=');
		}
			
	};
private:
	void Init();
	int find(char ch);
};

#include "Base64.cpp"

#endif // !defined(AFX_BASE64_H__21BC1BF0_E577_11D1_868E_0060083663C0__INCLUDED_)
