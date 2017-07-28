// UnitAutoReport.cpp : ʵ���ļ�
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


// CUnitAutoReport ���

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
	m_UnitReportListCtl.InsertColumn(0,_T("���"));
	m_UnitReportListCtl.InsertColumn(1,_T("��Ŀ"));
	m_UnitReportListCtl.InsertColumn(2,_T("ϵͳ"));
	m_UnitReportListCtl.InsertColumn(3,_T("ģ��"));
	m_UnitReportListCtl.InsertColumn(4,_T("������"));
	m_UnitReportListCtl.InsertColumn(5,_T("������"));
	m_UnitReportListCtl.InsertColumn(6,_T("��������"));
	m_UnitReportListCtl.InsertColumn(7,_T("��������"));
	m_UnitReportListCtl.InsertColumn(8,_T("�������Ƕ�"));

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

�����б��ʽ

<IVTLIST></IVTLIST>
<INVTLIST></INVTLIST>
<BTLIST></BTLIST>
<RCTLIST></RCTLIST>

<TCCDT></TCCDT>



<w:p wsp:rsidR="00196406" wsp:rsidRPr="00EE5236" wsp:rsidRDefault="00587006" wsp:rsidP="00C07296">
<w:pPr>
<w:rPr>
<w:rFonts w:ascii="����" w:h-ansi="����" w:hint="fareast"/>
<wx:font wx:val="����"/>
<w:color w:val="000000"/>
<w:sz w:val="28"/>
<w:sz-cs w:val="28"/>
</w:rPr>
</w:pPr>
<w:r wsp:rsidRPr="00EE5236">
<w:rPr>
<w:rFonts w:ascii="����" w:h-ansi="����" w:hint="fareast"/>
<wx:font wx:val="����"/>
<w:color w:val="000000"/>
<w:sz w:val="28"/>
<w:sz-cs w:val="28"/>
</w:rPr>
<w:t>IVT-32�쳣 IVT-58 �쳣</w:t>
</w:r>
</w:p>

�����б�

1. ע��߽������ж���
2. ע����������ڡ�
3. ָ��������ʱ�ж�ָ��ĺϷ��ԡ�
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
<wx:font wx:val="����"/>
</w:rPr>
<w:t>1.ע����������ڡ�</w:t>
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
	// CUnitAutoReport ��Ϣ�������
	
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
	szOutVal+=_T("<w:pPr><w:rPr><w:rFonts w:ascii=\"����\" w:h-ansi=\"����\" w:hint=\"fareast\"/>");
	szOutVal+=_T("<wx:font wx:val=\"����\"/><w:color w:val=\"000000\"/><w:sz w:val=\"28\"/><w:sz-cs w:val=\"28\"/>");
	szOutVal+=_T("</w:rPr></w:pPr><w:r wsp:rsidRPr=\"00EE5236\"><w:rPr><w:rFonts w:ascii=\"����\" w:h-ansi=\"����\" w:hint=\"fareast\"/>");
	szOutVal+=_T("<wx:font wx:val=\"����\"/><w:color w:val=\"000000\"/><w:sz w:val=\"28\"/><w:sz-cs w:val=\"28\"/>");
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
	DefectType.push_back(tstring(_T("�쳣")));
	DefectType.push_back(tstring(_T("û�дﵽԤ����Ӧ")));
	//DefectType.push_back(tstring(_T("���쳣��־��¼")));
	DefectType.push_back(tstring(_T("ʧȥ��Ӧ")));

	MakeUnitTestDefectList(szList,tstring(_T("IVT-")),DefectType,Set.nIVT*Set.fIVT,Set.nIVT);
	MAKEVAL("<IVTLIST></IVTLIST>",szList);

	DefectType.clear();
	DefectType.push_back(tstring(_T("�쳣")));
	DefectType.push_back(tstring(_T("��״̬�쳣��־��¼")));
	DefectType.push_back(tstring(_T("ʧȥ��Ӧ")));
	MakeUnitTestDefectList(szList,tstring(_T("INVT-")),DefectType,Set.nINVT*Set.fINVT,Set.nINVT);
	MAKEVAL("<INVTLIST></INVTLIST>",szList);

	
	DefectType.clear();
	DefectType.push_back(tstring(_T("�쳣")));
	DefectType.push_back(tstring(_T("û�дﵽԤ����Ӧ")));
	DefectType.push_back(tstring(_T("ʧȥ��Ӧ")));

	MakeUnitTestDefectList(szList,tstring(_T("BT-")),DefectType,Set.nBT*Set.fBT,Set.nBT);
	MAKEVAL("<BTLIST></BTLIST>",szList);

	DefectType.clear();
	DefectType.push_back(tstring(_T("�쳣")));
	DefectType.push_back(tstring(_T("û�дﵽԤ����Ӧ")));
	DefectType.push_back(tstring(_T("�޲��������쳣��־��¼")));
	DefectType.push_back(tstring(_T("ʧȥ��Ӧ")));

	MakeUnitTestDefectList(szList,tstring(_T("RCT-")),DefectType,Set.nBT*Set.fBT,Set.nBT);
	MAKEVAL("<RCTLIST></RCTLIST>",szList);

	tstring szSug=_T("<w:p wsp:rsidR=\"00315158\" wsp:rsidRDefault=\"00315158\"><w:pPr><w:rPr><w:rFonts w:hint=\"fareast\"/></w:rPr></w:pPr><w:r><w:rPr><w:rFonts w:hint=\"fareast\"/><wx:font wx:val=\"����\"/></w:rPr><w:t>")
		+tstring(Set.szSug)+_T("</w:t></w:r></w:p>");
	MAKEVAL("<UNITSUG></UNITSUG>",szSug);

	//���������б�
	tstring szOutFileName=tstring(theApp.GetAppPath().GetBuffer(0))+tstring(_T("��Ԫ���Ա���\\"));
	szOutFileName+=Set.szSysName;
	szOutFileName+=Set.szModuleName;
	itoa_t(Set.nID,szVal,10);
	szOutFileName+=_T("Ver")+tstring(szVal)+_T(".xml");
	BOOL bSucess=CTemplateTool::MakeFileByTemplateFile(
		ValMap,tstring(theApp.GetAppPath().GetBuffer(0))+tstring(_T("��Ԫ���Ա���2003xmlģ��.xml")),
		szOutFileName);

	return bSucess;
}


void CUnitAutoReport::OnBnClickedAutomake()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION   pos   =   m_UnitReportListCtl.GetFirstSelectedItemPosition();   
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("��ѡ��Ҫ��Ҫ���ɵĲ����ĵ�"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	
	*pResult = 0;
}

void CUnitAutoReport::OnBnClickedDelsel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION   pos   =   m_UnitReportListCtl.GetFirstSelectedItemPosition();   
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("��ѡ��Ҫɾ����Ԫ��"));
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
			m_pShareData->m_UnitReport.m_Data.UnitReportArray[nIndex].szState=_T("ɾ��");

			//   you   could   do   your   own   processing   on   nItem   here   
		}
		for(unsigned int i=0;i<m_pShareData->m_UnitReport.m_Data.UnitReportArray.size();)
		{
			if(m_pShareData->m_UnitReport.m_Data.UnitReportArray[i].szState==_T("ɾ��"))
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
		//����
		return TRUE;
	}

	if(
		tm>COleDateTime(tm.GetYear(),4,30,0,0,0)&&
		tm<COleDateTime(tm.GetYear(),5,8,0,0,0)
		)
	{
		//��һ
		return TRUE;
	}



	if(
		tm>COleDateTime(tm.GetYear(),9,20,0,0,0)&&
		tm<COleDateTime(tm.GetYear(),10,8,0,0,0)
		)
	{
		//�������
		return TRUE;
	}

	if(
		tm>COleDateTime(tm.GetYear(),12,30,0,0,0)&&
		tm<COleDateTime(tm.GetYear(),1,4,0,0,0)
		)
	{
		//Ԫ��
		return TRUE;
	}

	if(
		tm>COleDateTime(tm.GetYear(),1,18,0,0,0)&&
		tm<COleDateTime(tm.GetYear(),2,18,0,0,0)
		)
	{
		//�������
		return TRUE;
	}


	if(tm.GetDayOfWeek()==1||tm.GetDayOfWeek()==7)
	{
		//��ĩ
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
			//����
			return FALSE;
		}
		//�����ڼ���
		JmpVacationDay(tm);

		//���������գ����룮
		tm+=dateSpan;
		JmpVacationDay(tm);
		n++;
	}
	szDate=tm.Format().GetBuffer(0);
	return TRUE;
	
}
BOOL GetDateList(tstring & szBeginDate,tstring & szEndTime,vector<tstring> & DateList)
{
	//������
	unsigned int nCyc=15;
	//�ų��ڼ�������ָ������
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
//�õ��µ�ȱ����
double GetNewfRate(double PrvefRate,double fRate,unsigned int index,unsigned int nTotalDate,unsigned int nTotalTest)
{
	double OldfRate=PrvefRate;
	fRate-=(index*(fRate/nTotalDate));

	//ȱ�����ϸ����㹫ʽ�������ϸ��ݼ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION   pos   =   m_UnitReportListCtl.GetFirstSelectedItemPosition();   
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("��ѡ��Ҫɾ����Ԫ��"));
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
						AfxMessageBox(_T("��Ŀ���ڰ��Ŵ���"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CUnitNewEdit New;
	New.m_szTitle=_T("�½�");
	New.szPrjName=m_pShareData->GetSubProjectName().c_str()+strlen_t(_T("ChildTest_"));
	New.szJudgeName=_T("Ҷ����");
	New.szTesterName=_T("����");

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	
	
}

void CUnitAutoReport::OnNMDblclkUnitlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	m_iCurIndex=atoi_t(m_UnitReportListCtl.GetItemText(pNMItemActivate->iItem,0).GetBuffer(0));
	m_CurSelSet=m_pShareData->m_UnitReport.m_Data.UnitReportArray[m_iCurIndex];
	OnBnClickedEdit();
}

void CUnitAutoReport::OnLvnItemchangedUnitlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	if(pNMLV->uNewState!=3) return;
	m_iCurIndex=atoi_t(m_UnitReportListCtl.GetItemText(pNMLV->iItem,0).GetBuffer(0));
	if(m_pShareData->m_UnitReport.m_Data.UnitReportArray.size()>m_iCurIndex)
	{
		m_CurSelSet=m_pShareData->m_UnitReport.m_Data.UnitReportArray[m_iCurIndex];
	}
}
