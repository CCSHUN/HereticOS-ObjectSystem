// XMLObjectTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "..\..\other\TextIoSystem.h"
#include "..\..\other\HeapAnslyze.h"
/*
使用方法
1.stdafx.h中添加
#define ZIP
#define X86FOR64SYS
#include "..\..\other\Serialize.h"
#include "TestObject.h"

2.定义你需要做XML序列化的对象到一个头文件，比如 TestObject.h，要做XML序列化代码生成的类型要用MAKESTRUCTINFO定义

3.用代码生成器处理TestObject.h后会在ObjectSerDef目录生成各个对象的XML序列化工具代码。

4.将ObjectSerDef目录中的代码拖入解决方案相关目录，比如XmlObject;

5.之后就可以在相关代码文件中引用stdafx.h来使用TestObject.h中的相关对象

6._tmain是XML序列化相关用例代码。

7. XML不要手工设计，要以C++ struct定义的数据结构为准，否则不保证能够准确运行，需要XML样例时，可以初始化一个C++对象，然后将其序列化到XML文件
*/


#define USED_TIME(_nWaitTime,_Code) _nWaitTime=GetTickCount();_Code;_nWaitTime=GetTickCount()-_nWaitTime;





int _tmain(int argc, _TCHAR* argv[])
{
	
	//Node<PointImpl<int,char>> s;
	

	DWORD nWaitTime = 0;

	ErrorPrinter_OutputDebugString error;
	_tagTestObject tmp,tmp1,tmp2;
	vector_share<tstring_share> vct;

	error(_T("UsedTime=%u SerObjectToAnsiXmlFile(_tagTestObject, tmp, tstring(_T(\"d:\\TestObject.txt\")));"), nWaitTime);
	USED_TIME(nWaitTime,{
	tmp.bVal=FALSE;
	tmp.szObjectName=_T("TestObject001");
	tmp.nObjectType=5554;
	tmp.szVal=_T("<TestObject001></TestObject001>");
	tmp.fVal=1.01;
	tmp.lfVal=2.00555;
	tmp.nVal=666;
	tmp.iVal=-500;
	for(unsigned int i=0;i<4000;i++)
	{
		_tagTestSubObject subobj;
		error(subobj.szSubObjectName,_T("SubTestObject_%d"),i);
		subobj.nSubObjectType=i*100;
		subobj.bSubVal=i%2;
		subobj.iSubObject=i*((subobj.bSubVal==TRUE)?(-1):1);
		subobj.fSubObject=i*1.1234;
		subobj.lfSubObject=i*1.123456789;
		tmp.SubObjectArray.push_back(subobj);
		tmp.SubObjectMap[subobj.szSubObjectName]=subobj;
		vct.push_back(tstring_share(tmp.szObjectName.c_str()));
	}
	tmp.SubObject=tmp.SubObjectArray[0];
	tmp.SubObject.szSubObjectName=_T("TestSubObject");
	});
	vct.clear();

	//error(_T("UsedTime=%u Make..."), nWaitTime);
	//tmp.
	//序列化tmp对象到c:\\TestObject.txt
	//SerObjectToAnsiXmlFile(_tagTestObject, tmp, tstring(_T("d:\\TestObject.txt")));
	//SerAnsiFileToObject(_tagTestObject, tmp1, _T("d:\\TestObject.txt"));

	

	USED_TIME(nWaitTime, { SerObjectToAnsiXmlFile(_tagTestObject, tmp, tstring(_T("d:\\TestObject.txt"))); });
	error(_T("UsedTime=%u SerObjectToAnsiXmlFile(_tagTestObject, tmp, tstring(_T(\"d:\\TestObject.txt\")));"), nWaitTime);
	//读取c:\\TestObject.txt到tmp1
	USED_TIME(nWaitTime, { SerAnsiFileToObject(_tagTestObject, tmp1, _T("d:\\TestObject.txt")); });
	error(_T("UsedTime=%u SerAnsiFileToObject(_tagTestObject, tmp1, tstring(_T(\"d:\\TestObject.txt\")));"), nWaitTime);
	return 0;
	//序列化tmp对象到szXMLBuffer字符串
	wstring szXMLBuffer;
	SerObjectToUnicodeXmlBuffer(_tagTestObject,tmp1,szXMLBuffer);
	//error(_T("%s"),szXMLBuffer.c_str());

	//读取XML字符串到tmp2
	SerTCHARXmlBufferToObject(_tagTestObject,tmp2,szXMLBuffer.c_str());
	return 0;
}

