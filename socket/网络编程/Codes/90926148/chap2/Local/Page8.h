#pragma once
#include "afxcmn.h"


// CPage8 �Ի���

class CPage8 : public CDialog
{
	DECLARE_DYNAMIC(CPage8)

public:
	CPage8(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPage8();

// �Ի�������
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ȡ�������Ϣ
	int GetInfo(void);
	virtual BOOL OnInitDialog();
	// IP��ַ
	CIPAddressCtrl m_IPAddress;
	// ����MAC��ַ
	CString m_MACAddress;
	// ��������
	CString m_InterfaceName;
	afx_msg void OnBnClickedButton1();
	// ������
	DWORD m_dwIndex;
	// ��������
	DWORD m_dwType;
	// ����MAC��ַ����
	DWORD m_dwAddressLength;
};
