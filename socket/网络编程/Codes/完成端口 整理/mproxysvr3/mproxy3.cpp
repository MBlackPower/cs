//*******************************************************************
//              
//  FILE:       mproxy3.cpp
//              
//  AUTHOR:     sam sha
//              
//  PROJECT:    mproxysvr3
//              
//  COMPONENT:  CMProxy3
//              
//  DATE:       23.06.2003
//              
//  COMMENTS:   - ����ģ��
//              
//              
//*******************************************************************
// Includes
 
// mproxy3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iodata.h"
#include "mproxy3.h"
#include <map>
#include "assert.h"
#include "greta/regexpr2.h"


using namespace std;
using namespace regex;



const int	 THREAD_MAXNUM = 10;//�߳���Ŀ���ֵ

DWORD WINAPI MProxy3Thread(LPVOID pArgu);
//*******************************************************************
//              
//  FUNCTION:   - CMProxy3
//              
//  RETURNS:    -
//              
//  PARAMETERS: - int nListenPort ��������˿�,const char * pAddr2 ���������ַ, int nPort2 ��������˿�
//              
//  COMMENTS:   - ������ΪӦ��windows socket IO��ɶ˿�ģ���ṩ��������ԭ�����.Ŀǰ֧��http��һ���Ͷ�������
//                ����ָ���������κ��������ӵĶ�������
//                 
//*******************************************************************

CMProxy3::CMProxy3(int nListenPort ,const char * pAddr2, int nPort2)
{
	m_nListenPort = nListenPort;
	m_Addr2[0] = 0; //�Ƿ��ж������������
	if (pAddr2)
	{
		strcpy(m_Addr2,pAddr2);
	}
	m_nPort2 = nPort2;
	m_hThread = NULL;
	m_nThreadState = STOP;
}

CMProxy3::~CMProxy3()
{

}
//*******************************************************************
//              
//  FUNCTION:   -Start()
//              
//  RETURNS:    -
//              
//  PARAMETERS: -
//              
//  COMMENTS:   - ���������߳�
//              
//              
//*******************************************************************

void CMProxy3::Start()
{
	
	DWORD dwThreadID;
	m_nThreadState = RUNNIG; 
	m_hThread = CreateThread(NULL,0,MProxy3Thread,(LPVOID)this,0,&dwThreadID);
	if (m_hThread != NULL)
	{
		m_nThreadState = RUNNIG;
	}
	else
	{
		m_nThreadState = STOP;
	}
	
}

//*******************************************************************
//              
//  FUNCTION:   - Stop()
//              
//  RETURNS:    -
//              
//  PARAMETERS: -
//              
//  COMMENTS:   - ֹͣ������������¸���������ֹͣ
//              
//              
//*******************************************************************

void CMProxy3::Stop()
{
	m_nThreadState = STOP;
	
}
//*******************************************************************
//              
//  FUNCTION:   - SafeClose
//              
//  RETURNS:    -
//              
//  PARAMETERS: - LPWSAOVERLAPPEDEX lpOvlpEx ��չ���ص�IOģ��
//              
//  COMMENTS:   - ��Ҫ�ر�socket����ʱ��Ҫ��ȫ�ر�һ��soket
//              
//              
//*******************************************************************

void SafeClose(LPWSAOVERLAPPEDEX lpOvlpEx)
{
	if ( lpOvlpEx->pPair != NULL )
	{
		SOCKET hPair = lpOvlpEx->hSocketPair;
		lpOvlpEx->pPair->hSocketPair = INVALID_SOCKET - 1; //���߰����ҹ���
		lpOvlpEx->pPair->pPair = NULL;//���߰����ڴ��Լ�����
		closesocket(lpOvlpEx->hSocket); //close�Լ�
		GlobalFree(lpOvlpEx);//�ͷ��Լ�

		shutdown(hPair,SD_BOTH);//�Ѱ�����λshutdown 
	
	}
	else
	{
		closesocket(lpOvlpEx->hSocket); //close�Լ�
		GlobalFree(lpOvlpEx);//�ͷ��Լ�
	}
	
}
//*******************************************************************
//              
//  FUNCTION:   - MProxy3Thread
//              
//  RETURNS:    - 
//              
//  PARAMETERS: - LPVOID pArgu = CMProxy3 *pProxy3
//              
//  COMMENTS:   - �������߳�
//              
//              
//*******************************************************************

DWORD WINAPI MProxy3Thread(LPVOID pArgu)
{

	CMProxy3 *pProxy3 = (CMProxy3 *)pArgu;

	int nErr;
	
	HANDLE hCompletionPort = CreateIoCompletionPort (
		INVALID_HANDLE_VALUE,
		NULL,
		0,
		0
		);
	
	if (!hCompletionPort)
	{
		//printf( "CompletionPort Create Failed\n");
		return  -1;
	}
	
	pProxy3->m_hCompletionPort = hCompletionPort;

	SYSTEM_INFO si;
	GetSystemInfo(&si);

	DWORD i = 0;
	for ( i = 0 ; i < THREAD_MAXNUM; i++ )
	{
		HANDLE hThread;
		DWORD dwThreadID;
		hThread = CreateThread(NULL,0,ServerWorkerThread,hCompletionPort,0,&dwThreadID);
		
		//CloseHandle���ޱ�Ҫֵ�����ۣ���Ϊ��ʱ������ҪWaitForSingleObject(hThread,-1)���ȴ��߳̽���.
		//
		//CloseHandle(hThread);
	}
	
	
	
	SOCKADDR_IN localAddr;

	SOCKET hListener;

	hListener = WSASocket (AF_INET, SOCK_STREAM, 0,NULL,0,WSA_FLAG_OVERLAPPED);
	if (hListener == INVALID_SOCKET)
	{
		//printf( "Socket Create Failed\n");
		return -1;
	}
	
	//
	// Bind our server to the agreed upon port number.  See
	// commdef.h for the actual port number.
	//
	ZeroMemory (&localAddr, sizeof (localAddr));
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons (pProxy3->m_nListenPort);
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	nErr = bind (hListener, (PSOCKADDR) & localAddr, sizeof (localAddr));
	if (nErr == SOCKET_ERROR)
	{
		//printf( "Socket Bind Failed\n");
		if (WSAGetLastError () == WSAEADDRINUSE)
            //printf( "The port number may already be in use.\n");
		return -1;
	}
	nErr = listen (hListener, 5);
	if (nErr == SOCKET_ERROR)
	{
		//printf( "Socket Listen Failed\n");
		return -1;
	}

	SOCKET hAcceptSocket;
	while (pProxy3->m_nThreadState == CMProxy3::RUNNIG)
	{

		hAcceptSocket = WSAAccept(hListener,NULL,NULL,NULL,0);
		
		//�߳̾�������ǵȺ���WSAAccept
		if (pProxy3->m_nThreadState != CMProxy3::RUNNIG)
		{
			closesocket(hAcceptSocket);
			break;
		}

/*

		int TimeOut=0; //���÷��ͳ�ʱ6��
		if(setsockopt(hAcceptSocket,SOL_SOCKET,SO_SNDTIMEO,(char *)&TimeOut,sizeof(TimeOut))!=SOCKET_ERROR){
			////printf("client send time out = %d\n",TimeOut);
		}
		TimeOut=0;//���ý��ճ�ʱ6��
		if(::setsockopt(hAcceptSocket,SOL_SOCKET,SO_RCVTIMEO,(char *)&TimeOut,sizeof(TimeOut))!=SOCKET_ERROR){
			////printf("client send time out = %d\n",TimeOut);
		}
*/



		WSAOVERLAPPEDEX * pAcceptOvl = (WSAOVERLAPPEDEX *) GlobalAlloc(GPTR,sizeof(WSAOVERLAPPEDEX));
		if (pAcceptOvl == NULL)
		{
			closesocket(hAcceptSocket);
			//printf("accept %d error...\n",hAcceptSocket);
			continue;
		}
		//printf("=======================================Accept= %d \n",hAcceptSocket);
		//assert(pAccept);
		pAcceptOvl->pPair = NULL;
		pAcceptOvl->WSABuf.buf   = pAcceptOvl->Buffer;
		pAcceptOvl->WSABuf.len   = DATA_BUFSIZE;
		pAcceptOvl->hSocket = hAcceptSocket;
		pAcceptOvl->hSocketPair = INVALID_SOCKET;
		pAcceptOvl->pProxy3 = pProxy3;
		CreateIoCompletionPort((HANDLE)hAcceptSocket,hCompletionPort,(DWORD)hAcceptSocket,0);
		//pAccept->Recv();
		DWORD dwRecvBytes = 0,dwFlags = 0;
		
		if ( WSARecv(hAcceptSocket,&pAcceptOvl->WSABuf,1,&dwRecvBytes,&dwFlags,(LPWSAOVERLAPPED)pAcceptOvl,NULL) == SOCKET_ERROR)
		{
			if ( WSAGetLastError() != WSA_IO_PENDING)
			{
				//printf("%d accept recv err = %d",hAcceptSocket,WSAGetLastError());
			}
		}

	}


//**************************
//���һ��Ҫǿ����ֹ�Ի����������ӣ�������Ĵ���
/*
	for( i = 0 ; i < THREAD_MAXNUM ; i++)
	{
		PostQueuedCompletionStatus(hCompletionPort,0,0,0);
	}
*/
//*****************************
	CloseHandle(hCompletionPort);

	return 0;
}



//*******************************************************************
//              
//  FUNCTION:   - GetURL
//              
//  RETURNS:    -
//              
//  PARAMETERS: - const string &strHeader , string & strProtocal, string &strAddress , int & nPort
//              
//  COMMENTS:   - ��������з�������Э�飬��������ַ���˿ں� 
//              
//              
//*******************************************************************

bool GetURL(const string &strHeader, string & strProtocal, string &strAddress , int & nPort);
//�������ӣ�ֱ�Ӵ���
bool GetURL(const string &strHeader, string & strProtocal, string &strAddress , int & nPort)
{

//	string strDebug = strHeader.substr(0,50);
//	cout << strDebug << "\n\n";
//	Ӧ��Greta������ʽ����
	match_results results;
	int nCount;
	
    string str = strHeader;
	string strPort;
	rpattern pat("^.+ (.+)://(?:.+@)?([^/:]+)(?:.*:)?(\\d+)?");
	
    match_results::backref_type br = pat.match( str, results );
    if(!br.matched ) 
		return false;

  	nCount = results.cbackrefs();
	if (nCount == 4)
	{
		match_results::backref_type br1 = results.backref(1);
		strProtocal = br1.str();
		match_results::backref_type br2 = results.backref(2);
		strAddress = br2.str();
		match_results::backref_type br3 = results.backref(3);
		strPort = br3.str();
		nPort = atoi(strPort.c_str());
		if (nPort == 0)
		{
			if (strProtocal =="http")
				nPort = 80;
			else 
				nPort = 21;
		}

		
	}
	return true;
}

//*******************************************************************
//              
//  FUNCTION:   - ServerWorkerThread
//              
//  RETURNS:    -
//              
//  PARAMETERS: - LPVOID CompletionPortID
//              
//  COMMENTS:   - �����������߳�
//              
//              
//*******************************************************************

DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID)
{
	HANDLE hCompletionPort = (HANDLE) CompletionPortID;
	DWORD  dwBytesTransferred = 0;
	SOCKET hSocket; 
	LPWSAOVERLAPPEDEX	lpOvlpEx;
	int nErr;
		
	
	while (1)
	{
		BOOL r = GetQueuedCompletionStatus(hCompletionPort,&dwBytesTransferred,(LPDWORD)&hSocket,(LPWSAOVERLAPPED *) &lpOvlpEx,INFINITE );
		if (!r)
		{
			nErr = WSAGetLastError();
			//printf("GetQueuedCompletionStatus = %d\n",nErr);
		}
		
		if (hSocket == 0 || lpOvlpEx == NULL)
			break;

		//printf("%d bytes transed...\n",dwBytesTransferred);

	
		if (dwBytesTransferred == 0)
		{
			if (hSocket == lpOvlpEx->hSocket)
			{
				SafeClose(lpOvlpEx);
				//printf(" .....................%d..........closed & freed........\n",hSocket);
				
			}

			continue;
		}
		if (hSocket == lpOvlpEx->hSocket)
		{//
			//printf("%d  ,  recv = %d\n",hSocket,dwBytesTransferred);
			
			if (lpOvlpEx->hSocketPair == INVALID_SOCKET)
			{//��һ�������󣬴�����ص�socket
				
				std::string strProtocal,strAddress;
				int nPort;
				CMProxy3 *pProxy = (CMProxy3 *)lpOvlpEx->pProxy3;
				if (pProxy->m_Addr2[0] == 0)
				{
					char szHeader[DATA_BUFSIZE];
					memcpy(szHeader,lpOvlpEx->Buffer,dwBytesTransferred);
					szHeader[dwBytesTransferred] = 0;
					if ( !GetURL(szHeader, strProtocal, strAddress , nPort))
					{
						closesocket(lpOvlpEx->hSocket);
						GlobalFree(lpOvlpEx);
						//printf("err url\n");
						continue ;
					}
				}
				else
				{
					strAddress  = pProxy->m_Addr2;
					nPort = pProxy->m_nPort2;
				}	
			
				SOCKADDR_IN remoteAddr;
				ZeroMemory (&remoteAddr, sizeof (remoteAddr));
				remoteAddr.sin_family = AF_INET;
				remoteAddr.sin_port = htons (nPort);
				remoteAddr.sin_addr.s_addr = inet_addr(strAddress.c_str());
				
				if(remoteAddr.sin_addr.s_addr == INADDR_NONE)
				{
					hostent * host = gethostbyname(strAddress.c_str());
					if(host == NULL)
					{
						closesocket(lpOvlpEx->hSocket);
						GlobalFree(lpOvlpEx);
						//printf("err address\n");
						continue;
					}
					memcpy(&remoteAddr.sin_addr,host->h_addr_list[0],host->h_length);
				}

				SOCKET hConnect;
				hConnect = WSASocket (AF_INET, SOCK_STREAM, 0,NULL,0,WSA_FLAG_OVERLAPPED);
				if (hConnect == INVALID_SOCKET)
				{
					//printf ("Socket Create Failed\n");
					closesocket(lpOvlpEx->hSocket);
					GlobalFree(lpOvlpEx);
					continue;
				}
			
				int r = connect(hConnect,(PSOCKADDR)&remoteAddr,sizeof(remoteAddr));
				if (r)
				{
					//printf ("Socket Connect Failed\n");
					closesocket(hConnect);
					closesocket(lpOvlpEx->hSocket);
					GlobalFree(lpOvlpEx);
				
					continue;
				}
				int iSize = sizeof(WSAOVERLAPPEDEX);
			
				WSAOVERLAPPEDEX * pConnOvlEx = (WSAOVERLAPPEDEX *) GlobalAlloc(GPTR,sizeof(WSAOVERLAPPEDEX));
				lpOvlpEx->pPair = pConnOvlEx;//����
				pConnOvlEx->pPair = lpOvlpEx;//ָ��
				lpOvlpEx->hSocketPair = hConnect;
				pConnOvlEx->hSocketPair = lpOvlpEx->hSocket;
				pConnOvlEx->hSocket = hConnect;
				pConnOvlEx->WSABuf.buf = pConnOvlEx->Buffer;
				pConnOvlEx->WSABuf.len = DATA_BUFSIZE;
				pConnOvlEx->pProxy3 = pConnOvlEx->pProxy3;
				CreateIoCompletionPort((HANDLE)hConnect,hCompletionPort,(DWORD)hConnect,0);

			/*
				LINGER  sl;
							sl.l_onoff = 1;
							sl.l_linger = 1;
							setsockopt(pSocket->hSocket,SOL_SOCKET,SO_LINGER,(char *)&sl,sizeof(sl));
							setsockopt(pSocket->pPair->hSocket,SOL_SOCKET,SO_LINGER,(char *)&sl,sizeof(sl));*/
			

				//printf("==========================Connect = %d\n",hConnect);

				DWORD dwRecvBytes = 0,dwFlags = 0;
				ZeroMemory(pConnOvlEx,sizeof(WSAOVERLAPPED));
				pConnOvlEx->WSABuf.len = DATA_BUFSIZE;
				if ( WSARecv(hConnect,&pConnOvlEx->WSABuf,1,&dwRecvBytes,&dwFlags,(LPWSAOVERLAPPED)pConnOvlEx,NULL) == SOCKET_ERROR)
				{
					if ( WSAGetLastError() != WSA_IO_PENDING)
					{
						//printf("%d conn recv err = %d",pConnOvlEx->hSocket,WSAGetLastError());
						SafeClose(lpOvlpEx);
						continue;
				
					}
				}

			}
			//ת��
				
			DWORD dwReadBytes = 0,dwFlags = 0;
			
			ZeroMemory(lpOvlpEx,sizeof(WSAOVERLAPPED));
			lpOvlpEx->WSABuf.len = dwBytesTransferred;
		
			if ( WSASend(lpOvlpEx->hSocketPair,&lpOvlpEx->WSABuf,1,&dwReadBytes,dwFlags,(LPWSAOVERLAPPED)lpOvlpEx,NULL) == SOCKET_ERROR)
			{
				if ( WSAGetLastError() != WSA_IO_PENDING)
				{
					//printf("%d Send err = %d",lpOvlpEx->hSocketPair,WSAGetLastError());
					SafeClose(lpOvlpEx);
					continue;
				}
			}
		
		}
		else if (hSocket == lpOvlpEx->hSocketPair)
		{//���ݷ�����,ת�����״̬
			//printf("%d  ,  send = %d\n",hSocket,dwBytesTransferred);
		
			DWORD dwRecvBytes = 0,dwFlags = 0;
			lpOvlpEx->WSABuf.len = DATA_BUFSIZE;
			ZeroMemory(lpOvlpEx,sizeof(WSAOVERLAPPED));
		
			if ( WSARecv(lpOvlpEx->hSocket,&lpOvlpEx->WSABuf,1,&dwRecvBytes,&dwFlags,(LPWSAOVERLAPPED)lpOvlpEx,NULL) == SOCKET_ERROR)
			{
				if ( WSAGetLastError() != WSA_IO_PENDING)
				{
					//printf("%d recv err = %d\n",lpOvlpEx->hSocket,WSAGetLastError());
					SafeClose(lpOvlpEx);
					continue;
				}
			}
		
		}
	
		
	
	}
	return 0;
}
