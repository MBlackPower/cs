#include <iostream>
int main()
{
	char* p = "I Love China";
	p = "hehe";
//	*p = 'a'; // ���Ǿ��Բ��еģ�����Ϊʲô����Ա���Ա�����ȴ˵������ô��
	std::cout << p << std::endl;
	std::cout << ++p << std::endl;
	return 0;
}