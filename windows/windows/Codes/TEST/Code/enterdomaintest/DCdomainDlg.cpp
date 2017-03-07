// DCdomainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DCdomain.h"
#include "DCdomainDlg.h"
#include "Lm.h"
#include "Lmjoin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "Winnt.h"
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDCdomainDlg dialog

CDCdomainDlg::CDCdomainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDCdomainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDCdomainDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDCdomainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDCdomainDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDCdomainDlg, CDialog)
	//{{AFX_MSG_MAP(CDCdomainDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDCdomainDlg message handlers

BOOL CDCdomainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDCdomainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDCdomainDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDCdomainDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDCdomainDlg::OnButton1() 
{       	
//�жϵ�ǰ��������������
        if(TRUE==Is_Win2000_DomainController())
		{
             AfxMessageBox("��ǰ��������������");
		}
		else
		{
              AfxMessageBox("��ǰ����������������");
		}
//�жϵ�ǰ�������������
		UINT uType;		
		char SErvername[100];

		GetGroupInfo(SErvername, &uType);
//��ע����жϵ�¼��
		HKEY hKey = HKEY_LOCAL_MACHINE;
		CString strSubKey = _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\winlogon");
		HKEY hNewKey = 0;
		LONG lResult = ERROR_SUCCESS;
		lResult = ::RegOpenKeyEx(hKey, 
			                     strSubKey, 
			                     0,
			                     KEY_READ, 
			                     &hNewKey);
		if(ERROR_SUCCESS != lResult)
		{
			char ch[256] = {0};
//			sprintf(ch, "����ִ��ʧ�� [%d][%d]", GetLastError(), lResult);
			RegCloseKey(hKey);
			RegCloseKey(hNewKey);			
//			AfxMessageBox(ch);
			return ;
		}
		DWORD dwLp = 1000;
		DWORD dwRegType = REG_SZ;
		unsigned char bRtn[100] = {0};
		
		lResult = ::RegQueryValueEx(hNewKey, 
			                        "AltDefaultDomainName", 
			                        NULL, 
			                        &dwRegType, 
			                        bRtn, 
			                        &dwLp);

		if(ERROR_SUCCESS != lResult)
		{
			RegCloseKey(hKey);
			AfxMessageBox("����ִ��ʧ��");
			return ;
		}	
		RegCloseKey(hNewKey);
		RegCloseKey(hKey);	
		TCHAR lpBuffer[100];
		DWORD lpnSize=MAX_PATH;
		GetComputerName(lpBuffer, //  LPTSTR
			            &lpnSize  ); //LPDWORD
		CString str;
		str.Format("%s",lpBuffer);
		
			
		if (CString(bRtn)==str) 
		{
               AfxMessageBox("��¼����");
		}
		else
		{
               AfxMessageBox("��¼����");
		}
		//UpdateData(FALSE);
}
BOOL CDCdomainDlg::Is_Win2000_DomainController()
{
	OSVERSIONINFOEX osvi;
	DWORDLONG dwlConditionMask = 0;
	
	// Initialize the OSVERSIONINFOEX structure.
	//��һ���ڴ�������0
	ZeroMemory(&osvi,//ָ��������ڴ�������ָ��
		       sizeof(OSVERSIONINFOEX));//�ڴ���С
	
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	osvi.dwMajorVersion = 5;
	osvi.wProductType = VER_NT_DOMAIN_CONTROLLER;
	
	// Initialize the condition mask.
	VER_SET_CONDITION( dwlConditionMask, VER_MAJORVERSION, 
	                   VER_GREATER_EQUAL );
	VER_SET_CONDITION( dwlConditionMask, VER_PRODUCT_TYPE, 
		VER_EQUAL );
	
	// Perform the test.
	//VerifyVersionInfo������汾�š��ΰ汾���Լ��������
	return VerifyVersionInfo(&osvi, 
		                     VER_MAJORVERSION | VER_PRODUCT_TYPE,
		                     dwlConditionMask);
}
int CDCdomainDlg::GetGroupInfo(LPSTR strServerName, UINT *uType)
{
	LPWSTR buffer;	
		ZeroMemory(strServerName,_tcslen(strServerName));
	WCHAR pszServerName[MAX_PATH]={0};

	DWORD Kc = MultiByteToWideChar(CP_ACP, 
		0, 
		strServerName,
		-1,	
		pszServerName,
		sizeof(pszServerName));

	NET_API_STATUS net = NetApiBufferAllocate(1024,(LPVOID*)&buffer);	
	if(net != NERR_Success)		
	{		
		return net;		
	}	
	NETSETUP_JOIN_STATUS netStatus;	
	net = NetGetJoinInformation(NULL,&buffer,&netStatus);	
	if(net != NERR_Success)		
	{		
		net = NetApiBufferFree((LPVOID*)buffer);		
		if(net != NERR_Success)			
		{			
			return net;			
		}		
		return net;		
	}	
	DWORD rc = WideCharToMultiByte(CP_ACP,0,buffer,-1,strServerName,256,NULL,NULL);	
	if(rc==0)		
	{		
		int error = GetLastError();		
		net = NetApiBufferFree((LPVOID*)buffer);		
		if(net != NERR_Success)			
		{
			return net;
		}
		return error;		
	}	
	if(netStatus == NetSetupWorkgroupName)//The computer is joined to a workgroup	
	{
		*uType = JOIN_GROUP;
		AfxMessageBox("��ǰ�������������");
	}	
	else if(netStatus == NetSetupDomainName)//The computer is joined to a domain		
	{	
		*uType = JOIN_DOMAIN;
		AfxMessageBox("��ǰ�������������");
	}
	else		
	{
		*uType = NOT_JOIN;
		AfxMessageBox("��ǰ�����û�м����������");		
	}
	net = NetApiBufferFree((LPVOID*)buffer);	
	if(net != NERR_Success)		
	{		
		return net;		
	}	
	return 0;	
}




