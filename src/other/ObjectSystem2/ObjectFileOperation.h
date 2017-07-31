///////////////////////////////////////////////////////////////////////////////////
//	Copyright 2017 shushen,ye
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//	http://www.apache.org/licenses/LICENSE-2.0
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
///////////////////////////////////////////////////////////////////////////////////

#pragma once

class CObjectFileOperation_Nop
{
public:
	CObjectFileOperation_Nop(void) {};
	~CObjectFileOperation_Nop(void) {};
	HANDLE m_hObject;
	BOOL OpenObjectFile(tstring & szDirPath, BOOL bClear) { return TRUE; };
	BOOL ReadObject(OUT tstring & szObject) { return TRUE; };
	BOOL WriteObject(IN tstring & szObject) { return TRUE; };
	BOOL DelObjectOrDir(tstring & szDirPath) { return TRUE; };
	BOOL CloseObject() { return TRUE; };

	BOOL ClearFile(tstring & szObjectPath) { return TRUE; };
	BOOL OpenObjectFile_OnlyOpen(tstring & szObject) { return FALSE; };

	static BOOL GetDirectoryInfo(IN tstring & DirectoryPath, IN tstring & szFinder, OUT ObjectSystem::_tagDirectoryInfo & DirectoryInfo, OUT ObjectSystem::SYSTEMERROR * pError) { return TRUE; };


};

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

	static BOOL GetDirectoryInfo(IN tstring & DirectoryPath, IN tstring & szFinder, OUT ObjectSystem::_tagDirectoryInfo & DirectoryInfo, OUT ObjectSystem::SYSTEMERROR * pError);

private:
	BOOL RemoveDir(tstring & szFileDir);

	BOOL GetObjectDirPath(IN tstring & szObjectPath,OUT tstring & szDirPath);

	BOOL FolderExist(tstring & szDirPath);
	

	BOOL CreatedObjectMultipleDirectory( tstring & szObjectPath);

	

};
