#include <iostream>
// ����һ������ͷ�ļ�
#include "myAddDLL.h" // �����ַ��������ԣ������ʱ����Ҫ.lib������
// ���е�ʱ�������ͨ������������֪�����ⲿ�����ĺ���

// ����������extern
// extern int add(const int&, const int&); // OK
// class _declspec(dllexport) CBook;    // ֻ�������У��ۺ϶��ԣ����鷽��һ��
//class _declspec(dllexport) CBook {
//public:
//	void print();
//};

int main()
{
	std::cout << add(3, 4) << std::endl;

	CBook a;
	a.print();
	return 0;
}