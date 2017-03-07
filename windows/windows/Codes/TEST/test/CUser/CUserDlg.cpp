// CUserDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "CUser.h"
#include "CUserDlg.h"
#include ".\cuserdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCUserDlg �_�C�A���O



CCUserDlg::CCUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCUserDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCUserDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CCUserDlg ���b�Z�[�W �n���h��

BOOL CCUserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
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

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
	
	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void CCUserDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CCUserDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CCUserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "..\TestDll\TestDll\TestDll.h"

void CCUserDlg::OnBnClickedOk()
{
//	CTestDllApp tdllapp;

	//����DLL����
	typedef void (_cdecl *GETHOSTNAME)(LPTSTR strHostName);
	typedef void (_cdecl *GETSYSTEMTYPE)(char * strSystemType);
	typedef void (_cdecl *GETIPADDRESSLIST)(char ** lpIPList,DWORD *lpNumber);

	//���������啿
	HMODULE hTestDLL = NULL;
	GETHOSTNAME GetHostName = NULL;
	GETSYSTEMTYPE GetSystemType = NULL;
	GETIPADDRESSLIST GetIpAddressList = NULL;

	// ��????��?
	hTestDLL = LoadLibrary("D:\\test\\TestDll\\TestDll\\Debug\\TestDLL.dll");
	if(hTestDLL == NULL)\
	{
		printf("cannot load LCDDLL.dll\n");
		exit(0);
	}

	/*** �Q��?�������I���� ****/
	//�n?����
	GetHostName = (GETHOSTNAME)GetProcAddress(hTestDLL,"GetHostName");
	if(GetHostName==NULL)
	{
		printf("cannot load process GetHostName\n");
		FreeLibrary(hTestDLL);
		exit(1);
	}

	//����n??�^
	GetSystemType = (GETSYSTEMTYPE)GetProcAddress(hTestDLL,"GetSystemType");
	if(GetSystemType==NULL)
	{
		printf("cannot load process GetSystemType\n");
		FreeLibrary(hTestDLL);
		exit(1);
	}

	//IP�n����\
	GetIpAddressList = (GETIPADDRESSLIST)GetProcAddress(hTestDLL,"GetIPAddressList");
	if(GetSystemType==NULL)
	{
		printf("cannot load process GetIpAddressList\n");
		FreeLibrary(hTestDLL);
		exit(1);
	}

	/*** �g�pLPTSTR�a�g�pchar*��?�I���ʐ���?�I ***/

	//����햼��
	LPTSTR szHostName = new char[1024];
	(*GetHostName)(szHostName);

	//�摀��n??�^
	char* szSystemType = new char[1024];
	(*GetSystemType)(szSystemType);

	//IP Address List
	DWORD ipListNumber = 0;
	//����������
	//LPTSTR* lpAddress = new LPTSTR[256];
	//����������
	char** lpAddress = new char*[256];
	for(int i=0;i<256;i++)
	{
		lpAddress[i] = NULL;
	}
	(*GetIpAddressList)(lpAddress,&ipListNumber);

	//?���݊E��
//	m_setHostName.SetWindowText(szHostName);
//	m_setSystemType.SetWindowText(szSystemType);

	//��IP�Y����list ��
	for(DWORD i=0;i < ipListNumber;i++)
	{
//		m_IPList.AddString(lpAddress[i]);
	}

//	OnOK();
}
