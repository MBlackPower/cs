// PublicNetSoftDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PublicNetSoft.h"
#include "PublicNetSoftDlg.h"

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
	public:
	virtual BOOL DestroyWindow();
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPublicNetSoftDlg dialog

CPublicNetSoftDlg::CPublicNetSoftDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPublicNetSoftDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPublicNetSoftDlg)
	str = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	IsTrue = FALSE;
	Client = INVALID_SOCKET;
}

void CPublicNetSoftDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPublicNetSoftDlg)
	DDX_Control(pDX, IDC_LIST, list);
	DDX_Text(pDX, IDC_EDIT, str);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPublicNetSoftDlg, CDialog)
	//{{AFX_MSG_MAP(CPublicNetSoftDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, OnSend)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_CLIENT_ACCEPT,OnAccept)
	ON_MESSAGE(WM_CLIENT_READCLOSE,OnReadClose)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPublicNetSoftDlg message handlers

BOOL CPublicNetSoftDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPublicNetSoftDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPublicNetSoftDlg::OnPaint() 
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
HCURSOR CPublicNetSoftDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CAboutDlg::DestroyWindow() 
{
	return CDialog::DestroyWindow();
}

/*
	//}}AFX_VIRTUAL

	LRESULT OnAccept(WPARAM wParam, LPARAM lParam);
	LRESULT OnReadClose(WPARAM wParam,LPARAM lParam);

// Implementation

typedef struct ZyMsg
{
	char msg[100];
	int i;
}Msg;

public:

	SOCKET Client;        //�ͻ�����������
	SOCKET ServerSocket;                 //SOCKET 
	SOCKADDR_IN m_sockServerAddr;          //SOCKET �ṹ

	BOOL IsTrue;

	Msg msg;

	ON_MESSAGE(WM_CLIENT_ACCEPT,OnAccept)
	ON_MESSAGE(WM_CLIENT_READCLOSE,OnReadClose)
*/



void CPublicNetSoftDlg::OnOK() 
{//��ʼ����󶨷�����
    WSADATA wsaData;
    int iErrorCode;
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

    m_sockServerAddr.sin_family = AF_INET;
    m_sockServerAddr.sin_addr.s_addr = INADDR_ANY;   //�����е�IP��ַ������Ϣ
    m_sockServerAddr.sin_port = htons(8001);

    if (bind(ServerSocket,(LPSOCKADDR)&m_sockServerAddr,sizeof(m_sockServerAddr)) == SOCKET_ERROR) //��ѡ���Ķ˿ڰ�
    {
	    list.InsertString(0,"�޷��󶨷�������");
        return;
	}

    list.InsertString(0,"�������˿�:8001.");

    iErrorCode=WSAAsyncSelect(ServerSocket,m_hWnd,WM_CLIENT_ACCEPT,FD_ACCEPT);
         // ������Ӧ���ݸ����ڵ���ϢΪWM_SERVER_ACCEPT �������Զ�����Ϣ

    if (iErrorCode == SOCKET_ERROR) 
	{
         list.InsertString(0,"WSAAsyncSelect�趨ʧ��!�������������������Ϣ");
         return;
	}

    if (listen(ServerSocket,1) == SOCKET_ERROR) //��ʼ�����ͻ���������
	{
		list.InsertString(0,"����������ʧ��!");
        return;
	}

	IsTrue = TRUE;

 	list.AddString("�������󶨼����ɹ���");
    return; 
}

void CPublicNetSoftDlg::OnSend() 
{//��������
	if(!IsTrue)
		list.InsertString(0,"��û�й���վ���ӣ��������û�г�ʼ���ɹ���");
	UpdateData();
	strcpy((char *)msg.msg,(LPCTSTR)str);
	msg.i = 0;
	if(send(Client,(char *)&msg,sizeof(msg),0) == SOCKET_ERROR)//	recv(ServerSocket,buf,sizeof(buf),0);
	{
		list.InsertString(0,"�������ݴ���");
		return;
	}
	else
		list.InsertString(0,str);
	list.InsertString(0,str);
	str.Empty();
	UpdateData(FALSE);
	((CEdit *)GetDlgItem(IDC_EDIT))->SetActiveWindow();
}

LRESULT CPublicNetSoftDlg::OnAccept(WPARAM wParam,LPARAM lParam)
{//�Զ�����տͻ����������Ϣ   ON_MESSAGE(WM_CLIENT_ACCEPT,OnAccept)
	if (WSAGETSELECTERROR(lParam))
	{
		list.InsertString(0,"Error detected on entry into OnServerAccept.");
		return 0L;
	}
	
	if(WSAGETSELECTEVENT(lParam) == FD_ACCEPT)//���
	{
	    Client = accept(ServerSocket,(LPSOCKADDR)&m_sockServerAddr,0);

	    if (Client == INVALID_SOCKET)
		{
			list.InsertString(0,"Server socket failed to accept connection.");
			return 0L;
		}
		
		WSAAsyncSelect(Client,m_hWnd,WM_CLIENT_READCLOSE,FD_READ|FD_CLOSE);

		IsTrue = TRUE;
	}
	
	list.InsertString(0,"�й���վ�������˷�������");
	
	return 0L;
}


LRESULT CPublicNetSoftDlg::OnReadClose(WPARAM wParam,LPARAM lParam)
{//�Զ���Ĺر��뻺��������Ϣ
	if(!IsTrue)
	{
		list.InsertString(0,"�����ݵ������û�й���վ���ӡ�");
	}

	CString str;
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
		if(recv(Client,(char *)&msg,sizeof(msg),0) == SOCKET_ERROR)
		{
			list.InsertString(0,"�������ݷ�������");
			return 0;
		}
		str.Format("%s",msg.msg);
		list.InsertString(0,str);
		break;
	case FD_CLOSE:
		str = _T("����վ�˳���");
		list.InsertString(0,str);
		closesocket(Client);
		IsTrue = FALSE;
		break;
	}
	return 0L;
}

BOOL CPublicNetSoftDlg::DestroyWindow() 
{//�������˳�ʱ����SOCKET���
	WSACleanup();
	
	return CDialog::DestroyWindow();
}
