int main()
{
    int j = 10;
    const int& i = j; // const���ÿ��԰󶨵�non-const����non-const����ȴ���ܰ󶨵�const����
    // i++; wrong
    j++; // ok
    return 0;
}