#pragma once


// CPage7 �Ի���

class CPage7 : public CDialog
{
	DECLARE_DYNAMIC(CPage7)

public:
	CPage7(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPage7();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��������������Դ
	CString m_EnumResource;
	// ��ȡ�������Ϣ
	int GetInfo(void);
	virtual BOOL OnInitDialog();
};
