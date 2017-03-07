#include "CBook.h"
int main()
{
    // ���ʱ�򣬱�����Ӧ��������һ����ʱ��std::string���Ͷ���Ȼ���ٰ������ʱ���󴫽����캯����ȥ
	// ���ʱ�����빹�캯��������ֻ���幹�캯����ʱ�����벻��ͨ��
    CBook book("I love China"); 
								
	std::cout << book << std::endl;
	std::cout << "I love China\n" << std::endl;

	//std::string s = "I love American";
	//CBook book2(s); // �ֶ��幹�캯�������ֶ���������������ִ�в����ˣ���Ϊ��������Ϊ����ģ����
	//std::cout << book2 << std::endl;

	std::string s2 = "I love spring"; // 1.�������ڹ������ʱ��һ������û��๹�캯���������ǵ����˻����ж�Ӧ�����ع��캯��
	CBookOnSale bookOnSale(s2, 3);    // 2.�������ڹ������ʱ�����û���ҵ�������Ӧ�Ļ������ع��캯��������û���Ĭ�Ϲ��캯��
	std::cout << bookOnSale << std::endl; // 3.����������ڶ��幹�캯��ʱָ����ʹ�û������һ�����캯����

	CBookOnSale bookOnSale2("I love China");
	std::cout << bookOnSale2 << std::endl;

	CBookOnSale bookOnSale3(5, 2.0);
	std::cout << bookOnSale3 << std::endl;

	std::cout << "\nprint function\n" << std::endl;

	book.print(std::cout);
	bookOnSale.print(std::cout);

	CBook* pBook = new CBookOnSale(5, 2.3);
	CBook* pBook2 = new CBook();

	pBook2->print(std::cout);
	pBook2->print2(std::cout);

	pBook->print(std::cout);
	pBook->print2(std::cout);

	CBookOnSale a(5, 2.3);
	CBook& book4 = a;
	book4.print(std::cout);
	book4.print2(std::cout);
	return 0;
}