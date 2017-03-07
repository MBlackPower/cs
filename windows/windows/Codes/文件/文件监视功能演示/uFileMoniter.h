//---------------------------------------------------------------------------
// �ļ����ӵ�Ԫ
// by ccrun(����) - info@ccrun.com
// Last modify: ***
//---------------------------------------------------------------------------
// Welcome C++Builder Study - http://www.ccrun.com
//---------------------------------------------------------------------------
#ifndef uFileMoniterH
#define uFileMoniterH

long g_HSHNotify;
LPITEMIDLIST g_pidlDesktop;

typedef struct _IDLSTRUCT
{
	LPITEMIDLIST pidl;
	long bWatchSubFolders;
}IDLSTRUCT, *PIDLSTRUCT;

typedef struct _SHNOTIFYSTRUCT
{
	LPITEMIDLIST dwItem1;
    LPITEMIDLIST dwItem2;
}SHNOTIFYSTRUCT, *PSHNOTIFYSTRUCT;

// ����δ����API����
typedef int (WINAPI *SHCHANGENOTIFYREGISTER)(long, int, DWORD, int, DWORD, PIDLSTRUCT);
typedef int (WINAPI *SHCHANGENOTIFYDEREGISTER)(int);
SHCHANGENOTIFYREGISTER   SHChangeNotifyRegister;
SHCHANGENOTIFYDEREGISTER SHChangeNotifyDeregister;

// ע��֪ͨ��Ϣ
bool __fastcall RegSHNotify(HANDLE hWnd);
// ���֪ͨע��
bool __fastcall UnregSHNotify();
// ��ȡ��Ϣ��������
String __fastcall NotifyReceipt(WPARAM wParam, LPARAM lParam);

// ֪ͨ��Ϣ
#define WM_SHNOTIFY 0x401

//---------------------------------------------------------------------------
bool __fastcall RegSHNotify(HANDLE hWnd)
{
    IDLSTRUCT ps;

    HINSTANCE hDll = LoadLibrary("SHELL32");
    if(hDll)
    {
        SHChangeNotifyRegister = (SHCHANGENOTIFYREGISTER)GetProcAddress(hDll, (char *)2);
        if(!SHChangeNotifyRegister)
        {
        	ShowMessage("GetProcAddr register error!");
        	return false;
        }
    }
    else
    	return false;
    if(g_HSHNotify == 0)
    {
        // ȡ�������IDL
        // SHGetSpecialFolderLocation(0, CSIDL_DESKTOP, &g_pidlDesktop);
		SHGetSpecialFolderLocation(0, CSIDL_DRIVES, &g_pidlDesktop);
        if(g_pidlDesktop)
        {
			memset(&ps, 0x00, sizeof(ps));
            ps.pidl = g_pidlDesktop;
            ps.bWatchSubFolders = 1;
            // ע��Windows����
            g_HSHNotify = SHChangeNotifyRegister(
            		long(hWnd),
                    SHCNF_TYPE | SHCNF_IDLIST,
		            SHCNE_ALLEVENTS | SHCNE_INTERRUPT,
    		        WM_SHNOTIFY,
                    1,
                    &ps
                    );
            FreeLibrary(hDll);
            return bool(g_HSHNotify);
        }
        else
            CoTaskMemFree(g_pidlDesktop);
    }
    FreeLibrary(hDll);
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall UnregSHNotify()
{
    HINSTANCE hDll = LoadLibrary("SHELL32.dll");
    if(hDll)
    {
        SHChangeNotifyDeregister = (SHCHANGENOTIFYDEREGISTER)
                GetProcAddress(hDll, (char *)4);
        if(!SHChangeNotifyDeregister)
        {
        	ShowMessage("GetProcAddr deregister error!");
        	return false;
        }
    }
    else
    	return false;

	if(g_HSHNotify)
    {
    	if(SHChangeNotifyDeregister(g_HSHNotify))
        {
            g_HSHNotify = 1;
            CoTaskMemFree(g_pidlDesktop);
            g_pidlDesktop = 0;
            FreeLibrary(hDll);
            return true;
        }
    }
    FreeLibrary(hDll);
    return false;
}
//---------------------------------------------------------------------------
String __fastcall NotifyReceipt(WPARAM wParam, LPARAM lParam)
{
	String strEvent;
	char szBuf[MAX_PATH];
	String strPath1, strPath2;

	SHNOTIFYSTRUCT *pidlItem = PSHNOTIFYSTRUCT(wParam);
  	SHGetPathFromIDList(pidlItem->dwItem1, szBuf);
    strPath1 = String(szBuf);
	SHGetPathFromIDList(pidlItem->dwItem2, szBuf);
    strPath2 = String(szBuf);

    switch(lParam)
    {
        case SHCNE_RENAMEITEM:
			strEvent = "�������ļ�: " + strPath1 + " Ϊ " + strPath2;
            break;
        case SHCNE_CREATE:
        	strEvent = "�����ļ�, �ļ���: " + strPath1 + strPath2;
            break;
        case SHCNE_DELETE:
        	strEvent = "ɾ���ļ�, �ļ���: " + strPath1;
            break;
        case SHCNE_MKDIR:
        	strEvent = "����Ŀ¼, Ŀ¼��: " + strPath1;
            break;
        case SHCNE_RMDIR:
            strEvent = "ɾ��Ŀ¼,Ŀ¼��: " + strPath1;
            break;
        case SHCNE_MEDIAINSERTED:
        	strEvent = strPath1 + " �в�����ƶ��洢����";
            break;
        case SHCNE_MEDIAREMOVED:
        	strEvent = strPath1 + " ����ȥ���ƶ��洢����";
            break;
        case SHCNE_DRIVEREMOVED:
        	strEvent = "��ȥ������: " + strPath1;
            break;
        case SHCNE_DRIVEADD:
        	strEvent = "���������: " + strPath1;
            break;
        case SHCNE_NETSHARE:
        	strEvent = "�ı�Ŀ¼ " + strPath1 + " �Ĺ�������";
            break;
        case SHCNE_UPDATEDIR:
        	strEvent = "����Ŀ¼: " + strPath1;
            break;
        case SHCNE_UPDATEITEM:
        	strEvent = "�����ļ�, �ļ���: " + strPath1;
            break;
        case SHCNE_SERVERDISCONNECT:
        	strEvent = "�Ͽ��������������: " + strPath1 + " " + strPath2;
            break;
        case SHCNE_UPDATEIMAGE:
        	strEvent = "����ͼ��:" + strPath1 + " " + strPath2;
        	break;
        case SHCNE_DRIVEADDGUI:
        	strEvent = "��Ӳ���ʾ������: " + strPath1;
            break;
        case SHCNE_RENAMEFOLDER:
        	strEvent = "�������ļ���: " + strPath1 + " Ϊ " + strPath2;
            break;
        case SHCNE_FREESPACE:
			strEvent = "���̿ռ��С�ı�: " + strPath1 + strPath2;
            break;
        case SHCNE_ASSOCCHANGED:
        	strEvent = "�ı��ļ�����: " + strPath1 + " " + strPath2;
            break;
        default:
        	strEvent = "��������.";
        	break;
    }
    return strEvent;
}



//---------------------------------------------------------------------------
#endif
