#include "CString.h"
int main()
{
	//CString str1;
	//CString str2;
	//if (str1 == str2)
	//{
	//	std::cout << "I love China" << std::endl;
	//}

	//CString str3;
	//std::cin >> str3;
	//std::cout << str3 << std::endl;

	//CString str4(str3);  // �����ÿ������캯��
	//CString str5 = str3; // �������캯��

	//CString str6;		 // ��ֵ������
	//str6 = str3;		 // ����˵����ֵ�����������ֿ��ܣ�һ���ǵ��ÿ������캯����һ���ǵ��ø�ֵ������
	
	int aCnt = 0;
	int eCnt = 0;
	int iCnt = 0;
	int oCnt = 0;
	int uCnt = 0;
	int theCnt = 0;
	int itCnt = 0;
	int wdCnt = 0;
	int notVowel = 0;
	
	CString buf;
	CString the("the");
	CString it("it");
	/*	���뻺�����л��塣���Ӽ���������һ���ַ������س�����Щ�ַ������ȱ��͵����뻺�����д洢��ÿ�����»س�����
cin.get()   �ͻ������뻺�������Ƿ����˿ɶ������ݡ�cin.get()   ����Լ������Ƿ�����Ϊ��������־��   Ctrl+Z   ����   Ctrl+D  
������������飬����ķ�ʽ�����֣�����ʽ�Լ�������ʽ�� 
����ʽ��鷽ʽָ����ֻ���ڻس�������֮��ŶԴ�ǰ�Ƿ���   Ctrl+Z   ��ϼ����½��м�飬������ʽ��ָ���ǰ���   Ctrl+D   
֮��������Ӧ�ķ�ʽ������ڰ�   Ctrl+D   ֮ǰ�Ѿ��Ӽ����������ַ�����   Ctrl+D�����þ��൱�ڻس���
������Щ�ַ��͵����뻺��������ȡʹ�ã���ʱCtrl+D�������������������á������   Ctrl+D   ֮ǰû���κμ������룬
��   Ctrl+D   �������������źš� 
Windowsϵͳ��һ���������ʽ���   Ctrl+Z��Unix/Linuxϵͳ��һ����÷�����ʽ�ļ��   Ctrl+D��¥������Windowsϵͳ��
�����ʹ������ʽ��   Ctrl+Z   ����ʶ���Ľ����� 
��������ʽ�ķ�ʽ��һ���ص㣺ֻ�а��»س�֮����п��ܼ���ڴ�֮ǰ�Ƿ���Ctrl+Z���¡�����һ���ص���ǣ�
������뻺�������пɶ��������򲻻���Ctrl+Z����Ϊ��Ҫ�������ݣ���������Ϊ��������ĩβ��������һ����Ҫ֪����
Ctrl+Z�����Ĳ���һ����ͨ��ASCII��ֵ��Ҳ����˵�������Ĳ���һ���ַ������Բ���������Ӽ�����������ַ�һ���ܹ���������뻺������
�������⼸��֮��Ϳ���������¥������������ˡ� 
�Ӽ���������abcd^z   ��   �س�֮����Windowsϵͳ������������ģ����ڻس������ã�ǰ���   abcd  
���ַ����͵����뻺������ע�⣺����˵���ˣ�^z��������ַ������Ը�����洢�����뻺��������������û��   ^z   �Ĵ��ڣ���
��ʱ��cin.get()   ��⵽���뻺�������Ѿ������ݴ��ڣ���˲��ټ���Ƿ���   ^z   �����룩�����Ǵӻ����ж�ȡ��Ӧ�����ݡ�
�������ȡ���ˣ������뻺�������±�Ϊ�գ�cin.get()   �ȴ��µ����롣�ɼ���������   ^z   ���£����������ڴ�֮ǰ�������������ַ���abcd��
��������Ҳ��������� 
��ˣ��������������������ǣ�^z   ֮ǰ�������κ��ַ����루�س����⣩������   ^z   �𲻵������������á� 
��Сʱ���Ҿͽ�����ϣ����λ��������������Ի󶼿�����������*/ 
	while(std::cin >> buf)
	{
		++wdCnt;
		std::cout << buf << ' ';
		if (wdCnt %12 == 0)
		{
			std::cout << std::endl;
		}

		if (buf == the || buf == "the")
		{
			++ theCnt;
		}
		else if (buf == it || buf == "it")
		{
			++itCnt;
		}

		for (int ix = 0; ix < buf.size(); ix++)
		{
			switch(buf[ix])
			{
			case 'a': 
			case 'A':
				++aCnt;
				break;
			case 'e': 
			case 'E':
				++eCnt;
				break;
			case 'i': 
			case 'I':
				++iCnt; 
				break;
			case 'o':
			case 'O': 
				++oCnt;
				break;
			case 'u':
			case 'U':
				++uCnt;
				break;
			default:
				++notVowel;
				break;
			}
		}
	}
	std::cout << "\n\n" 
		<< "Word read: " << wdCnt << "\n\n"
		<< "the/The: " << theCnt << '\n'
		<< "it/It: " << itCnt << "\n\n"
		<< "non-vowels read: " << notVowel << "\n\n"
		<< "a: " << aCnt << '\n'
		<< "e: " << eCnt << '\n'
		<< "i: " << iCnt << '\n'
		<< "o: " << oCnt << '\n'
		<< "u: " << uCnt << std::endl;
	return 0;
}