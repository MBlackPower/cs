//TempSample11.h
#include "stdafx.h"

// ��������Ͷ����Լ���ģ����
template<  class T >
class Test2
{
public:
    Test2( void ){};
    ~Test2( void ){};

    //��ζ���ͳһ�Ĵ�����
    void OutMsg( LPCSTR lpszMsg );

    //��ζ���ͳһ�Ĵ�����
    void OutMsg1( LPCSTR lpszParent, LPCSTR lpszMsg );

};

//��ζ���ͳһ�Ĵ�����
template< class T >
 void Test2<T>::OutMsg( LPCSTR lpszMsg )
{
    T Outer;

    Outer.OutMsg1( "template< class T > Test2<T>::OutputMsg1 ->", lpszMsg );

    return;
}

template< class T >
 void Test2<T>::OutMsg1( LPCSTR lpszParent, LPCSTR lpszMsg )
{
    T Outer;

    Outer.OutMsg2( lpszParent, "template< class T > Test2<T>::OutputMsg2 ->", lpszMsg );

    return;
}