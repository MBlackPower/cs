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

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved )
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