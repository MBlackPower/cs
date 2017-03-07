// Page4.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chapter5.h"
#include "Page4.h"
#include ".\page4.h"
#include "iphlpapi.h"

// ��Ϊ��ͨ��NetAPI����ȡ������Ϣ,������Ҫ��������ͷ�ļ�nb30.h
#include <nb30.h>


// CPage4 �Ի���

IMPLEMENT_DYNAMIC(CPage4, CDialog)
CPage4::CPage4(CWnd* pParent /*=NULL*/)
	: CDialog(CPage4::IDD, pParent)
	, m_MACAddress(_T(""))
	, m_MACAddress2(_T(""))
{
}

CPage4::~CPage4()
{
}

void CPage4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_MACAddress);
	DDX_Text(pDX, IDC_EDIT4, m_MACAddress2);
}


BEGIN_MESSAGE_MAP(CPage4, CDialog)
END_MESSAGE_MAP()


// ��ȡ����MAC��ַ

int CPage4::GetInfo(void)
{
	//����1��NetApi32
	typedef struct _ASTAT_
	{
		ADAPTER_STATUS adapt;
		NAME_BUFFER
		NameBuff [30];
	} ASTAT, * PASTAT;

	ASTAT Adapter;
	// ����һ����ŷ���������Ϣ�ı���

      NCB Ncb;
      UCHAR uRetCode;
      char NetName[50];
      LANA_ENUM   lenum;
      int      i;

	  memset( &Ncb, 0, sizeof(Ncb) );
      Ncb.ncb_command = NCBENUM;
      Ncb.ncb_buffer = (UCHAR *)&lenum;
      Ncb.ncb_length = sizeof(lenum);
      uRetCode = Netbios( &Ncb );
      //printf( "The NCBENUM return code is: 0x%x \n", uRetCode );

      for(i=0; i < lenum.length ;i++)
      {
          memset( &Ncb, 0, sizeof(Ncb) );
          Ncb.ncb_command = NCBRESET;
          Ncb.ncb_lana_num = lenum.lana[i];

          uRetCode = Netbios( &Ncb );
          //printf( "The NCBRESET on LANA %d return code is: 0x%x \n",
          //        lenum.lana[i], uRetCode );

          memset( &Ncb, 0, sizeof (Ncb) );
          Ncb.ncb_command = NCBASTAT;
          Ncb.ncb_lana_num = lenum.lana[i];

          strcpy( (char*)Ncb.ncb_callname,  "*               " );
          Ncb.ncb_buffer = (PUCHAR) &Adapter;
          Ncb.ncb_length = sizeof(Adapter);

          uRetCode = Netbios( &Ncb );
          //printf( "The NCBASTAT on LANA %d return code is: 0x%x \n",
          //        lenum.lana[i], uRetCode );
          if ( uRetCode == 0 )
          {
             m_MACAddress.AppendFormat( "%02X-%02X-%02X-%02X-%02X-%02X\t",
                  Adapter.adapt.adapter_address[0],
                  Adapter.adapt.adapter_address[1],
                  Adapter.adapt.adapter_address[2],
                  Adapter.adapt.adapter_address[3],
                  Adapter.adapt.adapter_address[4],
                  Adapter.adapt.adapter_address[5] );
          }
       }
	  m_MACAddress.AppendFormat("%s","//����NetApi32ʵ��");
	  UpdateData(False);
 
	  //����2��GetAdaptersInfo
	PIP_ADAPTER_INFO pinfo=NULL;
	unsigned long len=0;

	if (pinfo!=NULL)
		delete (pinfo);
	unsigned  long nError;

	//��ñ��ؼ������������Ϣ
	nError	=	GetAdaptersInfo(pinfo,&len);
	if (nError==0)
	{
		do
		{
			m_MACAddress2.AppendFormat("%02X-%02X-%02X-%02X-%02X-%02X\t",
				pinfo->Address[0],
				pinfo->Address[1],
				pinfo->Address[2],
				pinfo->Address[3],
				pinfo->Address[4],
				pinfo->Address[5]);
		}
		while(pinfo->Next != NULL);
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
				do
				{
					m_MACAddress2.AppendFormat("%02X-%02X-%02X-%02X-%02X-%02X\t",
						pinfo->Address[0],
						pinfo->Address[1],
						pinfo->Address[2],
						pinfo->Address[3],
						pinfo->Address[4],
						pinfo->Address[5]);
				}
				while(pinfo->Next != NULL);
			}
	}

	m_MACAddress2.AppendFormat("%s","//����GetAdaptersInfo()ʵ��");
	UpdateData(False);

	if (pinfo!=NULL)
		delete (pinfo);	

	return 0;
}

BOOL CPage4::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
