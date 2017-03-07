#include "Gdi.h"
#include "Server.h"
#include <windows.h>

// ���һ��Ԫ�ص�GDI����
struct GdiList *Add_Gdi(struct GdiList *pNode,struct GdiDS Gdi)
{
	// ��ӵ������ĩβ
	if (pNode->pNext = (struct GdiList *)malloc(sizeof(struct GdiList)))
	{
		pNode = pNode->pNext;

		// �����������
		pNode->Gdi.iGridX = Gdi.iGridX;
		pNode->Gdi.iGridY = Gdi.iGridY;

		// ��������ľ�������
		pNode->Gdi.iWidth1 = Gdi.iWidth1;
		pNode->Gdi.iWidth2 = Gdi.iWidth2;
		pNode->Gdi.iHeight1 = Gdi.iHeight1;
		pNode->Gdi.iHeight2 = Gdi.iHeight2;

		// ����DIB��ɫ�����ɫ��
		pNode->Gdi.nColors = Gdi.nColors;

		// ����DIB��Ϣͷ���ֽ���
		pNode->Gdi.dwBitMapHeader = Gdi.dwBitMapHeader;

		// ����λͼ���Ⱥ���ʼ����
		pNode->Gdi.dwLen = Gdi.dwLen;
		pNode->Gdi.dwCompress = Gdi.dwCompress;
		pNode->Gdi.iStartPos = Gdi.iStartPos;

		//����DIB
		pNode->Gdi.DIBitmap = Gdi.DIBitmap;

		// ����DIB��Ϣͷ
		pNode->Gdi.BMIH = Gdi.BMIH;

		// ����DIB��Ϣͷ��ָ��
		pNode->Gdi.lpBMIH = Gdi.lpBMIH;

		// ���������װ���豸���
		pNode->Gdi.hMemDC = Gdi.hMemDC;

		// ���������λͼ���
		pNode->Gdi.hDIBitmap = Gdi.hDIBitmap;

		// ������ѹ��DIB��ָ��
		pNode->Gdi.pDIB = Gdi.pDIB;

		//����ָ������DIB�仯�Ĳ��ֵ�ָ��
		pNode->Gdi.pDIBChange = Gdi.pDIBChange;

		//����ָ��ѹ�������DIB��ָ��
		pNode->Gdi.pDIBCompress = Gdi.pDIBCompress;

		//����ָ��ȫ������λͼָ��
		pNode->Gdi.pDIBitmap = Gdi.pDIBitmap;

		// ����λͼ��־
		pNode->Gdi.fDIBitmap = Gdi.fDIBitmap;
		pNode->Gdi.fChange = Gdi.fChange;

		pNode->pNext = NULL;
		return pNode;
	}
	return NULL;
}

// ��ȫ���GDI����
void Clear_Gdi(struct GdiList *pStart)
{
	struct	GdiList	*pPrev;
	struct	GdiList	*pNode;
	while (pNode = pStart->pNext)
	{
		pPrev = pStart;
		pPrev->pNext = pNode->pNext;
		DeleteDC(pNode->Gdi.hMemDC);
		DeleteObject(pNode->Gdi.hDIBitmap);
		if (pNode->Gdi.fDIBitmap)
		{
			free(pNode->Gdi.pDIBitmap);
			free(pNode->Gdi.pDIB);
			free(pNode->Gdi.pDIBChangeStart);
		}
		free(pNode);
	}
}