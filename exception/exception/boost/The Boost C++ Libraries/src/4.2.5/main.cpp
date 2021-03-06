#include <boost/signal.hpp> 
#include <iostream> 

void func1() 
{ 
  std::cout << "Hello" << std::endl; 
} 

void func2() 
{ 
  std::cout << ", world!" << std::endl; 
} 

int main() 
{ 
  boost::signal<void ()> s; 
  s.connect(func1); 
  s.connect(func2); 
  s.disconnect(func2); 
  s(); 
} 