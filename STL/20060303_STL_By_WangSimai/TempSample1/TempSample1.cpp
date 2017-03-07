// TempSample1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "TempSample1.h"
#include "TempSample11.h"

//ʹ��STLģ���std�����ռ�
#include <vector>
using namespace std;

class Out1
{
public:
    Out1( void ){};
    ~Out1( void ){};

    //��ζ���ͳһ�Ĵ�����
    void OutMsg( LPCSTR lpszMsg )
    {
        cout << " Class Out1::OutMsg( " << lpszMsg << " )" << endl;
    }
    
    void OutMsg1( LPCSTR lpszParent, LPCSTR lpszMsg )
    {
        cout <<  lpszParent <<" Class Out1::OutMsg1( " << lpszMsg << " )" << endl;
    }

    void OutMsg2( LPCSTR lpszRoot , LPCSTR lpszParent, LPCSTR lpszMsg )
    {
        cout << lpszRoot <<  lpszParent <<" Class Out1::OutMsg2( " << lpszMsg << " )" << endl;
    }

    
};

//��ζ���ͳһ�Ĵ�����
template< class T >
void Test1<T>::Textincpp( void )
{
    T outer;
    outer.OutMsg( " template<class T> void Test1<T>::Textincpp()" );
    
}


//����ģ��������
typedef Test1< Out1 > OutTest1_type;
typedef Test2< Out1 > OutTest2_type;

//������ģ���������Ͷ�����һ��ģ����
typedef Test1< OutTest2_type > OutTestExt_type; 

//ʹ��STLģ���std�����ռ�
typedef vector<OutTestExt_type> Vector_type;

//��ζ���ģ�溯��
template< class T > void GTest( vector<T>&  Outer, LPCSTR lpszMsg )
{
        Outer.begin()->OutputMsg(lpszMsg );
}
//��ζ���ģ�溯��
template< class T > void GTest1( Test1<T>&  Outer, LPCSTR lpszMsg )
{
        Outer.OutputMsg(lpszMsg );
}


int main(int argc, char* argv[])
{
//ģ�����ʵ����	
    OutTest1_type test1;
    OutTest2_type test2;
    OutTestExt_type test3;
    
    test1.Textincpp();

    test1.OutputMsg( "test 1 output" );
    //ʹ��ģ�溯��
    GTest1( test3, "TestTemplatFunction GTest1() " );

    test2.OutMsg( "test 2 output" );

    test3.OutputMsg( "test 3 output" );

    //ģ�����ʵ����
    Vector_type vOut;
    vOut.push_back( test3 );

    //ʹ��ģ�溯��
    GTest( vOut, "TestTemplatFunction GTest() " );

    vOut.clear();

////////////////////////////////
// output messages in prompt screen //
////////////////////////////////
//Class Out1::OutMsg(  template<class T> void Test1<T>::Textincpp() )
//template< class T > Test1<T>::OutputMsg1 -> Class Out1::OutMsg1( test 1 output )
//template< class T > Test1<T>::OutputMsg1 ->template< class T > Test2<T>::OutputMsg2 -> Class Out1::OutMsg2( TestTemplatFunction GTest1()  )
//template< class T > Test2<T>::OutputMsg1 -> Class Out1::OutMsg1( test 2 output )
//template< class T > Test1<T>::OutputMsg1 ->template< class T > Test2<T>::OutputMsg2 -> Class Out1::OutMsg2( test 3 output )
//template< class T > Test1<T>::OutputMsg1 ->template< class T > Test2<T>::OutputMsg2 -> Class Out1::OutMsg2( TestTemplatFunction GTest()  )

	return 0;
}

