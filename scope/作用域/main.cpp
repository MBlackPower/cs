#include <iostream> // i��Ȼ��ȫ�������򣬵���Ҫ���������棬��������Ҫ������������
extern int i; // ��int i = 10���ں��������棬��ǰ���Ҫ����һ�²��С�
int main()
{
	int sum = 0; // sum�ֲ�������
	for (int val = 1; val <= 10; ++val)
	{
		sum += val;
	}
	std::cout << "Sum of 1 to 10 inclusive is "
		      << sum << std::endl;
	std::cout << i << std::endl;
	std::cout << val << std::endl; // ������˵�����ǲ�Ӧ���ܹ������
	return 0;                      // ��Ϊval�����������
}
int i = 10;
