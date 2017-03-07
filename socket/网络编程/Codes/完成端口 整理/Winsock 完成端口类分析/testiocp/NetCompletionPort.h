/*++
Copyright (c) 2004 
ģ����: 
iomodel.h
ģ������:
Winsock ��ɶ˿���ͷ�ļ�

��������:

Visual C++ 6.0, Windows 2000.

�޶���¼:
������: 2004.1.16
����޸�����:
2004.1.23
	  
--*/
#ifndef      _IOMODEL_H
#define      _IOMODEL_H
//
//Head files
//
#include <winsock2.h>
#include <mswsock.h>

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	
#define    BUFFER_SIZE           4096
#define    MAXTHREAD_COUNT       8
#define    PORT                  18080
#define    LOCALADDRESS          "10.158.110.111"
#define    IO_READ_COMPLETION    100
#define    IO_WRITE_COMPLETION   200
#define    IO_ACCEPT_COMPLETION  300
	
	//
	//�Զ���ö���������ͣ�������ʶ�׽���IO��������
	//
	typedef enum _IO_OPERATION 
	{
		IoAccept,	//AcceptEx/accept
		IoRead,		//WSARecv/recv/ReadFile
		IoWrite,	//WSASend/send/WriteFile
		IoEnd
	}
	IO_OPERATION, *PIO_OPERATION;
	//
	//�Զ���ṹ����"��ɼ�"(���������)
	//
	typedef struct _PER_HANDLE_CONTEXT
	{
		SOCKET                     IoSocket;
		_PER_HANDLE_CONTEXT*       pNext;
	}
	PER_HANDLE_CONTEXT, *PPER_HANDLE_CONTEXT;
	
	//
	//��IO���ݣ���չ��WSAOVERLAPPED
	//
	typedef struct _PER_IO_CONTEXT
	{
		WSAOVERLAPPED              ol;
		char                       szBuffer[BUFFER_SIZE];
		WSABUF                     wsaBuffer;
		SOCKET                     sClient;
		unsigned int               unId;
		IO_OPERATION               IoOperation;
		_PER_IO_CONTEXT*           pNext; 
	}
	PER_IO_CONTEXT, *PPER_IO_CONTEXT;
	//
	// global var
	//
	static  GUID g_GUIDAcceptEx = WSAID_ACCEPTEX;
	static  GUID g_GUIDTransmitFile = WSAID_TRANSMITFILE;
	DWORD __stdcall   CompletionRoutine(LPVOID);
	
	//
	//��ɶ˿�ģ����
	//
	
	class CompletionPortModel
	{
	public:
		CompletionPortModel();
		~CompletionPortModel();

		BOOL                Init();
		BOOL                ThreadLoop();
		BOOL                AllocEventMessage();
		BOOL                PostAcceptEx();
		
		virtual BOOL        HandleData(
										PPER_IO_CONTEXT lpPerIoContext, 
										int nFlags
										);
		virtual BOOL        DataAction(
										PPER_IO_CONTEXT lpPerIoContext,
										PPER_HANDLE_CONTEXT lpNewperHandletext
										);
		
		void                InsertNode(
										PPER_IO_CONTEXT pNode,
										PPER_HANDLE_CONTEXT pHandleNode
										);

		void                ReleaseNode(PPER_IO_CONTEXT pNode);

		void                InsertToLookaside(
												PPER_IO_CONTEXT lpIoNode,
												PPER_HANDLE_CONTEXT lpHandleNode
												);

		PPER_IO_CONTEXT     GetIoFromLookaside();
		PPER_HANDLE_CONTEXT GetHandleFromLookaside();
		
		
		
		HANDLE                        m_hCOP;
		SOCKET                        m_ListenSocket;
		
		CRITICAL_SECTION              m_ListCriSection;
		CRITICAL_SECTION              m_HandleCriSection;
		CRITICAL_SECTION              m_IoCriSection;
		LPFN_TRANSMITFILE             lpTransmitFile;
		volatile PPER_IO_CONTEXT      m_lpIoLookasideLists;
		volatile PPER_HANDLE_CONTEXT  m_lpHandleLOOKasideLists;
		
	protected:
		BOOL                InitWinsock();
		BOOL                BindAndListenSocket();
		BOOL                InitLinkListHead();
		void                CloseThreadHandle();
		void                GetAddressAndPort();
		
		UINT                uPort;
		char                szAddress[20];
		
		HANDLE                        m_hThreadArray[MAXTHREAD_COUNT];
		HANDLE                        m_hEvent;
		
		volatile LONG                 m_lAcceptExCounter;
		volatile PPER_IO_CONTEXT      m_lpConnectionListHead;
		LPFN_ACCEPTEX                 lpAcceptEx;
	private:
	};



#ifdef __cplusplus
}
#endif
#endif  //_IOMODEL_H

