// CodeTest.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//û�����õĲ���,�������û��������Ӧ�������к괦��
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
	char pIn=new char[512];
	char pOut=new char[1024];
	testCopy(pIn,pOut);

	return 0;
}

