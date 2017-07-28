#include "StdAfx.h"
#include "CommonFunc.h"

CommonFunc::CommonFunc(void)
{
}

CommonFunc::~CommonFunc(void)
{
}

CString CommonFunc::GetFileName(const CString &sFileName)
{
	int nPos = sFileName.ReverseFind('\\');
	if (nPos != -1){
		return sFileName.Mid(nPos+1);
	}
	return CString("");
}