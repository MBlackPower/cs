#include "Animal.h" // ��һ���������ݲ��٣��ڱ�����p132����ϸ����
                    // �����ּ̳з�ʽ��
void Func(Animal& an)
{
	an.eat();
}
int main()
{
	Cat dao;
	Giraffe gir;
	Func(dao);
//	Func(gir);
	return 0;
}
