VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form Phone 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "����绰��ʾ"
   ClientHeight    =   1920
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3750
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1920
   ScaleWidth      =   3750
   StartUpPosition =   3  '����ȱʡ
   Begin MSWinsockLib.Winsock Listen 
      Left            =   1200
      Top             =   120
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin MSWinsockLib.Winsock Connect 
      Left            =   2040
      Top             =   120
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.CommandButton Command3 
      Caption         =   "�˳�"
      Height          =   495
      Left            =   2640
      TabIndex        =   5
      ToolTipText     =   "������������"
      Top             =   840
      Width           =   855
   End
   Begin VB.CommandButton Command2 
      Caption         =   "�һ�"
      Enabled         =   0   'False
      Height          =   495
      Left            =   1440
      TabIndex        =   4
      ToolTipText     =   "�Ҷ���Զ������������"
      Top             =   840
      Width           =   975
   End
   Begin VB.CommandButton Command1 
      Caption         =   "����"
      Height          =   495
      Left            =   240
      TabIndex        =   3
      ToolTipText     =   "���������ַ����Զ������"
      Top             =   840
      Width           =   975
   End
   Begin VB.TextBox Text1 
      Height          =   270
      Left            =   960
      TabIndex        =   1
      ToolTipText     =   "������Է��������� IP ��ַ"
      Top             =   240
      Width           =   2535
   End
   Begin MSComctlLib.StatusBar StatusBar1 
      Align           =   2  'Align Bottom
      Height          =   315
      Left            =   0
      TabIndex        =   0
      Top             =   1605
      Width           =   3750
      _ExtentX        =   6615
      _ExtentY        =   556
      Style           =   1
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
   End
   Begin VB.Label Label1 
      Caption         =   "��������"
      Height          =   270
      Left            =   240
      TabIndex        =   2
      Top             =   285
      Width           =   855
   End
End
Attribute VB_Name = "Phone"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'���嶯̬�⺯��
'phone.dll Ϊ�Զ���DLL�⣬��VC++���ɣ����� StartPhone �� ClosePhone ��������
Private Declare Function StartPhone Lib "phone" (ByVal Name As String, ByVal LocalPort As Long, ByVal RemotePort As Long) As Long
Private Declare Sub ClosePhone Lib "phone" ()
'���峣��
Const TcpPort As Long = 2048
Const LocalPort As Long = 2049
Const RemotePort As Long = 2049
Dim InputData As Long
Dim OutputData As Long


Private Sub Command1_Click()
    If Len(Text1) > 0 Then
        Connecting '��������
    End If
End Sub

Private Sub Command2_Click()
    OutputData = 4
    Connect.SendData OutputData '��������
End Sub

Private Sub Command3_Click()
    Unload Me '�رմ���
End Sub

Private Sub Connect_Close()
'���Է�ִ��Connect.Close�����ر�����ʱ���������¼�
    Disconnect
End Sub

Private Sub Connect_Connect()
'���Է�ͬ����������ʱ���������¼�
    OutputData = 0
    Connect.SendData OutputData '��������
End Sub

Private Sub Connect_DataArrival(ByVal bytesTotal As Long)
'Connect�����յ�����ʱ���������¼�
    Connect.GetData InputData '��������
    Select Case InputData
        Case 0
            Message "ʵ��Զ������"
            If MsgBox("�յ���" + Connect.RemoteHostIP + "�����У��Ƿ�Ӧ��", vbYesNo, "������ʾ") = vbNo Then
                Disconnect
            ElseIf OpenPhone Then
                OutputData = 1
                Connect.SendData OutputData '��������
                Message "�Ѿ���ʼͨ��"
            Else
                OutputData = 3
                Connect.SendData OutputData '��������
                MsgBox "�޷�����Ƶ�豸", vbOKOnly, ""
            End If
        Case 1
            If OpenPhone Then
                OutputData = 2
                Connect.SendData OutputData '��������
                Message "���з�����ͨ��..."
                Command1.Enabled = False
                Command2.Enabled = True
                Text1.Enabled = False
            Else
                OutputData = 3
                Connect.SendData OutputData '��������
                MsgBox "�����޷�����Ƶ�豸", vbOKOnly, ""
            End If
        Case 2
            Message "���з�����ͨ��..."
            Command1.Enabled = False
            Command2.Enabled = True
            Text1.Text = Connect.RemoteHostIP
            Text1.Enabled = False
        Case 3
            Disconnect
            MsgBox "�Է��޷���ʼͨ����������ֹ", vbOKOnly, "��ֹ"
        Case 4
            Disconnect
            MsgBox "�Է��Ҷϣ�������ֹ", vbOKOnly, "��ֹ"
    End Select
End Sub

Private Sub Connect_Error(ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    Disconnect
End Sub

Private Sub Form_Load()
    Dim CurrentDrive As String
    
    CurrentDrive = Left(App.Path, 1)  '��õ�ǰ����������������
    ChDrive CurrentDrive '���õ�ǰ������
    ChDir App.Path '���õ�ǰĿ¼��������������ʵ�ֶԹ���Ŀ¼�� phone.dll �ļ��ĵ���
    Listen.LocalPort = TcpPort
    Listen.Listen '��ʼ����
    Message "���ڼ�������..."
End Sub

Private Sub Disconnect()
    Connect.Close
    Listen.Listen
    ClosePhone
    Message "���ڼ�������..."
    Command1.Enabled = True
    Command2.Enabled = False
    Text1.Enabled = True
End Sub

Private Sub Connecting()
    Listen.Close
    Connect.RemoteHost = Text1.Text
    Connect.RemotePort = TcpPort
    Connect.Connect
    Message "��ʼ��������..."
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Connect.Close
    Listen.Close
    ClosePhone
End Sub

Private Sub Listen_ConnectionRequest(ByVal requestID As Long)
'����������ʱ�������ú���
    Message "�յ���������"
    Listen.Close
    Connect.Accept requestID
End Sub

Private Sub Message(s As String)
'��ʾ��Ϣ����
    StatusBar1.SimpleText = s
End Sub

Private Function OpenPhone() As Boolean
    Dim Sta As Long
    Dim ErrString As String
    
    '���� StartPhone ������ʼͨ��
    '��һ������������IP��ַ�������޷������Է�����
    '������óɹ����������� 0
    Sta = StartPhone(Connect.RemoteHostIP, LocalPort, RemotePort)
    Select Case Sta
        Case 0
            OpenPhone = True
            Exit Function
        Case -1
            ErrString = "�豸����ʹ��"
        Case -2
            ErrString = "������ַΪ�գ����麯�����ò���"
        Case -3
            ErrString = "�׽��ִ���ʧ�ܣ��޷�ʵ������ͨ��"
        Case 1
            ErrString = "�����豸����������ռ��"
        Case 2
            ErrString = "¼���豸��ʧ�ܣ�����������֧��ȫ˫��"
        Case 3
            ErrString = "�޷�����¼���ڴ�"
        Case 4
            ErrString = "�޷�����¼���ڴ�"
        Case 5
            ErrString = "�޷���ʼ¼��"
    End Select
    Message ErrString
    OpenPhone = False '����ֵ
End Function

Private Sub Text1_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
    '�س����� ASCII ��ֵΪ 13
        Command1_Click
    End If
End Sub
