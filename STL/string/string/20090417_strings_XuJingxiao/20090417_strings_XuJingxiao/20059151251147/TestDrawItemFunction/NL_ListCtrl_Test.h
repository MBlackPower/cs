/*
* Copyright (c) 2004,NLSoft 
* Http://newnan.8u8.com
* All rights reserved. At �Ӽ�
* 
* �ļ����ƣ�NL_ListCtrl_Test.h
* �ļ���ʶ��NL_ListCtrl_Test Class
* ժ    Ҫ����ҪDrawItem����
* 
* ��ǰ�汾��1.0
* ��    �ߣ�����
* ������ڣ�2002��8��3��
*
* ԭ����  ��
* ժ    Ҫ���̳�CListCtrl
* ��    ʾ�����Ƹ߶�ʱ��ҪCImageList
*/

#if !defined(AFX_NL_LISTCTRL_TEST_H__DEA05EBA_10C7_4CCE_AD31_A14ABC2CC7B9__INCLUDED_)
#define AFX_NL_LISTCTRL_TEST_H__DEA05EBA_10C7_4CCE_AD31_A14ABC2CC7B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NL_ListCtrl_Test.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NL_ListCtrl_Test window

class NL_ListCtrl_Test : public CListCtrl
{
// Construction
public:
	NL_ListCtrl_Test();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NL_ListCtrl_Test)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~NL_ListCtrl_Test();

	// Generated message map functions
protected:
	//{{AFX_MSG(NL_ListCtrl_Test)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	void DrawItem( LPDRAWITEMSTRUCT lpDIS );
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NL_LISTCTRL_TEST_H__DEA05EBA_10C7_4CCE_AD31_A14ABC2CC7B9__INCLUDED_)
