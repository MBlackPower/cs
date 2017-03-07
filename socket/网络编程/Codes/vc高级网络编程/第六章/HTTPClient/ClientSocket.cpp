// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "HTTPClient.h"
#include "ClientSocket.h"
#include "HttpClientView.h"
#include "clientsocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket(CHTTPClientView* pView)
{
	m_pView = pView;
}

CClientSocket::~CClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions

void CClientSocket::OnReceive(int nErrorCode) 
{
	m_pView->Receive();
	CAsyncSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnSend(int nErrorCode) 
{
	CAsyncSocket::OnSend(nErrorCode);
}

void CClientSocket::OnConnect(int nErrorCode) 
{
	if(nErrorCode != 0){
		int nRet = AfxMessageBox("���ӷ�����ʧ�ܣ��Ƿ����ԣ�",MB_OKCANCEL);
		if(nRet == IDOK){
			m_pView->Connect();
			return;
		}
		else
			return;
	}
	m_pView->m_bConnected = TRUE;
	m_pView->TextOut("�ɹ����ӵ���������\n", RGB(255,122,100));
	if(m_pView->m_bSend){
		m_pView->SendData();
		m_pView->m_bSend = FALSE;
	}
	CAsyncSocket::OnConnect(nErrorCode);
}
