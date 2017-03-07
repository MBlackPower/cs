#include <cassert>
#include <iostream>
class CIntArray {
public:
    // friend std::ostream& operator<<(std::ostream& os, CIntArray& arr);
    // ��ʼ��ʱ��֪��Ϊʲô�Ҳ���������Ϊconst CIntArray������������û�аѺ���CIntArray::operator[]����Ϊconst��Ա������
    // ��Ϊconst����ֻ�ܵ���const��Ա���������Ե�arrΪconst����ʱ�����ǲ��ܵ���operator[]��������ģ�����arr[i]�ᱨ��
    friend std::ostream& operator<<(std::ostream& os, const CIntArray& arr) 
    {
        for (int i = 0; i != arr.size(); i++)
        {
            os << arr[i] << ' ';
        }
        return os;
    }
public:
    explicit CIntArray(int sz = DefaultArraySize);
    CIntArray(int* array, int array_size);
    CIntArray(const CIntArray& rhs);
    ~CIntArray()
    {
        delete[] ia;
    }
	bool operator==(const CIntArray&) const;
	bool operator!=(const CIntArray&) const;
	CIntArray& operator=(const CIntArray&);
    int size() const
    {
        return m_iSize; // �����������������κκ������á�
    }
    int& operator[](int index) const
    {
        assert(index >= 0 && index <size());
        return ia[index];
    }
protected:
    void Init(int* arr, int sz);
    int m_iSize;
    int* ia;
    static const int DefaultArraySize = 12;
};