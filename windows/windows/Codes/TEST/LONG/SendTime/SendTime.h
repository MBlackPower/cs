// SendTime.h : main header file for the SENDTIME application
//

#if !defined(AFX_SENDTIME_H__CC220FEF_95D6_4C2C_8FCE_F7D4C43F84CE__INCLUDED_)
#define AFX_SENDTIME_H__CC220FEF_95D6_4C2C_8FCE_F7D4C43F84CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSendTimeApp:
// See SendTime.cpp for the implementation of this class
//

class CSendTimeApp : public CWinApp
{
public:
	CSendTimeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendTimeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSendTimeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDTIME_H__CC220FEF_95D6_4C2C_8FCE_F7D4C43F84CE__INCLUDED_)
