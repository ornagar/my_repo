#include <cstring>  //strlen
#include <iosfwd>   //istream, ostream
#include <new>      //(std::nothrow)
#include <cstdlib>  //(malloc(), realloc())
#include <sstream>  //get

#include "string.hpp"

const size_t STRING_SIZE = 124;

namespace ilrd
{

inline String& String::operator=(const String& rhs)
{
    String temp(rhs);
    
    delete[] m_cp;
    m_cp = temp.m_cp;
    temp.m_cp = NULL;
    
    return *this;
}


String& String::operator+=(const String& rhs)
{
    char *temp = new char[strlen(m_cp) + 1 + strlen(rhs.m_cp)];

    strcpy(temp, m_cp);

    if (0 != strcat(temp, rhs.m_cp)){
        delete[] m_cp;
        m_cp = temp;
    }

    return *this;
}


std::istream& operator>>(std::istream& is, String& str)
{
    String temp;
    char new_str[STRING_SIZE];

    // takes every iteration a buffer of 124B and concats it to temp (String).
    while ('\n' != (new_str[0] = is.get())) {
        is.get((new_str + 1), STRING_SIZE - 2);
        temp += new_str;
    }

    str = temp;

    return is;
}

}//namespace ilrd;
