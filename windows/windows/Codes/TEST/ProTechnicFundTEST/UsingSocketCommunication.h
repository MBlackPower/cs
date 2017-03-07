// UsingSocketCommunication.h: interface for the CUsingSocketCommunication class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USINGSOCKETCOMMUNICATION_H__B3FACE91_98EE_40CB_875E_53B3DC02832E__INCLUDED_)
#define AFX_USINGSOCKETCOMMUNICATION_H__B3FACE91_98EE_40CB_875E_53B3DC02832E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Winsock2.h"

#pragma comment(lib, "Ws2_32")


typedef struct _COMMUNICATION
{
	
	SOCKET			   AcceptSocket;
	
}COMMUNICATION, *PCOMMUNICATION;


class CUsingSocketCommunication  
{
public:
	CUsingSocketCommunication();
	virtual ~CUsingSocketCommunication();

};


/************************************************************************/
/*                                                                      */
/************************************************************************/
class CTCP_SocketCommuntication : public CUsingSocketCommunication
{
public:
	CTCP_SocketCommuntication();
	virtual ~CTCP_SocketCommuntication();


	static ACE_Thread_Mutex m_mutex;

public:
///////////////////////////////////���������߳�
	static BOOL StartNetWorkListenTask();

///////////////////////////////////��������
	static unsigned _stdcall ReceiveControlMsgTask( LPVOID param );

private:
///////////////////////////////////��ʼ���׽���
	static int InitializeSocket(
								IN	SOCKET		&sockCommunication,
								IN	u_short		 dwCommunicationPort );

private:
///////////////////////////////////���������߳�
	static unsigned __stdcall __RunNetWorkListenTask( LPVOID param );
};








/************************************************************************/
/*                                                                      */
/************************************************************************/
class CUDP_SocketCommuntication : public CUsingSocketCommunication
{
public:
	SOCKET m_UdpSocket;

public:
	CUDP_SocketCommuntication();
	virtual ~CUDP_SocketCommuntication();

public:
	int	CreateReceiveTask();

	bool SendMsg( PCHAR		Msg,
				  int		Len,
				  PCHAR		host,
				  short		port );

private:
	static unsigned __stdcall __ReceiveTask( LPVOID param );

};
#endif // !defined(AFX_USINGSOCKETCOMMUNICATION_H__B3FACE91_98EE_40CB_875E_53B3DC02832E__INCLUDED_)
