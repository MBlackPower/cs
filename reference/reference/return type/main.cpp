#include <iostream>

class C {
public:
    // int & getRef() const // һ�����ԣ����Ǵ��
    // int const & getRef() const // ��һ��const˵�������Ա���������޸ĳ�Ա��ǰһ��const��ʾ����
                                  // ���ݳ�Աn������Ϊ��һ�����ð󶨶��ı�
    int & getRef() 
    {
        return n;
    }
    int getN() const
    {
        return n;
    }

private:
    int n;
};

int main()
{
    C c;
    // int k = c.getN(); // ���������仰�Ĳ�ͬ���Ǻǡ�
    int& k = c.getRef();
    k = 7;
    std::cout << c.getN() << std::endl;
    return 0;
}