#include <iostream>
#include <string>
// �����������൱�Ѻð�warning C4172: returning address of local
// variable or temporary һ����Ҫ���ؾֲ�������

char* GetMemory(void)
{
    char p[] = "hello world";
    return p; // �����Ƿ���local��address
}

int get_int(void)
{
    int i = 3;
    return i; // ���Ƿ���local��ֵ���������������£�������˵����֮���õ������ַ����ֵ
}             // Ҫ��GetMemory�������������Ѿ������˵�����  
              // ��������漰��get_int������������local��������Ϊ����ֻ�����intֵ
int main()
{
    char *str = NULL;
    //	std::cout << *str; //�������������0ô��
    str = GetMemory();
    printf(str);
    std::cout << std::endl;

    std::cout << get_int() << std::endl;
    return 0;
}
