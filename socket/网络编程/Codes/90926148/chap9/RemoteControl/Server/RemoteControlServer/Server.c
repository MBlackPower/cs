//�������ˣ����ͱ������浽���ӵĿͻ���
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <winuser.h>
#include "Server.h"
#include "Command.h"
#include "Gdi.h"
#include "HuffCompress.h"
#include "RLE.h"
//Ĭ�϶˿�
#define DEFAULT_PORT        5150
#define SETFLAGS			XP1_GUARANTEED_DELIVERY|XP1_GUARANTEED_ORDER
#define NOTSETFLAGS			XP1_CONNECTIONLESS
#define	LPBMIH				LPBITMAPINFOHEADER

UINT    gPort  = DEFAULT_PORT;
int		nGridX = 8;
int		nGridY = 2;
DWORD	dwLen,dwCompress,dwSendLen;
int		iCompressionLevel = 10;
HWND	hServerWnd;
HDC		hDDC = NULL,hMemDC,hNullDC;
BOOL	fChange = FALSE;
SOCKET	Socket;
SOCKET	Listen;
int		iWidth,iHeight;
WORD	bmBitsPixel = 4;
// ָ��ȫ��λͼ
BOOL	fDIBitmap = FALSE;

// GDI����ṹ
struct	GdiList	GdiStart;
struct	GdiList	*pGdiNode;

// ����ṹ������LPARAM�����д�����Ϣ���ͻ����߳�
struct	myStruct
{
	SOCKET	Socket;
	HWND	hWnd;
};

int SelectProtocols(DWORD dwSetFlags,DWORD dwNotSetFlags,LPWSAPROTOCOL_INFO lpProtocolBuffer,LPDWORD lpdwBufferLength,WSAPROTOCOL_INFO *pProtocol);

//LoadWinsock����װ�غͳ�ʼ��Winsock���󶨱��ص�ַ����������socket���Ⱥ�ͻ�������
DWORD WINAPI LoadWinsock(LPVOID lpParam)
{
	// Э�����
	LPBYTE				pBuf;
	WSAPROTOCOL_INFO	Protocol;
	int					nRet;
	int					nZero = 0;

	int					iAddrSize;
	HANDLE				hThread;
	DWORD				dwThreadId;
	char				szClientIP[81];
	char				szString[255];
	struct	sockaddr_in	local,client;
	// ����ṹ������LPARAM�����д�����Ϣ���ͻ����߳�
	struct	myStruct	myStructure;

	// ΪЭ���ѡ�������Э��ı���������Ҫ�Ļ������Ĵ�С
	dwLen = 0;
	nRet = WSAEnumProtocols(NULL,NULL,&dwLen);
	if (nRet == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAENOBUFS)
			return 1;
	}
	pBuf = malloc(dwLen);
	// ΪWSASocketGet()�õ�Э��
	nRet = SelectProtocols(SETFLAGS,NOTSETFLAGS,(LPWSAPROTOCOL_INFO)pBuf,&dwLen,&Protocol);

	// �������ǵļ���socket
	Listen = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_IP,NULL,0,SOCK_STREAM);
	if (Listen == SOCKET_ERROR)
	{
		sprintf(szString,"socket() failed: %d",WSAGetLastError());
		MessageBox(NULL,szString,"Remote Server",MB_OK);
		return 1;
	}

	// ����server����Ϣ
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_family = AF_INET;
	local.sin_port = htons(gPort);

	// �󶨵�socket
	if (bind(Listen,(struct sockaddr *)&local,sizeof(local)) == SOCKET_ERROR)
	{
		sprintf(szString,"bind() failed: %d\n", WSAGetLastError());
		MessageBox(NULL,szString,"Remote Server",MB_OK);
		return 1;
	}

	//Ϊ�˼�СCPU�������ʣ���ֹ��socket�Ͻ����ݷ��͵����塣����SO_SNDBUFΪ0,
	//�Ӷ�ʹwinsockֱ�ӷ������ݵ��ͻ��ˣ������ǽ����ݻ���ŷ��͡�
	nZero = 0;
	setsockopt(Listen,SOL_SOCKET,SO_SNDBUF,(char *)&nZero,sizeof(nZero));
	//��ʼ����
	listen(Listen,SOMAXCONN);

	iAddrSize = sizeof(client);
	while (TRUE)
	{
		// ������ʽ�Ľ��տͻ��˵����ӣ�����Ϊ����һ���̺߳����������û�����е�����
		Socket = accept(Listen,(struct sockaddr *)&client,&iAddrSize);
		if (Socket != INVALID_SOCKET)
		{
			// ���ô����ͻ����̵߳���Ϣ�����ݽṹ
			myStructure.Socket = Socket;
			myStructure.hWnd = hServerWnd;
			//�ҳ��ͻ��˵�IP��ַ
			memset(szClientIP,'\0',sizeof(szClientIP));
			sprintf(szClientIP,"%s",inet_ntoa(client.sin_addr));
			// Ϊÿһ���ͻ��˴���һ���߳�
			hThread = CreateThread(NULL,0,ClientThread,(LPVOID)&myStructure,0,&dwThreadId);
			if (hThread)
			{
				//�ر��߳̾��
				CloseHandle(hThread);
			}
		}
		else
			return 1;
	}

	return 0;
}


//�ͻ����̺߳�������������Ⱥ�ӿͻ��˳����͹�������Ϣ��
//��������Ϣ��"REFRESH",��ô�����͵�ǰ������ͼƬ
//��������Ϣ��"DISCONNECT",��ô�������Ϳͻ��˵�����
//��������Ϣ��"WM_"��ͷ����ô���͸�����Ϣ���ͣ��ڷ�������ִ�и���Ϣ
DWORD WINAPI ClientThread(LPVOID lpParam)
{
	HWND	hWnd;
	SOCKET	MySocket;
	FD_SET	SocketSet;
	struct	timeval	timeout;
	char	szMessage[2049];
	DWORD	iRecv;
	struct	myStruct	*myStructure;
	DWORD	iLength;
	DWORD	iRet;
	int		iUpdates;

	// ��������
	myStructure = (struct myStruct *)lpParam;
	MySocket = myStructure->Socket;
	hWnd = myStructure->hWnd;

	// ���ó�ʱֵ
	timeout.tv_sec = 0;		// ��
	timeout.tv_usec = 0;	// ΢��

	// ����Socket����
	SocketSet.fd_count = 1;
	SocketSet.fd_array[1] = MySocket;

	// ��ѯsockets
	while(TRUE)
	{
		// �Ⱥ��͹���������ֱ����ʱ
		iRet = select(0,&SocketSet,NULL,NULL,&timeout);
		if (iRet != 0)
		{
 			//��ʼ������
			memset(szMessage,'\0',sizeof(szMessage));
			// ������ʽ����recv()
			iRecv = recv(MySocket,szMessage,2048,0);
			szMessage[iRecv] = '\0';

			CHECK_MSG:
			// �ǲ���"REFRESH"��Ϣ
			if (strncmp(szMessage,"REFRESH",7) == 0)
			{
				// �����ҷ�������ĸ��µ�����
				iUpdates = SendRegionDisplay(hServerWnd,MySocket);
			}
			
			// ���ӿͻ��˷��͹�����Windows ������Ϣ������һ�����Ĳ���
			else if (strncmp(szMessage,"WM_",3) == 0)
			{
				// �����ӿͻ��˷��͹�������Ϣ�����͵���������Ϣ����
				DispatchWMMessage(szMessage);

				// �����Ƿ�����Ϣ
				iLength = strlen(szMessage);
				if (iLength > 0)
					goto CHECK_MSG;
			}
			// ����Ƿ��ǲ�ѯ��Ϣ
			else if (strncmp(szMessage,"RESOLUTION",10) == 0)
			{
				SendResolution(MySocket);
			}
			// ����Ƿ���DISCONNECT��Ϣ
			else if (strncmp(szMessage,"DISCONNECT",10) == 0)
			{
				fChange = FALSE;
				fDIBitmap = FALSE;

				pGdiNode = GdiStart.pNext;
				while (pGdiNode)
				{
					free(pGdiNode->Gdi.pDIBitmap);
					free(pGdiNode->Gdi.pDIBChangeStart);
					pGdiNode->Gdi.fDIBitmap = FALSE;
					pGdiNode->Gdi.fChange = FALSE;
					pGdiNode = pGdiNode->pNext;
				}
				// ֹͣ��ѯ���൱�ڽ������߳�
				break;
			}
		}
	}
	closesocket(MySocket);
	return 0;
}

// �����ӿͻ��˷��͹�������Ϣ�����͵���������Ϣ����
void DispatchWMMessage(char *szString)
{
	//�����Ϣ
	struct {char *szWMMouseMsg;} 
	WMMouseMsg[] = {"WM_MM","WM_LBD","WM_LBU","WM_LBK",
					"WM_MBD","WM_MBU","WM_MBK",
					"WM_RBD","WM_RBU","WM_RBK"};

	// ������Ϣ
	struct {char *szWMKeyBdMsg;}
	WMKeyBdMsg[] = {"WM_KD","WM_KU"};

	// ͨ����Ϣ��ɫ��ģʽ����������ѹ����Ϣ
	struct {char *szMsg;}
	Msg[] = {"WM_COMP","WM_GRID","WM_CMOD"};

	int		nWMMouseMsg;
	int		nWMKeyBdMsg;
	int		nMsg;

	struct	CommandList	CommandStart;
	struct	CommandList	*pCommandNode;
	struct	CommandDS	Command;
	char	*pDest;
	int		iLoc,nChar;
	int		iLoop,iParms;
	char	szString2[2049];

	// �ֱ�õ���꣬���̣�ͨ����Ϣ����Ŀ
	nWMMouseMsg = (int)(sizeof(WMMouseMsg)/sizeof(WMMouseMsg[0]));
	nWMKeyBdMsg = (int)(sizeof(WMKeyBdMsg)/sizeof(WMKeyBdMsg[0]));
	nMsg = (int)(sizeof(Msg)/sizeof(Msg[0]));

	// ��ʼ��command����
	CommandStart.pNext = NULL;
	pCommandNode = &CommandStart;

	// ����command����ػ�����Ĳ���
	iParms = 0;
	while (pDest = strchr(szString,';'))
	{
		iLoc = pDest - szString;
		nChar = iLoc;
		memset(Command.szElement,'\0',sizeof(Command.szElement));
		strncpy(Command.szElement,szString,nChar);
		// ���͵�����ջ��
		pCommandNode = Add_Command(pCommandNode,Command);
		memset(szString2,'\0',sizeof(szString2));
		strcpy(szString2,&szString[iLoc + 1]);
		strcpy(szString,szString2);

		iParms++;
		if (iParms == 5) // ÿ������5������
			break;
	}

	// ��������
	pCommandNode = CommandStart.pNext;
	if (pCommandNode)
	{
		// �����Ϣ
		UINT	keyFlags;
		int		iMessage;
		int		fWMMouseMsg;
		double	iScaleX,iScaleY,iX,iY;
		DWORD	dwX,dwY;

		// ������Ϣ
		int		fWMKeyBdMsg;
		UINT	vk;
		int		fDown;
		int		cRepeat;
		UINT	flags;

		// �ж��Ƿ��������Ϣ
		fWMMouseMsg = FALSE;
		for (iLoop = 0;iLoop < nWMMouseMsg;iLoop++)
		{
			if (strcmp(pCommandNode->Command.szElement,WMMouseMsg[iLoop].szWMMouseMsg) == 0)
			{
				// ���������Ϣ�ı�־
				fWMMouseMsg = TRUE;
				// ����������Ϣ
				if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_MM\0") == 0)
					iMessage = 1;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_LBD\0") == 0)
					iMessage = 2;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_LBU\0") == 0)
					iMessage = 3;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_LBK\0") == 0)
					iMessage = 4;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_MBD\0") == 0)
					iMessage = 5;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_MBU\0") == 0)
					iMessage = 6;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_MBK\0") == 0)
					iMessage = 7;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_RBD\0") == 0)
					iMessage = 8;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_RBU\0") == 0)
					iMessage = 9;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_RBK\0") == 0)
					iMessage = 10;

				// �ƶ�������ջ����һ���ڵ㣬x����
				pCommandNode = pCommandNode->pNext;
				iX = atof(pCommandNode->Command.szElement);

				// �ƶ�������ջ����һ���ڵ㣬y����
				pCommandNode = pCommandNode->pNext;
				iY = atof(pCommandNode->Command.szElement);

				// �ƶ�������ջ����һ���ڵ㣬������
				pCommandNode = pCommandNode->pNext;
				keyFlags = atoi(pCommandNode->Command.szElement);

				// �˳�ѭ��
				break;
			}
		}

		// ����������Ϣ��������Ϣ���д���
		if (fWMMouseMsg)
		{
			// �õ�����ķ�Χ����
			iScaleX = 65535.0 / (iWidth - 1);
			iScaleY = 65535.0 / (iHeight - 1);
			// ��������б�������
			iX *= iScaleX;
			iY *= iScaleY;
			// ת����DWORDS
			dwX = (DWORD)iX;
			dwY = (DWORD)iY;

			// ���������Ϣ
			if (iMessage == 1) 
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE,dwX,dwY,0,0);
			}
			else if (iMessage == 2) 
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,dwX,dwY,0,0);
			}
			else if (iMessage == 3) 
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,dwX,dwY,0,0);
			}
			else if (iMessage == 4) 
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,dwX,dwY,0,0);
			}
			else if (iMessage == 5) 
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEDOWN,dwX,dwY,0,0);
			}
			else if (iMessage == 6) 
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEUP,dwX,dwY,0,0);
			}
			else if (iMessage == 7) 
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEDOWN,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEUP,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEDOWN,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEUP,dwX,dwY,0,0);
			}
			else if (iMessage == 8) 
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN,dwX,dwY,0,0);
			}
			else if (iMessage == 9) 
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP,dwX,dwY,0,0);
			}
			else if (iMessage == 10)
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP,dwX,dwY,0,0);
			}
		}
		else
		{
			// û�������Ϣ���ж��Ƿ��м�����Ϣ
			fWMKeyBdMsg = FALSE;
			for (iLoop = 0;iLoop < nWMKeyBdMsg;iLoop++)
			{
				if (strcmp(pCommandNode->Command.szElement,WMKeyBdMsg[iLoop].szWMKeyBdMsg) == 0)
				{
					// ���ü�����Ϣ��־
					fWMKeyBdMsg = TRUE;
					if (strcmp(WMKeyBdMsg[iLoop].szWMKeyBdMsg,"WM_KD\0") == 0)
						iMessage = 1;//���¼�
					else if (strcmp(WMKeyBdMsg[iLoop].szWMKeyBdMsg,"WM_KU\0") == 0)
						iMessage = 2;//�ɿ���

					// �ƶ��������������һ���ڵ㣬Virtural ����
					pCommandNode = pCommandNode->pNext;
					vk = atoi(pCommandNode->Command.szElement);

					//�ƶ��������������һ���ڵ㣬���¼���־
					pCommandNode = pCommandNode->pNext;
					fDown = atoi(pCommandNode->Command.szElement);

					// �ƶ��������������һ���ڵ㣬�����ظ���
					pCommandNode = pCommandNode->pNext;
					cRepeat = atoi(pCommandNode->Command.szElement);

					// �ƶ��������������һ���ڵ㣬��־λ
					pCommandNode = pCommandNode->pNext;
					flags = atoi(pCommandNode->Command.szElement);

					break;
				}
			}

			// ����м�����Ϣ�����������Ϣ
			if (fWMKeyBdMsg)
			{
				if (iMessage == 1) //ģ�ⰴ����Ϣ
				{
					keybd_event((BYTE)vk,(BYTE)vk,0,0);
				}
				else if (iMessage == 2) //ģ���ɿ�������Ϣ
				{
					keybd_event((BYTE)vk,(BYTE)vk,KEYEVENTF_KEYUP,0);
				}
			}
			else // ͨ����Ϣ
			{
				for (iLoop = 0;iLoop < nMsg;iLoop++)
				{
					if (strcmp(pCommandNode->Command.szElement,Msg[iLoop].szMsg) == 0)
					{
						if (strcmp(Msg[iLoop].szMsg,"WM_COMP\0") == 0)
						{
							// �ƶ��������������һ���ڵ㣬ѹ������
							pCommandNode = pCommandNode->pNext;
							iCompressionLevel = atoi(pCommandNode->Command.szElement);
						}
						else if (strcmp(Msg[iLoop].szMsg,"WM_GRID\0") == 0)
						{
							// �ƶ��������������һ���ڵ㣬x������
							pCommandNode = pCommandNode->pNext;
							nGridX = atoi(pCommandNode->Command.szElement);

							// �ƶ��������������һ���ڵ㣬y������
							pCommandNode = pCommandNode->pNext;
							nGridY = atoi(pCommandNode->Command.szElement);

							// �����ǰ����ʾ����
							ClearDisplay(hServerWnd);
							// ��ʼ���µ���ʾ����
							InitDisplay(hServerWnd);
						}
						else if (strcmp(Msg[iLoop].szMsg,"WM_CMOD\0") == 0)
						{
							// �ƶ��������������һ���ڵ㣬ÿ����Ļ����ֽ���
							pCommandNode = pCommandNode->pNext;
							bmBitsPixel = atoi(pCommandNode->Command.szElement);

							ClearDisplay(hServerWnd);
							InitDisplay(hServerWnd);
						}
					}
				}
			}
		}
	}
	// ����������
	Clear_Command(&CommandStart);
}

// ��ʼ����ʾ����
void InitDisplay(HWND hWnd)
{
	struct	GdiDS	Gdi;
	int		iWidthX,iHeightY,nGrid;
	int		iXGrid,iYGrid,iLoop;

	GdiStart.pNext = NULL;
	pGdiNode = &GdiStart;
	hDDC = CreateDC("DISPLAY",NULL,NULL,NULL);

	// �õ���Ļ�Ŀ�Ⱥ͸߶�
	iWidth = GetDeviceCaps(hDDC,HORZRES);
	iHeight = GetDeviceCaps(hDDC,VERTRES);

	// �ָ���Ļ��X��������
	if (nGridX > 0)
		iWidthX = iWidth/nGridX;
	else
		iWidthX = iWidth;

	// �ָ���Ļ��Y��������
	if (nGridY > 0)
		iHeightY = iHeight/nGridY;
	else
		iHeightY = iHeight;

	// Ϊ���񴴽������λͼ��Memory DC
	if ((nGridX > 0) && (nGridY > 0))
	{
		for (iXGrid = 0;iXGrid < nGridX;iXGrid++)
		{
			for (iYGrid = 0;iYGrid < nGridY;iYGrid++)
			{
				Gdi.fChange = FALSE;
				Gdi.fDIBitmap = FALSE;

				Gdi.iGridX = iXGrid;
				Gdi.iGridY = iYGrid;

				Gdi.iWidth1 = iXGrid * iWidthX;
				Gdi.iWidth2 = iXGrid * iWidthX + iWidthX;
				Gdi.iHeight1 = iYGrid * iHeightY;
				Gdi.iHeight2 = iYGrid * iHeightY + iHeightY;

				Gdi.hMemDC = CreateCompatibleDC(hDDC);
				Gdi.hDIBitmap = CreateCompatibleBitmap(hDDC,iWidthX,iHeightY);
				SelectObject(Gdi.hMemDC,Gdi.hDIBitmap);

				// �����������GDI��Ϣ
				pGdiNode = Add_Gdi(pGdiNode,Gdi);
			}
		}
	}
	else 
	{
		nGrid = max(nGridX,nGridY);
		for (iLoop = 0;iLoop < nGrid;iLoop++)
		{
			Gdi.fChange = FALSE;
			Gdi.fDIBitmap = FALSE;

			if (nGridX > 0)
			{
				Gdi.iGridX = iLoop;
				Gdi.iWidth1 = iLoop * iWidthX;
				Gdi.iWidth2 = iLoop * iWidthX + iWidthX;
			}
			else
			{
				Gdi.iGridX = 0;
				Gdi.iWidth1 = 0;
				Gdi.iWidth2 = iWidthX;
			}

			if (nGridY > 0)
			{
				Gdi.iGridY = iLoop;
				Gdi.iHeight1 = iLoop * iHeightY;
				Gdi.iHeight2 = iLoop * iHeightY + iHeightY;
			}
			else
			{
				Gdi.iGridY = 0;
				Gdi.iHeight1 = 0;
				Gdi.iHeight2 = iHeightY;
			}

			Gdi.hMemDC = CreateCompatibleDC(hDDC);
			Gdi.hDIBitmap = CreateCompatibleBitmap(hDDC,iWidthX,iHeightY);
			SelectObject(Gdi.hMemDC,Gdi.hDIBitmap);
			pGdiNode = Add_Gdi(pGdiNode,Gdi);
		}
	}
	hNullDC = GetDC(NULL);
}

// �����ʾ����
void ClearDisplay(HWND hWnd)
{
	DeleteDC(hDDC);
	DeleteDC(hNullDC);
	Clear_Gdi(&GdiStart);
}

//�õ��������ʾλͼ
int GetRegionDisplay(HWND hWnd)
{
	int		iWidth1,iWidth2,iHeight1,iHeight2;
	BOOL	bGotBits;
	DWORD	iLength;
	char	*pStartDIB;

	DWORD	dwLen1;
	DWORD	dwBitMapHeader1;
	char	*pDIBitmap1;
	char	*pDIB1;
	int		fChange1;
	char	*pDIBChange1;

	// �õ�����ľ�������
	iWidth1 = pGdiNode->Gdi.iWidth1;
	iWidth2 = pGdiNode->Gdi.iWidth2;
	iHeight1 = pGdiNode->Gdi.iHeight1;
	iHeight2 = pGdiNode->Gdi.iHeight2;

	BitBlt(pGdiNode->Gdi.hMemDC,0,0,iWidth2,iHeight2,hDDC,iWidth1,iHeight1,SRCCOPY);

	//��DDBת����DIB
	// �õ�����λͼ��Ϣ
	GetObject(pGdiNode->Gdi.hDIBitmap,sizeof(BITMAP),&(pGdiNode->Gdi.DIBitmap));
	// ������ɫģʽ
	pGdiNode->Gdi.DIBitmap.bmBitsPixel = bmBitsPixel;
	// ��ʼ��λͼ��Ϣͷ
	pGdiNode->Gdi.BMIH.biSize = sizeof(BITMAPINFOHEADER);
	pGdiNode->Gdi.BMIH.biWidth = pGdiNode->Gdi.DIBitmap.bmWidth;
	pGdiNode->Gdi.BMIH.biHeight = pGdiNode->Gdi.DIBitmap.bmHeight;
	pGdiNode->Gdi.BMIH.biPlanes = 1;
	pGdiNode->Gdi.BMIH.biBitCount = (WORD)pGdiNode->Gdi.DIBitmap.bmPlanes * (WORD)pGdiNode->Gdi.DIBitmap.bmBitsPixel;
	pGdiNode->Gdi.BMIH.biCompression = BI_RGB;
	pGdiNode->Gdi.BMIH.biSizeImage = 0;
	pGdiNode->Gdi.BMIH.biXPelsPerMeter = 0;
	pGdiNode->Gdi.BMIH.biYPelsPerMeter = 0;
	pGdiNode->Gdi.BMIH.biClrUsed = 0;
	pGdiNode->Gdi.BMIH.biClrImportant = 0;

	//�����������ɫ��
	pGdiNode->Gdi.nColors = 1 << pGdiNode->Gdi.BMIH.biBitCount;
	if (pGdiNode->Gdi.nColors > 256)
		pGdiNode->Gdi.nColors = 0; 
	// ����Ϊλͼ��Ϣͷ�Ͳ�ɫ������ڴ�����ĳߴ�
	pGdiNode->Gdi.dwLen = (DWORD)(sizeof(BITMAPINFOHEADER) + pGdiNode->Gdi.nColors * sizeof(RGBQUAD));

	if (!pGdiNode->Gdi.fDIBitmap)
	{
		pGdiNode->Gdi.pDIB = (char *)malloc(pGdiNode->Gdi.dwLen);
		pStartDIB = pGdiNode->Gdi.pDIB;
	}

	pGdiNode->Gdi.lpBMIH = (LPBMIH)pGdiNode->Gdi.pDIB;
	*(pGdiNode->Gdi.lpBMIH) = pGdiNode->Gdi.BMIH;
	GetDIBits(hNullDC,pGdiNode->Gdi.hDIBitmap,0L,(DWORD)pGdiNode->Gdi.BMIH.biHeight,(LPBYTE)NULL,(LPBITMAPINFO)pGdiNode->Gdi.lpBMIH,DIB_RGB_COLORS);

	// �Լ���ĳߴ���������λͼ��Ϣͷ
	pGdiNode->Gdi.BMIH = *(pGdiNode->Gdi.lpBMIH);
	// ����λͼ��Ϣͷ�Ĵ�С
	pGdiNode->Gdi.dwBitMapHeader = pGdiNode->Gdi.dwLen;
	pGdiNode->Gdi.dwLen += (DWORD)(pGdiNode->Gdi.BMIH.biSizeImage);
	if (!pGdiNode->Gdi.fDIBitmap)
	{
		pGdiNode->Gdi.pDIB = pStartDIB;
		pGdiNode->Gdi.pDIB = (char *)realloc(pGdiNode->Gdi.pDIB,pGdiNode->Gdi.dwLen);
	}

	pGdiNode->Gdi.lpBMIH = (LPBMIH)pGdiNode->Gdi.pDIB;
	bGotBits = GetDIBits(hNullDC,pGdiNode->Gdi.hDIBitmap,0L,(DWORD)pGdiNode->Gdi.BMIH.biHeight,(LPBYTE)pGdiNode->Gdi.lpBMIH + (pGdiNode->Gdi.BMIH.biSize + pGdiNode->Gdi.nColors * sizeof(RGBQUAD)),(LPBITMAPINFO)pGdiNode->Gdi.lpBMIH,DIB_RGB_COLORS);

	// �Ƚ�����DIBS֮ǰ��֮��ı仯
	if (pGdiNode->Gdi.fDIBitmap)
	{
		dwLen1 = pGdiNode->Gdi.dwLen;
		dwBitMapHeader1 = pGdiNode->Gdi.dwBitMapHeader;
		pDIBitmap1 = pGdiNode->Gdi.pDIBitmap;
		pDIB1 = pGdiNode->Gdi.pDIB;
		fChange1 = pGdiNode->Gdi.fChange;

		// ÿ��4���ֽڵıȽ�����λͼ,ע��Ҫ����λͼ��ͷ��
		__asm
		{
			MOV		ECX,dwLen1
			SUB		ECX,dwBitMapHeader1
			SHR		ECX,2 
			MOV		EDX,dwBitMapHeader1
			MOV		ESI,pDIBitmap1
			ADD		ESI,EDX
			MOV		EDI,pDIB1
			ADD		EDI,EDX
			REP		CMPSD
			JNZ		SetFlagRegion1
			MOV		fChange1,FALSE
			JMP		ExitRegion1
			SetFlagRegion1:
			MOV		fChange1,TRUE
			ExitRegion1:
		}

		//���ñ仯״̬
		pGdiNode->Gdi.fChange = fChange1;
		// Ϊ��������DIB�Ĳ����һ���µ�DIB
		if (pGdiNode->Gdi.fChange)
		{
			DWORD		iZeros = 0;
			iLength = (pGdiNode->Gdi.dwLen - pGdiNode->Gdi.dwBitMapHeader);
			pGdiNode->Gdi.pDIBChange = pGdiNode->Gdi.pDIBChangeStart;
			pDIBChange1 = pGdiNode->Gdi.pDIBChange;

			__asm
			{
				MOV		ECX,iLength 
				SHR		ECX,2 
				MOV		EDI,pDIBChange1
				MOV		ESI,pDIB1
				ADD		ESI,dwBitMapHeader1
				MOV		EDX,pDIBitmap1
				ADD		EDX,dwBitMapHeader1
				SubtractRegion:
				LODSD
				SUB		EAX,[EDX]
				ADD		EDX,4
				STOSD
				DEC		ECX
				JNZ		SubtractRegion
			}

			//������ȫ�������DIB
			memblast(pGdiNode->Gdi.pDIBitmap,pGdiNode->Gdi.pDIB,pGdiNode->Gdi.dwLen);
			// ����ѹ������
			pGdiNode->Gdi.dwCompress = pGdiNode->Gdi.dwLen - pGdiNode->Gdi.dwBitMapHeader;
			// �������ݵ���ʼλ
			pGdiNode->Gdi.iStartPos = pGdiNode->Gdi.dwBitMapHeader;
		}
	}
	else
	{
		iLength = (pGdiNode->Gdi.dwLen);
		pGdiNode->Gdi.pDIBitmap = (char *)malloc(iLength);
		pGdiNode->Gdi.pDIBChange = (char *)malloc(iLength);
		pGdiNode->Gdi.pDIBChangeStart = pGdiNode->Gdi.pDIBChange;
		memblast(pGdiNode->Gdi.pDIBitmap,pGdiNode->Gdi.pDIB,pGdiNode->Gdi.dwLen);
		memblast(pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.pDIB,pGdiNode->Gdi.dwLen);

		// ����Ҫ�ٷ����ڴ�
		pGdiNode->Gdi.fDIBitmap = TRUE;
		pGdiNode->Gdi.fChange = TRUE;

		pGdiNode->Gdi.dwCompress = pGdiNode->Gdi.dwLen;
		pGdiNode->Gdi.iStartPos = 0;
	}

	return pGdiNode->Gdi.fChange;
}

// ����Resolution���ͻ���
void SendResolution(SOCKET MySocket)
{
	char	szMessage[81];
	DWORD	iSent,iRecv;

	// ������Ļ���
	memset(szMessage,'\0',sizeof(szMessage));
	sprintf(szMessage,"%d",iWidth);
	iSent = Transmit(MySocket,szMessage,strlen(szMessage));

	// ����ȷ��
	memset(szMessage,'\0',sizeof(szMessage));
	iRecv = recv(MySocket,szMessage,81,0);
	szMessage[iRecv] = '\0';

	// ������Ļ�ĸ߶�
	memset(szMessage,'\0',sizeof(szMessage));
	sprintf(szMessage,"%d",iHeight);
	iSent = Transmit(MySocket,szMessage,strlen(szMessage));

	// ����ȷ��
	memset(szMessage,'\0',sizeof(szMessage));
	iRecv = recv(MySocket,szMessage,81,0);
	szMessage[iRecv] = '\0';
}

// ͨ��socket����������ʾλͼ
int SendRegionDisplay(HWND hWnd,SOCKET MySocket)
{
	char	szMessage[81];
	DWORD	iSent,iRecv;
	int		fSend = FALSE;
	int		iUpdates;
	WORD	wTreeSize;
	DWORD	dwByteTree[768];
	DWORD	dwCodes[514];
	DWORD	dwCompLen,dwLastCompLen;
	BOOL	fTransmit;
	char	*pTempDIB;
	DWORD	dwMinCompress;

	// ָ��GDI�������ʼλ
	iUpdates = 0;
	pGdiNode = GdiStart.pNext;
	while (pGdiNode)
	{
		//Ϊÿ������õ�������ʾ
		fSend = GetRegionDisplay(hWnd);
		// ������Ҫ���͵ı仯����ʾ�������Ŀ
		if (fSend)
			iUpdates++;
		// �ƶ�����һ���ڵ�
		pGdiNode = pGdiNode->pNext;
	}

	// ���͵��ͻ�����Ҫ���µ���ʾ�������Ŀ
	memset(szMessage,'\0',sizeof(szMessage));
	sprintf(szMessage,"%d",iUpdates);
	iSent = Transmit(MySocket,szMessage,strlen(szMessage));
	// ����ȷ��
	memset(szMessage,'\0',sizeof(szMessage));
	iRecv = recv(MySocket,szMessage,81,0);
	szMessage[iRecv] = '\0';

	if (iUpdates > 0)
	{
		// ָ��GDI�������ʼλ
		pGdiNode = GdiStart.pNext;
		while (pGdiNode)
		{
			// ������淢���˱仯������DIB
			if (pGdiNode->Gdi.fChange)
			{
				int		iCompressions = 1;
				//��ѹ��
				if (iCompressionLevel == 0) 
				{
					pGdiNode->Gdi.pDIBCompress = (char *)malloc(pGdiNode->Gdi.dwCompress);
					memblast(pGdiNode->Gdi.pDIBCompress,pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress);
					dwSendLen = pGdiNode->Gdi.dwCompress;
				}
				if (iCompressionLevel == 10) // �������������ѹ��
				{
					pGdiNode->Gdi.pDIBCompress = (char *)malloc(pGdiNode->Gdi.dwCompress + 1536);
					// ���ɻ������ֽ����ֵ�
					wTreeSize = HuffmanDictionary(pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress,&dwByteTree[0],&dwCodes[0]);
					// ʹ�û�����ѹ������ѹ��ͼƬ
					dwSendLen = HuffmanCompress(pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress,wTreeSize,&dwByteTree[0],&dwCodes[0],pGdiNode->Gdi.pDIBCompress);
				}
				else if (iCompressionLevel == 11) // ��������ѹ������
				{
					dwMinCompress = pGdiNode->Gdi.dwCompress + 1536;
					pGdiNode->Gdi.pDIBCompress = (char *)malloc(dwMinCompress);
					pTempDIB = (char *)malloc(pGdiNode->Gdi.dwCompress);
					memblast(pTempDIB,pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress);
					iCompressions = 0;
					dwCompLen = pGdiNode->Gdi.dwCompress;
					dwLastCompLen = dwCompLen;
					for (;;)
					{
						// ���ɻ������ֽ����ֵ�
						wTreeSize = HuffmanDictionary(pTempDIB,pGdiNode->Gdi.dwCompress,&dwByteTree[0],&dwCodes[0]);
						// ����ѹ������
						dwCompLen = HuffmanCountCompress(pTempDIB,dwCompLen,wTreeSize,&dwCodes[0]);
						if (dwCompLen < dwMinCompress)
						{
							dwSendLen = HuffmanCompress(pTempDIB,dwLastCompLen,wTreeSize,&dwByteTree[0],&dwCodes[0],pGdiNode->Gdi.pDIBCompress);
							memblast(pTempDIB,pGdiNode->Gdi.pDIBCompress,dwSendLen);
							dwMinCompress = dwSendLen;
							dwLastCompLen = dwCompLen;
							iCompressions++;
						}
						else
							break;
					}
					free(pTempDIB);
				}
				else if (iCompressionLevel == 12) // Run Length����
				{
					//Ϊ����������ѹ���ռ�
					pGdiNode->Gdi.pDIBCompress = (char *)malloc(pGdiNode->Gdi.dwCompress * 3 + 4);
					// Run Length����ͼ��
					dwSendLen = RunLengthEncode(pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress,pGdiNode->Gdi.pDIBCompress);
				}
				else if (iCompressionLevel == 13) // Run Length&Huffman����
				{
					pTempDIB = (char *)malloc(pGdiNode->Gdi.dwCompress * 3 + 4);
					pGdiNode->Gdi.pDIBCompress = (char *)malloc(pGdiNode->Gdi.dwCompress * 3 + 4);
					// Run Length ����ͼ��
					dwCompLen = RunLengthEncode(pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress,pTempDIB);
					// ���ɻ������ֽ������ֵ�
					wTreeSize = HuffmanDictionary(pTempDIB,dwCompLen,&dwByteTree[0],&dwCodes[0]);
					// ʹ�û�����ѹ��Run Lenght�����ͼ��
					dwSendLen = HuffmanCompress(pTempDIB,dwCompLen,wTreeSize,&dwByteTree[0],&dwCodes[0],pGdiNode->Gdi.pDIBCompress);
					// �ͷ���ʱ��DIB
					free(pTempDIB);
				}

				// ����λͼ������Ϣ
				memset(szMessage,'\0',sizeof(szMessage));
				sprintf(szMessage,"%d;%d;%d;%ld;%ld;%ld;",
					iCompressions,
					pGdiNode->Gdi.iGridX,pGdiNode->Gdi.iGridY,
					pGdiNode->Gdi.iStartPos,
					pGdiNode->Gdi.dwCompress,dwSendLen);
				// ���Ϳ�����Ϣ
				iSent = Transmit(MySocket,szMessage,strlen(szMessage));

				// ����ȷ��
				memset(szMessage,'\0',sizeof(szMessage));
				iRecv = recv(MySocket,szMessage,81,0);
				szMessage[iRecv] = '\0';

				// ����ѹ����DIB
				fTransmit = Transmit(MySocket,pGdiNode->Gdi.pDIBCompress,dwSendLen);
				// �ͷ�ѹ����DIB
				free(pGdiNode->Gdi.pDIBCompress);
				// ����ȷ��
				memset(szMessage,'\0',sizeof(szMessage));
				iRecv = recv(MySocket,szMessage,81,0);
				szMessage[iRecv] = '\0';
			}
			pGdiNode = pGdiNode->pNext;
		}
	}
	return iUpdates;
}

//�������ݵ��ͻ���
BOOL Transmit(SOCKET MySocket,char *pData,DWORD dwLength)
{
	WSAOVERLAPPED	olSend;
	WSAEVENT	gheventOlSock;
	WSAEVENT	eventArray[2];
	WSABUF		buffSend;
	DWORD		dwRet,dwNumBytes,dwFlags;
	int			nWSAError;
	char		szError[81];

	// Ϊ������ɴ���һ���ź��¼�
	gheventOlSock = WSACreateEvent();
	eventArray[0] = gheventOlSock;

	// ��ʼ���ص����͵Ľṹ
	ZeroMemory(&olSend, sizeof(WSAOVERLAPPED));
	// Ϊ�����ص��ṹ����һ���ź�ʱ��
	olSend.hEvent= gheventOlSock;
	buffSend.len = dwLength;
	buffSend.buf = pData;
	// �������ͣ�ֱ��dwSendLen���ֽڱ��������
	while (TRUE)
	{
		if ((dwRet = WSASend(MySocket,&buffSend,1,&dwNumBytes,0,&olSend,NULL)) == SOCKET_ERROR)
		{
			nWSAError= WSAGetLastError();
			if (nWSAError != ERROR_IO_PENDING)
			{
				sprintf(szError,"WSASend failed with error %d\n",nWSAError);
				MessageBox(NULL,szError,"Server",MB_OK);
			}
		}
	
		if (WSAWaitForMultipleEvents(1,eventArray,FALSE,WSA_INFINITE,FALSE) == WSA_WAIT_FAILED)
		{
			sprintf(szError,"WSAWaitForMultipleEvents failed %d\n", WSAGetLastError());
			MessageBox(NULL,szError,"Server",MB_OK);
		} 
		// ����gheventOlSock
		WSAResetEvent(eventArray[0]);
		if (WSAGetOverlappedResult(MySocket,&olSend,&dwNumBytes,FALSE,&dwFlags) == FALSE)
		{
			sprintf(szError,"WSAGetOverlappedResult failed with error %d\n", WSAGetLastError());
			MessageBox(NULL,szError,"Server",MB_OK);
		}
		buffSend.len -= dwNumBytes;
		if (buffSend.len == 0) 
			break;
		else 
			buffSend.buf += dwNumBytes;
	}

	// �ر��ź��¼�
	WSACloseEvent(gheventOlSock);
	return TRUE;
}

//���ر�����װ�����е���XP1_GUARANTEED_DELIVERY and XP1_GUARANTEED_ORDER��־��Э���Э����
int SelectProtocols(DWORD dwSetFlags,DWORD dwNotSetFlags,LPWSAPROTOCOL_INFO lpProtocolBuffer,LPDWORD lpdwBufferLength,WSAPROTOCOL_INFO *pProtocol)
{
	LPBYTE				pBuf;
	LPWSAPROTOCOL_INFO	pInfo;
	DWORD				dwNeededLen;
	LPWSAPROTOCOL_INFO	pRetInfo;
	DWORD				dwRetLen;
	int					nCount;
	int					nMatchCount;
	int					nRet;

	// ������Ҫ�Ļ�������С
	dwNeededLen = 0;
	nRet = WSAEnumProtocols(NULL, NULL, &dwNeededLen);
	if (nRet == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAENOBUFS)
			return SOCKET_ERROR;
	}
	// �����С
	pBuf = malloc(dwNeededLen);
	if (pBuf == NULL)
	{
		WSASetLastError(WSAENOBUFS);
		return SOCKET_ERROR;
	}

	nRet = WSAEnumProtocols(NULL,(LPWSAPROTOCOL_INFO)pBuf,&dwNeededLen);
	if (nRet == SOCKET_ERROR)
	{
		free(pBuf);
		return SOCKET_ERROR;
	}

	#define REJECTSET(f) \
	    ((dwSetFlags & f) && !(pInfo->dwServiceFlags1 & f))
	#define REJECTNOTSET(f) \
	    ((dwNotSetFlags &f) && (pInfo->dwServiceFlags1 & f))
	#define REJECTEDBY(f) (REJECTSET(f) || REJECTNOTSET(f))

	pInfo = (LPWSAPROTOCOL_INFO)pBuf;	
	pRetInfo = lpProtocolBuffer;
	dwRetLen = 0;
	nMatchCount = 0;
	for(nCount = 0; nCount < nRet; nCount++)
	{
		while(1)
		{
			if (REJECTEDBY(XP1_CONNECTIONLESS))
				break;
			if (REJECTEDBY(XP1_GUARANTEED_DELIVERY))
				break;
			if (REJECTEDBY(XP1_GUARANTEED_ORDER))
				break;
			if (REJECTEDBY(XP1_MESSAGE_ORIENTED))
				break;
			if (REJECTEDBY(XP1_PSEUDO_STREAM))
				break;
			if (REJECTEDBY(XP1_GRACEFUL_CLOSE))
				break;
			if (REJECTEDBY(XP1_EXPEDITED_DATA))
				break;
			if (REJECTEDBY(XP1_CONNECT_DATA))
				break;
			if (REJECTEDBY(XP1_DISCONNECT_DATA))
				break;
			if (REJECTEDBY(XP1_SUPPORT_BROADCAST)) 
				break;
			if (REJECTEDBY(XP1_SUPPORT_MULTIPOINT))
				break;
			if (REJECTEDBY(XP1_MULTIPOINT_DATA_PLANE))
				break;
			if (REJECTEDBY(XP1_QOS_SUPPORTED))
				break;
			if (REJECTEDBY(XP1_UNI_SEND))
				break;
			if (REJECTEDBY(XP1_UNI_RECV))
				break;
			if (REJECTEDBY(XP1_IFS_HANDLES))
				break;
			if (REJECTEDBY(XP1_PARTIAL_MESSAGE))
				break;

			dwRetLen += sizeof(WSAPROTOCOL_INFO);

			if (dwRetLen > *lpdwBufferLength)
			{
				WSASetLastError(WSAENOBUFS);
				*lpdwBufferLength = dwNeededLen;
				free(pBuf);
				return SOCKET_ERROR;
			}
			nMatchCount++;
			// ����Э�鵽�����ߵ�buffer��
			memblast(pRetInfo,pInfo,sizeof(WSAPROTOCOL_INFO));
			if (strcmp(pInfo->szProtocol,"MSAFD Tcpip [TCP/IP]") == 0)
				memblast(pProtocol,pInfo,sizeof(WSAPROTOCOL_INFO));
			pRetInfo++;
			break;
		}
		pInfo++;
	}
	free(pBuf);
	*lpdwBufferLength = dwRetLen;
	return(nMatchCount);
}

void memblast(void* dest,void* src,DWORD count)
{
	DWORD	iCount;

	__asm
	{
		MOV		ECX,count
		SHR		ECX,2
		SHL		ECX,2
		MOV		iCount,ECX

		MOV		ESI,src
		MOV		EDI,dest
		MOV		ECX,iCount
		SHR		ECX,2	
		REP		MOVSD	

		MOV		ECX,count
		MOV		EAX,iCount
		SUB		ECX,EAX

		JZ		Exit

		MOV		ESI,src	
		ADD		ESI,EAX	
		MOV		EDI,dest	
		ADD		EDI,EAX		
		REP		MOVSB		
		Exit:
	}
}
/*
int GetLocalHostName(char* sHostName)	//��ñ��ؼ��������
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
int GetIpAddress(char *sHostName, BYTE *f0,BYTE *f1,BYTE *f2,BYTE *f3)//��ñ���IP
{
	struct hostent FAR * lpHostEnt=gethostbyname(sHostName);
	if(lpHostEnt==NULL)
	{
		//��������
		f0=f1=f2=f3=0;
		return GetLastError();
	}
	//��ȡIP
	if(lpHostEnt->h_addr_list[0])
	{
		struct in_addr inAddr;
		memmove(&inAddr,lpHostEnt->h_addr_list[0],4);
		*f0=inAddr.S_un.S_un_b.s_b1;
		*f1=inAddr.S_un.S_un_b.s_b2;
		*f2=inAddr.S_un.S_un_b.s_b3;
		*f3=inAddr.S_un.S_un_b.s_b4;
	}
	return 0;
}
*/