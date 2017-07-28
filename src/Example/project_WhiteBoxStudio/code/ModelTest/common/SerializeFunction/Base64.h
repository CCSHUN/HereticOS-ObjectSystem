// Base64.h: interface for the Base64 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE64_H__21BC1BF0_E577_11D1_868E_0060083663C0__INCLUDED_)
#define AFX_BASE64_H__21BC1BF0_E577_11D1_868E_0060083663C0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class Base64  
{
	char EncodeTable[64];
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
	
    void Base64DeCode(unsigned char *src,int ssize,unsigned char *dst,int &dsize);
	
	void Base64EnCode(unsigned char *src,int ssize,unsigned char *dst,int &dsize);
private:
	void Init();
	int find(char ch);
};

#endif // !defined(AFX_BASE64_H__21BC1BF0_E577_11D1_868E_0060083663C0__INCLUDED_)
