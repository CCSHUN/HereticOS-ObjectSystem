#pragma once
#include "stdafx.h"
#include "TestConfig.h"


//阶乘

//等差求和
#define SumGrade(_a1,_d,_n) (_n*_a1+((_n*(_n-1)*_d)/2))
class TestLibDataMode
{
public:
	_tagExpLib		m_ExpLib;
	_tagFuncLib		m_FuncLib;
	map<tstring ,int,less<tstring>> m_LibMgr;
	tstring m_szCurLib;

	

	BOOL m_bNewUpdataExp;
	BOOL m_bNeedSave;
	TestLibDataMode(){m_bNewUpdataExp=FALSE;m_bNeedSave=FALSE;};
	~TestLibDataMode(){};

private:
	IDType GetNewFuncID()
	{
		/*if(m_FuncLib.tidRecover.tIDRecover.size())
		{
			unsigned int id=m_FuncLib.tidRecover.tIDRecover.front();
			m_FuncLib.tidRecover.tIDRecover.pop_front();
			return id;
		}*/
		return ++m_FuncLib.tidRecover.nID;
	}
	IDType GetNewExpID()
	{
		/*if(m_ExpLib.tidRecover.tIDRecover.size())
		{
			unsigned int id=m_ExpLib.tidRecover.tIDRecover.front();
			m_ExpLib.tidRecover.tIDRecover.pop_front();
			return id;
		}*/
		return ++m_ExpLib.tidRecover.nID;
	}

	IDType GetNewFuncParamID(_tagFuncDef &Func)
	{
		/*if(Func.tParamidRecover.tIDRecover.size())
		{
			unsigned int id=Func.tParamidRecover.tIDRecover.front();
			Func.tParamidRecover.tIDRecover.pop_front();
			return id;
		}*/
		return ++Func.tParamidRecover.nID;
	}
	BOOL Load(tstring & szLibName,_tagExpLib & explib,_tagFuncLib & func)
	{
		tstring szAddrFunc=tstring(_T("CodeTest\\_Func_"))+szLibName;
		_tagFuncLib_Wrap funclib;
		funclib.m_szAddr=szAddrFunc;
		if(funclib.GetObject())
		{
			func=funclib.m_Data;
		}else
		{
			return FALSE;
		}

		tstring szAddrExp=tstring(_T("CodeTest\\_Exp_"))+szLibName;
		_tagExpLib_Wrap exp;
		exp.m_szAddr=szAddrExp;
		if(exp.GetObject())
		{
			explib=exp.m_Data;
		}else
		{
			return FALSE;
		}

		return TRUE;
	}
	

	BOOL Save(tstring & szLibName,_tagExpLib & explib,_tagFuncLib & func)
	{
		UpdataLib();
		tstring szAddrFunc=tstring(_T("CodeTest\\_Func_"))+szLibName;
		_tagFuncLib_Wrap funclib;
		funclib.m_szAddr=szAddrFunc;
		funclib.m_Data=func;
		if(funclib.UpDataObject()==FALSE)
		{
			return FALSE;
		}

		tstring szAddrExp=tstring(_T("CodeTest\\_Exp_"))+szLibName;
		_tagExpLib_Wrap exp;
		exp.m_szAddr=szAddrExp;
		exp.m_Data=explib;
		if(exp.UpDataObject()==FALSE)
		{
			return FALSE;
		}
		return TRUE;
	}

	tstring GetFuncDefStringFromFunc(map<tstring,_tagFuncDef,less<tstring> >::iterator & itFunc)
	{
		if(m_FuncLib.m_FuncLib.end()==itFunc) return tstring(_T("NULL()"));


		vector<_tagParamDef> & ParamDefArray=itFunc->second.m_ParamDefArray;

		tstring szRet=itFunc->first;
		szRet+=_T("(");

		unsigned int i=0;
		for(;i<ParamDefArray.size();i++)
		{
			szRet+=ParamDefArray[i].szParamName;
			szRet+=_T(",");
		}
		if(i)
		{
			szRet[szRet.length()-1]=_T(')');
		}else
		{
			szRet+=_T(")");
		}

		return szRet;
	}

	//通过ID查找Func
	BOOL GetFuncByFuncID(IDType nID,OUT map<tstring,_tagFuncDef,less<tstring> >::iterator & itFunc)
	{
		//map<tstring,_tagFuncDef,less<tstring> >::iterator 
		itFunc=m_FuncLib.m_FuncLib.begin();
		for(;itFunc!=m_FuncLib.m_FuncLib.end();itFunc++)
		{
			if(itFunc->second.nFuncID==nID)
			{
				//Func=itFunc->second;
				return TRUE;
			}
		}
		return FALSE;
	}


	map<tstring,_tagFuncDef,less<tstring> >::iterator FindFuncByFuncID(IDType nID)
	{
		map<tstring,_tagFuncDef,less<tstring> >::iterator itFunc=m_FuncLib.m_FuncLib.begin();
		for(;itFunc!=m_FuncLib.m_FuncLib.end();itFunc++)
		{
			if(itFunc->second.nFuncID==nID)
			{
				//Func=itFunc->second;
				return itFunc;
			}
		}
		return itFunc;
	}

public:

	
	
	

	BOOL GetFuncByFuncID(IDType nID,OUT _tagFuncDef & Func)
	{
		map<tstring,_tagFuncDef,less<tstring> >::iterator  itFunc=m_FuncLib.m_FuncLib.begin();
		for(;itFunc!=m_FuncLib.m_FuncLib.end();itFunc++)
		{
			if(itFunc->second.nFuncID==nID)
			{
				Func=itFunc->second;
				return TRUE;
			}
		}
		return FALSE;
	}

	BOOL FuncParamIsReDef(IDType nFuncID,tstring & szParamName)
	{
		_tagFuncDef Func;
		if(GetFuncByFuncID(nFuncID,Func))
		{
			for(unsigned int i=0;i<Func.m_ParamDefArray.size();i++)
			{
				if(szParamName==Func.m_ParamDefArray[i].szParamName)
				{
					return TRUE;
				}
			}
		}
		return FALSE;
		
	}
	
	BOOL AddNewFuncParam(IDType nFuncID,_tagParamDef & Param)
	{
		if(FuncParamIsReDef(nFuncID,Param.szParamName)==FALSE)
		{
			map<tstring,_tagFuncDef,less<tstring> >::iterator  itFunc;
			if(GetFuncByFuncID(nFuncID,itFunc))
			{
				Param.nParamID=GetNewFuncParamID(itFunc->second);
				itFunc->second.m_ParamDefArray.push_back(Param);
				return TRUE;
			}
			
		}
		
		return TRUE;
	}
	BOOL DelFuncParam(IDType nFuncID,tstring & szParamName)
	{
		map<tstring,_tagFuncDef,less<tstring> >::iterator  itFunc;
		if(GetFuncByFuncID(nFuncID,itFunc))
		{
			vector<_tagParamDef>::iterator itPar=itFunc->second.m_ParamDefArray.begin();
			for(;itPar!=itFunc->second.m_ParamDefArray.end();itPar++)
			{
				if(itPar->szParamName==szParamName)
				{
					itFunc->second.tParamidRecover.tIDRecover.push_back(itPar->nParamID);
					itFunc->second.m_ParamDefArray.erase(itPar);
					return TRUE;
				}
			}
		}
		return FALSE;
	}
	BOOL UpdataFuncParam(IDType nFuncID,_tagParamDef & Param)
	{

		map<tstring,_tagFuncDef,less<tstring> >::iterator  itFunc;
		if(GetFuncByFuncID(nFuncID,itFunc))
		{
			vector<_tagParamDef>::iterator itPar=itFunc->second.m_ParamDefArray.begin();
			for(;itPar!=itFunc->second.m_ParamDefArray.end();itPar++)
			{
				if(itPar->nParamID==Param.nParamID)
				{
					*itPar=Param;
					return TRUE;
				}
			}
		}
		return FALSE;
	}

	BOOL GetFuncParamByParName(IDType nFuncID,tstring & szParName,OUT _tagParamDef & Param)
	{
		map<tstring,_tagFuncDef,less<tstring> >::iterator  itFunc;
		if(GetFuncByFuncID(nFuncID,itFunc))
		{
			vector<_tagParamDef>::iterator itPar=itFunc->second.m_ParamDefArray.begin();
			for(;itPar!=itFunc->second.m_ParamDefArray.end();itPar++)
			{
				if(itPar->szParamName==szParName)
				{
					Param=*itPar;
					return TRUE;
				}
			}
		}
		return FALSE;
	}

	BOOL GetFuncParamByParID(IDType nFuncID,IDType nParamID,OUT _tagParamDef & Param)
	{
		map<tstring,_tagFuncDef,less<tstring> >::iterator  itFunc;
		if(GetFuncByFuncID(nFuncID,itFunc))
		{
			vector<_tagParamDef>::iterator itPar=itFunc->second.m_ParamDefArray.begin();
			for(;itPar!=itFunc->second.m_ParamDefArray.end();itPar++)
			{
				if(itPar->nParamID==nParamID)
				{
					Param=*itPar;
					return TRUE;
				}
			}
		}
		return FALSE;
	}


	BOOL GetFuncByFuncName(tstring & FuncName,OUT _tagFuncDef & Func)
	{
		map<tstring,_tagFuncDef,less<tstring> >::iterator itFunc=m_FuncLib.m_FuncLib.begin();
		for(;itFunc!=m_FuncLib.m_FuncLib.end();itFunc++)
		{
			if(itFunc->second.szFuncName==FuncName)
			{
				Func=itFunc->second;
				return TRUE;
			}
		}
		return FALSE;
	}

	tstring GetFuncNameByFuncID(IDType nID)
	{
		map<tstring,_tagFuncDef,less<tstring> >::iterator itFunc=m_FuncLib.m_FuncLib.begin();
		for(;itFunc!=m_FuncLib.m_FuncLib.end();itFunc++)
		{
			if(itFunc->second.nFuncID==nID)
			{
				return itFunc->first;
			}
		}
		return tstring(_T("NULL"));
	}

	IDType GetFuncIDByName(tstring & szFuncName)
	{
		map<tstring,_tagFuncDef,less<tstring> >::iterator itFunc=m_FuncLib.m_FuncLib.begin();
		for(;itFunc!=m_FuncLib.m_FuncLib.end();itFunc++)
		{
			if(itFunc->second.szFuncName==szFuncName)
			{
				return itFunc->second.nFuncID;
			}
		}
		return 0;
	}

	
	BOOL AddNewFunc(_tagFuncDef & Func)
	{
	
		if(Func.szFuncName.length()==0)
		{
			return FALSE;
		}else if(m_FuncLib.m_FuncLib.find(Func.szFuncName)!=m_FuncLib.m_FuncLib.end())
		{
			return FALSE;
		}
		Func.tParamidRecover.nID=0;
		Func.nFuncID=GetNewFuncID();
		m_FuncLib.m_FuncLib[Func.szFuncName]=Func;
		return TRUE;
	}

	//通过ID更新Func
	BOOL UpDataFuncByID(IDType nID,IN _tagFuncDef & Func)
	{
		
		_tagFuncDef  FindFunc;
		if(GetFuncByFuncName(Func.szFuncName,FindFunc))
		{
			if (FindFunc.nFuncID!=Func.nFuncID)
			{
				//名字不能与其它表达式重复
				return FALSE;
			}
		}
		map<tstring,_tagFuncDef,less<tstring> >::iterator itFunc=m_FuncLib.m_FuncLib.begin();
		for(;itFunc!=m_FuncLib.m_FuncLib.end();itFunc++)
		{
			if(itFunc->second.nFuncID==nID)
			{
				//itFunc->second=Func;
				//itFunc->first=Func.szFuncName;
				m_FuncLib.m_FuncLib.erase(itFunc);
				m_FuncLib.m_FuncLib[Func.szFuncName]=Func;
				return TRUE;
			}
		}
		return FALSE;
	}

	BOOL DelFuncByName(tstring & FuncName)
	{
		map<tstring,_tagFuncDef,less<tstring> >::iterator itFunc=m_FuncLib.m_FuncLib.find(FuncName);
		if(itFunc!=m_FuncLib.m_FuncLib.end())
		{
			m_FuncLib.tidRecover.tIDRecover.push_back(itFunc->second.nFuncID);
			m_FuncLib.m_FuncLib.erase(itFunc);
			return TRUE;
		}
		return FALSE;
	}


	BOOL ExpIsReDef(tstring & expName)
	{
		if(m_ExpLib.m_ExpLib.find(expName)!=m_ExpLib.m_ExpLib.end())
		{
			return TRUE;
		}
		return FALSE;
	}

	BOOL AddNewExp(_tagExp &exp)
	{
		if(ExpIsReDef(exp.szExpName)==FALSE)
		{
			exp.nExpID=GetNewExpID();
			m_ExpLib.m_ExpLib[exp.szExpName]=exp;
			return TRUE;
		}
		return FALSE;
	}
	BOOL DelExpByID(IDType nExpID)
	{
		//for_each(m_ExpLib.m_ExpLib.begin(),m_ExpLib.m_ExpLib.end())
		map<tstring,_tagExp,less<tstring>>::iterator itExp=m_ExpLib.m_ExpLib.begin();
		for(;itExp!=m_ExpLib.m_ExpLib.end();itExp++)
		{
			if(itExp->second.nExpID==nExpID)
			{
				m_ExpLib.m_ExpLib.erase(itExp);
				return TRUE;
			}
		}
		return FALSE;
	}
	BOOL UpDataExp(IDType nExpID,_tagExp & exp)
	{
		_tagExp  FindExp;
		if(GetExpByName(FindExp.szExpName,FindExp))
		{
			if (FindExp.szExpName!=exp.szExpName)
			{
				//名字不能与其它表达式重复
				return FALSE;
			}
		}

		map<tstring,_tagExp,less<tstring>>::iterator itExp=m_ExpLib.m_ExpLib.begin();
		for(;itExp!=m_ExpLib.m_ExpLib.end();itExp++)
		{
			if(itExp->second.nExpID==nExpID)
			{
				//itExp->first=exp.szExpName;
				m_ExpLib.m_ExpLib.erase(itExp);
				m_ExpLib.m_ExpLib[exp.szExpName]=exp;
				return TRUE;
			}
		}
		return FALSE;
	}
	BOOL GetExpByName(tstring & szExpName,_tagExp & exp)
	{
		map<tstring,_tagExp,less<tstring>>::iterator itExp=m_ExpLib.m_ExpLib.find(szExpName);
		if(itExp!=m_ExpLib.m_ExpLib.end())
		{
			exp=itExp->second;
			return TRUE;
		}
		return FALSE;

	}
	BOOL GetExp(IDType nExpID,_tagExp & exp)
	{
		map<tstring,_tagExp,less<tstring>>::iterator itExp=m_ExpLib.m_ExpLib.begin();
		for(;itExp!=m_ExpLib.m_ExpLib.end();itExp++)
		{
			if(itExp->second.nExpID==nExpID)
			{
				exp=itExp->second;
				return TRUE;
			}
		}
		return FALSE;
	}

	tstring GetExpNameByID(IDType nExpID)
	{
		map<tstring,_tagExp,less<tstring>>::iterator itExp=m_ExpLib.m_ExpLib.begin();
		for(;itExp!=m_ExpLib.m_ExpLib.end();itExp++)
		{
			if(itExp->second.nExpID==nExpID)
			{
				//exp=itExp->first;
				return itExp->second.szExpName;
			}
		}
		return tstring(_T("NULL"));
	}


	BOOL UpDataExpPar(IDType nExpID,IDType nFuncID,_tagParamDef & ExpFuncPar)
	{
		map<tstring,_tagExp,less<tstring>>::iterator itExp=m_ExpLib.m_ExpLib.begin();
		for(;itExp!=m_ExpLib.m_ExpLib.end();itExp++)
		{
			if(itExp->second.nExpID==nExpID)
			{
				map<IDType,vector<_tagParamDef>,less<IDType>>::iterator itFunc=itExp->second.m_ExpValMap.find(nFuncID);
				if(itFunc!=itExp->second.m_ExpValMap.end())
				{
					for(unsigned int i=0;i<itFunc->second.size();i++)
					{
						if(ExpFuncPar.nParamID==itFunc->second[i].nParamID)
						{
							itFunc->second[i]=ExpFuncPar;
							return TRUE;
						}
					}
				}
				
			}
		}
		return FALSE;
	}

	BOOL GetExpPar(IDType nExpID,IDType nFuncID,_tagParamDef & ExpFuncPar)
	{
		map<tstring,_tagExp,less<tstring>>::iterator itExp=m_ExpLib.m_ExpLib.begin();
		for(;itExp!=m_ExpLib.m_ExpLib.end();itExp++)
		{
			if(itExp->second.nExpID==nExpID)
			{
				map<IDType,vector<_tagParamDef>,less<IDType>>::iterator itFunc=itExp->second.m_ExpValMap.find(nFuncID);
				if(itFunc!=itExp->second.m_ExpValMap.end())
				{
					for(unsigned int i=0;i<itFunc->second.size();i++)
					{
						if(ExpFuncPar.nParamID==itFunc->second[i].nParamID)
						{
							ExpFuncPar=itFunc->second[i];
							return TRUE;
						}
					}
				}

			}
		}
		return FALSE;
	}


	//功能库修改参数定义后 重新规整调用表达式的表达式
	void UpdataLib()
	{
		if(m_bNewUpdataExp==FALSE) return;

		m_bNewUpdataExp=FALSE;
		m_bNeedSave=TRUE;

		map<tstring,_tagFuncDef,less<tstring> >::iterator itFunc;
		map<tstring,_tagExp,less<tstring>>::iterator itExp;
		for (itExp=m_ExpLib.m_ExpLib.begin();itExp!=m_ExpLib.m_ExpLib.end();itExp++)
		{
			for(unsigned int s=0;s<itExp->second.FuncIDArray.size();s++)
			{
				//if(FindFuncByFuncID(itExp->second.FuncIDArray[s])==m_FuncLib.m_FuncLib.end())
				//{
				//	continue;
				//}
				itFunc=FindFuncByFuncID(itExp->second.FuncIDArray[s]);
				if(itFunc==m_FuncLib.m_FuncLib.end())
				{
					vector<IDType>::iterator it1=itExp->second.FuncIDArray.begin();
					it1+=s;
					IDType nFuncID=itExp->second.FuncIDArray[s];
					//vector<_tagParamDef>::iterator it2=itExp->second.m_ExpValMap.begin();
					//it2+=s;
					//清除 exp中无效的func
					itExp->second.FuncIDArray.erase(it1);
					itExp->second.m_ExpValMap.erase(nFuncID);
					
				}else
				{

					//调整参数列表
					vector<_tagParamDef> & ExpFuncPar=itExp->second.m_ExpValMap.find(itExp->second.FuncIDArray[s])->second;
					for(unsigned int i=0;i<itFunc->second.m_ParamDefArray.size();i++)
					{
						if(itFunc->second.m_ParamDefArray.size()>ExpFuncPar.size()) 
						{
							ExpFuncPar.resize(itFunc->second.m_ParamDefArray.size());
						}
						if(itFunc->second.m_ParamDefArray[i].nParamID==ExpFuncPar[i].nParamID)
						{
							//位置字段正确
							ExpFuncPar[i].szDefaultParam=itFunc->second.m_ParamDefArray[i].szDefaultParam;
							ExpFuncPar[i].szParamAttribute=itFunc->second.m_ParamDefArray[i].szParamAttribute;
							ExpFuncPar[i].szParamDesc=itFunc->second.m_ParamDefArray[i].szParamDesc;
							ExpFuncPar[i].szParamName=itFunc->second.m_ParamDefArray[i].szParamName;

							continue;
						}else
						{
							BOOL bNew=TRUE;
							_tagParamDef OldPar;
							for(unsigned int j=0;j<ExpFuncPar.size();j++)
							{
								if(itFunc->second.m_ParamDefArray[i].nParamID==ExpFuncPar[j].nParamID)
								{
									OldPar=ExpFuncPar[j];
									bNew=FALSE;
									break;
								}
							}
							vector<_tagParamDef>::iterator itExpPar=ExpFuncPar.begin();
							
							//it2+=s;
							if(bNew)
							{
								//新字段
								//ExpFuncPar.insert(i,itFunc->first);
								itExpPar+=i;
								//_tagParamDef Par=itFunc->second.m_ParamDefArray[i];
								ExpFuncPar.insert(itExpPar,itFunc->second.m_ParamDefArray[i]);
								
							}else
							{
								//找到但位置不正确
								itExpPar+=i;

								OldPar.szDefaultParam=itFunc->second.m_ParamDefArray[i].szDefaultParam;
								OldPar.szParamAttribute=itFunc->second.m_ParamDefArray[i].szParamAttribute;
								OldPar.szParamDesc=itFunc->second.m_ParamDefArray[i].szParamDesc;
								OldPar.szParamName=itFunc->second.m_ParamDefArray[i].szParamName;

								ExpFuncPar.insert(itExpPar,OldPar);
								//itExp->second.szFuncArray.insert(i,itFunc->first);
								//itExp->second.m_ExpValMap.insert(i,NewPos);
							}
						}
						
					}
					//删除老的字段
					if(ExpFuncPar.size()>itFunc->second.m_ParamDefArray.size())
					{
						//itExp->second.szFuncArray.resize(itFunc->second.szFuncName.size());
						ExpFuncPar.resize(itFunc->second.m_ParamDefArray.size());
					}
						
				}
			}
			
		}
	}
	BOOL FixExpFunc(IN tstring & szNewExpFuncName,IN tstring & szNewExpFuncType,IN OUT _tagExp &exp)
	{
		IDType nFuncId;
		if(szNewExpFuncName.length())
		{
			nFuncId=GetFuncIDByName(szNewExpFuncName);
			if(nFuncId)
			{
				BOOL bFind=FALSE;
				for (unsigned int n=0;n<exp.FuncIDArray.size();n++)
				{
					_tagFuncDef Func;
					if(GetFuncByFuncID(exp.FuncIDArray[n],Func))
					{
						if(nFuncId==exp.FuncIDArray[n])
						{
							//没有变化不修改
							bFind=TRUE;
							return TRUE;
						}else
						{
							if(szNewExpFuncType==Func.szFuncType)
							{
								//同类型不同表达式修改替换
								vector<_tagParamDef> DefaultVal;
								if(GetDefaultVal(szNewExpFuncName,DefaultVal,m_FuncLib))
								{
									exp.m_ExpValMap.erase(Func.nFuncID);
									exp.m_ExpValMap[nFuncId]=DefaultVal;
								}
								exp.FuncIDArray[n]=nFuncId;
								bFind=TRUE;
								return TRUE;
							}
						}
					}
				}
				if(bFind)
				{
					//新增的，旧表达式中缺失的新增
					exp.FuncIDArray.push_back(nFuncId);
					vector<_tagParamDef> DefaultVal;
					if(GetDefaultVal(szNewExpFuncName,DefaultVal,m_FuncLib))
					{
						exp.m_ExpValMap[nFuncId]=DefaultVal;
					}
					return TRUE;
				}
			}
		}
		return FALSE;
	}
	BOOL Clear()
	{
		m_ExpLib.m_ExpLib.clear();
		m_FuncLib.m_FuncLib.clear();
		m_szCurLib.clear();
		m_bNewUpdataExp=TRUE;
		return TRUE;
	}
	

	
	tstring GetFuncDefStringFromFuncID(IDType nFuncID,_tagFuncLib & tFuncLib)
	{
		return GetFuncDefStringFromFunc(FindFuncByFuncID(nFuncID));
	}

	tstring GetExpDefString(_tagExp & tExp,_tagFuncLib & tFuncLib)
	{
		//if(tFuncLib.m_FuncLib.find(szFuncName)==tFuncLib.m_FuncLib.end()) return tstring();


		//vector<_tagParamDef> & ParamDefArray=tFuncLib.m_FuncLib[szFuncName].m_ParamDefArray;

		tstring szRet=tExp.szExpName;
		szRet+=_T("(");

		unsigned int i=0;
		for(;i<tExp.FuncIDArray.size();i++)
		{
			szRet+=GetFuncDefStringFromFuncID(tExp.FuncIDArray[i],tFuncLib);
			szRet+=_T(",");
		}
		if(i)
		{
			szRet[szRet.length()-1]=_T(')');
		}else
		{
			szRet+=_T(")");
		}

		return szRet;

	}

	BOOL GetDefaultVal(tstring & szFuncName,OUT vector<_tagParamDef> &ValArray,_tagFuncLib & tFuncLib)
	{
		if(tFuncLib.m_FuncLib.find(szFuncName)==tFuncLib.m_FuncLib.end()) return FALSE;

		ValArray=tFuncLib.m_FuncLib[szFuncName].m_ParamDefArray;
		return TRUE;
	}

	BOOL GetTestParamFromExp(tstring & szExpName,_tagTestParam & test,_tagExpLib &tExpLib)
	{
		map<IDType,vector<_tagParamDef>,less<IDType>>::iterator itExpVal=tExpLib.m_ExpLib[szExpName].m_ExpValMap.begin();
		map<IDType,vector<_tagParamDef>,less<IDType>> & tExp=tExpLib.m_ExpLib[szExpName].m_ExpValMap;
		vector<IDType> & FuncArray=tExpLib.m_ExpLib[szExpName].FuncIDArray;
		test.sTestUseCaseName=szExpName;
		for(unsigned int i=0;i<FuncArray.size();i++)
		{
			itExpVal=tExp.find(FuncArray[i]);
			_tagFuncDef Func;
			if(GetFuncByFuncID(FuncArray[i],Func))
			{
				if(tstring(_T("驱动用例"))==Func.szFuncType)
				{
					test.Driver[_T("UseCaseName")]=Func.szFuncName;
					for(unsigned int j=0;j<itExpVal->second.size();j++)
					{
						if(itExpVal->second[j].szLastEditParamVal.length())
						{
							test.Driver[itExpVal->second[j].szParamName]=itExpVal->second[j].szLastEditParamVal;
						}else
						{
							test.Driver[itExpVal->second[j].szParamName]=itExpVal->second[j].szDefaultParam;
						}
					}
				}else if(tstring(_T("场景用例"))==Func.szFuncType)
				{
					test.Client[_T("UseCaseName")]=Func.szFuncName;
					for(unsigned int j=0;j<itExpVal->second.size();j++)
					{
						if(itExpVal->second[j].szLastEditParamVal.length())
						{
							test.Client[itExpVal->second[j].szParamName]=itExpVal->second[j].szLastEditParamVal;
						}else
						{
							test.Client[itExpVal->second[j].szParamName]=itExpVal->second[j].szDefaultParam;
						}
					}
				}else if(tstring(_T("期望评估"))==Func.szFuncType)
				{
					test.Expect[_T("UseCaseName")]=Func.szFuncName;
					for(unsigned int j=0;j<itExpVal->second.size();j++)
					{
						if(itExpVal->second[j].szLastEditParamVal.length())
						{
							test.Expect[itExpVal->second[j].szParamName]=itExpVal->second[j].szLastEditParamVal;

						}else
						{
							test.Expect[itExpVal->second[j].szParamName]=itExpVal->second[j].szDefaultParam;
						}
					}
				}else if(tstring(_T("系统配置"))==Func.szFuncType)
				{
					test.SysConfig[_T("UseCaseName")]=Func.szFuncName;
					for(unsigned int j=0;j<itExpVal->second.size();j++)
					{
						if(itExpVal->second[j].szLastEditParamVal.length())
						{
							test.SysConfig[itExpVal->second[j].szParamName]=itExpVal->second[j].szLastEditParamVal;
						}else
						{
							test.SysConfig[itExpVal->second[j].szParamName]=itExpVal->second[j].szDefaultParam;
						}
					}
				}
			}
		}
		return TRUE;
	}

protected:
	
private:
};