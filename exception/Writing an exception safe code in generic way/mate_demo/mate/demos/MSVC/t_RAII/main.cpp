#include "t_RAII.h"

void fcn() throw() // ����Ա��Ϊ���׳��κ��쳣
{
    Sleep(1000);
    //Resource<int> const res(1024);
    Resource<std::string> const res(1024);
}

void fcn2() throw(std::exception) // ����Ա��Ϊ������������׳�std::exception���ͻ��������������͵��쳣
{
    Sleep(1000);
    //Resource<std::string> const res(1);
    Resource<int> const res(1000);
    //Resource<char> const res(1000);
    throw std::exception("a! yi chang le!!!");
}

int func_pointer(int const & i)
{
    int j = i + 1;
    return j;
}

int main()
{
    //while(true) // ������֤�ҵ�RAII�ǲ��Ǻ��ã�һ��ע�������е�release��Ȼ��ȡ��ע�ͣ�ͨ������������ܿ��ĺ����
    //{
    //    fcn();
    //}
    // ������ע���������������������쳣ʱ���ܷ���Ч
    //while(true)
    //{
    //    try
    //    {
    //        fcn2();
    //    }
    //    catch(std::exception const & e)
    //    {
    //        std::cout << e.what() << std::endl;
    //    }
    //}
    
    int i = 10;
    i = func_pointer(i);
    std::cout << i << std::endl;

    int (*p_func)(int const &) = func_pointer;
    i = p_func(i);
    std::cout << i << std::endl;

    return 0;
}