// XMLObjectTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "windows.h"
#include "..\..\other\TextIoSystem.h"
#include "..\..\other\HeapAnslyze.h"
/*
ʹ�÷���
1.stdafx.h�����
#define ZIP
#define X86FOR64SYS
#include "..\..\other\Serialize.h"
#include "TestObject.h"

2.��������Ҫ��XML���л��Ķ���һ��ͷ�ļ������� TestObject.h��Ҫ��XML���л��������ɵ�����Ҫ��MAKESTRUCTINFO����

3.�ô�������������TestObject.h�����ObjectSerDefĿ¼���ɸ��������XML���л����ߴ��롣

4.��ObjectSerDefĿ¼�еĴ����������������Ŀ¼������XmlObject;

5.֮��Ϳ�������ش����ļ�������stdafx.h��ʹ��TestObject.h�е���ض���

6._tmain��XML���л�����������롣

7. XML��Ҫ�ֹ���ƣ�Ҫ��C++ struct��������ݽṹΪ׼�����򲻱�֤�ܹ�׼ȷ���У���ҪXML����ʱ�����Գ�ʼ��һ��C++����Ȼ�������л���XML�ļ�
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
	//���л�tmp����c:\\TestObject.txt
	//SerObjectToAnsiXmlFile(_tagTestObject, tmp, tstring(_T("d:\\TestObject.txt")));
	//SerAnsiFileToObject(_tagTestObject, tmp1, _T("d:\\TestObject.txt"));

	

	USED_TIME(nWaitTime, { SerObjectToAnsiXmlFile(_tagTestObject, tmp, tstring(_T("d:\\TestObject.txt"))); });
	error(_T("UsedTime=%u SerObjectToAnsiXmlFile(_tagTestObject, tmp, tstring(_T(\"d:\\TestObject.txt\")));"), nWaitTime);
	//��ȡc:\\TestObject.txt��tmp1
	USED_TIME(nWaitTime, { SerAnsiFileToObject(_tagTestObject, tmp1, _T("d:\\TestObject.txt")); });
	error(_T("UsedTime=%u SerAnsiFileToObject(_tagTestObject, tmp1, tstring(_T(\"d:\\TestObject.txt\")));"), nWaitTime);
	return 0;
	//���л�tmp����szXMLBuffer�ַ���
	wstring szXMLBuffer;
	SerObjectToUnicodeXmlBuffer(_tagTestObject,tmp1,szXMLBuffer);
	//error(_T("%s"),szXMLBuffer.c_str());

	//��ȡXML�ַ�����tmp2
	SerTCHARXmlBufferToObject(_tagTestObject,tmp2,szXMLBuffer.c_str());
	return 0;
}

