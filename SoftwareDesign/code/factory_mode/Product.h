#ifndef _PRODUCT_H_
#define _PRODUCT_H_

/*
Ϊ������ھۣ�Cohesion��������ϣ�Coupling�������Ǿ���������һЩ��Ĺ����ӿ����γɳ��������߽ӿڡ�
�������ǿ���ͨ������һ��ָ������ָ����ָ��ʵ�ʵ�����ʵ�֣��ﵽ�˶�̬��Ŀ�ġ�
*/
class Product
{
public:
	virtual ~Product() = 0;
protected:
	Product();
private:
};

class ConcreteProduct:public Product
{
public:
	~ConcreteProduct();
	ConcreteProduct();
protected:
private:

};
#endif //~_PRODUCT_H_

