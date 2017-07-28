#pragma once


extern int g_nBuildCount;
extern BOOL	g_bStopBuild;
class CReport
{
public:
	CReport(void);
	~CReport(void);

	enum{ BUILD_TYPE, REBUILD_TYPE };

public:
	BOOL _Build();
	BOOL _ReBuild();
	BOOL BuildPClintReport();
	BOOL BuildYDReport();
	BOOL BuildReport();
	BOOL Build();
	BOOL AddReportItem(_S_REPORT_Wrap &report, const CString &sInfo, 
		const CString &sModuleName, const CString &sErrorRowContent, int no, const tstring &sCodeRootPath);
	BOOL GetPCLintObject(const CString &sInfo, _tagPCLintReportItem &pclint_item);

	void SetBuildType(int nIsReBuild){ m_nIsReBuild = nIsReBuild; };
	int GetBuildType(){ return m_nIsReBuild; };

public:
	CProjectSharedData *m_pShareData;
private:
	int m_nIsReBuild;
};
