#include <iostream>

template <class T> // ģ�������
T max(T a, T b);

int main()
{
	int a = 100;
	int b = 200;
	std::cout << max(a, b) << std::endl;
	return 0;
}

template <class T> // ģ��Ķ���
T max(T a, T b)
{
	return a>b ? a:b;
}