/*++
Copyright (c) 2004 
ģ����: 
iomodel.cpp
ģ������:
Winsock ��ɶ˿���ʵ���ļ�
����:
PPP elssann@hotmail.com
��������:

Visual C++ 6.0, Windows 2000.

�޶���¼:
������: 2004.1.16
����޸�����:
2004.1.23
	
--*/
#include <iostream.h>

#include "NetCompletionPort.h"

#include <windows.h>
#include <iostream.h>


#pragma comment(lib, "ws2_32.lib")


/*++
��������:
���캯������ʼ���߳̾�����飬��ʼ��AcceptEx()���õļ�������ʼ���ٽ�δ��������
Arguments:
�ޡ�
Return Value:
�ޡ�
--*/
CompletionPortModel::CompletionPortModel()
{
	for (int i=0; i< MAXTHREAD_COUNT; i++)
	{
		m_hThreadArray[i] = INVALID_HANDLE_VALUE;
	}
	m_lAcceptExCounter = 0;
	InitializeCriticalSection(&m_ListCriSection); 
	InitializeCriticalSection(&m_HandleCriSection);
	InitializeCriticalSection(&m_IoCriSection);
	m_lpHandleLOOKasideLists = NULL;
	m_lpIoLookasideLists = NULL;
#ifndef _DEBUG
	GetAddressAndPort();
#endif
}//end of CompletionPortModel()



/*++
��������:
�����������ͷ��������н�㡣
Arguments:
�ޡ�
Return Value:
--*/
CompletionPortModel::~CompletionPortModel()
{
	PPER_IO_CONTEXT lpIoNode;
	while (m_lpConnectionListHead->pNext)
	{
		lpIoNode = m_lpConnectionListHead->pNext;
		m_lpConnectionListHead->pNext = lpIoNode->pNext;
		closesocket(lpIoNode->sClient);
		HeapFree(GetProcessHeap(), 0, lpIoNode);
	}
	while(NULL != m_lpIoLookasideLists)
	{
		lpIoNode = m_lpIoLookasideLists;
		m_lpIoLookasideLists = m_lpIoLookasideLists->pNext;
		HeapFree(GetProcessHeap(), 0, lpIoNode);
	}
	PPER_HANDLE_CONTEXT lpHandleNode;
	while(NULL != m_lpHandleLOOKasideLists)
	{
		lpHandleNode = m_lpHandleLOOKasideLists;
		m_lpHandleLOOKasideLists = m_lpHandleLOOKasideLists->pNext;
		HeapFree(GetProcessHeap(), 0, lpHandleNode);
	}
	DeleteCriticalSection(&m_ListCriSection); 
	DeleteCriticalSection(&m_HandleCriSection);
	DeleteCriticalSection(&m_IoCriSection);
	
}//end of ~CompletionPortModel()




/*++
��������:
��ʼ����������ɶ˿ڡ�������ɶ˿��̣߳����������Ա����InitWinsock��ʼ��Winsock��
����һ�������׽���m_ListenSocket���������׽���ͬ��ɶ˿ڹ�����������ȡAcceptExָ�롣
Arguments:
�ޡ�
Return Value:
�������óɹ�����TRUE��ʧ�ܷ���FALSE��
--*/
BOOL CompletionPortModel::Init()
{
	BOOL bSuccess = InitLinkListHead();
	
	if (FALSE == bSuccess)
	{
		return FALSE;
	}
	
	m_hCOP = CreateIoCompletionPort(
		INVALID_HANDLE_VALUE,	//��ָ��һ��Ҫͬ��ɶ˿ڹ�����һ����׽��־��
		NULL,					//����ָ������һ�����е���ɶ˿�
		NULL,					//��ָ��Ҫ��ĳ���ض��׽��־��������һ��ġ���������ݡ�
		0		//NumberOfConcurrentThreads������������һ����ɶ˿��ϣ�ͬʱ����ִ�е��߳�������
		);
	/*
	��Ϊ0������ϵͳ�ڰ�װ�˶��ٸ���������������ͬʱ���ж��ٸ��̣߳�
	*/
	if (NULL == m_hCOP)
	{
		cout << "CreateIoCompletionPort() failed: " << GetLastError() << endl;
		return FALSE;
	}
	//
	//ȡ��ϵͳ��CPU����Ŀ��������CPU��Ŀ��ȵ��̣߳�������ȹ��Ƶ���ɶ˿ڴ����̻߳������
	//���Կ��Ǵ��� SysInfo.dwNumberOfProcessors*2���̡߳�һ���ڵ��������ϴ�����CPU��Ŀ���
	//���߳̾Ϳ�����
	//
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	if (MAXTHREAD_COUNT < SysInfo.dwNumberOfProcessors)
	{
		SysInfo.dwNumberOfProcessors = MAXTHREAD_COUNT;
	}

	/*
	�ɹ�����һ����ɶ˿ں󣬱�ɿ�ʼ���׽��־������������һ�𡣵��ڹ����׽���
	֮ǰ�����ȱ��봴��һ���������������̡߳��Ա���I / O����Ͷ�ݸ���ɶ˿ڶ���
	��Ϊ��ɶ˿��ṩ����
	*/
	for (int i=0; i<(int)SysInfo.dwNumberOfProcessors; i++)
	{
		m_hThreadArray[i] = CreateThread(
											NULL,
											0,
											CompletionRoutine,
											(LPVOID)this,
											0,
											NULL
											);

		if (NULL == m_hThreadArray[i])
		{
			while (i>0)
			{
				CloseHandle(m_hThreadArray[i-1]);
				m_hThreadArray[i-1] = INVALID_HANDLE_VALUE;
				i--;
			}//end of while
			cout << "CreateThread() failed: " << GetLastError() << endl;
			
			CloseHandle(m_hCOP);

			HeapFree(GetProcessHeap(), 0, m_lpConnectionListHead);
			
			return FALSE;
		}
	}//end of for
	//
	//����InitWinsock������ʼ��Winsock������һ�������׽���m_ListenSocket��
	//�������׽���ͬ��ɶ˿ڹ�����������ȡAcceptExָ�롣
	//
	bSuccess = InitWinsock();
	if (!bSuccess)
	{
		//
		//����ɶ˿��̷߳�����Ϣ��ָʾ�߳��˳���
		//
		PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
		CloseThreadHandle();
		CloseHandle(m_hCOP);
		HeapFree(GetProcessHeap(), 0, m_lpConnectionListHead); 
		return FALSE;
	}
	//
	//����BindAndListenSocket()���׽��ֲ����׽������ڼ���״̬
	//
	bSuccess = BindAndListenSocket(); 
	if (!bSuccess)
	{
		PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
		CloseThreadHandle();
		CloseHandle(m_hCOP);
		HeapFree(GetProcessHeap(), 0, m_lpConnectionListHead);  
		
		return FALSE;
	}
	return TRUE; 
}//end of Init()



/*++
��������:
��ÿһ���������̵߳���CloseHandle()��
Arguments:
�ޡ�
Return Value:
�ޡ�
--*/
void CompletionPortModel::CloseThreadHandle()
{
	for (int i=0; i< MAXTHREAD_COUNT; i++)
	{
		if (INVALID_HANDLE_VALUE != m_hThreadArray[i])
		{
			CloseHandle(m_hThreadArray[i]);
			m_hThreadArray[i] = INVALID_HANDLE_VALUE;
		}
	}//end of for
	
	return;
}//end of CloseThreadHandle()



/*++
��������:
��ʼ��Winsock,����һ�������׽��֣���ȡAcceptEx����ָ�룬Ϊ�����׽��ַ���һ�������
���ݣ����������׽�������ɶ˿�hCOP������
Arguments:
�ޡ�
Return Value:
�������óɹ�����TRUE��ʧ�ܷ���FALSE��
--*/
BOOL CompletionPortModel::InitWinsock()
{
	WSADATA wsd;
	int nResult = WSAStartup(MAKEWORD(2,2), &wsd);
	if (0 != nResult)
	{
		cout << "WSAStartup() failed" << endl;
		
		return FALSE;
	}
	m_ListenSocket = WSASocket(
								AF_INET,
								SOCK_STREAM,
								IPPROTO_IP, 
								NULL,
								0,
								WSA_FLAG_OVERLAPPED
								);
	
	if (INVALID_SOCKET == m_ListenSocket)
	{
		cout << "WSASocket() failed: " << WSAGetLastError() << endl;
		WSACleanup();
		
		return FALSE;
	}
	
	
	DWORD dwResult;
	//
	//��ȡ΢��SOCKET��չ����ָ��
	//
	nResult = WSAIoctl( 
						m_ListenSocket,
						SIO_GET_EXTENSION_FUNCTION_POINTER,
						&g_GUIDAcceptEx,
						sizeof(g_GUIDAcceptEx),
						&lpAcceptEx,
						sizeof(lpAcceptEx),
						&dwResult,
						NULL,
						NULL
						);
	
	if (SOCKET_ERROR == nResult)
	{
		cout << "Get AcceptEx failed: " << WSAGetLastError() << endl;
		closesocket(m_ListenSocket);
		WSACleanup();
		return FALSE;
	}
	nResult = WSAIoctl( 
						m_ListenSocket,
						SIO_GET_EXTENSION_FUNCTION_POINTER,
						&g_GUIDTransmitFile,
						sizeof(g_GUIDTransmitFile),
						&lpTransmitFile,
						sizeof(lpTransmitFile),
						&dwResult,
						NULL,
						NULL
						);
	
	if (SOCKET_ERROR == nResult)
	{
		cout << "Get TransmitFile failed: " << WSAGetLastError() << endl;
		closesocket(m_ListenSocket);
		WSACleanup();
		
		return FALSE;
	}
	
	//
	//Ϊ�����׽��ַ���һ�����������
	//
	PPER_HANDLE_CONTEXT lpListenHandleContext =
		(PPER_HANDLE_CONTEXT)HeapAlloc(
										GetProcessHeap(),
										HEAP_ZERO_MEMORY, 
										sizeof(PER_HANDLE_CONTEXT)
										);
	if (NULL == lpListenHandleContext)
	{
		closesocket(m_ListenSocket);
		WSACleanup();
		cout << "HeapAlloc() failed " << endl;
		
		return FALSE;
	}
	lpListenHandleContext->IoSocket = m_ListenSocket;
	lpListenHandleContext->pNext = NULL;
	//
	//�������׽���m_ListenSocket���Ѿ���������ɶ˿ڹ�������
	//
	HANDLE hrc = CreateIoCompletionPort(
										(HANDLE)m_ListenSocket,
										m_hCOP,
										(ULONG_PTR)lpListenHandleContext,
										0
										);

	
	if (NULL == hrc)
	{
		closesocket(m_ListenSocket);
		HeapFree(GetProcessHeap(), 0, lpListenHandleContext);
		WSACleanup();
		cout << "CreateIoCompletionPort failed: " << GetLastError() << endl;
		
		return FALSE;
	}
	return TRUE;
}//end of InitWinsock()



/*++
��������:
private��������Init���á�
�������׽���m_ListenSocket�󶨵�����IP��ַ�������ڼ���ģʽ��

Arguments:
�ޡ�
Return Value:
�������óɹ�����TRUE��ʧ�ܷ���FALSE��
--*/
BOOL CompletionPortModel::BindAndListenSocket()
{
	SOCKADDR_IN InternetAddr;
	InternetAddr.sin_family = AF_INET;
#ifdef _DEBUG
	InternetAddr.sin_addr.s_addr = inet_addr(LOCALADDRESS);
	InternetAddr.sin_port = htons(PORT);   
#else
	InternetAddr.sin_addr.s_addr = inet_addr(szAddress);
	InternetAddr.sin_port = htons(uPort);    
#endif 
	
	int nResult = bind(m_ListenSocket, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr));
	if (SOCKET_ERROR == nResult)
	{
		int nRet = GetLastError();
		WSACleanup();
		closesocket(m_ListenSocket);
		
		cout << "bind() failed: " << WSAGetLastError() << endl;
		
		return FALSE;
	} 
	nResult = listen(m_ListenSocket, 20);
	if (SOCKET_ERROR == nResult)
	{
		WSACleanup();
		closesocket(m_ListenSocket);
		cout << "listen() failed: " << WSAGetLastError() << endl;
		
		return FALSE;
	}  
	return TRUE;
}//end of BindAndListenSocket()




/*++
��������:
��ɶ˿ڴ����̣߳�ѭ������GetQueuedCompletionStatus����ȡIO���������
Arguments:
Return Value:
�߳��˳����롣
--*/
DWORD __stdcall CompletionRoutine(LPVOID Param)
{
	CompletionPortModel* pThis = (CompletionPortModel*)Param;
	DWORD dwNumberBytes;
	PPER_HANDLE_CONTEXT lpHandleContext = NULL;
	LPWSAOVERLAPPED lpOverlapped = NULL;
	int nResult;
	BOOL bSuccess;
	
	while (TRUE)
	{
		bSuccess = GetQueuedCompletionStatus(
												pThis->m_hCOP,		//��Ӧ��Ҫ������ȴ�����ɶ˿�
												&dwNumberBytes,		//�����������һ��I / O��������WSASend��WSARecv��������ʵ�ʴ�����ֽ���
												(PULONG_PTR )&lpHandleContext,	//Ϊԭ�ȴ��ݽ���CreateCompletionPort�������׽��ַ��ء����������
												&lpOverlapped,		//���ڽ�����ɵ�I / O�������ص����
												INFINITE	//����ָ��������ϣ���ȴ�һ��������ݰ�����ɶ˿��ϳ��ֵ�ʱ�䡣���罫����ΪINFINITE�����û�����ֹ�صȴ���ȥ
												);
		
		if (FALSE == bSuccess)
		{
#ifndef _DEBUG
			cout << "GetQueuedCompletionStatus() failed: " << GetLastError() << endl;
#endif
			continue;
		}
		if (NULL == lpHandleContext)
		{
			//
			//PostQueuedCompletionStatus������һ���յĵ�������ݣ���ʾ�߳�Ҫ�˳��ˡ�
			//
			return 0;
		}
		PPER_IO_CONTEXT lpPerIoContext = (PPER_IO_CONTEXT)lpOverlapped;
#ifdef _DEBUG
		cout << "recv buffer data: " << lpPerIoContext->szBuffer << endl;  
#endif
		
		if(IoAccept != lpPerIoContext->IoOperation)
		{
			if((!bSuccess) || (bSuccess && (0 == dwNumberBytes))) 
			{
				closesocket(lpPerIoContext->sClient);
				lpPerIoContext->pNext = NULL;
				pThis->InsertToLookaside(lpPerIoContext, NULL);
				lpHandleContext->pNext = NULL;
				pThis->InsertToLookaside(NULL, lpHandleContext);
				
				continue;
			}
		}
		HANDLE hResult;
		PPER_HANDLE_CONTEXT lpNewperHandleContext;
		switch(lpPerIoContext->IoOperation)
		{
		case IoAccept : 
			if (dwNumberBytes)
			{
				//
				//��һ�����ӳɹ������յ�������,��������������н��
				//
				EnterCriticalSection(&pThis->m_ListCriSection);
				pThis->ReleaseNode(lpPerIoContext);
				LeaveCriticalSection(&pThis->m_ListCriSection);
			}
			nResult = setsockopt(
									lpPerIoContext->sClient, 
									SOL_SOCKET,
									SO_UPDATE_ACCEPT_CONTEXT,
									(char *)&pThis->m_ListenSocket,
									sizeof(pThis->m_ListenSocket)
									);
			
			if(SOCKET_ERROR == nResult) 
			{
				cout << "SO_UPDATE_ACCEPT_CONTEXT failed to update accept socket" << endl;
				closesocket(lpPerIoContext->sClient); 
				lpPerIoContext->pNext = NULL;
				pThis->InsertToLookaside(lpPerIoContext, NULL);
				
				continue;
			}
			
			lpNewperHandleContext = pThis->GetHandleFromLookaside();
			if (NULL == lpNewperHandleContext)
			{
				lpNewperHandleContext =
					(PPER_HANDLE_CONTEXT)HeapAlloc(
													GetProcessHeap(),
													HEAP_ZERO_MEMORY,
													sizeof(PER_HANDLE_CONTEXT)
													);
				if (NULL == lpNewperHandleContext)
				{
					cout << "HeapAlloc() for lpNewperHandlecontext failed" << endl;
					
					closesocket(lpPerIoContext->sClient);
					lpPerIoContext->pNext = NULL;
					pThis->InsertToLookaside(lpPerIoContext, NULL);
					
					continue;
				}    
			}
			lpNewperHandleContext->IoSocket = lpPerIoContext->sClient;
			lpNewperHandleContext->pNext = NULL;
			
			//
			//���½������׽��ֹ�������ɶ˿�
			//
			hResult = CreateIoCompletionPort(
												(HANDLE)lpPerIoContext->sClient,
												pThis->m_hCOP,
												(DWORD_PTR)lpNewperHandleContext,
												0
												);
			
			if (NULL == hResult)
			{
				cout << "CreateIoCompletionPort() failed: " << GetLastError();
				closesocket(lpPerIoContext->sClient);
				lpPerIoContext->pNext = NULL;
				lpNewperHandleContext->pNext = NULL;
				pThis->InsertToLookaside(lpPerIoContext, NULL);
				pThis->InsertToLookaside(NULL, lpNewperHandleContext);
				
				continue;
			}
			if (dwNumberBytes)
			{
				//
				//�����������ݡ�
				//
				pThis->HandleData(lpPerIoContext, IO_READ_COMPLETION);
				bSuccess = pThis->DataAction(lpPerIoContext, lpNewperHandleContext);
				if (FALSE == bSuccess)
				{
					continue;
				}
			}
			//
			//������ӳɹ�����û���յ�����
			//
			else
			{
				pThis->HandleData(lpPerIoContext, IO_ACCEPT_COMPLETION);
				bSuccess = pThis->DataAction(lpPerIoContext, lpNewperHandleContext);
				if (FALSE == bSuccess)
				{
					continue;
				}
			}
			break;//end of case IoAccept
			
		case IoRead:
			pThis->HandleData(lpPerIoContext, IO_READ_COMPLETION);
			bSuccess = pThis->DataAction(lpPerIoContext, lpNewperHandleContext);
			if (FALSE == bSuccess)
			{
				continue;
			}
			break;//end of case IoRead
		case IoWrite:
			pThis->HandleData(lpPerIoContext, IO_WRITE_COMPLETION);
			bSuccess = pThis->DataAction(lpPerIoContext, lpNewperHandleContext);
			if (FALSE == bSuccess)
			{
				continue;
			} 
			break;
		default:
			continue;
			break;
		}
	}
	return 0;
}//end of CompletionRoutine()



/*++
Fucntion Description:
��������10��AcceptEx���á�
Arguments:
Return Value:
�������óɹ�����TRUE��ʧ�ܷ���FALSE��

--*/
BOOL CompletionPortModel::PostAcceptEx()
{
	while (m_lAcceptExCounter < 10)
	{
		SOCKET AcceptSocket = WSASocket(
										AF_INET,
										SOCK_STREAM,
										IPPROTO_IP,
										NULL,
										0,
										WSA_FLAG_OVERLAPPED
										);
		
		if (INVALID_SOCKET == AcceptSocket)
		{
			cout << "WSASocket failed " << endl;
			
			return FALSE;
		}
		PPER_IO_CONTEXT lpAcceptExIoContext = GetIoFromLookaside();
		if (NULL == lpAcceptExIoContext)
		{
			lpAcceptExIoContext = (PPER_IO_CONTEXT)HeapAlloc(
																GetProcessHeap(),
																HEAP_ZERO_MEMORY,
																sizeof(PER_IO_CONTEXT)
																);
			if (NULL == lpAcceptExIoContext)
			{
				cout << "HeapAlloc() failed " << endl;
				closesocket(AcceptSocket);
				
				return FALSE;
			}
		}
		ZeroMemory(&(lpAcceptExIoContext->ol), sizeof(lpAcceptExIoContext->ol));
		lpAcceptExIoContext->sClient = AcceptSocket;
		lpAcceptExIoContext->IoOperation = IoAccept;
		lpAcceptExIoContext->pNext = NULL;
		
		ZeroMemory(lpAcceptExIoContext->szBuffer, BUFFER_SIZE);
		lpAcceptExIoContext->wsaBuffer.buf = lpAcceptExIoContext->szBuffer;
		lpAcceptExIoContext->wsaBuffer.len = BUFFER_SIZE;
		lpAcceptExIoContext->unId = lpAcceptExIoContext->sClient;
		
		DWORD dwBytes;
		BOOL bSuccess = lpAcceptEx(
									m_ListenSocket,
									lpAcceptExIoContext->sClient,
									lpAcceptExIoContext->szBuffer,
									lpAcceptExIoContext->wsaBuffer.len - ((sizeof(SOCKADDR_IN) + 16) * 2),
									sizeof(SOCKADDR_IN) + 16,
									sizeof(SOCKADDR_IN) + 16,
									&dwBytes,
									&(lpAcceptExIoContext->ol)
									);

		if (FALSE == bSuccess)
		{
			int nResult = WSAGetLastError();
			if (nResult != ERROR_IO_PENDING)
			{
				cout << "AcceptEx() failed :" << nResult << endl;
				closesocket(AcceptSocket);
				HeapFree(GetProcessHeap(), 0 , lpAcceptExIoContext);
				
				return FALSE;
			}
			
			InsertNode(lpAcceptExIoContext, NULL); 
			InterlockedExchangeAdd(&m_lAcceptExCounter, 1);
		} 
	}
	InterlockedExchangeAdd(&m_lAcceptExCounter, -10);
	return TRUE;
}//end of PostAccetExRoutine()



/*++
Fucntion Description:
���ݲ������ͽ����ݽ��������뵽��Ӧ������ͷ��
Arguments:
pNode       -  Ҫ���������еĽ��
pHandleNode -  Ҫ���������еĽ��

Return Value:
��.
--*/
void CompletionPortModel::InsertNode(PPER_IO_CONTEXT pNode, PPER_HANDLE_CONTEXT pHandleNode)
{
	if (NULL != pNode)
	{  
		EnterCriticalSection(&m_ListCriSection);
		pNode->pNext = m_lpConnectionListHead->pNext;
		m_lpConnectionListHead->pNext = pNode;
		LeaveCriticalSection(&m_ListCriSection);
	}
	return;
}//end of InsertNode



/*++
Fucntion Description:

���߳�ѭ������WaitForSigleObject�ȴ�m_hEvent���Ѿ�������AcceptEx()���úľ���FD_ACCEPT
�¼�����������WaitForSigleObject�ɹ����أ�Ȼ�����PostAcceptEx()���·���10��AcceptEx()���á�
WaitForSigleObjectÿ�εȴ�10�룬��ʱ���غ󣬶�ϵͳ���Ѿ������ɹ��˵Ĳ��һ�û���շ������ݵ�
SOCKET���ӽ��м�⣬���ĳ�������Ѿ�������30�룬���һ�û�շ������ݣ���ǿ�ƹرա�
Arguments:

�ޡ�
Return Value:

�������óɹ�����TRUE������ʧ�ܷ���FALSE��

--*/
BOOL CompletionPortModel::ThreadLoop()
{
	int nOptval;
	int nOptlen;
	int nResult;
	DWORD dwResult;
	int nCounter = 0;
#ifdef _DEBUG
	int nTimeOut = 0;
#endif
	cout << "Server is running.........." << nCounter << " times" << endl; 
	
	while (TRUE)
	{  
		dwResult = WaitForSingleObject(m_hEvent, 10000);
		
		if (WAIT_FAILED == dwResult)
		{
			PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
			cout << "WSAWaitForMultipleEvents() failed: " << WSAGetLastError() << endl;
			return FALSE;
		}
		
		if (WAIT_TIMEOUT == dwResult)
		{ 
			nCounter++;
			cout << "Server is running.........." << nCounter << " times" << endl;
			
#ifdef _DEBUG
			nTimeOut++;
			cout << nTimeOut << "*******TIME_OUT********" << nTimeOut << endl;
#endif
			
			PPER_IO_CONTEXT lpCurentNode = m_lpConnectionListHead->pNext;
			PPER_IO_CONTEXT lpPreNode = m_lpConnectionListHead;
			PPER_IO_CONTEXT lpTempNode; 
			
			while (NULL != lpCurentNode)
			{ 
				EnterCriticalSection(&m_ListCriSection);
				nOptlen = sizeof(nOptval);
				
				nResult = getsockopt(
										lpCurentNode->sClient,
										SOL_SOCKET,
										SO_CONNECT_TIME,
										(char*)&nOptval,
										&nOptlen
										);
#ifdef _DEBUG
				cout << "nOptval = " << nOptval << endl;
#endif _DEBUG
				
				if (SOCKET_ERROR == nResult)
				{
					cout << "SO_CONNECT_TIME failed: " << WSAGetLastError() << endl;
					lpPreNode = lpCurentNode;
					lpCurentNode = lpCurentNode->pNext;
					LeaveCriticalSection(&m_ListCriSection);
					
					continue;
				}
				if ((nOptval!=0xFFFFFFFF) && (nOptval>30))
				{
					lpPreNode->pNext = lpCurentNode->pNext;
					lpTempNode = lpCurentNode;
					lpCurentNode = lpCurentNode->pNext;
					closesocket(lpTempNode->sClient);
					lpTempNode->pNext = NULL;
					InsertToLookaside(lpTempNode, NULL);
				}
				else
				{
					lpPreNode = lpCurentNode;
					lpCurentNode = lpCurentNode->pNext;
				}
				LeaveCriticalSection(&m_ListCriSection);
			}
		}
		else
		{
			if (WAIT_TIMEOUT != dwResult)
			{
				if (FALSE == PostAcceptEx())
				{
					PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
					
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}//end of CheckConnectTime



/*++
Fucntion Description:
�������д��ݵĽ��������н��,�����ͷŽ�㡣�Ա㲻��ThreadLoop����������г�ʱ��⡣
�˺�������ɶ˿��߳����շ����ݳɹ�����á�
Arguments:

Ҫ���������ͷŵĽ�㡣
Return Value:
�ޡ�

--*/
void CompletionPortModel::ReleaseNode(PPER_IO_CONTEXT pNode)
{
	PPER_IO_CONTEXT pTempNode = m_lpConnectionListHead->pNext;
	PPER_IO_CONTEXT pPreNode =m_lpConnectionListHead;
	PPER_IO_CONTEXT pDeleteNode;
	
	while (NULL != pTempNode)
	{
		if (pNode->unId == pTempNode->unId)
		{  
			pPreNode->pNext = pTempNode->pNext;
			pDeleteNode = pTempNode;
			pTempNode = pTempNode->pNext;
			
			return;
		}
		else
		{ 
			pPreNode = pTempNode;
			pTempNode = pTempNode->pNext;
		}
	}
	return;
}//end of RealeseNode



/*++
Fucntion Description:
���ݴ�������nFlags������lpPerIoContext�������ã���ָʾ��һ��IO������
Arguments:

lpPerIoContext - ����GetQueueCompletionStatus�����õ�����һ��IO�����Ľ��(��չ��
WSAOVERLAPPED�ṹ)��
nFlags         - ָ���Ѿ������һ��IO�Ĳ������͡�
Return Value:
�������óɹ�����TRUE��ʧ�ܷ���FALSE��

--*/
BOOL CompletionPortModel::HandleData(PPER_IO_CONTEXT lpPerIoContext, int nFlags)
{
	//
	//nFlags == IO_READ_COMPLETION��ʾ��ɵ���һ��IO������WSARecv��
	//
	if (IO_READ_COMPLETION == nFlags)
	{
		//
		//�����WSARecv����������Ҫ����WSASend�Ѹս��յ������ݷ��ͻ�ȥ����
		//lpPerIoContext->ContinueAction = ContinueWrite;
		//
		lpPerIoContext->IoOperation = IoWrite;
		ZeroMemory(&(lpPerIoContext->ol), sizeof(WSAOVERLAPPED));
		
		//
		//���յ���������lpPerIoContext->wsaBuffer.buf����Ե���
		//�Զ��庯�����������д��������У��򵥵Ľ������ٷ��ͻ�ȥ
		//
		strcpy(lpPerIoContext->szBuffer, lpPerIoContext->wsaBuffer.buf);
		lpPerIoContext->wsaBuffer.buf = lpPerIoContext->szBuffer;
		lpPerIoContext->wsaBuffer.len = BUFFER_SIZE;
		
		return TRUE;
	}
	if (IO_WRITE_COMPLETION == nFlags)
	{
		//
		//��һ��IO����WSASend���ݷ�����ɣ�������������־����Ϊ�ر�
		//�������Ҫ�رն���Ҫ�������ͣ���lpPerIoContext->IoOperation����Ϊ
		//IoWrite�����Ҫ�������գ���lpPerIoContext->IoOperation����Ϊ
		//IoRead,����ʼ����BUFFER,�����У����ùر�
		//
		lpPerIoContext->IoOperation = IoEnd;
		return TRUE;
	}
	if (IO_ACCEPT_COMPLETION == nFlags)
	{
		//
		//�ս�����һ�����ӣ�����û���շ����ݣ�������
		//
		lpPerIoContext->IoOperation = IoRead;
		ZeroMemory(&(lpPerIoContext->ol), sizeof(WSAOVERLAPPED));
		ZeroMemory(lpPerIoContext->szBuffer, BUFFER_SIZE);
		lpPerIoContext->wsaBuffer.len = BUFFER_SIZE;
		lpPerIoContext->wsaBuffer.buf = lpPerIoContext->szBuffer;
		return TRUE;
	}
	
	
	return FALSE;
}// end of HandleData()



/*++
Fucntion Description:
��ʼ������ͷָ�롣
Arguments:
�ޡ�
Return Value:
�������óɹ�����TRUE��ʧ�ܷ���FALSE��

--*/
BOOL CompletionPortModel::InitLinkListHead()
{
	m_lpConnectionListHead = (PPER_IO_CONTEXT)HeapAlloc(
														GetProcessHeap(),
														HEAP_ZERO_MEMORY,
														sizeof(PER_IO_CONTEXT)
														);
	
	if (NULL == m_lpConnectionListHead)
	{
		cout << "HeapAlloc() failed " << endl;
		
		return FALSE;
	}
	m_lpConnectionListHead->pNext = NULL;
	
	return TRUE;
}// end of InitLinkListHead()



/*++
Fucntion Description:
��FD_ACCEPT�¼�ע�ᵽm_hEvent������������AcceptEx���ñ��ľ���ʱ�򣬾ͻᴥ��FD_ACCEPT
�¼���Ȼ��ThreadLoop���WaitForSingleObject�ͻ�ɹ����أ�����PostAcceptEx�����á�
Arguments:
�ޡ�
Return Value:
�������óɹ�����TRUE��ʧ�ܷ���FALSE��

--*/
BOOL CompletionPortModel::AllocEventMessage()
{
	m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (NULL == m_hEvent)
	{
		PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
		cout << "CreateEvent() failed: " << GetLastError() << endl;
		return FALSE;
	}
	
	int nResult = WSAEventSelect(m_ListenSocket, m_hEvent, FD_ACCEPT);
	if (SOCKET_ERROR == nResult)
	{
		PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
		CloseHandle(m_hEvent);
		cout << "WSAEventSeclet() failed: " << WSAGetLastError() << endl;
		
		return FALSE;
	}
	return TRUE;
}//end of AllocEventMessage()



/*++
Fucntion Description:
���ݲ���lpPerIoContext�ĳ�ԱIoOperation��ֵ��������һ��IO������
Arguments:

lpPerIoContext        - ����WSASend����WSARecvһ��Ͷ�ݵ���չWSAOVERLAPPED�ṹ��
lpNewperHandleContext - AcceptEx���óɹ�������׽��ַ����"���������"��
Return Value:
�������óɹ�����TRUE��ʧ�ܷ���FALSE��

--*/
BOOL CompletionPortModel::DataAction(PPER_IO_CONTEXT lpPerIoContext, PPER_HANDLE_CONTEXT lpNewperHandleContext)
{
	int nResult;
	DWORD dwIosize = 0;
	DWORD dwFlags =0;
	if (IoWrite == lpPerIoContext->IoOperation)
	{
		nResult = WSASend(
							lpPerIoContext->sClient,
							&(lpPerIoContext->wsaBuffer),
							1,
							&dwIosize,
							0,
							&(lpPerIoContext->ol),
							NULL
							);
		
		if((SOCKET_ERROR==nResult) && (ERROR_IO_PENDING != WSAGetLastError()))
		{
			cout << "WSASend() failed: " << WSAGetLastError() << endl;
			
			closesocket(lpPerIoContext->sClient);
			lpPerIoContext->pNext = NULL;
			lpNewperHandleContext->pNext = NULL;
			InsertToLookaside(lpPerIoContext, NULL);
			InsertToLookaside(NULL, lpNewperHandleContext);
			
			return FALSE;
		}
	}
	
	if (IoRead == lpPerIoContext->IoOperation)
	{
		nResult = WSARecv(
							lpPerIoContext->sClient,
							&(lpPerIoContext->wsaBuffer),
							1,
							&dwIosize,
							&dwFlags,
							&(lpPerIoContext->ol),
							NULL
							);
		
		if((SOCKET_ERROR==nResult) && (ERROR_IO_PENDING != WSAGetLastError()))
		{
			cout << "WSARecv() failed: " << WSAGetLastError() << endl;
			
			closesocket(lpPerIoContext->sClient);
			lpNewperHandleContext->pNext = NULL;
			lpPerIoContext->pNext = NULL;
			InsertToLookaside(lpPerIoContext, NULL);
			InsertToLookaside(NULL, lpNewperHandleContext);
			
			return FALSE;
		}
		
	}
	
	if (IoEnd == lpPerIoContext->IoOperation)
	{
		closesocket(lpPerIoContext->sClient);
		lpNewperHandleContext->pNext = NULL;
		InsertToLookaside(NULL, lpNewperHandleContext);
		lpPerIoContext->pNext = NULL;
		InsertToLookaside(lpPerIoContext, NULL);
	}
	return TRUE;
}// end of DataAction()



/*++
Fucntion Description:
���๹�캯�����õĺ������������������Ҫ�󶨵ı���IP��ַ�Ͷ˿ڡ�
Arguments:

�ޡ�
Return Value:

�ޡ�   

--*/
void CompletionPortModel::GetAddressAndPort()
{
	cout << "\nPlease input a port: ";
	cin >> uPort;
	cout << "\nPlease input localaddress:";
	cin >> szAddress;
	system("cls");
	return;
}// end of GetAddressAdnPort




/*++
Fucntion Description:
�������б�������в���һ�����еĽ�㡣
Arguments:

lpIoNode     - Ҫ����Ľ�㣬����ΪPPER_IO_CONTEXT��
lpHandleNode - Ҫ����Ľ�㣬����ΪPPER_HANDLE_CONTEXT��
Return Value:

�ޡ�   

--*/
void CompletionPortModel::InsertToLookaside(PPER_IO_CONTEXT lpIoNode, PPER_HANDLE_CONTEXT lpHandleNode)
{
	if (NULL != lpIoNode)
	{
		if (NULL == m_lpIoLookasideLists)
		{
			m_lpIoLookasideLists = lpIoNode;
			
			return;
		}
		lpIoNode->pNext = m_lpIoLookasideLists->pNext;
		m_lpIoLookasideLists->pNext = lpIoNode;
		
		return;
	}
	if (NULL != lpHandleNode)
	{
		if (NULL == m_lpHandleLOOKasideLists)
		{
			m_lpHandleLOOKasideLists = lpHandleNode;
			
			return;
		}
		lpHandleNode->pNext = m_lpHandleLOOKasideLists->pNext;
		m_lpHandleLOOKasideLists->pNext = lpHandleNode;
		
		return;
	}
	return;
}



/*++
Fucntion Description:
�������б��н��һ����㲢���䷵�ء�
Arguments:

�ޡ�
Return Value:

����һ��PPER_IO_CONTEXT���͵Ľ�㡣   

--*/
PPER_IO_CONTEXT CompletionPortModel::GetIoFromLookaside()
{
	if (NULL == m_lpIoLookasideLists)
	{
		return NULL;
	}
	EnterCriticalSection(&m_IoCriSection);
	PPER_IO_CONTEXT lpReturnNode = m_lpIoLookasideLists;
	m_lpIoLookasideLists = m_lpIoLookasideLists->pNext;
	LeaveCriticalSection(&m_IoCriSection);
	return lpReturnNode;
}



/*++
Fucntion Description:
�������б��н��һ����㲢���䷵�ء�
Arguments:

�ޡ�
Return Value:

����һ��PPER_HANDLE_CONTEXT���͵Ľ�㡣   

--*/
PPER_HANDLE_CONTEXT CompletionPortModel::GetHandleFromLookaside()
{
	if (NULL == m_lpHandleLOOKasideLists)
	{
		return NULL;
	}
	EnterCriticalSection(&m_HandleCriSection);
	PPER_HANDLE_CONTEXT lpReturnNode = m_lpHandleLOOKasideLists;
	m_lpHandleLOOKasideLists = m_lpHandleLOOKasideLists->pNext;
	LeaveCriticalSection(&m_HandleCriSection);
	
	return lpReturnNode;
}
