#pragma once

class CObjectFileOperation
{
public:
	CObjectFileOperation(void);
	~CObjectFileOperation(void);
	HANDLE m_hObject;
	BOOL OpenObjectFile(tstring & szDirPath,BOOL bClear);
	BOOL ReadObject(OUT tstring & szObject);
	BOOL WriteObject(IN tstring & szObject);
	BOOL DelObjectOrDir(tstring & szDirPath);
	BOOL CloseObject();

	BOOL ClearFile(tstring & szObjectPath);
	BOOL OpenObjectFile_OnlyOpen(tstring & szObject);

	
private:
	BOOL RemoveDir(tstring & szFileDir);

	BOOL GetObjectDirPath(IN tstring & szObjectPath,OUT tstring & szDirPath);

	BOOL FolderExist(tstring & szDirPath);
	

	BOOL CreatedObjectMultipleDirectory( tstring & szObjectPath);

	

};
