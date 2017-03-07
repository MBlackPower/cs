// ReadCompassView.cpp : implementation of the CReadCompassView class
//

#include "stdafx.h"
#include "ReadCompass.h"

#include "ReadCompassSet.h"
#include "ReadCompassDoc.h"
#include "ReadCompassView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define CR 0X0D
/////////////////////////////////////////////////////////////////////////////
// CReadCompassView

double m_heading[2000];
int m_num=0;

IMPLEMENT_DYNCREATE(CReadCompassView, CRecordView)

BEGIN_MESSAGE_MAP(CReadCompassView, CRecordView)
	//{{AFX_MSG_MAP(CReadCompassView)
	ON_BN_CLICKED(IDC_BUTTON1, OnOpenComm)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadCompassView construction/destruction

CReadCompassView::CReadCompassView()
	: CRecordView(CReadCompassView::IDD)
{
	//{{AFX_DATA_INIT(CReadCompassView)
	m_pSet = NULL;
	m_strRXData = _T("");
		m_strPortRXData2="";
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CReadCompassView::~CReadCompassView()
{
}

void CReadCompassView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadCompassView)
	DDX_Control(pDX, IDC_BUTTON1, m_ctrlOpenPort);
	DDX_Text(pDX, IDC_EDIT3, m_strRXData);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	DDX_FieldText(pDX, IDC_EDIT2, m_pSet->m_temperature, m_pSet);
	//}}AFX_DATA_MAP
}

BOOL CReadCompassView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CReadCompassView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_readCompassSet;
	CRecordView::OnInitialUpdate();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CReadCompassView printing

BOOL CReadCompassView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CReadCompassView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CReadCompassView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CReadCompassView diagnostics

#ifdef _DEBUG
void CReadCompassView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CReadCompassView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CReadCompassDoc* CReadCompassView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReadCompassDoc)));
	return (CReadCompassDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReadCompassView database support
CRecordset* CReadCompassView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CReadCompassView message handlers

BEGIN_EVENTSINK_MAP(CReadCompassView, CRecordView)
    //{{AFX_EVENTSINK_MAP(CReadCompassView)
	ON_EVENT(CReadCompassView, IDC_MSCOMM1, 1 /* OnComm */, OnComm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CReadCompassView::OnComm() 
{
	// TODO: Add your control notification handler code here
    VARIANT variant_inp;
    COleSafeArray safearray_inp;//COleSafeArray����������������ά��������
    LONG len,k;
    BYTE rxdata[2048]; //����BYTE���� An 8-bit integerthat is not signed.
    CString strtemp;//,m_strRXData1;//,m_strRXData2;

	static char checksum=0;
	static int flag;
	static char c1,c2;
	static long countdraw=0;

   if(m_ctrlComm.GetCommEvent()==2) //�¼�ֵΪ2��ʾ���ջ����������ַ�
	{              ////////��������Ը����Լ���ͨ��Э����봦�����
        
	       variant_inp=m_ctrlComm.GetInput(); //��������
           safearray_inp=variant_inp; //VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
           len=safearray_inp.GetOneDimSize(); //�õ���Ч���ݳ���//����һάCOleSafeArray�����е�Ԫ����
           for(k=0;k<len;k++)
            safearray_inp.GetElement(&k,rxdata+k);//ת��ΪBYTE������
		   for(k=0;k<len;k++) //������ת��ΪCstring�ͱ���
		   {
            BYTE bt=*(char*)(rxdata+k); //�ַ���

			strtemp.Format("%c",bt); 
			m_strPortRXData2 += strtemp;
			m_strRXData+=strtemp; //������ձ༭���Ӧ�ַ��� 
//			UpdateData(FALSE);


			   switch(bt)
			   {
			   case '$':
				   checksum=0;
				   flag=0;
				   break;
			   case'*':
				   flag=2;
				   c2=checksum & 0x0f;
				   c1=( (checksum >>4 ) & 0x0f);
				   if(c1<10)
					   c1+='0';
				   else
					   c1+='A'-10;
				   if(c2<10)
					   c2+='0';
				   else
					   c2+='A'-10;
				   break;
			   case CR:
				   m_strPortRXData2.Empty();
				   break;
			   default:
				   if(flag>0)
				   {
					   m_strChecksum2+=bt;
					   if(flag==1)
					   {
						   CString strCheck="";
						   strCheck.Format("%c%c",c1,c2);
						   if(strCheck!=m_strChecksum2)
						   {
							   m_strRXData.Empty();
						   }
						   else
						   {
		
							   if(m_strRXData.GetLength() >= 200)
								   m_strRXData.Empty();
							   UpdateData(FALSE);
							  
							   if(!m_pSet->IsEOF()) 
								   m_pSet->MoveLast();////////
							   m_pSet->AddNew();
 							   UpdateData(TRUE);

							   CString m_strRXData1;
							   
							   char tbuf[10];
							   
							   CString strTemp1;
							   strTemp1 = m_strPortRXData2.Mid(8,5);
							   char *temp1= (char*) ((LPCSTR)strTemp1);
							   tbuf[0]=temp1[0];
							   tbuf[1]=temp1[1]; 
							   tbuf[2]=temp1[2];
							   tbuf[3]=temp1[3];
							   tbuf[4]=0;
							   m_pSet->m_temperature=strTemp1;
							   m_heading[m_num]=atof(tbuf);
							   m_pSet->m_number++;
							   UpdateData(FALSE);
							   if (m_pSet->CanUpdate())
							   {
                				if(!m_pSet->Update()) 
									AfxMessageBox(_T("�����¼�¼ʧ��!"));
							   }
							   if(!m_pSet->IsEOF())
							   {
									 m_pSet->MoveLast();
							   }
							   m_num++;

							   countdraw++;
							//   if((countdraw%10)==0)
							   {
								CReadCompassDoc *pDoc=GetDocument();////ÿ��һ���жϼ���һ���ػ�
								pDoc->UpdateAllViews(NULL);
								
							   }
						   }
						   m_strChecksum2.Empty();
					   }
					   flag--;
				   }
				   else
					   checksum=checksum^bt;
				   break;
			   }
		   }	
     }
}

void CReadCompassView::OnOpenComm() 
{
	// TODO: Add your control notification handler code here
	m_bOpenPort=!m_bOpenPort;
	if(m_bOpenPort)
	{
		m_ctrlOpenPort.SetWindowText("�򿪴���");
		if(m_ctrlComm.GetPortOpen())
          m_ctrlComm.SetPortOpen(FALSE);
	}
	else
	{
		m_ctrlOpenPort.SetWindowText("�رմ���");
		
		m_ctrlComm.SetCommPort(1); //ѡ��com1
		m_ctrlComm.SetSettings("9600,n,8,1");
        if( !m_ctrlComm.GetPortOpen())
                  m_ctrlComm.SetPortOpen(TRUE);//�򿪴���
        else
			AfxMessageBox("û�з��ִ˴��ڻ�ռ��");

       m_ctrlComm.SetInputMode(1); //1����ʾ�Զ����Ʒ�ʽ��ȡ����
       m_ctrlComm.SetRThreshold(1); 
 //����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼�
       m_ctrlComm.SetInputLen(0); //���õ�ǰ���������ݳ���Ϊ0
       m_ctrlComm.GetInput();//��Ԥ����			
	}	
}
