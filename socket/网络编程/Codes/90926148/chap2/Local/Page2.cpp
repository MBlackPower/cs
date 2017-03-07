// Page2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chapter5.h"
#include "Page2.h"
#include ".\page2.h"
#include "Iphlpapi.h"

// CPage2 �Ի���

IMPLEMENT_DYNAMIC(CPage2, CDialog)
CPage2::CPage2(CWnd* pParent /*=NULL*/)
	: CDialog(CPage2::IDD, pParent)
	, m_getIPMask(_T(""))
{
}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_getIPMask);
}


BEGIN_MESSAGE_MAP(CPage2, CDialog)
END_MESSAGE_MAP()


// ��ü������������

int CPage2::GetInfo(void)
{
	PIP_ADAPTER_INFO pinfo=NULL;
	unsigned long len=0;

	if (pinfo!=NULL)
		delete (pinfo);
	unsigned  long nError;

	//��ñ��ؼ������������Ϣ
	nError	=	GetAdaptersInfo(pinfo,&len);
	if (nError==0)
	{
		m_getIPMask.Format("%s",pinfo->IpAddressList.IpMask.String);
		UpdateData(False);
	}
	if (nError==ERROR_NO_DATA)
	{
		AfxMessageBox("No adapter information exists for the local computer");
	}
	if (nError==ERROR_NOT_SUPPORTED)
	{
		AfxMessageBox("GetAdaptersInfo is not supported by the operating system running on the local computer");
	}
	if (nError==ERROR_BUFFER_OVERFLOW)
	{
		pinfo= (PIP_ADAPTER_INFO)malloc(len);
		nError	=	GetAdaptersInfo(pinfo,&len);
		if (nError==0)
		{
			m_getIPMask.Format("%s",pinfo->IpAddressList.IpMask.String);
			UpdateData(False);
		}
	}

	if (pinfo!=NULL)
		delete (pinfo);
	return 0;
}

BOOL CPage2::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
