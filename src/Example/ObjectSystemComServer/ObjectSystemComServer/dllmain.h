// dllmain.h : 模块类的声明。

class CObjectSystemComServerModule : public CAtlDllModuleT< CObjectSystemComServerModule >
{
public :
	DECLARE_LIBID(LIBID_ObjectSystemComServerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_OBJECTSYSTEMCOMSERVER, "{C90051EB-BDB7-47A1-9673-3AD03BA1C8A0}")
};

extern class CObjectSystemComServerModule _AtlModule;
