// FileSpltDlg.cpp : implementation file
//
//Modify by �쾰�� ��2001.2.13
//���ܣ��ļ��ָ�Ϊ1.4M��С��������ϲ���һ��
//
#include "stdafx.h"
#include "FileSplt.h"
#include "FileSpltDlg.h"
#include "DirDialog.h" //Ŀ¼����Ի���

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CWBButton m_OK;
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
	DDX_Control(pDX, IDOK, m_OK);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSpltDlg dialog

CFileSpltDlg::CFileSpltDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSpltDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileSpltDlg)
	m_parts = _T("״̬��ʾ");
	m_path = _T("");
	m_targetpath = _T("");
	m_split = TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileSpltDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSpltDlg)
	DDX_Control(pDX, IDC_PROGRESS, pProgress);
	DDX_Control(pDX, IDC_BUTTON_MERGE, m_buttMerge);
	DDX_Control(pDX, IDCANCEL, m_buttExit);
	DDX_Control(pDX, IDOK, m_buttSplit);
	DDX_Control(pDX, IDC_BROWSE, m_Browse);
	DDX_Control(pDX, IDC_BROWSE2, m_Browse2);
	DDX_Control(pDX, IDC_RADIO3, m_RadioSplit);
	DDX_Control(pDX, IDC_PATH, m_edit);
	DDX_Text(pDX, IDC_PARTS, m_parts);
	DDX_Text(pDX, IDC_PATH, m_path);
	DDX_Text(pDX, IDC_PATH2, m_targetpath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileSpltDlg, CDialog)
	//{{AFX_MSG_MAP(CFileSpltDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_BN_CLICKED(IDC_BUTTON_MERGE, OnButtonMerge)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_BROWSE2, OnBrowse2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSpltDlg message handlers

BOOL CFileSpltDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_split) 
		m_RadioSplit.SetCheck(1);

	CButton *pButtonMerge = (CButton*)(GetDlgItem(IDC_BUTTON_MERGE));
	pButtonMerge->EnableWindow(FALSE);

	m_path =_T("");
	m_filename =_T("");

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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//����λͼ��ť
	m_Browse.LoadBitmaps(IDB_BITMAP2,6, 1, 1, 1, 1 );
	m_Browse.SetFontColor(RGB(240,200,90));
	m_Browse2.LoadBitmaps(IDB_BITMAP2,6, 1, 1, 1, 1 );
	m_Browse2.SetFontColor(RGB(240,200,90));
	m_buttExit.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	m_buttMerge.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	m_buttSplit.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );

	//�ڴ˳�ʼ������ɫ������
	pProgress.SetRange32(1,500);
    pProgress.SetBkColor(RGB(160,180,220));
	pProgress.ShowPercent(true);	
	pProgress.SetPos(500);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileSpltDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileSpltDlg::OnPaint() 
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
HCURSOR CFileSpltDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// �ļ��ϲ����� 
int CFileSpltDlg::MergeMe() 
{
	CWaitCursor wait;
	// constructing these file objects
	CFile destFile;
	// we'll use a CFileException object to get error information
	CFileException ex;

	BYTE buffer[140000];
	DWORD dwRead;
	UINT nCount = 140000;
	UINT newlen = 1400000;
	char buff [20];
	long l = 1;
	CString name;
	CString pref;
	CString newpath;
		
	UpdateData(TRUE);

	//open file for read
	if (!m_path.IsEmpty()) {
		if (!m_SourceFile.Open(m_path, CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary, &ex)) {
			TCHAR szError[1024];
			ex.GetErrorMessage(szError, 1024);
      		::AfxMessageBox(szError);
			m_edit.SetFocus();
			m_edit.SetSel(0, -1);
			return 1;
		}
		//construct new name
		m_filename = m_path.Right((m_path.GetLength() - m_path.ReverseFind('\\')) - 1);
		//close file
		m_SourceFile.Close();
	}

	//constuct a new path name
	newpath = m_path.Left(m_path.GetLength() - m_filename.GetLength());

	if (!m_targetpath.IsEmpty()) {
		//some silly check, that could be chnged
		if (!m_filename.IsEmpty() && m_filename.Left(2) != _T("1_")) {
			::AfxMessageBox(_T("���ϲ���Դ�ļ�������..."), MB_ICONERROR);
			return 1;
		}
		else if(m_filename.IsEmpty()) {
			MessageBox(_T("��ѡ����ϲ���Դ�ļ�."), _T("�ļ��ָ���"), MB_ICONEXCLAMATION);
			return 1;
		}
		//constuct an original file name
		m_filename = m_filename.Right(m_filename.GetLength() - 2);
		m_path = m_targetpath + _T("\\") + m_filename;
		//create target file
		if (!destFile.Open(m_path,  
			CFile::modeWrite		| 
			CFile::shareExclusive	| 
			CFile::typeBinary		| 
			CFile::modeCreate, &ex)) {
			TCHAR szError[1024];
			ex.GetErrorMessage(szError, 1024);
			::AfxMessageBox(szError);
			return 0;
		}
	}
	else if(m_path.IsEmpty())
	{//souce is not there
		MessageBox(_T("��ѡ����ϲ���Դ�ļ�."), _T("�ļ��ָ���"), MB_ICONEXCLAMATION);
		return 1;
	}
	if (m_targetpath.IsEmpty()) {//target is not there
		MessageBox(_T("��ѡ��ϲ���Ҫ���浽��Ŀ���ļ���."), _T("�ļ��ָ���"), MB_ICONEXCLAMATION);
		return 1;
	}
	//do merge 
	do {
		//constuct a new name by dynamicly incrementing prefix
		pref = _ltoa(l, buff, 10);
		pref += _T("_");
		//open file with new name
		if (!m_SourceFile.Open(newpath + pref + m_filename,  
			CFile::modeRead		| 
			CFile::shareExclusive	| 
			CFile::typeBinary, &ex)) {
			TCHAR szError[1024];
			ex.GetErrorMessage(szError, 1024);
			destFile.Close();
			m_path = _T("");
			m_filename = _T("");
//			pProgress.SetPos(0);
			newpath = _T("");
//			m_parts = _T("");
			UpdateData(FALSE);
			//return OK because this f_n is aborting the loop if name is not found
			return 0;
		}
		else
			//constuct a new name 
			name = _T(newpath + pref + m_filename);
		do  {//write into file while it size < than 1.4 MB
			dwRead = m_SourceFile.Read(buffer, nCount);
			destFile.Write(buffer, dwRead);
		}
		//while we can read from source file
		while (dwRead > 0);

		m_SourceFile.Close();

		// Set the range to be 0 to 500.
		pProgress.SetRange(0, 500);
		// Set the position
		for (int i = 0; i < 500; i++)
			pProgress.SetPos(i);
		m_parts = _ltoa(l, buff, 10);
		m_parts += _T("���ļ��Ѻϲ�");
		UpdateData(FALSE);
		l++;
		UpdateWindow();
	}
	while (l < 500);//little bit dirty solution, but you can always improve it!...
		
	return 0;
}
//�ļ��ָ��
int CFileSpltDlg::SplitMe() 
{
	CWaitCursor wait;
	// constructing these file objects
	CFile destFile;
	// we'll use a CFileException object to get error information
	CFileException ex;

	BYTE buffer[140000];
	DWORD dwRead;
	UINT nCount = 140000;
	double newlen = 1400000;
	char buff [20];
	char b [20];
	long l = 1;
	CString name;
	int len = 0;
//	CGradientProgressCtrl *pProgress = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS);

	UpdateData(TRUE);

	//open file for read
	//m_path contain the file path
	if (!m_path.IsEmpty()) {
		if (!m_SourceFile.Open(m_path, CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary, &ex)) {
			TCHAR szError[1024];
			ex.GetErrorMessage(szError, 1024);
      		::AfxMessageBox(szError);
			m_edit.SetFocus();
			m_edit.SetSel(0, -1);
			return 1;
		}
		//get file length
		len = m_SourceFile.GetLength();
	}
	//too lazy to put all "hard coded" strings in string table
	else {
		MessageBox(_T("��ѡ����ָ��Դ�ļ�."), _T("�ļ��ָ���"), MB_ICONEXCLAMATION);
		return 1;
	}
	if (m_targetpath.IsEmpty()) {
		MessageBox(_T("��ѡ��ָ�󱣴浽��Ŀ���ļ���."), _T("�ļ��ָ���"), MB_ICONEXCLAMATION);
		return 1;
	}
	//quick and dirty check for file size
	if (len < 1452001) {
		CString length = _itoa(len, b, 10);
		MessageBox(_T("�ļ�����Ϊ " + length + " �ֽڣ�����1.4M, û�б�Ҫ�ٽ��зָ�."), _T("�ļ��ָ���"), MB_ICONEXCLAMATION);
		m_SourceFile.Close();
		m_path = _T("");
		m_filename = _T("");
		UpdateData(FALSE);
		return 1;
	}

	//do split
	do {
		//constuct a new name dynamicly changing prefix
		name = _ltoa(l, buff, 10);
		name += _T("_");
		CString newpath = m_targetpath + _T("\\");
		if (!destFile.Open(newpath + name + m_SourceFile.GetFileName(),  
			CFile::modeWrite		| 
			CFile::shareExclusive	| 
			CFile::typeBinary		|
			CFile::modeCreate, &ex)) {
			TCHAR szError[1024];
			ex.GetErrorMessage(szError, 1024);
			::AfxMessageBox(szError);
			m_SourceFile.Close();
			return 1;
		}
		do {
			dwRead = m_SourceFile.Read(buffer, nCount);
			destFile.Write(buffer, dwRead);
		}//while size is less than 1.4 MB
		while (dwRead > 0 && destFile.GetLength() < newlen); 
		destFile.Close();
		// Set the range
		pProgress.SetRange(0, len / 1400000);
		// Set the position
		pProgress.SetPos(l);
		m_parts = _ltoa(l , buff, 10);
		m_parts += _T("���ļ�����");
		UpdateData(FALSE);
		l++;
		UpdateWindow();
	}
	while (dwRead > 0);
		// close source
		m_SourceFile.Close();

	m_path = _T("");
	m_filename = _T("");
//	pProgress->SetPos(0);
//	m_parts = _T("");
	UpdateData(FALSE);
	return 0;
}

//ѡ����ָ��ϲ���Դ�ļ�
void CFileSpltDlg::OnBrowse() 
{
	//set filter for split source
	static char BASED_CODE szSplitFilter[] = _T("���ָ��ļ�(*.*)|*.*||");
	//set filter for target source
	static char BASED_CODE szMergeFilter[] = _T("���ϲ��ļ�(1_*.*)|1_*.*||");

	CString filter;
	if (!m_split)
		filter = szMergeFilter;
	else 
		filter = szSplitFilter;

	CFileDialog dlg(TRUE,
					NULL, 
					NULL, 
					OFN_HIDEREADONLY	| 
					OFN_OVERWRITEPROMPT | 
					OFN_FILEMUSTEXIST,
					filter,
					0);

	//set source path
	if (dlg.DoModal() == IDOK) {
		m_path = dlg.GetPathName();
		m_filename = dlg.GetFileName();
		UpdateData(FALSE);
	}
	
}

//��ʼ�ָ��ļ�
void CFileSpltDlg::OnOk() 
{
    //split file
	int error = SplitMe();

	//get result
	if (!error) 
		MessageBox(_T("�ļ��ѱ��ɹ��ָ�!"), _T("�ļ��ָ���"), MB_ICONEXCLAMATION);
		
}

//��ʼ�ϲ��ļ�
void CFileSpltDlg::OnButtonMerge() 
{
    //merge file
	int error = MergeMe();

	//get result
	if (!error) 
		MessageBox(_T("�ļ��ϲ��ɹ�!"), _T("�ļ��ָ���"), MB_ICONEXCLAMATION);
	
}

//ѡ���ļ��ϲ���ѡ��
void CFileSpltDlg::OnRadio4() 
{
  	CButton *pButtonMerge = (CButton*)(GetDlgItem(IDC_BUTTON_MERGE));
	CButton *pButtonSplit = (CButton*)(GetDlgItem(IDOK));
	
	//play with button and edit ctrl states
	pButtonSplit->EnableWindow(FALSE);
	pButtonMerge->EnableWindow(TRUE);
	m_split = FALSE;
	m_path = _T("");
	UpdateData(FALSE);	
}

//ѡ���ļ��ָѡ��
void CFileSpltDlg::OnRadio3() 
{
	CButton *pButtonMerge = (CButton*)(GetDlgItem(IDC_BUTTON_MERGE));
	CButton *pButtonSplit = (CButton*)(GetDlgItem(IDOK));
	
	//play with button and edit ctrl states
	pButtonSplit->EnableWindow(TRUE);
	pButtonMerge->EnableWindow(FALSE);
	m_split = TRUE;
	m_path = _T("");
	UpdateData(FALSE);	
}

//ѡ��Ŀ���ļ���
void CFileSpltDlg::OnBrowse2() 
{
  CDirDialog	dlg;
	if (dlg.DoBrowse(this) == IDOK) {
		//set target path
		m_targetpath = dlg.m_strPath;
		UpdateData(FALSE);
	}	
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//����λͼ��ť
	m_OK.LoadBitmaps(IDB_BITMAP1,5, 5, 5, 5, 4 );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
