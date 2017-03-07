// EnumProtocalView.cpp : implementation of the CEnumProtocalView class
//

#include "stdafx.h"
#include "EnumProtocal.h"

#include "EnumProtocalDoc.h"
#include "EnumProtocalView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnumProtocalView

IMPLEMENT_DYNCREATE(CEnumProtocalView, CTreeView)

BEGIN_MESSAGE_MAP(CEnumProtocalView, CTreeView)
	//{{AFX_MSG_MAP(CEnumProtocalView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnumProtocalView construction/destruction

CEnumProtocalView::CEnumProtocalView()
{
	WSACleanup();

}

CEnumProtocalView::~CEnumProtocalView()
{
}

BOOL CEnumProtocalView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_EDITLABELS;
	
	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEnumProtocalView drawing

void CEnumProtocalView::OnDraw(CDC* pDC)
{
	CEnumProtocalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CEnumProtocalView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
    WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	AddAllProtocals();
    // TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CEnumProtocalView printing

BOOL CEnumProtocalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEnumProtocalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEnumProtocalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEnumProtocalView diagnostics

#ifdef _DEBUG
void CEnumProtocalView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CEnumProtocalView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CEnumProtocalDoc* CEnumProtocalView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEnumProtocalDoc)));
	return (CEnumProtocalDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEnumProtocalView message handlers
LPCTSTR CEnumProtocalView::GetProtoDesc(int iProtocol)
{
	// WINSOCK2.H
	switch(iProtocol)
	{
	case IPPROTO_IP:
		return "IPPROTO_IP";
	case IPPROTO_ICMP:
		return "IPPROTO_ICMP";
	case IPPROTO_IGMP:
		return "IPPROTO_IGMP";
	case IPPROTO_GGP:
		return "IPPROTO_GGP";
	case IPPROTO_TCP:
		return "IPPROTO_TCP";
	case IPPROTO_PUP:
		return "IPPROTO_PUP";
	case IPPROTO_UDP:
		return "IPPROTO_UDP";
	case IPPROTO_IDP:
		return "IPPROTO_IDP";
	case IPPROTO_ND:
		return "IPPROTO_ND";
    case IPPROTO_RAW:
		return "IPPROTO_RAW";
		// Novell - WSIPX.H
	case NSPROTO_IPX:
		return "NSPROTO_IPX";
	case NSPROTO_SPX:
		return "NSPROTO_SPX";
	case NSPROTO_SPXII:
		return "NSPROTO_SPXII";
		//DecNet - WS2DNET.H
	case ISOPROTO_TP_CONS:
		return "ISOPROTO_TP_CONS";
	case ISOPROTO_TP4_CLNS:
		return "ISOPROTO_TP4_CLNS";
    case ISOPROTO_CLTP_CLNS:
		return "ISOPROTO_CLTP_CLNS";
	case 	ISOPROTO_X25:		
		return "ISOPROTO_X25";
		// ATM - WS2ATM.H
   	case ATMPROTO_AAL5:
		return "ATMPROTO_AAL5";
		// RSVP - WS2RSVP.H
	case IPPROTO_RSVP:
		return "IPPROTO_RSVP";
	default:
		return("Unknown Protocol Description");
	}
}


void CEnumProtocalView::AddAllProtocals()
{
	LPBYTE pBuf;                   //��������Э����Ϣ�Ļ�����
	DWORD dwLen;					//�������ĳ���
	LPWSAPROTOCOL_INFO pInfo;
	HTREEITEM hParent;
	HTREEITEM hParent2;
	HTREEITEM hParent3;
	//ͨ����һ�ε���WSAEnumProtocols�Ի�����軺�����Ĵ�С
	dwLen = 0;
	int nRet = WSAEnumProtocols(NULL,
								NULL, //ָ��WSAPROTOCOL_INFO�ṹΪ��
								&dwLen);
	if (nRet == SOCKET_ERROR)
	{
		// ����ʧ��
		if (WSAGetLastError() != WSAENOBUFS)
		{   
			CString strTemp;
			strTemp.Format("EnumProtocals() failed:%d",WSAGetLastError());
			AfxMessageBox(strTemp);
			return;
		}
	}
	//��黺�����Ĵ�С�Ƿ����������Ϣ
	if (dwLen < sizeof(WSAPROTOCOL_INFO))
	{
		AfxMessageBox("Internal error");
		return;
	}
	dwLen++;
	pBuf = (LPBYTE) malloc(dwLen);    //����������ڴ�
	if (pBuf == NULL)
	{
		AfxMessageBox("Couldn't allocate protocol buffer");
		return;
	}
    //���еڶ���ʵ�ʵĵ��ã�nRet����Э��ĸ���
	nRet = WSAEnumProtocols(NULL, 
						   (LPWSAPROTOCOL_INFO)pBuf, 
						   &dwLen);
	if (nRet == SOCKET_ERROR)
	{   
        //����ʧ��
		free(pBuf);
		CString strTemp;
		strTemp.Format("EnumProtocals() failed:%d",WSAGetLastError());
		AfxMessageBox(strTemp);
		return;		
	}
	//������Э�����Ϣ���Ѳ�ͬ��ε�Э����Ϣ�ӵ�������ͼ��
	pInfo = (LPWSAPROTOCOL_INFO)pBuf;	
	for(int nCount = 0; nCount < nRet; nCount++)
	{
		// ÿ��Э��Ӹ���ʼ���
		hParent = AddTreeItem(GetTreeCtrl().m_hWnd, 
							  TVI_ROOT, 
							  pInfo->szProtocol);

		// ������Ӹ�Э����֧�ֵ�����
		hParent2 = AddTreeItem(GetTreeCtrl().m_hWnd, 
							   hParent, 
							   "Service Flags");

		//������Ա����Э��֧�ֵ�����
		#define ADDSF(f, s1, s2)				\
		AddTreeItem(GetTreeCtrl().m_hWnd,		\
				hParent2,						\
				(pInfo->dwServiceFlags1 & f) ?	\
				s1 : s2)

		//�ṩ�����ӷ���
        ADDSF(XP1_CONNECTIONLESS, 
			"Connectionless",
			"Connection-oriented");
        //��֤���ͳ�ȥ���������ݶ�������ȶ����ն�
        ADDSF(XP1_GUARANTEED_DELIVERY,
			"Delivery guaranteed",
			"Delivery NOT guaranteed");
        //��֤���ݰ��䷢��˳�򵽴���նˣ������ݲ����ظ�
        ADDSF(XP1_GUARANTEED_ORDER,
			"Order guaranteed",
			"Order NOT guaranteed");
        //ʵ����Ϣ�߽�
        ADDSF(XP1_MESSAGE_ORIENTED,
			"Message boundaries preserved",
			"Message boundaries NOT preserved");
        if (pInfo->dwServiceFlags1 & XP1_PSEUDO_STREAM)
			AddTreeItem(GetTreeCtrl().m_hWnd, hParent2, 
				"Message oriented with boundaries ignored");
        //֧��֧�ֶ���ر�
        ADDSF(XP1_GRACEFUL_CLOSE,
			"Can perform graceful close",
			"Abortive close only");
         //��Э���ṩ��������
        ADDSF(XP1_EXPEDITED_DATA,
			"Supports expedited data",
			"Doesn't support expedited data");
         //֧���������ӷ���
        ADDSF(XP1_CONNECT_DATA,
			"Supplies connect data",
			"Doesn't supply connect data");
        ADDSF(XP1_DISCONNECT_DATA,
			"Supplies disconnect data",
			"Doesn't supply disconnect data");
        //֧�ֹ㲥
        ADDSF(XP1_SUPPORT_BROADCAST,
			"Supports broadcasts",
			"Doesn't support broadcasts");
		
		// ֧�ֶಥ
        if (pInfo->dwServiceFlags1 & XP1_SUPPORT_MULTIPOINT)
		{
			hParent3 = AddTreeItem(GetTreeCtrl().m_hWnd, 
								   hParent2, 
								   "Supports multicast");
            //֧�ֶಥ���԰����������棺���Դ򿪿������򲻿���
			AddTreeItem(GetTreeCtrl().m_hWnd,
						hParent3,
						(pInfo->dwServiceFlags1 & 
						XP1_MULTIPOINT_CONTROL_PLANE) ?
						"Control plane rooted" :
			            "Control plane non-rooted");
			AddTreeItem(GetTreeCtrl().m_hWnd,
						hParent3,
						(pInfo->dwServiceFlags1 & 
						XP1_MULTIPOINT_DATA_PLANE) ?
						"Data plane rooted" :
						"Data plane non-rooted");
		}
		else
			AddTreeItem(GetTreeCtrl().m_hWnd, 
						hParent2, 
						"Doesn't support multicast");
        //֧�ַ�����������
       ADDSF(XP1_QOS_SUPPORTED,
			"Supports quality of service",
			"Doesn't support quality of service");
        //������
        if (pInfo->dwServiceFlags1 & XP1_UNI_SEND)
			AddTreeItem(GetTreeCtrl().m_hWnd, 
					hParent2, 
					"Unidirectional in the send direction");
        //�������
        if (pInfo->dwServiceFlags1 & XP1_UNI_RECV)
			AddTreeItem(GetTreeCtrl().m_hWnd, 
					hParent2, 
					"Unidirectional in the recv direction");
 
        //�����ͺͽ���
        if (!(pInfo->dwServiceFlags1 & XP1_UNI_SEND) &&
			!(pInfo->dwServiceFlags1 & XP1_UNI_RECV))
			 AddTreeItem(GetTreeCtrl().m_hWnd, 
					    hParent2, 
					   "Bidirectional sending and receiving");
        if (pInfo->dwServiceFlags1 & XP1_IFS_HANDLES)
			AddTreeItem(GetTreeCtrl().m_hWnd, 
					hParent2, 
					"Socket descriptors are IFS handles");
        ADDSF(XP1_PARTIAL_MESSAGE,
			"Supports MSG_PARTIAL",
			"Doesn't support MSG_PARTIAL");
		//Э���ṩ�� 
		hParent2 = AddTreeItem(GetTreeCtrl().m_hWnd, 
							   hParent, 
							   "Provider Flags");
        	if (pInfo->dwProviderFlags & 
				PFL_MULTIPLE_PROTO_ENTRIES)
			AddTreeItem(GetTreeCtrl().m_hWnd, 
						hParent2, 
						"This is one behavior of two or"
						" more for this protocol");
        	if (pInfo->dwProviderFlags & 
				PFL_RECOMMENDED_PROTO_ENTRY)
			AddTreeItem(GetTreeCtrl().m_hWnd, 
						hParent2, 
						"This is the recommended entry"
						" for this protocol.");
        //��ʾ���ص�Ŀ¼���
		if (pInfo->dwProviderFlags & PFL_HIDDEN)
			AddTreeItem(GetTreeCtrl().m_hWnd, 
						hParent2, 
						"WS2 SPI ERROR."
						" Hidden catalog entry shown");
        //����Э�����Ϊ0
		if (pInfo->dwProviderFlags & 
				PFL_MATCHES_PROTOCOL_ZERO)
			AddTreeItem(GetTreeCtrl().m_hWnd, 
						hParent2, 
						"Use zero as protocol parameter");
             AddTreeItem(GetTreeCtrl().m_hWnd, 
					hParent, 
					"GUID: %s", 
					GUIDtoString((GUID *)&pInfo->ProviderId));
        //Ŀ¼���
		AddTreeItem(GetTreeCtrl().m_hWnd, 
					hParent, 
					"Catalog entry: %ld", 
					pInfo->dwCatalogEntryId);

		// Э����
		switch(pInfo->ProtocolChain.ChainLen)
		{
			case 0:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
							hParent, 
							"Layered protocol");
				break;
			case 1:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
							hParent, 
							"Base protocol");
				break;
			default:
				if (pInfo->ProtocolChain.ChainLen > 1)
					AddTreeItem(GetTreeCtrl().m_hWnd, 
								hParent, 
								"Protocol chain");
				else
					AddTreeItem(GetTreeCtrl().m_hWnd, 
								hParent, 
								"SPI ERROR:"
								" Invalid ChainLen");
		}
		
        //Э��İ汾��Ϣ
		AddTreeItem(GetTreeCtrl().m_hWnd, 
					hParent, 
					"Version: %d", 
					pInfo->iVersion);
		// ��ַ��
		AddTreeItem(GetTreeCtrl().m_hWnd, 
					hParent, 
					"Address family: %s",
					GetDescription(pInfo->iAddressFamily));
                    //�������GetDescription�����Ӧ��ַ������������
		// SOCKADDR�����ߴ�
		AddTreeItem(GetTreeCtrl().m_hWnd, 
					hParent, 
					"Min/Max Address length: %d/%d",
					pInfo->iMinSockAddr,
					pInfo->iMaxSockAddr);
		// ֧�ֵ��׽�������
		switch(pInfo->iSocketType)
		{
			case SOCK_STREAM:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
							hParent, 
							"SOCK_STREAM");
				break;
			case SOCK_DGRAM:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
							hParent, 
							"SOCK_DGRAM");
				break;
			case SOCK_RAW:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
							hParent, 
							"SOCK_RAW");
				break;
			case SOCK_RDM:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
							hParent, 
							"SOCK_RDM");
				break;
			case SOCK_SEQPACKET:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
							hParent, 
							"SOCK_SEQQPACKET");
				break;
			default:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
							hParent, 
							"Unknown");
		}
		// Э��
		AddTreeItem(GetTreeCtrl().m_hWnd, 
					hParent, 
					"Protocol: %s",
					GetProtoDesc(pInfo->iProtocol));
                    //�������GetProtoDesc������ȡ��Ӧ��Э�������
		AddTreeItem(GetTreeCtrl().m_hWnd, 
					hParent, 
					"Protocol Max Offset: %d", 
					pInfo->iProtocolMaxOffset);
		// �����ӽ�˳��
		switch(pInfo->iNetworkByteOrder)
		{
			case BIGENDIAN:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
	                         hParent, 
							"Big Endian");
				break;
			case LITTLEENDIAN:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
							hParent, 
							"Little Endian");
				break;
			default:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
							hParent, 
							"Unknown");
		}
		//֧�ֵİ�ȫ����
		AddTreeItem(GetTreeCtrl().m_hWnd, 
					hParent, 
					"Security scheme: %d",
					pInfo->iSecurityScheme);
		// ���ĵ����ߴ�
		switch(pInfo->dwMessageSize)
		{
			case 0:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
							hParent, 
							"Max message siz��e"
							" not applicable");
				break;
			case 1:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
							hParent, 
							"Max message size based on MTU");
				break;
			case 0xFFFFFFFF:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
							hParent, 
							"No limit on max message size");
				break;
			default:
				AddTreeItem(GetTreeCtrl().m_hWnd, 
							hParent, 
							"Unknown max message size: %ld", 
							pInfo->dwMessageSize);
		}
		// ��ȡ��һ��Э��
		pInfo++;
	}
    //�����������ͷ��ڴ�
	free(pBuf);
	return;

}

HTREEITEM CEnumProtocalView::AddTreeItem(HWND hWndTree, 
					  HTREEITEM hParent, 
					  LPSTR lpszFormat, 
					  ...)
{
	va_list Marker;
	char szBuf[256];
	TV_ITEM tvi;
	TV_INSERTSTRUCT tvis;

	// Format the string
	va_start(Marker, lpszFormat);
	vsprintf(szBuf, lpszFormat, Marker);
	va_end(Marker);

	// Fill in the TV_ITEM structure
	tvi.mask	      = TVIF_TEXT;
	tvi.pszText	      = szBuf; 
	tvi.cchTextMax    = lstrlen(szBuf); 

	// Fill in the TV_INSERTSTRUCT
	tvis.item         = tvi;
	tvis.hInsertAfter = TVI_LAST;
	tvis.hParent       = hParent; 
	return (TreeView_InsertItem(hWndTree, &tvis));
}

LPCTSTR CEnumProtocalView::GUIDtoString(GUID *pGUID)
{
	static char szStr[33];
	wsprintf(szStr, 
	    "%08lx-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		pGUID->Data1,
		pGUID->Data2,
		pGUID->Data3,
		pGUID->Data4[0],
		pGUID->Data4[1],
		pGUID->Data4[2],
		pGUID->Data4[3],
		pGUID->Data4[4],
		pGUID->Data4[5],
		pGUID->Data4[6],
		pGUID->Data4[7]);
	return(szStr);	
	

}

LPCTSTR CEnumProtocalView::GetDescription(int nAddressFamily)
{
	switch(nAddressFamily)
	{
	case AF_UNSPEC:
		return "AF_UNSPEC";
	case AF_UNIX:
		return "AF_UNIX";
	case AF_INET:
		return "AF_INET";
	case AF_IMPLINK:
		return "AF_IMPLINK";
	case AF_PUP:
		return "AF_PUP";
	case AF_CHAOS:
		return "AF_CHAOS";
		//	AF_NS,		"AF_NS",	// Same as AF_IPX
	case AF_IPX:
		return "AF_IPX";
	case AF_ISO:
		return "AF_ISO";
	case AF_ECMA:
		return "AF_ECMA";
	case AF_DATAKIT:
		return "AF_DATAKIT";
	case AF_CCITT:
		return "AF_CCITT";
	case AF_SNA:
		return "AF_SNA";
	case AF_DECnet:
		return "AF_DECnet";
	case AF_DLI:
		return "AF_DLI";
	case AF_LAT:
		return "AF_LAT";
	case AF_HYLINK:
		return "AF_HYLINK";
	case AF_APPLETALK:
		return "AF_APPLETALK";
	case AF_NETBIOS:
		return "AF_NETBIOS";
	case AF_VOICEVIEW:
		return "AF_VOICEVIEW";
	case AF_FIREFOX:
		return "AF_FIREFOX";
	case AF_UNKNOWN1:
		return "AF_UNKNOWN1 Somebody is using this!";
	case AF_BAN:
		return "AF_BAN";
	case AF_ATM:
		return "AF_ATM";
	case AF_INET6:
		return "AF_INET6";
	default:
		return("Unknown Protocol Type");
	}
}

