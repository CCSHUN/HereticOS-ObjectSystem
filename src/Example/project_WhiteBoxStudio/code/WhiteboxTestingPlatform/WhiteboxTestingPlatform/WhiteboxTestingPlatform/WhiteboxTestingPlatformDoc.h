
// WhiteboxTestingPlatformDoc.h : CWhiteboxTestingPlatformDoc ��Ľӿ�
//


#pragma once


class CWhiteboxTestingPlatformDoc : public CDocument
{
protected: // �������л�����
	CWhiteboxTestingPlatformDoc();
	DECLARE_DYNCREATE(CWhiteboxTestingPlatformDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CWhiteboxTestingPlatformDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void SetTitle(LPCTSTR lpszTitle);
};


