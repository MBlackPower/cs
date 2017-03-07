#include "ColorMode.h"
#include "resource.h"

CColorMode::CColorMode()
{
}

CColorMode::~CColorMode()
{
}

//�Ի����ʼ��
CColorMode::OnInitDialog(HWND hDlg,HWND hwndFocus, LPARAM lParam)
{
	// ������ɫģʽ
	if (m_bmBitsPixel == 4)
		Button_SetCheck(GetDlgItem(hDlg,IDC_RADIO0),TRUE);
	else
		Button_SetCheck(GetDlgItem(hDlg,IDC_RADIO1),TRUE);

	return TRUE;
}

//�Ի���WM_COMMAND��Ϣ����
void CColorMode::OnCommand(HWND hDlg,int iId,HWND hWndCtl,UINT iCodeNotify)
{
	if (iId == IDOK)
	{
		//�����µ���ɫģʽ
		if (Button_GetState(GetDlgItem(hDlg,IDC_RADIO0)))
			m_bmBitsPixel = 4;
		else if (Button_GetState(GetDlgItem(hDlg,IDC_RADIO1)))
			m_bmBitsPixel = 8;
		EndDialog(hDlg,TRUE);
	}
	else if (iId == IDCANCEL)
		EndDialog(hDlg,FALSE);
}
