// UsingSocketCommunication.cpp: implementation of the CUsingSocketCommunication class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProgrammeTechnicFund.h"
#include "UsingSocketCommunication.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUsingSocketCommunication::CUsingSocketCommunication()
{
#ifdef _WIN32	// �����win32ϵͳ

	WSADATA wsaData;
	
	int nResult = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
	
	if ( NO_ERROR != nResult )
	{

	}
	
#endif
}

CUsingSocketCommunication::~CUsingSocketCommunication()
{

#ifdef _WIN32	// ����WSACleanup

	WSACleanup();

#endif

}
int HintMsg( IN	 HWND		hWnd,
			 IN	 string		strHintMsg,
			 IN	 string		strPlaceHint,
			 IN	 UINT		uType )
{
	//��ô�����
	int nError = WSAGetLastError();

	//ת��������Ϊ�ַ�
	CHAR szError[MAX_PATH] = {0};
	sprintf( szError, "%d", nError );

	CHAR szErrorHint[MAX_PATH] = {0};
	
	strcpy( szErrorHint, strHintMsg.c_str() );
	strcat( szErrorHint, szError );
	
	int nResult = ::MessageBox( hWnd,
								szErrorHint,
								strPlaceHint.c_str(),
								uType );
	
	return nResult;
}

////////////////////////////////////////////
CTCP_SocketCommuntication::CTCP_SocketCommuntication()
{

}

CTCP_SocketCommuntication::~CTCP_SocketCommuntication()
{
	WSACleanup();//�����׽���ʧ�ܣ�����Winsock�⣬���Ҳ�����Ҫ�����κ�Winsock����ʱ���������̻�ж������⣬���ͷ���Դ��	
}

int CTCP_SocketCommuntication::InitializeSocket( IN	SOCKET		&sockCommunication,
											 	 IN	u_short		 dwCommunicationPort )
{
	//����Winsock DLL����Ӧ�汾���������Winsock֮ǰ��û�м���Winsock�⣬��������ͻ᷵��һ��SOCKET_ERROR��������Ϣ��WSANOTINITIALISE
	WSADATA		wsaData;
	WORD		wVersionRequired = MAKEWORD(2,2);//wVersionRequested��������ָ��׼�����ص�Winsock��İ汾��
												 //��λ�ֽ�ָ������Ҫ��Winsock��ĸ��汾������λ�ֽ��������汾��
												 //�ú�MAKEWORD( X , Y )�����У�x�Ǹ�λ�ֽڣ� y�ǵ�λ�ֽڣ�

	int nResult = WSAStartup( wVersionRequired, &wsaData );//WSAStartup������صĿ�汾�йص���Ϣ����WSADATA�ṹ�У�

	if ( 0 != nResult )
	{
		HintMsg( NULL,
				 "ERROR HINT : WSAStartup FAIL ## error = ",
				 "PLACE : CTCP_SocketCommuntication::InitializeSocket()",
				 MB_OK );

		return -1;
	}

	//�����׽���
	sockCommunication = WSASocket( AF_INET,			//��Э��ĵ�ַ����.����뽨��һ��UDP��TCP�׽��֣����ó���AF_INET��ָ��������Э�飨IP����ָ��׼��ʹ������Э��
								   SOCK_STREAM,		//��Э����׽�������
								   IPPROTO_IP,		//��ָ���ĵ�ַ������׽��������ж����Ŀʱ���Ϳ�������ֶ����޶�ʹ���ض����䡣
								   NULL,
								   0,
								   SOCK_STREAM );

	if ( SOCKET_ERROR == sockCommunication )
	{
		HintMsg( NULL,
				 "ERROR HINT : WSASocket FAIL ## error = ",
				 "PLACE : CTCP_SocketCommuntication::InitializeSocket()",
				 MB_OK );

		return -1;
	}

	//��ָ��Э����׽����뱾�ؽӿڵ�IP��ַ�Ͷ˿ڱ�Ű󶨡�Ϊĳ���ض�Э�鴴�����׽��֣��ͱ��뽫�׽��ְ󶨵�һ����֪��ַ��bind�����ɽ�ָ�����׽���ͬһ����֪��ַ�󶨵�һ��
	sockaddr_in service;

	service.sin_addr.s_addr	= htonl(INADDR_ANY);
	service.sin_port		= htons( dwCommunicationPort );
	service.sin_family		= AF_INET;

	int nStatus = bind( sockCommunication,		//�ȴ��ͻ������ӵ��Ǹ��׽���
						(SOCKADDR*) &service,
						sizeof(service) );		//Ҫ���ݵġ���Э������ĵ�ַ�ĳ��ȡ�
	
	if ( SOCKET_ERROR == nStatus )
	{
		closesocket( sockCommunication );	//�ر��׽���
		
		HintMsg( NULL,
				 "ERROR HINT : bind FAIL ## error = ",
				 "PLACE : CTCP_SocketCommuntication::InitializeSocket()",
				 MB_OK );

		return -1;
	}

	return 0;
}

///// __stdcall����Լ��(�������Ĳ�����������ͨ��ջ���ݣ������õĺ����ڷ���ǰ�����Ͳ������ڴ�ջ)
unsigned __stdcall CTCP_SocketCommuntication::__RunNetWorkListenTask( LPVOID param )
{
	//��ʼ��socket
	SOCKET sockListen;

	int nResult = InitializeSocket( sockListen, 1982 );

	if ( 0 != nResult )
	{
		closesocket( sockListen );

		HintMsg( NULL,
				 "ERROR HINT : InitializeSocket FAIL ## error = ",
				 "PLACE : CTCP_SocketCommuntication::__RunNetWorkListenTask",
				 MB_OK );

		return -1;
	}

	//�����˿�
	nResult = listen( sockListen, SOMAXCONN );

	if ( SOCKET_ERROR == nResult )
	{
		closesocket( sockListen );

		HintMsg( NULL,
				 "ERROR HINT : listen FAIL ## error = ",
				 "PLACE : CTCP_SocketCommuntication::__RunNetWorkListenTask",
				 MB_OK );

		return -1;
	}

	//��������
	SOCKET sockReceive = SOCKET_ERROR;

	sockaddr_in  client;
	int			 nAddrSize = sizeof(client);

	while ( TRUE )
	{
		sockReceive = accept( sockListen,
							  (struct sockaddr*)&client,
							  &nAddrSize );
		
		if ( INVALID_SOCKET == sockReceive )
		{
			HintMsg( NULL,
					 "ERROR HINT : accept FAIL ## error = ",
					 "PLACE : CTCP_SocketCommuntication::__RunNetWorkListenTask",
					 MB_OK );

			break;
		}
		
		COMMUNICATION iCommunication;
		
		iCommunication.AcceptSocket = sockReceive;
		
		//��������
		UINT uThreadid = 0;

		HANDLE hReceiveThread = (HANDLE)_beginthreadex( NULL,
														0,
														ReceiveControlMsgTask,
														(LPVOID)&iCommunication,
														0,
														&uThreadid );

		if ( INVALID_HANDLE_VALUE == hReceiveThread )
		{
			HintMsg( NULL,
					 "ERROR HINT : _beginthreadex FAIL ## error = ",
					 "PLACE : CTCP_SocketCommuntication::__RunNetWorkListenTask",
					 MB_OK );
			
			return -1;
		}

		CloseHandle( hReceiveThread );
	}
	
	closesocket( sockListen );

	return 0;
}

ACE_Thread_Mutex CTCP_SocketCommuntication::m_mutex;

unsigned _stdcall CTCP_SocketCommuntication::ReceiveControlMsgTask(LPVOID param)
{
	//	ACE_GUARD_RETURN(ACE_Thread_Mutex, lock, m_mutex, -1);
	
	PCOMMUNICATION pCommunication = (PCOMMUNICATION)param;

	COMMUNICATION_DATA iReceive;

	memset( &iReceive, 0, sizeof(COMMUNICATION_DATA) );

	int nResult = recv( pCommunication->AcceptSocket,
						(PCHAR)&iReceive,
						sizeof(COMMUNICATION_DATA),
						0 );

	if ( SOCKET_ERROR == nResult )
	{
		HintMsg( NULL,
				 "ERROR HINT : recv FAIL ## error = ",
				 "PLACE : CTCP_SocketCommuntication::ReceiveControlMsgTask",
				 MB_OK );
		
		return -1;
	}

	DWORD dwThreadId = ::GetCurrentThreadId();

	CHAR szThreadid[1024] = {0};

	sprintf( szThreadid, "%d", dwThreadId );

	::MessageBox( NULL, iReceive.szMsg, szThreadid, MB_OK );
	
	closesocket( pCommunication->AcceptSocket );

	return 0;
}

BOOL CTCP_SocketCommuntication::StartNetWorkListenTask()
{
	UINT uThreadId = 0;

	HANDLE hThread = (HANDLE)_beginthreadex( NULL,
											 0,
											 __RunNetWorkListenTask,
											 0,
											 0,
											 &uThreadId );

	if ( INVALID_HANDLE_VALUE == hThread )
	{
		HintMsg( NULL,
				 "ERROR HINT : _beginthreadex",
				 "PLACE : CTCP_SocketCommuntication::StartNetWorkListenTask()",
				 MB_OK );
		
		return FALSE;
	}

	CloseHandle( hThread );

	return TRUE;
}
//////////////////////////////////////////// UDPͨѶ��
CUDP_SocketCommuntication::CUDP_SocketCommuntication()
{
	m_UdpSocket = socket(PF_INET, SOCK_DGRAM, 0);
	
	if ( m_UdpSocket == INVALID_SOCKET )
	{

	}
}

CUDP_SocketCommuntication::~CUDP_SocketCommuntication()
{
	closesocket( m_UdpSocket );
}

int CUDP_SocketCommuntication::CreateReceiveTask()
{	
	sockaddr_in srv;
	
	srv.sin_family		= PF_INET;
	srv.sin_addr.s_addr = htonl( INADDR_ANY );	// �κε�ַ
	srv.sin_port		= htons( 1111 );
	
	if ( 0 != bind( m_UdpSocket,
		       (struct sockaddr *)&srv,
		       sizeof(srv) ) )
	{
		closesocket( m_UdpSocket );
		return false;
	}
	
	UINT uThreadId = 0;
	
	HANDLE hThreadHandle = (HANDLE) _beginthreadex( NULL,
													0,
													__ReceiveTask,
													(LPVOID)this,
													0,
													&uThreadId );
	
	if ( INVALID_HANDLE_VALUE == hThreadHandle )
	{
		//LogError
	}
	
	CloseHandle( hThreadHandle );

	return 0;
}

unsigned __stdcall CUDP_SocketCommuntication::__ReceiveTask(LPVOID param)
{
	CUDP_SocketCommuntication *pCommuntication =
									(CUDP_SocketCommuntication*)param;

	char        buf[4096] = {0};
	sockaddr_in client;			// �������ݹ����ĵ�ַ
	int         len = sizeof(client);

	while( TRUE )
	{
		int result = recvfrom( pCommuntication->m_UdpSocket,
							   buf,
							   sizeof(buf)-1,
							   0,
							   (sockaddr*)&client,
							   (int*)&len);
		
		if ( result > 0 )
		{
			fflush(0);
		}
		::MessageBox( NULL, buf, "", MB_OK );
	}

	return 0;
}


bool CUDP_SocketCommuntication::SendMsg( PCHAR		Msg,
										 int		Len,
										 PCHAR		host,
										 short		port )
{
	signed int		 Sent;
	hostent			*hostdata;

	if ( atoi(host) )	// �Ƿ�IP��ַΪ��׼��ʽ
	{
		u_long ip = inet_addr( host );
		hostdata  = gethostbyaddr( (PCHAR)&ip,
								   sizeof(ip),
								   PF_INET );
	}
	else	// ����������ǻ�����
	{
		hostdata = gethostbyname( host );
	}
	
	if ( !hostdata )
	{
		fflush(0);
		return false;
	}
	
	sockaddr_in dest;	// ����Ŀ���ַ
	
	dest.sin_family  = PF_INET;
	dest.sin_addr	 = *(in_addr *)(hostdata->h_addr_list[0]);
	dest.sin_port	 = htons( port );

	//���ݷ���
	Sent = sendto( m_UdpSocket,
				   Msg,
				   Len,
				   0,
				   (sockaddr *)&dest,
				   sizeof(sockaddr_in) );
	
	if ( Sent != Len )
	{
		fflush(0);
		return false;
	}
	
	return true;
}
