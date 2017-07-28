// ShareObject.h: interface for the CShareObject class.
// 2006.4.16 叶树深，驱动应用层共享内存
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAREOBJECT_H__C92017ED_A2C3_4A72_B2E0_D64372816CB2__INCLUDED_)
#define AFX_SHAREOBJECT_H__C92017ED_A2C3_4A72_B2E0_D64372816CB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <aclapi.h>
#include "stdio.h"
#include <sddl.h>
#include <AccCtrl.h>
#include "..\TextIoSystem.h"
//std::vector
template<class _Type>
class CShareObject 
{
private:
	HANDLE m_DataMutex;		//映射操作互拆句柄
	LPVOID m_DataMapView;		//映射内存指针
	SECURITY_ATTRIBUTES m_sMapa;
	SECURITY_ATTRIBUTES m_sMutexa;
	BOOL m_bInit;
	HANDLE m_DataMap;
	BOOL m_bPrivate;
	TCHAR m_szPrefix[32];
	ErrorPrinter_OutputDebugString Error;

	

	typedef BOOL(__stdcall*fp_ConvertStringSecurityDescriptorToSecurityDescriptor)(WCHAR * StringSecurityDescriptor, DWORD StringSDRevision, PSECURITY_DESCRIPTOR* SecurityDescriptor, PULONG SecurityDescriptorSize);
	
	BOOL SetLowIntegrity(TCHAR *pObjName)
	{

#ifndef LOW_INTEGRITY_SDDL_SACL

#define LOW_INTEGRITY_SDDL_SACL L"S:(ML;;NW;;;LW)"


#endif // !LOW_INTEGRITY_SDDL_SACL

#ifndef LABEL_SECURITY_INFORMATION

#define LABEL_SECURITY_INFORMATION 0x00000010L

#endif // !LOW_INTEGRITY_SDDL_SACL

		DWORD dwErr = ERROR_SUCCESS;
		PSECURITY_DESCRIPTOR pSD = NULL;    
		PACL pSacl = NULL; // not allocated
		BOOL fSaclPresent = FALSE;
		BOOL fSaclDefaulted = FALSE;
		
		fp_ConvertStringSecurityDescriptorToSecurityDescriptor ConvertStringSecurityDescriptorToSecurityDescriptor;
		HMODULE hMod = LoadLibrary(_T("Advapi32.dll"));
		ConvertStringSecurityDescriptorToSecurityDescriptor = (fp_ConvertStringSecurityDescriptorToSecurityDescriptor)GetProcAddress(hMod, "ConvertStringSecurityDescriptorToSecurityDescriptorW");
		if (ConvertStringSecurityDescriptorToSecurityDescriptor != NULL) {
			if (ConvertStringSecurityDescriptorToSecurityDescriptor(LOW_INTEGRITY_SDDL_SACL, SDDL_REVISION_1, &pSD, NULL)) {
				if (GetSecurityDescriptorSacl(pSD, &fSaclPresent, &pSacl,&fSaclDefaulted)) {
					dwErr = SetNamedSecurityInfo(pObjName,SE_KERNEL_OBJECT, LABEL_SECURITY_INFORMATION,NULL, NULL, NULL, pSacl);
				}
				LocalFree(pSD);
				return TRUE;
			}
		}
		return FALSE;
	}

	//设置安全参数
	void SetMutexSecurity()
	{
		
		InitializeSecurityDescriptor(&m_sMutexa,SECURITY_DESCRIPTOR_REVISION);
		SetSecurityDescriptorDacl(&m_sMutexa,TRUE,NULL,FALSE);

		
		DWORD dwRes=0;
		PSID pEveryoneSID = NULL, pAdminSID = NULL;
		PACL pACL = NULL;
		PSECURITY_DESCRIPTOR pSD = NULL;
		EXPLICIT_ACCESS ea[2];
		SID_IDENTIFIER_AUTHORITY SIDAuthWorld =SECURITY_WORLD_SID_AUTHORITY;
		SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;
    
		// Create a well-known SID for the Everyone group.
		if(!AllocateAndInitializeSid(&SIDAuthWorld, 1,
    		SECURITY_WORLD_RID,
    		0, 0, 0, 0, 0, 0, 0,
    		&pEveryoneSID))
		{
        
			goto Cleanup;
		}
    
		// Initialize an EXPLICIT_ACCESS structure for an ACE.
		// The ACE will allow Everyone read access to the key.
		ZeroMemory(&ea, 2 * sizeof(EXPLICIT_ACCESS));
		ea[0].grfAccessPermissions = EVENT_ALL_ACCESS|MUTEX_ALL_ACCESS;
		ea[0].grfAccessMode = SET_ACCESS;
		ea[0].grfInheritance= NO_INHERITANCE;
		ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
		ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
		ea[0].Trustee.ptstrName  = (LPTSTR) pEveryoneSID;
    
    
		dwRes = SetEntriesInAcl(1, ea, NULL, &pACL);
		if (ERROR_SUCCESS != dwRes) 
		{
        
			goto Cleanup;
		}
    
		// Initialize a security descriptor.  
		pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, 
    		SECURITY_DESCRIPTOR_MIN_LENGTH); 
		if (NULL == pSD) 
		{ 
       
			goto Cleanup; 
		} 
    
		if (!InitializeSecurityDescriptor(pSD,
    		SECURITY_DESCRIPTOR_REVISION)) 
		{  
        
			goto Cleanup; 
		}

		// Add the ACL to the security descriptor. 
		if (!SetSecurityDescriptorDacl(pSD, 
    		TRUE,     // bDaclPresent flag   
    		pACL, 
    		FALSE))   // not a default DACL 
		{  
			goto Cleanup; 
		}
    

		m_sMutexa.nLength=sizeof(SECURITY_ATTRIBUTES);
		m_sMutexa.bInheritHandle = FALSE;
		m_sMutexa.lpSecurityDescriptor = pSD;

		return ;

		Cleanup:
    
		if (pEveryoneSID) 
			FreeSid(pEveryoneSID);
		if (pAdminSID) 
			FreeSid(pAdminSID);
		if (pACL) 
			LocalFree(pACL);
		if (pSD) 
			LocalFree(pSD);
        
	}

	TCHAR * GetVistaObjectName(TCHAR * pObjName)
	{
		TCHAR szUserName[MAX_PATH];
		BOOL bSystemProcess = FALSE;
		char * pRetName = pObjName;
		unsigned long nSize = 256;
		if (GetUserName(szUserName, &nSize))
		{
			if (stricmp_t("system", szUserName) == 0)
			{
				if (strstr_t(pObjName,_T("Global\\")))
				{
					pRetName = strchr_t(pObjName, '\\');
					if (pRetName)
					{
						pRetName++;
					}
				}
			}
		}
		else
		{
			return NULL;
		}

		Error(_T("GetVistaObjectName %s"), pRetName);
		return pRetName;

	}

	void SetMapSecurity()
	{
		//2009.12.1叶树深，修正对象访问属性
		DWORD dwRes=0;
		PSID pEveryoneSID = NULL, pAdminSID = NULL;
		PACL pACL = NULL;
		PSECURITY_DESCRIPTOR pSD = NULL;
		EXPLICIT_ACCESS ea[2];
		SID_IDENTIFIER_AUTHORITY SIDAuthWorld =SECURITY_WORLD_SID_AUTHORITY;
		SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;
		// Create a well-known SID for the Everyone group.
		if(!AllocateAndInitializeSid(&SIDAuthWorld, 1,
    		SECURITY_WORLD_RID,
    		0, 0, 0, 0, 0, 0, 0,
    		&pEveryoneSID))
		{
			goto Cleanup;
		}
    
		// Initialize an EXPLICIT_ACCESS structure for an ACE.
		// The ACE will allow Everyone read access to the key.
		ZeroMemory(&ea, 2 * sizeof(EXPLICIT_ACCESS));
		ea[0].grfAccessPermissions = FILE_MAP_ALL_ACCESS;
		ea[0].grfAccessMode = SET_ACCESS;
		ea[0].grfInheritance= NO_INHERITANCE;
		ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
		ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
		ea[0].Trustee.ptstrName  = (LPTSTR) pEveryoneSID;
    

		dwRes = SetEntriesInAcl(1, ea, NULL, &pACL);
		if (ERROR_SUCCESS != dwRes) 
		{
			goto Cleanup;
		}
    
		// Initialize a security descriptor.  
		pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, 
    		SECURITY_DESCRIPTOR_MIN_LENGTH); 
		if (NULL == pSD) 
		{ 
			goto Cleanup; 
		} 
    
		if (!InitializeSecurityDescriptor(pSD,
    		SECURITY_DESCRIPTOR_REVISION)) 
		{  
			goto Cleanup; 
		}

		// Add the ACL to the security descriptor. 
		if (!SetSecurityDescriptorDacl(pSD, 
    		TRUE,     // bDaclPresent flag   
    		pACL, 
    		FALSE))   // not a default DACL 
		{  
			goto Cleanup; 
		}
    

		m_sMapa.nLength=sizeof(SECURITY_ATTRIBUTES);
		m_sMapa.bInheritHandle = FALSE;
		m_sMapa.lpSecurityDescriptor = pSD;

		return ;

		Cleanup:
    
		if (pEveryoneSID) 
			FreeSid(pEveryoneSID);
		if (pAdminSID) 
			FreeSid(pAdminSID);
		if (pACL) 
			LocalFree(pACL);
		if (pSD) 
			LocalFree(pSD);
	}

	
public:

	BOOL EnableDebugPrivilege(BOOL bEnableDebugPrivilege)
	{
		HANDLE hToken;
		TOKEN_PRIVILEGES tp;
		LUID luid;
		UINT	nErrorPos = 0;
		DWORD	nError = 0;
		do
		{
			if (!::OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
			{
				nErrorPos = 1;
				nError = GetLastError();
				break;
			}

			if (!::LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
			{
				nErrorPos = 2;
				nError = GetLastError();
				::CloseHandle(hToken);
				break;
			}

			tp.PrivilegeCount = 1;
			tp.Privileges[0].Luid = luid;
			if (bEnableDebugPrivilege)
			{
				tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			}
			else
			{
				tp.Privileges[0].Attributes = 0;
			}

			if (!::AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL))
			{
				nErrorPos = 3;
				nError = GetLastError();
				::CloseHandle(hToken);
				break;
			}

			::CloseHandle(hToken);

			nError = GetLastError();
			if (::GetLastError() == ERROR_NOT_ALL_ASSIGNED)
			{
				nErrorPos = 4;

				break;
			}
			return TRUE;
		} while (TRUE);
		//gLockDeviceMsgQueue.Error(_T("EnableDebugPrivilege %d errpos=%d err=%d"), bEnableDebugPrivilege, nErrorPos, nError);
		return FALSE;
	}

	BOOL initWin7(TCHAR * pObjectName)
	{
		TCHAR szBufferName[MAX_PATH];
		BOOL bOpen = TRUE;
		sprintf_s_t(szBufferName, MAX_PATH, _T("%sMAP_%s"), m_szPrefix, pObjectName);
		if(m_bInit==TRUE)
		{
			return FALSE;
		}
		 
		m_DataMap=NULL;
		m_DataMutex=NULL;
		m_DataMapView=NULL;
		
		
		//创建进程共享内存
		SetMapSecurity();
		SetMutexSecurity();
		if (m_DataMap==NULL)
		{
			m_DataMap=OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,szBufferName);
			DWORD nErr=::GetLastError();
			if (NULL == m_DataMap)
			{
				bOpen = FALSE;
				m_DataMap=CreateFileMapping(INVALID_HANDLE_VALUE,
					&m_sMapa,
					PAGE_READWRITE,
					0,
					((sizeof(_Type)/4096)+1*4096),
					szBufferName);
				if (m_DataMap == NULL)
				{
					m_DataMap = NULL;
					DWORD nErr = ::GetLastError();
					//char szLog[512];
					Error(_T("CreateFileMapping %s Fail err=%d..."), szBufferName,nErr);
					return FALSE;
				}

				m_DataMapView=MapViewOfFile(m_DataMap,FILE_MAP_ALL_ACCESS,0,0,0);
				
				memset(m_DataMapView,0,sizeof(_Type));
				
			}
		}
		if (NULL == m_DataMap)
		{
			return FALSE;
		}

		if (m_DataMapView==NULL)
		{
			m_DataMapView=MapViewOfFile(m_DataMap,FILE_MAP_ALL_ACCESS,0,0,0);
			if (m_DataMapView==NULL)
			{
				CloseHandle(m_DataMap);
				m_DataMap=NULL;
				return FALSE;
			}
		}
		
		Error(_T("initWin7 %s obj=%s  Ok"), pObjectName, (bOpen == TRUE ? _T("OpenFileMapping") : _T("CreateFileMapping")));

		SetLowIntegrity(szBufferName);
		
		//打开或者创建进程通讯用同步互斥
		sprintf_s_t(szBufferName, MAX_PATH, _T("%sMUTEX_%s"), m_szPrefix, pObjectName);
		if (NULL == m_DataMutex)
		{
			m_DataMutex = OpenMutex(MUTEX_ALL_ACCESS,FALSE,szBufferName);
			if (NULL == m_DataMutex)
			{
				bOpen = FALSE;
				m_DataMutex = CreateMutex(&m_sMutexa,FALSE,szBufferName);
				if (NULL == m_DataMutex)
				{ 
					Error(_T("CreateMutex %s Fail..."), szBufferName); 
					return FALSE;
				}
			}
		}
		SetLowIntegrity(szBufferName);

		Error(_T("initWin7 %s obj=%s  Ok"), pObjectName, (bOpen == TRUE ? _T("OpenMutex") : _T("CreateMutex")));
		
		
		m_bInit=TRUE;
		Error(_T("initWin7 obj=%s ok"), pObjectName);

		
		return TRUE;
	}
	

	BOOL initWin10(char * pObjectName)
	{
		m_DataMap = NULL;
		m_DataMutex = NULL;
		m_DataMapView = NULL;
		char szBufferName[512];
		sprintf_s(szBufferName,512, "Global\\MAP_%s", pObjectName);
		EnableDebugPrivilege(TRUE);
		if (m_bInit == TRUE)
		{
			return FALSE;
		}

		if (m_DataMap == NULL)
		{
			
			m_DataMap = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, szBufferName);
			DWORD nErr = ::GetLastError();
			if (NULL == m_DataMap)
			{
				//
				m_DataMap = CreateFileMappingW(INVALID_HANDLE_VALUE,
					NULL,
					PAGE_READWRITE,
					0,
					((sizeof(_Type) / 4096) + 1 * 4096),
					//L"BaseNamedObjects\\MAP_Test");
					L"Local\\MAP_Test");/*Global*/
				DWORD nErr = GetLastError();

				m_DataMapView = MapViewOfFile(m_DataMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
				if (m_DataMapView == NULL)
				{
					CloseHandle(m_DataMap);
					m_DataMap = NULL;
					return FALSE;
				}
				memset(m_DataMapView, 0, sizeof(_Type));

			}
		}
	}

	BOOL init(TCHAR * pObjectName, BOOL bPrivate = FALSE, BOOL bGlobal=FALSE)
	{

		m_bPrivate = bPrivate;
		if (bPrivate)
		{
			sprintf_s_t(m_szPrefix, 32, _T("Private_%u_"), ::GetCurrentProcessId());
		}
		else
		{
			if (bGlobal)
			{
				strcpy_s_t(&m_szPrefix[0], 32, _T("Global\\"));
			}
			else
			{
				strcpy_s_t(&m_szPrefix[0], 32, _T("Local\\"));
			}

		}
		OSVERSIONINFO osvi;

		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

		if (!GetVersionEx(&osvi))
		{
			OutputDebugStringA("CShareObject get system version failed");
			return FALSE;
		}

		Error(_T("CShareObject init osver=%d %d"), osvi.dwMajorVersion, osvi.dwMinorVersion);

		return initWin7(pObjectName);
	}



	BOOL Lock()
	{
		if(m_DataMutex)
		{
			WaitForSingleObject(m_DataMutex,INFINITE);
			return TRUE;
		}
		return FALSE;
	}
	BOOL UnLock()
	{
		if(m_DataMutex)
		{
			ReleaseMutex(m_DataMutex);
			return TRUE;
		}
		return FALSE;
	}
	
	_Type& operator*() const
	{
		return &(*((_Type*)m_DataMapView)); 
	}
	
	_Type * operator->() const
	{
		return ((_Type*)m_DataMapView); 
	}

	operator _Type *()
	{
		return ((_Type*)m_DataMapView); 
	}
	CShareObject()
	{
		m_DataMap=NULL;
		m_DataMutex=NULL;
		m_DataMapView=NULL;
		m_bPrivate = TRUE;
	};
	BOOL IsValid()
	{
		return (m_DataMap == NULL) ? FALSE : TRUE;
	}
	virtual ~CShareObject()
	{
	
		
		if(m_DataMutex)
		{
			CloseHandle(m_DataMutex);
		}
		
		if(m_DataMap)
		{
			CloseHandle(m_DataMap);
		}
	};


};

#endif // !defined(AFX_SHAREOBJECT_H__C92017ED_A2C3_4A72_B2E0_D64372816CB2__INCLUDED_)
