// CodeTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include <string>
using namespace std;


//#define MYUNREFERENCED_PARAMETER(d) (d)=(d);



void testCopy(char * pIN,char * pOut)
{
	char szBuf[256];
	memcpy(szBuf,pIN,strlen(pIN));
	strcpy(szBuf,pIN);
	strcpy(pOut,pIN);
	memcpy(pOut,pIN,strlen(pIN));
}

int _tmain(int argc, _TCHAR* argv[])
{
	//没有引用的参数,如果参数没有引用则应该用下列宏处理
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
	char pIn=new char[512];
	char pOut=new char[1024];
	testCopy(pIn,pOut);

	return 0;
}

