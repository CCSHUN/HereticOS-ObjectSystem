#include "stdafx.h"
#include "myworkthread.h"
#include <process.h>

vector<CReport *> g_vReport;
CRITICAL_SECTION  g_cs_report; 
int g_bExit = 0;

unsigned __stdcall WorkThreadFunc(void * pParam)
{
	vector<CReport *> vReport;

	while (!g_bExit){
		EnterCriticalSection(&g_cs_report);
		if (g_vReport.size() > 0){
			for (unsigned int i=0; i<g_vReport.size(); i++){
				vReport.push_back(g_vReport[i]);			
			}
			g_vReport.clear();
		}
		LeaveCriticalSection(&g_cs_report);	

		for (unsigned int i=0; i<vReport.size(); i++){
			CReport *pReport = vReport[i];
			pReport->Build();
			delete pReport;

			g_nBuildCount--;
		}

		vReport.clear();
		Sleep(100);
	}

	::DeleteCriticalSection(&g_cs_report);
	return 0;
}

BOOL CreateWorkThread()
{
	HANDLE hThread;
	unsigned threadID;

	::InitializeCriticalSection(&g_cs_report);

	hThread = (HANDLE)_beginthreadex(NULL, 0, &WorkThreadFunc, NULL, 0, &threadID);

	if(hThread == NULL)
		return FALSE;

	return TRUE;
}

 void AddTaskToWorkThread(CReport *pReport)
 {
	 EnterCriticalSection(&g_cs_report);
	 g_vReport.push_back(pReport);	
	 LeaveCriticalSection(&g_cs_report);	
 }


















