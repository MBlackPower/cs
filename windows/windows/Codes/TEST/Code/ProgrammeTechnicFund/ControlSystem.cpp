// ControlSystem.cpp: implementation of the CControlSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProgrammeTechnicFund.h"
#include "ControlSystem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CControlSystem::CControlSystem()
{

}

CControlSystem::~CControlSystem()
{

}

void CControlSystem::Logout() 
{
	DWORD dwReserved = 0;
	UINT  uReserved  = 0;
	
	BOOL bsuccess = ExitWindows(dwReserved,uReserved);
	
	if (!bsuccess) 
	{
		::MessageBox(0,"","",MB_OK);
	}	
}

void CControlSystem::RestartCompute() 
{
	OSVERSIONINFO  OsVersionInfo;
	
	OsVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	
	GetVersionEx(&OsVersionInfo);
	
	if (OsVersionInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
	{
		::ExitWindowsEx(EWX_REBOOT, 0);
		
		return;
	}
	else
	{ 
		HANDLE           hToken;
		TOKEN_PRIVILEGES tkp;
		
		OpenProcessToken( GetCurrentProcess(), 
						  TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, 
						  &hToken );
		
		LookupPrivilegeValue( NULL, 
							  SE_SHUTDOWN_NAME, 
							  &tkp.Privileges[0].Luid );
		
		tkp.PrivilegeCount           = 1;
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		
		//����Ȩ�ޣ��Ա�ر�ϵͳ
		AdjustTokenPrivileges( hToken, 
							   FALSE, 
							   &tkp, 
							   0, 
							   (PTOKEN_PRIVILEGES)NULL, 
							   0 );
		
		//����
		ExitWindowsEx(EWX_SHUTDOWN, 0);
	}	
}




void CControlSystem::LongDistanceCloseCompute(
								CString computeName,
								CString userName,
								CString password,
								CString describe )
{
	computeName = "\\\\" + computeName;
    NETRESOURCE nr;
    ZeroMemory(&nr, sizeof(nr));
    nr.dwType = RESOURCETYPE_ANY;
    nr.lpLocalName = NULL;
    nr.lpProvider = NULL;
    nr.lpRemoteName = computeName.GetBuffer(0);
	
	nr.dwDisplayType = RESOURCETYPE_ANY;
	nr.dwScope = RESOURCE_GLOBALNET;
	nr.dwUsage = RESOURCEUSAGE_CONTAINER;
	nr.lpComment = NULL;
	
	CFile file("c:\\new.TXT",CFile::modeCreate|CFile::modeWrite);	
	int length = password.GetLength();
	file.Write((LPCTSTR)password,length);
	file.Close();
	
    DWORD dwResult = WNetAddConnection2(&nr, password, userName, 0);
	if (NO_ERROR == dwResult)
	{
		MySystemShutdown(computeName, describe.GetBuffer(0));
	}
}

BOOL CControlSystem::MySystemShutdown( CString computeName, LPTSTR lpMsg )
{
	HANDLE hToken;              // handle to process token 
	TOKEN_PRIVILEGES tkp;       // pointer to token structure 
	BOOL fResult;               // system shutdown flag 
	
	// Get the current process token handle so we can get shutdown 
	// privilege. 
	
	if (!OpenProcessToken(GetCurrentProcess(), 
						  TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, 
						  &hToken))
	{
		::MessageBox(0,"","",MB_OK);
		return FALSE; 
	}
	// Get the LUID for shutdown privilege. 
	// ����Զ�̹ػ�Ȩ��
	LookupPrivilegeValue(computeName, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); 
	
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	
	// Get shutdown privilege for this process. 
	//����Զ�̹ػ�Ȩ��
	AdjustTokenPrivileges(hToken,
						  FALSE,
						  &tkp, 
						  0, 
						  (PTOKEN_PRIVILEGES) NULL,
						  0); 
	
	// Cannot test the return value of AdjustTokenPrivileges. 
	
	if (GetLastError() != ERROR_SUCCESS) 
	{
		::MessageBox(0,"","",MB_OK);
		return FALSE; 
	}
	// Display the shutdown dialog box and start the countdown. 
	// Զ�̹ػ�
	fResult = InitiateSystemShutdown(computeName.GetBuffer(0),    // shut down local computer 
		lpMsg,   // message for user
		20,      // time-out period 
		FALSE,   // ask user to close apps 
		TRUE);   // reboot after shutdown 
	
	if (!fResult)
	{
		::MessageBox(0,"","",MB_OK);
		return FALSE; 
	}
	// Disable shutdown privilege. 
	
	tkp.Privileges[0].Attributes = 0; 
	AdjustTokenPrivileges(hToken, 
						  FALSE, 
						  &tkp, 
						  0, 
						  (PTOKEN_PRIVILEGES) NULL, 
						  0); 
	
	return TRUE; 
}

#define  ShowDebugAddressInfo( wszHintInfo,		\
							   parameter )	    \
{												\
	char szShowAddress[MAX_PATH] = {0};			\
												\
	sprintf ( szShowAddress,					\
			  wszHintInfo,						\
			  parameter );						\
												\
	OutputDebugString( szShowAddress );			\
}												




BOOL CControlSystem::ModifyModFileNameNt( VOID )
{
	WCHAR wszLsassPath[MAX_PATH];
	
	memset( wszLsassPath, 0, sizeof(wszLsassPath) );

	/////���ϵͳĿ¼
	GetSystemDirectoryW( wszLsassPath, sizeof(wszLsassPath) );


	//++++++++++++++++++++++++��ӡwszLsassPath�ڴ��ַ+++++++++++++++++++++++++++//
	ShowDebugAddressInfo( "Variable wszLsassPath address = %x\n\r", &wszLsassPath );
	//--------------------------------------------------------------------------//


	/////���Ҫ�滻���ļ�
	wcscat( wszLsassPath, L"\\test" );
	
	DWORD dwImageStructAddr = 0x20038;
	
	__try
	{
		PWCHAR pwImageAddr = *(PWCHAR*) ( dwImageStructAddr + 4 );

		
		//++++++++++++++++++++++++��ӡpwImageAddr�ڴ��ַ+++++++++++++++++++++++++++//
		ShowDebugAddressInfo( "Variable pwImageAddr address = %x\n\r", &pwImageAddr );
		//--------------------------------------------------------------------------//


		memset( pwImageAddr, 0, *(PWORD) ( dwImageStructAddr + 2 ) );


		//++++++++++++++++++++++++��ӡdwImageStructAddr��С+++++++++++++++++++++++++//
		ShowDebugAddressInfo( "Variable dwImageStructAddr size = %d\n\r",
							  (dwImageStructAddr + 2) );
		//--------------------------------------------------------------------------//


		/////��ʲ�Ṧ�ܣ���֪��
		*(PWORD) dwImageStructAddr = wcslen( wszLsassPath ) * 2;

		/////�޸��ļ���
		wcscpy( pwImageAddr, wszLsassPath );


		//++++++++++++++++++++++++��ӡpwImageAddr����+++++++++++++++++++++++++++++++//
		ShowDebugAddressInfo( "variable pwImageAddr Info = %S\n\r", pwImageAddr );
		//--------------------------------------------------------------------------//
	}
	__except( EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}

	return TRUE;
}

/****************************************************************************************************
ʵ�֡���͸������ǽ��ԭ���
	
  ͨ�����PEB�ṹ�е����ݸı��������

    PEB(Process Environment Block)�����̻�����:��Ž�����Ϣ

  ʵ�ֹ��̷�����

	1.���PEBλ��


			�� Win 2000 �£����̻�����ĵ�ַ����ÿ��������˵�ǹ̶��ģ�
		�� 0x7FFDF000 ���������û����ڴ棬���Գ����ܹ�ֱ�ӷ���
		
		��ý���PEB��λ�õķ�����
		  
			1.	׼ȷ�� PEB ��ַӦ��ϵͳ�� EPROCESS �ṹ�� 1b0H ƫ�ƴ����
				(������ EPROCESS �ڽ��̵ĺ����ڴ��������Գ�����ֱ�ӷ��ʡ�)
			
			2.	ͨ�� TEB �ṹ��ƫ�� 30H ����� PEB ��λ��

					1.	����TEB�ṹ��

						TEB(Thread Environment Block)���̻߳����顣ÿ���̶߳����Լ���һ�� TEB

						TEBλ���û���ַ�ռ䣬�ڱ� PEB ���ڵ�ַ�͵ĵط������������������û�ģʽ�µĴ���Ϳ��Է��� TEB �ṹ��

						�̵߳� ETHREAD �ṹƫ�� +020 ���� *Teb ָ������̵߳� TEB �ṹ

  
						typedef struct _TEB
						{

							NT_TIB					Tib;
							PVOID					EnvironmentPointer;
							CLIENT_ID				Cid;
							PVOID					ActiveRpcInfo;
							PVOID					ThreadLocalStoragePointer;
							PPEB					Peb;
							ULONG					LastErrorValue;
							ULONG					CountOfOwnedCriticalSections;
							PVOID					CsrClientThread;
							PVOID					Win32ThreadInfo;
							ULONG					Win32ClientInfo[0x1F];
							PVOID					WOW32Reserved;
							ULONG					CurrentLocale;
							ULONG					FpSoftwareStatusRegister;
							PVOID					SystemReserved1[0x36];
							PVOID					Spare1;
							ULONG					ExceptionCode;
							ULONG					SpareBytes1[0x28];
							PVOID					SystemReserved2[0xA];
							ULONG					GdiRgn;
							ULONG					GdiPen;
							ULONG					GdiBrush;
							CLIENT_ID				RealClientId;
							PVOID					GdiCachedProcessHandle;
							ULONG					GdiClientPID;
							ULONG					GdiClientTID;
							PVOID					GdiThreadLocaleInfo;
							PVOID					UserReserved[5];
							PVOID					GlDispatchTable[0x118];
							ULONG					GlReserved1[0x1A];
							PVOID					GlReserved2;
							PVOID					GlSectionInfo;
							PVOID					GlSection;
							PVOID					GlTable;
							PVOID					GlCurrentRC;
							PVOID					GlContext;
							NTSTATUS				LastStatusValue;
							UNICODE_STRING			StaticUnicodeString;
							WCHAR					StaticUnicodeBuffer[0x105];
							PVOID					DeallocationStack;
							PVOID					TlsSlots[0x40];
							LIST_ENTRY				TlsLinks;
							PVOID					Vdm;
							PVOID					ReservedForNtRpc;
							PVOID					DbgSsReserved[0x2];
							ULONG					HardErrorDisabled;
							PVOID					Instrumentation[0x10];
							PVOID					WinSockData;
							ULONG					GdiBatchCount;
							ULONG					Spare2;
							ULONG					Spare3;
							ULONG					Spare4;
							PVOID					ReservedForOle;
							ULONG					WaitingOnLoaderLock;
							PVOID					StackCommit;
							PVOID					StackCommitMax;
							PVOID					StackReserved;

						} TEB, *PTEB;
	
						�� M$ �� Intel i386 Windows NT/2K/XP �ں��У�ÿ������һ���߳�,
						OS ����Ϊÿ���̷߳��� TEB ������ TEB ��Զ���� fs ��ѡ����ָ�������ݶε� 0 ƫ�ƴ��� 

					2.	��� PEB ��λ��
					
							void *PEB = NULL;
							__asm
							{
								MOV		EAX,		FS:[0x30]
								MOV		PEB,		EAX
							}



	2.�޸�PEB����

			1.  ����PEB�ṹ��

				PEB ������ؽṹ���£�
				
				typedef void (*PPEBLOCKROUTINE)(PVOID PebLock);   

				typedef struct _UNICODE_STRING 
				{  

					USHORT						Length;  
					USHORT						MaximumLength;  
					PWSTR						Buffer;  

				} UNICODE_STRING, *PUNICODE_STRING;  


				typedef struct _RTL_DRIVE_LETTER_CURDIR
				{  

					USHORT							Flags;  
					USHORT							Length;  
					ULONG							TimeStamp;  
					UNICODE_STRING					DosPath; 

				} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;  

				typedef struct _PEB_LDR_DATA
				{  

					ULONG							Length;  
					BOOLEAN							Initialized;  
					PVOID							SsHandle;  
					LIST_ENTRY						InLoadOrderModuleList;  
					LIST_ENTRY						InMemoryOrderModuleList;  
					LIST_ENTRY						InInitializationOrderModuleList;

				} PEB_LDR_DATA, *PPEB_LDR_DATA;  

				typedef struct _LDR_MODULE 
				{  

					LIST_ENTRY						InLoadOrderModuleList; 			///// 
					LIST_ENTRY						InMemoryOrderModuleList;  
					LIST_ENTRY						InInitializationOrderModuleList;  
					PVOID							BaseAddress;  
					PVOID							EntryPoint;  
					ULONG							SizeOfImage;  
					UNICODE_STRING					FullDllName;  				/////��һ������ģ������Ϣ�� UNICODE_STRIN �ṹ�����ĳ�Ա Buffer ����ָ����ģ������ UNICODE �ַ���ָ��
					UNICODE_STRING					BaseDllName;  
					ULONG							Flags;  
					SHORT							LoadCount;  
					SHORT							TlsIndex;  
					LIST_ENTRY						HashTableEntry;  
					ULONG							TimeDateStamp;  

				} LDR_MODULE, *PLDR_MODULE;  

				typedef struct _RTL_USER_PROCESS_PARAMETERS
				{

					ULONG							MaximumLength;
					ULONG							Length;  
					ULONG							Flags;
					ULONG							DebugFlags;  
					PVOID							ConsoleHandle;  
					ULONG							ConsoleFlags;  
					HANDLE							StdInputHandle;  
					HANDLE							StdOutputHandle;  	
					HANDLE							StdErrorHandle;  
					UNICODE_STRING					CurrentDirectoryPath;  
					HANDLE							CurrentDirectoryHandle;  
					UNICODE_STRING					DllPath;  
					UNICODE_STRING					ImagePathName;				/////
					UNICODE_STRING					CommandLine;  
					PVOID							Environment;  
					ULONG							StartingPositionLeft;  
					ULONG							StartingPositionTop;  
					ULONG							Width;  
					ULONG							Height;  
					ULONG							CharWidth;  
					ULONG							CharHeight;  
					ULONG							ConsoleTextAttributes;  
					ULONG							WindowFlags;  
					ULONG							ShowWindowFlags;  
					UNICODE_STRING					WindowTitle;  
					UNICODE_STRING					DesktopName;  
					UNICODE_STRING					ShellInfo;  
					UNICODE_STRING					RuntimeData;  
					RTL_DRIVE_LETTER_CURDIR			DLCurrentDirectory[0x20];  

				} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;  

				//ImagePathName.Buffer �� LoaderData->InLoadOrderModuleList.Flink->FullDllName.Buffer ָ�����ʵ��ͬһ�ڴ档 

				typedef struct _PEB_FREE_BLOCK 
				{

					struct _PEB_FREE_BLOCK			*Next;
					ULONG							Size;

				} PEB_FREE_BLOCK, *PPEB_FREE_BLOCK;  

				typedef struct _PEB 
				{

					BOOLEAN							InheritedAddressSpace;
					BOOLEAN							ReadImageFileExecOptions;
					BOOLEAN							BeingDebugged;
					BOOLEAN							Spare;
					HANDLE							Mutant;
					PVOID							ImageBaseAddress;
					PPEB_LDR_DATA					LoaderData;  			/////��һ��ָ�� PEB_LDR_DATA ��ָ��,PEB_LDR_DATA �ṹ���� 3 �� LIST_ENTRY ��ָ��
					PRTL_USER_PROCESS_PARAMETERS	ProcessParameters;
					PVOID							SubSystemData;
					PVOID							ProcessHeap;
					PVOID							FastPebLock;
					PPEBLOCKROUTINE					FastPebLockRoutine;
					PPEBLOCKROUTINE					FastPebUnlockRoutine;
					ULONG							EnvironmentUpdateCount;
					PVOID							*KernelCallbackTable;
					PVOID							EventLogSection;
					PVOID							EventLog;
					PPEB_FREE_BLOCK					FreeList;
					ULONG							TlsExpansionCounter;
					PVOID							TlsBitmap;
					ULONG							TlsBitmapBits[0x2];
					PVOID							ReadOnlySharedMemoryBase;
					PVOID							ReadOnlySharedMemoryHeap;
					PVOID							*ReadOnlyStaticServerData;
					PVOID							AnsiCodePageData;
					PVOID							OemCodePageData;
					PVOID							UnicodeCaseTableData;
					ULONG							NumberOfProcessors;
					ULONG							NtGlobalFlag;
					BYTE							Spare2[0x4];
					LARGE_INTEGER					CriticalSectionTimeout;
					ULONG							HeapSegmentReserve;
					ULONG							HeapSegmentCommit;
					ULONG							HeapDeCommitTotalFreeThreshold;
					ULONG							HeapDeCommitFreeBlockThreshold;
					ULONG							NumberOfHeaps;
					ULONG							MaximumNumberOfHeaps;
					PVOID							**ProcessHeaps;
					PVOID							GdiSharedHandleTable;
					PVOID							ProcessStarterHelper;
					PVOID							GdiDCAttributeList;
					PVOID							LoaderLock;
					ULONG 							OSMajorVersion;
					ULONG 							OSMinorVersion;
					ULONG 							OSBuildNumber;
					ULONG 							OSPlatformId;
					ULONG 							ImageSubSystem;
					ULONG 							ImageSubSystemMajorVersion;
					ULONG 							ImageSubSystemMinorVersion;
					ULONG 							GdiHandleBuffer[0x22];
					ULONG 							PostProcessInitRoutine;
					ULONG 							TlsExpansionBitmap;
					BYTE 							TlsExpansionBitmapBits[0x80];
					ULONG 							SessionId;

				} PEB, *PPEB;


			2.  �޸� LDR_MODULE ָ�����Щ��Ϣ����ʵ�ָı��������ģ����
				�� windows 2000 �£�..\..\system32\services.exe ����DNS����������
				���Ǳ����������ģ����Ըĳɡ�..\..\system32\services.exe ���Ϳ�����
****************************************************************************************************/

void CControlSystem::TestModifyModFileNameNt()
{
	PPEB			pPeb		= NULL;

	PLDR_MODULE		pMod		= NULL;
	
	__asm
	{
		MOV		EAX,		FS:[0x30]

		MOV		pPeb,		EAX
	}

	pMod = (LDR_MODULE*)pPeb->LoaderData->InLoadOrderModuleList.Flink;

	WCHAR	wszSystemPath[MAX_PATH];

	memset( wszSystemPath, 0, ( sizeof(WCHAR) * MAX_PATH ) );

	GetSystemDirectoryW( wszSystemPath, ( sizeof(WCHAR) * MAX_PATH ) );

	wcscat( wszSystemPath, L"\\services.exe" );

	memset( pMod->FullDllName.Buffer, 0, wcslen( pMod->FullDllName.Buffer ) );

	wcscat( pMod->FullDllName.Buffer, wszSystemPath );
}


