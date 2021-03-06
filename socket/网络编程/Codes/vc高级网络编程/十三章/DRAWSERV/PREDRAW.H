// predraw.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.


#include <atlbase.h>

// You may derive a class from CComModule and use it if you want
// to override something, but do not change the name of _Module

class CServiceModule : public CComModule
{
public:
	HRESULT RegisterServer(BOOL bRegTypeLib);
	HRESULT UnregisterServer();
	void Init(_ATL_OBJMAP_ENTRY* p, HINSTANCE h, UINT nServiceNameID);
   void Start();
	void ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
   void Handler(DWORD dwOpcode);
   void Run();
   BOOL IsInstalled();
   BOOL Install();
   BOOL Uninstall();
	LONG Unlock();
	void LogEvent(LPCTSTR pszFormat, ...);
   void SetServiceStatus(DWORD dwState);
	void SetupAsLocalServer();

//Implementation
private:
	static void WINAPI _ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
   static void WINAPI _Handler(DWORD dwOpcode);

// data members
public:
   TCHAR m_szServiceName[256];
   SERVICE_STATUS_HANDLE m_hServiceStatus;
   SERVICE_STATUS m_status;
	DWORD dwThreadID;
	BOOL m_bService;
};

extern CServiceModule _Module;

#include <atlcom.h>
