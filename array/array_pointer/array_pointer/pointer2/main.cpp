#include <iostream>
#include <string>

int main()
{
    char *str = (char *) malloc(10);
    strcpy(str, "hello");
    free(str);
    if(str != NULL)
    {
        strcpy(str, "world"); // ����˵���ָ�����ڷǳ�Σ�պǺǣ�
        printf(str);          // ���Ǿ����ܹ�������ݣ��Ǻ�
    }  
    std::cout << std::endl;
    return 0;
}