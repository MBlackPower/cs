#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item a;
    Sales_item b;
    // ��Ҫѧϰreturn by valueֵ���أ���ȫ�ֺ���
    // Sales_item operator+(Sales_item const &, Sales_item const &)
    // �У���return����У�������1�����ȵ��ÿ������캯�����ƶ���ret�����ڷ���ret�ĸ���
    // Ȼ����Ϊ����Sales_item operator+(Sales_item const &, Sales_item const &)������
    // �Ľ�����2��Ҫ����ret������������3�����ڷ��ص�ret�ĸ�����������һ����ʱ����
    // ��ʹ�����������Ϊȫ�ֺ���ostream& operator<<(ostream &, Sales_item const &)����
    // ��������Ҫ���������ʱ�������������
    std::cout << a + b << std::endl;

    return 0;
}

//Sales_item()                    // a�Ĺ��캯��
//Sales_item()                    // b�Ĺ��캯��
//Sales_item(Sales_item const &)  // Sales_item ret(lhs)
//Sales_item(Sales_item const &)  // ��ʱ������ret�ĸ������Ĺ��캯��
//2 ~Sales_item()                 // ret����������
//0       0       0               // std::cout�Ĵ�ӡ
//3 ~Sales_item()                 // ��ʱ������ret�ĸ���������������
//1 ~Sales_item()                 // b����������
//0 ~Sales_item()                 // a����������