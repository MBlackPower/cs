#include "CIntArray.h"
#include <iostream>
int main()
{
    CIntArray arr(10);     // ��ʼ�� Ĭ�Ϲ��캯��
    CIntArray arr1;        // ��ʼ�� Ĭ�Ϲ��캯��
    //CIntArray array2();
    CIntArray arr3(arr);   // ��ʼ�� �������캯��

    for (int i = 0; i !=10; i++)
    {
        // std::cout << arr[20] << std::endl; // assert ʧ��
        std::cout << arr[i] << std::endl;
    }

    std::cout << arr << std::endl;
    std::cout << arr1 << std::endl;
    //std::cout << arr2 << std::endl;
    std::cout << arr3 << std::endl;

    int a[3] = { 2, 7, 4};
    CIntArray a1(a, 3);     // ��ʼ�� ���캯��2
    CIntArray a2 = a1;      // ��ʼ�� �������캯��
    CIntArray a3;
    //a3 = a1;              // ��ֵ���� ���ǳ�ʼ�� �������صĸ�ֵ����������û�ж������صĸ�ֵ������ʱ����������Ϊ���Ǻϳ�һ����
                            // ������������ָ���Ա��������Ϊ���ǺϳɵĲ�����ֻ�ǽ���Ӧָ��ָ��ͬһλ�ã���û��new�µĿռ����
                            // ���������Ƿǳ�����ġ�֮��������Ķ������������˸�ֵ��������������ͱ���ͨ�����ˣ�����һ�ַ�����
                            // �������ߣ�ͨ�����ַ������������û�ʹ�ø�ֵ�������������캯��Ҳ������������
    std::cout << a1 << std::endl;
    std::cout << a2 << std::endl;
    std::cout << a3 << std::endl;

	a1[2] = 200;
	std::cout << a1 << std::endl;
    return 0;
}