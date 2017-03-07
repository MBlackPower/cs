#include <iostream>
class CBook {
public:
	CBook()
    {
        i = 10;
        j = 20;
    }
	int GetJ()              // ���������ʾ���������̳����������û��ʲô˵�ġ�
    {
        return j;
    }
    virtual int GetIJ()     // ���������ʾ�����������า������û��ʲô˵�ġ�
    {
        return i + j;
    }
	virtual int GetI() = 0; // ���������ʾ��������า������û��ʲô˵�ġ�

protected:
	int i;
	int j;
};

class CBookChild : public CBook {
public:
	int GetJ()  // ����̳����������û�������ҵ��������C++��������ĵĴ��� 
    {
        return j + 1;
    }
    int GetIJ() // �㸲�����ң��������ҵ����������������û�и����ң���Ҳ�����㡣
    {
        return i + j + 1;
    }
	int GetI()  // �㸲�����ң�������������������ҵ�����㲻�����ң�����c++���Բ�����Ĵ���
    {
        return i + 1;
    }
};

int main()
{
//  CBook* p = new CBook(); // ����ʵ��������
	CBook* p = new CBookChild();
	CBookChild* q = new CBookChild();
	std::cout << p->GetJ()  << std::endl;
    std::cout << p->GetIJ() << std::endl;
	std::cout << p->GetI()  << std::endl;

	std::cout << q->GetJ()  << std::endl;
    std::cout << q->GetIJ() << std::endl;
    std::cout << q->GetI()  << std::endl;
	return 0;
}
