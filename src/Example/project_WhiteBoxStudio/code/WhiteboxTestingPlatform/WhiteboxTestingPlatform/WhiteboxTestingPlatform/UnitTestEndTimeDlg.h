#pragma once


// CUnitTestEndTimeDlg �Ի���

class CUnitTestEndTimeDlg : public CDialog
{
	DECLARE_DYNAMIC(CUnitTestEndTimeDlg)

public:
	CUnitTestEndTimeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUnitTestEndTimeDlg();

// �Ի�������
	enum { IDD = IDD_UNIT_ENDTime };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_szEndTime;
};
