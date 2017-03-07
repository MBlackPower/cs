#include "MainWnd.h"
#include "WndProc.h"
#include "Server.h"
#include "Gdi.h"
#include "resource.h"

//���õ����ⲿȫ�ֱ���
extern	"C"	SOCKET	Listen;
extern	"C"	HWND	hServerWnd;
extern	"C"	BOOL	fDIBitmap;
extern	"C"	struct	GdiList	GdiStart;
extern	"C"	struct	GdiList	*pGdiNode;
extern  "C" UINT    gPort;
// �̱߳���
HANDLE	hThread;
DWORD	dwThreadId;

//��ΪIP��ַ��һ��ȫ����Ϣ���������ǰ�������ΪCMainWnd�ľ�̬����
BYTE	CMainWnd::m_ip[4];

CMainWnd::CMainWnd()
{

}

CMainWnd::~CMainWnd()
{
	// ɾ���Դ��������ָ��
	delete this;

	// �ͷ�ȫ�������DIB
	ClearDisplay(m_hWnd);
}

// ���ó���Instance
void CMainWnd::SetInstance(HINSTANCE hInst)
{
	m_hInst = hInst;
}

// ����WM_CREATE��Ϣ
BOOL CMainWnd::OnCreate(HWND hWnd,CREATESTRUCT FAR *lpCreateStruct)
{
	// ��ʾ������
	lpCreateStruct->cx=400;
	lpCreateStruct->cy=600;
	lpCreateStruct->x=100;
	lpCreateStruct->y=100;

	ShowWindow(hWnd,*(LPINT)lpCreateStruct->lpCreateParams);
	
	m_hWnd = hWnd;

	m_hMenu = GetMenu(m_hWnd);
	EnableMenuItem(m_hMenu,IDM_STARTSERVER,MF_BYCOMMAND|MF_ENABLED);
	EnableMenuItem(m_hMenu,IDM_STOPSERVER,MF_BYCOMMAND|MF_GRAYED);
	
	// Winsock��ʼ���ĵط�
	WSADATA				wsd;
	char				szString[255];
	char				name[20];

	// װ��Winsock2.2�汾
	if (WSAStartup(0x202,&wsd) != 0)
	{
		sprintf(szString,"Failed to load Winsock!");
		MessageBox(NULL,szString,"Remote Server",MB_OK);
		return 1;
	}
	//�õ�������IP��ַ
	GetLocalHostName(name);
	GetIpAddress(name,&m_ip[0],&m_ip[1],&m_ip[2],&m_ip[3]);
	return TRUE;
}

// ����WM_DESTORY��Ϣ
void CMainWnd::OnDestroy(HWND hWnd)
{
	// �رռ���Socket
	closesocket(Listen);
	// ���socket
	WSACleanup();
	// ���ͽ�����Ϣ������
	PostMessage(hWnd,WM_QUIT,(WPARAM)0,0L);
}

// ����WM_GETMINMAXINFO��Ϣ
void CMainWnd::OnGetMinMaxInfo(HWND hWnd,MINMAXINFO FAR* lpMinMaxInfo)
{
	RECT size;
	size.bottom=1000;
	size.top=100;
	size.left=100;
	size.right=1000;
	lpMinMaxInfo->ptMaxTrackSize.x = size.right-size.left;
	lpMinMaxInfo->ptMaxTrackSize.y = size.bottom-size.top;

	lpMinMaxInfo->ptMaxSize.x = size.right-size.left;
	lpMinMaxInfo->ptMaxSize.y = size.bottom-size.top;
}

// ����WM_KEYDOWN��Ϣ
void CMainWnd::OnKeyDown(HWND hWnd,UINT vk,BOOL fDown,int cRepeat,UINT flags)
{
	if (vk == VK_ESCAPE || vk == VK_F12)
		PostMessage(hWnd,WM_CLOSE,0,0);
}
//�Ի�����Ļص�����
BOOL CALLBACK SettingItemProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
	BOOL b;
	char name[15];
    switch (message) 
    { 
	  case WM_INITDIALOG:
		  sprintf(name,"%d.%d.%d.%d",CMainWnd::m_ip[0],CMainWnd::m_ip[1],CMainWnd::m_ip[2],CMainWnd::m_ip[3]);
   	     ::SetDlgItemInt(hwndDlg,IDC_EDIT1,gPort,false);
		 ::SetDlgItemText(hwndDlg,IDC_IP,name);
			return TRUE;
        case WM_COMMAND: 
            switch (LOWORD(wParam)) 
            { 
                case IDOK: 
                  gPort=::GetDlgItemInt(hwndDlg, IDC_EDIT1,&b, false);                     
                case IDCANCEL: 
                    EndDialog(hwndDlg, wParam); 
                    return TRUE; 
            } 
    } 
    return FALSE; 
} 
//����WM_COMMAND��Ϣ
void CMainWnd::OnCommand(HWND hWnd,int iId,HWND hWndCtl,UINT iCodeNotify)
{
	if (iId == IDM_EXIT)
	{
		//�ս��߳�
		if (hThread)
		{
			//�رռ�������
			closesocket(Listen);
			// ���socket
			WSACleanup();
		}
		// ��������
		PostQuitMessage(0);
	}
	else if (iId == IDM_STARTSERVER)
	{
       if (DialogBox(this->m_hInst, 
                     MAKEINTRESOURCE(IDD_DIALOG), 
                     hWnd, (DLGPROC)SettingItemProc)==IDOK)
	   {
		ShowWindow(hWnd,SW_MINIMIZE);

		RedrawWindow(hWnd,NULL,NULL,RDW_ERASE|RDW_INVALIDATE);

		// ����һ���µ��̣߳�LoadWinsock����Server.c�ж�����̺߳���
		hThread = CreateThread(NULL,0,LoadWinsock,(LPVOID)NULL,0,&dwThreadId);
		if (hThread == NULL)
			MessageBox(hWnd,"Socket�̴߳���ʧ��","Զ�̿��Ʒ�������",MB_ICONEXCLAMATION|MB_OK);
		else
		{
			InitDisplay(hWnd);
			hServerWnd = hWnd;
			EnableMenuItem(m_hMenu,IDM_STARTSERVER,MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem(m_hMenu,IDM_STOPSERVER,MF_BYCOMMAND|MF_ENABLED);
		}
	   }
	}
	else if (iId == IDM_STOPSERVER)
	{
		if(MessageBox(hWnd,"�������ر�Զ�̿��Ʒ���?","Զ�̿��Ʒ�������",MB_YESNO)==IDYES)
		{
			EnableMenuItem(m_hMenu,IDM_STARTSERVER,MF_BYCOMMAND|MF_ENABLED);
			EnableMenuItem(m_hMenu,IDM_STOPSERVER,MF_BYCOMMAND|MF_GRAYED);

			ClearDisplay(hWnd);

			// �ս��߳�
			if (hThread)
			{
				// �����������
				closesocket(Listen);
			}
		}
	}
	else if(iId==IDC_About)
	{
		MessageBox(hWnd,"2003-7-2����\r\nһ��Զ�̿��Ƶĳ���","Զ�̿��Ʒ�������",MB_OK);
	}
}
//��ñ��ؼ��������
int CMainWnd::GetLocalHostName(char* sHostName)	
{
	char szHostName[256];
	int nRetCode;
	nRetCode=gethostname(szHostName,sizeof(szHostName));
	if(nRetCode!=0)
	{
		//��������
		strcpy(sHostName,"û��ȡ��");
		return GetLastError();
	}
	strcpy(sHostName,szHostName);
	return 0;
}
//��ñ���IP
int CMainWnd::GetIpAddress(char *sHostName, char *sIpAddress)
{
	struct hostent FAR * lpHostEnt=gethostbyname(sHostName);
	if(lpHostEnt==NULL)
	{
		//��������
		sIpAddress=NULL;
		return GetLastError();
	}
	//��ȡIP
	LPSTR lpAddr=lpHostEnt->h_addr_list[0];
	if(lpAddr)
	{
		struct in_addr inAddr;
		memmove(&inAddr,lpAddr,4);
		//ת��Ϊ��׼��ʽ
		strcpy(sIpAddress,inet_ntoa(inAddr));
	}
	return 0;
}
//��ñ���IP
int CMainWnd::GetIpAddress(char *sHostName, BYTE *f0,BYTE *f1,BYTE *f2,BYTE *f3)
{
	struct hostent FAR * lpHostEnt=gethostbyname(sHostName);
	if(lpHostEnt==NULL)
	{
		//��������
		f0=f1=f2=f3=0;
		return GetLastError();
	}
	//��ȡIP
	LPSTR lpAddr=lpHostEnt->h_addr_list[0];
	if(lpAddr)
	{
		struct in_addr inAddr;
		memmove(&inAddr,lpAddr,4);
		*f0=inAddr.S_un.S_un_b.s_b1;
		*f1=inAddr.S_un.S_un_b.s_b2;
		*f2=inAddr.S_un.S_un_b.s_b3;
		*f3=inAddr.S_un.S_un_b.s_b4;
	}
	return 0;
}
