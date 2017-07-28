// GlobalsMsg.h: interface for the CGlobalsMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBALSMSG_H__F291D20F_7A20_4ED5_9D2E_D0037C7DE0F5__INCLUDED_)
#define AFX_GLOBALSMSG_H__F291D20F_7A20_4ED5_9D2E_D0037C7DE0F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "GlobalsMsgDef.h"
//#include "GlobalMsgConfig.h"

#ifndef SYSOP_KERNEL
#include "ThreadBaseForWin32App.h"
#include <list>
using namespace std;

#endif

#ifdef SYSOP_KERNEL
#include "ThreadBaseForKernel.h"

#endif

#pragma pack(push,1)
typedef struct _tagGlobalsMsgCtl
{
	unsigned int nCommand;			//发送的命令ID
	unsigned int nSendMsgBuferPos;		//发送缓冲
	unsigned int nSendMsgLen;		//发送消息长度
	unsigned int nRetMsgBuferPos;	//返回消息缓冲
	unsigned int nRetMsgLen;		//返回消息长度	
	unsigned int nRetFalg;			//返回标志
	unsigned int nContext;			//消息接受关联上下文
}GlobalsMsgCtl,*PGlobalsMsgCtl;
#pragma pack(pop)

class CGlobalsMsg  : public CThreadBase
{
public:
	//BOOL BuildAlowingSD(PSECURITY_DESCRIPTOR *pSecurityDescriptor,ACCESS_MASK AccessMask) ;
	static DWORD __stdcall RecvThread(void *param);
	BOOL init(char * pMsgName);
	BOOL SetRecvMsgCallBack(fp_MsgCallBack  pCall,unsigned int nContext);
	BOOL SendMsg(unsigned int nCommand, void *pInBuffer, unsigned int nInBufLen,void ** pRetBuffer,unsigned int * nRetBufLen,unsigned int * nRetFalg,unsigned int nTimerWait=INFINITE);
	HANDLE m_hRecvThread;
	fp_MsgCallBack m_RecvCallBack;
	HANDLE m_CloseEvent;
	HANDLE m_DataMutex;		//映射操作互拆句柄
	//消息控制事件
	HANDLE m_SendMsgEvent;
	HANDLE m_MsgEventComplate;
	LPVOID m_DataMapView;		//映射内存指针

	CGlobalsMsg();
	CGlobalsMsg(char * pName)
	{
		init(pName);
	}
	~CGlobalsMsg();

	
	SECURITY_ATTRIBUTES m_sMapa;
	
	SECURITY_ATTRIBUTES m_sMutexa;
	SECURITY_ATTRIBUTES m_sEventa;
	SECURITY_ATTRIBUTES m_sEventComplatea;
private:
	//设置安全参数
	void SetSecurity();

	//控制参数MAP
	HANDLE m_DataMap;			//映射内存句柄
		

	BOOL m_bInit;

	
};

#endif // !defined(AFX_GLOBALSMSG_H__F291D20F_7A20_4ED5_9D2E_D0037C7DE0F5__INCLUDED_)
