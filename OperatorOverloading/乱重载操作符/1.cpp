#include <iostream>
#include "cin_to_cout.h" // �Ұ���cin_to_cout�Ķ�����������������ص�
int main() // ���������'>>'
{
	cin_to_cout a(5);
	// ����˼�ɣ�ǰ�������֮�󣬷��ص���Ȼ�Ǳ�׼������������Կ���
	// �������

	std::cout >> a << ' ' << 1 << std::endl;
	
	return 0;
}