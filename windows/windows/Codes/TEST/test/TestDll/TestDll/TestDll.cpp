// TestDll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "TestDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CTestDllApp

BEGIN_MESSAGE_MAP(CTestDllApp, CWinApp)
END_MESSAGE_MAP()


// CTestDllApp construction

CTestDllApp::CTestDllApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTestDllApp object

CTestDllApp theApp;


// CTestDllApp initialization

/********************************************
��������:GetHostName
���\�F?��{���I���햼��
�ԉ�:strHostName-�{�����햼��
*********************************************/
extern "C" _declspec(dllexport) void GetHostName(LPTSTR strHostName )
{
	//�@�ʐ�??���������v�g�pstrcpy��?�������I�n���C���s�\���ړ����B
	strcpy(strHostName, theApp.GetHostName());
}
/********************************************
��������:GetSystemType
���\�F?��{������n?�Ŗ{
�ԉ�:strSystemType-�{������n?�Ŗ{
*********************************************/
extern "C" _declspec(dllexport) void GetSystemType(char * strSystemType)
{
	strcpy(strSystemType, theApp.GetSystemType());
}
/********************************************
��������:GetIPAddressList
���\�F?��{���IIP�n��
�ԉ�:lpIPList-�{���IIP�n����?�ClpNumber IP�n������
*********************************************/
extern "C" _declspec(dllexport) void GetIPAddressList(char ** lpIPList,DWORD *lpNumber)
{
	theApp.GetIPAddressList(lpIPList,lpNumber);
}

#include "TestDlg.h"

BOOL CTestDllApp::InitInstance()
{
	CWinApp::InitInstance();

	CTestDlg dlg;
	dlg.DoModal();

	::MessageBox(NULL, "CTestDllApp::InitInstance", "Title", NULL);

	return TRUE;
}

char* CTestDllApp::GetHostName(void)
{
	char* lpsz = new char[1024];
//	m_SystemInfo.GetHostName(lpsz);
	::MessageBox(NULL, "CTestDllApp::GetHostName", "Title", NULL);

	return lpsz;
}
//�n??�^
char* CTestDllApp::GetSystemType(void)
{
	char* lpsz = new char[1024];
//	m_SystemInfo.GetlSystemType(lpsz);
	::MessageBox(NULL, "CTestDllApp::GetSystemType", "Title", NULL);

	return lpsz;
}
//IP�n��
void CTestDllApp::GetIPAddressList(char ** lpIPList,DWORD *lpNumber)
{
//	m_SystemInfo.GetIPAddressList(lpIPList,lpNumber);
	::MessageBox(NULL, "CTestDllApp::GetIPAddressList", "Title", NULL);
}
