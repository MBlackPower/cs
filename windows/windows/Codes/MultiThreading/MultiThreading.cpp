// MultiThreading.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <windows.h>

int g_i = 10;  //һ��ȫ�ֱ���

CRITICAL_SECTION cs;  //һ���ٽ�������

DWORD WINAPI ThreadProc(LPVOID lpv)
{
//	EnterCriticalSection(&cs);  //�����ٽ���

	g_i += 10;
	std::cout <<"In the Thread " << ::GetCurrentThreadId() << ",the first g_i is "  << g_i << "!" <<std::endl;

//	::LeaveCriticalSection(&cs);

	Sleep(5000); //˯��

//	EnterCriticalSection(&cs);
	g_i += 10;

	std::cout <<"In the Thread " << ::GetCurrentThreadId() << ",the secend g_i is "  << g_i << "!" <<std::endl;

//	::LeaveCriticalSection(&cs);

	return 0;

}

int main(int argc, char* argv[])
{
	
	DWORD threadID[2];
	HANDLE hThreads[2];

	InitializeCriticalSection(&cs);

	for(int i = 0; i <= 1; i++ )			//���������߳�
		hThreads[i] = ::CreateThread(NULL,
									0,
									ThreadProc,
									NULL,
									0,
									&threadID[i]);


	WaitForMultipleObjects(2,hThreads,TRUE,INFINITE);   //�ȴ��߳̽���

	for(i = 0; i <= 1; i++ )
		::CloseHandle(hThreads[i]);				//�ر��߳̾��



	system("pause");

	return 0;
}