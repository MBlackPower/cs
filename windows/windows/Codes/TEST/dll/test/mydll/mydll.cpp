// mydll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "mydll.h"

#ifdef UNICODE
                     
	#define aMsgBox aMsgBoxW

#else

	#define aMsgBox aMsgBoxA

#endif

EXPORT BOOL CALLBACK aMsgBoxA(HWND, LPCSTR, LPCSTR);
EXPORT BOOL CALLBACK aMsgBoxW(HWND, LPCWSTR, LPCWSTR);

/////	ÿһ��DLL������һ����ڵ㣬DllMain��һ��ȱʡ����ں�����DllMain�����ʼ��(Initialization)
   //	�ͽ���(Termination)������ÿ��һ���µĽ��̻��߸ý��̵��µ��̷߳���DLLʱ�����߷���DLL��ÿһ
   //	�����̻����̲߳���ʹ��DLL���߽���ʱ���������DllMain��
   //	���ǣ�ʹ��TerminateProcess��TerminateThread�������̻����̣߳��������DllMain��

BOOL APIENTRY DllMain( HANDLE hModule,				///// �Ƕ�̬�ⱻ����ʱ����������һ��ָ���Լ��ľ��(ʵ���ϣ�����ָ��_DGROUP�ε�һ��ѡ���)��
                       DWORD  ul_reason_for_call,	///// ��һ��˵����̬�ⱻ��ԭ��ı�־�������̻��߳�װ���ж�ض�̬���ӿ��ʱ�򣬲���ϵͳ����
													   // ��ں�������˵����̬���ӿⱻ���õ�ԭ��
													   // ���еĿ���ֵΪ��
															// DLL_PROCESS_ATTACH: ���̱����ã�
															// DLL_THREAD_ATTACH: �̱߳����ã�
															// DLL_PROCESS_DETACH: ���̱�ֹͣ��
															// DLL_THREAD_DETACH: �̱߳�ֹͣ��
				   
                       LPVOID lpReserved )			///// ��һ����ϵͳ�������Ĳ�����
{
    return TRUE;
}

EXPORT BOOL CALLBACK MyMsgBox()
{
	return MessageBox(NULL, TEXT("MessageBox in DLL"), TEXT("USE DLL"), MB_ICONERROR);
}

//ʹ��ASCII�ַ���
EXPORT BOOL CALLBACK aMsgBoxA(HWND hwnd, LPCSTR lpText, LPCSTR lpCaption)
{
	return MessageBoxA(hwnd, lpText, lpCaption, NULL);
}

//ʹ��UNICODE�ַ���
EXPORT BOOL CALLBACK aMsgBoxW(HWND hwnd, LPCWSTR lpText, LPCWSTR lpCaption)
{
	return MessageBoxW(hwnd, lpText, lpCaption, NULL);
}