#include <iostream>
using std::cout;
using std::endl;
int main()
{
	char greeting[]  = "ILoveChina!";
	char greeting2[] = "ILoveChina!";
	char greeting3[] = "ILoveChina!";
	char greeting4[] = "ILoveChina!";

	char* p = greeting; // �����ҵķ����@_@~. // û�з����Ƿ��һ����C++ Primerһ�£�����һ��
	const char* p2 = greeting2; // ���ǿ�const��*�����ұ��������ġ�
	char* const p3 = greeting3;
	const char* const p4 = greeting4;
	
	// ��һ�ֶ��巽ʽ
	cout << p << "\t" << *p << endl; 
	p++;                                // ok! char* p��ָ����������޸�
	cout << p << "\t" << *p << endl; 
    
	p--;                            
	*p = 'Y';                           // ok! char* p��ָ����ָ��������޸�
	cout << p << "\n\n" << endl;

	// �ڶ��ֶ��巽ʽ
	cout << p2 << "\t" << *p2 << endl; 
	p2++;                               // ok! char* p��ָ����������޸�
	cout << p2 << "\t" << *p2 << "\n\n" << endl; 

	p2--;
//	*p2 = 'Y';                          // ��p��ָ����ָ�������޸�

	// �����ֶ��巽ʽ
	cout << p3 << "\t" << *p3 << endl;  
//	p3++;                               // ��ָ�����������޸�

	*p3 = 'Y';                          // ok! ָ����ָ��������޸�
	cout << p3 << "\t" << *p3 << "\n\n" << endl; 

	// �����ֶ��巽ʽ
	cout << p4 << "\t" << *p4 << endl;
//	p4++;                               // ��ָ�����������޸�
	
//	*p4 = 'y';                          // ��ָ����ָ���󲻿����޸� 
	
	return 0;
}