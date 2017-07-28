// ThreadBaseForWin32App.cpp: implementation of the CThreadBaseForWin32App class.
//2006.4.16 叶树深，驱动应用层共享内存
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <aclapi.h>

#include <sddl.h>
#include <AccCtrl.h>
#include "ThreadBaseForWin32App.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThreadBaseForWin32App::CThreadBaseForWin32App()
{

}

CThreadBaseForWin32App::~CThreadBaseForWin32App()
{

} 

BOOL CThreadBaseForWin32App::Log( const char * line,...)
{
		
		char cpBuf[1024];	
		char  AppName[260];
		GetModuleFileNameA(NULL,AppName,256);
		char * pName=strrchr(AppName,'\\');
		if(pName)
		{
			pName++;
		}
		memset(cpBuf,0,sizeof(cpBuf));
		sprintf(cpBuf,"[==%s==]:",pName);
		va_list	vl;
		va_start( vl, line );
		vsprintf(cpBuf+strlen(cpBuf), line, vl );
		va_end( vl);
		strcat(cpBuf,"\n");
		OutputDebugStringA(cpBuf);
		
		return TRUE;
}

BOOL CThreadBaseForWin32App::BuildAlowingSD(SECURITY_ATTRIBUTES *pObjectAttributes,ACCESS_MASK AccessMask,void * pObjName)
{
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
    ea[0].grfAccessPermissions = AccessMask;
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
    
	
	pObjectAttributes->nLength=sizeof(SECURITY_ATTRIBUTES);
	pObjectAttributes->bInheritHandle = FALSE;
	pObjectAttributes->lpSecurityDescriptor = pSD;
	
	return TRUE;
	
Cleanup:
    
    if (pEveryoneSID) 
        FreeSid(pEveryoneSID);
    if (pAdminSID) 
        FreeSid(pAdminSID);
    if (pACL) 
        LocalFree(pACL);
    if (pSD) 
        LocalFree(pSD);

	return FALSE;
}
typedef BOOL(__stdcall*fp_ConvertStringSecurityDescriptorToSecurityDescriptor)(LPCSTR StringSecurityDescriptor, DWORD StringSDRevision, PSECURITY_DESCRIPTOR* SecurityDescriptor, PULONG SecurityDescriptorSize);

BOOL CThreadBaseForWin32App::SetLowIntegrity(char *pObjName)
{
#if (SYSTEMOP==SYS_APP)
#define LOW_INTEGRITY_SDDL_SACL "S:(ML;;NW;;;LW)"
#define LABEL_SECURITY_INFORMATION 0x00000010L
	DWORD dwErr = ERROR_SUCCESS;
	PSECURITY_DESCRIPTOR pSD = NULL;    
	PACL pSacl = NULL; // not allocated
	BOOL fSaclPresent = FALSE;
	BOOL fSaclDefaulted = FALSE;
	
	fp_ConvertStringSecurityDescriptorToSecurityDescriptor ConvertStringSecurityDescriptorToSecurityDescriptor;
	HMODULE hMod = LoadLibraryA("Advapi32.dll");
	ConvertStringSecurityDescriptorToSecurityDescriptor = (fp_ConvertStringSecurityDescriptorToSecurityDescriptor)GetProcAddress(hMod, "ConvertStringSecurityDescriptorToSecurityDescriptorA");
	if (ConvertStringSecurityDescriptorToSecurityDescriptor != NULL) {
		if (ConvertStringSecurityDescriptorToSecurityDescriptor(LOW_INTEGRITY_SDDL_SACL, SDDL_REVISION_1, &pSD, NULL)) {
			if (GetSecurityDescriptorSacl(pSD, &fSaclPresent, &pSacl,&fSaclDefaulted)) {
				dwErr = SetNamedSecurityInfoA(pObjName,SE_KERNEL_OBJECT, LABEL_SECURITY_INFORMATION,NULL, NULL, NULL, pSacl);
			}
			LocalFree(pSD);
			return TRUE;
		}
	}
	return FALSE;
#endif
	return FALSE;
}


