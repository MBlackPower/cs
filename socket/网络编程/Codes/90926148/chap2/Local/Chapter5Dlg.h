// Chapter5Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "TabSheet.h"
#include "Page1.h"
#include "Page2.h"
#include "Page3.h"
#include "Page4.h"
#include "Page5.h"
#include "Page6.h"
#include "Page7.h"
#include "Page8.h"
#include "Page9.h"


// CChapter5Dlg �Ի���
class CChapter5Dlg : public CDHtmlDialog
{
// ����
public:
	CChapter5Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHAPTER5_DIALOG, IDH = IDR_HTML_CHAPTER5_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CTabSheet m_sheet;
	CPage1 m_page1;
	CPage2 m_page2;
	CPage3 m_page3;
	CPage4 m_page4;
	CPage5 m_page5;
	CPage6 m_page6;
	CPage7 m_page7;
	CPage8 m_page8;
	CPage9 m_page9;
};
