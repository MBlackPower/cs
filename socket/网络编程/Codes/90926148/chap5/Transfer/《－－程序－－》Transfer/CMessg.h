#ifndef _CMESSG_
#define _CMESSG_

class CMessg : public CObject
{
protected:
	DECLARE_DYNCREATE(CMessg)
public:
	CMessg();

// Attributes
public:
	//0��ʾ���ͱ��صĹ����ļ��б�,���еĹ����ļ�������m_strText�У������ļ�����'%'���ŷָ�;
	//1��ʾ����Է���������ļ����ļ�������m_strText�У������ļ�����'%'���ŷָ�;
	//2��ʾ�����ļ����Է����ļ����ݷ���m_strText��
	int		m_iCommand;			
//	long    m_lLength;
	CString m_strText;			

// Operations
public:
	void Init();

// Implementation
public:
	virtual ~CMessg();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

#endif

/////////////////////////////////////////////////////////////////////////////
