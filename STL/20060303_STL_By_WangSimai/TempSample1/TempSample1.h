//TempSample1.h
#include "stdafx.h"

// ��������Ͷ����Լ���ģ����
template<  class T >
class Test1
{
public:
    Test1( void ){};
    ~Test1( void ){};
   
    //��ζ���ͳһ�Ĵ�����
    void OutputMsg( LPCSTR lpszMsg );

    void Textincpp( void );
};

//��ζ���ͳһ�Ĵ�����
template< class T >
 void Test1<T>::OutputMsg( LPCSTR lpszMsg )
{
    // ��ζ���ͳһ�Ĵ�����
    T Outer;
    Outer.OutMsg1( "template< class T > Test1<T>::OutputMsg1 ->", lpszMsg );
    return;
}