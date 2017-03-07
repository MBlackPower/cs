// modem.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "modem.h"
#include "modemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModemApp

BEGIN_MESSAGE_MAP(CModemApp, CWinApp)
	//{{AFX_MSG_MAP(CModemApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModemApp construction

CModemApp::CModemApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CModemApp object

CModemApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CModemApp initialization

BOOL CModemApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CModemDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
/*	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDABOUT)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
		
		
	}*/

	return FALSE;
}
