/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Complex Numbers library.                   #################################
 *                                             ##########    ####       ########
 *  Or Nagar                                   ########  ####  ##  ###  ########
 *  14-09-2017                                 ########  ####  ##     ##########
 *  12:00:00                                   ########  ####  ##  ###  ########
 *                                             ##########    ####  ###  ########
 *                                             #################################
 *
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <iostream>     //ostream, istream

#include <cstdlib>      //strtod()
#include <cctype>       //isdigit()

#include "complex.hpp"

namespace ilrd {

Complex& Complex::operator*=(const Complex& other)
{
    double temp_real = m_real;
    double temp_imag = m_imag;

    m_real = ((m_real * other.m_real) - (m_imag * other.m_imag));
    m_imag = ((temp_real * other.m_imag) + (temp_imag * other.m_real));

    return *this;
}

std::istream& operator>>(std::istream& is, Complex& num)
{
    char buffer[30];
    char* ptr = buffer;

	is.getline(buffer, 30);
	
	while (!isdigit(*ptr))
	{
		++(ptr);
	}
	
	num.real(strtod(ptr, &ptr));
	
	while (!isdigit(*ptr))
	{
		++(ptr);
	}

	num.imag(strtod(ptr, &ptr));
	
	return is;
   
}

} //namespace ilrd




