	MAKEINCLUDE="c:\\dx89codetree.mk"
	
	//MAKE DX COM�����ϳɿ�
	MAKE_Def�ղ�����do<MAKE>=WORD("NodefName")
	MAKE_Def�ղ�����MAKE<MAKE>=WORD("MAKE_Def�ղ�����do<MAKE>=WORD(\"")#MAKE_Def�ղ�����do#WORD("1\")")
	MAKE_Def�ղ�����<MAKE>=MAKE_Def�ղ�����do&MAKE_ADD<MAKE_Def�ղ�����MAKE>
	//MAKE_Def�ղ�����ÿ����һ�ξͼ�1�������ø�λ���½�������ΪĬ��ֵ
	MAKE_��λDef�ղ�����MAKE<MAKE>=WORD("MAKE_Def�ղ�����do<MAKE>=WORD(\"NodefName\")")
	MAKE_��λDef�ղ�����<MAKE>=MAKE_ADD<MAKE_��λDef�ղ�����MAKE>
	
	MAKE_�ղ�������<MAKE>=O.��������.�ղ�������#MAKE_Def�ղ�����
	MAKE_��������<MAKE>=MAKE_�ղ�������|O.��������
	MAKE_����������1<MAKE>=��������.�����Ͳ���+MAKE_��������
	MAKE_����������2<MAKE>=��������.�����Ͳ���+MAKE_��������
	MAKE_����������3<MAKE>=��������.ָ���Ͳ���+MAKE_��������
	MAKE_����������4<MAKE>=��������.ָ��ָ���Ͳ���+MAKE_��������
	
	MAKE_����������11<MAKE>=��������.CONST�����Ͳ���+MAKE_��������
	MAKE_����������21<MAKE>=��������.CONST�����Ͳ���+MAKE_��������
	MAKE_����������31<MAKE>=��������.CONSTָ���Ͳ���+MAKE_��������
	MAKE_����������41<MAKE>=��������.CONSTָ��ָ���Ͳ���+MAKE_��������
	
	
	MAKE_����������7<MAKE>=MAKE_����������1|MAKE_����������2|MAKE_����������3|MAKE_����������4|MAKE_����������11|MAKE_����������21|MAKE_����������31|MAKE_����������41
	MAKE_����������8<MAKE>=WORD(,)+MAKE_����������1|MAKE_����������2|MAKE_����������3|MAKE_����������4|MAKE_����������11|MAKE_����������21|MAKE_����������31|MAKE_����������41
	MAKE_����ROOT<MAKE>=������.������1.��������.������������.������������5.��������
	MAKE_����ROOT1<MAKE>=������.������1.��������.������������.������������5.��������.��������1
	MAKE_����ROOT2<MAKE>=������.������1.��������.������������.������������5.��������.��������2
	
	MAKE_����ROOT1_MAKE<MAKE>=WORD("������.������1.��������.������������.������������5.��������.��������1")
	MAKE_����ROOT2_MAKE<MAKE>=WORD("������.������1.��������.������������.������������5.��������.��������2")
	
	MAKE_����������ROOT<MAKE>=������������.��������������.����������������
	MAKE_�ӿ���ROOT<MAKE>=ROOTROOT.ROOT
	
	//��������
	MAKE_����������<MAKE>=MAKE_��λDef�ղ�����&MAKE_N<MAKE_����������ROOT,MAKE_����������7,MAKE_����������8,MAKE_����������8>
	MAKE_����1<MAKE>=WORD("HRESULT STDMETHODCALLTYPE")&O.������#WORD(()&MAKE_����������&WORD())#WORD(;)#WORD("\r\n")
	MAKE_����2<MAKE>=MAKE_����2���ز���&WORD("STDMETHODCALLTYPE")&O.������#WORD(()&MAKE_����������&WORD())#WORD(;)#WORD("\r\n")
	MAKE_����2���ز���<MAKE>=O.������������.��������.�����Ͳ���|O.������������.��������.ָ���Ͳ���|O.������������.��������.�����Ͳ���|O.������������.��������.ָ��ָ���Ͳ���
	MAKE_����22<MAKE>=NOT<MAKE_����Ҫ�ĺ���>|MAKE_����2
	MAKE_����11<MAKE>=NOT<MAKE_����Ҫ�ĺ���>|MAKE_����1
		
	//��������
	MAKE_�������ò�����1<MAKE>=MAKE_��������
	MAKE_�������ò�����2<MAKE>=WORD(,)+MAKE_��������
	MAKE_�������ò�����<MAKE>=MAKE_��λDef�ղ�����&MAKE_N<MAKE_����������ROOT,MAKE_�������ò�����1,MAKE_�������ò�����2,MAKE_�������ò�����2>
	MAKE_��������<MAKE>=O.������#WORD(()&MAKE_�������ò�����&WORD())



	
	//����Ҫ��ע�ĺ���
	MAKE_����Ҫ�ĺ���1<MAKE>=������.AddRef|������.Release|������.QueryInterface
	MAKE_����Ҫ�ĺ���<MAKE>=IF<MAKE_����Ҫ�ĺ���1>
	
	//��������ͷ
	MAKE_������������ROOT<MAKE>=PARENT.PARENT.PARENT.PARENT.PARENT.����
	MAKE_��������ͷ1<MAKE>=WORD(HRESULT)&MAKE_������������ROOT#WORD("::")#O.������#WORD(()&MAKE_����������&WORD())#WORD("\r\n")
	MAKE_��������ͷ2<MAKE>=MAKE_����2���ز���&MAKE_������������ROOT#WORD("::")#O.������#WORD(()&MAKE_����������&WORD())#WORD("\r\n")
	MAKE_��������ͷ22<MAKE>=MAKE_����Ҫ�ĺ���|MAKE_��������ͷ2
	MAKE_��������ͷ11<MAKE>=MAKE_����Ҫ�ĺ���|MAKE_��������ͷ1		

	
	
	
	//��������

	MAKE��������������<MAKE>=MAKE_N<MAKE_����ROOT2,MAKE_����22,MAKE_����22,MAKE_����22>&MAKE_N<MAKE_����ROOT1,MAKE_����11,MAKE_����11,MAKE_����11>
	MAKE��������������<MAKE>=MAKE_N<MAKE_����ROOT2,MAKE_��������22,MAKE_��������22,MAKE_��������22>&MAKE_N<MAKE_����ROOT1,MAKE_��������11,MAKE_��������11,MAKE_��������11>
	
	MAKE��������������ͷ1<MAKE>=MAKE_N<MAKE_����ROOT2,MAKE_��������ͷ22,MAKE_��������ͷ22,MAKE_��������ͷ22>&MAKE_N<MAKE_����ROOT1,MAKE_��������ͷ11,MAKE_��������ͷ11,MAKE_��������ͷ11>
	MAKE��������������ͷ<MAKE>=MAKE_TO<MAKE��������������ͷ1,������·��>
	
	MAKE������<MAKE>=MAKE_N<MAKE_�ӿ���ROOT,MAKE��������������ͷ,MAKE��������������ͷ,MAKE��������������ͷ>

	//make ���ݻ��� �����ӿ�cpp�ļ�
		//COM HOOK����������
		MAKE_��������ͷ1<MAKE>=WORD(HRESULT)&MAKE_COMHOOK��������#WORD("::")#O.������#WORD(()&MAKE_����������&WORD())#WORD("\r\n")
		MAKE_��������ͷ2<MAKE>=MAKE_����2���ز���&MAKE_COMHOOK��������#WORD("::")#O.������#WORD(()&MAKE_����������&WORD())#WORD("\r\n")
	
		MAKE_ԭʼ�ӿڶ���<MAKE>=WORD("m_p")#MAKE_������������ROOT
		MAKE_�̳�������ԭʼ�ӿڶ���<MAKE>=WORD("m_p")#MAKE_��ǰ����
		MAKE_COMHOOKPACKET��������1<MAKE>=WORD("\r\n")#MAKE_��������ͷ1#WORD("{\r\n\t return ")+MAKE_ԭʼ�ӿڶ���#WORD("->")#MAKE_��������+WORD(";\r\n}\r\n")
		MAKE_COMHOOKPACKET��������2<MAKE>=WORD("\r\n")#MAKE_��������ͷ2#WORD("{\r\n\t return ")+MAKE_ԭʼ�ӿڶ���#WORD("->")#MAKE_��������+WORD(";\r\n}\r\n")
		
		MAKE_COMHOOKPACKET��������11<MAKE>=MAKE_����Ҫ�ĺ���|MAKE_COMHOOKPACKET��������1
		MAKE_COMHOOKPACKET��������22<MAKE>=MAKE_����Ҫ�ĺ���|MAKE_COMHOOKPACKET��������2
		
		
		
		//make ���нӿ���������
		MAKE_COMHOOKCPP1<MAKE>=MAKE_N<MAKE_����ROOT2,MAKE_COMHOOKPACKET��������22,MAKE_COMHOOKPACKET��������22,MAKE_COMHOOKPACKET��������22>&MAKE_N<MAKE_����ROOT1,MAKE_COMHOOKPACKET��������11,MAKE_COMHOOKPACKET��������11,MAKE_COMHOOKPACKET��������11>
		MAKE_COMHOOKCPP11<MAKE>=WORD("\r\n#include \"")#COMHOOK�������ļ���#WORD("\"\r\n\r\n")+MAKE_COMHOOKCPP1
		MAKE_COMHOOKCPP2<MAKE>=MAKE_TO<MAKE_COMHOOKCPP11,���ݻ���������·��>
		//make ���нӿ�
		MAKE_COMHOOKCPP3<MAKE>=MAKE_N<MAKE_�ӿ���ROOT,MAKE_COMHOOKCPP2,MAKE_COMHOOKCPP2,MAKE_COMHOOKCPP2>
	
	//make COM HOOK ���ݻ���ͷ�ļ�
		
		MAKE_ԭʼ�ӿڶ�������<MAKE>=������.������1.����
	
		//make COM HOOK ����ͷβ
		MAKE_ԭʼ�ӿڼ̳ж�������1<MAKE>=WORD("\t\t\t: public")+�ӿ�����#WORD("<")#MAKE_COMHOOK��������#WORD(">\r\n")
		MAKE_ԭʼ�ӿڼ̳ж�������2<MAKE>=WORD("\t\t\t, public")+�ӿ�����#WORD("<")#MAKE_COMHOOK��������#WORD(">\r\n")
		MAKE_�̳в�����<MAKE>=MAKE_N<MAKE_�ӿ���ROOT,MAKE_ԭʼ�ӿڼ̳ж�������2,MAKE_ԭʼ�ӿڼ̳ж�������2,MAKE_ԭʼ�ӿڼ̳ж�������2>
		
		MAKE_�������ݽӿ�ͷ�ļ�<MAKE>=WORD("\r\n#include \"")#�ӿ�����#WORD(".h\"\r\n")
		MAKE_�������ݽӿ�ͷ�ļ���<MAKE>=MAKE_N<MAKE_�ӿ���ROOT,MAKE_�������ݽӿ�ͷ�ļ�,MAKE_�������ݽӿ�ͷ�ļ�,MAKE_�������ݽӿ�ͷ�ļ�>
		
		
		MAKE_COMHOOKHPPͷ<MAKE>=WORD("\r\n#pragma once\r\n\r\n")#MAKE_�������ݽӿ�ͷ�ļ���#WORD("\r\n\r\nclass ")+MAKE_COMHOOK��������+WORD("\r\n")+WORD("\t\t\t: public KcgComHook\r\n")#MAKE_�̳в�����#WORD("{\r\npublic:\r\n\r\n")
		MAKE_COMHOOKHPPβ<MAKE>=WORD("};\r\n")
		
		MAKE_���ݻ���ͷ�ļ�IUNKNOWN<MAKE>=WORD("\r\n\tHRESULT HookQueryInterface(REFIID riid, void** ppvObj);\r\n\r\n")
		
		MAKE_COMHOOKHPPX<MAKE>=MAKE_COMHOOKHPPͷ#MAKE_���ݻ���ͷ�ļ�IUNKNOWN#MAKE_COMHOOKHPPβ
		
		MAKE_COMHOOKHPPXX<MAKE>=MAKE_TO<MAKE_COMHOOKHPPX,COMHOOK����������·��>
	
	
	
	//make COM HOOK ���ݻ��� ��Cpp�ļ�
		//#include "" ��
	
		//make �ӿ�hook cpp�ļ�
		//��ӿ������
		//BEGIN_INTERFACE_LIST(Sham_FileSaveDialog)
		//IMPLEMENT_INTERFACE(RealDialog)
		//IMPLEMENT_INTERFACE(IFileDialogCustomize)
		//BEGIN_INTERFACE_MAP(RealDialog)
			//MAP_INTERFACE(IModalWindow,			RealDialog)
			//MAP_INTERFACE(IFileDialog,			RealDialog)
			//MAP_INTERFACE(IFileSaveDialog,		RealDialog)
			//MAP_INTERFACE(IFileDialogCustomize,	IFileDialogCustomize)
		//END_INTERFACE_LIST
		
		MAKE_��ӿڶ����BEGIN<MAKE>=WORD("\r\nBEGIN_INTERFACE_LIST1(")+MAKE_COMHOOK��������+WORD(")\r\n")
		
		MAKE_��ӿڶ����IMPLEMENT<MAKE>=WORD("\tIMPLEMENT_INTERFACE1(")+������.������1.����+WORD(")\r\n")
		MAKE_��ӿڶ����IMPLEMENT_ARRAY<MAKE>=MAKE_N<MAKE_�ӿ���ROOT,MAKE_��ӿڶ����IMPLEMENT,MAKE_��ӿڶ����IMPLEMENT,MAKE_��ӿڶ����IMPLEMENT>
		
		MAKE_��ӿڶ����MAP_BEGIN<MAKE>=WORD("\t\BEGIN_INTERFACE_MAP1(")#MAKE_COMHOOK��������#WORD(")\r\n")
		
		MAKE_��ӿڶ����MAP<MAKE>=WORD("\t\tMAP_INTERFACE1(")#������.������1.����+WORD(",")+������.������1.����#WORD(")\r\n")
		MAKE_��ӿڶ����MAP_ARRAY<MAKE>=MAKE_N<MAKE_�ӿ���ROOT,MAKE_��ӿڶ����MAP,MAKE_��ӿڶ����MAP,MAKE_��ӿڶ����MAP>
		
		MAKE_��ӿڶ����END<MAKE>=WORD("END_INTERFACE_LIST1 \r\n\r\n\r\n")
		
		MAKE_��ӿڶ����<MAKE>=MAKE_��ӿڶ����BEGIN#MAKE_��ӿڶ����IMPLEMENT_ARRAY#MAKE_��ӿڶ����MAP_BEGIN#MAKE_��ӿڶ����MAP_ARRAY#MAKE_��ӿڶ����END
		
		MAKE_��������ͷ<MAKE>=Ԥ��������ļ�����#WORD("\r\n#include \"")#COMHOOK�������ļ���#WORD("\"\r\n\r\n")
		MAKE_���������ļ�<MAKE>=WORD("\r\n#include \"")#�ӿ���H�ļ���#WORD("\"\r\n")
		MAKE_���������ļ���<MAKE>=MAKE_N<MAKE_�ӿ���ROOT,MAKE_���������ļ�,MAKE_���������ļ�,MAKE_���������ļ�>
		
		MAKE_��CPP_HookQueryInterfaceͷ<MAKE>=WORD("HRESULT ")#MAKE_COMHOOK��������#WORD("::HookQueryInterface(REFIID riid, void** ppvObj)\r\n{\r\n")
		MAKE_��CPP_HookQueryInterfaceͷ1<MAKE>=WORD("\r\n\tBOOL bFind=FALSE;\r\n\tif(riid==__uuidof(IUnknown))\r\n\t{\r\n\t\treturn S_OK;\r\n\t}")
		MAKE_��CPP_HookQueryInterfaceβ<MAKE>=WORD("\r\n\treturn bFind? S_OK: E_NOINTERFACE;\r\n}\r\n\r\n")
		MAKE_�ӿڰ���ָ��At��Cpp<MAKE>=WORD("((")#�ӿ�����#WORD("<")#MAKE_COMHOOK��������#WORD("> *)this)")
		MAKE_�ӿ�ԭʼָ��At��Cpp<MAKE>=MAKE_�ӿڰ���ָ��At��Cpp#WORD("->")#MAKE_ԭʼ�ӿڶ�����AtROOT
		MAKE_�ӿ�ԭʼIUnKnownָ��At��Cpp<MAKE>=MAKE_�ӿڰ���ָ��At��Cpp#WORD("->m_pIUnknown")
		MAKE_��CPP_HookQueryInterface�ӿڴ���<MAKE>=WORD("else if(riid==__uuidof(")#��������+WORD("))\r\n\t{\r\n\t\t")#MAKE_�ӿ�ԭʼָ��At��Cpp#WORD("=(")#��������#WORD("*)*ppvObj;\r\n\t\t")#MAKE_�ӿ�ԭʼIUnKnownָ��At��Cpp#WORD("=(IUnknown*)*ppvObj;\r\n\t\t*ppvObj=")#MAKE_�ӿڰ���ָ��At��Cpp#WORD(";\r\n\t\tbFind=TRUE;\r\n\t}")
		MAKE_��CPP_HookQueryInterface�ӿڴ����<MAKE>=MAKE_N<MAKE_�ӿ���ROOT,MAKE_��CPP_HookQueryInterface�ӿڴ���,MAKE_��CPP_HookQueryInterface�ӿڴ���,MAKE_��CPP_HookQueryInterface�ӿڴ���>
		MAKE_��CPP_HookQueryInterface<MAKE>=MAKE_��CPP_HookQueryInterfaceͷ#MAKE_��CPP_HookQueryInterfaceͷ1#MAKE_��CPP_HookQueryInterface�ӿڴ����#MAKE_��CPP_HookQueryInterfaceβ
		
		MAKE_��Cpp�ļ�1<MAKE>=MAKE_��������ͷ+MAKE_���������ļ���+MAKE_��CPP_HookQueryInterface
		MAKE_��Cpp�ļ�<MAKE>=MAKE_TO<MAKE_��Cpp�ļ�1,��Cpp�ļ�>
	
	
	//make �ӿ�hook h�ļ�
		
		
		//make COM HOOK ����ͷβ
		MAKE_���⺯��1<MAKE>=WORD("\r\n\tvirtual ")#MAKE_����1
		MAKE_���⺯��2<MAKE>=WORD("\r\n\tvirtual ")#MAKE_����2
		MAKE_���⺯��11<MAKE>=MAKE_����Ҫ�ĺ���|MAKE_���⺯��1
		MAKE_���⺯��22<MAKE>=MAKE_����Ҫ�ĺ���|MAKE_���⺯��2
		//make �ӿ���������
		MAKE���������⺯������1<MAKE>=MAKE_N<MAKE_����ROOT2,MAKE_���⺯��22,MAKE_���⺯��22,MAKE_���⺯��22>&MAKE_N<MAKE_����ROOT1,MAKE_���⺯��11,MAKE_���⺯��11,MAKE_���⺯��11>
		MAKE���������⺯������<MAKE>=WORD("\r\n\t/*=======================")#MAKE_ԭʼ�ӿڶ�������#WORD("�ӿں�������=======================*/\r\n")#MAKE���������⺯������1#WORD("\r\n\r\n\t/*=======================")#MAKE_ԭʼ�ӿڶ�������#WORD("�ӿں������� End=======================*/\r\n\r\n\r\n")
	
		MAKE_ԭʼ�ӿڶ�����AtROOT<MAKE>=WORD("m_p")#������.������1.����
		MAKE_ԭʼ�ӿڶ���ָ������<MAKE>=WORD("ComPointer<")#MAKE_ԭʼ�ӿڶ�������#WORD(">")
		MAKE_ԭʼ�ӿڶ�������<MAKE>=������.������1.����
		MAKE_ԭʼ�ӿ�ָ������<MAKE>=WORD("\r\n\t")#MAKE_ԭʼ�ӿڶ���ָ������+MAKE_ԭʼ�ӿڶ�����AtROOT+WORD(";\r\n")
		
		
		MAKE_�ӿ�H�ļ�ͷ<MAKE>=WORD("\r\n#pragma once\r\n\r\n#include \"common.h\"\r\n\r\n")#WORD("template<typename InterfaceMapBase>\r\n")#WORD("class ")+�ӿ�����#WORD("\r\n")#WORD("\t\t\t: public KcgComHook1\r\n")#WORD("\t\t\t, public")+��������#WORD("\r\n{\r\npublic:\r\n")
		//#WORD("\r\n\t\t\t, public")+�ӿ�������ǰ׺#MAKE_�̳л�����#WORD("<")#�ӿ�����#WORD("<InterfaceMapBase> >\r\n{\r\npublic:\r\n")
		MAKE_�ӿ�H�ļ�β<MAKE>=WORD("};\r\n#include \"")#�ӿ�����#WORD(".cpp\"\r\n")
		
		MAKE_�ӿ�H�ļ�IUNKNOWN<MAKE>=WORD("\r\n\tComPointer<IUnknown> m_pIUnknown;\r\n\r\n\r\n\tvirtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObj);\r\n\r\n\tvirtual ULONG STDMETHODCALLTYPE AddRef();\r\n\r\n\tvirtual ULONG STDMETHODCALLTYPE Release();\r\n\r\n")
		
	//���л��ຯ������
		MAKE_�̳л�����<MAKE>=������.������1.�̳л�����.������
		MAKE_���ü̳л�����MAKE<MAKE>=WORD("MAKE_�̳л�����<MAKE>=WORD(\"")#������.������1.�̳л�����.������#WORD("\")")
		MAKE_���ü̳л�����<MAKE>=DEBUGOUT<"MAKE_���ü̳л�����MAKE">+DEBUGOUT<MAKE_���ü̳л�����MAKE>+MAKE_ADD<MAKE_���ü̳л�����MAKE>
		MAKE_�̳л���ROOTPATH<MAKE>=WORD("Hello world")
		MAKE_TMPROOTPATH<MAKE>=WORD("Hello world")
		MAKE_�̳л���ROOTPATH_MAKE<MAKE>=WORD("MAKE_�̳л���ROOTPATH<MAKE>=ROOTROOT.ROOT.������.������1.")#MAKE_�̳л�����#WORD(".PARENT.PARENT.PARENT")
		
		MAKE_���ü̳л������·��<MAKE_SET>=DEBUGOUT<"MAKE_���ü̳л������·��">&MAKE_���ü̳л�����+MAKE_ADD<MAKE_�̳л���ROOTPATH_MAKE>
	
	
		MAKE_��ǰ��·����<MAKE>=WORD("Hello world")
		MAKE_��ǰ����<MAKE>=WORD("Hello world")
		MAKE_��ǰ������<MAKE>=WORD("Hello world")
		MAKE_�̳������ຯ����1ROOT<MAKE>=WORD("Hello world")
		MAKE_�̳������ຯ����2ROOT<MAKE>=WORD("Hello world")
		MAKE_�̳������ຯ����1<MAKE>=DEBUGOUT<"MAKE_�̳������ຯ����1">+WORD("MAKE_�̳������ຯ����1ROOT<MAKE>=")#MAKE_��ǰ��·����#WORD(".")#MAKE_����ROOT1_MAKE#WORD(".")#MAKE_��ǰ������
		MAKE_�̳������ຯ����2<MAKE>=DEBUGOUT<"MAKE_�̳������ຯ����2">+WORD("MAKE_�̳������ຯ����2ROOT<MAKE>=")#MAKE_��ǰ��·����#WORD(".")#MAKE_����ROOT2_MAKE#WORD(".")#MAKE_��ǰ������
		
		MAKE_��ǰ�ຯ����ROOT_MAKE<MAKE>=WORD("MAKE_��ǰ������<MAKE>=WORD(\"������.")#O.������#WORD("\")")
		MAKE_�����Ƿ��ڼ̳�������1<MAKE>=DEBUGOUT<MAKE_��ǰ�ຯ����ROOT_MAKE>+MAKE_ADD<MAKE_��ǰ�ຯ����ROOT_MAKE>+MAKE_ADD<MAKE_�̳������ຯ����1>+DEBUGOUT<MAKE_�̳������ຯ����1>+DEBUGOUT<MAKE_�̳������ຯ����1ROOT>+MAKE_�̳������ຯ����1ROOT
		MAKE_�����Ƿ��ڼ̳�������2<MAKE>=DEBUGOUT<MAKE_��ǰ�ຯ����ROOT_MAKE>+MAKE_ADD<MAKE_��ǰ�ຯ����ROOT_MAKE>+MAKE_ADD<MAKE_�̳������ຯ����2>+DEBUGOUT<MAKE_�̳������ຯ����2>+DEBUGOUT<MAKE_�̳������ຯ����2ROOT>+MAKE_�̳������ຯ����2ROOT
		
		
		MAKE_��ǰ��ROOT_MAKE<MAKE>=DEBUGOUT<"MAKE_��ǰ��ROOT_MAKE">+WORD("MAKE_��ǰ��·����<MAKE>=WORD(\"ROOTROOT.ROOT.������.������1.")#MAKE_��ǰ����#WORD(".PARENT.PARENT.PARENT\")")

		MAKE_���õ�ǰ����MAKE<MAKE>=WORD("MAKE_��ǰ����<MAKE>=WORD(\"")#��������#WORD("\")")
		MAKE_���õ�ǰ����<MAKE>=DEBUGOUT<"MAKE_���õ�ǰ����">+DEBUGOUT<MAKE_���õ�ǰ����MAKE>+MAKE_ADD<MAKE_���õ�ǰ����MAKE>
		MAKE_���õ�ǰ�����·��<MAKE_SET>=DEBUGOUT<"MAKE_���õ�ǰ�����·��">+DEBUGOUT<MAKE_��ǰ��ROOT_MAKE>+DEBUGOUT<"MAKE_���õ�ǰ����">+DEBUGOUT<MAKE_���õ�ǰ����>+MAKE_���õ�ǰ����+MAKE_ADD<MAKE_��ǰ��ROOT_MAKE>
		
		MAKE_�ظ��̳еĺ���<MAKE_CHECK>=NOT<MAKE_�ظ��̳еĺ���1>
		//NOT<MAKE_����Ҫ�ĺ���>|
		MAKE_�������⺯��11<MAKE>=DEBUGOUT<"MAKE_�������⺯��11">+IF<MAKE_�����Ƿ��ڼ̳�������1>|MAKE_���⺯��1
		MAKE_�������⺯��22<MAKE>=DEBUGOUT<"MAKE_�������⺯��22">+IF<MAKE_�����Ƿ��ڼ̳�������2>|MAKE_���⺯��2
		MAKE�������������⺯������1<MAKE>=DEBUGOUT<"MAKE�������������⺯������1">&MAKE_N<MAKE_����ROOT2,MAKE_�������⺯��22,MAKE_�������⺯��22,MAKE_�������⺯��22>&DEBUGOUT<"MAKE�������������⺯������111">&MAKE_N<MAKE_����ROOT1,MAKE_�������⺯��11,MAKE_�������⺯��11,MAKE_�������⺯��11>
		
		MAKE�������������⺯������2<MAKE>=MAKE_ONE<MAKE_�̳л���ROOTPATH,MAKE�������������⺯������1>#WORD(" ")
		MAKE�������������⺯������<MAKE>=MAKE_���õ�ǰ�����·��&MAKE_���ü̳л������·��&WORD("\r\n\t/*=======================")#MAKE_�̳л�����#WORD("�ӿں�������=======================*/\r\n")#MAKE�������������⺯������2#WORD("\r\n\r\n\t/*=======================")#MAKE_�̳л�����#WORD("�ӿں������� End=======================*/\r\n\r\n\r\n")
	
	
		MAKE_�ӿ�H�ļ���<MAKE>=MAKE_�ӿ�H�ļ�ͷ#MAKE_�ӿ�H�ļ�IUNKNOWN#MAKE_ԭʼ�ӿ�ָ������&MAKE���������⺯������&MAKE�������������⺯������&MAKE_�ӿ�H�ļ�β
		MAKE_�ӿ�H�ļ�1<MAKE>=MAKE_TO<MAKE_�ӿ�H�ļ���,�ӿ���H�ļ�����·��>
		//make ���нӿ�
		MAKE_�ӿ�H�ļ�<MAKE>=MAKE_N<MAKE_�ӿ���ROOT,MAKE_�ӿ�H�ļ�1,MAKE_�ӿ�H�ļ�1,MAKE_�ӿ�H�ļ�1>
	
		
	//make �ӿ� hook cpp�ļ�	

		
		MAKE_�ӿں�������ͷ1<MAKE>=WORD("template<typename InterfaceMapBase>\r\n")#WORD(HRESULT)&�ӿں�����������#WORD("<InterfaceMapBase>::")#O.������#WORD(()&MAKE_����������&WORD())#WORD("\r\n")
		MAKE_�ӿں�������ͷ2<MAKE>=WORD("template<typename InterfaceMapBase>\r\n")#MAKE_����2���ز���&�ӿں�����������#WORD("<InterfaceMapBase>::")#O.������#WORD(()&MAKE_����������&WORD())#WORD("\r\n")
		MAKE_�ӿں�������1<MAKE>=WORD("\r\n")#MAKE_�ӿں�������ͷ1#WORD("{\r\n\t return ")+MAKE_ԭʼ�ӿڶ���#WORD("->")#MAKE_��������+WORD(";\r\n}\r\n")
		MAKE_�ӿں�������2<MAKE>=WORD("\r\n")#MAKE_�ӿں�������ͷ2#WORD("{\r\n\t return ")+MAKE_ԭʼ�ӿڶ���#WORD("->")#MAKE_��������+WORD(";\r\n}\r\n")
		
		MAKE_�ӿں�������11<MAKE>=MAKE_����Ҫ�ĺ���|MAKE_�ӿں�������1
		MAKE_�ӿں�������22<MAKE>=MAKE_����Ҫ�ĺ���|MAKE_�ӿں�������2
		
		
		
		//make ���нӿ���������
		MAKE_�ӿں��������1<MAKE>=MAKE_N<MAKE_����ROOT2,MAKE_�ӿں�������22,MAKE_�ӿں�������22,MAKE_�ӿں�������22>&MAKE_N<MAKE_����ROOT1,MAKE_�ӿں�������11,MAKE_�ӿں�������11,MAKE_�ӿں�������11>
		
		//make ���ຯ��
		MAKE_����ӿں�������ͷ1<MAKE>=WORD("template<typename InterfaceMapBase>\r\n")#WORD(HRESULT)&�ӿ�������ǰ׺#MAKE_��ǰ����#WORD("<InterfaceMapBase>::")#O.������#WORD(()&MAKE_����������&WORD())#WORD("\r\n")
		MAKE_����ӿں�������ͷ2<MAKE>=WORD("template<typename InterfaceMapBase>\r\n")#MAKE_����2���ز���&�ӿ�������ǰ׺#MAKE_��ǰ����#WORD("<InterfaceMapBase>::")#O.������#WORD(()&MAKE_����������&WORD())#WORD("\r\n")
		MAKE_����ӿں�������1<MAKE>=WORD("\r\n")#MAKE_����ӿں�������ͷ1#WORD("{\r\n\t return ")+MAKE_�̳�������ԭʼ�ӿڶ���#WORD("->")#MAKE_��������+WORD(";\r\n}\r\n")
		MAKE_����ӿں�������2<MAKE>=WORD("\r\n")#MAKE_����ӿں�������ͷ2#WORD("{\r\n\t return ")+MAKE_�̳�������ԭʼ�ӿڶ���#WORD("->")#MAKE_��������+WORD(";\r\n}\r\n")
		
		MAKE_����ӿں�������11<MAKE>=MAKE_����Ҫ�ĺ���&IF<MAKE_�����Ƿ��ڼ̳�������1>|MAKE_����ӿں�������1
		MAKE_����ӿں�������22<MAKE>=MAKE_����Ҫ�ĺ���&IF<MAKE_�����Ƿ��ڼ̳�������2>|MAKE_����ӿں�������2
		MAKE_����ӿں��������1<MAKE>=DEBUGOUT<"MAKE_����ӿں��������1">&MAKE_N<MAKE_����ROOT2,MAKE_����ӿں�������22,MAKE_����ӿں�������22,MAKE_����ӿں�������22>&MAKE_N<MAKE_����ROOT1,MAKE_����ӿں�������11,MAKE_����ӿں�������11,MAKE_����ӿں�������11>
		MAKE_����ӿں��������<MAKE>=MAKE_���õ�ǰ�����·��&MAKE_���ü̳л������·��&MAKE_ONE<MAKE_�̳л���ROOTPATH,MAKE_����ӿں��������1>#WORD(" ")
		
		MAKE_�ӿ�CPPͷ<MAKE>=Ԥ��������ļ�����#WORD("\r\n#include \"common.h\"\r\n")#WORD("\r\n#include \"")#�ӿ���H�ļ���#WORD("\"\r\n\r\n")
		
		MAKE_�ӿ�CPPIUNKNOWN1<MAKE>=WORD("\r\ntemplate<typename InterfaceMapBase>\r\n")#WORD("HRESULT ")#�ӿ�����#WORD("<InterfaceMapBase>::")#WORD("QueryInterface(REFIID riid, void** ppvObj)")#WORD("\r\n{\r\n\t*ppvObj=NULL;\r\n")#WORD("\r\n\tif(riid==__uuidof(IUnknown))\r\n\t{\r\n\t\t*ppvObj=(IUnknown*)(")#��������#WORD(" *)this;\r\n\t\treturn S_OK;\r\n\t}")#WORD("\r\n\tHRESULT rst=m_pIUnknown->QueryInterface(riid, ppvObj);\r\n\tif(rst==S_OK)\r\n\t{\r\n\t\trst=GETPARENTCLASS(InterfaceMapBase,")#�ӿ�����#WORD(",this)->HookQueryInterface(riid, ppvObj);\r\n\t}\r\n\treturn ppvObj != NULL? S_OK: E_NOINTERFACE;\r\n}\r\n\r\n")
		MAKE_�ӿ�CPPIUNKNOWN2<MAKE>=WORD("\r\ntemplate<typename InterfaceMapBase>\r\n")#WORD("ULONG ")#�ӿ�����#WORD("<InterfaceMapBase>::")#WORD("AddRef()")#WORD("\r\n{\r\n\treturn m_pIUnknown->AddRef();\r\n\}\r\n")
		MAKE_�ӿ�CPPIUNKNOWN3<MAKE>=WORD("\r\ntemplate<typename InterfaceMapBase>\r\n")#WORD("ULONG ")#�ӿ�����#WORD("<InterfaceMapBase>::")#WORD("Release()")#WORD("\r\n{\r\n\treturn m_pIUnknown->Release();\r\n\}\r\n")

		MAKE_�ӿ�CPPIUNKNOWN4<MAKE>=WORD("\r\ntemplate<typename InterfaceMapBase>\r\n")#WORD("HRESULT ")#�ӿ�����#WORD("<InterfaceMapBase>::")#WORD("HookQueryInterface(REFIID riid, void** ppvObj)")#WORD("\r\n{\r\n\tHRESULT rst=GETPARENTCLASS(InterfaceMapBase,")#�ӿ�����#WORD(",this)->HookQueryInterface(riid, ppvObj);\r\n\treturn ppvObj != NULL? S_OK: E_NOINTERFACE;\r\n}\r\n\r\n")
		

		MAKE_�ӿ�CPP��<MAKE>=MAKE_�ӿ�CPPIUNKNOWN1#MAKE_�ӿ�CPPIUNKNOWN2#MAKE_�ӿ�CPPIUNKNOWN3#MAKE_�ӿں��������1#MAKE_����ӿں��������
		//#MAKE_�ӿں��������1#MAKE_����ӿں��������
		MAKE_�ӿ�CPP1<MAKE>=MAKE_TO<MAKE_�ӿ�CPP��,�ӿ�������·��>
		//make ���нӿ�
		MAKE_�ӿ�CPP<MAKE>=MAKE_N<MAKE_�ӿ���ROOT,MAKE_�ӿ�CPP1,MAKE_�ӿ�CPP1,MAKE_�ӿ�CPP1>
	
	
	//����Ԫ����
	//COM HOOK ��������
	��Cpp�ļ�<MAKE>=�����ļ���Ŀ¼#MAKE_COMHOOK��������#WORD(".cpp")
	MAKE_COMHOOK��������<MAKE>=WORD("ComHookPacketBase")
	�����ļ���Ŀ¼<MAKE>=WORD("c:\\dx89\\")
	��������<MAKE>=������.������1.����
	������CPP�ļ���<MAKE>=��������#WORD(".cpp")
	������H�ļ���<MAKE>=��������#WORD(".h")
	���ݻ���CPP�ļ���<MAKE>=MAKE_COMHOOK��������#WORD("_")#������CPP�ļ���
	���ݻ���������·��<MAKE>=�����ļ���Ŀ¼#���ݻ���CPP�ļ���
	COMHOOK�������ļ���<MAKE>=MAKE_COMHOOK��������#WORD(".h")
	COMHOOK����������·��<MAKE>=�����ļ���Ŀ¼#COMHOOK�������ļ���
	
	Ԥ��������ļ�����<MAKE>=WORD("\r\n#include \"stdafx.h\"\r\n\r\n")
	�ӿ�������ǰ׺<MAKE>=WORD("ComHook_")
	�ӿ���H�ļ���<MAKE>=�ӿ�������ǰ׺#������H�ļ���
	�ӿ���CPP�ļ���<MAKE>=�ӿ�������ǰ׺#������CPP�ļ���
	�ӿ�������·��<MAKE>=�����ļ���Ŀ¼#�ӿ���CPP�ļ���
	
	�ӿ���H�ļ�����·��<MAKE>=�����ļ���Ŀ¼#�ӿ���H�ļ���
	�ӿ�����<MAKE>=�ӿ�������ǰ׺#��������
	�ӿں�����������<MAKE>=�ӿ�������ǰ׺#MAKE_������������ROOT
	
	//make��
	//������·��
	//MAKE_�ӿ�H�ļ�+MAKE_�ӿ�CPP+MAKE_��Cpp�ļ�+MAKE_COMHOOKHPPXX+MAKE_COMHOOKCPP3
	MAKE_HPP_CPP<MAKE>=MAKE_�ӿ�H�ļ�+MAKE_�ӿ�CPP+MAKE_��Cpp�ļ�+MAKE_COMHOOKHPPXX
	
	
	
	
	
	
	
	