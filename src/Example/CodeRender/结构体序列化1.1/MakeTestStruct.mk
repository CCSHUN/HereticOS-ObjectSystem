MAKEINCLUDE="E:\\白盒测试\\me\\CodeRender\\结构体序列化1.1\\structtree.mk"
MAKEINCLUDE="E:\\白盒测试\\me\\CodeRender\\结构体序列化1.1\\结构预处理语法树.mk"
MAKEINCLUDE="E:\\白盒测试\\me\\CodeRender\\结构体序列化1.1\\结构预处理MAKE.mk"

ROOT<代码>=结构声明|预处理命令


MAKE_HPP<MAKE>=MAKE_TO<MAKE_HPP_CPP,接口类生成路径>
接口类生成路径<MAKE>=生成文件基目录#WORD("StructInfo_")#类生成H文件名


//定制元素名
	//COM HOOK 包容类名
	主Cpp文件<MAKE>=生成文件基目录#MAKE_COMHOOK包容类名#WORD(".cpp")
	MAKE_COMHOOK包容类名<MAKE>=WORD("ComHookPacketBase")
	生成文件基目录<MAKE>=WORD("E:\\白盒测试\\svn\\project\\project_AutoEvaluate\\AutoEvaluate\\AutoEvaluate\\ObjectSerDef\\")	
	类生成名<MAKE>=类生成名1|类生成名2
	类生成名1<MAKE>=结构声明.结构声明1.结构体名
	类生成名2<MAKE>=结构声明.结构声明2.结构体名
	
	类生成CPP文件名<MAKE>=类生成名#WORD(".cpp")
	类生成H文件名<MAKE>=类生成名#WORD(".h")
	COMHOOK类声明文件名<MAKE>=MAKE_COMHOOK包容类名#WORD(".h")
	COMHOOK类声明生成路径<MAKE>=生成文件基目录#COMHOOK类声明文件名
	
	预编译包含文件代码<MAKE>=WORD("\r\n#include \"stdafx.h\"\r\n\r\n")
	
	
	
ROOT_MAKE<ROOT_MAKE>=MAKE_HPP_CPP

