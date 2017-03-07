// Phone.h : main header file for the PHONE DLL
//

#if !defined(AFX_PHONE_H__53C8C668_3837_11D3_BB17_00104BC71186__INCLUDED_)
#define AFX_PHONE_H__53C8C668_3837_11D3_BB17_00104BC71186__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CExchange;

#define MAXWAVEBLOCK  10//�����ڴ����
#define MAXWAVEBUFFER 800//ÿ���ڴ��С

extern CString RemoteHost;//Զ��������
extern CString RemoteIp;//Զ������IP��ַ
extern long RemotePort;//Զ�˵绰IP�˿�
extern HWAVEOUT hWaveOut;
extern WAVEHDR WaveHdrOut[MAXWAVEBLOCK];
extern bool m_Opened;//�绰״̬

/////////////////////////////////////////////////////////////////////////////
// CPhoneApp
// See Phone.cpp for the implementation of this class
//

class CPhoneApp : public CWinApp
{
public:
	CPhoneApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhoneApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPhoneApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHONE_H__53C8C668_3837_11D3_BB17_00104BC71186__INCLUDED_)
