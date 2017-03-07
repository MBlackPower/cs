#include <iostream>

class father {
public:
    //father() { i = 10; j = 20; } // ��������
    father() : i(10), j(20) { }     // good
    virtual void print() const
    {
        std::cout << i << " " << j;
    }
private:
    int i;
    int j;
};

class son: public father {
public:
    //son() { m = 30; } // ��������
    son() : m(30) {}    // ������������������һ��
    //son() : father(), m(30) {}
    void print() const
    {
        father::print(); // ��֪�����������ò��ã�
        std::cout << " " << m;
    }
private:
    int m;
};

int main()
{
    father* p = new son;
    p->print(); // ��̬��

    son aa;
    father const & bb = aa;
    bb.print(); // ��̬��
    std::cout << std::endl;

    son a;
    father b = a; // ����ת�������ܻ�ض�
    b.print();
    std::cout << std::endl;

    return 0;
}
