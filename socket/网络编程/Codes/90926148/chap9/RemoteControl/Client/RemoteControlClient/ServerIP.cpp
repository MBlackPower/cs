#include "ServerIP.h"
#include "resource.h"

//����Server IP�༭��
HWND	hServerIP;
extern "C" UINT port;
CServerIP::CServerIP()
{
}

CServerIP::~CServerIP()
{
}

// �Ի����ʼ��
CServerIP::OnInitDialog(HWND hDlg,HWND hwndFocus, LPARAM lParam)
{
//	hServerIP = GetDlgItem(hDlg,IDC_SERVERIP);
	this->port =::port;
//	SetWindowText(hServerIP,szIP);
	SetDlgItemText(hDlg,IDC_SERVERIP,szIP);
	SetDlgItemInt(hDlg,IDC_PORT,port,false);
	return TRUE;
}

// �Ի���WM_COMMAND����
void CServerIP::OnCommand(HWND hDlg,int iId,HWND hWndCtl,UINT iCodeNotify)
{
	if (iId == IDOK)
	{
		::GetDlgItemText(hDlg,IDC_SERVERIP,szIP,sizeof(szIP));
		BOOL t;
		port=::GetDlgItemInt(hDlg,IDC_PORT,&t,false);
		::port=port;
		EndDialog(hDlg,TRUE);
	}
	else if (iId == IDCANCEL)
		EndDialog(hDlg,FALSE);
}
