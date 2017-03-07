// Page6.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chapter5.h"
#include "Page6.h"
#include ".\page6.h"


// CPage6 �Ի���

IMPLEMENT_DYNAMIC(CPage6, CDialog)
CPage6::CPage6(CWnd* pParent /*=NULL*/)
	: CDialog(CPage6::IDD, pParent)
	, m_ServiceName(_T(""))
	, m_ServiceName2(_T(""))
{
}

CPage6::~CPage6()
{
}

void CPage6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_ServiceName);
	DDX_Text(pDX, IDC_EDIT4, m_ServiceName2);
}


BEGIN_MESSAGE_MAP(CPage6, CDialog)
END_MESSAGE_MAP()


// CPage6 ��Ϣ�������

BOOL CPage6::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	GetInfo();
	UpdateData(False);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// ��ȡ�������Ϣ
int CPage6::GetInfo(void)
{
	struct servent *servrec;
	struct sockaddr_in serv_addr;

	WSADATA     WSAData;
	int WSAReturn;
	//��ʹ��WinSock API֮ǰ���������WSAStartup������
	//ֻ�иú����ɹ����أ���ʾ��WinSock��ɹ��ؽ��������ӣ���
	//�ſ��Ե�������Windows Sockets DLL�еĺ���
	WSAReturn = WSAStartup( 0x0101, &WSAData );
	if( WSAReturn == 0 ){
		//ʹ��getservbyname��÷���
		m_ServiceName.AppendFormat("����ʹ��getservbyname��ȡftp����\r\n");
		servrec = getservbyname("ftp", "tcp");
		if (servrec != NULL) {
			m_ServiceName.AppendFormat("����ķ�������%s\r\n",servrec->s_name);
			m_ServiceName.AppendFormat("��ѡ���������У�%s\r\n",servrec->s_aliases);
			m_ServiceName.AppendFormat("���Ӹ÷���ʱ��Ҫ�õ��Ķ˿ںţ��������ֽ��򣩣�%d\r\n",servrec->s_port);
			m_ServiceName.AppendFormat("���Ӹ÷���ʱ�õ���Э������%s\r\n",servrec->s_proto);
		} 
		//����getservbyport��÷���
		m_ServiceName2.AppendFormat("\r\n����ʹ��getservbyport��ȡftp����\r\n");
		servrec = getservbyport(servrec->s_port, "tcp");
		if (servrec != NULL) {
			m_ServiceName2.AppendFormat("����ķ�������%s\r\n",servrec->s_name);
			m_ServiceName2.AppendFormat("��ѡ���������У�%s\r\n",servrec->s_aliases);
			m_ServiceName2.AppendFormat("���Ӹ÷���ʱ��Ҫ�õ��Ķ˿ںţ��������ֽ��򣩣�%d\r\n",servrec->s_port);
			m_ServiceName2.AppendFormat("���Ӹ÷���ʱ�õ���Э������%s\r\n",servrec->s_proto);
		} 

	}
	//����WSACleanup��������WinSock�����������Ա��ͷ���ռ�õ���Դ
	WSACleanup();

	return 0;
}
