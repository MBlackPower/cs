#include <iostream>
#include <string>
void GetMemory(char** p, int num)
{
	*p = (char* )malloc(num);
}
int main()
{
	char *str = NULL;
	GetMemory(&str, 100);
	strcpy(str, "I Love China!");
//	strcpy(str, "I Love \0China!"); // ����ܹ��ضϰ���
	printf(str);
	std::cout << std::endl;// ��ν������ڴ�й¶�����أ�����str == NULL?
	return 0;
}
