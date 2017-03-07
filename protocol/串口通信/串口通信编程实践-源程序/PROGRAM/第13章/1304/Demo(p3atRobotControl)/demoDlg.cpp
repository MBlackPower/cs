// demoDlg.cpp : implementation file
//
#include "stdafx.h"
#include "demo.h"
#include "demoDlg.h"
#include "io.h"
#include "math.h"
#include "SetCurStatus.h"
#include "Command.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BufSize 512
bool flag1=1;//ͬ��1��򿪵ı�־
bool flag2=1;//ͬ��2��򿪵ı�־

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}
BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
/*	m_ctrlHyperLink1.SetURL(_T("mailto:webmaster@gjwtech.com"));
	m_ctrlHyperLink1.SetUnderline(TRUE);
	m_ctrlHyperLink1.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_HAND));

	m_ctrlHyperLinkWWWXFS.SetURL(_T("http://www.gjwtech.com"));
	m_ctrlHyperLinkWWWXFS.SetUnderline(TRUE);
	m_ctrlHyperLinkWWWXFS.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_HAND));*/
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlg)
	m_ReceiveData = _T("");
	m_strSendData = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bAutoSend=FALSE;
	//m_bVisible=FALSE;
	// m_bSendFile=FALSE;
	m_bStopDispRXData=FALSE;
	m_bOpenPort=FALSE;
	m_nCycleTime=1000;
	// m_strCurPath="C:\\COMDATA";
	// m_strSendFilePathName="��û��ѡ���ļ�";//"No File Selected!";
	// m_nFileLength=0;
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
	DDX_Control(pDX, IDC_STATIC_ControlStatus, m_ctrlControlStatus);
	DDX_Control(pDX, IDC_STATIC_TXCOUNT, m_ctrlTXCount);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_ctrlPortStatus);
	DDX_Control(pDX, IDC_STATIC_RXCOUNT, m_ctrlRXCOUNT);
	DDX_Control(pDX, IDC_EDIT_RECIVE, m_ctrlReceiveData);
	DDX_Control(pDX, IDC_STATIC_OPENOFF, m_ctrlIconOpenoff);
	DDX_Control(pDX, IDC_COMBO_STOPBITS, m_StopBits);
	DDX_Control(pDX, IDC_COMBO_DATABITS, m_DataBits);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_Parity);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_Baud);
	DDX_Control(pDX, IDC_COMBO_COMSELECT, m_Com);
	DDX_Control(pDX, IDC_CHECK_HEXSEND, m_ctrlHexSend);
	DDX_Control(pDX, IDC_CHECK_HEXRECIEVE, m_ctrlHexReceive);
	DDX_Control(pDX, IDC_CHECK_AUTOSEND, m_ctrlAutoSend);
	DDX_Control(pDX, IDC_BUTTON_URGENCYSTOP, m_ctrlUrgencyStop);
	DDX_Control(pDX, IDC_BUTTON_TURNRIGHT, m_ctrlTurnRight);
	DDX_Control(pDX, IDC_BUTTON_TURNLEFT, m_ctrlTurnLeft);
	DDX_Control(pDX, IDC_BUTTON_SYN2, m_ctrlSyn2);
	DDX_Control(pDX, IDC_BUTTON_SYN1, m_ctrlSyn1);
	DDX_Control(pDX, IDC_BUTTON_SYN0, m_ctrlSyn0);
	DDX_Control(pDX, IDC_BUTTON_STOPDISP, m_ctrlStopDisp);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_ctrlStop);
	DDX_Control(pDX, IDC_BUTTON_STARTMOTOR, m_ctrlStartMotor);
	DDX_Control(pDX, IDC_BUTTON_OPENPORT, m_ctrlOpenPort);
	DDX_Control(pDX, IDC_BUTTON_ONWARD, m_ctrlOnWard);
	DDX_Control(pDX, IDC_BUTTON_MANUALSEND, m_ctrlManualSend);
	DDX_Control(pDX, IDC_BUTTON_CLOSEMOTOR, m_ctrlCloseMotor);
	DDX_Control(pDX, IDC_BUTTON_CLEARRECASENDA, m_ctrlClearTXData);
	DDX_Control(pDX, ID_BUTTONC_REVERSE, m_ctrlReverse);
	DDX_Text(pDX, IDC_EDIT_RECIVE, m_ReceiveData);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSendData);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_MESSAGE(WM_COMM_RXCHAR, OnCommunication)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CLOSEMOTOR, OnButtonClosemotor)
	ON_BN_CLICKED(IDC_BUTTON_OPENPORT, OnButtonOpenport)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_RECI_AREA, OnButtonClearReciArea)
	ON_BN_CLICKED(IDC_BUTTON_STOPDISP, OnButtonStopdisp)
	ON_BN_CLICKED(IDC_BUTTON_CLEARRECASENDA, OnButtonClearrecasenda)
	ON_BN_CLICKED(IDC_BUTTON_MANUALSEND, OnButtonManualsend)
	ON_BN_CLICKED(IDC_CHECK_AUTOSEND, OnCheckAutosend)
	ON_EN_CHANGE(IDC_EDIT_CYCLETIME, OnChangeEditCycletime)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT_SEND, OnChangeEditSend)
	ON_BN_CLICKED(IDC_BUTTON_SYN0, OnButtonSyn0)
	ON_BN_CLICKED(IDC_BUTTON_SYN1, OnButtonSyn1)
	ON_BN_CLICKED(IDC_BUTTON_SYN2, OnButtonSyn2)
	ON_BN_CLICKED(IDC_BUTTON_STARTMOTOR, OnButtonStartmotor)
	ON_BN_CLICKED(IDC_BUTTON_URGENCYSTOP, OnButtonUrgencystop)
	ON_BN_CLICKED(IDC_BUTTON_ONWARD, OnButtonOnward)
	ON_BN_CLICKED(ID_BUTTONC_REVERSE, OnButtonReverse)
	ON_BN_CLICKED(IDC_BUTTON_TURNLEFT, OnButtonTurnleft)
	ON_BN_CLICKED(IDC_BUTTON_TURNRIGHT, OnButtonTurnright)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_COUNTRESET, OnButtonCountreset)
	ON_CBN_SELENDOK(IDC_COMBO_DATABITS, OnSelendokComboDatabits)
	ON_CBN_SELENDOK(IDC_COMBO_PARITY, OnSelendokComboParity)
	ON_CBN_SELENDOK(IDC_COMBO_STOPBITS, OnSelendokComboStopbits)
	ON_CBN_SELENDOK(IDC_COMBO_COMSELECT, OnSelendokComboComselect)
	ON_CBN_SELENDOK(IDC_COMBO_BAUD, OnSelendokComboBaud)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTONC_REVERSE, OnButtoncReverse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
{
	// CDialog::OnInitDialog();
	  BOOL b = CDialog::OnInitDialog(); 

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	CMenu* pMenu = GetSystemMenu(FALSE);
    pMenu->EnableMenuItem(SC_MAXIMIZE,MF_BYCOMMAND | MF_GRAYED);


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Com.SetCurSel(0);
	m_Baud.SetCurSel(5);
	m_Parity.SetCurSel(0);
	m_DataBits.SetCurSel(0);
	m_StopBits.SetCurSel(1);
    m_ctrlHexSend.SetCheck(1);
	m_ctrlHexReceive.SetCheck(1);

	m_hIconRed  = AfxGetApp()->LoadIcon(IDI_ICON_RED);
	m_hIconOff	= AfxGetApp()->LoadIcon(IDI_ICON_OFF);
	// m_hIconGreen= AfxGetApp()->LoadIcon(IDI_ICON_GREEN);

	m_nBaud=9600;
	m_nCom=1;
	m_cParity='N';
	m_nDatabits=8;
	m_nStopbits=1;
	m_dwCommEvents = EV_RXFLAG | EV_RXCHAR;//�����¼�

		CString strStatus;
	if (m_Port.InitPort(this, m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits,m_dwCommEvents,512))
	{
		m_Port.StartMonitoring();
		strStatus.Format("STATUS��COM%d OPENED��%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
		m_ctrlIconOpenoff.SetIcon(m_hIconRed);
		//m_ctrlIconOpenoff.SetIcon(m_hIconOff);

		//"��ǰ״̬�����ڴ򿪣�����żУ�飬8����λ��1ֹͣλ");
	}
	else
	{
		AfxMessageBox("û�з��ִ˴���");
		m_ctrlIconOpenoff.SetIcon(m_hIconOff);
	}
     m_ctrlPortStatus.SetWindowText(strStatus);

	CEdit* pEdit=(CEdit*)GetDlgItem(IDC_EDIT_CYCLETIME);
	CString strText;
	strText.Format("%d",m_nCycleTime);
	pEdit->SetWindowText(strText);   //Display cycle time

	m_strSendData="��ӭ��ʹ�ø���ʾ�����";
	char cr=13,lf=10;
	m_strSendData+=cr+lf;

	// m_ctrlAutoClear.SetCheck(1);
	// m_ctrlEditSendFile.SetWindowText("No File Selected!");

	// m_animIcon.SetImageList(IDB_ANIM_IMGLIST,4,RGB(0,0,0));   
	SetTimer(4,200,NULL);

	UpdateData(FALSE);

	ShowWindow(SW_SHOW); 
	
	// return TRUE;  // return TRUE  unless you set the focus to a control
	return b;
}

void CDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CDemoDlg::OnButtonOpenport() 
{
	// TODO: Add your control notification handler code here
	m_bOpenPort=!m_bOpenPort;
	if(m_bOpenPort)  //�رմ���
	{
		if(m_ctrlAutoSend.GetCheck())
		{
			m_bOpenPort=!m_bOpenPort;
			AfxMessageBox("���ȹص��Զ�����");
			return;
		}

		m_ctrlOpenPort.SetWindowText("�򿪴���");
		m_Port.ClosePort();//�رմ���
    	m_ctrlPortStatus.SetWindowText("STATUS��COM Port Closed");
		m_ctrlIconOpenoff.SetIcon(m_hIconOff);
	}
	else  //�򿪴���
	{
		m_ctrlOpenPort.SetWindowText("�رմ���");
		
		CString strStatus;
		if (m_Port.InitPort(this, m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits,m_dwCommEvents,512))
		{
			m_Port.StartMonitoring();
			m_ctrlIconOpenoff.SetIcon(m_hIconRed);
			strStatus.Format("STATUS��COM%d OPENED��%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
			//"��ǰ״̬�����ڴ򿪣�����żУ�飬8����λ��1ֹͣλ");
		}
		else
		{
			AfxMessageBox("û�з��ִ˴��ڻ�ռ��");
			m_ctrlIconOpenoff.SetIcon(m_hIconOff);
		}
		 m_ctrlPortStatus.SetWindowText(strStatus);
	}
}

void CDemoDlg::OnButtonClearReciArea() 
{
	// TODO: Add your control notification handler code here
	m_ReceiveData.Empty();
	UpdateData(FALSE);
}

void CDemoDlg::OnButtonStopdisp() 
{
	// TODO: Add your control notification handler code here
	m_bStopDispRXData=!m_bStopDispRXData;
	if(m_bStopDispRXData)
		m_ctrlStopDisp.SetWindowText("������ʾ");
	else
		m_ctrlStopDisp.SetWindowText("ֹͣ��ʾ");
}

void CDemoDlg::OnButtonClearrecasenda() 
{
	// TODO: Add your control notification handler code here
	m_strSendData.Empty();
	UpdateData(FALSE);
	
}

long TX_count=0;

void CDemoDlg::OnButtonManualsend() 
{
	// TODO: Add your control notification handler code here
	if(m_Port.m_hComm==NULL)
	{
		m_ctrlAutoSend.SetCheck(0);
		AfxMessageBox("����û�д򿪣���򿪴���");
		return;
	}
	else
	{
		UpdateData(TRUE);
		
		if(m_ctrlHexSend.GetCheck())//����ʮ������
		{
			char data[512];
			int len=Str2Hex(m_strSendData,data);
			m_Port.WriteToPort(data,len);
			TX_count+=(long)((m_strSendData.GetLength()+1)/3);
			// m_Port.WriteToPort(hexdata);	
		}
		else //����ASCII�ı�
		{
			 m_Port.WriteToPort((LPCTSTR)m_strSendData);	//��������
			 TX_count+=m_strSendData.GetLength();
		}
		CString strTemp;  
		strTemp.Format("TX:%d",TX_count);
	 	m_ctrlTXCount.SetWindowText(strTemp);// ��ʾ����
	}
}

//��һ���ַ�����Ϊʮ�����ƴ�ת��Ϊһ���ֽ����飬�ֽڼ���ÿո�ָ���
//����ת������ֽ����鳤�ȣ�ͬʱ�ֽ����鳤���Զ����á�
int CDemoDlg::Str2Hex(CString str, char *data)
{
	int t,t1;
	int rlen=0;//�ֽ����鳤��
	int len=str.GetLength();
	//data.SetSize(len/2);
	for(int i=0;i<len;)
	{
		char l;
		char h=str[i];
		if(h==' ')
		{
			i++;
			continue;
		}
		i++;
		if(i>=len)
			break;
		l=str[i];
		t=HexChar(h);
		t1=HexChar(l);
		if((t==16)||(t1==16))
			break;
		else 
			t=t*16+t1;//?????
		i++;
		data[rlen]=(char)t;
		rlen++;
	}
	return rlen;

}

char CDemoDlg::HexChar(char c)
{
	if((c>='0')&&(c<='9'))
		return c-0x30;
	else if((c>='A')&&(c<='F'))
		return c-'A'+10;
	else if((c>='a')&&(c<='f'))
		return c-'a'+10;
	else 
		return 0x10;

}

void CDemoDlg::OnCheckAutosend() 
{
	// TODO: Add your control notification handler code here
	m_bAutoSend=!m_bAutoSend;
	if(m_bAutoSend)
	{
		if(m_Port.m_hComm==NULL)
		{
			m_bAutoSend=!m_bAutoSend;
			m_ctrlAutoSend.SetCheck(0);
			AfxMessageBox("����û�д򿪣���򿪴���");
			return;
		}
		else
			SetTimer(1,m_nCycleTime,NULL);//���õݶ�ʱ��1
	}
	else
	{
		KillTimer(1);//�ص���ʱ��
	}
}

void CDemoDlg::OnChangeEditCycletime() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CEdit* pEdit=(CEdit*)GetDlgItem(IDC_EDIT_CYCLETIME);
	CString strText;
	pEdit->GetWindowText(strText);
	m_nCycleTime=atoi(strText);
}

void CDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	m_ctrlAutoSend.SetCheck(0);  //ǿ�йر��Զ�����
	KillTimer(1);   //�رն�ʱ��
	KillTimer(4);
	m_Port.ClosePort();  //�رմ���
	m_ReceiveData.Empty();  //��ս��������ַ��� 

}

void CDemoDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString strStatus;
	switch(nIDEvent)
	{
	case 1:
		OnButtonManualsend();
		break;
	/*case 2:
		// m_ctrlSavePath.SetWindowText(m_strCurPath);
	    KillTimer(2);
		break;*/
	case 3:
		m_ctrlManualSend.EnableWindow(TRUE);
		m_ctrlAutoSend.EnableWindow(TRUE);
		// m_ctrlSendFile.EnableWindow(TRUE);
		// m_strSendFilePathName=m_strTempSendFilePathName;
		// m_ctrlEditSendFile.SetWindowText(m_strSendFilePathName);//m_strSendFilePathName
		KillTimer(3);

		if(!(m_ctrlAutoSend.GetCheck()))
		{
			if (m_Port.InitPort(this, m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits,m_dwCommEvents,512))
			{
				m_Port.StartMonitoring();
				strStatus.Format("STATUS��COM%d OPENED��%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
				m_ctrlIconOpenoff.SetIcon(m_hIconRed);
			}
			else
			{
				AfxMessageBox("Failed to reset send buffer size!");
				m_ctrlIconOpenoff.SetIcon(m_hIconOff);
			}
			m_ctrlPortStatus.SetWindowText(strStatus);
		}
		break;
/*	case 4:
		// m_animIcon.ShowNextImage();
		// break;*/
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
	
}

void CDemoDlg::OnChangeEditSend() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

}

static long rxdatacount=0;  //�ñ������ڽ����ַ�����

LONG CDemoDlg::OnCommunication(WPARAM ch, LPARAM port)
{
	if (port <= 0 || port > 4)
		return -1;
	rxdatacount++;   //���յ��ֽڼ���
	CString strTemp;
	strTemp.Format("%ld",rxdatacount);
	strTemp="RX:"+strTemp;
	m_ctrlRXCOUNT.SetWindowText(strTemp);  //��ʾ���ռ���
	
	if(m_bStopDispRXData)   //���ѡ���ˡ�ֹͣ��ʾ���������ݣ��򷵻�
		return -1;          //ע�⣬��������£��������ڼ�����ֻ�ǲ���ʾ
	//�������ˡ��Զ���ա�����ﵽ50�к��Զ���ս��ձ༭������ʾ������
	/*if((m_ctrlAutoClear.GetCheck())&&(m_ctrlReceiveData.GetLineCount()>=50))
	{
		m_ReceiveData.Empty();
		UpdateData(FALSE);
	}*/
	//���û�С��Զ���ա��������дﵽ400��Ҳ�Զ����
	//��Ϊ���ݹ��࣬Ӱ������ٶȣ���ʾ�����CPUʱ��Ĳ���
	if(m_ctrlReceiveData.GetLineCount()>400)
	{
		m_ReceiveData.Empty();
		m_ReceiveData="***The Length of the Text is too long, Emptied Automaticly!!!***\r\n";        
		UpdateData(FALSE);
	}

	//���ѡ����"ʮ��������ʾ"������ʾʮ������ֵ
	CString str;
	if(m_ctrlHexReceive.GetCheck()) 
		str.Format("%02X ",ch);
	else 
		str.Format("%c",ch);
	//�����ǽ����յ��ַ������ַ�������������ʱ�ܶ�
	//�����ǵ�������Ҫ������ļ�������û����List Control
	int nLen=m_ctrlReceiveData.GetWindowTextLength();
	m_ctrlReceiveData.SetSel(nLen, nLen);
	m_ctrlReceiveData.ReplaceSel(str);

 	nLen+=str.GetLength();

    m_ReceiveData+=str;
	return 0;
}

void CDemoDlg::OnButtonSyn0() //ͬ��1
{
	// TODO: Add your control notification handler code here
	CString str;//��ʱ����
	str=m_strSendData;
    m_strSendData = SY0 ;
	StrtoHex(m_strSendData);
	CountDisplay(m_strSendData);
	m_strSendData=str;
	CurrentControlStatus(0);


/*	CString strTemp;
    str="ͬ��0";  
	strTemp.Format("��ǰ�˶�״̬:%s",str);
	m_ctrlControlStatus.SetWindowText(strTemp);// ��ʾ��ǰ�˶�״̬
*/
}

void CDemoDlg::OnButtonSyn1() //ͬ��1
{
	// TODO: Add your control notification handler code here
	// char data[512]; 
	CString str;//��ʱ����
	str=m_strSendData;
	m_strSendData=SY1;
	StrtoHex(m_strSendData);

	CountDisplay(m_strSendData);
	m_strSendData=str;
	CurrentControlStatus(1);

}

void CDemoDlg::OnButtonSyn2() //ͬ��2
{
	// TODO: Add your control notification handler code here
	// char data[512]; 
	CString str;//��ʱ����
	str=m_strSendData;
	m_strSendData=SY2;
	StrtoHex(m_strSendData);
	CountDisplay(m_strSendData);
	m_strSendData=str;
	CurrentControlStatus(2); 
}

void CDemoDlg::OnButtonStartmotor() //�������
{
	// TODO: Add your control notification handler code here
	// char data[512]; 
	CString str;//��ʱ����
	str=m_strSendData;
	m_strSendData=STARTMOTOR;
	StrtoHex(m_strSendData);

	CountDisplay(m_strSendData);
	m_strSendData=str;
	CurrentControlStatus(041); 
}

void CDemoDlg::OnButtonUrgencystop() 
{
	// TODO: Add your control notification handler code here
	// char data[512];
	CString str;//��ʱ����
	str=m_strSendData;
	m_strSendData=URGENCYSTOP;
	StrtoHex(m_strSendData);

	CountDisplay(m_strSendData);
	m_strSendData=str;
	CurrentControlStatus(055); 

}

void CDemoDlg::OnButtonOnward() //ǰ��
{
	// TODO: Add your control notification handler code here
	CString str;//��ʱ����
	str=m_strSendData;
	m_strSendData=ONWARD;
	StrtoHex(m_strSendData);
	CountDisplay(m_strSendData);
	m_strSendData=str;
	CurrentControlStatus(111);
}

void CDemoDlg::OnButtonReverse() 
{
	// TODO: Add your control notification handler code here
	CString str;//��ʱ����
	str=m_strSendData;
	m_strSendData=REVERSE;
	StrtoHex(m_strSendData);

	CountDisplay(m_strSendData);
	m_strSendData=str;
	CurrentControlStatus(110);
}

void CDemoDlg::OnButtonTurnleft()  //��ת
{
	// TODO: Add your control notification handler code here
    CString str;//��ʱ����
	str=m_strSendData;
	m_strSendData=TURNLEFT;
	StrtoHex(m_strSendData);

	CountDisplay(m_strSendData);
	m_strSendData=str;
	CurrentControlStatus(121);  
}

void CDemoDlg::OnButtonTurnright() 
{
	// TODO: Add your control notification handler code here
	CString str;//��ʱ����
	str=m_strSendData;
	m_strSendData=TURNRIGHT;
	StrtoHex(m_strSendData);

	CountDisplay(m_strSendData);
	m_strSendData=str;
	CurrentControlStatus(120);
}

void CDemoDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	CString str;//��ʱ����
	str=m_strSendData;
	m_strSendData=STOP;
	StrtoHex(m_strSendData);

	CountDisplay(m_strSendData);
	m_strSendData=str;
	CurrentControlStatus(29);

}

void CDemoDlg::OnButtonClosemotor() // 4������رյ��
{
	// TODO: Add your control notification handler code here
	// char data[512]; 
	CString str;//��ʱ����
	str=m_strSendData;
	m_strSendData=CLOSEMOTOR;
	StrtoHex(m_strSendData);

	CountDisplay(m_strSendData);
	m_strSendData=str;
	CurrentControlStatus(040);
   
}

void CDemoDlg::CountDisplay(CString str)//������ʾ������ֽ���
{   
	TX_count+=(long)((str.GetLength()+1)/3);
	CString strTemp;  
	strTemp.Format("TX:%d",TX_count);
	m_ctrlTXCount.SetWindowText(strTemp);// ��ʾ����

}

void CDemoDlg::OnButtonCountreset() 
{
	// TODO: Add your control notification handler code here
	rxdatacount=0;
	CString strTemp;
	strTemp.Format("%ld",rxdatacount);
	strTemp="RX:"+strTemp;
	m_ctrlRXCOUNT.SetWindowText(strTemp);
	TX_count=0;
	strTemp.Format("%ld",TX_count);
	strTemp="TX:"+strTemp;
	m_ctrlTXCount.SetWindowText(strTemp);
}



void CDemoDlg::OnSelendokComboDatabits() 
{
	// TODO: Add your control notification handler code here
	//char temp;
	int i=m_DataBits.GetCurSel();
	switch(i)
	{
	case 0:
		i=8;
		break;
	case 1:
		i=7;
		break;
	case 2:
		i=6;
		break;
	}
	m_nDatabits=i;
	CString strStatus;
	if (m_Port.InitPort(this, m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits,m_dwCommEvents,512))
	{
		if(!m_bOpenPort)
		{
			m_Port.StartMonitoring();
			m_ctrlIconOpenoff.SetIcon(m_hIconRed);
			strStatus.Format("STATUS��COM%d OPENED��%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
		}
		else
		{
			m_ctrlIconOpenoff.SetIcon(m_hIconOff);
			strStatus.Format("STATUS��COM%d CLOSED��%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
		}
		m_ctrlPortStatus.SetWindowText(strStatus);

	}
	else
	{
		AfxMessageBox("û�гɹ���������");
		m_ctrlIconOpenoff.SetIcon(m_hIconOff);
	}
}



void CDemoDlg::OnSelendokComboParity() 
{
	// TODO: Add your control notification handler code here
	char temp;
	int i=m_Parity.GetCurSel();
	switch(i)
	{
	case 0:
		temp='N';
		break;
	case 1:
		temp='O';
		break;
	case 2:
		temp='E';
		break;
	}
	m_cParity=temp;
	CString strStatus;
	if (m_Port.InitPort(this, m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits,m_dwCommEvents,512))
	{
		if(!m_bOpenPort)
		{
			m_Port.StartMonitoring();
			m_ctrlIconOpenoff.SetIcon(m_hIconRed);
			strStatus.Format("STATUS��COM%d OPENED��%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
		}
		else
		{
			m_ctrlIconOpenoff.SetIcon(m_hIconOff);
			strStatus.Format("STATUS��COM%d CLOSED��%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
		}
		m_ctrlPortStatus.SetWindowText(strStatus);

	}
	else
	{
		AfxMessageBox("û�гɹ���������");
		m_ctrlIconOpenoff.SetIcon(m_hIconOff);
	}

}

void CDemoDlg::OnSelendokComboStopbits() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	int i=m_StopBits.GetCurSel();
	switch(i)
	{
	case 0:
		i=1;
		break;
	case 1:
		i=2;
		break;
	}
	m_nStopbits=i;
	CString strStatus;
	if (m_Port.InitPort(this, m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits,m_dwCommEvents,512))
	{
		if(!m_bOpenPort)
		{
			m_Port.StartMonitoring();
			m_ctrlIconOpenoff.SetIcon(m_hIconRed);
			strStatus.Format("STATUS��COM%d OPENED��%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
		}
		else
		{
			m_ctrlIconOpenoff.SetIcon(m_hIconOff);
			strStatus.Format("STATUS��COM%d CLOSED��%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
		}
		m_ctrlPortStatus.SetWindowText(strStatus);

	}
	else
	{
		AfxMessageBox("û�гɹ���������");
		m_ctrlIconOpenoff.SetIcon(m_hIconOff);
	}
}

void CDemoDlg::OnSelendokComboComselect() 
{
	// TODO: Add your control notification handler code here
		if(m_Port.m_hComm!=NULL)
	{
		m_Port.ClosePort();
	}

	m_nCom=m_Com.GetCurSel()+1;
	CString strStatus;
	if (m_Port.InitPort(this, m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits,m_dwCommEvents,512))
	{
		if(!m_bOpenPort)
		{
			m_Port.StartMonitoring();
			m_ctrlIconOpenoff.SetIcon(m_hIconRed);
			strStatus.Format("STATUS��COM%d OPENED��%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
		}
		else
		{
			m_ctrlIconOpenoff.SetIcon(m_hIconOff);
			strStatus.Format("STATUS��COM%d CLOSED��%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
		}
		m_ctrlPortStatus.SetWindowText(strStatus);

	}
	else
	{
		m_ctrlIconOpenoff.SetIcon(m_hIconOff);
		AfxMessageBox("û�з��ִ˴��ڻ�ռ��");
	}

}

void CDemoDlg::OnSelendokComboBaud() 
{
	// TODO: Add your control notification handler code here
		CString temp;
	int i=m_Baud.GetCurSel();
	switch(i)
	{
	case 0:
		i=300;
		break;
	case 1:
		i=600;
		break;
	case 2:
		i=1200;
		break;
	case 3:
		i=2400;
		break;
	case 4:
		i=4800;
		break;
	case 5:
		i=9600;
		break;
	case 6:
		i=19200;
		break;
	case 7:
		i=38400;
		break;
	case 8:
		i=43000;
		break;
	case 9:
		i=56000;
		break;
	case 10:
		i=57600;
		break;
	case 11:
		i=115200;
		break;
	default:
		break;

	}
	m_nBaud=i;
	CString strStatus;
	if (m_Port.InitPort(this, m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits,m_dwCommEvents,512))
	{
		if(!m_bOpenPort)
		{
			m_Port.StartMonitoring();
			m_ctrlIconOpenoff.SetIcon(m_hIconRed);
			

			strStatus.Format("STATUS��COM%d OPENED��%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
		}
		else
		{
			m_ctrlIconOpenoff.SetIcon(m_hIconOff);
			strStatus.Format("STATUS��COM%d CLOSED��%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
		}
		m_ctrlPortStatus.SetWindowText(strStatus);

	}
	else
	{
		AfxMessageBox("û�гɹ���������");
		m_ctrlIconOpenoff.SetIcon(m_hIconOff);

	}

}

void CDemoDlg::CurrentControlStatus(int ControlStatus)
{  
	CString str;
	CString strTemp;
	switch(ControlStatus)
	{
	case 0:	
		str="ͬ��0";  
		strTemp.Format("��ǰ�˶�״̬:%s",str);
		m_ctrlControlStatus.SetWindowText(strTemp);// ��ʾ��ǰ�˶�״̬
		break;
	case 1:
			if(flag1==1)
			{
				str="ͬ��1";  
				strTemp.Format("��ǰ�˶�״̬:%s",str);
				flag1=0;

			}
			else
			{
				str="�Ѵ򿪷�����";  
				strTemp.Format("��ǰ�˶�״̬:%s",str);
				flag1=1;

		}
		m_ctrlControlStatus.SetWindowText(strTemp);// ��ʾ��ǰ�˶�״̬
		break;
	case 2:
			if(flag2==1)
			{
				str="ͬ��2";  
				strTemp.Format("��ǰ�˶�״̬:%s",str);
				flag2=0;

			}
			else
			{
				str="�ѹرշ�������ͻ��˵�����";  
				strTemp.Format("��ǰ�˶�״̬:%s",str);
				flag2=1;

		}
		m_ctrlControlStatus.SetWindowText(strTemp);// ��ʾ��ǰ�˶�״̬
		break;

	case 110:
		str="����";  
		strTemp.Format("��ǰ�˶�״̬:%s",str);
		m_ctrlControlStatus.SetWindowText(strTemp);// ��ʾ��ǰ�˶�״̬
		break;
	case 111:
		str="ǰ��";  
		strTemp.Format("��ǰ�˶�״̬:%s",str);
		m_ctrlControlStatus.SetWindowText(strTemp);// ��ʾ��ǰ�˶�״̬
		break;

	case 121:
		str="��ת";  
		strTemp.Format("��ǰ�˶�״̬:%s",str);
		m_ctrlControlStatus.SetWindowText(strTemp);// ��ʾ��ǰ�˶�״̬
       	break;
    case 120:
		str="��ת";  
		strTemp.Format("��ǰ�˶�״̬:%s",str);
		m_ctrlControlStatus.SetWindowText(strTemp);// ��ʾ��ǰ�˶�״̬
		break;

	case 041:
		str="���������";  
		strTemp.Format("��ǰ�˶�״̬:%s",str);
		m_ctrlControlStatus.SetWindowText(strTemp);// ��ʾ��ǰ�˶�״̬
		break;
	case 040:
		str="����ѹر�";  
		strTemp.Format("��ǰ�˶�״̬:%s",str);
		m_ctrlControlStatus.SetWindowText(strTemp);// ��ʾ��ǰ�˶�״̬
	    break;

	case 29:
		str="ֹͣ";  
		strTemp.Format("��ǰ�˶�״̬:%s",str);
		m_ctrlControlStatus.SetWindowText(strTemp);// ��ʾ��ǰ�˶�״̬
		break;		
	case 055:
		str="����ֹͣ";  
		strTemp.Format("��ǰ�˶�״̬:%s",str);
		m_ctrlControlStatus.SetWindowText(strTemp);// ��ʾ��ǰ�˶�״̬
 		break;		

	case 256:
		str="״̬�Ѿ���λ";  
		strTemp.Format("��ǰ�˶�״̬:%s",str);
		m_ctrlControlStatus.SetWindowText(strTemp);// ��ʾ��ǰ�˶�״̬
    
		break;
	default:
		str="����";  
		strTemp.Format("��ǰ�˶�״̬:%s",str);
		m_ctrlControlStatus.SetWindowText(strTemp);
	}
	UpdateData(FALSE);

}

void CDemoDlg::StrtoHex(CString str)
{
	char data[512]; 
	int len=Str2Hex(m_strSendData,data);
	m_Port.WriteToPort(data,len);
}

void CDemoDlg::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
    OnButtonClosemotor();// �رյ��
	flag2=0;
	OnButtonSyn2();// �ر�����
	OnButtonCountreset();
    OnDestroy();//�ͷ���Դ
	// OnInitDialog();// ��ʼ���Ի���
	m_Com.SetCurSel(0);
	m_Baud.SetCurSel(5);
	m_Parity.SetCurSel(0);
	m_DataBits.SetCurSel(0);
	m_StopBits.SetCurSel(1);
    m_ctrlHexSend.SetCheck(1);
	m_ctrlHexReceive.SetCheck(1);

	CString strStatus;
	m_Port.InitPort(this, m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits,m_dwCommEvents,512);
	m_Port.StartMonitoring();
	strStatus.Format("STATUS��COM%d OPENED��%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
	m_ctrlIconOpenoff.SetIcon(m_hIconRed);
    m_ctrlPortStatus.SetWindowText(strStatus);
	CEdit* pEdit=(CEdit*)GetDlgItem(IDC_EDIT_CYCLETIME);
	CString strText;
	m_nCycleTime=1000;
	strText.Format("%d",m_nCycleTime);
	pEdit->SetWindowText(strText);   //Display cycle time

	m_strSendData="��ӭ��ʹ�ø���ʾ�����";
	char cr=13,lf=10;
	m_strSendData+=cr+lf;

	// m_ctrlAutoClear.SetCheck(1);
	// m_ctrlEditSendFile.SetWindowText("No File Selected!");

	// m_animIcon.SetImageList(IDB_ANIM_IMGLIST,4,RGB(0,0,0));   
	SetTimer(4,200,NULL);
	ShowWindow(SW_SHOW); 

	CurrentControlStatus(256);// ��ʾ��ǰ״̬
	OnButtonCountreset();
	UpdateData(FALSE);
}

BOOL CDemoDlg::PreTranslateMessage(MSG *pMsg)
{
	

// TODO: Add your specialized code here and/or call the base class

//�ػ�ESC�ͻس��������ⰴ�´˼�ʱ�رնԻ���

	if (pMsg->message == WM_KEYDOWN)

	{   LPARAM  temp;
		temp=pMsg->wParam;
		switch(temp) 
		{

			case VK_ESCAPE://����ESC��
				return true;
				break;
			case VK_RETURN:
				// (pMsg->wParam==VK_RETURN) */
				return true; 
				break;


			case VK_UP :// ǰ��
				OnButtonOnward();
				break;
			case VK_DOWN:
				OnButtonReverse();
				break;
		
			case VK_LEFT:
                OnButtonTurnleft();
				break;

			case VK_RIGHT:
				OnButtonTurnright();
				break;

			case VK_SPACE:
				OnButtonStop();
				return true; 

				break;
		default:
			return 0;
			break;
		}

	/*if (pMsg->wParam==VK_ESCAPE):

		return true; 

	 // if(pMsg->wParam==VK_RETURN) */

	// 	return true; 

	}

	return CDialog::PreTranslateMessage(pMsg);

	
}

void CDemoDlg::OnButtoncReverse() 
{
	// TODO: Add your control notification handler code here
	
}
