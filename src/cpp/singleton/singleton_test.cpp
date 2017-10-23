#include <iostream>
#include <string>

#include "singleton.hpp"

int main()
{
    std::string& s = Singleton<std::string>::get_instance();
    std::string& f = Singleton<std::string>::get_instance();
    
    f = "fun fun fun";
    std::cout << s << std::endl;
    std::cout << f << std::endl;
}
