#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	//����Socket��̬���ӿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 2, 2 );
	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		cout<<"client:Tell the user that we could not find a usable"<<endl;
		return 1;
	}
	
	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */
	
	if ( LOBYTE( wsaData.wVersion ) != 2 ||
        HIBYTE( wsaData.wVersion ) != 2 ) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		cout<<"client:Tell the user that we could not find a usable"<<endl;
		WSACleanup( );
		return 1; 
	}
	
	/* The WinSock DLL is acceptable. Proceed. */

	//1.�����׽���
	cout<<"client:create socket"<<endl;
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET == WSAGetLastError())
		MessageBox(NULL, "Create Socket failed!", "Error", MB_OK);

	//2.�������������������
	cout<<"client:send connect requst to server"<<endl;
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//3.�ͷ���������ͨ�ţ����ջ��Ƿ�������
	cout<<"client:transfor with srv"<<endl;

	char recvBuf[100];
	recv(sockClient, recvBuf, 100, 0);
	if(SOCKET_ERROR == WSAGetLastError())
			MessageBox(NULL, "Server recieve data failed!", "Error", MB_OK);
	printf("%s\n", recvBuf);
	char sendBuf[] = "Hello Server";
	send(sockClient, sendBuf, sizeof(sendBuf) + 1, 0);
	if(SOCKET_ERROR == WSAGetLastError())
			MessageBox(NULL, "Server send data failed!", "Error", MB_OK);


	//4.�ر��׽��ֵ���Դ���Լ�ж���׽��ֶ�̬���ӿ�
	cout<<"client:close socket"<<endl;
	closesocket(sockClient);
	WSACleanup();

	return 0;
}