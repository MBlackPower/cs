#include <iostream>
using namespace std;
int main()
{
	char* p = "I love China";
	wchar_t* p1 = L"I love China";
	char* p2 = "�����й���";
	wchar_t* p3 = L"�����й���";

	std::cout  << p << std::endl; // ����p��������������ת����
	std::wcout << p << std::endl;

	std::cout  << std::endl;

	std::cout  << p1 << std::endl; // ʧ��
	std::wcout << p1 << std::endl; 

	std::cout << std::endl;

	std::cout << p2 << std::endl; // ������������������
	std::wcout << p2 << std::endl;

	std::cout << std::endl;

	std::wcout.imbue(std::locale("chs")); // �������������ܹ��������Ϻ�ڶ�����������������
	std::cout << p3 << std::endl;
	std::wcout << p3 << std::endl;

	std::cout << std::endl;

	return 0;
}