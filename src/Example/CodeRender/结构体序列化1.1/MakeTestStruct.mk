MAKEINCLUDE="E:\\�׺в���\\me\\CodeRender\\�ṹ�����л�1.1\\structtree.mk"
MAKEINCLUDE="E:\\�׺в���\\me\\CodeRender\\�ṹ�����л�1.1\\�ṹԤ�����﷨��.mk"
MAKEINCLUDE="E:\\�׺в���\\me\\CodeRender\\�ṹ�����л�1.1\\�ṹԤ����MAKE.mk"

ROOT<����>=�ṹ����|Ԥ��������


MAKE_HPP<MAKE>=MAKE_TO<MAKE_HPP_CPP,�ӿ�������·��>
�ӿ�������·��<MAKE>=�����ļ���Ŀ¼#WORD("StructInfo_")#������H�ļ���


//����Ԫ����
	//COM HOOK ��������
	��Cpp�ļ�<MAKE>=�����ļ���Ŀ¼#MAKE_COMHOOK��������#WORD(".cpp")
	MAKE_COMHOOK��������<MAKE>=WORD("ComHookPacketBase")
	�����ļ���Ŀ¼<MAKE>=WORD("E:\\�׺в���\\svn\\project\\project_AutoEvaluate\\AutoEvaluate\\AutoEvaluate\\ObjectSerDef\\")	
	��������<MAKE>=��������1|��������2
	��������1<MAKE>=�ṹ����.�ṹ����1.�ṹ����
	��������2<MAKE>=�ṹ����.�ṹ����2.�ṹ����
	
	������CPP�ļ���<MAKE>=��������#WORD(".cpp")
	������H�ļ���<MAKE>=��������#WORD(".h")
	COMHOOK�������ļ���<MAKE>=MAKE_COMHOOK��������#WORD(".h")
	COMHOOK����������·��<MAKE>=�����ļ���Ŀ¼#COMHOOK�������ļ���
	
	Ԥ��������ļ�����<MAKE>=WORD("\r\n#include \"stdafx.h\"\r\n\r\n")
	
	
	
ROOT_MAKE<ROOT_MAKE>=MAKE_HPP_CPP

