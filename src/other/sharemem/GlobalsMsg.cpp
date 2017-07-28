// GlobalsMsg.cpp: implementation of the CGlobalsMsg class.
// 2006.4.16 叶树深，驱动应用层共享内存消息
//////////////////////////////////////////////////////////////////////


#ifndef SYSOP_KERNEL

#include <stdio.h>
#include <stdlib.h>
#include <aclapi.h>
#include <sddl.h>
#include <AccCtrl.h>

#endif


#include "GlobalsMsg.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGlobalsMsg::CGlobalsMsg()
{
	m_CloseEvent=NULL;
	m_MsgEventComplate=NULL;
	m_SendMsgEvent=NULL;
	m_DataMutex=NULL;
	m_DataMap=NULL;
	m_MsgEventComplate=NULL;
	m_MsgEventComplate=NULL;
	m_MsgEventComplate=NULL;
	m_MsgEventComplate=NULL;


}

CGlobalsMsg::~CGlobalsMsg()
{
	if(m_CloseEvent)
	{
		SetEvent(m_CloseEvent);
		WaitForSingleObject(m_hRecvThread,INFINITE);
		CloseHandle(m_CloseEvent);
		CloseHandle(m_hRecvThread);
	}

	if(m_MsgEventComplate)
	{
		CloseHandle(m_MsgEventComplate);
	}

	if(m_SendMsgEvent)
	{
		CloseHandle(m_SendMsgEvent);
	}

	if(m_DataMutex)
	{
		CloseHandle(m_DataMutex);
	}

	if(m_DataMap)
	{
		CloseHandle(m_DataMap);
	}

}

BOOL CGlobalsMsg::SendMsg(unsigned int nCommand, void *pInBuffer, unsigned int nInBufLen,void ** pRetBuffer,unsigned int * nRetBufLen,unsigned int * nRetFalg,unsigned int nTimerWait)
{
	if(m_bInit==FALSE)
	{
		return FALSE;
	}
	//WaitForSingleObject(m_DataMutex,INFINITE);
	if(pInBuffer)
	{
		memcpy((char *)m_DataMapView+sizeof(GlobalsMsgCtl),pInBuffer,nInBufLen);
	}
	
	((PGlobalsMsgCtl)m_DataMapView)->nCommand=nCommand;
	((PGlobalsMsgCtl)m_DataMapView)->nSendMsgBuferPos=sizeof(GlobalsMsgCtl);
	((PGlobalsMsgCtl)m_DataMapView)->nSendMsgLen=nInBufLen;
	((PGlobalsMsgCtl)m_DataMapView)->nRetMsgBuferPos=((PGlobalsMsgCtl)m_DataMapView)->nSendMsgBuferPos+nInBufLen;
	//BOOL nMutexRet=ReleaseMutex(m_DataMutex);

	ResetEvent(m_MsgEventComplate);
	SetEvent(m_SendMsgEvent);
	DWORD nObj=WaitForSingleObject(m_MsgEventComplate,nTimerWait);
	if(nObj==WAIT_TIMEOUT)
	{
		return FALSE;
	}
	if(nObj==WAIT_OBJECT_0)
	{
		if(pRetBuffer)
		{
			*pRetBuffer=((PGlobalsMsgCtl)m_DataMapView)->nRetMsgBuferPos+(char *)m_DataMapView;
			*nRetBufLen=((PGlobalsMsgCtl)m_DataMapView)->nRetMsgLen;
		}
		if(nRetFalg)
		{
			*nRetFalg=((PGlobalsMsgCtl)m_DataMapView)->nRetFalg;
		}
		
		ResetEvent(m_MsgEventComplate);
		
		return TRUE;
	}
	return FALSE;
}
//typedef void (WINAPI * fp_MsgCallBack)(IN unsigned int nCommand,IN void *pBuffer,IN unsigned int nBufLen,OUT void * pRetBuffer,OUT unsigned int * nRetBufLen,OUT unsigned int * nRetFalg );

DWORD __stdcall CGlobalsMsg::RecvThread(void *param)
{
	
	CGlobalsMsg * pCtl=(CGlobalsMsg *)param;
	HANDLE HandleArray[2];
	HandleArray[0]=pCtl->m_SendMsgEvent;
	HandleArray[1]=pCtl->m_CloseEvent;
	DWORD nWaitObj;
	//CThreadBase threadtool;
	for(;;)
	{
		nWaitObj=WaitForMultipleObjects(2,HandleArray,FALSE,INFINITE);
		switch(nWaitObj)
		{
		case WAIT_OBJECT_0:
			//ReleaseMutex(HandleArray[0]);
			//有消息
			{
				//WaitForSingleObject(pCtl->m_DataMutex,INFINITE);
				//消息处理函数
				pCtl->m_RecvCallBack(
					((PGlobalsMsgCtl)pCtl->m_DataMapView)->nContext,
					((PGlobalsMsgCtl)pCtl->m_DataMapView)->nCommand,
					((PGlobalsMsgCtl)pCtl->m_DataMapView)->nSendMsgBuferPos+(char *)pCtl->m_DataMapView,
					((PGlobalsMsgCtl)pCtl->m_DataMapView)->nSendMsgLen,
					((PGlobalsMsgCtl)pCtl->m_DataMapView)->nRetMsgBuferPos+(char *)pCtl->m_DataMapView,
					&((PGlobalsMsgCtl)pCtl->m_DataMapView)->nRetMsgLen,
					&((PGlobalsMsgCtl)pCtl->m_DataMapView)->nRetFalg
					);
				//BOOL nMutexRet=ReleaseMutex(pCtl->m_DataMutex);
				SetEvent(pCtl->m_MsgEventComplate);
			}
			break;
		case WAIT_OBJECT_0+1:
			//关闭
			return 0;
			break;
		default:
			break;
		}

	}
	
}

BOOL CGlobalsMsg::SetRecvMsgCallBack(fp_MsgCallBack pCall,unsigned int nContext)
{
	Log("CGlobalsMsg::SetRecvMsgCallBack CallFun=0x%08x,nContext=0x%08x",pCall,nContext);
	m_RecvCallBack=pCall;
	DWORD dwThreadID=0;
	if(m_bInit==FALSE)
	{
		return FALSE;
	}
	if(m_hRecvThread==NULL)
	{
		m_hRecvThread=CreateThread(NULL,0,RecvThread,this,0,&dwThreadID);
	}

	//创建关闭事件
	if(m_CloseEvent==NULL)
	{
		m_CloseEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	}
	((PGlobalsMsgCtl)m_DataMapView)->nContext=nContext;

	return TRUE;
}

//设置安全参数
/*
void CGlobalsMsg::SetSecurity()
{      
	BuildAlowingSD(&m_sMutexa,MUTEX_ALL_ACCESS,NULL);
	BuildAlowingSD(&m_sEventa,EVENT_ALL_ACCESS,NULL);
	BuildAlowingSD(&m_sMapa,FILE_MAP_ALL_ACCESS,NULL);
}*/




BOOL CGlobalsMsg::init(char * pMsgName)
{
	//"Global\\%s";
	char szBufferName[512];
	sprintf(szBufferName,"Global\\MAP_%s",pMsgName);
	if(m_bInit==TRUE)
	{
		return FALSE;
	}


	m_hRecvThread=NULL;
	m_RecvCallBack=NULL;
	m_bInit=FALSE;
	m_CloseEvent=NULL;
	m_SendMsgEvent=NULL;
	m_MsgEventComplate=NULL;
	
	m_DataMap=NULL;
	m_DataMutex=NULL;
	m_DataMapView=NULL;


	//创建进程共享内存
	//SetSecurity();
	BuildAlowingSD(&m_sMapa,FILE_MAP_ALL_ACCESS,szBufferName);
	if (m_DataMap==NULL)
	{
		m_DataMap=OpenFileMappingA(FILE_MAP_ALL_ACCESS,FALSE,szBufferName);
		DWORD nErr=GetLastError();
		if (NULL == m_DataMap)
		{
			m_DataMap=CreateFileMappingA(INVALID_HANDLE_VALUE,
				&m_sMapa,
				PAGE_READWRITE,
				0,
				4096*256,
				szBufferName);
		}
	}
	if (NULL == m_DataMap)
	{
		return FALSE;
	}
	//今天日志写详细点，包括硬件监管的方案描述，不然后面陆总有意见问题都不好说
	m_DataMapView=MapViewOfFile(m_DataMap,FILE_MAP_ALL_ACCESS,0,0,0);
	if (m_DataMapView==NULL)
	{
		CloseHandle(m_DataMap);
		m_DataMap=NULL;
		return FALSE;
	}

	SetLowIntegrity(szBufferName);

	//打开或者创建进程通讯用同步互斥
	sprintf(szBufferName,"Global\\MUTEX_%s",pMsgName);
	BuildAlowingSD(&m_sMutexa,MUTEX_ALL_ACCESS,szBufferName);
	if (NULL == m_DataMutex)
	{
		m_DataMutex = OpenMutexA(MUTEX_ALL_ACCESS,FALSE,szBufferName);
		if (NULL == m_DataMutex)
		{
			m_DataMutex = CreateMutexA(&m_sMutexa,FALSE,szBufferName);
			if (NULL == m_DataMutex)
			{
				return FALSE;
			}
		}
	}
	SetLowIntegrity(szBufferName);
	

	//初始换消息通知事件
	//m_=CreateEvent(NULL,TRUE,FALSE,NULL);
	sprintf(szBufferName,"Global\\EVENT_SEND_%s",pMsgName);
	BuildAlowingSD(&m_sEventa,EVENT_ALL_ACCESS,szBufferName);
	m_SendMsgEvent=OpenEventA(EVENT_ALL_ACCESS,FALSE,szBufferName);
	if (NULL == m_SendMsgEvent)
	{
		m_SendMsgEvent = CreateEventA(&m_sEventa,FALSE,FALSE,szBufferName);
		if (NULL == m_SendMsgEvent)
		{
			return FALSE;
		}
	}

	SetLowIntegrity(szBufferName);

	sprintf(szBufferName,"Global\\EVENT_SENDRET_%s",pMsgName);
	BuildAlowingSD(&m_sEventComplatea,EVENT_ALL_ACCESS,szBufferName);
	m_MsgEventComplate=OpenEventA(EVENT_ALL_ACCESS,FALSE,szBufferName);
	if (NULL == m_MsgEventComplate)
	{
		m_MsgEventComplate = CreateEventA(&m_sEventComplatea,FALSE,FALSE,szBufferName);
		if (NULL == m_MsgEventComplate)
		{
			return FALSE;
		}
	}
	SetLowIntegrity(szBufferName);

	m_bInit=TRUE;

	return TRUE;
}

