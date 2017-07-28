#pragma once


// CListCtlStringSort

class CListCtlStringSort : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtlStringSort)

public:
	int sort ;
	int SubItem ;
	static BOOL isNum(TCHAR * pStr)
	{
		if(strlen_t(pStr)==0) return FALSE;

		for(unsigned int i=0;pStr[i]!='\0';i++)
		{
			if((pStr[i]>='0')&&(pStr[i]<='9'))
			{
				continue;
			}else
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
	{
		CString &lp1 = *((CString *)lParam1);
		CString &lp2 = *((CString *)lParam2);
		int &sort = *(int *)lParamSort;

		if(isNum(lp1.GetBuffer(0)))
		{
			int np1=atoi_t(lp1.GetBuffer(0));
			int np2=atoi_t(lp2.GetBuffer(0));
			int nRet=0;
			if (sort == 0)
			{
				if(np1>np2)
				{
					nRet=1;
				}else
				{
					if(np1==np2)
					{
						nRet=0;
					}else
					{
						nRet=-1;
					}
				}
			}
			else
			{
				if(np1<np2)
				{
					nRet=1;
				}else
				{
					if(np1==np2)
					{
						nRet=0;
					}else
					{
						nRet=-1;
					}
				}
			}
			return nRet;
		}else
		{
			if (sort == 0)
			{
				return lp1.CompareNoCase(lp2);
			}
			else
			{
				return lp2.CompareNoCase(lp1);
			}
		}
		
	}

	CListCtlStringSort();
	virtual ~CListCtlStringSort();
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	//virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//BOOL PreTranslateMessage(MSG* pMsg);
protected:
	DECLARE_MESSAGE_MAP()
};


