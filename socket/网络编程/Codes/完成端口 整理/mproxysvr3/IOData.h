// IOData.h: interface for the IOData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IODATA_H__85562453_FA38_4CE0_BF03_9467360D910D__INCLUDED_)
#define AFX_IODATA_H__85562453_FA38_4CE0_BF03_9467360D910D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const int DATA_BUFSIZE	= 8192; 

typedef struct TagLPWSAOVERLAPPEDEX
{
	WSAOVERLAPPED Overlapped; //�ص��ṹ
	WSABUF     WSABuf;//socket���ݻ���
	char       Buffer[DATA_BUFSIZE];//wsaBufָ�����ʵ����λ��
	SOCKET	   hSocket;//socket ���
	SOCKET	   hSocketPair;//��ص�socket���
	LPVOID     pProxy3;//ָ��������
	TagLPWSAOVERLAPPEDEX *pPair;//ָ�����socket���ص���չ�ṹ
}WSAOVERLAPPEDEX, *LPWSAOVERLAPPEDEX;//�ص���չ�ṹ




#endif // !defined(AFX_IODATA_H__85562453_FA38_4CE0_BF03_9467360D910D__INCLUDED_)
