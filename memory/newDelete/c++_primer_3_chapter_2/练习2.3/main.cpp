#include <iostream>
int b; // ��ʼ��Ϊ0��

int main()
{
    int a; // �����г�ʼ����
    int ival = 1024;
    // �������ͱ����ĳ�ʼ��
    // �������ͱ����ĳ�ʼ��ȡ���ڱ��������λ�á��ں������ⶨ��ı�������ʼ����0��
    // �ں������ﶨ����������ͱ����������Զ���ʼ��

    // �����ͱ����ĳ�ʼ��
    // ÿ���඼�����˸����͵Ķ������������ʼ������ͨ������һ���������캯�������������ĳ�ʼ����
    // ������඼�ṩ��Ĭ�Ϲ��캯������������Ĭ�Ϲ��캯������ô�Ϳ����ڶ������ı���ʱ������ʽ�س�ʼ��������
    // û��Ĭ�Ϲ��캯�������ͣ�ÿ�����嶼�����ṩ��ʽ�ĳ�ʼ��ʽ��

    int * pi = &ival;
    int * pi1 = new int;                // ��̬����һ��int���Ͷ���δ��ʼ��
    int * pi2 = new int();              // ��̬����һ��int���Ͷ��󣬳�ʼ��0
    int * pi3 = new int(1024);          // ��̬����һ��int���Ͷ��󣬳�ʼ��1024
    int * pi4 = new int[1024];          // ��̬����һ���������δ��ʼ��
    int * pi5 = new int[1024]();        // ��̬����һ��������󣬳�ʼ��0
    // int * pi6 = new int[1024](1024); // wrong

    char * p1 = new char;              // ������������ͬ
    char * p2 = new char();
    char * p3 = new char('a');
    char * p4 = new char[1024];
    char * p5 = new char[1024]();

    std::string * p_str1 = new std::string;
    std::string * p_str2 = new std::string();
    std::string * p_str3 = new std::string("abc");
    std::string * p_str4 = new std::string[1024];
    std::string * p_str5 = new std::string[1024]();
    std::string * p_str6 = new std::string[1]; // delete [] p_str6 is ok compared to delete [] p_str1

    delete pi1;
    delete pi2;
    delete pi3;
    delete [] pi4;
    delete [] pi5;

    delete p1;
    delete p2;
    delete p3;
    delete [] p4;
    delete [] p5;

    // delete [] p_str1; exception happened
    delete p_str1;
    delete p_str2;
    delete p_str3;
    // delete p_str4; exception happened
    delete [] p_str4;
    delete [] p_str5;
    delete [] p_str6;
    return 0;
}
