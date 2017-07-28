#pragma once


class CTemplateTool
{
public:

	CTemplateTool(void);
	~CTemplateTool(void);
	typedef map<tstring,tstring,less<tstring> > TemplateMap;
	static BOOL MakeStringByTemplateString(IN map<tstring,tstring,less<tstring> > & ValMap,IN tstring & szTemplate,OUT tstring & szData);
	//递归模板,直到没有模板为止 
	static BOOL MakeStringByTemplateString_Recursion(IN map<tstring,tstring,less<tstring> > & ValMap,IN tstring & szTemplate,OUT tstring & szData);
	static BOOL MakeFileByTemplateFile(IN CTemplateTool::TemplateMap & ValMap,IN tstring & szTemplateFileName,OUT tstring & szOutFileName);

	static BOOL FileToString(tstring & szFilePath,tstring & szData);
	static BOOL  StringToFile(tstring & szFilePath,tstring & szData);
};
