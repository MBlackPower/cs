#include <deque> 

int main() 
{ 
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; //������һ������ 
    std::deque<int> y(a, a + 10); //����������ǰ10������ʵҲ����ȫ����Ԫ������ʼ��һ��deque 
    return 0; 
} 