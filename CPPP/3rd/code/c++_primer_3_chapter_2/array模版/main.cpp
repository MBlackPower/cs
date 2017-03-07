#include "CArray.h"
int main()
{
    CArray<std::string> strArray; // 12�����ַ���
    CArray<int> intArray;         // 12��0

    std::cout << strArray << std::endl;
    std::cout << intArray << std::endl;

    int intArr[3] = { 2, 8, 4 };
    CArray<int> intArray2(intArr, 3);
    std::cout << intArray2 << std::endl;

    std::string str[3] = { "I love China", "I love American", "I love japan"};
    CArray<std::string> strArray2(str, 3);
    std::cout << strArray2 << std::endl;

    CArray<char> ca;
    std::cout << ca << std::endl; // 12�����ַ� // ��֪��Ϊʲô���������ĺ���ֵ����150%��
                                  // ��ô����̨�ͻὫ���ַ���ӡ��Сд��ĸa
								  // ����º�����װ��һ��ϵͳҲû���ҳ���

    return 0;
}