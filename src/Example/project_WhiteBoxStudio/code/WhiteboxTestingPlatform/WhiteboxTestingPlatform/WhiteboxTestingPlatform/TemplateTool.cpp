#include "StdAfx.h"
#include "TemplateTool.h"

CTemplateTool::CTemplateTool(void)
{
}

CTemplateTool::~CTemplateTool(void)
{
}

typedef struct _tagTemplateContext
{
	TCHAR * pReplacePoint;
	TCHAR * pNextBeginPoint;
	tstring szIntex;
}TemplateContext,*PTemplateContext;
BOOL CTemplateTool::MakeStringByTemplateString_Recursion(IN map<tstring,tstring,less<tstring> > & ValMap,IN tstring & szTemplate,OUT tstring & szData)
{
	for(unsigned int n=0;;n++)
	{
		BOOL bRet=MakeStringByTemplateString(ValMap,szTemplate, szData);
		if(bRet==FALSE)
		{
			if(n==0)
			{
				return FALSE;
			}else
			{
				return TRUE;
			}
		}else
		{
			szTemplate=szData;
		}
	}
	
}
BOOL CTemplateTool::MakeStringByTemplateString(IN map<tstring,tstring,less<tstring> > & ValMap,IN tstring & szTemplate,OUT tstring & szData)
{
	map<DWORD_PTR,_tagTemplateContext,less<unsigned int> > ReplaceMap;

	map<tstring,tstring,less<tstring> >::iterator itDst=ValMap.begin();
	szData.clear();

	for(;itDst!=ValMap.end();itDst++)
	{
		_tagTemplateContext Context;
		Context.pNextBeginPoint=(TCHAR *)szTemplate.c_str();
		for(;;)
		{
			Context.pReplacePoint=strstr_t(Context.pNextBeginPoint,itDst->first.c_str());
			if(Context.pReplacePoint)
			{
				Context.pNextBeginPoint=Context.pReplacePoint+itDst->first.length();
				Context.szIntex=itDst->first;
				ReplaceMap[(DWORD_PTR)Context.pReplacePoint]=Context;
			}else
			{
				break;
			}
		}
	}
	if(ReplaceMap.size()==0)
	{
		return FALSE;
	}
	//¶Ï¾ä
	map<DWORD_PTR,_tagTemplateContext,less<unsigned int> >::iterator itContext=ReplaceMap.begin();
	for(;itContext!=ReplaceMap.end();itContext++)
	{
		(*(itContext->second.pReplacePoint))=0;
	}

	//ÖØ×é
	itContext=ReplaceMap.begin();
	szData=szTemplate.c_str();
	for(;itContext!=ReplaceMap.end();itContext++)
	{
		tstring sz=ValMap[itContext->second.szIntex];
		tstring szEnd=itContext->second.pNextBeginPoint;
		szData+=ValMap[itContext->second.szIntex];
		szData+=itContext->second.pNextBeginPoint;
	}

	return TRUE;
}

BOOL CTemplateTool::MakeFileByTemplateFile(IN CTemplateTool::TemplateMap & ValMap,IN tstring & szTemplateFileName,OUT tstring & szOutFileName)
{
	CStdioFile fTemplatefile;
	if (!fTemplatefile.Open(/*theApp.GetAppPath()+*/szTemplateFileName.c_str(), CFile::modeRead)){
		return FALSE;
	}

	CStdioFile fOutfile;
	if(strstr_t(szOutFileName.c_str(),_T("\\")))
	{
		if (!fOutfile.Open(szOutFileName.c_str(), CFile::modeCreate | CFile::modeReadWrite)){
			return FALSE;
		}
	}else
	{
		if (!fOutfile.Open(/*theApp.GetAppPath()+*/szOutFileName.c_str(), CFile::modeCreate | CFile::modeReadWrite)){
			return FALSE;
		}
	}


	CString szTemplate1;
	tstring szTemplate;
	tstring szOutFile;
	for(;;)
	{
		if(fTemplatefile.ReadString(szTemplate1))
		{
			szTemplate+=(LPCTSTR)szTemplate1;
			szTemplate+=_T("\r\n");
		}else
		{
			break;
		}
	}

	if(MakeStringByTemplateString(ValMap,szTemplate,szOutFile))
	{
		fOutfile.WriteString(szOutFile.c_str());
		fTemplatefile.Close();
		fOutfile.Close();
		return TRUE;
	}
	fTemplatefile.Close();
	fOutfile.Close();
	return FALSE;
}

BOOL CTemplateTool::FileToString(tstring & szFilePath,tstring & szData)
{
	CStdioFile fOutfile;
	szData.clear();
	if(szFilePath.length()==0) return FALSE;
	if(szFilePath[1]==':')
	{
		if (!fOutfile.Open(szFilePath.c_str(), CFile::modeRead)){
			return FALSE;
		}
	}else
	{
		TCHAR   szPath[MAX_PATH]; 
		::GetModuleFileName(NULL, szPath, MAX_PATH);
		TCHAR * pPos=strrchr_t(szPath,'\\');
		if(pPos)
		{
			*(pPos+1)=0;
		}
		tstring strPath=szPath;
		strPath+=szFilePath;
		

		if (!fOutfile.Open(strPath.c_str(), CFile::modeRead)){
			return FALSE;
		}
	}
	CString szLine;
	for(;;)
	{
		if(fOutfile.ReadString(szLine))
		{
			szData+=(LPCTSTR)szLine;
			szData+=_T("\r\n");
		}else
		{
			break;
		}
	}
	szData+=_T("\r\n");
	fOutfile.Close();
	return TRUE;

}


BOOL  CTemplateTool::StringToFile(tstring & szFilePath,tstring & szData)
{
	CStdioFile fOutfile;
	if(szFilePath[1]==':')
	{
		if (!fOutfile.Open(szFilePath.c_str(), CFile::modeRead)){
			return FALSE;
		}
	}else
	{
		TCHAR   szPath[MAX_PATH]; 
		::GetModuleFileName(NULL, szPath, MAX_PATH);
		TCHAR * pPos=strrchr_t(szPath,'\\');
		if(pPos)
		{
			*(pPos+1)=0;
		}
		tstring strPath=szPath;
		strPath+=szFilePath;


		if (!fOutfile.Open(strPath.c_str(), CFile::modeRead)){
			return FALSE;
		}
	}
	fOutfile.WriteString(szData.c_str());
	fOutfile.Close();
	return TRUE;
}
