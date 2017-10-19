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
#include <iostream>

#include "complex.hpp"
using namespace ilrd;

int main()
{
    Complex c1(14, 3);
    Complex c2(c1);
    Complex c3;

    c3 = c2;

    if (c3 == c2){
        if (c1 != c2){
        std::cout << "fail" << std::endl;
        }
    }
    
    Complex c4 = c1 + c2;
    if (c4 != (c1 + c2)) {
		std::cout << "fail" << std::endl;
	}
    
    c3 = c1 - c2;
    if (c3 == 0) {
		std::cout << "(14 + 3i) - (14 + 3i) = "
						<< c3 << std::endl;
	}
	else {
		std::cout << "fail" << std::endl;
	}

	Complex c5 = c4;

	std::cout << "("<< c4 << ")"<< " * " << "("<< c2 << ")" << " = ";
	c4 *= c2;
	std::cout << c4 << std::endl;

	std::cout << "("<< c5 << ")"<< " / " << "("<< c2 << ")" << " = ";
	c5 /= c2;
	std::cout << c5 << std::endl;


	std::cout << "abs(" << c4 << ") = " << c4.abs() << std::endl;

	std::cout << "conjugate(" << c4 << ") = " << c4.conjugate() << std::endl;

	std::cin >> c5;

	std::cout << "c5 = " << c5 << std::endl;

	std::cout << c5 * c2 + c3 / c1 << std::endl;

	Complex c6(28, 5);
	std::cout << Cos(c6) << std::endl;

	Complex c7(28, 5);
	std::cout << Sin(c7) << std::endl;

    return 0;
}
