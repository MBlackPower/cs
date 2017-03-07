#include <algorithm>
#include <vector>
#include <list>
#include <functional>
#include <iostream>
#include <numeric>
using namespace std;
template< class Type >
void printElem( Type t){ cout << t << " ";};

//�����㷨
void TestSearch( vector<int> &ivec )
{
    // �����㷨find and find_if
    // ���ҵ�һ������2��Ԫ��
    vector<int>::iterator it = find( ivec.begin(), ivec.end(), 2 );
    // �������һ������2��Ԫ��
    vector<int>::reverse_iterator rit = find( ivec.rbegin(), ivec.rend(), 2 );
    // ���ҵ�һ������3��Ԫ��
    it = find_if( ivec.begin(), ivec.end(),
        bind2nd( greater<int>(), 3));
    // ���ҵ�һ������3��С��8�����ܱ�5������Ԫ��
    //     it = find_if( ivec.begin(), ivec.end(), 
    //         compose2( logical_and<bool>(),
    //                   compose2( logical_and<bool>(),
    //                             bind2nd( greater<int>(),3),
    //                             bind2nd( less<int>(), 8) ),
    //                   not2(bind2nd( modulus<int>(), 5 )))));
    
    // ���ҵ�һ���ܱ�5������Ԫ��
    it = find_if( ivec.begin(), ivec.end(), not1( bind2nd( modulus<int>(), 5 )));
    if ( it != ivec.end())
    {
        int nPos = it - ivec.begin() + 1;
        cout << "The found value moduled by 5 is " << *it
            << " Position " << nPos << endl;
    }
}
// �����㷨
void TestSort( vector<int> &ivec )
{
    sort( ivec.begin(), ivec.end());// ��С��������
    cout << "After sort by less: ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    sort( ivec.begin(), ivec.end(), greater<int>());// �Ӵ�С����
    cout << "After sort by greater: ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    sort( ivec.rbegin(), ivec.rend());// �Ӵ�С���У�ע������һ�㷨������
    partial_sort( ivec.begin(), ivec.begin()+5, ivec.end());// �ų���С��5�������಻��
    cout << "After sort by partial_sort: ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    // �Ե�5��Ԫ��Ϊ�ֽ磬С�ڵ�����ߣ����ڵ��ڵ����ұߣ����Ժ�find����ʹ��
    nth_element( ivec.begin(), ivec.begin()+4, ivec.end());
    cout << "After nth_element: ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

// ɾ�����滻�㷨
void TestDeleteAndReplace( vector<int> &ivec )
{
    vector<int>::iterator it = remove( ivec.begin(), ivec.end(), 5 );// ɾ�����е���5��Ԫ��
    // ע�⣬�������ɾ�������ǽ�Ҫɾ����Ԫ�ط���it֮��
    // ���һ�ı�ԭ�е�ֵ,����һ����Ҫ�ٵ���earse����
    // ������5��Ԫ��ɾ��
    cout << "after remove :";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    it = remove_if( ivec.begin(), ivec.end(), bind2nd(greater<int>(), 5));
    cout << "after remove_if:";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    it = unique( ivec.begin(), ivec.end() );// �޳������ظ���Ԫ��
    // ע������ͬremove, �������ɾ��, ���һ�ı�ԭ�е�ֵ��Ҳ��Ҫ��earse����ʹ��
    cout << "after unique :";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

// ��������㷨
void TestPermutation( vector<int> &ivec )
{
    while ( next_permutation( ivec.begin(), ivec.begin()+3 ))
    {
        copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
}
// ��ֵ�㷨
void TestNumeric( vector<int> &ivec )
{
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    int nSum = accumulate( ivec.begin(), ivec.end(), 0 );
    cout << " The sum is " << nSum << endl;
}
// ����������㷨
void TestGenerateAndTransform( vector<int> &ivec, int* ia )
{
    void( *pif)(int) = printElem;
    cout << "after for_each:";
    for_each( ivec.begin(), ivec.end(), pif );// ��ӡ����Ԫ��
    cout << endl;
    // ������Ԫ��+1
    cout << "after transform for increase element by 1:";
    transform( ivec.begin(), ivec.end(), ivec.begin(), bind2nd(plus<int>(), 1));
    for_each( ivec.begin(), ivec.end(), pif );
    cout << endl;
    // ������������Ӻ�浽��һ��������
    cout << "after transform for plus the elements of two vectors:";
    transform( ivec.begin(), ivec.end(), ia, ivec.begin(), plus<int>());
    for_each( ivec.begin(), ivec.end(), pif );
    cout << endl;
}
// ��ϵ�㷨
void TestRelation( vector<int> &ivec )
{
    vector<int>::iterator it = max_element( ivec.begin(), ivec.end());
    cout << "max is " << *it << " position " << it-ivec.begin()+1 << endl;
    sort( ivec.begin(), ivec.end());
    cout << "after sort: ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    //�����ܹ�����5�������ƻ������λ��
    int nInsertNum = 4;
    it = lower_bound( ivec.begin(), ivec.end(), nInsertNum );
    cout << "Lower_bound ";
    cout << "found the insert position of " << nInsertNum<<" is " << it - ivec.begin();
    cout << endl;
}
// ���㷨
void TestSet( vector<int> &ivec, int* ia )
{
    vector<int> vecUninRes;
    for ( int i =0; i < ivec.size(); i++)
    {
        *(ia+i) = i;
    }
    cout << "another array is: ";
    copy( ia, ia+ivec.size(), ostream_iterator<int>(cout, " "));
    cout << endl;
    set_union( ivec.begin(), ivec.end(), ia, ia + 8, back_inserter( vecUninRes ));
    cout << "after set_union: ";
    copy( vecUninRes.begin(), vecUninRes.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    vector<int> vecDifRes;
    set_difference( ivec.begin(), ivec.end(), ia, ia+8, back_inserter( vecDifRes ));
    cout << "after set_difference: ";
    copy( vecDifRes.begin(), vecDifRes.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

void TestHeap( vector<int> &ivec )
{
    make_heap( ivec.begin(), ivec.end());// ������
    cout << "after make_heap: ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    ivec.push_back( 4 );
    push_heap( ivec.begin(), ivec.end());
    cout << "after push_heap: ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

inline void TestAlgorithms()
{
    int ia[] = { 1, 0, 5, 2, 3, 1, 5, 8 };
    vector<int> ivec( ia, ia+8 );
    cout << "The initial vector is ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    
//     TestSearch(ivec);//�����㷨    
//     TestSort(ivec);// �����㷨    
//     TestDeleteAndReplace(ivec);// ɾ�����滻�㷨    
//     TestPermutation(ivec);// ��������㷨    
//     TestNumeric(ivec);// �����㷨    
//     TestGenerateAndTransform( ivec, ia );// ���ɺ�����㷨    
//     TestRelation(ivec);// ��ϵ�㷨    
//     TestSet(ivec, ia);// �����㷨   
//     TestHeap(ivec); // ���㷨   
}