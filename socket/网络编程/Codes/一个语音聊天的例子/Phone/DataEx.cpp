// DataEx.cpp : implementation file
//

#include "stdafx.h"
#include "Phone.h"
#include "DataEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExchange

CExchange::CExchange()
{
	//��ʼ����˽������
	DataBlock = 0;
	MaxDataBlock = MAXWAVEBLOCK;
	CurrentBlock = 0;
}

CExchange::~CExchange()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CExchange, CAsyncSocket)
	//{{AFX_MSG_MAP(CExchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CExchange member functions

void CExchange::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	char buf[MAXWAVEBUFFER];
	CString Host;
	UINT Port;
	int RecieveLen;

	if(!m_Opened)
		//�Ѿ�ֹͣ����
		return;

	RecieveLen = this->ReceiveFrom(buf, MAXWAVEBUFFER, Host, Port);
	if(Host != RemoteHost)
	//�յ��Ǳ�����������
		return;

	if(DataBlock < MaxDataBlock)
	{//�ܲ������ݿ����Ҫ��
		//char* buff1 = new char[RecieveLen];//���벥�������ڴ�
		memcpy(WaveHdrOut[CurrentBlock].lpData, buf, RecieveLen);//������������

		//WaveHdrOut = new WAVEHDR;//����ṹ�ڴ�
		//Ϊ�ṹ��ֵ
		WaveHdrOut[CurrentBlock].dwBufferLength=RecieveLen;
		WaveHdrOut[CurrentBlock].dwFlags=0;
		WaveHdrOut[CurrentBlock].dwUser=0;
		//׼���������ڴ��
		waveOutPrepareHeader(hWaveOut, &WaveHdrOut[CurrentBlock], sizeof(WAVEHDR));
		//���Ÿ���������
		waveOutWrite(hWaveOut, &WaveHdrOut[CurrentBlock], sizeof(WAVEHDR));
		DataBlock++;
		CurrentBlock = (CurrentBlock+1) % MAXWAVEBLOCK;
		MaxDataBlock = MAXWAVEBLOCK;
	}else
	{//���ڴ����࣬��Ҫ���٣���2�����ڴ��
	 //�����ñ�֤�������Ϊ MAXWAVEBLOCK��������Ϊ2��
	 //�ڵ�ǰ�����£����������ʱΪ 0.5�루����������ʱ����
		MaxDataBlock = 3;
	}
	CAsyncSocket::OnReceive(nErrorCode);
}
