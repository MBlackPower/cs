         // DialogRelation.cpp : implementation file
//

#include "stdafx.h"
#include "NewTab.h"
#include "DialogRelation.h"

extern En_Decode Coder;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogRelation dialog


CDialogRelation::CDialogRelation(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CDialogRelation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogRelation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogRelation::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogRelation)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogRelation, CTabPageSSL)
	//{{AFX_MSG_MAP(CDialogRelation)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogRelation message handlers

void CDialogRelation::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	// �ַ���
	CString str;
	// ѭ������
	LONG i;

	// ������
	LONG lMaxCount = Coder.GetMaxFreq();
	// �豸������
//	CPaintDC dc(this);

	// ��ȡ����������ı���
	CWnd* pWnd = GetDlgItem(IDC_STATIC_HISTGRAM);
	// ָ��
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pDC->Rectangle(0,0,350,300);
	// �������ʶ���
	CPen* pPenRed = new CPen;
	// ��ɫ����
	pPenRed->CreatePen(PS_SOLID,1,RGB(255,0,0));
	// �������ʶ���
	CPen* pPenBlue = new CPen;
	// ��ɫ����
	pPenBlue->CreatePen(PS_SOLID,1,RGB(0,0, 255));
	// �������ʶ���
	CPen* pPenGreen = new CPen;
	// ��ɫ����
	pPenGreen->CreatePen(PS_DOT,1,RGB(0,255,0));

	// ѡ�е�ǰ��ɫ���ʣ���������ǰ�Ļ���
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);

	// ����������
	pDC->MoveTo(10,10);

	// ��ֱ��
	pDC->LineTo(10,280);

	// ˮƽ��
	pDC->LineTo(320,280);

	// дX��̶�ֵ
	str.Format("0");
	pDC->TextOut(10, 283, str);
	str.Format("50");
	pDC->TextOut(60, 283, str);
	str.Format("100");
	pDC->TextOut(110, 283, str);
	str.Format("150");
	pDC->TextOut(160, 283, str);
	str.Format("200");
	pDC->TextOut(210, 283, str);
	str.Format("255");
	pDC->TextOut(265, 283, str);

	// ����X��̶�
	for (i = 0; i < 256; i += 5)
	{
		if ((i & 1) == 0)
		{
			// 10�ı���
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 284);
		}
		else
		{
			// 10�ı���
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 282);
		}
	}

	// ����X���ͷ
	pDC->MoveTo(315,275);
	pDC->LineTo(320,280);
	pDC->LineTo(315,285);

	// ����X���ͷ
	pDC->MoveTo(10,10);
	pDC->LineTo(5,15);
	pDC->MoveTo(10,10);
	pDC->LineTo(15,15);

	// ���������ֵ
	pDC->MoveTo(10, 25);
	pDC->LineTo(14, 25);
	str.Format("%d", lMaxCount);
	pDC->TextOut(11, 26, str);

	// ���ĳ���ɫ����
	pDC->SelectObject(pPenGreen);	
/*
	// ���ƴ���������
	pDC->MoveTo(m_iLowGray + 10, 25);
	pDC->LineTo(m_iLowGray + 10, 280);
	pDC->MoveTo(m_iUpGray + 10, 25);
	pDC->LineTo(m_iUpGray + 10, 280);//*/

	// ���ĳ���ɫ����
	pDC->SelectObject(pPenBlue);	

	// �ж��Ƿ��м���
	if (lMaxCount > 0)
	{
		// ����ֱ��ͼ
		for (i = 0; i <= 256; i ++)
		{
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 281 - (int) (Coder.GetFreq(i) * 256 / lMaxCount));
		}
	}//*/

	// �ָ���ǰ�Ļ���
	pDC->SelectObject(pOldPen);	

	// ɾ���µĻ���
	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;

	// Do not call CTabPageSSL::OnPaint() for painting messages
}

void CDialogRelation::DrawHistgram()
{
/*	// �ַ���
	CString str;
	// ѭ������
	LONG i;

	// ������
	LONG lMaxCount = 0;
	// �豸������
	CPaintDC dc(this);

	// ��ȡ����������ı���
	CWnd* pWnd = GetDlgItem(IDC_STATIC_HISTGRAM);
	// ָ��
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pDC->Rectangle(0,0,350,300);
	// �������ʶ���
	CPen* pPenRed = new CPen;
	// ��ɫ����
	pPenRed->CreatePen(PS_SOLID,1,RGB(255,0,0));
	// �������ʶ���
	CPen* pPenBlue = new CPen;
	// ��ɫ����
	pPenBlue->CreatePen(PS_SOLID,1,RGB(0,0, 255));
	// �������ʶ���
	CPen* pPenGreen = new CPen;
	// ��ɫ����
	pPenGreen->CreatePen(PS_DOT,1,RGB(0,255,0));

	// ѡ�е�ǰ��ɫ���ʣ���������ǰ�Ļ���
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);

	// ����������
	pDC->MoveTo(10,10);

	// ��ֱ��
	pDC->LineTo(10,280);
	
	// ˮƽ��
	pDC->LineTo(320,280);

	// дX��̶�ֵ
	str.Format("0");
	pDC->TextOut(10, 283, str);
	str.Format("50");
	pDC->TextOut(60, 283, str);
	str.Format("100");
	pDC->TextOut(110, 283, str);
	str.Format("150");
	pDC->TextOut(160, 283, str);
	str.Format("200");
	pDC->TextOut(210, 283, str);
	str.Format("255");
	pDC->TextOut(265, 283, str);

	// ����X��̶�
	for (i = 0; i < 256; i += 5)
	{
		if ((i & 1) == 0)
		{
			// 10�ı���
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 284);
		}
		else
		{
			// 10�ı���
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 282);
		}
	}

	// ����X���ͷ
	pDC->MoveTo(315,275);
	pDC->LineTo(320,280);
	pDC->LineTo(315,285);

	// ����X���ͷ
	pDC->MoveTo(10,10);
	pDC->LineTo(5,15);
	pDC->MoveTo(10,10);
	pDC->LineTo(15,15);

	// ����������ֵ
	for (i = m_iLowGray; i <= m_iUpGray; i ++)
	{
		// �ж��Ƿ���ڵ�ǰ���ֵ
		if (m_lCount[i] > lMaxCount)
		{
			// �������ֵ
			lMaxCount = m_lCount[i];
		}
	}

	// ���������ֵ
	pDC->MoveTo(10, 25);
	pDC->LineTo(14, 25);
	str.Format("%d", lMaxCount);
	pDC->TextOut(11, 26, str);

	// ���ĳ���ɫ����
	pDC->SelectObject(pPenGreen);	

	// ���ƴ���������
	pDC->MoveTo(m_iLowGray + 10, 25);
	pDC->LineTo(m_iLowGray + 10, 280);
	pDC->MoveTo(m_iUpGray + 10, 25);
	pDC->LineTo(m_iUpGray + 10, 280);

	// ���ĳ���ɫ����
	pDC->SelectObject(pPenBlue);	

	// �ж��Ƿ��м���
	if (lMaxCount > 0)
	{
		// ����ֱ��ͼ
		for (i = m_iLowGray; i <= m_iUpGray; i ++)
		{
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 281 - (int) (m_lCount[i] * 256 / lMaxCount));
		}
	}

	// �ָ���ǰ�Ļ���
	pDC->SelectObject(pOldPen);	

	// ɾ���µĻ���
	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;*/

}
