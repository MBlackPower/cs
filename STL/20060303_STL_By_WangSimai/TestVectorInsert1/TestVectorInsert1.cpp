 // TestVectorInsert1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
// ����ͷ�ļ� #include<vector>
#include <vector>

// ʹ�������ռ� using namespace std;
using namespace std;

// �����Զ������Ͳ����䴴��ʵ�� 
typedef vector<int> IntArray_type;

int main(int argc, char* argv[])
{
	// ʵ��������
    IntArray_type Vecint_1;

	// ����ʹ��std::vector�ж�������Ͷ��������ʹ��
	// ���������
    IntArray_type::const_iterator constIt = Vecint_1.begin();
    IntArray_type::iterator It = Vecint_1.begin();
    IntArray_type::iterator It1 = Vecint_1.begin();
	// ���巴�������
    IntArray_type::reverse_iterator rIt = Vecint_1.rbegin(); 
	// �������
    IntArray_type::size_type Vecint_1_sz = 10;
    IntArray_type::size_type Vecint_1_cnt = 0;
	// ����Ԫ�����ͱ���
    IntArray_type::value_type Vecint_1_Val = 6;

	// Ϊvector<int>���ٵĴ洢�����ռ�
    cout << "the capacity of Vecint_1 is " << Vecint_1.capacity() << endl;

	// ��������ֵ
    Vecint_1.assign( Vecint_1_sz, Vecint_1_Val );

	// �۲�洢�����ռ�
    cout << "the capacity of Vecint_1 is " << Vecint_1.capacity() << endl;

	// �������Ԫ��
	// ��ʹ�õ�������������Ԫ�صķ���
    for ( constIt = Vecint_1.begin(); constIt != Vecint_1.end(); constIt++ )
    {
        cout << *constIt << " ";
    }
    cout << endl;

    Vecint_1_Val = 12345;

	// begin��������ָ��������һ��Ԫ�صĵ�����
    It = Vecint_1.begin();

	// �ı��һ��Ԫ�ص�ֵ��iterator���Ըı�Ԫ�ص�ֵ
    *It = 1;
	// �ƶ�ָ���Ԫ��
    It = It+4;

    constIt = Vecint_1.begin();
	// const_iterator���ܸı�Ԫ�ص�ֵ
	// *constIt = 5678;
    constIt++;
    
    // ����ֵ
    It1 = Vecint_1.insert( It+4, Vecint_1_Val );

    // back() �����������һ��Ԫ�ص����� 
    int& nback = Vecint_1.back();
    nback++;

	// back() �����������һ��Ԫ�ص�const reference
    const int& ncback = Vecint_1.back();
//    ncback++;

	// front() �����������һ��Ԫ�ص�����
    int& nFront = Vecint_1.front();

	// size() ������������Ԫ�ظ���
    Vecint_1_cnt = Vecint_1.size();
	
	// �۲�Ԫ�ظ���
    cout << "the count of elements int Vecint_1 is " << Vecint_1_cnt << endl;

	// �۲�洢�����ռ�
    cout << "the capacity of Vecint_1 is " << Vecint_1.capacity() << endl;

	// �����趨������С
    Vecint_1.resize( 6 );

	// �۲�洢�����ռ�
    cout << "the capacity of Vecint_1 is " << Vecint_1.capacity() << endl;

	// �������Ԫ��
	// ��ʹ�õ�������������Ԫ�صķ���
    for ( constIt = Vecint_1.begin(); constIt != Vecint_1.end(); constIt++ )
    {
        cout << *constIt << " ";
    }
    cout << endl;
    cout << endl;

	// �����������Ԫ��
	// ��ʹ�õ�������������Ԫ�صķ���
    for ( rIt = Vecint_1.rbegin(); rIt != Vecint_1.rend(); rIt++ )
    {
        cout << *rIt << " ";
    }
    cout << endl;
    cout << endl;

	// �������
    Vecint_1.clear();

	// �۲�Ԫ�ظ���
    Vecint_1_cnt = Vecint_1.size();
    cout << "After clear Vecint_1.size() = " << Vecint_1_cnt << endl;

	// �������Ԫ��
	// ��ʹ�õ�������������Ԫ�صķ���
    for ( constIt = Vecint_1.begin(); constIt != Vecint_1.end(); constIt++ )
    {
        cout << *constIt << " ";
    }
    cout << endl;

	// �۲�洢�����ռ�
    cout << "the capacity of Vecint_1 is " << Vecint_1.capacity() << endl;

	// ���ñ����ռ�
    Vecint_1.reserve( 21 );

	// �۲�洢�����ռ�
    cout << "the capacity of Vecint_1 is " << Vecint_1.capacity() << endl;

	return 0;
}

