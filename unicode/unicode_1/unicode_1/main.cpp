#include "tchar.h"
#include <string>
#include <iostream>
int main()
{
    char a = 'A';
    char* p2 = "I love china";

    wchar_t* p = _T("I love China");

    wchar_t* q = _T("�й�");
    std::cout << p2 << std::endl;

    std::cout << p << std::endl;
    std::wcout << p << std::endl;

    std::cout << q << std::endl;
    std::wcout << q << std::endl; // ʲô�����������
    wprintf(L"%s \n", q);
/* */   return 0;
}