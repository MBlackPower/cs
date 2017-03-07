// Pop3.h: interface for the CPop3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POP3_H__C7D744E6_CB2C_44AC_9E1D_71D0D9F1D1CC__INCLUDED_)
#define AFX_POP3_H__C7D744E6_CB2C_44AC_9E1D_71D0D9F1D1CC__INCLUDED_

#include "Pop3Socket.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPop3  
{
public:
	BOOL Reset(void);
	// ����ʼ�����
	LPCTSTR GetMailHeader(UINT nIndex);
	// ����NOOP�������һ�οղ���
	BOOL Noop(void);
	// ��ó�����Ϣ
	LPCTSTR GetErrorString(void);
	// ����STAT�������ʼ������״̬��Ϣ
	BOOL GetState(void);
	// ����LIST�������ʼ��ľ���״̬��Ϣ
	BOOL List(void);
	// ����RETR��������ʼ�����
	BOOL RetrieveMail(UINT nIndex,CString &strMsg);
	// ����DELE�������ѡ�ʼ����Ϊɾ��
	BOOL Delete(UINT nIndex);
	// ����TOP���������е��ʼ�����
	BOOL ListHeader(void);
	// ˽�б����ӿں��������ظ����������ʼ���С
	DWORD GetMsgSize(UINT nID);
	// ˽�б����ӿں����������ʼ���Ŀ
	UINT GetMailCount(void) const;
	// ��������
	BOOL Send(LPCTSTR lpszSend,UINT nLength);
	// �Ͽ����ӣ�����QUIT�������������ɾ����Ҫ����ʼ�
	BOOL Disconnect(void);
	// ����������������ӣ����а�����¼�Ĺ���
	BOOL Connect(LPCTSTR strAddress,LPCTSTR strUser,LPCTSTR strPassword,UINT nPort = 110);
	CPop3();
	virtual ~CPop3();

protected:
	// �����ʼ��������С
	UINT m_nSize;
	// ͨ�ŵ��׽���
	SOCKET m_sock;
	// �ʼ���Ŀ����GetMailCountΪ�ӿں���
	UINT m_nMails;
	// ��¼�Ƿ��͹���Ч��LIST����
	BOOL m_bList;
	// ��¼�Ƿ��͹���Ч��STAT����
	BOOL m_bState;
	// ��¼ÿ���ʼ���С��MFC�������
	CDWordArray m_arSizes;
	// ��¼ÿ���ʼ������MFC�������
	CStringArray m_arHeaders;
	// ��¼�Ƿ��Ѿ����������������
	BOOL m_bConnected;
	// ��¼��Ӧ����Ϣ
	CString m_sResponse;
	// ȷ���Ƿ�ʱ��ֻҪ��ȥ��ʱ�䳬����ֵ�ͱ�ʾ��ʱ
	// Ӧ�ò�ȡ��Ӧ��ʩ
	DWORD m_dwTimeout;

private:
	// ��¼������Ϣ����GetErrorStringΪ�ӿں���
	CString m_sError;
	// ȥ����ͷ��+OK��ʶ����û�Ӧ����Ч��Ϣ
	// �ӷ��ص���Ϣ����ȡ��Ŀ�ʹ�С��Ϣ����Ҫ����LIST����Ļ�Ӧ��Ϣ
	BOOL ParseNumAndSize(UINT &nNum,UINT &nSize,LPCTSTR lpszBuf,UINT &nEnd);
	// ��ȡ��Ӧ��Ϣ����GetResponse������ͬ��������ʵ�ʵĹ���
	BOOL ReadResponse(TCHAR *pChar,UINT nSize,BOOL bDouble);
	BOOL GetResponse(void);
	// ��ȡ���LIST����ķ�����Ϣ
	// ���ڶ�LIST����ķ�����Ϣ�����⣬�����õ����ĺ���
	BOOL ReadList(void);
	// ��STAT����ķ�����Ϣ��ԭ��ͬ��
	BOOL ReadState(void);
};

#endif // !defined(AFX_POP3_H__C7D744E6_CB2C_44AC_9E1D_71D0D9F1D1CC__INCLUDED_)
