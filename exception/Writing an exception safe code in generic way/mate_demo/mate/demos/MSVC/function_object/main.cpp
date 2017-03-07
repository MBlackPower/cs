// Negate.cpp
#include <iostream>
using namespace std;

class Negate
{
public:
    Negate()
    {
        std::cout << "template <class T> constructor" << std::endl;
    }
    template<class T> T operator()(T const & t) const
    {
        return -t;
    }
    ~Negate()
    {
        std::cout << "template <class T> destructor" << std::endl;
    }
};

void Callback(int n, Negate const & neg) // ����һ����������
{
    n = neg(n);  // �������ص�()��������n����negate����
    cout << n << endl;
}

int main(int argc, char * argv[])
{
    // ���÷�ʽһ
    // ��ʱ�����ǲ��Ǿ�����������򰡣�callback������һ�������β�
    // �󶨵�������������ʱ�����ǲ��������⣬��������ʱ����
    // �ܹ���ֵ�callback����������ô��û�����⣬�ҿ���ͨ������
    // template<class T>�������������˽⣬ͨ�����ԣ������������ӵ�
    // ���۾��ǿ��Զ���һ���βΰ󶨵�һ����ʱ�����ʵ��
    Callback(5, Negate());

    // ���÷�ʽ��
    //Negate neg;
    //cout << neg(9.99999) << endl;
    //cout << neg(__int32(39999999)) << endl;

    return 0;
}