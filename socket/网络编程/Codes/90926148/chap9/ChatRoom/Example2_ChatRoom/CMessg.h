#ifndef _CMESSG_
#define _CMESSG_
#include "Sound.h"

class CMessg : public CObject
{
protected:
	DECLARE_DYNCREATE(CMessg)
public:
	CMessg();

// Attributes
public:
	CString m_strText;
	CHAR    m_tag;	//0��ʾ����Ҫ�ų�������1��ʾ��Ҫ�ų�����
	CHAR    m_buffer[MAX_BUFFER_SIZE];
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
