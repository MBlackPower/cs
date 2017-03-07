// �����ܣ������ȡ�û�������з��͵��ಥ�飬����ಥ����κοͻ���Ӧ����ʾ�Ӷಥ���ж��������ݡ�


//Project Setting -> C/C++ -> Code Generation -> ȷ��ѡ��"Debug Multithreaded"


#include <process.h> //_beginthreadҪ��

#include "Multicast.h"

using namespace std;

const char* MULTICAST_IP = "224.0.0.99"; //�ಥ���ַ
const int MULTICAST_PORT = 2002; //�ಥ��˿�

const int BUFFER_SIZE = 1024;


void do_send(void* arg); //��ȡ�û����벢���͵��ಥ���̺߳���
void do_read(void* arg); //����ಥ�����ݺ���
int SetOpt(CMulticast &multicast);

int main()
{
	CMulticast multicast;
	
	multicast.Initialize(AF_INET, SOCK_DGRAM, 0);
		
	if ( SetOpt(multicast) )
	{
		return 0;
	}
	
	HANDLE hHandle[2];	//	//�����������̣߳�һ�����û����벢���ͣ�һ�����ಥ������	
	hHandle[0] = (HANDLE)_beginthread(do_send,0,(void*)&multicast);
	hHandle[1] = (HANDLE)_beginthread(do_read,0,(void*)&multicast);
	
	//����û�����������������ֹ��
	WaitForSingleObject(hHandle[0], INFINITE);
	
	return 0;
}


int SetOpt(CMulticast &multicast)
{
	const int on = 1; //�������Ķ��ʵ��������ͬһ̨������
	
	if (-1 == multicast.SetSockOpt( SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on) ) )
	{
		cout<<"Error in setsockopt(SO_REUSEADDR): "<<WSAGetLastError()<<endl;
		return -1;
	}
	
	const int routenum = 10;
	
	if (-1 == multicast.SetSockOpt( IPPROTO_IP,	IP_MULTICAST_TTL, (char*)&routenum, sizeof(routenum) ) )
	{
		cout<<"Error in setsockopt(IP_MULTICAST_TTL): "<<WSAGetLastError()<<endl;
		return -1;
	}
	
	const int loopback = 0; //��ֹ����
	
	if (-1 == multicast.SetSockOpt( IPPROTO_IP, IP_MULTICAST_LOOP, (char*)&loopback, sizeof(loopback) ) )
	{
		cout<<"Error in setsockopt(IP_MULTICAST_LOOP): "<<WSAGetLastError()<<endl;
		return -1;
	}
	
	sockaddr_in local;
	
	multicast.SetAddr(local, AF_INET, MULTICAST_PORT, INADDR_ANY);
	
	if( -1 == multicast.Bind((sockaddr*)(&local), sizeof(local)) )
	{		
		cout<<"Error in bind: "<<WSAGetLastError()<<endl;
		return -1;
	}
	
	ip_mreq mreq;
	
	multicast.SetMreg(mreq, INADDR_ANY, MULTICAST_IP);
	
	//����һ���ಥ��
	if ( -1 == multicast.SetSockOpt( IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq) ) )
	{
		cout<<"Error in setsockopt(IP_ADD_MEMBERSHIP): "<<WSAGetLastError()<<endl;
		return -1;
	}
	return 0;
}

void do_send(void* arg)
{
	CMulticast * pM = (CMulticast *)arg;
	
	char sendline[BUFFER_SIZE+1];
	
	sockaddr_in remote;
	pM->SetAddr(remote, AF_INET, MULTICAST_PORT, MULTICAST_IP);
	
	while (true) //��ȡ�û�����֪���û�����"end"
	{
		cout<<"sender : ";
		cin.getline(sendline, BUFFER_SIZE);

		if(strncmp(sendline,"end",3)==0)
			break;
		
		//�����û���������ݵ��ಥ��
		pM->Send_n(sendline, BUFFER_SIZE, 0, (sockaddr*)(&remote), sizeof(remote)); 
	}
	cout<<"do_send end..."<<endl;
}

void do_read(void* arg)
{
	CMulticast * pM = (CMulticast *)arg;
	
	char buf[BUFFER_SIZE+1];
	
	sockaddr_in client;
	int clientLen;
	
	while (true) //һֱ��ȡ֪�����߳���ֹ
	{
		clientLen = sizeof(client);
		memset(&client, 0, clientLen);
		
		if (pM->Rece_n(buf, BUFFER_SIZE, 0, (sockaddr*)(&clientLen), &clientLen))
		{
			continue;
		}
		cout<<"\r\nreceiver : "<<buf<<endl;
		cout<<"sender : ";
	}
	
	cout<<"do_read end..."<<endl;
}