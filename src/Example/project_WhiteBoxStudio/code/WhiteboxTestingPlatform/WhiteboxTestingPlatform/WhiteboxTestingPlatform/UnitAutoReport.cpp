// UnitAutoReport.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "UnitAutoReport.h"
#include "UnitNewEdit.h"
#include "TemplateTool.h"
// CUnitAutoReport

IMPLEMENT_DYNCREATE(CUnitAutoReport, CFormView)

CUnitAutoReport::CUnitAutoReport()
	: CFormView(CUnitAutoReport::IDD)
{
	m_iCurIndex=-1;
}

CUnitAutoReport::~CUnitAutoReport()
{
}

void CUnitAutoReport::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UnitList, m_UnitReportListCtl);
}

BEGIN_MESSAGE_MAP(CUnitAutoReport, CFormView)
	ON_BN_CLICKED(IDC_NEW, &CUnitAutoReport::OnBnClickedNew)
	ON_BN_CLICKED(IDC_EDIT, &CUnitAutoReport::OnBnClickedEdit)
	ON_BN_CLICKED(IDC_AutoMake, &CUnitAutoReport::OnBnClickedAutomake)
	//ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CUnitAutoReport::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_DELSEL, &CUnitAutoReport::OnBnClickedDelsel)
	ON_BN_CLICKED(IDC_COPYSEL, &CUnitAutoReport::OnBnClickedCopysel)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_UnitList, OnLvnColumnclickListReport)
	ON_NOTIFY(HDN_ITEMCHANGED, 0, &CUnitAutoReport::OnHdnItemchangedUnitlist)
	ON_NOTIFY(NM_DBLCLK, IDC_UnitList, &CUnitAutoReport::OnNMDblclkUnitlist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_UnitList, &CUnitAutoReport::OnLvnItemchangedUnitlist)
END_MESSAGE_MAP()


// CUnitAutoReport 诊断

#ifdef _DEBUG
void CUnitAutoReport::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUnitAutoReport::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CUnitAutoReport::UpDataUnitReportUiList()
{
	m_UnitReportListCtl.DeleteAllItems();
	//_tagMachineCheckStandardSet UniteStandardLib;
	vector<_tagUnitReportSet>::iterator it=m_pShareData->m_UnitReport.m_Data.UnitReportArray.begin();
	for(int i=0;i<m_pShareData->m_UnitReport.m_Data.UnitReportArray.size();i++)
	{
		TCHAR szVal[64];
		itoa_t(i,szVal,10);
		int Pos=m_UnitReportListCtl.InsertItem(m_UnitReportListCtl.GetItemCount(),
			szVal);
		//m_UniteStandardList.SetItemText(Pos,0,it->second.id);
		m_UnitReportListCtl.SetItemText(Pos,1,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szPrjName.c_str());

		m_UnitReportListCtl.SetItemText(Pos,2,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szSysName.c_str());
		m_UnitReportListCtl.SetItemText(Pos,3,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szModuleName.c_str());
		m_UnitReportListCtl.SetItemText(Pos,4,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szTesterName.c_str());
		m_UnitReportListCtl.SetItemText(Pos,5,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szJudgeName.c_str());
		m_UnitReportListCtl.SetItemText(Pos,6,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szTestDate.c_str());
		m_UnitReportListCtl.SetItemText(Pos,7,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szJudgeDate.c_str());
		
		//_tcscanf_s(_T("%f"),m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].fTCCDT,szVal
		//m_UnitReportListCtl.SetItemText(Pos,7,);
		//m_UnitReportListCtl.SetItemText(Pos,4,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szJudgeName.c_str());
		/*m_UnitReportListCtl.SetItemText(Pos,1,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szSysName.c_str());
		m_UnitReportListCtl.SetItemText(Pos,2,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szModuleName.c_str());
		m_UnitReportListCtl.SetItemText(Pos,3,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szTesterName.c_str());
		m_UnitReportListCtl.SetItemText(Pos,4,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szJudgeName.c_str());
		m_UnitReportListCtl.SetItemText(Pos,1,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szSysName.c_str());
		m_UnitReportListCtl.SetItemText(Pos,2,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szModuleName.c_str());
		m_UnitReportListCtl.SetItemText(Pos,3,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szTesterName.c_str());
		m_UnitReportListCtl.SetItemText(Pos,4,m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szJudgeName.c_str());*/
	}
};
void CUnitAutoReport::OnInitialUpdate()
{
	//CFormView::OnInitialUpdate();
	CFormView::OnInitialUpdate();

	//m_szCurStandardName=
	m_pShareData=(CProjectSharedData *)(((CChildFrame *)GetParentFrame())->m_ProjectIndex.pSharedObject);
	m_pShareData->GetUnitReport();
	((CChildFrame *)GetParentFrame())->m_ProjectIndex.pViewInterface=this;
	
	m_UnitReportListCtl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_UnitReportListCtl.InsertColumn(0,_T("编号"));
	m_UnitReportListCtl.InsertColumn(1,_T("项目"));
	m_UnitReportListCtl.InsertColumn(2,_T("系统"));
	m_UnitReportListCtl.InsertColumn(3,_T("模块"));
	m_UnitReportListCtl.InsertColumn(4,_T("测试者"));
	m_UnitReportListCtl.InsertColumn(5,_T("评审者"));
	m_UnitReportListCtl.InsertColumn(6,_T("测试日期"));
	m_UnitReportListCtl.InsertColumn(7,_T("评审日期"));
	m_UnitReportListCtl.InsertColumn(8,_T("用例覆盖度"));

	m_UnitReportListCtl.SetColumnWidth(0, 50);
	m_UnitReportListCtl.SetColumnWidth(1, 80);
	m_UnitReportListCtl.SetColumnWidth(2, 80);
	m_UnitReportListCtl.SetColumnWidth(3, 80);
	m_UnitReportListCtl.SetColumnWidth(4, 80);
	m_UnitReportListCtl.SetColumnWidth(5, 80);
	m_UnitReportListCtl.SetColumnWidth(6, 80);
	m_UnitReportListCtl.SetColumnWidth(7, 80);
	m_UnitReportListCtl.SetColumnWidth(8, 40);

	UpDataUnitReportUiList();

}


void CUnitAutoReport::OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	SetRedraw(FALSE);
	m_UnitReportListCtl.OnLvnColumnclickList1(pNMHDR, pResult);
	SetRedraw(TRUE);
	m_UnitReportListCtl.Invalidate();
	m_UnitReportListCtl.UpdateWindow();
	*pResult = 0;
}




/*
##ProjectName###
###SystemName###
###ModuleName###
###IVTNUM###
###INVTNUM###
###BT###
###RCT###

###TesterName###
###TesterDate###
###JudgeName###
###JudgeDate###

问题列表格式

<IVTLIST></IVTLIST>
<INVTLIST></INVTLIST>
<BTLIST></BTLIST>
<RCTLIST></RCTLIST>

<TCCDT></TCCDT>



<w:p wsp:rsidR="00196406" wsp:rsidRPr="00EE5236" wsp:rsidRDefault="00587006" wsp:rsidP="00C07296">
<w:pPr>
<w:rPr>
<w:rFonts w:ascii="宋体" w:h-ansi="宋体" w:hint="fareast"/>
<wx:font wx:val="宋体"/>
<w:color w:val="000000"/>
<w:sz w:val="28"/>
<w:sz-cs w:val="28"/>
</w:rPr>
</w:pPr>
<w:r wsp:rsidRPr="00EE5236">
<w:rPr>
<w:rFonts w:ascii="宋体" w:h-ansi="宋体" w:hint="fareast"/>
<wx:font wx:val="宋体"/>
<w:color w:val="000000"/>
<w:sz w:val="28"/>
<w:sz-cs w:val="28"/>
</w:rPr>
<w:t>IVT-32异常 IVT-58 异常</w:t>
</w:r>
</w:p>

建议列表

1. 注意边界条件判定。
2. 注意对象生命期。
3. 指针参与计算时判断指针的合法性。
<UNITSUG></UNITSUG>

<w:p wsp:rsidR="00315158" wsp:rsidRDefault="00315158">
<w:pPr>
<w:rPr>
<w:rFonts w:hint="fareast"/>
</w:rPr>
</w:pPr>
<w:r>
<w:rPr>
<w:rFonts w:hint="fareast"/>
<wx:font wx:val="宋体"/>
</w:rPr>
<w:t>1.注意对象生命期。</w:t>
</w:r>
</w:p>
*/

float GetFloatRand(float Range)
{
	return ((Range*rand())/RAND_MAX);
}

int GetIntRand(int Range)
{
	return ((Range*rand())/RAND_MAX);
}

double GetFloatRand(float begin,float end,int nMax)
{
	//for(;;)
	double fRate=(((end-begin)*rand())/RAND_MAX);
	int nRet=(begin+fRate)*nMax;
	return ((double)nRet)/((double)nMax);
}

BOOL Getrandtab(IN int nMax,
				IN int nNum,
				OUT map<int,int,less<int> > & IntArray)
{
	// CUnitAutoReport 消息处理程序
	
	for(int i=0;i<nNum;)
	{
		int n=GetIntRand(nMax);
		if(IntArray.find(n)==IntArray.end())
		{
			i++;
			IntArray[n]=n;
		}
	}
	return TRUE;
}

BOOL GetWordListSet(IN tstring & szData,OUT tstring & szOutVal)
{
	szOutVal+=_T("<w:p wsp:rsidR=\"00196406\" wsp:rsidRPr=\"00EE5236\" wsp:rsidRDefault=\"00587006\" wsp:rsidP=\"00C07296\">");
	szOutVal+=_T("<w:pPr><w:rPr><w:rFonts w:ascii=\"宋体\" w:h-ansi=\"宋体\" w:hint=\"fareast\"/>");
	szOutVal+=_T("<wx:font wx:val=\"宋体\"/><w:color w:val=\"000000\"/><w:sz w:val=\"28\"/><w:sz-cs w:val=\"28\"/>");
	szOutVal+=_T("</w:rPr></w:pPr><w:r wsp:rsidRPr=\"00EE5236\"><w:rPr><w:rFonts w:ascii=\"宋体\" w:h-ansi=\"宋体\" w:hint=\"fareast\"/>");
	szOutVal+=_T("<wx:font wx:val=\"宋体\"/><w:color w:val=\"000000\"/><w:sz w:val=\"28\"/><w:sz-cs w:val=\"28\"/>");
	szOutVal+=_T("</w:rPr><w:t>");
	szOutVal+=szData;
	szOutVal+=_T("</w:t></w:r></w:p>");
	return TRUE;
}
BOOL MakeUnitTestDefectList(OUT tstring  & OutVal,
							IN tstring & Pix,
							IN vector<tstring> & DefectType,
							IN int nNum,
							IN int nMax
							)
{
	map<int,int,less<int> > IntArray;
	Getrandtab(nMax,nNum,IntArray);
	map<int,int,less<int> >::iterator itInt=IntArray.begin();
	tstring szDefect;
	TCHAR szVal[64];
	OutVal.clear();
	for(;itInt!=IntArray.end();itInt++)
	{
		itoa_t(itInt->first,szVal,10);
		szDefect=Pix+tstring(szVal)+tstring(_T(" "))+DefectType[GetIntRand(DefectType.size()-1)];
		GetWordListSet(szDefect,OutVal);
	}
	if(IntArray.size()==0)
	{
		szDefect.clear();
		GetWordListSet(szDefect,OutVal);
	}
	return TRUE;
}

BOOL MakeUnitDoc(_tagUnitReportSet & Set)
{
#define MAKEVAL(name,Val)	ValMap[tstring(_T(name))]=Val;
	srand(GetTickCount());
	map<tstring,tstring,less<tstring> >  ValMap;
	MAKEVAL("##ProjectName###",Set.szPrjName)
	MAKEVAL("###SystemName###",Set.szSysName)
	MAKEVAL("###ModuleName###",Set.szModuleName)

	MAKEVAL("###TesterName###",Set.szTesterName)

	MAKEVAL("###TesterDate###",Set.szTestDate)

	MAKEVAL("###JudgeName###",Set.szJudgeName)

	MAKEVAL("###JudgeDate###",Set.szJudgeDate)

	TCHAR szVal[64];
	itoa_t(Set.nIVT,szVal,10);
	MAKEVAL("###IVTNUM###",szVal);
	itoa_t(Set.nINVT,szVal,10);
	MAKEVAL("###INVTNUM###",szVal);
	itoa_t(Set.nBT,szVal,10);
	MAKEVAL("###BT###",szVal);
	itoa_t(Set.nRCT,szVal,10);
	MAKEVAL("###RCT###",szVal);

	sprintf_s_t(szVal,64,_T("%f"),Set.fTCCDT);
	tstring szTCCDT;
	GetWordListSet(tstring(szVal),szTCCDT);
	MAKEVAL("<TCCDT></TCCDT>",szTCCDT);
	tstring szList;
	/*
	<IVTLIST></IVTLIST>
	<INVTLIST></INVTLIST>
	<BTLIST></BTLIST>
	<RCTLIST></RCTLIST>

	<TCCDT></TCCDT>
	*/
	vector<tstring> DefectType;
	DefectType.push_back(tstring(_T("异常")));
	DefectType.push_back(tstring(_T("没有达到预期响应")));
	//DefectType.push_back(tstring(_T("无异常日志记录")));
	DefectType.push_back(tstring(_T("失去响应")));

	MakeUnitTestDefectList(szList,tstring(_T("IVT-")),DefectType,Set.nIVT*Set.fIVT,Set.nIVT);
	MAKEVAL("<IVTLIST></IVTLIST>",szList);

	DefectType.clear();
	DefectType.push_back(tstring(_T("异常")));
	DefectType.push_back(tstring(_T("无状态异常日志记录")));
	DefectType.push_back(tstring(_T("失去响应")));
	MakeUnitTestDefectList(szList,tstring(_T("INVT-")),DefectType,Set.nINVT*Set.fINVT,Set.nINVT);
	MAKEVAL("<INVTLIST></INVTLIST>",szList);

	
	DefectType.clear();
	DefectType.push_back(tstring(_T("异常")));
	DefectType.push_back(tstring(_T("没有达到预期响应")));
	DefectType.push_back(tstring(_T("失去响应")));

	MakeUnitTestDefectList(szList,tstring(_T("BT-")),DefectType,Set.nBT*Set.fBT,Set.nBT);
	MAKEVAL("<BTLIST></BTLIST>",szList);

	DefectType.clear();
	DefectType.push_back(tstring(_T("异常")));
	DefectType.push_back(tstring(_T("没有达到预期响应")));
	DefectType.push_back(tstring(_T("无参数错误异常日志记录")));
	DefectType.push_back(tstring(_T("失去响应")));

	MakeUnitTestDefectList(szList,tstring(_T("RCT-")),DefectType,Set.nBT*Set.fBT,Set.nBT);
	MAKEVAL("<RCTLIST></RCTLIST>",szList);

	tstring szSug=_T("<w:p wsp:rsidR=\"00315158\" wsp:rsidRDefault=\"00315158\"><w:pPr><w:rPr><w:rFonts w:hint=\"fareast\"/></w:rPr></w:pPr><w:r><w:rPr><w:rFonts w:hint=\"fareast\"/><wx:font wx:val=\"宋体\"/></w:rPr><w:t>")
		+tstring(Set.szSug)+_T("</w:t></w:r></w:p>");
	MAKEVAL("<UNITSUG></UNITSUG>",szSug);

	//生成问题列表
	tstring szOutFileName=tstring(theApp.GetAppPath().GetBuffer(0))+tstring(_T("单元测试报告\\"));
	szOutFileName+=Set.szSysName;
	szOutFileName+=Set.szModuleName;
	itoa_t(Set.nID,szVal,10);
	szOutFileName+=_T("Ver")+tstring(szVal)+_T(".xml");
	BOOL bSucess=CTemplateTool::MakeFileByTemplateFile(
		ValMap,tstring(theApp.GetAppPath().GetBuffer(0))+tstring(_T("单元测试报告2003xml模板.xml")),
		szOutFileName);

	return bSucess;
}


void CUnitAutoReport::OnBnClickedAutomake()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION   pos   =   m_UnitReportListCtl.GetFirstSelectedItemPosition();   
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("请选择要需要生成的测试文档"));
	}
	else   
	{   
		int s=0;
		while(pos)   
		{   
			int   nItem   =   m_UnitReportListCtl.GetNextSelectedItem(pos);   
			int nIndex = atol_t(m_UnitReportListCtl.GetItemText(nItem, 0).GetBuffer(0));
			//m_pShareData->m_Report.m_Data.items.iterator it=;
			//vector<_tagUnitReportSet>::iterator itPos=;

			//m_lstReport.DeleteItem(nItem);
			MakeUnitDoc(m_pShareData->m_UnitReport.m_Data.UnitReportArray[nIndex]);

			//   you   could   do   your   own   processing   on   nItem   here   
		}   

	}  

	
}

void CUnitAutoReport::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	
	*pResult = 0;
}

void CUnitAutoReport::OnBnClickedDelsel()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION   pos   =   m_UnitReportListCtl.GetFirstSelectedItemPosition();   
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("请选择要删除的元素"));
	}
	else   
	{   

		while(pos)   
		{   
			int   nItem   =   m_UnitReportListCtl.GetNextSelectedItem(pos);   
			int nIndex = atol_t(m_UnitReportListCtl.GetItemText(nItem, 0).GetBuffer(0));
			//m_pShareData->m_Report.m_Data.items.iterator it=;
			//vector<_tagUnitReportSet>::iterator itPos=m_pShareData->m_UnitReport.m_Data.UnitReportArray.begin()+nIndex-s;

			//m_lstReport.DeleteItem(nItem);
			m_pShareData->m_UnitReport.m_Data.UnitReportArray[nIndex].szState=_T("删除");

			//   you   could   do   your   own   processing   on   nItem   here   
		}
		for(unsigned int i=0;i<m_pShareData->m_UnitReport.m_Data.UnitReportArray.size();)
		{
			if(m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szState==_T("删除"))
			{
				vector<_tagUnitReportSet>::iterator itPos=m_pShareData->m_UnitReport.m_Data.UnitReportArray.begin()+i;
				m_pShareData->m_UnitReport.m_Data.UnitReportArray.erase(itPos);
			}else
			{
				i++;
			}
		}
		UpDataUnitReportUiList();
		m_pShareData->UpDataUnitReport();
	}  
}

BOOL IsVacationDay(COleDateTime tm)
{

	if(
		tm>COleDateTime(tm.GetYear(),4,1,0,0,0)&&
		tm<COleDateTime(tm.GetYear(),4,5,0,0,0)
		)
	{
		//清明
		return TRUE;
	}

	if(
		tm>COleDateTime(tm.GetYear(),4,30,0,0,0)&&
		tm<COleDateTime(tm.GetYear(),5,8,0,0,0)
		)
	{
		//五一
		return TRUE;
	}



	if(
		tm>COleDateTime(tm.GetYear(),9,20,0,0,0)&&
		tm<COleDateTime(tm.GetYear(),10,8,0,0,0)
		)
	{
		//中秋国庆
		return TRUE;
	}

	if(
		tm>COleDateTime(tm.GetYear(),12,30,0,0,0)&&
		tm<COleDateTime(tm.GetYear(),1,4,0,0,0)
		)
	{
		//元旦
		return TRUE;
	}

	if(
		tm>COleDateTime(tm.GetYear(),1,18,0,0,0)&&
		tm<COleDateTime(tm.GetYear(),2,18,0,0,0)
		)
	{
		//春节年底
		return TRUE;
	}


	if(tm.GetDayOfWeek()==1||tm.GetDayOfWeek()==7)
	{
		//周末
		return TRUE;
	}

	return FALSE;
}
BOOL JmpVacationDay(COleDateTime & tm)
{
	COleDateTimeSpan dateSpan(1,0,0,0);
	for(;;)
	{
		if(IsVacationDay(tm))
		{
			tm+=dateSpan;
		}else
		{
			return TRUE;
		}
	}
	return TRUE;
}

BOOL JmpVacationDay(tstring & sztm)
{
	COleDateTime tm;
	tm.ParseDateTime(sztm.c_str());
	COleDateTimeSpan dateSpan(1,0,0,0);
	for(;;)
	{
		if(IsVacationDay(tm))
		{
			tm+=dateSpan;
		}else
		{
			sztm=tm.Format();
			return TRUE;
		}
	}
	return TRUE;
}

BOOL AddDate(IN OUT tstring & szDate,tstring & szEndTime,unsigned int nCyc)
{
	COleDateTime tm,endtm;
	COleDateTimeSpan dateSpan(1,0,0,0);
	tm.ParseDateTime(szDate.c_str());
	endtm.ParseDateTime(szEndTime.c_str());
	for(unsigned int n=0;n<nCyc;)
	{
		if(tm>(endtm-COleDateTimeSpan(3,0,0,0)))
		{
			//过了
			return FALSE;
		}
		//跳过节假日
		JmpVacationDay(tm);

		//正常工作日，记入．
		tm+=dateSpan;
		JmpVacationDay(tm);
		n++;
	}
	szDate=tm.Format().GetBuffer(0);
	return TRUE;
	
}
BOOL GetDateList(tstring & szBeginDate,tstring & szEndTime,vector<tstring> & DateList)
{
	//周期天
	unsigned int nCyc=15;
	//排除节假日增加指定天数
	tstring szDate=szBeginDate;
	for(;;)
	{
		if(AddDate(szDate,szEndTime,5+GetIntRand(4)))
		{
			DateList.push_back(szDate);
		}else
		{
			break;
		}
	}
	
	return TRUE;
}
//得到新的缺陷率
double GetNewfRate(double PrvefRate,double fRate,unsigned int index,unsigned int nTotalDate,unsigned int nTotalTest)
{
	double OldfRate=PrvefRate;
	fRate-=(index*(fRate/nTotalDate));

	//缺陷率上浮计算公式．依次上浮递减
	fRate+=GetFloatRand(0.15*
		(((float)(nTotalDate-index))/(float)nTotalDate)
		);
	if(fRate>1.0)
	{
		fRate=0.95;
	}
	if(fRate>OldfRate)
	{
		fRate=GetFloatRand(OldfRate,fRate,nTotalTest);
	}else
	{
		fRate=GetFloatRand(fRate,OldfRate,nTotalTest);
	}
	return fRate;
}
BOOL MakeUnitReportList(tstring & szEndTime,IN _tagUnitReportSet & Set,OUT vector<_tagUnitReportSet> & Array)
{
	srand(GetTickCount());
	vector<tstring>  DateList;
	_tagUnitReportSet  OldTmp,Tmp;
	#define GetNewfRateVal(name) Tmp.f##name=GetNewfRate(Tmp.f##name,Set.f##name,i,DateList.size(),Tmp.n##name);
#define GetNewTotalVal(name) Tmp.n##name+=0.15*Set.n##name*fVal;
	if(GetDateList(Set.szTestDate,szEndTime,DateList))
	{
		double fVal;
		Tmp=Set;
		for (unsigned int i=0;i<DateList.size();i++)
		{
			//OldTmp=Tmp;
			Tmp.nID+=i+1;
			Tmp.szTestDate=Tmp.szJudgeDate=DateList[i];
			fVal=(((float)(DateList.size()-i-1))/((float)DateList.size()));
			//Tmp.fBT=GetNewfRate(Tmp.fBT,i,DateList.size(),Tmp.nBT);
			GetNewTotalVal(IVT);
			GetNewTotalVal(INVT);
			GetNewTotalVal(BT);
			GetNewTotalVal(RCT);

			GetNewfRateVal(IVT);
			GetNewfRateVal(INVT);
			GetNewfRateVal(BT);
			GetNewfRateVal(RCT);
			Tmp.fTCCDT=(0.9-Tmp.fTCCDT)*(((float)i)/((float)DateList.size()));

			
			Array.push_back(Tmp);
		}
	}
	return TRUE;
}
#include "UnitTestEndTimeDlg.h"
void CUnitAutoReport::OnBnClickedCopysel()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION   pos   =   m_UnitReportListCtl.GetFirstSelectedItemPosition();   
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("请选择要删除的元素"));
	}
	else   
	{   
		vector<_tagUnitReportSet>  Array;
		CUnitTestEndTimeDlg dlg;
		dlg.m_szEndTime=COleDateTime::GetCurrentTime().Format();
		if(dlg.DoModal()==IDOK)
		{
			while(pos)   
			{   
				int   nItem   =   m_UnitReportListCtl.GetNextSelectedItem(pos);   
				int nIndex = atol_t(m_UnitReportListCtl.GetItemText(nItem, 0).GetBuffer(0));
				//m_pShareData->m_Report.m_Data.items.iterator it=;
				//vector<_tagUnitReportSet>::iterator itPos=m_pShareData->m_UnitReport.m_Data.UnitReportArray.begin()+nIndex-s;

				//m_lstReport.DeleteItem(nItem);
				Array.clear();
				JmpVacationDay(m_pShareData->m_UnitReport.m_Data.UnitReportArray[nIndex].szTestDate);
				if(MakeUnitReportList(tstring(dlg.m_szEndTime),m_pShareData->m_UnitReport.m_Data.UnitReportArray[nIndex],Array))
				{
					if(Array.size()==0)
					{
						AfxMessageBox(_T("项目日期安排错误"));
						m_pShareData->GetUnitReport();
						UpDataUnitReportUiList();
						return;
					}
					for(unsigned int i=0;i<Array.size();i++)
					{
						m_pShareData->m_UnitReport.m_Data.UnitReportArray.push_back(Array[i]);
					}
					
				}
				
				//	m_pShareData->m_UnitReport.m_Data.UnitReportArray[nIndex];

				//   you   could   do   your   own   processing   on   nItem   here   
			}
			
			UpDataUnitReportUiList();
			m_pShareData->UpDataUnitReport();
		}
		
	}  
}

void CUnitAutoReport::OnBnClickedNew()
{
	// TODO: 在此添加控件通知处理程序代码
	CUnitNewEdit New;
	New.m_szTitle=_T("新建");
	New.szPrjName=m_pShareData->GetSubProjectName().c_str()+strlen_t(_T("ChildTest_"));
	New.szJudgeName=_T("叶树深");
	New.szTesterName=_T("张新");

	New.szJudgeDate=COleDateTime::GetCurrentTime().Format();
	New.szTestDate=COleDateTime::GetCurrentTime().Format();

	srand(GetTickCount());
	New.nIVT=200+GetIntRand(300);
	New.nINVT=50+GetIntRand(200);
	New.nBT=50+GetIntRand(200);
	New.nRCT=50+GetIntRand(100);
	New.nTCCDT=0;

	New.fIVT=GetFloatRand(0.6,0.95,New.nIVT);
	New.fINVT=GetFloatRand(0.6,0.95,New.nINVT);
	New.fBT=GetFloatRand(0.6,0.95,New.nBT);
	New.fRCT=GetFloatRand(0.6,0.95,New.nRCT);
	New.fTCCDT=0.3+GetFloatRand(0.3);//,New.nIVT);



#define BINDVAL(Val) Set.Val=New.Val;
	if(New.DoModal()==IDOK)
	{
		_tagUnitReportSet Set;
		Set.nID=1;
		BINDVAL(szPrjName)
			BINDVAL(szSysName)
			BINDVAL(szModuleName)
			BINDVAL(szTesterName)
			BINDVAL(szJudgeName)
			BINDVAL(szTestDate)
			BINDVAL(szJudgeDate)
			BINDVAL(szSug)

			JmpVacationDay(Set.szTestDate);


		BINDVAL(nIVT)
			BINDVAL(nINVT)
			BINDVAL(nBT)
			BINDVAL(nRCT)
			BINDVAL(nTCCDT)

			BINDVAL(fIVT)
			BINDVAL(fINVT)
			BINDVAL(fBT)
			BINDVAL(fRCT)
			BINDVAL(fTCCDT)
			m_pShareData->m_UnitReport.m_Data.UnitReportArray.push_back(Set);
		m_pShareData->UpDataUnitReport();
		UpDataUnitReportUiList();
	}
}



void CUnitAutoReport::OnBnClickedEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	CUnitNewEdit Edit;
	//New.szJudgeDate=
	POSITION pos=m_UnitReportListCtl.GetFirstSelectedItemPosition();

	int item=m_UnitReportListCtl.GetNextSelectedItem(pos);
	if(item==-1) return;
	//m_iCurIndex=atoi_t(((LPCTSTR)m_UnitReportListCtl.GetItemText(item,0)));

#define BINDVAL(Val) Edit.Val=m_CurSelSet.Val;
#define BINDVALS(Val) Edit.Val=m_CurSelSet.Val.c_str();
	BINDVALS(szPrjName)
		BINDVALS(szSysName)
		BINDVALS(szModuleName)
		BINDVALS(szTesterName)
		BINDVALS(szJudgeName)
		BINDVALS(szTestDate)
		BINDVALS(szJudgeDate)
		BINDVALS(szSug)


		BINDVAL(nIVT)
		BINDVAL(nINVT)
		BINDVAL(nBT)
		BINDVAL(nRCT)
		BINDVAL(nTCCDT)

		BINDVAL(fIVT)
		BINDVAL(fINVT)
		BINDVAL(fBT)
		BINDVAL(fRCT)
		BINDVAL(fTCCDT)
		if(Edit.DoModal()==IDOK)
		{
			//_tagUnitReportSet Set;
#define BINDVAL(Val) m_CurSelSet.Val=Edit.Val;
			BINDVAL(szPrjName)
				BINDVAL(szSysName)
				BINDVAL(szModuleName)
				BINDVAL(szTesterName)
				BINDVAL(szJudgeName)
				BINDVAL(szTestDate)
				BINDVAL(szJudgeDate)
				BINDVAL(szSug)

				JmpVacationDay(m_CurSelSet.szTestDate);

			BINDVAL(nIVT)
				BINDVAL(nINVT)
				BINDVAL(nBT)
				BINDVAL(nRCT)
				BINDVAL(nTCCDT)

				BINDVAL(fIVT)
				BINDVAL(fINVT)
				BINDVAL(fBT)
				BINDVAL(fRCT)
				BINDVAL(fTCCDT)
				m_pShareData->m_UnitReport.m_Data.UnitReportArray[m_iCurIndex]=m_CurSelSet;
			m_pShareData->UpDataUnitReport();
			UpDataUnitReportUiList();
		}
}
void CUnitAutoReport::OnHdnItemchangedUnitlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	
	
}

void CUnitAutoReport::OnNMDblclkUnitlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	
	m_iCurIndex=atoi_t(m_UnitReportListCtl.GetItemText(pNMItemActivate->iItem,0).GetBuffer(0));
	m_CurSelSet=m_pShareData->m_UnitReport.m_Data.UnitReportArray[m_iCurIndex];
	OnBnClickedEdit();
}

void CUnitAutoReport::OnLvnItemchangedUnitlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if(pNMLV->uNewState!=3) return;
	m_iCurIndex=atoi_t(m_UnitReportListCtl.GetItemText(pNMLV->iItem,0).GetBuffer(0));
	if(m_pShareData->m_UnitReport.m_Data.UnitReportArray.size()>m_iCurIndex)
	{
		m_CurSelSet=m_pShareData->m_UnitReport.m_Data.UnitReportArray[m_iCurIndex];
	}
}
