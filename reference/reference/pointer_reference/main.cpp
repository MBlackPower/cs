#include <iostream>
#include <string> // & �����char* ��ʾ����˭�����ã��ұ���p���ñ�����
char*& GetMemory(char*& p) // �󶨵�ָ������ã�����˵��ָ������á�


//char* GetMemory(char* p) // û���ܹ��ı����������е�str��ֻ�����ò���
{                        // ���������񣬺Ǻǡ�
    p = (char *)malloc(100);
    return p;
}

int main()
{
    char *str = NULL;
    GetMemory(str);	
    strcpy(str, "hello world");
    printf(str); // ��ɹ��ҵ��ˣ��Ǻǣ�Ҫ��һ�ºò����á�
    std::cout << std::endl;
    return 0;
}                               