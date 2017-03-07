#include <iostream>
class CBookBase {
public:
    std::string GetISBN() // ��������̳еĺ��������Զ���Ϊ�麯����
    {
        return isbn;
    }

    virtual void GetTitle() // �������า�ǵĺ���һ��Ҫ����Ϊ�麯����
    {
        std::cout << "CBookBase::GetTitle" << std::endl;
    }

    virtual void GetColor() = 0; // ������븲�ǵĺ�������Ϊ���麯����

private:
    std::string isbn;
    int title;
    int color;
};

class CBookChild1 : public CBookBase {
public:
    /*
    std::string GetISBN() // ����û�ж�����������ǶԵģ���Ϊ��Ƹ����ʱ�����Ҫ������
    {
        ////
    }
    */
    void GetTitle()
    {
        std::cout << "CBookChild1::GetTitle" << std::endl;
    }

    void GetColor()
    {
        std::cout << "CBookChild1::GetColor" << std::endl;
    }
};

class CBookChild2 : public CBookBase {
public:
    void GetTitle()
    {
        std::cout << "CBookChild2::GetTitle" << std::endl;
    }

    void GetColor()
    {
        std::cout << "CBookChild2::GetColor" << std::endl;
    }
};
