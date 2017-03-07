#include "Screen.h"

Screen::Screen(index h, index w, string c)
{
    height   = h;
    width    = w;
    contents = c;
}

Screen & Screen::display(ostream & os)
{
    do_display(os);
    return (*this);   //�����ã�����screen����
}

Screen const & Screen::display(ostream & os) const
{
    do_display(os);
    return (*this); 
}

void Screen::do_display(ostream & os) const
{	
    cout << "" << endl;
    string::size_type index = 0;
    while (index != contents.size())
    {
        os << contents[index];
        if((index + 1) % width == 0)
        {
            os << endl;
        }
        ++index;
    }
}

Screen::index Screen::max()
{
    return height;
}
