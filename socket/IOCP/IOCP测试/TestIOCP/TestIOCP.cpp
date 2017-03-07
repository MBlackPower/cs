// TestIOCP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "InitSock.h"

CInitSock theSock;

#define BUFFER_SIZE 1024

typedef struct _PER_HANDLE_DATA
{
	SOCKET s;  //��Ӧ���׽��־��
	sockaddr_in addr;  //�ͻ���IP��ַ
}PER_HANDLE_DATA, *PPER_HANDLE_DATA;

typedef struct _PER_IO_DATA
{
	OVERLAPPED ol; //�ص��ṹ
	char buf[BUFFER_SIZE]; //���ݻ�����
	int nOperationType;  //��������
#define OP_READ 1
#define OP_WRITE 2
#define OP_ACCEPT 3
}PER_IO_DATA, *PPER_IO_DATA;

DWORD WINAPI ServerThread(LPVOID lpParam);

int main(int argc, char* argv[])
{
	int nPort = 4567; 

	//������ɶ˿ڶ���
	HANDLE hCompletion = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	::CreateThread(NULL, 0, ServerThread, (LPVOID)hCompletion, 0, 0);

	//���������׽���
	SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN si;
	si.sin_family = AF_INET;
	si.sin_port = ::ntohs(nPort);
	si.sin_addr.S_un.S_addr = INADDR_ANY;
	::bind(sListen, (sockaddr*)&si, sizeof(si));
	::listen(sListen, 5);

	//ѭ��������������
	while (TRUE)
	{
		//�ȴ�����δ������������
		SOCKADDR_IN saRemote;
		int nRemoteLen = sizeof(saRemote);
		SOCKET sNew = ::accept(sListen, (sockaddr*)&saRemote, &nRemoteLen);
		//���ܵ��µ����Ӻ�Ϊ������һ��per-handle���ݣ��������ǹ������˿ڶ���
		PPER_HANDLE_DATA pPerHandle = (PPER_HANDLE_DATA)::GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA));
		pPerHandle->s = sNew;
		memcpy(&pPerHandle->addr, &saRemote, nRemoteLen);
		::CreateIoCompletionPort((HANDLE)pPerHandle->s, hCompletion, (DWORD)pPerHandle, 0);
		//Ͷ��һ����������
		PPER_IO_DATA pPerIO = (PPER_IO_DATA)::GlobalAlloc(GPTR, sizeof(PER_IO_DATA));
		pPerIO->nOperationType = OP_READ;
		WSABUF buf;
		buf.buf = pPerIO->buf;
		buf.len = BUFFER_SIZE;
		DWORD dwRecv;
		DWORD dwFlags = 0;
		::WSARecv(pPerHandle->s, &buf, 1, &dwRecv, &dwFlags, &pPerIO->ol, NULL);
	}
	return 0;
}

DWORD WINAPI ServerThread(LPVOID lpParam)
{
	//�õ���ɶ˿ڶ���ľ��
	HANDLE hCompletion = (HANDLE)lpParam;
	DWORD dwTrans;
	PPER_HANDLE_DATA pPerhandle;
	PPER_IO_DATA pPerIO;
	while (TRUE)
	{
		//�ڹ������˶˿ڵ������׽����ϵȴ�IO�˿����
		BOOL bOk = ::GetQueuedCompletionStatus(hCompletion, 
			&dwTrans, (LPDWORD)&pPerhandle, (LPOVERLAPPED*)&pPerIO, WSA_INFINITE);

		if (bOk != TRUE)  //���׽������д�����
		{
			::closesocket(pPerhandle->s);
			::GlobalFree(pPerhandle);
			::GlobalFree(pPerIO);
			continue;
		}

		if (dwTrans == 0 && (pPerIO->nOperationType == OP_READ || 
			pPerIO->nOperationType == OP_WRITE))  //���׽��ֱ��Է��ر�
		{
			::closesocket(pPerhandle->s);
			::GlobalFree(pPerhandle);
			::GlobalFree(pPerIO);
			continue;
		}

		switch (pPerIO->nOperationType) //������ʲô���͵�IO���������
		{
		case OP_READ: //���һ����������
			{
				pPerIO->buf[dwTrans] = '\0';
				printf(pPerIO->buf);
				//����Ͷ��IO����
				pPerIO->nOperationType = OP_READ;
				WSABUF buf;
				buf.buf = pPerIO->buf;
				buf.len = BUFFER_SIZE;
				DWORD dwFlags = 0;
				::WSARecv(pPerhandle->s, &buf, 1, &dwTrans, &dwFlags, &pPerIO->ol, NULL);
			}
			break;
			//������������δʵ��
		case OP_ACCEPT:
			break;
		case OP_WRITE:
			break;
		}
	}
	return 0;
}

