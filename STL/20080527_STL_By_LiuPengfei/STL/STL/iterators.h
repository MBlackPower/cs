#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>

#include <functional>// greater��Ҫ
#include <fstream>
using namespace std;

inline void TestIterators()
{
    int ia[] = { 0, 1, 1, 2, 3, 5, 5, 8 };
    vector<int> ivec( ia, ia+8 );
    vector<int> vres;

    // reverse iterator
    vector<int>::reverse_iterator rIt = ivec.rbegin();//����
    // ���ִ�� rIt++, ʵ��Ч������ivec.back()--
    // ���������� vector
    sort( ivec.begin(), ivec.end() );
    // �Խ�������vector
    sort( ivec.rbegin(), ivec.rend() );


    // insert iterator
    vector<int> vecInsert;
    back_insert_iterator<vector<int> > it( vecInsert );//��ʼ��
    it = 3;// ��3����vecInsert.

    // unique_copy() ������ vres.push_back() ����
    // ��ivec�������ظ�Ԫ���޳�����vres��
    unique_copy( ivec.begin(), ivec.end(), back_inserter( vres ));

    // Error, vector���ṩpush_front������
    // unique_copy( ivec.begin(), ivec.end(), front_inserter( vres ));
    
    // ��ivec�������ظ�Ԫ���޳��������vres��
    unique_copy( ivec.begin(), ivec.end(), inserter( vres, vres.begin() ));

    // iostream iterator
    istream_iterator< int > input( cin );//��ʼ��
    istream_iterator< int > end_of_stream;
    vector<int> vec;
    copy ( input, end_of_stream, inserter( vec, vec.begin() ));// ����
    sort( vec.begin(), vec.end(), greater<int>() );// �Ӵ�С����
    ostream_iterator< int > output( cout, " " );
    unique_copy( vec.begin(), vec.end(), output );// �޳���ͬԪ�ز�����


    // �����׼���벢����
    copy( istream_iterator< int >( cin ),
            istream_iterator< int >(),
            ostream_iterator< int >( cout ));
}