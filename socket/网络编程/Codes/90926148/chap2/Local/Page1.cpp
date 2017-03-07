// Page1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chapter5.h"
#include "Page1.h"
#include ".\page1.h"

// CPage1 �Ի���

IMPLEMENT_DYNAMIC(CPage1, CDialog)
CPage1::CPage1(CWnd* pParent /*=NULL*/)
	: CDialog(CPage1::IDD, pParent)
	, m_GetComputerName(_T(""))
	, m_gethostname(_T(""))
	, m_IPAddress(_T(""))
{
}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_GetComputerName);
	DDX_Text(pDX, IDC_EDIT2, m_gethostname);
	DDX_Text(pDX, IDC_EDIT3, m_IPAddress);
}


BEGIN_MESSAGE_MAP(CPage1, CDialog)
END_MESSAGE_MAP()


// CPage1 ��Ϣ�������

BOOL CPage1::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// ��ȡ��������ƺ�IP��ַ
int CPage1::GetInfo(void)
{
	#define BUFSIZE 1024

	LPTSTR lpszSystemInfo;      // pointer to system information string 
	DWORD cchBuff = BUFSIZE;    // size of computer
	TCHAR tchBuffer[BUFSIZE];   // buffer for string

	lpszSystemInfo = tchBuffer; 

	// Get and display the name of the computer. 
	if( GetComputerName(lpszSystemInfo, &cchBuff) )
	{
		m_GetComputerName.AppendFormat("%s\t//GetComputerName()", lpszSystemInfo);
		UpdateData(False);
	}

	WSADATA     WSAData;
	int WSAReturn;
	//��ʹ��WinSock API֮ǰ���������WSAStartup������
	//ֻ�иú����ɹ����أ���ʾ��WinSock��ɹ��ؽ��������ӣ���
	//�ſ��Ե�������Windows Sockets DLL�еĺ���
	WSAReturn = WSAStartup( 0x0101, &WSAData );
	if( WSAReturn == 0 ){
		if( gethostname(lpszSystemInfo, cchBuff) )
		{
			m_gethostname.AppendFormat("%s\t//gethostname()", lpszSystemInfo);
			UpdateData(False);
		}

		struct hostent *p_HostEnt;
		p_HostEnt = gethostbyname(lpszSystemInfo);
		if(p_HostEnt != NULL)
		{
			char  Hostaddress[20]; // ����IP��ַ
			wsprintf( Hostaddress, " %d. %d. %d. %d",
			( p_HostEnt->h_addr_list[0][0] & 0x00ff ),
			( p_HostEnt->h_addr_list[0][1] & 0x00ff ),
			( p_HostEnt->h_addr_list[0][2] & 0x00ff ),
			( p_HostEnt->h_addr_list[0][3] & 0x00ff ) );
			m_IPAddress.Format(Hostaddress);
			UpdateData(False);
			//����WSACleanup��������WinSock�����������Ա��ͷ���ռ�õ���Դ
			WSACleanup();
		}
	}

	return 0;
}
