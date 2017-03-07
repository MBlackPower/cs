//---------------------------------------------------------------------------
#define  NO_WIN32_LEAN_AND_MEAN  // �� Windows ͷ���ų�����ʹ�õ�����
#include  "shlobj.h"
#include  <vcl.h>
#pragma hdrstop

#include "uMain.h"
#include "uAbout.h"
#include "uFileMoniter.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmMain *frmMain;    
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
    Caption = Application->Title;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::WndProc(TMessage &Message)
{
	switch(Message.Msg)
    {
    	case WM_SHNOTIFY:
        	mmoResult->Lines->Add(NotifyReceipt(Message.WParam, Message.LParam));
            break;
        default:
        	break;
    }
    TForm::WndProc(Message);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnStartClick(TObject *Sender)
{
	g_HSHNotify = 0;
    mmoResult->Lines->Add(String("��ʼ���ӳ���-->")
            + (RegSHNotify(Handle)? String("�ɹ�!"): String("ʧ��!")));
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(g_pidlDesktop)
        UnregSHNotify();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnAboutClick(TObject *Sender)
{
    frmAbout = new TfrmAbout(this);
    frmAbout->ShowModal();
    delete frmAbout;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnStopClick(TObject *Sender)
{
	if(g_pidlDesktop)
    {
        mmoResult->Lines->Add(String("ֹͣ���ӳ���-->")
                + (UnregSHNotify()? String("�ɹ�!"): String("ʧ��!")));
    }
}
//---------------------------------------------------------------------------

