#include <iostream>
int main()
{
    int test[2][3] = { {1, 2, 3}, { 4, 5, 6 } };
    //	int (*p)[4]; // ���������3���κ��������������У�
    // �����ǲ���˵��p��һ��ָ�룬��ָ��һ�����飬�����
    int (*p)[3]; // ����3������Ԫ�أ��������ϸ�������ƥ��ġ�@.@	             
    p = &test[1];
    // ������ô�����鶼���ܹ�ֱ���������
    // �������������ÿ�����ĸ��ֽڡ�
    std::cout << test[0]     << ' ' << *test[0] << std::endl;
    std::cout << test[0] + 1 << ' ' << *(test[0] + 1) << std::endl;
    std::cout << test[0] + 2 << ' ' << *(test[0] + 2) << "\n\n";

    std::cout << test[0] + 3 << ' ' << *(test[0] + 3) << std::endl;
    std::cout << test[1]     << ' ' << *test[1]       << std::endl;
    std::cout << *p          << ' ' << **p            << "\n\n";

    std::cout << *p + 1      << ' ' << *(*p + 1)      << std::endl;
    std::cout << *(p - 1)    << ' ' << **(p - 1)      << std::endl;

    return 0;
}                