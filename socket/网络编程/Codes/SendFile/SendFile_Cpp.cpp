//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SendFile_Cpp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TSendFiles *SendFiles;
//---------------------------------------------------------------------------
__fastcall TSendFiles::TSendFiles(TComponent* Owner)
        : TForm(Owner)
{
FullFileName=new TStringList();//Ҫ���͵�ȫ·���ļ���
FSTimeOut=0;                   //���ʱ������
BuildTable16(cnCRC_CCITT);     //����CRCУ���
SleepTime=30;
}
//---------------------------------------------------------------------------


//****************�����ļ�����·��******************
void __fastcall TSendFiles::Button5Click(TObject *Sender)
{
  AnsiString Dir0 = "";
  if (SelectDirectory(Dir0, TSelectDirOpts() << sdAllowCreate << sdPerformCreate << sdPrompt,0)) Dir->Text = Dir0;
}
//---------------------------------------------------------------------------


//****************������ã�����������***************
void __fastcall TSendFiles::Button4Click(TObject *Sender)
{
Notebook1->ActivePage="Main";
}
//---------------------------------------------------------------------------


//****************�������û���*******************
void __fastcall TSendFiles::SetUpClick(TObject *Sender)
{
Notebook1->ActivePage="SetUp";
}
//---------------------------------------------------------------------------


//****************��Ӱ�ť�¼�*******************
void __fastcall TSendFiles::AddClick(TObject *Sender)
{
AnsiString FileName,TempName;                         //�ļ���
if (OpenDialog1->Execute())                           //���ļ��Ի���
  {
    for (int i=0;i<OpenDialog1->Files->Count;i++)
        {
         TempName=OpenDialog1->Files->Strings[i];     //ȡ��ȫ·���ļ���
         FullFileName->Add(TempName);                 //����
         FileName=ExtractFileName(TempName);          //ȡ����·���ļ���
         ListView1->AddItem(FileName,NULL);           //��ListView����ʾ
        }
   Sent->Enabled=true;                                //���Ͱ�ť
   Cancel->Enabled=false;                             //ȡ����ť
  }
}
//---------------------------------------------------------------------------


void __fastcall TSendFiles::ListView1Resize(TObject *Sender)
{
ListView1->Columns->Items[0]->Width=ListView1->Width-5;
}
//---------------------------------------------------------------------------


//*****************���**************************
void __fastcall TSendFiles::ClearClick(TObject *Sender)
{
FullFileName->Clear();
ListView1->Clear();
Sent->Enabled=false;
Cancel->Enabled=false;
Add->Enabled=true;
FSCMDS->Lines->Clear();
FRCMDS->Lines->Clear();
FSRepa->Lines->Clear();
FRError->Lines->Clear();
}
//---------------------------------------------------------------------------


//**************************�������ݵ�UDP�ؼ�************************
//**������CMD---�����룬Buffer---����ȥָ�룬Size---���ݳ���
//*******************************************************************
void __fastcall TSendFiles::SendData_1(AnsiString CMD,char *Buffer,long Size)
{
SendData_1(CMD,Buffer,Size,0);                  //��Position��ʽ��������
}

void __fastcall TSendFiles::SendData_1(AnsiString CMD,char *Buffer,long Size,long Position)
{
TSendFileData TempData;                             //��ʱ���ݻ���
Application->ProcessMessages();
memset(&TempData,0,sizeof(TSendFileData));          //���������

//**************************����Ҫ���͵�����*********************************
TempData.Ver='1';
if (!(CMD=="FRLast"||CMD=="FSLast"))                //ִ�еĲ���"�ط�"����
   {
   if (CMD=="FSCrea") TempData.Position=ReadFileSize;//�����ļ��������Position�����ļ�����
   if (CMD=="FSFile") TempData.Position=Position;   //�����ļ�ʱ�����ļ�ָ�루��ǰPosition�Ѿ�����Size�ֽ�)
   strcpy(TempData.FileFlage,CMD.c_str());          //����������
   TempData.Size=Size;                              //�������ݳ���
   memmove(&TempData.Data,Buffer,Size);             //��Ҫ���͵����ݱ��浽��ʱ������
   TempData.CRC=0;
   unsigned short CRC;
   CRC=CRC_16(&TempData.FileFlage[0],sizeof(TempData));//����CRCУ����
   TempData.CRC=CRC;                                //����CRC
   ErrorCount=0;                                    //���������
   FSTimeOut=0;
   }
else                                                //ִ��"�ط�"����
   {
   if (CMD=="FSLast")                               //���ͷ��ط�
       memmove(&TempData,&LastSendData,sizeof(TSendFileData));//�����һ�εķ��ͷ�����ȡ��
   else
       memmove(&TempData,&LastReciveCMD,sizeof(LastReciveCMD));//�����һ�εĽ��շ�����ȡ��
   Size=TempData.Size;
   ErrorCount++;                                    //���������+1
   if (ErrorCount>10)                               //�ط�����10��
      {
        FSStatusBar->Panels->Items[1]->Text="�������,����ʧ��";
        return;
      }
   }
//***************׼������******************************************************
   if (CMD.SubString(1,2)=="FS")                    //�������һ�η��͵�����
      {
       memmove(&LastSendData,&TempData,sizeof(TSendFileData));    //���ͷ�����
       FSTimer->Enabled=true;                              //������ʱ��ʱ������
      }
   else
      {
       memmove(&LastReciveCMD,&TempData,sizeof(LastReciveCMD));    //���ܷ���Ӧ����
      }
   WriteToUDF(TempData.FileFlage,sizeof(TSendFileData)-1000+Size);  //�������ݰ���UDP
}




//******************�ƺ���***********************
void __fastcall TSendFiles::FormDestroy(TObject *Sender)
{
delete ReadFile;
delete WriteFile;
delete [] WriteList;//ɾ���ļ���״̬����
ReadFile=NULL;
WriteFile=NULL;
}
//---------------------------------------------------------------------------


//***************����UDP����****************************
//�˴�Ϊ��������ϲ��ӿ����ݣ���ֵ��������SendBuff���ͣ���2000��û���⣬��9X�»����
//����������MyStream������һ�£�����SendStream���͡�
//******************************************************
void __fastcall TSendFiles::WriteToUDF(char *Buffer,int Size)
{
NMUDP1->RemoteHost=RemoteIP->Text;
NMUDP1->RemotePort=RemotePort->Text.ToIntDef(6666);
TMemoryStream *MyStream =new TMemoryStream();
try
{
MyStream->WriteBuffer(Buffer,Size);
NMUDP1->SendStream(MyStream);
}
catch (...){}
delete MyStream;
}


//**************���յ���UDP����******************************
//�˴�Ϊ��������Ľӿڲ��֣��ж�FileFlag��һ���ֽ�Ϊ"F"����Proc_Send_F��
//***********************************************************
void __fastcall TSendFiles::NMUDP1DataReceived(TComponent *Sender,
      int NumberBytes, AnsiString FromIP, int Port)
{
TSendFileData RecivedData;
memset(&RecivedData,0,sizeof(TSendFileData));

NMUDP1->RemoteHost=FromIP;
RemoteIP->Text=FromIP;
NMUDP1->RemotePort=Port;
RemotePort->Text=IntToStr(Port);

NMUDP1->ReadBuffer(&RecivedData.FileFlage[0],8192,NumberBytes);//��������
AnsiString Flag;
Flag=RecivedData.FileFlage;             //���ݰ�����
if (Flag.SubString(1,1)=="F")           //�ļ�����������
  {
   if (RecivedData.Ver=='1') Proce_Send_F_1(RecivedData);       //1�洦���ļ����������ݰ�
  }
}
//---------------------------------------------------------------------------


//********************�ļ����������ݴ������******************
void __fastcall TSendFiles::Proce_Send_F_1(TSendFileData FileData)
{
Application->ProcessMessages();
unsigned short CRC1,CRC2;               //���¼���CRCУ����
CRC1=FileData.CRC;                      //��������CRC
FileData.CRC=0;
CRC2=CRC_16(&FileData.FileFlage[0],sizeof(TSendFileData));//����CRC
AnsiString CMD,FileName;                //�����룬�ļ���
CMD=FileData.FileFlage;                 //ȡ���Է�������������
div_t x=div(FileData.Position,1000);    //��������Index
int Index=x.quot;
if (x.rem>0) Index++;

if (CRC1!=CRC2)                         //У������ط�
   {
    if (CMD=="FSFile")                  //������������ļ����ݰ�
       {
        FRError->Lines->Add(IntToStr(Index));//��ʾCRC����İ����
        SendData_1("FRCRC","",0,FileData.Position);//֪ͨ���ͷ��ط�CRC����İ�
       }
    else                                //�����ļ����ݰ�����Ҫ���ͷ��ط����һ����
       {
        if (CMD.SubString(1,2)=="FR")   //�յ����ǽ��շ�����������(Ŀǰ��������Ϊ���ͷ�)
           SendData_1("FSRepa","",0);   //���ͣ����ͷ���������"�ط�"����
        else                            //�յ����Ƿ��ͷ�����������(Ŀǰ��������Ϊ���շ�)
           SendData_1("FRRepa","",0);   //���ͣ����շ�������"�ط�"����
       }
    return;
   }
//***********************������CRCУ����ȷ�İ�*********************
if (CMD=="FSFile")                      //������ļ����ݰ�
   {
    WriteList[Index]=true;              //�ö�Ӧ����ȷ��־
   }
if (CMD.SubString(1,2)=="FR")           //�յ����ǽ��ն˷��ص���Ϣ
     {
      if (CMD!="FRRate") FRCMDS->Lines->Add(CMD);
      FSTimer->Enabled=false;           //�رշ��ͳ�ʱ��ʱ������
      if (FRCMD!="FRRead" &&FRCMD!="FREnd" && FRCMD==CMD) return;//����ִ�з��Ͷ���������ظ�������
      if (CMD!="FRRate") FRCMD=CMD;                        //���浱ǰ����
     }
else                                    //�յ����Ƿ��Ͷ˷�������Ϣ
     {
     if (!(FSCMD=="FSFile"&&CMD=="FSFile")) FSCMDS->Lines->Add(CMD);
     if (CMD!="FSFile" &&CMD!="FSStop" && FSCMD==CMD) return;//����ִ�н��ն�����
     FSCMD=CMD;                          //���浱ǰ����
     }


//********************�����ǽ��շ���������***************************************
if (CMD=="FSName")                      //���������������ļ���
   {
    FSCMDS->Lines->Clear();
    FSCMDS->Lines->Add(CMD);
    FileName=FileData.Data;             //ȡ���ļ���
    if (ReciveType->ItemIndex==2)       //�ܾ������κ��ļ�
       {
        SendData_1("FRReje","",0);      //���ͷ������ܾ������ļ�ָ��
        return;
       }
    if (ReciveType->ItemIndex==1)       //���û���ʾ�����ļ�
       {
        if (MessageDlg("�Է�����"+FileName+",������",mtConfirmation,mbOKCancel,0)!=mrOk)//�û��ܾ�
           {
            if (FRCMD!="FSCanc") SendData_1("FRReje","",0);//�ڴ�֮ǰû���յ�Cancel�����ͷ������ܾ������ļ�ָ��
            return;
           }
       }
    if (FRCMD=="FSCanc") return;           //�ڴ�֮ǰ�յ�Cancel
    if (FileExists(GetDir()+"\\"+FileName))//���ָ��·�������������ļ�
         SendData_1("FRExis",FileName.c_str(),FileName.Length());//�У�����������Ϣ
    else SendData_1("FRNot",FileName.c_str(),FileName.Length()); //�ޣ�������������Ϣ
    return;
   }
if (CMD=="FSCrea")                      //�������������ǽ����ļ�����
   {
    if (WriteFile!=NULL)
       {
        return;
       }
    FileName=FileData.Data;             //ȡ���ļ���
    WriteFileSize=FileData.Position;    //ȡ���������ļ�����
    if (WriteListCount>0) delete [] WriteList;//ɾ���ļ���״̬����
    WriteListCount=0;                   //���ļ���״̬��
    div_t x;
    x=div(WriteFileSize,1000);          //�����ļ�������
    WriteListCount=x.quot;
    if (x.rem>0) WriteListCount++;
    WriteList=new bool [WriteListCount];//�����ļ���״̬����
    for (int j=0;j<WriteListCount;j++) WriteList[j]=false;//���ļ���״̬
    try
    {
     WriteFile=new TFileStream(GetDir()+"\\"+FileName,fmCreate|fmShareDenyNone);//�����ļ�
     SendData_1("FRAll","",0);           //���ͷ��������ļ�ָ��
    }
    catch (...)
    {
     FRStatusBar->Panels->Items[1]->Text="����"+FileName+"ʧ��";
     SendData_1("FRErr","",0);              //���ͷ�����д�ļ�ʧ����Ϣ
    }
    TimerCount=0;                           //�ļ����ͼ�ʱ��
    Timer1->Enabled=true;
    FRBlocks=0;
    FRStatusBar->Panels->Items[2]->Text="00:00:00";
    FRError->Lines->Clear();
    FRError->Lines->Add("CRC����Ŀ�");
    return;
   }
if (CMD=="FSFile")                        //���ͷ����������ļ�����
   {
    if (WriteFile!=NULL)                  //��Ч���ļ���
      {
       Cancel->Enabled=true;
       try
          {
           if (WriteFile->Size<=FileData.Position)      //��ǰ�����ļ�β(��������)
              FRStatusBar->Panels->Items[1]->Text=FormatFloat("###,###,###",FileData.Position+FileData.Size)+"/"+FormatFloat("###,###,###",WriteFileSize);
           else FRStatusBar->Panels->Items[1]->Text="����:"+IntToStr(FileData.Position);
           while (WriteFile!=NULL && WriteFile->Size<FileData.Position)    //�����ǰ�鳬�����ļ�β
              {
               WriteFile->Seek(0,soFromEnd);            //д�������ݵ��ļ�
               WriteFile->WriteBuffer(FileData.Data,FileData.Size);
              }
           if (WriteFile==NULL) return ;
           WriteFile->Seek(FileData.Position,soFromBeginning);//д��ǰ�ļ���
           WriteFile->WriteBuffer(FileData.Data,FileData.Size);
           FRBlocks++;
          }
       catch (...)
          {
           FRStatusBar->Panels->Items[1]->Text="д�ļ�����";
           SendData_1("FRErr","",0);              //���ͷ�����д�ļ�������Ϣ
          }
      }
    return;
   }
if (CMD=="FSStop")                                //���ͷ����������ļ����ͽ���ָ��
   {
    if (WriteFile!=NULL)                          //�ļ���Ч
      {
       int Poss[250];                             //��Ҫ�ط������ݿ�
       int k=0;
       int j=0;
       FRError->Lines->Add("**��Ҫ�ط��Ŀ�**");
       while (j<WriteListCount-1)                 //�����ļ�������
          {
           if (!WriteList[j])                     //������ļ���
              {
              if (k<250)                          //һ����෢250��������ļ�����Ϣ
                {
                 Poss[k]=j;                       //�����ļ���������
                 k++;                             //����������
                }
              FRError->Lines->Add(IntToStr(j*1000));
              }
           j++;
          }
       if (k>0)                                   //�д�����ļ���
          {
           SendData_1("FRRead",(char *)Poss,k*sizeof(int));//���ͷ����������
          }
       else                                      //û�д�������ݿ�
          {
           delete WriteFile;                     //�ر��ļ�
           WriteFile=NULL;
           FRBlocks=0;
           delete [] WriteList;                  //ɾ���ļ�״̬��־����
           WriteListCount=0;                     //�ļ�״̬��־����
           SendData_1("FREnd","",0);             //֪ͨ���ͷ��ļ��������
           Timer1->Enabled=false;                //�ر��ļ����ͼ�ʱ��
           FRStatusBar->Panels->Items[1]->Text="�������!";

          }
       }
    return;
   }
if (CMD=="FSCanc")                            //���ͷ����������ж�����
   {
    try
       {
        FileName=FileData.Data;               //ȡ���ļ��ļ���
        delete WriteFile;                     //�ر��ļ�
        WriteFile=NULL;
        DeleteFile(GetDir()+"\\"+FileName);   //ɾ��δ��������ļ�
        SendData_1("FRCanc","",0);            //֪ͨ���ͷ��Ѿ��ж�
       }
    catch (...)
       {
       }
       FRStatusBar->Panels->Items[1]->Text="���ͷ��жϴ���";
    return;
   }

//************************ִ���ط�����*******************************

if (CMD=="FRRepa")                        //���շ��������ط�����
   {
    SendData_1("FSLast","",0);            //ִ�з��ͷ��ط�
    return;
   }
if (CMD=="FSRepa")                        //���ͷ��������ط�����
   {
    SendData_1("FRLast","",0);            //ִ�н��շ��ط�
    return;
   }

//************************�����Ƿ��ͷ���������********************
if (CMD=="FRRate")
   {
    memmove(&Rate,FileData.Data,sizeof(float));
    return;
   }
if (CMD=="FRCRC")                         //���շ���������CRCУ�����Ϣ
   {
    SendFile_1(FileData.Position);        //�ط�������ļ���
    FSRepa->Lines->Add(IntToStr(FileData.Position));
    return;
   }
if (CMD=="FRCanc") return;              //���շ��Ѿ��ж�
if (CMD=="FRReje")                      //���շ������ܾ�����ָ��
   {
    if (FSTimeOut>MaxTimeOut->Text.ToIntDef(60)) return;      //��ʱ
    if (MessageDlg("�Է��ܾ�����,������",mtConfirmation,mbOKCancel,0)==mrOk)
       {
        SendData_1("FSLast","",0);        //����
        return;
       }
    else CMD="FREnd";                   //��������
   }
if (CMD=="FRNot")                       //���շ������ļ���������Ϣ
   {
    if (FSTimeOut>MaxTimeOut->Text.ToIntDef(60)) return;      //��ʱ
    StartSend();                        //��ʼ�����ļ�
    return;
   }
if (CMD=="FRExis")                      //���շ������ļ�������Ϣ
   {
    if (!Cancel->Enabled) return;       //�Ѿ�Cancel
    if (FSTimeOut>MaxTimeOut->Text.ToIntDef(60)) return;      //��ʱ
    FileName=FileData.Data;             //ȡ���ļ����������Ի���
    if (MessageDlg(FileName+"\r\nͬ�����ļ��Ѿ����ڣ�������",mtConfirmation,mbOKCancel,0)==mrOk)
      {
       StartSend();                     //��ʼ�����ļ�
       return;
      }
    else CMD="FREnd";                   //�û�ѡ��"No"��ִ�н����ļ���������
   }
if (CMD=="FRAll")                       //���շ��������Ǵ����ļ�����
   {
    if (ReadFile!=NULL)                 //�ļ���Ч
       {
        if (ReadFile->Position>0) return;//�ļ��Ѿ���ʼ����
        TimerCount=0;                   //�ļ����ͼ�ʱ��
        FSBlocks=0;
        Timer1->Enabled=true;
        FSStatusBar->Panels->Items[2]->Text="00:00:00";
        int Pos=0;
        while (Pos<ReadFileSize&&ReadFile!=NULL)//ѭ�������ļ���
           {
            try
              {
               if (!Cancel->Enabled) return;//�û�������"ȡ��"��
               Pos+=SendFile_1(Pos);    //�����ļ���
               if (Cancel->Enabled) FSStatusBar->Panels->Items[1]->Text=FormatFloat("###,###,###",Pos)+"/"+FormatFloat("###,###,###",ReadFileSize);
               else FSTimer->Enabled=false;
              }
            catch (...)
              {
              FSStatusBar->Panels->Items[1]->Text="���ļ�����!";
              }
           }
        SendData_1("FSStop","",0);      //֪ͨ���շ��������
       }
    else
       {
        FSStatusBar->Panels->Items[1]->Text="�ļ�δ��!";
       }
    return;
   }
if (CMD=="FRRead")                      //���ͷ������շ������Ŀ�Ŵ����ļ���(���ھ���)
   {
    if (ReadFile!=NULL)
       {
        int Pos[250];                   //�ļ��������
        memmove(Pos,FileData.Data,FileData.Size);//ȡ�����շ������������
        int n=FileData.Size/sizeof(int);//Ҫ���Ŀ�����
        for (int j=0;j<n;j++)
           {
            try
              {
               if (!Cancel->Enabled) return;//�û�������"ȡ��"��
               SendFile_1(Pos[j]*1000); //��������Ҫ���ļ���
               FSRepa->Lines->Add(IntToStr(Pos[j]*1000));
               if (Cancel->Enabled) FSStatusBar->Panels->Items[1]->Text="�ط�:"+FormatFloat("###,###,###",Pos[j]*1000);
               else FSTimer->Enabled=false;
              }
            catch (...)
              {
              FSStatusBar->Panels->Items[1]->Text="���ļ�����!";
              }
           }
        SendData_1("FSStop","",0);      //֪ͨ���շ��������
       }
    else
       {
        FSStatusBar->Panels->Items[1]->Text="�ļ�δ��!";
       }
    return;
   }
if (CMD=="FRErr")                      //���շ�����д������Ϣ
   {
    if (MessageDlg("���շ�д�ļ�ʧ�ܣ�������",mtConfirmation,mbOKCancel,0)==mrOk)
      {
       SendData_1("FSLast","",0);      //�ط�
       return;
      }
    else CMD="FREnd";                  //�û�ѡ��"No"��ִ�н����ļ���������
   }
if (CMD=="FREnd")                      //���շ������ļ����������Ϣ
   {
   if (ReadFile==NULL)
      {
       FSStatusBar->Panels->Items[1]->Text="ֹͣ����!";
       Sent->Enabled=false;                      //���洦��
       Cancel->Enabled=false;
       Add->Enabled=true;
       Clear->Enabled=true;
       SetUp->Enabled=true;
       return;
      }
   delete ReadFile;                    //�ر��ļ�
   ReadFile=NULL;
   Timer1->Enabled=false;              //�ر��ļ������ʱ��
   ListView1->Items->Delete(0);        //ɾ���Ѿ����͵��ļ���Ϣ
   FullFileName->Delete(0);
   if (ListView1->Items->Count>0)      //����δ���͵��ļ�
      {
       FSRepa->Lines->Clear();
       FRCMDS->Lines->Clear();
       FileName=ExtractFileName(FullFileName->Strings[0]);      //ȡ���ļ���
       SendData_1("FSName",FileName.c_str(),FileName.Length());   //�����ļ�����Ϣ
       ListView1->ItemIndex=0;
      }
   else                                          //�ļ��Ѿ�ȫ���������
      {
       Sent->Enabled=false;                      //���洦��
       Cancel->Enabled=false;
       Add->Enabled=true;
       Clear->Enabled=true;
       SetUp->Enabled=true;
      }
    FSStatusBar->Panels->Items[1]->Text="�������!";
    return;
   }
}
void __fastcall TSendFiles::FormCreate(TObject *Sender)
{
Dir->Text=GetCurrentDir();                       //��ʼ·��(��ֲʱҪ���ӱ����ϴ�ֵ�Ĺ���)
}
//---------------------------------------------------------------------------

void __fastcall TSendFiles::SentClick(TObject *Sender)  //���Ͱ�ť
{
AnsiString FileName;
FileName=ExtractFileName(FullFileName->Strings[0]);     //�ļ���
SendData_1("FSName",FileName.c_str(),FileName.Length());  //�����ļ�����Ϣ
FSStatusBar->Panels->Items[1]->Text="";
FSStatusBar->Panels->Items[2]->Text="";
FSStatusBar->Panels->Items[3]->Text="";
ListView1->ItemIndex=0;
Sent->Enabled=false;
Add->Enabled=false;
Cancel->Enabled=true;
Clear->Enabled=false;
SetUp->Enabled=false;
FSRepa->Lines->Clear();
FSRepa->Lines->Add("CRC�����ط���");
FSCMDS->Lines->Clear();

}
//---------------------------------------------------------------------------


void __fastcall TSendFiles::StartSend()                 //��ʼ�����ļ�
{
 FRCMDS->Lines->Clear();
 FRCMDS->Lines->Add(FRCMD); 
 if (FSTimeOut>MaxTimeOut->Text.ToIntDef(60)) return;      //��ʱ
 AnsiString FileName=FullFileName->Strings[0];          //�ļ���
 try
    {
    delete ReadFile;
    ReadFile=NULL;
    ReadFile=new TFileStream(FileName,fmOpenRead|fmShareDenyNone);//���ļ�
    }
 catch (...)
    {
    FSStatusBar->Panels->Items[1]->Text="���ļ�ʧ�ܣ�";
    }
 ReadFileSize=ReadFile->Size;                        //δ���ֽ���
 AnsiString WriteName=ExtractFileName(FileName);     //�ļ���
 SendData_1("FSCrea",WriteName.c_str(),WriteName.Length());//���ͽ����ļ�����
}

void __fastcall TSendFiles::FSTimerTimer(TObject *Sender) //���ͷ���ʱ��ʱ��������
{
FSTimeOut++;                                               //������
AnsiString CMD=LastSendData.FileFlage;                     //���һ�η��͵�����
CMD=CMD.SubString(1,6);                                    //ȡ��������
if (CMD!="FSName" && CMD!="FSFile")                        //������͵����ļ������ļ������������ִ���ط�
  {
   int temp=FSTimeOut/3;                                   //3�����ط�һ��
   if (temp*3==FSTimeOut)
      {
       SendData_1("FSLast","",0);                          //�ط�
      }
  }
if (FSTimeOut<5) return;        //С��5�벻��ʾ��Ϣ
if (FSTimeOut<20) FSStatusBar->Panels->Items[1]->Text=FSStatusBar->Panels->Items[1]->Text+".";
else FSStatusBar->Panels->Items[1]->Text="............."+IntToStr(FSTimeOut)+"��";
if (FSTimeOut>MaxTimeOut->Text.ToIntDef(60))               //��ʱ
   {
    FSTimer->Enabled=false;                               //�رն�ʱ��
    if (CMD!="FSName") FSStatusBar->Panels->Items[1]->Text="����ʧ��,���糬ʱ��";
    else FSStatusBar->Panels->Items[1]->Text="����ʧ��,�Է���Ӧ��";
    delete ReadFile;
    ReadFile=NULL;
    FSTimeOut=0;
    if (ListView1->Items->Count>0)
     {
      Sent->Enabled=true;                                //���水ť����
      Add->Enabled=false;
     }
    else
     {
      Sent->Enabled=false;
      Add->Enabled=true;
     }
    Clear->Enabled=true;
    SetUp->Enabled=true;
    Cancel->Enabled=false;
   }
}
//---------------------------------------------------------------------------



void __fastcall TSendFiles::CancelClick(TObject *Sender)     //���͹����е�"ȡ��"
{
if (ReadFile!=NULL)
   {
    if (MessageDlg("���ڷ����ļ�...,ֹͣ��",mtConfirmation,TMsgDlgButtons() << mbYes<<mbNo,0)==mrNo) return;
    if (ListView1->Items->Count>0)                          //���水ť����
         {
          Sent->Enabled=true;
          Add->Enabled=false;
         }
    else
         {
          Sent->Enabled=false;
          Add->Enabled=true;
         }
    Clear->Enabled=true;
    SetUp->Enabled=true;
    Cancel->Enabled=false;
    AnsiString FileName=ExtractFileName(FullFileName->Strings[0]); //ȡ�����ڷ��͵��ļ���
    SendData_1("FSCanc",FileName.c_str(),FileName.Length());         //֪ͨ���շ��жϷ���
    try
       {
        delete ReadFile;                                             //�ر����ڷ��͵��ļ�
        ReadFile=NULL;
       }
    catch(...){}
    FSStatusBar->Panels->Items[1]->Text="�û��ж�";
    FSTimer->Enabled=false;
    FSTimeOut=0;
   }
if (WriteFile!=NULL)
   {
    if (MessageDlg("���ڽ����ļ�...,ֹͣ��",mtConfirmation,TMsgDlgButtons() << mbYes<<mbNo,0)==mrNo) return;
    delete WriteFile;
    WriteFile=NULL;
    Cancel->Enabled=false;
    SendData_1("FREnd","",0);
    SendData_1("FREnd","",0);
    SendData_1("FREnd","",0);
    SendData_1("FREnd","",0);
    FRStatusBar->Panels->Items[1]->Text="�жϽ���";
   }
}
//---------------------------------------------------------------------------


AnsiString __fastcall TSendFiles::GetDir()      //ȡ�����ļ���·��
{
 AnsiString Direct=Dir->Text;
 while (Direct.SubString(Direct.Length(),1)=="\\") Direct.Delete(Direct.Length(),1);
 return Direct;
}
//---------------------------------------------------------------------------


//**********����CRCУ�����****************************
void __fastcall TSendFiles::BuildTable16(unsigned short aPoly)
{
    unsigned short i, j;
    unsigned short nData;
    unsigned short nAccum;

    for ( i = 0; i < 256; i++ )
    {
        nData = ( unsigned short )( i << 8 );
        nAccum = 0;
        for ( j = 0; j < 8; j++ )
        {
            if ( ( nData ^ nAccum ) & 0x8000 )
                nAccum = ( nAccum << 1 ) ^ aPoly;
            else
                nAccum <<= 1;
            nData <<= 1;
        }
        Table_CRC[i] = ( unsigned long )nAccum;
    }
}
//---------------------------------------------------------------------------


//**********����CRCУ����****************************
unsigned short __fastcall TSendFiles::CRC_16( unsigned char * aData, unsigned long aSize )
{
    unsigned long  i;
    unsigned short nAccum = 0;

    for ( i = 0; i < aSize; i++ )
        nAccum = ( nAccum << 8 ) ^ ( unsigned short )Table_CRC[( nAccum >> 8 ) ^ *aData++];
    return nAccum;
}
//---------------------------------------------------------------------------


int __fastcall TSendFiles::SendFile_1(int Position)
{
 char Buffer[1024];
 int Size;
try
 {
 if (ReadFile==NULL) return 0;
 if (ReadFile->Size-Position>1000) Size=1000;
 else Size=ReadFile->Size-Position;
 ReadFile->Seek(Position,soFromBeginning);
 ReadFile->ReadBuffer(Buffer,Size);
 SendData_1("FSFile",Buffer,Size,Position);
 FSBlocks++;
 Delay(SleepTime);
 return Size;
 }
catch (...)
 {
 FSStatusBar->Panels->Items[1]->Text="���ļ�����!";
 return -1;
 }
}
//---------------------------------------------------------------------------


void __fastcall TSendFiles::Timer1Timer(TObject *Sender)//�ļ������ʱ��
{
float FSRate=FSBlocks*1000/1024.0;
float FRRate=FRBlocks*1000/1024.0;
FSBlocks=0;
FRBlocks=0;
TimerCount++;
int hh,mm,ss;
ss=TimerCount;
hh=ss/3600;
ss=ss-hh*3600;
mm=ss/60;
ss=ss-mm*60;
if (FRRate>0)
   {
    LastFRRate=(LastFRRate+FRRate)/2;
    FRStatusBar->Panels->Items[3]->Text=FormatFloat("0.0",LastFRRate)+"k/s";
    FRStatusBar->Panels->Items[2]->Text= FormatDateTime("hh:mm:ss",EncodeTime(hh,mm,ss,0));
    SendData_1("FRRate",(char *) &LastFRRate,sizeof(float));
   }
if (FSRate>0)
   {
    LastFSRate=(LastFSRate+FSRate)/2;
    if (Speed->Down)
       {
        float Rate0=(LastFSRate-Rate)/LastFSRate;
        if (Rate0<0) Rate0=-1*Rate0;
        if (Rate0>0 && Rate0>0.15) SleepTime+=1;
        if (Rate0>0 && SleepTime>1 && Rate0<0.05) SleepTime-=1;
       }
    else
       {
        if (LastFSRate>23) SleepTime+=10;
        if (LastFSRate<18) SleepTime-=10;
       }
    FSStatusBar->Panels->Items[3]->Text=FormatFloat("0.0",LastFSRate)+"k/s,"+IntToStr(SleepTime);
    FSStatusBar->Panels->Items[2]->Text= FormatDateTime("hh:mm:ss",EncodeTime(hh,mm,ss,0));
   }
}
//---------------------------------------------------------------------------

void __fastcall TSendFiles::FormCloseQuery(TObject *Sender, bool &CanClose)
{
if (ReadFile!=NULL)
   {
    if (MessageDlg("���ڷ����ļ�...,ֹͣ��",mtConfirmation,TMsgDlgButtons() << mbYes<<mbNo,0)==mrYes)
       {
        delete ReadFile;
        ReadFile=NULL;
        CanClose=true;
       }
    else CanClose=false;
   }
if (WriteFile!=NULL)
   {
    if (MessageDlg("���ڽ����ļ�...,ֹͣ��",mtConfirmation,TMsgDlgButtons() << mbYes<<mbNo,0)==mrYes)
       {
        delete WriteFile;
        WriteFile=NULL;
        CanClose=true;
       }
    else CanClose=false;
   }
}
//---------------------------------------------------------------------------

void __fastcall TSendFiles::SpeedClick(TObject *Sender)
{
if (Speed->Down)
   {
    Speed->Caption="�Զ�";
    Speed->Hint="�Զ�����������ٶ�";
   }
else
   {
    Speed->Caption="����";
    Speed->Hint="���ƴ����ٶ��Ա�֤��������";
   }
}
//---------------------------------------------------------------------------



void __fastcall TSendFiles::Delay(int n)
{
long t1,t2;
t1=t2=timeGetTime();
while (abs(t2-t1)<n)
   {
    Application->ProcessMessages();
    t2=timeGetTime();
   }
}
