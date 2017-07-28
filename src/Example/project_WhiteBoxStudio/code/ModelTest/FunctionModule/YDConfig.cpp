#include "StdAfx.h"
#include "YDConfig.h"
#include "shlobj.h"

CYDConfig::CYDConfig(void)
{
}

BOOL CYDConfig::GetLocalDir(tstring & szRunPath)
{
	/*TCHAR path[MAX_PATH];
	if (FAILED(::SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL,
		SHGFP_TYPE_CURRENT, path)))
	{
		return FALSE;
	}
	szRunPath=tstring(path)+tstring(_T("\\WihiteBoxTest"));*/

	TCHAR szFile[MAX_PATH];
	::GetModuleFileName(ghInstance,szFile,MAX_PATH);
	TCHAR * pFileName=strrchr_t(szFile,'\\');
	pFileName++;
	strcpy_t(pFileName,_T("YDConfig.xml"));
	szRunPath=szFile;

	return TRUE;
}

CYDConfig::~CYDConfig(void)
{
}
