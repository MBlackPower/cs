// ProgrammeTechnicFund.h : main header file for the PROGRAMMETECHNICFUND application
//

#if !defined(AFX_PROGRAMMETECHNICFUND_H__5283924B_9304_4A23_A46C_615704573B1B__INCLUDED_)
#define AFX_PROGRAMMETECHNICFUND_H__5283924B_9304_4A23_A46C_615704573B1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "ShareResource.h"  //�� #include "filename.h" ��ʽ�����õ�ǰ�����е�ͷ�ļ������������Ӹ��ļ�����Ŀ¼��ʼ��������

#include "ACE_Frame.h"

#include "UsingSocketCommunication.h"

#include "ControlRegedit.h"

#include "FileOperateClass.h"

#include "VisitDatabaseInterface.h"

#include "FileOperateDlg.h"

#include "UsingMethodDlg.h"

#include "ControlSystem.h"

#pragma comment( lib, "aced" )
/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicFundApp:
// See ProgrammeTechnicFund.cpp for the implementation of this class
//

class CProgrammeTechnicFundApp : public CWinApp
{
public:
	CProgrammeTechnicFundApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgrammeTechnicFundApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CProgrammeTechnicFundApp)
	afx_msg void OnAppAbout();
	afx_msg void OnUsingMethod();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_PROGRAMMETECHNICFUND_H__5283924B_9304_4A23_A46C_615704573B1B__INCLUDED_)
