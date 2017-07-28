#include "stdafx.h"
#include "ObjectFileOperation.h"
#include "shellapi.h"
CObjectFileOperation::CObjectFileOperation(void)
{
	m_hObject=NULL;
}

CObjectFileOperation::~CObjectFileOperation(void)
{
	CloseObject();
}


BOOL CObjectFileOperation::ClearFile(tstring & szObjectPath)
{
	FILE_ALLOCATION_INFO filesize;
	filesize.AllocationSize.QuadPart=0;
	//::SetFileInformationByHandle(m_hObject,FileAllocationInfo,&filesize,sizeof(FILE_ALLOCATION_INFO));
	CloseObject();
	m_hObject=CreateFile(szObjectPath.c_str(),
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		0,
		TRUNCATE_EXISTING,
		FILE_ATTRIBUTE_NORMAL,0);
	return TRUE;
}

BOOL CObjectFileOperation::OpenObjectFile_OnlyOpen(tstring & szObject)
{

	//�򿪴����ļ�
	m_hObject=CreateFile(szObject.c_str(),
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,0);
	/*DWORD nError=GetLastError();
	if(nError==ERROR_FILE_NOT_FOUND )
	{
		m_hObject=CreateFile(szObject.c_str(),
			GENERIC_READ|GENERIC_WRITE,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			0,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,0);
	}*/

	if(m_hObject==INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	return TRUE;
}
BOOL CObjectFileOperation::OpenObjectFile(tstring & szObject,BOOL bClear)
{
	
	//�򿪴����ļ�
	m_hObject=CreateFile(szObject.c_str(),
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		0,
		bClear ? TRUNCATE_EXISTING:OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,0);
	DWORD nError=GetLastError();
	if(nError==ERROR_FILE_NOT_FOUND )
	{
		m_hObject=CreateFile(szObject.c_str(),
			GENERIC_READ|GENERIC_WRITE,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			0,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,0);
	}
	if(m_hObject==INVALID_HANDLE_VALUE)
	{
		if(CreatedObjectMultipleDirectory( szObject ))
		{
			//����Ŀ¼�ɹ�
			m_hObject=CreateFile(szObject.c_str(),
				GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ|FILE_SHARE_WRITE,
				0,OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,0);
			if(m_hObject==INVALID_HANDLE_VALUE)
			{
				//
				//OutputDebugString(_T());
				return FALSE;
			}else
			{
				return TRUE;
			}
		}
	}else
	{
		return TRUE;
	}
	//���ʧ�ܴ���Ŀ¼

	//�򿪴����ļ�
	return FALSE;
}
BOOL CObjectFileOperation::ReadObject(OUT tstring & szObject)
{
	DWORD nLen=GetFileSize(m_hObject,NULL);
	BYTE * pBuf=new BYTE[nLen+64];
	pBuf[nLen]=0;pBuf[nLen+1]=0;
	std::auto_ptr<BYTE> mem(pBuf);
	BOOL bRet=ReadFile(m_hObject,pBuf,nLen,&nLen,NULL);
	if(bRet)
	{
		szObject=(TCHAR*)pBuf;
	}

	return bRet;
}

BOOL CObjectFileOperation::WriteObject(IN tstring & szObject)
{
	DWORD nLen;
	SetFilePointer(m_hObject,0,0,FILE_BEGIN);
	BOOL bRet=WriteFile(m_hObject,szObject.c_str(),(szObject.length()+1)*sizeof(TCHAR),&nLen,NULL);
	return TRUE;
}
BOOL CObjectFileOperation::CloseObject()
{
	::CloseHandle(m_hObject);
	return TRUE;
}

BOOL CObjectFileOperation::GetObjectDirPath(IN tstring & szObjectPath,OUT tstring & szDirPath)
{
	size_t n=szObjectPath.rfind('\\');
	if(n==0) return FALSE;

	szDirPath.append(szObjectPath.c_str(),n);
	return TRUE;
}

BOOL CObjectFileOperation::FolderExist(tstring & szDirPath)
{
	WIN32_FIND_DATA wfd;
	BOOL rValue = FALSE;
	HANDLE hFind = FindFirstFile(szDirPath.c_str(), &wfd);
	if ((hFind!=INVALID_HANDLE_VALUE) &&
		(wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
	{
		rValue = TRUE;
	}
	FindClose(hFind);
	return rValue;
}

BOOL CObjectFileOperation::RemoveDir(tstring & szFileDir)
{
	tstring strDir = szFileDir;
	if (strDir.at(strDir.length()-1) != '\\')
	{
		strDir += '\\';
	}
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile((strDir + _T("*.*")).c_str(),&wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return false;
	do
	{
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (stricmp_t(wfd.cFileName,_T(".")) != 0 &&
				stricmp_t(wfd.cFileName,_T("..")) != 0)
				RemoveDir( (strDir + wfd.cFileName));
		}
		else
		{
			DeleteFile( (strDir + wfd.cFileName).c_str());
		}
	}
	while (FindNextFile(hFind,&wfd));
	FindClose(hFind);
	RemoveDirectory(szFileDir.c_str());
	return true;
}


BOOL CObjectFileOperation::DelObjectOrDir(tstring & szDirPath)
{
	if(m_hObject)
	{
		CloseHandle(m_hObject);
		m_hObject=NULL;
	}
	
	if(DeleteFile(szDirPath.c_str())==FALSE)
	{
		RemoveDir(szDirPath);
		/*SHFILEOPSTRUCT FileOp;
		FileOp.fFlags = FOF_NOCONFIRMATION;
		FileOp.hNameMappings = NULL;
		FileOp.hwnd = NULL;
		FileOp.lpszProgressTitle = NULL;
		FileOp.pFrom = szDirPath.c_str();
		FileOp.pTo = NULL;
		FileOp.wFunc = FO_DELETE;
		return SHFileOperation(&FileOp) == 0;*/
	}
	return TRUE;
}

BOOL CObjectFileOperation::CreatedObjectMultipleDirectory( tstring & szObjectPath)
{
	tstring Directoryname = szObjectPath;

	if (  Directoryname[Directoryname.length() - 1] !=  '\\' )
	{
		//Directoryname += 
		Directoryname.append( 1, '\\');
	}
	std::list<tstring> vpath;
	tstring strtemp;
	bool  bSuccess = false;
	for ( unsigned int i = 0; i < Directoryname.length(); i++ )
	{
		if ( Directoryname[i] != '\\')
		{
			strtemp.append( 1,Directoryname[i] );    
		}
		else
		{
			vpath.push_back( strtemp );
			strtemp.append( 1, '\\' );
		}
	}

	vpath.pop_back();

	std::list<tstring>:: const_iterator vIterDepth;

	for ( vIterDepth = vpath.begin();vIterDepth != vpath.end(); vIterDepth++ )
	{
		bSuccess = CreateDirectory( vIterDepth->c_str(), NULL ) ? true :false;
	}

	return bSuccess; 
}