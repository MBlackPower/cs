#ifdef SUNYJ_UNIXLIKE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#endif

#include <iostream>
#include <string>

char* GetMemory(char** p, int num) 
{
    *p = (char*)malloc(num);
    return *p;
}

int main()
{
    char* p_dele = NULL;           // ����str��һ�������˵ı������Ǳ�����Ҫ�����ڴ�ռ�
    char* str = NULL;              // ����str��һ�������˵ı������Ǳ�����Ҫ�����ڴ�ռ�
    p_dele = GetMemory(&str, 100); // &str������1000������GetMeory��p����&str,
    // Ҳ����˵��p����str�ĵ�ַ����ô*p������ָ��str,*pָ�������˵�
    // �ڴ棬Ҳ����˵strָ���˷�����˵��ڴ档���ˣ�һ���б����ⷽ��
    strcpy(str, "I Love China!"); 
    // strcpy(str, "I Love \0China!"); // ����ܹ��ضϰ���
    printf(str); // ��ν������ڴ�й¶�����أ�����str == NULL?
    std::cout << std::endl;
    free(p_dele);
    p_dele = NULL; // after deleting the pointer, set the pointer to NULL
    delete p_dele; // safe, because p_dele has been set to NULL
    return 0;
}
