#pragma once

#include "ModuleInterface.h"


class CDebugFunctionInterface
{
public:
	CDebugFunctionInterface(){};
	~CDebugFunctionInterface(){};
	virtual BOOL Log( const char * szHead,const char * line,... )=0;
	virtual BOOL Log( const WCHAR * szHead,const WCHAR * line,... )=0;
protected:
	
private:
};


class CDebugFunctionModule :public CFunctionModuleBase,public CDebugFunctionInterface
{
public:
	CDebugFunctionModule(void);
	~CDebugFunctionModule(void);
	BOOL init(CModuleMgrInterface * pMgr);
	BOOL close();

	BOOL Log( const char * szHead,const char * line,... );
	BOOL Log( const WCHAR * szHead,const WCHAR * line,... );

};
