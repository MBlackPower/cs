#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <iostream>

#include "..\TestComObject1\TestComObject1_i.c"
#include "..\TestComObject1\TestComObject1.h"

DWORD WINAPI ThreadProc(LPVOID lpv)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	//HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if ( FAILED(hr) )
	{
		std::cout << "CoinitializeEx failed!" << std::endl;
		return 0;
	}

	IStream *pStream = (IStream*)lpv;
	
	ITestInterface1 *pTest = NULL;

	 hr = ::CoGetInterfaceAndReleaseStream(pStream,
											IID_ITestInterface1,
											(void**)&pTest);
	if ( FAILED(hr) )
	{
		std::cout << "CoGetInterfaceAndReleaseStream failed!" << std::endl; 
		return 0;
	}

	std::cout << "ThradProc's threadid is " << ::GetCurrentThreadId() << std::endl; //���ThradProc���߳�ID


	hr = pTest->TestFunc1();

	if ( FAILED(hr) )
	{
		std::cout << "TestFunc1 failed!" << std::endl;
		return 0;
	}
	

	pTest->Release();

	::CoUninitialize();

	return 0;
}
DWORD ApartMentMsgWaitForMultipleObject(HANDLE *hHandle,DWORD dwWaitCout, DWORD dwMilliseconds)
{
	
	BOOL bQuit = FALSE;
	DWORD dwRet;
	
	while(!bQuit)
	{
		int rc;
		rc = ::MsgWaitForMultipleObjects
			(
			dwWaitCout,          // ��Ҫ�ȴ��Ķ�������
			hHandle,			// ��������
			FALSE,				//�ȴ����еĶ���
			(DWORD)dwMilliseconds,  // �ȴ���ʱ��
			(DWORD)(QS_ALLINPUT | QS_ALLPOSTMESSAGE)     // �¼�����       
			);
		
		if( rc ==  WAIT_OBJECT_0 )
		{			
			dwRet = rc;	
			bQuit = TRUE;
			
		}
		else if( rc == WAIT_OBJECT_0 + dwWaitCout )			
		{
			MSG msg;
			
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage (&msg);
				DispatchMessage(&msg);
			}			
		} 
	}
	
	return dwRet;
}

int main(int argc, char* argv[])
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	//HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if ( FAILED(hr) )
	{
		std::cout << "CoinitializeEx failed!" << std::endl;
		return 0;
	}

	ITestInterface1 *pTest = NULL;

	hr = ::CoCreateInstance(CLSID_TestInterface1,
							0,
							CLSCTX_INPROC,
							IID_ITestInterface1,
							(void**)&pTest);

	if ( FAILED(hr) )
	{
		std::cout << "CoCreateInstance failed!" << std::endl;
		return 0;
	}

	std::cout << "main's threadid is " << ::GetCurrentThreadId() << std::endl;  //��ӡmain���߳�ID

	hr = pTest->TestFunc1();

	if ( FAILED(hr) )
	{
		std::cout << "TestFunc1 failed!" << std::endl;
		return 0;
	}

	IStream *pStream = NULL;

	hr = ::CoMarshalInterThreadInterfaceInStream(IID_ITestInterface1,
												pTest,
												&pStream);

	if ( FAILED(hr) )
	{
		std::cout << "CoMarshalInterThreadInterfaceInStream failed!" << std::endl;
		return 0;
	}


	DWORD threadID;
	HANDLE hThreads[1];
	hThreads[0] =   ::CreateThread(NULL,			//����һ������
									0,
									ThreadProc,
									(LPVOID)pStream,  //��pStream��Ϊһ�������������߳�
									0,
									&threadID);




//	::WaitForSingleObject(hThreads,INFINITE);	//�ȴ��߳̽���

	ApartMentMsgWaitForMultipleObject(hThreads,1,INFINITE);
	

	::CloseHandle(hThreads);				//�ر��߳̾��

	pTest->Release();

	::CoUninitialize();

	system("pause");

	
	return 0;
}