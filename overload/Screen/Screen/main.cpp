#include "Screen.h"
// const non_const member function overload
// const ��const ���س�Ա����
int main()
{
    Screen myScreen(2, 3, "123456789");
    myScreen.display(cout);
    const Screen myScreen2(2, 3, "123456789");
    myScreen2.display(cout);
    myScreen.max();
}