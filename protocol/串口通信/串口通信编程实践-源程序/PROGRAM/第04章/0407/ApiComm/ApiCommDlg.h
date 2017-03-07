// ApiCommDlg.h : header file
//

#if !defined(AFX_APICOMMDLG_H__C105733E_AB00_4308_95C8_6B4FB5574C03__INCLUDED_)
#define AFX_APICOMMDLG_H__C105733E_AB00_4308_95C8_6B4FB5574C03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CApiCommDlg dialog

class CApiCommDlg : public CDialog
{
// Construction
public:
	CApiCommDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CApiCommDlg)
	enum { IDD = IDD_APICOMM_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApiCommDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	volatile HANDLE m_hCom; // ���пھ��
    OVERLAPPED m_osRead, m_osWrite; // �����ص���/д
	int m_nBaud;     //������
	int m_nDataBits; //ֹͣλ
	int m_nParity;   //У��λ
	CString m_strPort;     //���ں�
	int m_nStopBits; //ֹͣλ
	int m_nFlowCtrl; //������ѡ��
	BOOL m_bEcho;    //�Ƿ��ڱ��ػ���
	BOOL m_bNewLine; //�Ƿ��Զ�����

	// Generated message map functions
	//{{AFX_MSG(CApiCommDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APICOMMDLG_H__C105733E_AB00_4308_95C8_6B4FB5574C03__INCLUDED_)
