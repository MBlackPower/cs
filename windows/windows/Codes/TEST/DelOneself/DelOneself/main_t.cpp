#include <windows.h>

//�ڿ�ִ���ļ�����ʱ��ɾ������.exe�ļ�
void DelOneself()
{
	HMODULE module = GetModuleHandle(0); 
    CHAR buf[MAX_PATH]; 
    GetModuleFileName(module, buf, sizeof buf); 
    CloseHandle(HANDLE(4));

    __asm
	{
        lea     eax, buf 
        push    0 
        push    0 
        push    eax 
        push    ExitProcess 
        push    module 
        push    DeleteFile 
        push    UnmapViewOfFile 
        ret 
    }
}


int APIENTRY WinMain(	HINSTANCE		hInstance,
						HINSTANCE		hPrevInstance,
						LPSTR			lpCmdLine,
						int				nCmdShow	)
{
	DelOneself();

	return 0;
}