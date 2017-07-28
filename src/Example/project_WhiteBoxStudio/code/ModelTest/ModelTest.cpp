// ModelTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "DataModuleDef.h"


//#include "Serialize.h"CObjectSystem_Local sysobj;
#include "ObjectSystem_Local.h"
CObjectSystem_Local gobjsys;

//CObjectSystem * gpObjectSystem;

//gpObjectSystem=(CObjectSystem*)&gobjsys;

_tagUserMapSet_Wrap test,test1;

#include "shellapi.h"
#include "SoapOperation.h"


/*
void testsoap()
{
	CSoapOperation soap;
	tstring szUserName=_T("yess");
	tstring szConversation=_T("yess1");
	tstring szOpCode=_T("1");
	tstring szCallParameter=_T("yess3");
	tstring szRetXml=_T("yess4");

	gConfig.init(NULL);
	//tstring sz
	_tagCallParameter pa,retpa;
	soap.CallInterface(szUserName,szConversation,1,pa,retpa);
}*/
//转换标准

#define UNITE_STANDARD_NAME _T("MachineCheckStandardLib")
#define THIRD_STANDARD_NAME _T("ThirdStandardlib")
#define STANDARD_ERROR_TYPE_ADDR			_T("MachineCheckStandardTypeLib")
#define STANDARD_ERRORWARNING_ADDR			_T("ErrorWarningDefine")
void Trang()
{
	gpObjectSystem=&gobjsys;
	tstring szStandardName=_T("YD应用程序检查标准");
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\MachineCheckStandard_"))+szStandardName+tstring(_T("\\"));
	_tagMachineCheckStandardLib_Wrap		MachineCheckStandardLib;
	_tagThirdStandardlib_Wrap				ThirdStandardlib;
	_tagMachineCheckStandardTypeLib_Wrap	MachineCheckStandardTypeLib;
	_tagErrorWarningArray_Wrap				ErrorWarningArray;

	MachineCheckStandardLib.m_szAddr=szPath+UNITE_STANDARD_NAME;
	BOOL bOk=MachineCheckStandardLib.GetObject();

	/*map<tstring,_tagMachineCheckStandardSet,less<tstring> > 

	map<tstring,_tagThirdStandardSet,less<tstring> > libmap;*/
	/*map<tstring,_tagMachineCheckStandardSet,less<tstring> >::iterator itMap=MachineCheckStandardLib.m_Data.libmap.begin();
	for(;itMap!=MachineCheckStandardLib.m_Data.libmap.end();itMap++)
	{
		tstring szErrorSuggest=(WCHAR *)CMyString((char *)itMap->second.szErrorSuggest.c_str(),itMap->second.szErrorSuggest.length()*2);
		tstring szDesc=(WCHAR *)CMyString((char *)itMap->second.szDesc.c_str(),itMap->second.szDesc.length()*2);
		//tstring szThirdStandardErrorDesc=(WCHAR *)CMyString((char *)itMac->second.szThirdStandardErrorDesc.c_str(),itMac->second.szThirdStandardErrorDesc.length()*2);
		itMap->second.szErrorSuggest=szErrorSuggest;
		itMap->second.szDesc=szDesc;
	}

	bOk=MachineCheckStandardLib.UpDataObject();*/

	if(bOk==FALSE) return ;
	ThirdStandardlib.m_szAddr=szPath+THIRD_STANDARD_NAME;


	ThirdStandardlib.GetObject();
	/*map<tstring,_tagThirdStandardSet,less<tstring> >::iterator itMap=ThirdStandardlib.m_Data.libmap.begin();
	for(;itMap!=ThirdStandardlib.m_Data.libmap.end();itMap++)
	{
		tstring szErrorSuggest=(WCHAR *)CMyString((char *)itMap->second.szErrorSuggest.c_str(),itMap->second.szErrorSuggest.length()*2);
		tstring szManual_check_MethodSpecify=(WCHAR *)CMyString((char *)itMap->second.szManual_check_MethodSpecify.c_str(),itMap->second.szManual_check_MethodSpecify.length()*2);
		tstring szThirdStandardErrorDesc=(WCHAR *)CMyString((char *)itMap->second.szThirdStandardErrorDesc.c_str(),itMap->second.szThirdStandardErrorDesc.length()*2);
		//tstring szThirdStandardErrorDesc=(WCHAR *)CMyString((char *)itMac->second.szThirdStandardErrorDesc.c_str(),itMac->second.szThirdStandardErrorDesc.length()*2);
		itMap->second.szThirdStandardErrorDesc=szThirdStandardErrorDesc;
		itMap->second.szManual_check_MethodSpecify=szManual_check_MethodSpecify;
		itMap->second.szErrorSuggest=szErrorSuggest;
	}

	bOk=ThirdStandardlib.UpDataObject();*/


	if(bOk==FALSE) return ;
	MachineCheckStandardTypeLib.m_szAddr=szPath+THIRD_STANDARD_NAME;
	MachineCheckStandardTypeLib.GetObject();
	if(bOk==FALSE) return ;

	ErrorWarningArray.m_szAddr=szPath+STANDARD_ERRORWARNING_ADDR;
	ErrorWarningArray.GetObject();

	/*for(unsigned int i=0;i<ErrorWarningArray.m_Data.WarningArray.size();i++)
	{
		tstring szErrorWarningDesc=(WCHAR *)CMyString((char *)ErrorWarningArray.m_Data.WarningArray[i].szErrorWarningDesc.c_str(),ErrorWarningArray.m_Data.WarningArray[i].szErrorWarningDesc.length()*2);
		tstring szErrorWarningName=(WCHAR *)CMyString((char *)ErrorWarningArray.m_Data.WarningArray[i].szErrorWarningName.c_str(),ErrorWarningArray.m_Data.WarningArray[i].szErrorWarningName.length()*2);
		//tstring szThirdStandardErrorDesc=(WCHAR *)CMyString((char *)itMac->second.szThirdStandardErrorDesc.c_str(),itMac->second.szThirdStandardErrorDesc.length()*2);
		ErrorWarningArray.m_Data.WarningArray[i].szErrorWarningDesc=szErrorWarningDesc;
		ErrorWarningArray.m_Data.WarningArray[i].szErrorWarningName=szErrorWarningName;
	}
	bOk=ErrorWarningArray.UpDataObject();*/
	if(bOk==FALSE) return ;


	return ;
}

void TestCAutoVal()
{

};

int main(int argc, char* argv[])
{
	//Trang();
	tstring strTest=_T("1234567890");
	tstring strout;
	CBase64Zip::Base64ZipCompress((unsigned char *)strTest.c_str(),strTest.length()*sizeof(TCHAR),strout);
	vector<unsigned char> buf;
	CBase64Zip::Base64ZipUnCompress(strout,buf);

	return 0;
	tstring szf =_T("12213asdasd");
	int n=atoi_t(szf.c_str());
	return 0;

	tstring szFile=_T("e:\\test\\123\\1234\\123456");
	tstring szDir;
	//GetObjectDirPath(szFile,szDir);
	//BOOL bSucess=CreatedObjectMultipleDirectory(tstring(_T("e:\\test\\123\\1234\\123456")));
	tstring szData;
	/*
	for(int i=0;i<10240000;i++)
	{
		szData+="asdsadsadsad3243retretretrt45trytrytr";
	}
	*/
	unsigned int nLen=szData.length();

	gpObjectSystem=&gobjsys;
	test.m_szAddr=_T("UserInfo\\UserMap\\yess");
	test.m_Data.szUserName=_T("yess");
	test.m_Data.szPassword=_T("8ik,9ol.0p;/");
	test.m_Data.szUserType=_T("测试");
	test.UpDataObject();

	test1.m_szAddr=_T("UserInfo\\UserMap\\yess");
	/*test1.m_ObjectState.bLock=TRUE;
	test1.m_ObjectState.nLockTime=100;
	test1.m_ObjectState.nType=CObjectSystem::AutoProlong;
	test1.m_ObjectState.szLockUser=_T("yess");*/

	test1.GetObject();
	test1.UpDataObject();

	test1.m_szAddr=_T("UserInfo");
	//test1.DeleteObject();

	_tagTestHexString_Wrap asd;
	asd.m_szAddr=_T("UserInfo\\UserMap\\TestHexString");
	asd.m_Data.Test=_T("<Test>21321321,,,214,32,4,324,32,4,324,45,43,543\r\nasdasjnscdkjcnjkzncjds</Test>");
	asd.UpDataObject();

	_tagTestHexString_Wrap asd1;
	asd1.m_szAddr=_T("UserInfo\\UserMap\\TestHexString");
	/*asd1.m_Data.Test=_T("asdsafdssadasdasdas");*/
	BOOL bRet=asd1.GetObject();
	const TCHAR * pText=asd1.m_Data.Test.c_str();
	tstring str=asd1.m_Data.Test;

	_S_REPORT_Wrap test22;
	_S_REPORT_ITEM itSet;
	_tagReportLog Log;
	test22.m_szAddr=_T("UserInfo\\UserMap\\TestReport");
	//SER_TO_X<tstring,HexString> sz;
	//sz=(LPCTSTR)_T("asdsafdsfdsfdsfdsf");
	Log.szReport_log=(LPCTSTR)_T("asdsafdsfdsfdsfdsf");
	//itSet.szReport_log.push_back(Log);
	for(unsigned int i=0;i<10;i++)
	{
		itSet.szThirdStandardErrorNum=_T("100");
		itSet.szDesc=_T("<test>1221324324ewfdsafadsfdasf,ds,fre,wf,er,f,r,eg,t,ewf,re,g,t,g,ew,r,e3wr,54t,45,g,t5,g,45,g,werf,re,</test><test>1221324324ewfdsafadsfdasf,ds,fre,wf,er,f,r,eg,t,ewf,re,g,t,g,ew,r,e3wr,54t,45,g,t5,g,45,g,werf,re,</test><test>1221324324ewfdsafadsfdasf,ds,fre,wf,er,f,r,eg,t,ewf,re,g,t,g,ew,r,e3wr,54t,45,g,t5,g,45,g,werf,re,</test><test>1221324324ewfdsafadsfdasf,ds,fre,wf,er,f,r,eg,t,ewf,re,g,t,g,ew,r,e3wr,54t,45,g,t5,g,45,g,werf,re,</test><test>1221324324ewfdsafadsfdasf,ds,fre,wf,er,f,r,eg,t,ewf,re,g,t,g,ew,r,e3wr,54t,45,g,t5,g,45,g,werf,re,</test><test>1221324324ewfdsafadsfdasf,ds,fre,wf,er,f,r,eg,t,ewf,re,g,t,g,ew,r,e3wr,54t,45,g,t5,g,45,g,werf,re,</test>");
		
		test22.m_Data.items.push_back(itSet);
	}
	test22.UpDataObject();

	_S_REPORT_Wrap test12;
	test12.m_szAddr=_T("UserInfo\\UserMap\\TestReport");
	test12.GetObject();
	

	printf("Hello World!\n");
	return 0;
}

