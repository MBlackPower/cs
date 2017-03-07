#include <cassert>
#include <iostream>
#include <string>
template <class elemType>
class CArray {
public:
    friend std::ostream& operator<<(std::ostream& os, const CArray& arr) 
    {
        for (int i = 0; i != arr.size(); i++)
        {
            os << arr[i] << ' ';
        }
        return os;
    }
public:
    explicit CArray(int sz = DefaultArraySize)
    //CArray(int sz = DefaultArraySize)
    {
        Init(0, sz);
    }
    CArray(elemType* arr, int array_size)
    {
        Init(arr, array_size);
    }
    CArray(const CArray& rhs)
    {
        Init(rhs.ia, rhs.m_iSize);
    }
    ~CArray()
    {
        delete[] ia;
    }
public:
    int size() const
    {
        return m_iSize; 
    }
    virtual elemType& operator[](int index) const
    {
        assert(index >= 0 && index < size());
        return ia[index];
	}
	bool operator==(const CArray&) const;
	bool operator!=(const CArray&) const;
	CArray& operator=(const CArray&);
protected:
	void Init(elemType* arr, int sz);
	int m_iSize;
	elemType* ia;
    static const int DefaultArraySize = 12;
};

template <class elemType>
void CArray<elemType>::Init(elemType* arr, int sz)
{
	m_iSize = sz;
	ia = new elemType[m_iSize];
	for (int ix = 0; ix != m_iSize; ix++)
	{
		if (!arr)
		{
			//ia[ix] = 0; // ����ԭ����CIntArray��д�����ⲻ���ã���elemTypeΪstringʱ

			// �������������������һ�������elemTypeû��Ĭ�Ϲ��캯����ʱ������������elemTypeΪint����
			//elemType a; // Ϊstringʱ��aΪһ�����ַ�����������string���Ĭ�Ϲ��캯�����������嵱������������ʱ
			//ia[ix] = a; // ��Ϊ���������ں����ڲ�����ʱ���ǲ���ʼ���ģ���ִ�������䴦�ͻ����

			//elemType b = elemType(); // �������ǿ��Եģ������������������������ʼ��Ϊ�����൱���ⲿ����ʱ��Ĭ��ֵ
			//ia[ix] = b;              // ����������õ�������Ҳ������Ĭ�Ϲ��캯�������ͣ��������Ĭ�Ϲ��캯����ʼ���������

			ia[ix] = elemType();   // ����д�������ǵȼ۵ģ����������ǹ��캯�����ǲ�����ֵ����ô������������Ķ���ֵ�أ�
			// c++ primer 3 page70ÿ�������������Ͷ�֧��һ������Ĺ��캯���﷨���ɽ������ʼ��Ϊ0��
			// int ival = int();
			// double dval = double();
		}
		else
		{
			ia[ix] = arr[ix];
		}
	}
}
