#include <string>
#include <iostream>

class c_test {
public:
	c_test() { std::cout << "c_test constructor" << std::endl; }
};

class c_type_base {
public:
	c_type_base() { std::cout << "c_type_base constructor" << std::endl; }
};

class c_type : public c_type_base {
public:
	c_type(int a) { std::cout << a << std::endl; }
private:
	std::string s;
	c_test a;
};

int main()
{
	c_type a(3); // ���߻��๹�캯�������߳�Ա���캯���������Լ��Ĺ��캯��
	return 0;
}