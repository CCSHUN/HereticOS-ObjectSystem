#include "StdAfx.h"
#include "Report.h"
#include "WhiteboxTestingPlatform.h"
#include "MainFrm.h"
#include "ProjectDataModel.h"

#define PCLINT_REPORT_SUCCESS_FLAG_OFFSET -250

#define PCLINT_REPORT_NAME						_T("___OUTPUT.TXT\0")
#define PCLINT_CONFIG_NAME						_T("isf5.lnt\0")

#define PCLINT_REPORT_SEPARATORS		_T("###CF50A6A3-7BDB-9134-1D56-C79BA8CB647E###\0")
#define PCLINT_REPORT_MODULE_FLAG		_T("--- Module:   \0")
#define PCLINT_REPORT_SUCCESS_FLAG		_T("###CF50A6A3-7BDB-9134-1D56-C79BA8CB647E###900###CF50A6A3-7BDB-9134-1D56-C79BA8CB647E###")

#define PCLINT_REPORT_RECORD_FLAG		PCLINT_REPORT_SEPARATORS



int g_nBuildCount = 0;
BOOL	g_bStopBuild=FALSE;

CReport::CReport(void)
{
	m_pShareData = NULL;
}

CReport::~CReport(void)
{
}

BOOL CReport::_Build()
{
	if(BuildYDReport()==FALSE)
	{
		_ReBuild();
	}
	return TRUE;
}

BOOL CReport::BuildReport()
{
	return TRUE;
}

BOOL CReport::BuildYDReport()
{
	CStdioFile file;
	BOOL bSucess = FALSE;

	tstring sOutputName = m_pShareData->GetProjectName() + tstring(_T("_")) + 
		m_pShareData->GetSubProjectName() + tstring(_T("_OUTPUT.txt"));
	if (!file.Open(theApp.GetAppPath()+_T("lint\\")+sOutputName.c_str(), CFile::modeRead | CFile::typeText)){
		return bSucess;
	}
	LONGLONG lOffset = PCLINT_REPORT_SUCCESS_FLAG_OFFSET;
	if (file.GetLength() < 250){
		file.Close();
		return FALSE;
	}
	file.Seek(lOffset, CFile::end);

	//check pclint' repo
	CString sInfo;
	while (file.ReadString(sInfo)){
		if (sInfo.Find(PCLINT_REPORT_SUCCESS_FLAG) != -1){
			bSucess = TRUE;
			break;
		}
	}
	if (!bSucess){
		((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== PC-lint机械走读报告生成错误，请重新配置参数 ========\r\n"));
		return bSucess;
	}

	//file.Close();

	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== 开始生成YD机械走读报告 ========\r\n"), SB_BOTTOM, FALSE);

	//重新加载标准
	m_pShareData->GetYDStandardLibObject();
	m_pShareData->GetThirdStandardlibObject();
	m_pShareData->GetStandardErrorTypeNameLib();
	m_pShareData->GetStandardErrorWarningNameArray();
	m_pShareData->GetConfigObject();

	_S_REPORT_Wrap report;
	tstring szPath = m_pShareData->GetProjectWholePath()+tstring(_T("TestReport"));
	report.m_szAddr = szPath;
	report.m_Data.szName = _T("");
	report.m_Data.nErrorCount_1 = 0;
	report.m_Data.nErrorCount_2 = 0;
	report.m_Data.nErrorCount_3 = 0;

	//start to parse pclint' report
	tstring sCodeRootPath = m_pShareData->GetSubProjectCodePath();
	int nCount =1, nTotalCount = 0;
	CString sErrorRowContent, sModuleName;
	file.SeekToBegin();
	while (file.ReadString(sInfo)){
		if (sInfo.Find(PCLINT_REPORT_RECORD_FLAG) == 0){
			if (AddReportItem(report, sInfo, sModuleName, sErrorRowContent, nCount++, sCodeRootPath)){
				nTotalCount++;
			}
			if(g_bStopBuild)
			{
				g_bStopBuild=FALSE;
				((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== Build 过程被终止 ========\r\n"));
				return FALSE;
			}
			continue;
		}

		if (sInfo.Find(PCLINT_REPORT_MODULE_FLAG) == 0){
			sModuleName = sInfo.Mid(strlen_t(PCLINT_REPORT_MODULE_FLAG)-1);
			continue;
		}

		sErrorRowContent = sInfo;
	}

	report.m_Data.nTotalErrorCount = nTotalCount;

	
	report.UpDataObject();
	m_pShareData->m_bNeedGetReport=TRUE;
	//m_pShareData->GetReportObject();
	m_pShareData->m_bComplateReportUpdated = TRUE;
	m_pShareData->m_bManualReportUpdated = TRUE;
	m_pShareData->m_bNofindReportUpdated = TRUE;

	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== YD机械走读报告生成成功 ========\r\n"), SB_BOTTOM);
	return bSucess;
}

BOOL CReport::GetPCLintObject(const CString &sInfo, _tagPCLintReportItem &pclint_item)
{
	int nPos = sInfo.Find(PCLINT_REPORT_SEPARATORS, strlen_t(PCLINT_REPORT_SEPARATORS));
	if (nPos == -1){
		return FALSE;
	}
	CString sFileName = sInfo.Mid(strlen_t(PCLINT_REPORT_SEPARATORS), nPos-strlen_t(PCLINT_REPORT_SEPARATORS));

	int nPos2 = sInfo.Find(PCLINT_REPORT_SEPARATORS, nPos+1);
	if (nPos2 == -1){
		return FALSE;
	}
	CString sErrorNo = sInfo.Mid(nPos+strlen_t(PCLINT_REPORT_SEPARATORS), nPos2-nPos-strlen_t(PCLINT_REPORT_SEPARATORS));

	nPos = nPos2;
	nPos2 = sInfo.Find(PCLINT_REPORT_SEPARATORS, nPos+1);
	if (nPos2 == -1){
		return FALSE;
	}
	CString sRowNo = sInfo.Mid(nPos+strlen_t(PCLINT_REPORT_SEPARATORS), nPos2-nPos-strlen_t(PCLINT_REPORT_SEPARATORS));

	nPos = nPos2;
	CString sMsgTxt = sInfo.Mid(nPos+strlen_t(PCLINT_REPORT_SEPARATORS));

	pclint_item.filename = sFileName.GetBuffer(0);
	pclint_item.errorno = sErrorNo.GetBuffer(0);
	pclint_item.rowno = atol_t(sRowNo.GetBuffer(0));
	pclint_item.msgtxt = sMsgTxt.GetBuffer(0);

	return TRUE;
}

BOOL CReport::AddReportItem(_S_REPORT_Wrap &report, const CString &sInfo, 
							const CString &sModuleName, const CString &sErrorRowContent, int no, const tstring &sCodeRootPath)
{
	BOOL bRet = FALSE;
	_tagPCLintReportItem pclint_item;
	GetPCLintObject(sInfo, pclint_item);

	if ((pclint_item.filename.length()==0) && 
		(pclint_item.errorno.length()==0) &&
		(pclint_item.msgtxt.length()==0)){
		return bRet;
	}

	CString sDebugInfo;
	sDebugInfo.Format(_T("[%d]  %s, %s\r\n"), no, pclint_item.errorno.c_str(), pclint_item.msgtxt.c_str());
	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(sDebugInfo);

	CString sRowNo;
	sRowNo.Format(_T("%d"), pclint_item.rowno);

	_tagThirdStandardSet ThirdStandardSet;
	_S_REPORT_ITEM item;
	item.szTestState = _T("检查通过");

	_tagThirdStandardlib ThirdStandardlib = m_pShareData->m_ThirdStandardlib;
	map<tstring,_tagThirdStandardSet,less<tstring> >::iterator it = ThirdStandardlib.libmap.find(pclint_item.errorno);

	if (it == ThirdStandardlib.libmap.end()){
		item.szTestState = _T("需要充实规范");
	}else{
		ThirdStandardSet = it->second;
		if (ThirdStandardSet.is_dealwith){
			//return bRet;
			item.szTestState = _T("忽略");
		}else if (ThirdStandardSet.is_manual_check){
			item.szTestState = _T("需要人工复查");
		}

		if (ThirdStandardSet.szUniteStandardErrorNum == _T("未关联")){
			item.szTestState = _T("需要充实规范");
		}

		item.szUniteStandardErrorNum = ThirdStandardSet.szUniteStandardErrorNum;
		item.szThirdDesc = ThirdStandardSet.szThirdStandardErrorDesc;
		item.szThirdSuggest = ThirdStandardSet.szErrorSuggest;
	}

	if (item.szUniteStandardErrorNum != _T("未关联") && item.szUniteStandardErrorNum != _T("")){
		_tagMachineCheckStandardLib MachineCheckStandardLib = m_pShareData->m_YDStandardLib;
		map<tstring,_tagMachineCheckStandardSet,less<tstring> >::iterator it2 = MachineCheckStandardLib.libmap.find(item.szUniteStandardErrorNum);
		if (it2 != MachineCheckStandardLib.libmap.end()){
			_tagMachineCheckStandardSet MachineCheckStandardSet = it2->second;
			item.szErrorType = MachineCheckStandardSet.szErrorType;
			item.szErrorWarning = MachineCheckStandardSet.szErrorWarning;
			item.szUniteDesc=MachineCheckStandardSet.szDesc;
			item.szUniteSuggest=MachineCheckStandardSet.szErrorSuggest;
		}else
		{
			item.szTestState = _T("需要充实规范");
		}
	}

	if(item.szTestState == _T("检查通过"))
	{
		item.szTestItemSource=_T("自动生成");
	}

	item.szTestToolType=_T("PC-Lint");
	item.szThirdStandardErrorNum = pclint_item.errorno;
	item.szErrorCodeContent = pclint_item.msgtxt;

	//erase root path
	int nPos = -1;
	if ((nPos=pclint_item.filename.find(sCodeRootPath)) != -1){
		pclint_item.filename = pclint_item.filename.substr(sCodeRootPath.length()+1);
	}
	item.szErrorCodePosition = pclint_item.filename + tstring(_T("(")) + tstring(sRowNo.GetBuffer(0)) + tstring(_T(")"));

	if ((nPos=sModuleName.Find(sCodeRootPath.c_str())) != -1){
		item.szModule = sModuleName.Mid(sCodeRootPath.length()+2);
	}else{
		item.szModule = sModuleName;
	}

	if ((nPos=item.szModule.find(_T("(C++)"))) != -1){
		item.szModule = item.szModule.substr(0, nPos);
	}

	item.szDesc = _T("");
	item.szDevelopState = _T("新增");
	item.szCreateTime = item.szLastEditTime = theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetCurTime();
	report.m_Data.items.push_back(item);

	bRet = TRUE;
	return bRet;
}

BOOL CReport::BuildPClintReport()
{
	//call pc-lint to create plint' report, 
	TCHAR cmdline[1024] = {0};
	tstring sConfigName = m_pShareData->GetProjectName() + tstring(_T("_")) + m_pShareData->GetSubProjectName() + tstring(_T(".lnt"));
	sprintf_s_t(cmdline,1024,_T( "\"%slint\\lint-nt.exe\" +v -i\"%s\" -u \"%s\""),
		theApp.GetAppPath(), 
		theApp.GetAppPath()+_T("lint"), 
		sConfigName.c_str());

	//create pc-lint' config file(sConfigName) 
	CStdioFile fConfigfile;
	if (!fConfigfile.Open(theApp.GetAppPath()+_T("lint\\") + CString(sConfigName.c_str()), CFile::modeCreate | CFile::modeReadWrite)){
		return FALSE;
	}
	char bufCheckCfg[4096*64] = {0};
	int nRetLen = ::WideCharToMultiByte(CP_ACP,
		0,
		m_pShareData->m_UserProjectConfig.CheckCfgStandard.c_str(),
		-1,
		bufCheckCfg,
		sizeof(bufCheckCfg),
		NULL,
		NULL);
	fConfigfile.WriteString(CString(bufCheckCfg));

	memset(bufCheckCfg, 0, sizeof(bufCheckCfg));
	nRetLen = ::WideCharToMultiByte(CP_ACP,
		0,
		m_pShareData->m_ProjectConfig.CheckCfgStandard.c_str(),
		-1,
		bufCheckCfg,
		sizeof(bufCheckCfg),
		NULL,
		NULL);
	fConfigfile.Write(bufCheckCfg, nRetLen);
	fConfigfile.Close();

	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
	sa.lpSecurityDescriptor = NULL;					//使用系统默认的安全描述符 
	sa.bInheritHandle = TRUE;							//创建的进程继承句柄
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))  //创建匿名管道
	{  
		((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("CreateProcess Failed!\r\n"), SB_BOTTOM);
		return FALSE;
	}

	STARTUPINFO si; 
	PROCESS_INFORMATION pi;
	ZeroMemory(&si,sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO); 
	GetStartupInfo(&si); 
	si.hStdError = hWrite; 
	si.hStdOutput = hWrite;								//新创建进程的标准输出连在写管道一端
	si.wShowWindow = SW_HIDE;						//隐藏窗口 
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	if (!CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))  //创建子进程
	{
		((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("CreateProcess PCLint Failed!\r\n"), SB_BOTTOM);
		return FALSE;
	}
	CloseHandle(hWrite);									//关闭管道句柄

	CFile fOutput;
	tstring sOutputName = m_pShareData->GetProjectName() + tstring(_T("_")) + m_pShareData->GetSubProjectName() + tstring(_T("_OUTPUT.txt"));
	if (!fOutput.Open(theApp.GetAppPath()+_T("lint\\") + sOutputName.c_str(), CFile::modeCreate | CFile::modeReadWrite)){
		CloseHandle(hRead);
		return FALSE;
	}

	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("----- PC-lint机械走读程序已经启动 -----\r\n"), SB_BOTTOM, TRUE);
	char buffer[4096] = {0};
	WCHAR szWideBuffer[4096] = {0};
	DWORD bytesRead;
	while (true) 
	{
		if (ReadFile(hRead, buffer, sizeof(buffer)-1, &bytesRead, NULL) == NULL)  //读取管道
			break;

		long lLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), szWideBuffer, sizeof(szWideBuffer)); 
		fOutput.Write(buffer, bytesRead);

		((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(szWideBuffer);
		Sleep(0);

		memset(buffer, 0, sizeof(buffer));
		memset(szWideBuffer, 0, sizeof(szWideBuffer));
		if(g_bStopBuild)
		{
			g_bStopBuild=FALSE;
			fOutput.Close();
			CloseHandle(hRead);
			CloseHandle(hWrite);
			::TerminateProcess(pi.hProcess,0);
			((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== Build 过程被终止（PClint） ========\r\n"));
			return FALSE;
		}
	}

	fOutput.Close();
	CloseHandle(hRead);
	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== PC-lint机械走读报告已经生成! ========\r\n"), SB_BOTTOM);

	return TRUE;
}

BOOL CReport::_ReBuild()
{
	if(BuildPClintReport())
	{
		BuildYDReport();
	}
	
	return TRUE;
}

BOOL CReport::Build()
{
	if (m_nIsReBuild){
		_ReBuild();
	}else{
		_Build();
	}
	g_bStopBuild=FALSE;

	return TRUE;
}
