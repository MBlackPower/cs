#include <iostream>
#include <string>
using namespace std;
int main()
{
    string strArr1[] = { "Trend", "Micro", "Soft" };
    string *pStrArr1 = new string[2];
    pStrArr1[0] = "US";
    pStrArr1[1] = "CN";
    string s="aaaaaaaaaaaaaaabbbbbbaaaaaaaaaaaaaaaaaa";
    string b="a";

    cout << sizeof(s) << endl;
    cout << sizeof(b) <<endl;
    cout << sizeof(string) << endl;
    cout << sizeof(strArr1) << endl;
    cout << sizeof(pStrArr1) << endl; // �������ϣ���������32Ҳ��������sizeof(string)
    // �����Ҳ���Ϊʲôsizeof(string)��16����   
    for (int i = 0; i < sizeof(strArr1) / sizeof(string); i++)
        cout << strArr1[i];
    //	for (int j = 0; j < sizeof(pStrArr1) / sizeof(string); j++)
    for (int j = 0; j < sizeof(pStrArr1) * 8 / sizeof(string); j++)
        cout << pStrArr1[j];

    cout << endl;
    return 0;
}              