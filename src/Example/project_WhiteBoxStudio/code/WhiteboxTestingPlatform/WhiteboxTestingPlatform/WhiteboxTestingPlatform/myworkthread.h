#ifndef _MYWORKTHREAD_H

#include <winbase.h>
#include "Report.h"
#include <vector>
using namespace std;

extern int g_bExit;
extern BOOL CreateWorkThread();
extern void AddTaskToWorkThread(CReport *);

#endif
