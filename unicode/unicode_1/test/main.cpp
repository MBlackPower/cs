#include "stdio.h"
#include <locale.h>

int main()
{
	printf("\t-?\t\t\t\tFor Help\n");

	printf("���Ĳ���\n");

	//setlocale(LC_ALL,"zh_CN.UTF-8");

	setlocale(LC_ALL, "chs");

	wprintf(L"���Ĳ���\n");

	printf("w0:%ls\n", L"���Ĳ���");

	wprintf(L"w1:%s\n", L"1���Ĳ��� ���ַ�");

	wprintf(L"w2:%ls\n", L"2���Ĳ��� ���ַ�");

	wprintf(L"w3:%ls\n", L"3tDirectory ���Ĳ��� ���ַ� end");

	wprintf(L"w4:%S\n", L"4 ���Ĳ��� ���ַ� end");

	printf("w5:%S\n", L"���Ĳ���\n");
	return 0;
}

//��������CSDN���ͣ�ת�������������http://blog.csdn.net/chief1985/archive/2010/11/09/5998546.aspx