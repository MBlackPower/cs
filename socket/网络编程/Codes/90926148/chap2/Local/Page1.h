#pragma once


// CPage1 �Ի���

class CPage1 : public CDialog
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPage1();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ȡ���������GetComputerName
	CString m_GetComputerName;
	virtual BOOL OnInitDialog();
	// ��ȡ��������ƣ�gethostname
	CString m_gethostname;
	// ��ȡIP��ַ
	CString m_IPAddress;
	// ��ȡ��������ƺ�IP��ַ
	int GetInfo(void);
};
