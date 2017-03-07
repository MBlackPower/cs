//class Resource {
//public:
//    Resource(parms p): r(allocate(p)) { }
//    ~Resource() { release(r); }
//    // also need to define copy and assignment
//private:
//    resource_type *r;           // resource managed by this type
//    resource_type *allocate(parms p);     // allocate this resource
//    void release(resource_type*);         // free this resource
//};

//void fcn()
//{
//    Resource res(args);   // allocates resource_type
//    // code that might throw an exception
//    // if exception occurs, destructor for res is run automatically
//    // ...
//}  // res goes out of scope and is destroyed automatically

#include <exception>
#include <iostream>
#include "Windows.h"

template <class Type> class Resource {
public:
    Resource(int const & number) : r(allocate(number)) { }
    //Resource(int const & number)
    //{
    //    r = allocate(number);
    //}
    ~Resource() { release(r); }
    Type * get_object()
    {
        return r;
    }
private:
    Type * allocate(int const & number) const // ����Ա����Ϊ������������׳��κ��쳣
    {
        std::cout << "allocate 4k bytes " << std::endl;
        return new Type[number](); // С���ű�ʾ��ʼ��Ϊ0������������˵��
                                   // ��linux����仰Ҳ�Ǳ಻���ģ������С�����õ�
                                   // �����Զ�������Ӧ���ǵ���Ĭ�Ϲ��캯������˼
                                   // ��Ĭ�Ϲ��캯�����Զ�������Ӧ���Ǳ��뱨��
    }

    void release(Type * pRes) const throw()   // ����Ա����Ϊ����������׳��κ��쳣
    {
        std::cout << "free 4k bytes " << std::endl;
        delete [] pRes; // []��Ҫ��û�лᵼ���쳣������new�������飬delete�������飬�����쳣����
    }                   // �����windows�£����Ͳ������쳣��new��std::string���͵�����ᷢ���쳣
                        // int * p = new int[1]; ʹ��delete [] p�ǰ�ȫ��
                        // int * p = new int;    ʹ��delete [] p���׳��쳣��
private:
    Type * r;
};
