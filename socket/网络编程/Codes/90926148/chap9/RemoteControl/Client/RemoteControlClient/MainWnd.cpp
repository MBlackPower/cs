#include "MainWnd.h"
#include "WndProc.h"
#include "client.h"
#include "ServerIP.h"
#include "Compression.h"
#include "ColorMode.h"
#include "GridSpacing.h"
#include "Gdi.h"
#include "resource.h"

#define	DISCONNECT_MSG		"DISCONNECT"

// ������IP�����һ��ָ��
extern	CServerIP				*pServerIP;

// ѹ�����һ��ָ��
extern	CCompression			*pCompression;

// ����ռ����һ��ָ��
extern	CGridSpacing			*pGridSpacing;

// ��ɫģʽ���һ��ָ��
extern	CColorMode				*pColorMode;

// λͼ��socket����
extern	"C" char				*pDIBitmap;
extern	"C" BOOL				fDIBitmap;
extern	"C"	int					iWidth,iHeight;
extern	"C"	int					iScreenWidth,iScreenHeight;
extern	"C"	int					iWidth1,iWidth2,iHeight1,iHeight2;
extern	"C"	int					iCompressionLevel;
extern	"C" LPBITMAPINFOHEADER	lpBitmapIH;
extern	"C" SOCKET				sClient;
extern	"C"	BOOL				fConnected;
extern	"C"	struct	GdiList		GdiStart;
extern	"C"	struct	GdiList		*pGdiNode;
extern	"C"	int					nGridX,nGridY;
extern	"C"	BOOL				fGridX,fGridY;
extern	"C"	WORD				bmBitsPixel;
extern  "C" UINT				port;

// ���ӣ����ͺͽ��ձ���
int		iSent,iRecv;
char	szMouseMessage[81];

BYTE CMainWnd::m_ip[4];

CMainWnd::CMainWnd()
{
	// ��ʼ��������
	iHScrollPos = 0;
	iVScrollPos = 0;
	GdiStart.pNext = NULL;

	// ���ó�ʼ��ʱ����
	m_iTimerInterval = 398;
}

CMainWnd::~CMainWnd()
{
	delete this;
	// �ͷ�ȫ���ڴ�
	if (fDIBitmap)
		free(pDIBitmap);
	// �ͷ�ȫ��������ڴ�
	pGdiNode = GdiStart.pNext;
	while (pGdiNode)
	{
		if (pGdiNode->Gdi.fDIBitmap)
		{
			free(pGdiNode->Gdi.pDIBitmap);
			free(pGdiNode->Gdi.pDIB);
		}
		pGdiNode = pGdiNode->pNext;
	}
}

void CMainWnd::SetInstance(HINSTANCE hInst)
{
	m_hInst = hInst;
}

// ����WM_CREATE��Ϣ
BOOL CMainWnd::OnCreate(HWND hWnd,CREATESTRUCT FAR *lpCreateStruct)
{
	//����WinMains��nCmdShow������ʾ����
	ShowWindow(hWnd,*(LPINT)lpCreateStruct->lpCreateParams);
	m_hWnd = hWnd;
	m_hMenu = GetMenu(m_hWnd);
	EnableMenuItem(m_hMenu,IDM_DISCONNECT,MF_BYCOMMAND|MF_GRAYED);
	EnableMenuItem(m_hMenu,IDM_COLORMODE,MF_BYCOMMAND|MF_GRAYED);

	// ���ó�ʼ��ѹ������
	iCompressionLevel = 10;
	WSADATA				wsd;
	char				szString[255];
	char				name[20];

	if (WSAStartup(0x202,&wsd) != 0)
	{
		sprintf(szString,"Failed to load Winsock!");
		MessageBox(NULL,szString,"Remote Server",MB_OK);
		return 1;
	}
	GetLocalHostName(name);
	GetIpAddress(name,&m_ip[0],&m_ip[1],&m_ip[2],&m_ip[3]);

	return TRUE;
}

//����WM_DESTROY��Ϣ
void CMainWnd::OnDestroy(HWND hWnd)
{
	if (fDIBitmap)
	{
		KillTimer(m_hWnd,0);
	}

	if (fConnected)
	{
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		strcpy(szMouseMessage,DISCONNECT_MSG);

		// ���ͽ�����Ϣ����������
		iSent = Send(sClient,szMouseMessage);
		// �ر�socket
		closesocket(sClient);
		WSACleanup();
		// ��������״̬
		fConnected = FALSE;
	}
	// ����Windows Quit ��Ϣ������
	PostMessage(hWnd,WM_QUIT,(WPARAM)0,0L);
}

// ����WM_SIZE��Ϣ
void CMainWnd::OnSize(HWND hWnd,UINT state,int cx,int cy)
{
	if (fDIBitmap)
	{
		GetClientRect(m_hWnd,&m_Rect);

		// �����µ���Ļ�ߴ����ù�����
		SetScrollRange(m_hWnd,SB_HORZ,0,iScreenWidth - m_Rect.right,FALSE);
		SetScrollPos(m_hWnd,SB_HORZ,iHScrollPos,TRUE);
		SetScrollRange(m_hWnd,SB_VERT,0,iScreenHeight - m_Rect.bottom,FALSE);
		SetScrollPos(m_hWnd,SB_VERT,iVScrollPos,TRUE);

		// ���� WM_PAINT ��Ϣ
		InvalidateRect(hWnd,NULL,FALSE);
	}
}

// ����WM_PAINT��Ϣ
void CMainWnd::OnPaint(HWND hWnd)
{
	PAINTSTRUCT			ps;
	HDC					hDC;
	struct	GdiList		*pNode;
	int					iX1,iX2,iY1,iY2;

	hDC = BeginPaint(hWnd,&ps);

	if (fDIBitmap)
	{
		GetClientRect(m_hWnd,&m_Rect);
		if (!fConnected)
		{
			m_hMemDC = CreateCompatibleDC(hDC);
			m_hDDBitmap = CreateCompatibleBitmap(hDC,iScreenWidth,iScreenHeight);
			SelectObject(m_hMemDC,m_hDDBitmap);
		}
		pNode = GdiStart.pNext;
		while (pNode)
		{
			if (pNode->Gdi.fDIBitmap)
			{
				StretchDIBits(m_hMemDC,
					pNode->Gdi.iWidth1,pNode->Gdi.iHeight1,
					pNode->Gdi.lpBitmapIH->biWidth,pNode->Gdi.lpBitmapIH->biHeight,
					0,0,
					pNode->Gdi.lpBitmapIH->biWidth,pNode->Gdi.lpBitmapIH->biHeight,
					(LPBYTE)pNode->Gdi.lpBitmapIH + (pNode->Gdi.lpBitmapIH->biSize + (1 << pNode->Gdi.lpBitmapIH->biBitCount) * sizeof(RGBQUAD)),
					(LPBITMAPINFO)pNode->Gdi.lpBitmapIH,DIB_RGB_COLORS,SRCCOPY);
			}

			if (fGridX)
			{
				iX1 = pNode->Gdi.iWidth1;
				iY1 = pNode->Gdi.iHeight1;
				iY2 = pNode->Gdi.iHeight2;

				MoveToEx(m_hMemDC,iX1,iY1,NULL);
				LineTo(m_hMemDC,iX1,iY2);
			}

			if (fGridY)
			{
				iX1 = pNode->Gdi.iWidth1;
				iX2 = pNode->Gdi.iWidth2;
				iY1 = pNode->Gdi.iHeight1;
				MoveToEx(m_hMemDC,iX1,iY1,NULL);
				LineTo(m_hMemDC,iX2,iY1);
			}

			pNode = pNode->pNext;
		}

		BitBlt(hDC,0,0,iScreenWidth,iScreenHeight,m_hMemDC,iHScrollPos,-iVScrollPos,SRCCOPY);
		if (!fConnected)
		{
			DeleteObject(m_hDDBitmap);
			DeleteDC(m_hMemDC);
		}
	}
	EndPaint(hWnd,&ps);
}

//����WM_TIMER��Ϣ
void CMainWnd::OnTimer(HWND hWnd,UINT iId)
{
	// ������������˷�����
	if (fConnected)
	{
		// �õ�һ���µ���Ļ
		GetScreen();
	}
}

// ����WM_COMMAND��Ϣ
void CMainWnd::OnCommand(HWND hWnd,int iId,HWND hWndCtl,UINT iCodeNotify)
{
	// ѡ��˵����˳�
	if (iId == IDM_EXIT)
	{
		// �Ƿ������˷�����?
		if (fConnected)
		{
			// ���ͽ�����Ϣ��������
			memset(szMouseMessage,'\0',sizeof(szMouseMessage));
			strcpy(szMouseMessage,DISCONNECT_MSG);

			iSent = Send(sClient,szMouseMessage);

			// �ر�socket
			closesocket(sClient);
			// ���socket
			WSACleanup();
			// ��������״̬
			fConnected = FALSE;
			// ɾȥ������λͼ
			DeleteObject(m_hDDBitmap);
			// ɾȥ������Mem DC
			DeleteDC(m_hMemDC);
		}
		// ����Ӧ�ó���
		PostQuitMessage(0);
	}
	// ѡ��˵�������
	else if (iId == IDM_CONNECT)
	{
		// ��ʼ��IP��ַ
		sprintf(pServerIP->szIP,"%d.%d.%d.%d",CMainWnd::m_ip[0],CMainWnd::m_ip[1],CMainWnd::m_ip[2],CMainWnd::m_ip[3]);
		pServerIP->port=::port;
		// ����ip��port�ĶԻ���
		if (DialogBox(m_hInst,MAKEINTRESOURCE(IDD_SERVERIP),m_hWnd,(DLGPROC)ServerIPDlgProc))
		{
			if (LoadWinsock(m_hWnd,pServerIP->szIP) == 0)
				fConnected = TRUE;
			else
				fConnected = FALSE;

			if (fConnected)
			{
				// ʹ�Ͽ����Ӳ˵�����Ч
				EnableMenuItem(m_hMenu,IDM_DISCONNECT,MF_BYCOMMAND|MF_ENABLED);
				// ʹ���Ӳ˵�����Ч
				EnableMenuItem(m_hMenu,IDM_REFRESH,MF_BYCOMMAND|MF_GRAYED);
				// ʹɫ��ģʽ�˵���Ч
				EnableMenuItem(m_hMenu,IDM_COLORMODE,MF_BYCOMMAND|MF_ENABLED);

				if (fDIBitmap)
				{
					// ��Mem DC����������λͼ
					m_hMemDC = CreateCompatibleDC(GetDC(NULL));
					// ΪMem DC�������ݾ��
					m_hDDBitmap = CreateCompatibleBitmap(GetDC(NULL),iScreenWidth,iScreenHeight);
					SelectObject(m_hMemDC,m_hDDBitmap);

					// �õ��ͻ�����
					GetClientRect(m_hWnd,&m_Rect);

					// ���ù�����
					SetScrollRange(m_hWnd,SB_HORZ,0,iScreenWidth - m_Rect.right,FALSE);
					SetScrollPos(m_hWnd,SB_HORZ,iHScrollPos,TRUE);
					SetScrollRange(m_hWnd,SB_VERT,0,iScreenHeight - m_Rect.bottom,FALSE);
					SetScrollPos(m_hWnd,SB_VERT,iVScrollPos,TRUE);

					// ����ˢ��ʱ��
					SetTimer(m_hWnd,0,m_iTimerInterval,NULL);
				}
			}
		}
	}
	// ѡ��Ͽ����ӵĲ˵�
	else if (iId == IDM_DISCONNECT)
	{
		if (fConnected)
		{
			KillTimer(m_hWnd,0);
			EnableMenuItem(m_hMenu,IDM_DISCONNECT,MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem(m_hMenu,IDM_COLORMODE,MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem(m_hMenu,IDM_REFRESH,MF_BYCOMMAND|MF_ENABLED);
			//������Ϣ���������˽�������
			memset(szMouseMessage,'\0',sizeof(szMouseMessage));
			strcpy(szMouseMessage,DISCONNECT_MSG);
			
			// ������Ϣ��������
			iSent = Send(sClient,szMouseMessage);

			// �ر�socket
			closesocket(sClient);
			WSACleanup();
			fConnected = FALSE;
			DeleteObject(m_hDDBitmap);
			DeleteDC(m_hMemDC);
		}
	}
	// ѡ��ѹ���˵�ѡ��
	else if (iId == IDM_COMPRESSION)
	{
		// ѡ��ѹ��������ѹ����ʽ
		pCompression->m_iCompressionLevel = iCompressionLevel;
		if (DialogBox(m_hInst,MAKEINTRESOURCE(IDD_COMPRESSION),m_hWnd,(DLGPROC)CompressionDlgProc))
		{
			iCompressionLevel = pCompression->m_iCompressionLevel;
			if (fConnected)
			{
				KillTimer(m_hWnd,0);
				// ����ѹ����Ϣ
				memset(szMouseMessage,'\0',sizeof(szMouseMessage));
				sprintf(szMouseMessage,"WM_COMP;%d;0;0;0;\0",iCompressionLevel);
				// ����ѹ������
				SendCommand(hWnd,1,szMouseMessage);
				// ��������
				SetGrids(m_hWnd);
				UpdateRegionalScreen(m_hWnd,sClient,TRUE);
				SetTimer(m_hWnd,0,m_iTimerInterval,NULL);
			}
		}
	}
	// ѡ������ռ�˵�
	else if (iId == IDM_GRIDSPACING)
	{
		// ���õ�ǰ������ռ�
		pGridSpacing->m_nGridX = nGridX;
		pGridSpacing->m_nGridY = nGridY;
		pGridSpacing->m_fGridX = fGridX;
		pGridSpacing->m_fGridY = fGridY;
		if (DialogBox(m_hInst,MAKEINTRESOURCE(IDD_GRIDSPACING),m_hWnd,(DLGPROC)GridSpacingDlgProc))
		{
			BOOL	fChange = FALSE;
			if (nGridX != pGridSpacing->m_nGridX)
				fChange = TRUE;
			if (nGridY != pGridSpacing->m_nGridY)
				fChange = TRUE;

			// �õ�����ռ�ֵ
			nGridX = pGridSpacing->m_nGridX;
			nGridY = pGridSpacing->m_nGridY;
			fGridX = pGridSpacing->m_fGridX;
			fGridY = pGridSpacing->m_fGridY;
			if (fConnected && fChange)
			{
				KillTimer(m_hWnd,0);
				SetGrids(m_hWnd);
				UpdateRegionalScreen(m_hWnd,sClient,TRUE);
				SetTimer(m_hWnd,0,m_iTimerInterval,NULL);
			}
		}
	}
	// ѡ����ɫģʽ�Ĳ˵�
	else if (iId == IDM_COLORMODE)
	{
		// ���õ�ǰ��ѹ��������ģʽ
		pColorMode->m_bmBitsPixel = bmBitsPixel;
		if (DialogBox(m_hInst,MAKEINTRESOURCE(IDD_COLORMODE),m_hWnd,(DLGPROC)ColorModeDlgProc))
		{
			bmBitsPixel = pColorMode->m_bmBitsPixel;
			if (fConnected)
			{
				KillTimer(m_hWnd,0);
				memset(szMouseMessage,'\0',sizeof(szMouseMessage));
				sprintf(szMouseMessage,"WM_CMOD;%d;0;0;0;\0",bmBitsPixel);
				SendCommand(hWnd,1,szMouseMessage);
				SetGrids(m_hWnd);
				UpdateRegionalScreen(m_hWnd,sClient,TRUE);
				SetTimer(m_hWnd,0,m_iTimerInterval,NULL);
			}
		}
	}
	else if(iId==IDC_ABOUT)
	{
		MessageBox(hWnd,"2003-7-2����\r\nһ��Զ�̿��ƵĿͻ��˳���","Զ�̿��ƿͻ���",MB_OK);
	}

}
// ����WM_VSCROLL��Ϣ
void CMainWnd::OnVScroll(HWND hWnd,HWND hWndCtl,UINT iCode,int iPos)
{
	if (fDIBitmap)
	{
		if (iCode == SB_LINEUP)
			iVScrollPos = iVScrollPos + 1;
		else if (iCode == SB_LINEDOWN)
			iVScrollPos = iVScrollPos - 1;
		else if (iCode == SB_PAGEUP)
			iVScrollPos = iVScrollPos + 64;
		else if (iCode == SB_PAGEDOWN)
			iVScrollPos = iVScrollPos - 64;
		else if (iCode == SB_THUMBTRACK)
			iVScrollPos = -iPos;
		else if (iCode == SB_THUMBPOSITION)
			iVScrollPos = -iPos;

		if (-iVScrollPos < 0)
			iVScrollPos = 0;
		if (-iVScrollPos > (iScreenHeight - m_Rect.bottom))
			iVScrollPos = -(iScreenHeight - m_Rect.bottom);

		SetScrollPos(hWnd,SB_VERT,-iVScrollPos,TRUE);

		InvalidateRect(hWnd,NULL,FALSE);
	}
}

//����WM_HSCROLL��Ϣ
void CMainWnd::OnHScroll(HWND hWnd,HWND hWndCtl,UINT iCode,int iPos)
{
	if (fDIBitmap)
	{
		if (iCode == SB_LINEUP)
			iHScrollPos = iHScrollPos - 1;
		else if (iCode == SB_LINEDOWN)
			iHScrollPos = iHScrollPos + 1;
		else if (iCode == SB_PAGEUP)
			iHScrollPos = iHScrollPos - 48;
		else if (iCode == SB_PAGEDOWN)
			iHScrollPos = iHScrollPos + 48;
		else if (iCode == SB_THUMBTRACK)
			iHScrollPos = iPos;
		else if (iCode == SB_THUMBPOSITION)
			iHScrollPos = iPos;

		if (iHScrollPos < 0)
			iHScrollPos = 0;
		if (iHScrollPos > (iScreenWidth - m_Rect.right))
			iHScrollPos = iScreenWidth - m_Rect.right;

		SetScrollPos(hWnd,SB_HORZ,iHScrollPos,TRUE);

		InvalidateRect(hWnd,NULL,FALSE);
	}
}

// �������˫������Ϣ
void CMainWnd::OnLButtonDblClk(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags)
{
	if (fConnected)
	{
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_LBK;%d;%d;%d;0;\0",x,y,keyFlags);
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// ����������µ���Ϣ
void CMainWnd::OnLButtonDown(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags)
{
	if (fConnected)
	{
		x += iHScrollPos;
		y += (-1 * iVScrollPos);
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_LBD;%d;%d;%d;0;\0",x,y,keyFlags);
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// ��������������Ϣ
void CMainWnd::OnLButtonUp(HWND hWnd,int x,int y,UINT keyFlags)
{
	if (fConnected)
	{
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_LBU;%d;%d;%d;0;\0",x,y,keyFlags);

		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// �����м����µ���Ϣ
void CMainWnd::OnMButtonDblClk(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags)
{
	if (fConnected)
	{
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_MBK;%d;%d;%d;0;\0",x,y,keyFlags);

		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// �����м����µ���Ϣ
void CMainWnd::OnMButtonDown(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags)
{
	if (fConnected)
	{
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_MBD;%d;%d;%d;0;\0",x,y,keyFlags);
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// �����м��������Ϣ
void CMainWnd::OnMButtonUp(HWND hWnd,int x,int y,UINT keyFlags)
{
	if (fConnected)
	{
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_MBU;%d;%d;%d;0;\0",x,y,keyFlags);
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// �����Ҽ�˫������Ϣ
void CMainWnd::OnRButtonDblClk(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags)
{
	if (fConnected)
	{
		x += iHScrollPos;
		y += (-1 * iVScrollPos);
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_RBK;%d;%d;%d;0;\0",x,y,keyFlags);
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// �����Ҽ����µ���Ϣ
void CMainWnd::OnRButtonDown(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags)
{
	if (fConnected)
	{
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_RBD;%d;%d;%d;0;\0",x,y,keyFlags);

		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// �����Ҽ��������Ϣ
void CMainWnd::OnRButtonUp(HWND hWnd,int x,int y,UINT keyFlags)
{
	if (fConnected)
	{
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_RBU;%d;%d;%d;0;\0",x,y,keyFlags);

		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// ��������ƶ�����Ϣ
void CMainWnd::OnMouseMove(HWND hWnd,int x,int y,UINT keyFlags)
{
	if (fConnected)
	{
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_MM;%d;%d;%d;0;\0",x,y,keyFlags);
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// ��������µ���Ϣ
void CMainWnd::OnKeyDown(HWND hWnd,UINT vk,BOOL fDown,int cRepeat,UINT flags)
{
	if (fConnected)
	{
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_KD;%d;%d;%d;%d;\0",vk,fDown,cRepeat,flags);
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// ������������Ϣ
void CMainWnd::OnKeyUp(HWND hWnd,UINT vk,BOOL fDown,int cRepeat,UINT flags)
{
	if (fConnected)
	{
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_KU;%d;%d;%d;%d;\0",vk,fDown,cRepeat,flags);
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// �õ��µ���Ļ
void CMainWnd::GetScreen()
{
	SendCommand(m_hWnd,0,NULL);
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
