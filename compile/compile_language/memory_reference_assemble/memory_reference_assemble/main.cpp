int main() // alt + 8��ʾ������
{
    int i = 10;
    int j = 20;
    int& m = i;
    int k = 30;
    k = i + j;
    k = m + j;
    return 0;
}           