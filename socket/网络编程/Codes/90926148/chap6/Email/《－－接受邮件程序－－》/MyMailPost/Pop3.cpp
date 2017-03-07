// Pop3.cpp: implementation of the CPop3 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MailPost.h"
#include "Pop3.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPop3::CPop3()
{
	// ��ʼ������
	m_sError = _T("");
	m_sock = INVALID_SOCKET;
	m_nMails = 0;
	m_nSize = 0;
	m_bList = FALSE;
	m_bState = FALSE;
	m_arSizes.RemoveAll();
	m_arHeaders.RemoveAll();
	m_bConnected = FALSE;
	m_dwTimeout = 2000;
}

CPop3::~CPop3()
{

}

BOOL CPop3::Connect(LPCTSTR strAddress, LPCTSTR strUser, LPCTSTR strPassword,UINT nPort)
{
	// ��ʼ�������׽���
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET)
	{
		m_sError = _T("��ʼ���׽���ʧ��");
		return FALSE;
	}

	// ��ʼ��Զ���׽���
	SOCKADDR_IN sockAddr;
	memset(&sockAddr,'\0',sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons((u_short)nPort);
	sockAddr.sin_addr.s_addr = inet_addr(strAddress);

	// �������������IP��ַ����gethostbyname�����IP��ַ
	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(strAddress);
		if (lphost)
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
		{
			m_sError = _T("�޷�������ַ!"); 
			return FALSE;
		}
	}
	
	// ���������������
	if (connect(m_sock,(SOCKADDR *)(&sockAddr),sizeof(sockAddr)) == SOCKET_ERROR)
	{
		m_sError = _T("�޷����������������!");
		return FALSE;
	}

	// ���ջ�Ӧ��Ϣ
	if (!GetResponse())
	{
		// ��Ӧʧ��
		m_sError = _T("�޷��յ���Ӧ��Ϣ���յ�������Ϣ!");
		Disconnect();
		return FALSE;
	}

	// �����û���
	CString strTemp;
	strTemp.Format("USER %s\r\n",strUser);
    if (!Send((LPCTSTR)strTemp,strTemp.GetLength()))
    {
		// �����û���ʧ��
		m_sError = _T("�����û���ʧ��!");
		return FALSE;
    }

	// ���ջ�Ӧ��Ϣ
    if (!GetResponse())
    {
		// ���ջ�Ӧ��Ϣʧ��
		m_sError = _T("�޷��յ���Ӧ��Ϣ���յ���Ч��Ϣ!");
		Disconnect();
		return FALSE;
    } 

    // ��������
	strTemp.Format("PASS %s\r\n",strPassword);
    if (!Send((LPCTSTR)strTemp,strTemp.GetLength()))
    {
		// ��������ʧ��
		m_sError = _T("��������ʧ��!");
		Disconnect();
		return FALSE;
    }

	// ���ջ�Ӧ��Ϣ
    if (!GetResponse())
    {
		// ���ջ�Ӧ��Ϣʧ��
		m_sError = _T("�޷��յ���Ӧ��Ϣ���յ���Ч��Ϣ!");
		Disconnect();
		return FALSE;
    } 

	m_bConnected = TRUE;
	return TRUE;
}

BOOL CPop3::GetResponse(void)
{
	TCHAR chArray[1188];
	if (!ReadResponse(chArray,1188,FALSE))
	{
		return FALSE;
	}
	m_sResponse = chArray;
	return TRUE;
}

BOOL CPop3::ReadResponse(TCHAR *pChar, UINT nSize, BOOL bDouble)
{
	CString strTemp;

	// ��ȡ��Ӧ��Ϣ
	BOOL bEnd = FALSE;
	UINT nReceived = 0;
	DWORD dwStart = ::GetTickCount();
	while (!bEnd)
	{
		// ����ʱ�䵽
		if ((::GetTickCount() - dwStart) >	m_dwTimeout)
		{
			pChar[nReceived] = '\0';
			m_sError = _T("��ʱ");
			// ���浱ǰ��Ӧ����Ϣ
			m_sResponse = pChar;
			return FALSE;
		}

		// ���׽����Ƿ�ɶ�
		timeval timeout = {0, 0};
		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(m_sock,&fds);
		int nStatus = select(0,&fds,NULL,NULL,&timeout);

		if (nStatus == SOCKET_ERROR)
		{
			// �׽��ֲ��ɶ�
			m_sError = _T("�׽��ֲ��ɴ�");
			return FALSE;
		}
		else if (!nStatus)
		{
			// û�н��յ�����
			::Sleep(688);
			continue;
		}

		// ���׽����н�������
		::Sleep(288);
		nStatus = recv(m_sock,pChar + nReceived,nSize,0);
		if (nStatus == SOCKET_ERROR)
		{
			pChar[nReceived] = '\0';
			// �׽��ִ���
			m_sError = _T("δ�ܴ��׽������յ�����!");
			// ���浱ǰ��Ӧ��Ϣ
			m_sResponse = pChar; 
			return FALSE; 
		}
		else if (nStatus)
		{
			// ���ü�ʱ��
			dwStart = ::GetTickCount();
			// ���յ���������������
			nReceived += nStatus;
		}

		// ��pChar��Ϊ�ַ�����������CString�͵ı���
		pChar[nReceived] = '\0';
		strTemp = pChar;
								
		// ����Ƿ��յ��˽�����־
		LPCTSTR lpszComp = bDouble ? "\r\n.\r\n" : "\r\n";
		bEnd = (strTemp.Find(lpszComp) != -1);
	}

	// ȥ��������־
	nReceived -= bDouble ? 3 : 0;
	pChar[nReceived] = '\0';

	// ����Ӧ��Ϣ�Ƿ���Ч
	strTemp = pChar;
	strTemp.MakeUpper();
	int nStart = strTemp.Find("+OK");
	if (nStart == -1)
	{
		// �յ���Ч��Ϣ
		m_sError = _T("��Ӧ��Ϣ��Ч");
		return FALSE;
	}
	// ��ȡ��Ч��Ϣ
	strTemp = pChar;
	m_sResponse = strTemp.Right(strTemp.GetLength() - nStart - 3);
	
	return TRUE;
}

BOOL CPop3::Disconnect()
{
	BOOL bSuccess;
	
	// �������������״̬��Ͽ�
	if (m_bConnected)
	{
		CString strSend = "QUIT\r\n";
		// ���ͶϿ�����
		if (!this->Send((LPCTSTR)strSend,strSend.GetLength()))
		{
			AfxMessageBox(_T("���ͶϿ�����ʧ��"));
			return FALSE;
		}

		bSuccess = this->GetResponse();

		// ���йصı�����λ
	    m_bConnected = FALSE;
		m_bList = FALSE;
	    m_bState = FALSE;
		m_nMails = 0;
		m_nSize = 0;
		m_arHeaders.RemoveAll();
		m_arSizes.RemoveAll();

		// �ر��׽���
		closesocket(m_sock);
		m_sock = INVALID_SOCKET;
	}

	return bSuccess;
}

BOOL CPop3::Send(LPCTSTR lpszSend, UINT nLength)
{
	return send(m_sock,lpszSend,nLength,0) != SOCKET_ERROR;
}

BOOL CPop3::ReadState()
{
	// ��÷��ص�״̬��Ϣ
	if (!GetResponse())
	{
		// ���շ�����Ϣʧ��
		m_sError = _T("���շ�����Ϣʧ��!");
		return FALSE;
	}

	// �����ص���Ϣ�Ƿ���Ч
	m_sResponse.MakeUpper();
	UINT nEnd = 0;
	if (m_sResponse.Find("+OK") == -1)
	{
		// �յ���Ч�Ļ�Ӧ��Ϣ
		m_sError = _T("������Ϣ��Ч!");
		return FALSE;
	}
	else
	{ 
		// �����ʼ����ʹ�С�����ȷ�����Ŀ
		return this->ParseNumAndSize(m_nMails,m_nSize,(LPCTSTR)m_sResponse,nEnd);
	}
}

UINT CPop3::GetMailCount() const
{
	return m_nMails;
}

BOOL CPop3::ParseNumAndSize(UINT &nNum, UINT &nSize,LPCTSTR lpszBuf,UINT &nEnd)
{
	BOOL bNum = TRUE;
	for (int i = nEnd,j = -1;lpszBuf[i];i++)
	{
		if (isdigit(lpszBuf[i]))
			j = (j == -1) ? i : j;
		else
		{	
			if (j == -1)
			{
				// ��δ��������
				continue;
			}

			// ������һ���ֶ�
			else if (bNum)
			{
				// ������Ŀ
				m_nMails = atoi(&lpszBuf[j]);
				nNum = m_nMails;
				bNum = FALSE;
				j = -1;
			}

			else
			{
				// ������С
				m_nSize = atoi(&lpszBuf[j]);
				nSize = m_nSize;
				nEnd = i;
				return TRUE;
			}
		}
	}
	nEnd = i;
	return FALSE;
}

BOOL CPop3::ReadList()
{
	UINT nBuf = m_nMails * 18 + 188;
	char *pBuf = new char[nBuf];
	if (!pBuf)
	{
		return FALSE;
	}
	if (!ReadResponse(pBuf,nBuf,TRUE))
	{
		return FALSE;
	}
	m_arSizes.RemoveAll();
	m_arSizes.SetSize(m_nMails);
	UINT nNum,nSize,nEnd = 0;
	while (ParseNumAndSize(nNum,nSize,m_sResponse,nEnd))
	{
		m_arSizes.SetAt(nNum - 1,nSize);
	}

	return TRUE;
}

DWORD CPop3::GetMsgSize(UINT nID) 
{
	BOOL bSuccess;
	if (!m_bList)
		bSuccess = this->List();
	if (!bSuccess)
		return 0;

	return m_arSizes.GetAt(nID);
}

BOOL CPop3::ListHeader()
{
	m_arHeaders.RemoveAll();
	m_arHeaders.SetSize(m_nMails);
	CString strTemp;
	for (UINT nMsg = 1;nMsg <= m_nMails;nMsg++)
	{
		strTemp.Format("TOP %d 0\r\n",nMsg);
		if (!Send((LPCTSTR)strTemp,strTemp.GetLength()))
		{
			m_sError = _T("����TOP����ʧ��!");
			return FALSE;
		}

		if (!GetResponse())
		{
			m_sError = _T("�о��ʼ�����ʧ��!");
			return FALSE;
		}
		
		strTemp = m_sResponse;
		strTemp.MakeUpper();
		
		// ����SUBJECT��
		UINT nStart = strTemp.Find("\r\nSUBJECT:");
		if (nStart == -1)
		{
			m_arHeaders.SetAt(nMsg - 1,_T(""));			
			return TRUE;
		}
		strTemp = m_sResponse.Right(m_sResponse.GetLength() - nStart - 10);
		nStart = strTemp.Find("\r\n");
		if (nStart != -1)
			strTemp = strTemp.Left(nStart);
		strTemp.TrimLeft();
		strTemp.TrimRight();
		m_arHeaders.SetAt(nMsg - 1,strTemp);
	}

	return TRUE;
}

BOOL CPop3::Delete(UINT nIndex)
{
	CString strSend;
	strSend.Format("DELE %d\r\n",nIndex);

	// ����DELE����
	if (!Send((LPCTSTR)strSend,strSend.GetLength()))
	{
		// δ�ܳɹ�����
		m_sError = _T("ɾ���ʼ�ʧ��!");
		return FALSE;
	}

	// ���շ�����Ϣ
	if (!GetResponse())
	{
		m_sError = _T("�յ���Ч��Ϣ!");
		return FALSE;
	}
	
	// ��һ��STAT��LIST����õ�����Ϣ��Ч
	m_bState = FALSE;
	m_bList = FALSE;
	return TRUE;
}

BOOL CPop3::RetrieveMail(UINT nIndex,CString &strMsg)
{
	CString strSend;
	strSend.Format("RETR %d\r\n",nIndex);
	if (!Send((LPCTSTR)strSend,strSend.GetLength()))
	{
		m_sError = _T("��ȡ�ʼ�ʧ��!");
		return FALSE;
	}

	if (!GetResponse())
	{
		m_sError = _T("�޷��յ��ͻص��ʼ�!");
		return FALSE;
	}

	// ��CONTENT-DISPOSITION: INLINEΪ��ʼ��־
	strMsg = m_sResponse;
	strMsg.MakeUpper();
	int nStart = strMsg.Find("CONTENT-DISPOSITION: INLINE\r\n");
	strMsg = m_sResponse.Right(m_sResponse.GetLength() - nStart - 29);

	// ���б�ʾ�ʼ�����
	nStart = strMsg.Find("\r\n\r\n");
	strMsg = strMsg.Right(strMsg.GetLength() - nStart - 4);
	// ���б�ʾ�ʼ����Ľ���
	nStart = strMsg.Find("\r\n\r\n");
	if (nStart != -1)
		strMsg = strMsg.Left(nStart);
	return TRUE;
}

BOOL CPop3::List()
{
	CString strTemp = "LIST\r\n";
	if (m_bList)
		return TRUE;
	if (!Send((LPCTSTR)strTemp,strTemp.GetLength()))
	{
		// ����ʧ��
		m_sError = _T("��ѯ����״̬ʧ��!");
		Disconnect();
		return FALSE;
	}

	if (!ReadList())
	{
		// ���ջ�Ӧ��Ϣʧ��
		m_sError = _T("�޷��յ��ʼ�״̬��Ϣ���յ���Ч��Ϣ!");
		Disconnect();
		return FALSE;
    }

	return TRUE;
}

BOOL CPop3::GetState()
{
	CString strTemp = "STAT\r\n";
	if (m_bState)
		return TRUE;
	if (!Send((LPCTSTR)strTemp,strTemp.GetLength()))
	{
		// ����ʧ��
		m_sError = _T("��ѯ����״̬ʧ��!");
		Disconnect();
		return FALSE;
	}

    if (!ReadState())
    {
		// ���ջ�Ӧ��Ϣʧ��
		m_sError = _T("�޷��յ�����״̬��Ϣ���յ���Ч��Ϣ!");
		Disconnect();
		return FALSE;
    }

	return TRUE;
}

LPCTSTR CPop3::GetErrorString()
{
	return (LPCTSTR)m_sError;
}

BOOL CPop3::Noop()
{
	CString strTemp = "NOOP\r\n";

	// ����NOOP����
	if (!Send((LPCTSTR)strTemp,strTemp.GetLength()))
	{
		// ����ʧ��
		m_sError = _T("���пղ���ʧ��!");
		Disconnect();
		return FALSE;
	}

	// ���ջ�Ӧ��Ϣ
    if (!GetResponse())
    {
		// ���ջ�Ӧ��Ϣʧ��
		m_sError = _T("�޷��յ���Ӧ��Ϣ���յ���Ч��Ϣ!");
		Disconnect();
		return FALSE;
    }

	return TRUE;
}

LPCTSTR CPop3::GetMailHeader(UINT nIndex)
{
	return (LPCTSTR)m_arHeaders.GetAt(nIndex);
}


BOOL CPop3::Reset()
{
	CString strTemp = "RSET\r\n";

	// ����RSET����
	if (!Send((LPCTSTR)strTemp,strTemp.GetLength()))
	{
		m_sError = _T("����RSET����ʧ��!");
		return FALSE;
	}
	
	// ���ջ�Ӧ��Ϣ
	if (!GetResponse())
	{
		// ���ջ�Ӧ��Ϣʧ��
		m_sError = _T("��Ӧʧ��!");
		return FALSE;
	}

	return TRUE;
}
