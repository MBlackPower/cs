int& add2(int a, int b)
{
    int c = a + b;
    return c; // �����������档
}

int add(int a, int b)
{
    int c = a + b;
    return c; // ���Ͳ�������档
}

#include <iostream>
int main()
{
    int i = 10;
    int j = 20;
    int m = add(i, j);
    int n = add2(i, j);
    std::cout << m << " " << n << std::endl;
    return 0;
}       