#include "windows.h"
//----------------------start  ------------

HANDLE g_thread_handle =NULL; // ��DLL�ڲ��̵߳ľ��
DWORD  g_thread_id =0;        // ��DLL�ڲ��̵߳�ID
HANDLE g_hEvent=NULL;         // Ӧ���¼��ľ��

DWORD WINAPI InSideDll_ThreadProc( LPVOID p )
{     
	/* ��ʾһЩ������
	�����---- operations.----������ӡ��Output�������ˣ�
	˵�����̺߳����ڱ�ִ���ˡ� */ 
	OutputDebugString("---- operations.---- \n"); 
	/*  InSideDll_ThreadProc�Ĳ�����ɺ�
	֪ͨ��g_hEvent���ȴ����߳�,���Լ��������ˡ�*/ 
	SetEvent(g_hEvent);
	return  1;
}

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	switch (ul_reason_for_call)   
	{
	case DLL_PROCESS_ATTACH:
		//DLL����ӳ�䵽���̵�ַ�ռ���
		{     
			// ��ֹ�߳̿���ã�
			DisableThreadLibraryCalls((HINSTANCE)hModule);
			// ����DLL���߳�ʹ�õ��¼�����
			g_hEvent = ::CreateEvent( NULL, FALSE, FALSE, "hello11");
			//����DLL���̶߳���
			g_thread_handle = ::CreateThread(NULL,0,  
				InSideDll_ThreadProc,(LPVOID)0,0,   &( g_thread_id) ) ;
			// �ȴ��մ������߳������ز���
			::WaitForSingleObject( g_hEvent, INFINITE );    
			// �����Դ
			::CloseHandle(g_thread_handle);
			g_thread_id = 0 ;
			g_thread_handle = NULL ;                  
			::CloseHandle(g_hEvent);
			g_hEvent=NULL;

		}
		break;
	case DLL_PROCESS_DETACH:
		// DLL���ڴӽ��̵�ַ�ռ���ж��
		break;
	}
	return TRUE;
}

//----------------------end  ------------

int main()
{
	return 0;
}
