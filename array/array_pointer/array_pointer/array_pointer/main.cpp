#ifdef SUNYJ_UNIXLIKE
#include <stdio.h>
#endif

#include <iostream>
int main()
{
    // ��������       ��Ҫ����
    int a = 0;              // ����һ�����ͱ���a��

    int* b = NULL;             // ����һ��ָ��b��bָ��һ�����α�����
    // ����Ŀ���д�� int* *a;������ʽô������һ����^_^
    int** c = NULL;            // ����һ��ָ��c��cָ���һ��ָ�룬ָ�����α�����ָ�롣

    int d[10] = {0};          // ����һ������d��d�к���10�����α�����

    int* e[10] = {0};         // ����һ��ָ������e��e��10��ָ��Ԫ�أ�ÿ��Ԫ��ָ��һ����������

    // ���� С���� ������ ָ�������ָ��
    int (*f)[5] = NULL;        // ����һ��ָ��f��fָ��һ�����飬�����麬��5�����α�����

    // ���� С���� С���� ָ������ָ��
    int (*g)(int) = NULL;      // ����һ��ָ��g��gָ��һ���������˺�������һ������ʵ�Σ�����һ������ֵ��

    // ��x���ڵ�һ��С�����е����ݣ�x��int* e[10]��ͬ��xΪһ��ָ�����飬��
    // int (*h[10])(int) = int (x)(int) �� int(*g)(int)��ͬ
    int (*h[10])(int) = {0};  // ����һ��ָ������h��h��10��ָ��Ԫ�أ�ÿ��Ԫ��ָ��һ��������ÿ����������һ������ʵ�Σ�����һ������ֵ��
    
    // 10 pointers 10 x 8 = 80
    std::cout << " sizeof(e): = " << " " << sizeof(e) << std::endl;
    // 1 pointers 10 x 8 = 80
    std::cout << " sizeof(f): = " << " " << sizeof(f) << std::endl;

    int arr[5] = { 0, 1, 2, 3, 4 };
    int (*pp)[5] = &arr; // ppָ��һ������5��������������

    std::cout << (long)pp << std::endl;
    pp++; // pp += sizeof(pp)Ҳ����5 x 4 = 20
    std::cout << (long)pp << std::endl;

    // ������һ����������������⣬�������ˣ����������������
    int k = 1;

    // the right "k++" first calculate, but the out put operation of "k++" if after "k"
    std::cout << k << " " << k++  << std::endl;

    std::cout << k << " " << ++k << std::endl;

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    std::cout << g << std::endl;
    std::cout << h << std::endl;

    getchar();
    return 0;
}
