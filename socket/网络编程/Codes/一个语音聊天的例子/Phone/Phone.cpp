// Phone.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Phone.h"

#include "DataEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CPhoneApp

BEGIN_MESSAGE_MAP(CPhoneApp, CWinApp)
	//{{AFX_MSG_MAP(CPhoneApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhoneApp construction

CPhoneApp::CPhoneApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CPhoneApp object

CPhoneApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPhoneApp initialization

BOOL CPhoneApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	return TRUE;
}

//
//�Զ������
//
//ȫ�ֱ���
CString RemoteHost;
long RemotePort;
HWAVEOUT hWaveOut;
bool m_Opened;
WAVEHDR WaveHdrOut[MAXWAVEBLOCK];
//�ֲ�����
static WAVEHDR WaveHdrIn[MAXWAVEBLOCK];
static char WaveOutBuffer[MAXWAVEBLOCK][MAXWAVEBUFFER];//���沥���������ڴ��
static char WaveInBuffer[MAXWAVEBLOCK][MAXWAVEBUFFER];//��¼¼���������ڴ��
static HWAVEIN hWaveIn;
static CExchange* m_pChange;


static void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, WORD dwInstance,
						 WAVEHDR* dwParam1, DWORD dwParam2)
{
	long result;
	char buffer[MAXWAVEBUFFER];
	long buf_len;

	switch(uMsg)
	{//�жϻص�����
	case WIM_OPEN:
		//¼���豸������ʱ���������¼�
		//MessageBox(NULL,"Open success", "��ʾ", MB_OK);
		break;
	case WIM_CLOSE:
		//¼���豸�����ر�ʱ���������¼�
		//MessageBox(NULL,"Close success", "��ʾ", MB_OK);
		break;
	case WIM_DATA:
		//¼���豸��������ʱ���������¼�
		if(!waveInUnprepareHeader(hwi, dwParam1,sizeof(WAVEHDR)))
		{//�����ͷ��ڴ档�е������Ȼ�������ݣ��������ͷ��ڴ棬
		 //��ʹ��ͬһ��WAVEHDR���Ӷ���ڴ��ʱ��������������
			memcpy(buffer, dwParam1->lpData , MAXWAVEBUFFER);//���Ʒ�������
			buf_len = dwParam1->dwBytesRecorded;//��¼¼�����ݳ���
			dwParam1->dwUser=0;//�ָ�����
			dwParam1->dwBufferLength=MAXWAVEBUFFER;
			dwParam1->dwFlags=0;
			if(m_Opened)
			{//¼�����ڼ���
				result=waveInPrepareHeader(hwi,dwParam1,sizeof(WAVEHDR));
 				result=waveInAddBuffer(hwi,dwParam1,sizeof(WAVEHDR));
			}
		}
		if(buf_len > 0 && buf_len <= MAXWAVEBUFFER)
		{//��¼������
			//����¼������
			m_pChange->SendTo(buffer, buf_len, RemotePort, LPCTSTR(RemoteHost));
		}
		break;
	}
};


void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, WORD dwInstance,
						 WAVEHDR* dwParam1, DWORD dwParam2)
{
	switch(uMsg)
	{//�жϻص�����
	case WOM_OPEN:
		//�����豸������ʱ���������¼�
		//MessageBox(NULL,"Open success",NULL,MB_OK);
		break;
	case WOM_CLOSE:
		//�����豸�����ر�ʱ���������¼�
		//MessageBox(NULL,"Close success",NULL,MB_OK);
		break;
	case WOM_DONE:
		//�ڴ沥�����ʱ���������¼�
		if(!waveOutUnprepareHeader(hwo, dwParam1, sizeof(WAVEHDR)))
		{
			//delete dwParam1->lpData;//ɾ�����������ڴ�
			//delete dwParam1;//ɾ���ṹ�����ڴ�
			m_pChange->DelDataBlock();//�����ڴ���������
		}
		break;
	}
};

long _stdcall StartPhone(char* HostAddress, long lPort, long rPort) 
{
	// TODO: Add your dispatch handler code here

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	long sta;
	int i;
	void _stdcall ClosePhone();

	if(m_Opened)
	//�豸����ʹ��
		return -1;
	m_Opened = true;

	if(!strlen(HostAddress))
	//��������ַ
		return -2;
	else
	{
		RemoteHost = HostAddress;//����������ַ
		RemotePort = rPort;//���������˿ں�
	}

	m_pChange = new CExchange;//����Socket�࣬UDP�׽���
	if(!m_pChange->Create(lPort, SOCK_DGRAM, FD_READ|FD_WRITE|FD_OOB))
	{//�׽��ִ���ʧ��
		return -3;
	}

	WAVEFORMATEX waveFormatEx;
		waveFormatEx.cbSize=0;
		waveFormatEx.nAvgBytesPerSec=16000;
		waveFormatEx.nBlockAlign=2;
		waveFormatEx.nChannels=1;
		waveFormatEx.nSamplesPerSec=8000;
		waveFormatEx.wBitsPerSample=16;
		waveFormatEx.wFormatTag=WAVE_FORMAT_PCM;

	//�򿪲����豸����ʼ����
	for(i=0;i < MAXWAVEBLOCK; i++)
		WaveHdrOut[i].lpData=WaveOutBuffer[i];//���ò��������ڴ���
	hWaveOut = NULL;
	if(waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormatEx, (unsigned long)waveOutProc, 0L, CALLBACK_FUNCTION)) 
	{//�����豸��ʧ�ܣ������豸����������ռ��
		ClosePhone();
		return 1;
	}

	hWaveIn = NULL;
	if(sta=waveInOpen(&hWaveIn, WAVE_MAPPER, &waveFormatEx, (unsigned long)waveInProc, 1L, CALLBACK_FUNCTION)) 
	{//¼���豸��ʧ�ܣ�����������֧��ȫ˫����
		ClosePhone();
		return 2;
	}
	
	for(i=0;i < MAXWAVEBLOCK; i++)
	{//����¼���ڴ�
		WaveHdrIn[i].lpData=WaveInBuffer[i];
		WaveHdrIn[i].dwBufferLength=MAXWAVEBUFFER;
		WaveHdrIn[i].dwFlags=0;
		WaveHdrIn[i].dwUser=0;
		if(waveInPrepareHeader(hWaveIn, &WaveHdrIn[i], sizeof(WAVEHDR)))
		{//�޷��������ڴ�
			ClosePhone();
			return 3;
		}; 
		if(waveInAddBuffer(hWaveIn,&WaveHdrIn[i],sizeof(WAVEHDR)))
		{//�޷����Ӹ��ڴ�
			ClosePhone();
			return 4;
		}
	}
	if(waveInStart(hWaveIn))
	{//�޷���ʼ¼��
		ClosePhone();
		return 5;
	}

	return 0;
}

void _stdcall ClosePhone() 
{
	// TODO: Add your dispatch handler code here

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Opened)//�绰�Ѿ��ر�
		return;
	m_Opened = false;//�رյ绰ʹ�ñ�־

	if(hWaveIn){
		waveInStop(hWaveIn);//ֹͣ¼��
		waveInReset(hWaveIn);//���¼������
		waveInClose(hWaveIn);//�ر�¼���豸
		hWaveIn = NULL;
	}

	if(m_pChange)
		m_pChange->ShutDown();//ֹͣ��������

	if(hWaveOut)
	{
		waveOutReset(hWaveOut);//��������������
		waveOutClose(hWaveOut);//����������豸
		hWaveOut = NULL;
	}

	if(m_pChange)
	{
		BYTE Buffer[50];
		while (m_pChange->Receive(Buffer,50) > 0);//���δ��������
		delete m_pChange;//ɾ���������
		m_pChange = NULL;
	}
}
