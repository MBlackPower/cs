#include <iostream>

char * function(int & a)
{
    return "int& a";
}

char * function(int const & a)
{
    return "const int& a";
}

char* function(int a)
{
    return "int a";
}

//char* function(const int a) // �����������������ٺ�������������
//{
//    return "const int a";
//}

int main()
{
    int j = 20;
    const int k = 20;

    //std::cout << function(j) << std::endl;
    //std::cout << function(k) << std::endl;
    //std::cout << function(2) << std::endl;
    //std::cout << function(2.0) << std::endl;

    return 0;
}
