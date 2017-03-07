// FileSpltDlg.h : header file
//
//Modify by �쾰�� ��2001.2.13
//���ܣ��ļ��ָ�Ϊ1.4M��С��������ϲ���һ��
//
#if !defined(AFX_FILESPLTDLG_H__7FE4F386_019A_11D5_9005_D288FBFBF7E1__INCLUDED_)
#define AFX_FILESPLTDLG_H__7FE4F386_019A_11D5_9005_D288FBFBF7E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WBButton.h" //λͼ��ť
#include "GradientProgressCtrl.h" //����ɫ������
/////////////////////////////////////////////////////////////////////////////
// CFileSpltDlg dialog

class CFileSpltDlg : public CDialog
{
// Construction
public:
	CFileSpltDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFileSpltDlg)
	enum { IDD = IDD_FILESPLT_DIALOG };
	CGradientProgressCtrl  pProgress;
    CWBButton m_buttMerge;  //����λͼ��ť
	CWBButton m_buttExit;
	CWBButton m_buttSplit;
	CWBButton m_Browse;
    CWBButton m_Browse2;
	CButton	m_RadioSplit;
	CEdit	m_edit;
	CString	m_parts;
	CString	m_path;
	CString	m_targetpath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileSpltDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    BOOL m_split;
	CString m_filename;
	CFile m_SourceFile;
	HICON m_hIcon;
	int SplitMe();
	int MergeMe();

	// Generated message map functions
	//{{AFX_MSG(CFileSpltDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnOk();
	afx_msg void OnButtonMerge();
	afx_msg void OnRadio4();
	afx_msg void OnRadio3();
	afx_msg void OnBrowse2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESPLTDLG_H__7FE4F386_019A_11D5_9005_D288FBFBF7E1__INCLUDED_)
