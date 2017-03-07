// ClientTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientTest.h"
#include "ClientTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CClientTestDlg dialog

CClientTestDlg::CClientTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientTestDlg)
	str = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	IsTrue = FALSE;
}

void CClientTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientTestDlg)
	DDX_Control(pDX, IDC_LIST, list);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, str);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientTestDlg, CDialog)
	//{{AFX_MSG_MAP(CClientTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, OnSend)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_CLIENT_READCOLOSE,OnReadClose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientTestDlg message handlers

BOOL CClientTestDlg::OnInitDialog()
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

void CClientTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientTestDlg::OnPaint() 
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
HCURSOR CClientTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientTestDlg::OnOK() 
{//����
	LPCTSTR ip;

	CGetIP di;
	di.ipstr = _T("127.0.0.1");
	if(di.DoModal() == IDOK)
	{		
		if(di.ipstr.IsEmpty())
		{
			MessageBox("û������IP��ַ��","������IP��ַ",NULL);
			return;
		}
		else
			ip = di.ipstr;
	}
	else
		return;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,1),&wsaData)) //����Windows Sockets DLL
	{ 
         list.InsertString(0,"Winsock�޷���ʼ��!");
         WSACleanup();
         return;
	}

	list.InsertString(0,"��������ʼ����SOCKET��");

	ServerSocket=socket(PF_INET,SOCK_STREAM,0);    //������������Socket������ΪSOCK_STREAM���������ӵ�ͨ��

    if(ServerSocket == INVALID_SOCKET)
	{
         list.InsertString(0,"�޷�����������socket!");
         return;
	}

    list.InsertString(0,"�������˿�:8001.");

	DWORD dwip;
	if((dwip=inet_addr(ip))==INADDR_NONE)
	{
		list.InsertString(0,"IP��ֵ����");
		return;
	}
    sockStruct.sin_family=AF_INET; //ʹ��TCP/IPЭ��
    sockStruct.sin_port = htons(8001);
	sockStruct.sin_addr.S_un.S_addr = dwip;

	if(connect(ServerSocket,(LPSOCKADDR)&sockStruct,sizeof(sockStruct)) == SOCKET_ERROR)
    {
	    list.InsertString(0,"�޷����ӷ�������");
		list.InsertString(0,"");
        return;
	}
	else
	{
		char *buf = new char[100];
		strcpy(buf,"����վ���ӳɹ���������������������Ϣ��");
		send(ServerSocket,buf,100,0);
		delete buf;
	}

	WSAAsyncSelect(ServerSocket,m_hWnd,WM_CLIENT_READCOLOSE,FD_READ|FD_CLOSE);
         // ������Ӧ���ݸ����ڵ���ϢΪWM_SERVER_ACCEPT �������Զ�����Ϣ

 	list.InsertString(0,"���ӷ������ɹ���");
	list.InsertString(0,"IP��ַ:"+di.ipstr);
	IsTrue = TRUE;
    return;
}


LRESULT CClientTestDlg::OnReadClose(WPARAM wParam,LPARAM lParam)
{
	char *buf = new char[100];
	CString str;
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
		if(recv(ServerSocket,(char *)&msg,sizeof(msg),0) == SOCKET_ERROR)
		{
			list.InsertString(0,"�������ݷ�������");
			return 0L;
		}
		str.Format("%s",msg.msg);
		list.InsertString(0,str);
		break;
	case FD_CLOSE:
		closesocket(ServerSocket);
		list.InsertString(0,"�������˳���");
		IsTrue = FALSE;
		break;
	}
	return 0L;
}

void CClientTestDlg::OnSend() 
{//���Ͱ�ť
	if(!IsTrue)
	{
		list.InsertString(0,"��������û�������أ�");
		return;
	}
	UpdateData();
	if(str.IsEmpty())
	{
		list.InsertString(0,"���͵��ַ�������Ϊ�ա�");
		return;
	}
	strcpy(msg.msg,(LPCTSTR)str);
	msg.i = 0;
	if(send(ServerSocket,(char *)&msg,sizeof(msg),0) == SOCKET_ERROR)//	recv(ServerSocket,buf,sizeof(buf),0);
	{
		list.InsertString(0,"�������ݷ�������");
	}
	else
		list.InsertString(0,str);
	str.Empty();
	UpdateData(FALSE);
	((CEdit *)GetDlgItem(IDC_EDIT_MESSAGE))->SetActiveWindow();
}

BOOL CClientTestDlg::DestroyWindow() 
{
    WSACleanup();
	
	return CDialog::DestroyWindow();
}
