#if !defined(COLORMODE_H)
#define COLORMODE_H

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

//��ɫģʽ�Ի���Ĵ���
class	CColorMode
{
public:

	CColorMode();
	~CColorMode();

	// ��Ϣ������
	BOOL	OnInitDialog(HWND hDlg,HWND hwndFocus, LPARAM lParam);
	void	OnCommand(HWND hDlg,int iId,HWND hWndCtl,UINT iCodeNotify);

	int		m_bmBitsPixel;
};

#endif