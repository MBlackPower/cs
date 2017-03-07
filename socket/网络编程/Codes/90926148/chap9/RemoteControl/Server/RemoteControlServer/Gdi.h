#if !defined(GDI_H)
#define GDI_H

#include <windows.h>

// GDI���ݽṹ
struct GdiDS
{
	// ��������
	int		iGridX;
	int		iGridY;

	// �����������
	int		iWidth1;
	int		iWidth2;
	int		iHeight1;
	int		iHeight2;

	// �豸�޹�λͼ(DIB)��ɫ���е�ɫ�ʵ���Ŀ
	int		nColors;

	// DIB��Ϣͷ���ֽ���
	DWORD	dwBitMapHeader;

	// DIB ���Ⱥ���ʼ����
	DWORD	dwLen;
	DWORD	dwCompress;
	DWORD	iStartPos;

	// DIB
	BITMAP	DIBitmap;

	// DIB ��Ϣͷ
	BITMAPINFOHEADER	BMIH;

	// DIB��Ϣͷ��ָ��
	LPBITMAPINFOHEADER	lpBMIH;

	// ������豸���HDC
	HDC		hMemDC;

	// �����λͼ���
	HBITMAP	hDIBitmap;

	// ��ѹ����DIB����ָ��
	char	*pDIB;

	// ָ������DIB�ı仯��ָ��
	char	*pDIBChange;
	char	*pDIBChangeStart;

	// ָ��ѹ�������DIBָ��
	char	*pDIBCompress;

	// ָ��ȫ�������DIB
	char	*pDIBitmap;

	// DIB��־
	BOOL	fDIBitmap;
	BOOL	fChange;
};

// Gdi ����
struct GdiList
{
	struct	GdiDS	Gdi;
	struct	GdiList	*pNext;
};

struct	GdiList	*Add_Gdi(struct GdiList *pNode,struct GdiDS Gdi);
void			Clear_Gdi(struct GdiList *pStart);

#endif 
