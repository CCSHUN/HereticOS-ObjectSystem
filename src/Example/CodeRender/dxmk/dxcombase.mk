	MAKEINCLUDE="c:\\dx89codetree.mk"
	
	//MAKE DX COM基本合成库
	MAKE_Def空参数名do<MAKE>=WORD("NodefName")
	MAKE_Def空参数名MAKE<MAKE>=WORD("MAKE_Def空参数名do<MAKE>=WORD(\"")#MAKE_Def空参数名do#WORD("1\")")
	MAKE_Def空参数名<MAKE>=MAKE_Def空参数名do&MAKE_ADD<MAKE_Def空参数名MAKE>
	//MAKE_Def空参数名每引用一次就加1，可以用复位重新将其设置为默认值
	MAKE_置位Def空参数名MAKE<MAKE>=WORD("MAKE_Def空参数名do<MAKE>=WORD(\"NodefName\")")
	MAKE_置位Def空参数名<MAKE>=MAKE_ADD<MAKE_置位Def空参数名MAKE>
	
	MAKE_空参数名称<MAKE>=O.参数名称.空参数名称#MAKE_Def空参数名
	MAKE_参数名称<MAKE>=MAKE_空参数名称|O.参数名称
	MAKE_函数参数表1<MAKE>=参数类型.引用型参数+MAKE_参数名称
	MAKE_函数参数表2<MAKE>=参数类型.对象型参数+MAKE_参数名称
	MAKE_函数参数表3<MAKE>=参数类型.指针型参数+MAKE_参数名称
	MAKE_函数参数表4<MAKE>=参数类型.指针指针型参数+MAKE_参数名称
	
	MAKE_函数参数表11<MAKE>=参数类型.CONST引用型参数+MAKE_参数名称
	MAKE_函数参数表21<MAKE>=参数类型.CONST对象型参数+MAKE_参数名称
	MAKE_函数参数表31<MAKE>=参数类型.CONST指针型参数+MAKE_参数名称
	MAKE_函数参数表41<MAKE>=参数类型.CONST指针指针型参数+MAKE_参数名称
	
	
	MAKE_函数参数表7<MAKE>=MAKE_函数参数表1|MAKE_函数参数表2|MAKE_函数参数表3|MAKE_函数参数表4|MAKE_函数参数表11|MAKE_函数参数表21|MAKE_函数参数表31|MAKE_函数参数表41
	MAKE_函数参数表8<MAKE>=WORD(,)+MAKE_函数参数表1|MAKE_函数参数表2|MAKE_函数参数表3|MAKE_函数参数表4|MAKE_函数参数表11|MAKE_函数参数表21|MAKE_函数参数表31|MAKE_函数参数表41
	MAKE_函数ROOT<MAKE>=类声明.类声明1.类声明体.类声明体内容.类声明体内容5.函数声明
	MAKE_函数ROOT1<MAKE>=类声明.类声明1.类声明体.类声明体内容.类声明体内容5.函数声明.函数声明1
	MAKE_函数ROOT2<MAKE>=类声明.类声明1.类声明体.类声明体内容.类声明体内容5.函数声明.函数声明2
	
	MAKE_函数ROOT1_MAKE<MAKE>=WORD("类声明.类声明1.类声明体.类声明体内容.类声明体内容5.函数声明.函数声明1")
	MAKE_函数ROOT2_MAKE<MAKE>=WORD("类声明.类声明1.类声明体.类声明体内容.类声明体内容5.函数声明.函数声明2")
	
	MAKE_函数参数表ROOT<MAKE>=函数参数声明.函数声明参数表.函数声明参数声明
	MAKE_接口类ROOT<MAKE>=ROOTROOT.ROOT
	
	//函数声明
	MAKE_函数参数表<MAKE>=MAKE_置位Def空参数名&MAKE_N<MAKE_函数参数表ROOT,MAKE_函数参数表7,MAKE_函数参数表8,MAKE_函数参数表8>
	MAKE_函数1<MAKE>=WORD("HRESULT STDMETHODCALLTYPE")&O.函数名#WORD(()&MAKE_函数参数表&WORD())#WORD(;)#WORD("\r\n")
	MAKE_函数2<MAKE>=MAKE_函数2返回参数&WORD("STDMETHODCALLTYPE")&O.函数名#WORD(()&MAKE_函数参数表&WORD())#WORD(;)#WORD("\r\n")
	MAKE_函数2返回参数<MAKE>=O.函数返回类型.参数类型.引用型参数|O.函数返回类型.参数类型.指针型参数|O.函数返回类型.参数类型.对象型参数|O.函数返回类型.参数类型.指针指针型参数
	MAKE_函数22<MAKE>=NOT<MAKE_不需要的函数>|MAKE_函数2
	MAKE_函数11<MAKE>=NOT<MAKE_不需要的函数>|MAKE_函数1
		
	//函数调用
	MAKE_函数调用参数表1<MAKE>=MAKE_参数名称
	MAKE_函数调用参数表2<MAKE>=WORD(,)+MAKE_参数名称
	MAKE_函数调用参数表<MAKE>=MAKE_置位Def空参数名&MAKE_N<MAKE_函数参数表ROOT,MAKE_函数调用参数表1,MAKE_函数调用参数表2,MAKE_函数调用参数表2>
	MAKE_函数调用<MAKE>=O.函数名#WORD(()&MAKE_函数调用参数表&WORD())



	
	//不需要关注的函数
	MAKE_不需要的函数1<MAKE>=函数名.AddRef|函数名.Release|函数名.QueryInterface
	MAKE_不需要的函数<MAKE>=IF<MAKE_不需要的函数1>
	
	//函数定义头
	MAKE_函数定义类名ROOT<MAKE>=PARENT.PARENT.PARENT.PARENT.PARENT.类名
	MAKE_函数定义头1<MAKE>=WORD(HRESULT)&MAKE_函数定义类名ROOT#WORD("::")#O.函数名#WORD(()&MAKE_函数参数表&WORD())#WORD("\r\n")
	MAKE_函数定义头2<MAKE>=MAKE_函数2返回参数&MAKE_函数定义类名ROOT#WORD("::")#O.函数名#WORD(()&MAKE_函数参数表&WORD())#WORD("\r\n")
	MAKE_函数定义头22<MAKE>=MAKE_不需要的函数|MAKE_函数定义头2
	MAKE_函数定义头11<MAKE>=MAKE_不需要的函数|MAKE_函数定义头1		

	
	
	
	//函数定义

	MAKE类声明函数声明<MAKE>=MAKE_N<MAKE_函数ROOT2,MAKE_函数22,MAKE_函数22,MAKE_函数22>&MAKE_N<MAKE_函数ROOT1,MAKE_函数11,MAKE_函数11,MAKE_函数11>
	MAKE类声明函数调用<MAKE>=MAKE_N<MAKE_函数ROOT2,MAKE_函数调用22,MAKE_函数调用22,MAKE_函数调用22>&MAKE_N<MAKE_函数ROOT1,MAKE_函数调用11,MAKE_函数调用11,MAKE_函数调用11>
	
	MAKE类声明函数定义头1<MAKE>=MAKE_N<MAKE_函数ROOT2,MAKE_函数定义头22,MAKE_函数定义头22,MAKE_函数定义头22>&MAKE_N<MAKE_函数ROOT1,MAKE_函数定义头11,MAKE_函数定义头11,MAKE_函数定义头11>
	MAKE类声明函数定义头<MAKE>=MAKE_TO<MAKE类声明函数定义头1,类生成路径>
	
	MAKE类声明<MAKE>=MAKE_N<MAKE_接口类ROOT,MAKE类声明函数定义头,MAKE类声明函数定义头,MAKE类声明函数定义头>

	//make 包容基类 各个接口cpp文件
		//COM HOOK函数包容体
		MAKE_函数定义头1<MAKE>=WORD(HRESULT)&MAKE_COMHOOK包容类名#WORD("::")#O.函数名#WORD(()&MAKE_函数参数表&WORD())#WORD("\r\n")
		MAKE_函数定义头2<MAKE>=MAKE_函数2返回参数&MAKE_COMHOOK包容类名#WORD("::")#O.函数名#WORD(()&MAKE_函数参数表&WORD())#WORD("\r\n")
	
		MAKE_原始接口对象<MAKE>=WORD("m_p")#MAKE_函数定义类名ROOT
		MAKE_继承所属类原始接口对象<MAKE>=WORD("m_p")#MAKE_当前类名
		MAKE_COMHOOKPACKET函数定义1<MAKE>=WORD("\r\n")#MAKE_函数定义头1#WORD("{\r\n\t return ")+MAKE_原始接口对象#WORD("->")#MAKE_函数调用+WORD(";\r\n}\r\n")
		MAKE_COMHOOKPACKET函数定义2<MAKE>=WORD("\r\n")#MAKE_函数定义头2#WORD("{\r\n\t return ")+MAKE_原始接口对象#WORD("->")#MAKE_函数调用+WORD(";\r\n}\r\n")
		
		MAKE_COMHOOKPACKET函数定义11<MAKE>=MAKE_不需要的函数|MAKE_COMHOOKPACKET函数定义1
		MAKE_COMHOOKPACKET函数定义22<MAKE>=MAKE_不需要的函数|MAKE_COMHOOKPACKET函数定义2
		
		
		
		//make 所有接口所属函数
		MAKE_COMHOOKCPP1<MAKE>=MAKE_N<MAKE_函数ROOT2,MAKE_COMHOOKPACKET函数定义22,MAKE_COMHOOKPACKET函数定义22,MAKE_COMHOOKPACKET函数定义22>&MAKE_N<MAKE_函数ROOT1,MAKE_COMHOOKPACKET函数定义11,MAKE_COMHOOKPACKET函数定义11,MAKE_COMHOOKPACKET函数定义11>
		MAKE_COMHOOKCPP11<MAKE>=WORD("\r\n#include \"")#COMHOOK类声明文件名#WORD("\"\r\n\r\n")+MAKE_COMHOOKCPP1
		MAKE_COMHOOKCPP2<MAKE>=MAKE_TO<MAKE_COMHOOKCPP11,包容基类类生成路径>
		//make 所有接口
		MAKE_COMHOOKCPP3<MAKE>=MAKE_N<MAKE_接口类ROOT,MAKE_COMHOOKCPP2,MAKE_COMHOOKCPP2,MAKE_COMHOOKCPP2>
	
	//make COM HOOK 包容基类头文件
		
		MAKE_原始接口对象类型<MAKE>=类声明.类声明1.类名
	
		//make COM HOOK 声明头尾
		MAKE_原始接口继承对象类型1<MAKE>=WORD("\t\t\t: public")+接口类名#WORD("<")#MAKE_COMHOOK包容类名#WORD(">\r\n")
		MAKE_原始接口继承对象类型2<MAKE>=WORD("\t\t\t, public")+接口类名#WORD("<")#MAKE_COMHOOK包容类名#WORD(">\r\n")
		MAKE_继承参数表<MAKE>=MAKE_N<MAKE_接口类ROOT,MAKE_原始接口继承对象类型2,MAKE_原始接口继承对象类型2,MAKE_原始接口继承对象类型2>
		
		MAKE_包含包容接口头文件<MAKE>=WORD("\r\n#include \"")#接口类名#WORD(".h\"\r\n")
		MAKE_包含包容接口头文件表<MAKE>=MAKE_N<MAKE_接口类ROOT,MAKE_包含包容接口头文件,MAKE_包含包容接口头文件,MAKE_包含包容接口头文件>
		
		
		MAKE_COMHOOKHPP头<MAKE>=WORD("\r\n#pragma once\r\n\r\n")#MAKE_包含包容接口头文件表#WORD("\r\n\r\nclass ")+MAKE_COMHOOK包容类名+WORD("\r\n")+WORD("\t\t\t: public KcgComHook\r\n")#MAKE_继承参数表#WORD("{\r\npublic:\r\n\r\n")
		MAKE_COMHOOKHPP尾<MAKE>=WORD("};\r\n")
		
		MAKE_包容基类头文件IUNKNOWN<MAKE>=WORD("\r\n\tHRESULT HookQueryInterface(REFIID riid, void** ppvObj);\r\n\r\n")
		
		MAKE_COMHOOKHPPX<MAKE>=MAKE_COMHOOKHPP头#MAKE_包容基类头文件IUNKNOWN#MAKE_COMHOOKHPP尾
		
		MAKE_COMHOOKHPPXX<MAKE>=MAKE_TO<MAKE_COMHOOKHPPX,COMHOOK类声明生成路径>
	
	
	
	//make COM HOOK 包容基类 主Cpp文件
		//#include "" 表
	
		//make 接口hook cpp文件
		//宏接口隐射表
		//BEGIN_INTERFACE_LIST(Sham_FileSaveDialog)
		//IMPLEMENT_INTERFACE(RealDialog)
		//IMPLEMENT_INTERFACE(IFileDialogCustomize)
		//BEGIN_INTERFACE_MAP(RealDialog)
			//MAP_INTERFACE(IModalWindow,			RealDialog)
			//MAP_INTERFACE(IFileDialog,			RealDialog)
			//MAP_INTERFACE(IFileSaveDialog,		RealDialog)
			//MAP_INTERFACE(IFileDialogCustomize,	IFileDialogCustomize)
		//END_INTERFACE_LIST
		
		MAKE_宏接口定义表BEGIN<MAKE>=WORD("\r\nBEGIN_INTERFACE_LIST1(")+MAKE_COMHOOK包容类名+WORD(")\r\n")
		
		MAKE_宏接口定义表IMPLEMENT<MAKE>=WORD("\tIMPLEMENT_INTERFACE1(")+类声明.类声明1.类名+WORD(")\r\n")
		MAKE_宏接口定义表IMPLEMENT_ARRAY<MAKE>=MAKE_N<MAKE_接口类ROOT,MAKE_宏接口定义表IMPLEMENT,MAKE_宏接口定义表IMPLEMENT,MAKE_宏接口定义表IMPLEMENT>
		
		MAKE_宏接口定义表MAP_BEGIN<MAKE>=WORD("\t\BEGIN_INTERFACE_MAP1(")#MAKE_COMHOOK包容类名#WORD(")\r\n")
		
		MAKE_宏接口定义表MAP<MAKE>=WORD("\t\tMAP_INTERFACE1(")#类声明.类声明1.类名+WORD(",")+类声明.类声明1.类名#WORD(")\r\n")
		MAKE_宏接口定义表MAP_ARRAY<MAKE>=MAKE_N<MAKE_接口类ROOT,MAKE_宏接口定义表MAP,MAKE_宏接口定义表MAP,MAKE_宏接口定义表MAP>
		
		MAKE_宏接口定义表END<MAKE>=WORD("END_INTERFACE_LIST1 \r\n\r\n\r\n")
		
		MAKE_宏接口定义表<MAKE>=MAKE_宏接口定义表BEGIN#MAKE_宏接口定义表IMPLEMENT_ARRAY#MAKE_宏接口定义表MAP_BEGIN#MAKE_宏接口定义表MAP_ARRAY#MAKE_宏接口定义表END
		
		MAKE_包含代码头<MAKE>=预编译包含文件代码#WORD("\r\n#include \"")#COMHOOK类声明文件名#WORD("\"\r\n\r\n")
		MAKE_包含代码文件<MAKE>=WORD("\r\n#include \"")#接口类H文件名#WORD("\"\r\n")
		MAKE_包含代码文件表<MAKE>=MAKE_N<MAKE_接口类ROOT,MAKE_包含代码文件,MAKE_包含代码文件,MAKE_包含代码文件>
		
		MAKE_主CPP_HookQueryInterface头<MAKE>=WORD("HRESULT ")#MAKE_COMHOOK包容类名#WORD("::HookQueryInterface(REFIID riid, void** ppvObj)\r\n{\r\n")
		MAKE_主CPP_HookQueryInterface头1<MAKE>=WORD("\r\n\tBOOL bFind=FALSE;\r\n\tif(riid==__uuidof(IUnknown))\r\n\t{\r\n\t\treturn S_OK;\r\n\t}")
		MAKE_主CPP_HookQueryInterface尾<MAKE>=WORD("\r\n\treturn bFind? S_OK: E_NOINTERFACE;\r\n}\r\n\r\n")
		MAKE_接口包容指针At主Cpp<MAKE>=WORD("((")#接口类名#WORD("<")#MAKE_COMHOOK包容类名#WORD("> *)this)")
		MAKE_接口原始指针At主Cpp<MAKE>=MAKE_接口包容指针At主Cpp#WORD("->")#MAKE_原始接口对象名AtROOT
		MAKE_接口原始IUnKnown指针At主Cpp<MAKE>=MAKE_接口包容指针At主Cpp#WORD("->m_pIUnknown")
		MAKE_主CPP_HookQueryInterface接口处理<MAKE>=WORD("else if(riid==__uuidof(")#类生成名+WORD("))\r\n\t{\r\n\t\t")#MAKE_接口原始指针At主Cpp#WORD("=(")#类生成名#WORD("*)*ppvObj;\r\n\t\t")#MAKE_接口原始IUnKnown指针At主Cpp#WORD("=(IUnknown*)*ppvObj;\r\n\t\t*ppvObj=")#MAKE_接口包容指针At主Cpp#WORD(";\r\n\t\tbFind=TRUE;\r\n\t}")
		MAKE_主CPP_HookQueryInterface接口处理表<MAKE>=MAKE_N<MAKE_接口类ROOT,MAKE_主CPP_HookQueryInterface接口处理,MAKE_主CPP_HookQueryInterface接口处理,MAKE_主CPP_HookQueryInterface接口处理>
		MAKE_主CPP_HookQueryInterface<MAKE>=MAKE_主CPP_HookQueryInterface头#MAKE_主CPP_HookQueryInterface头1#MAKE_主CPP_HookQueryInterface接口处理表#MAKE_主CPP_HookQueryInterface尾
		
		MAKE_主Cpp文件1<MAKE>=MAKE_包含代码头+MAKE_包含代码文件表+MAKE_主CPP_HookQueryInterface
		MAKE_主Cpp文件<MAKE>=MAKE_TO<MAKE_主Cpp文件1,主Cpp文件>
	
	
	//make 接口hook h文件
		
		
		//make COM HOOK 声明头尾
		MAKE_虚拟函数1<MAKE>=WORD("\r\n\tvirtual ")#MAKE_函数1
		MAKE_虚拟函数2<MAKE>=WORD("\r\n\tvirtual ")#MAKE_函数2
		MAKE_虚拟函数11<MAKE>=MAKE_不需要的函数|MAKE_虚拟函数1
		MAKE_虚拟函数22<MAKE>=MAKE_不需要的函数|MAKE_虚拟函数2
		//make 接口所属函数
		MAKE类声明虚拟函数声明1<MAKE>=MAKE_N<MAKE_函数ROOT2,MAKE_虚拟函数22,MAKE_虚拟函数22,MAKE_虚拟函数22>&MAKE_N<MAKE_函数ROOT1,MAKE_虚拟函数11,MAKE_虚拟函数11,MAKE_虚拟函数11>
		MAKE类声明虚拟函数声明<MAKE>=WORD("\r\n\t/*=======================")#MAKE_原始接口对象类型#WORD("接口函数声明=======================*/\r\n")#MAKE类声明虚拟函数声明1#WORD("\r\n\r\n\t/*=======================")#MAKE_原始接口对象类型#WORD("接口函数声明 End=======================*/\r\n\r\n\r\n")
	
		MAKE_原始接口对象名AtROOT<MAKE>=WORD("m_p")#类声明.类声明1.类名
		MAKE_原始接口对象指针类型<MAKE>=WORD("ComPointer<")#MAKE_原始接口对象类型#WORD(">")
		MAKE_原始接口对象类型<MAKE>=类声明.类声明1.类名
		MAKE_原始接口指针声明<MAKE>=WORD("\r\n\t")#MAKE_原始接口对象指针类型+MAKE_原始接口对象名AtROOT+WORD(";\r\n")
		
		
		MAKE_接口H文件头<MAKE>=WORD("\r\n#pragma once\r\n\r\n#include \"common.h\"\r\n\r\n")#WORD("template<typename InterfaceMapBase>\r\n")#WORD("class ")+接口类名#WORD("\r\n")#WORD("\t\t\t: public KcgComHook1\r\n")#WORD("\t\t\t, public")+类生成名#WORD("\r\n{\r\npublic:\r\n")
		//#WORD("\r\n\t\t\t, public")+接口类名称前缀#MAKE_继承基类名#WORD("<")#接口类名#WORD("<InterfaceMapBase> >\r\n{\r\npublic:\r\n")
		MAKE_接口H文件尾<MAKE>=WORD("};\r\n#include \"")#接口类名#WORD(".cpp\"\r\n")
		
		MAKE_接口H文件IUNKNOWN<MAKE>=WORD("\r\n\tComPointer<IUnknown> m_pIUnknown;\r\n\r\n\r\n\tvirtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObj);\r\n\r\n\tvirtual ULONG STDMETHODCALLTYPE AddRef();\r\n\r\n\tvirtual ULONG STDMETHODCALLTYPE Release();\r\n\r\n")
		
	//所有基类函数声明
		MAKE_继承基类名<MAKE>=类声明.类声明1.继承基类名.基类名
		MAKE_设置继承基类名MAKE<MAKE>=WORD("MAKE_继承基类名<MAKE>=WORD(\"")#类声明.类声明1.继承基类名.基类名#WORD("\")")
		MAKE_设置继承基类名<MAKE>=DEBUGOUT<"MAKE_设置继承基类名MAKE">+DEBUGOUT<MAKE_设置继承基类名MAKE>+MAKE_ADD<MAKE_设置继承基类名MAKE>
		MAKE_继承基类ROOTPATH<MAKE>=WORD("Hello world")
		MAKE_TMPROOTPATH<MAKE>=WORD("Hello world")
		MAKE_继承基类ROOTPATH_MAKE<MAKE>=WORD("MAKE_继承基类ROOTPATH<MAKE>=ROOTROOT.ROOT.类声明.类声明1.")#MAKE_继承基类名#WORD(".PARENT.PARENT.PARENT")
		
		MAKE_设置继承基类代码路径<MAKE_SET>=DEBUGOUT<"MAKE_设置继承基类代码路径">&MAKE_设置继承基类名+MAKE_ADD<MAKE_继承基类ROOTPATH_MAKE>
	
	
		MAKE_当前类路径名<MAKE>=WORD("Hello world")
		MAKE_当前类名<MAKE>=WORD("Hello world")
		MAKE_当前函数名<MAKE>=WORD("Hello world")
		MAKE_继承所属类函数名1ROOT<MAKE>=WORD("Hello world")
		MAKE_继承所属类函数名2ROOT<MAKE>=WORD("Hello world")
		MAKE_继承所属类函数名1<MAKE>=DEBUGOUT<"MAKE_继承所属类函数名1">+WORD("MAKE_继承所属类函数名1ROOT<MAKE>=")#MAKE_当前类路径名#WORD(".")#MAKE_函数ROOT1_MAKE#WORD(".")#MAKE_当前函数名
		MAKE_继承所属类函数名2<MAKE>=DEBUGOUT<"MAKE_继承所属类函数名2">+WORD("MAKE_继承所属类函数名2ROOT<MAKE>=")#MAKE_当前类路径名#WORD(".")#MAKE_函数ROOT2_MAKE#WORD(".")#MAKE_当前函数名
		
		MAKE_当前类函数名ROOT_MAKE<MAKE>=WORD("MAKE_当前函数名<MAKE>=WORD(\"函数名.")#O.函数名#WORD("\")")
		MAKE_函数是否在继承所属类1<MAKE>=DEBUGOUT<MAKE_当前类函数名ROOT_MAKE>+MAKE_ADD<MAKE_当前类函数名ROOT_MAKE>+MAKE_ADD<MAKE_继承所属类函数名1>+DEBUGOUT<MAKE_继承所属类函数名1>+DEBUGOUT<MAKE_继承所属类函数名1ROOT>+MAKE_继承所属类函数名1ROOT
		MAKE_函数是否在继承所属类2<MAKE>=DEBUGOUT<MAKE_当前类函数名ROOT_MAKE>+MAKE_ADD<MAKE_当前类函数名ROOT_MAKE>+MAKE_ADD<MAKE_继承所属类函数名2>+DEBUGOUT<MAKE_继承所属类函数名2>+DEBUGOUT<MAKE_继承所属类函数名2ROOT>+MAKE_继承所属类函数名2ROOT
		
		
		MAKE_当前类ROOT_MAKE<MAKE>=DEBUGOUT<"MAKE_当前类ROOT_MAKE">+WORD("MAKE_当前类路径名<MAKE>=WORD(\"ROOTROOT.ROOT.类声明.类声明1.")#MAKE_当前类名#WORD(".PARENT.PARENT.PARENT\")")

		MAKE_设置当前类名MAKE<MAKE>=WORD("MAKE_当前类名<MAKE>=WORD(\"")#类生成名#WORD("\")")
		MAKE_设置当前类名<MAKE>=DEBUGOUT<"MAKE_设置当前类名">+DEBUGOUT<MAKE_设置当前类名MAKE>+MAKE_ADD<MAKE_设置当前类名MAKE>
		MAKE_设置当前类代码路径<MAKE_SET>=DEBUGOUT<"MAKE_设置当前类代码路径">+DEBUGOUT<MAKE_当前类ROOT_MAKE>+DEBUGOUT<"MAKE_设置当前类名">+DEBUGOUT<MAKE_设置当前类名>+MAKE_设置当前类名+MAKE_ADD<MAKE_当前类ROOT_MAKE>
		
		MAKE_重复继承的函数<MAKE_CHECK>=NOT<MAKE_重复继承的函数1>
		//NOT<MAKE_不需要的函数>|
		MAKE_基类虚拟函数11<MAKE>=DEBUGOUT<"MAKE_基类虚拟函数11">+IF<MAKE_函数是否在继承所属类1>|MAKE_虚拟函数1
		MAKE_基类虚拟函数22<MAKE>=DEBUGOUT<"MAKE_基类虚拟函数22">+IF<MAKE_函数是否在继承所属类2>|MAKE_虚拟函数2
		MAKE类声明基类虚拟函数声明1<MAKE>=DEBUGOUT<"MAKE类声明基类虚拟函数声明1">&MAKE_N<MAKE_函数ROOT2,MAKE_基类虚拟函数22,MAKE_基类虚拟函数22,MAKE_基类虚拟函数22>&DEBUGOUT<"MAKE类声明基类虚拟函数声明111">&MAKE_N<MAKE_函数ROOT1,MAKE_基类虚拟函数11,MAKE_基类虚拟函数11,MAKE_基类虚拟函数11>
		
		MAKE类声明基类虚拟函数声明2<MAKE>=MAKE_ONE<MAKE_继承基类ROOTPATH,MAKE类声明基类虚拟函数声明1>#WORD(" ")
		MAKE类声明基类虚拟函数声明<MAKE>=MAKE_设置当前类代码路径&MAKE_设置继承基类代码路径&WORD("\r\n\t/*=======================")#MAKE_继承基类名#WORD("接口函数声明=======================*/\r\n")#MAKE类声明基类虚拟函数声明2#WORD("\r\n\r\n\t/*=======================")#MAKE_继承基类名#WORD("接口函数声明 End=======================*/\r\n\r\n\r\n")
	
	
		MAKE_接口H文件体<MAKE>=MAKE_接口H文件头#MAKE_接口H文件IUNKNOWN#MAKE_原始接口指针声明&MAKE类声明虚拟函数声明&MAKE类声明基类虚拟函数声明&MAKE_接口H文件尾
		MAKE_接口H文件1<MAKE>=MAKE_TO<MAKE_接口H文件体,接口类H文件生成路径>
		//make 所有接口
		MAKE_接口H文件<MAKE>=MAKE_N<MAKE_接口类ROOT,MAKE_接口H文件1,MAKE_接口H文件1,MAKE_接口H文件1>
	
		
	//make 接口 hook cpp文件	

		
		MAKE_接口函数定义头1<MAKE>=WORD("template<typename InterfaceMapBase>\r\n")#WORD(HRESULT)&接口函数所属类名#WORD("<InterfaceMapBase>::")#O.函数名#WORD(()&MAKE_函数参数表&WORD())#WORD("\r\n")
		MAKE_接口函数定义头2<MAKE>=WORD("template<typename InterfaceMapBase>\r\n")#MAKE_函数2返回参数&接口函数所属类名#WORD("<InterfaceMapBase>::")#O.函数名#WORD(()&MAKE_函数参数表&WORD())#WORD("\r\n")
		MAKE_接口函数定义1<MAKE>=WORD("\r\n")#MAKE_接口函数定义头1#WORD("{\r\n\t return ")+MAKE_原始接口对象#WORD("->")#MAKE_函数调用+WORD(";\r\n}\r\n")
		MAKE_接口函数定义2<MAKE>=WORD("\r\n")#MAKE_接口函数定义头2#WORD("{\r\n\t return ")+MAKE_原始接口对象#WORD("->")#MAKE_函数调用+WORD(";\r\n}\r\n")
		
		MAKE_接口函数定义11<MAKE>=MAKE_不需要的函数|MAKE_接口函数定义1
		MAKE_接口函数定义22<MAKE>=MAKE_不需要的函数|MAKE_接口函数定义2
		
		
		
		//make 所有接口所属函数
		MAKE_接口函数定义表1<MAKE>=MAKE_N<MAKE_函数ROOT2,MAKE_接口函数定义22,MAKE_接口函数定义22,MAKE_接口函数定义22>&MAKE_N<MAKE_函数ROOT1,MAKE_接口函数定义11,MAKE_接口函数定义11,MAKE_接口函数定义11>
		
		//make 基类函数
		MAKE_基类接口函数定义头1<MAKE>=WORD("template<typename InterfaceMapBase>\r\n")#WORD(HRESULT)&接口类名称前缀#MAKE_当前类名#WORD("<InterfaceMapBase>::")#O.函数名#WORD(()&MAKE_函数参数表&WORD())#WORD("\r\n")
		MAKE_基类接口函数定义头2<MAKE>=WORD("template<typename InterfaceMapBase>\r\n")#MAKE_函数2返回参数&接口类名称前缀#MAKE_当前类名#WORD("<InterfaceMapBase>::")#O.函数名#WORD(()&MAKE_函数参数表&WORD())#WORD("\r\n")
		MAKE_基类接口函数定义1<MAKE>=WORD("\r\n")#MAKE_基类接口函数定义头1#WORD("{\r\n\t return ")+MAKE_继承所属类原始接口对象#WORD("->")#MAKE_函数调用+WORD(";\r\n}\r\n")
		MAKE_基类接口函数定义2<MAKE>=WORD("\r\n")#MAKE_基类接口函数定义头2#WORD("{\r\n\t return ")+MAKE_继承所属类原始接口对象#WORD("->")#MAKE_函数调用+WORD(";\r\n}\r\n")
		
		MAKE_基类接口函数定义11<MAKE>=MAKE_不需要的函数&IF<MAKE_函数是否在继承所属类1>|MAKE_基类接口函数定义1
		MAKE_基类接口函数定义22<MAKE>=MAKE_不需要的函数&IF<MAKE_函数是否在继承所属类2>|MAKE_基类接口函数定义2
		MAKE_基类接口函数定义表1<MAKE>=DEBUGOUT<"MAKE_基类接口函数定义表1">&MAKE_N<MAKE_函数ROOT2,MAKE_基类接口函数定义22,MAKE_基类接口函数定义22,MAKE_基类接口函数定义22>&MAKE_N<MAKE_函数ROOT1,MAKE_基类接口函数定义11,MAKE_基类接口函数定义11,MAKE_基类接口函数定义11>
		MAKE_基类接口函数定义表<MAKE>=MAKE_设置当前类代码路径&MAKE_设置继承基类代码路径&MAKE_ONE<MAKE_继承基类ROOTPATH,MAKE_基类接口函数定义表1>#WORD(" ")
		
		MAKE_接口CPP头<MAKE>=预编译包含文件代码#WORD("\r\n#include \"common.h\"\r\n")#WORD("\r\n#include \"")#接口类H文件名#WORD("\"\r\n\r\n")
		
		MAKE_接口CPPIUNKNOWN1<MAKE>=WORD("\r\ntemplate<typename InterfaceMapBase>\r\n")#WORD("HRESULT ")#接口类名#WORD("<InterfaceMapBase>::")#WORD("QueryInterface(REFIID riid, void** ppvObj)")#WORD("\r\n{\r\n\t*ppvObj=NULL;\r\n")#WORD("\r\n\tif(riid==__uuidof(IUnknown))\r\n\t{\r\n\t\t*ppvObj=(IUnknown*)(")#类生成名#WORD(" *)this;\r\n\t\treturn S_OK;\r\n\t}")#WORD("\r\n\tHRESULT rst=m_pIUnknown->QueryInterface(riid, ppvObj);\r\n\tif(rst==S_OK)\r\n\t{\r\n\t\trst=GETPARENTCLASS(InterfaceMapBase,")#接口类名#WORD(",this)->HookQueryInterface(riid, ppvObj);\r\n\t}\r\n\treturn ppvObj != NULL? S_OK: E_NOINTERFACE;\r\n}\r\n\r\n")
		MAKE_接口CPPIUNKNOWN2<MAKE>=WORD("\r\ntemplate<typename InterfaceMapBase>\r\n")#WORD("ULONG ")#接口类名#WORD("<InterfaceMapBase>::")#WORD("AddRef()")#WORD("\r\n{\r\n\treturn m_pIUnknown->AddRef();\r\n\}\r\n")
		MAKE_接口CPPIUNKNOWN3<MAKE>=WORD("\r\ntemplate<typename InterfaceMapBase>\r\n")#WORD("ULONG ")#接口类名#WORD("<InterfaceMapBase>::")#WORD("Release()")#WORD("\r\n{\r\n\treturn m_pIUnknown->Release();\r\n\}\r\n")

		MAKE_接口CPPIUNKNOWN4<MAKE>=WORD("\r\ntemplate<typename InterfaceMapBase>\r\n")#WORD("HRESULT ")#接口类名#WORD("<InterfaceMapBase>::")#WORD("HookQueryInterface(REFIID riid, void** ppvObj)")#WORD("\r\n{\r\n\tHRESULT rst=GETPARENTCLASS(InterfaceMapBase,")#接口类名#WORD(",this)->HookQueryInterface(riid, ppvObj);\r\n\treturn ppvObj != NULL? S_OK: E_NOINTERFACE;\r\n}\r\n\r\n")
		

		MAKE_接口CPP体<MAKE>=MAKE_接口CPPIUNKNOWN1#MAKE_接口CPPIUNKNOWN2#MAKE_接口CPPIUNKNOWN3#MAKE_接口函数定义表1#MAKE_基类接口函数定义表
		//#MAKE_接口函数定义表1#MAKE_基类接口函数定义表
		MAKE_接口CPP1<MAKE>=MAKE_TO<MAKE_接口CPP体,接口类生成路径>
		//make 所有接口
		MAKE_接口CPP<MAKE>=MAKE_N<MAKE_接口类ROOT,MAKE_接口CPP1,MAKE_接口CPP1,MAKE_接口CPP1>
	
	
	//定制元素名
	//COM HOOK 包容类名
	主Cpp文件<MAKE>=生成文件基目录#MAKE_COMHOOK包容类名#WORD(".cpp")
	MAKE_COMHOOK包容类名<MAKE>=WORD("ComHookPacketBase")
	生成文件基目录<MAKE>=WORD("c:\\dx89\\")
	类生成名<MAKE>=类声明.类声明1.类名
	类生成CPP文件名<MAKE>=类生成名#WORD(".cpp")
	类生成H文件名<MAKE>=类生成名#WORD(".h")
	包容基类CPP文件名<MAKE>=MAKE_COMHOOK包容类名#WORD("_")#类生成CPP文件名
	包容基类类生成路径<MAKE>=生成文件基目录#包容基类CPP文件名
	COMHOOK类声明文件名<MAKE>=MAKE_COMHOOK包容类名#WORD(".h")
	COMHOOK类声明生成路径<MAKE>=生成文件基目录#COMHOOK类声明文件名
	
	预编译包含文件代码<MAKE>=WORD("\r\n#include \"stdafx.h\"\r\n\r\n")
	接口类名称前缀<MAKE>=WORD("ComHook_")
	接口类H文件名<MAKE>=接口类名称前缀#类生成H文件名
	接口类CPP文件名<MAKE>=接口类名称前缀#类生成CPP文件名
	接口类生成路径<MAKE>=生成文件基目录#接口类CPP文件名
	
	接口类H文件生成路径<MAKE>=生成文件基目录#接口类H文件名
	接口类名<MAKE>=接口类名称前缀#类生成名
	接口函数所属类名<MAKE>=接口类名称前缀#MAKE_函数定义类名ROOT
	
	//make根
	//类生成路径
	//MAKE_接口H文件+MAKE_接口CPP+MAKE_主Cpp文件+MAKE_COMHOOKHPPXX+MAKE_COMHOOKCPP3
	MAKE_HPP_CPP<MAKE>=MAKE_接口H文件+MAKE_接口CPP+MAKE_主Cpp文件+MAKE_COMHOOKHPPXX
	
	
	
	
	
	
	
	