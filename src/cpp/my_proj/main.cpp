#include <iostream>
#include "Base.h"
#include "Derived.h"

int main() {

    Base b;
    Derived d;
    Base& bptr = b;
    Base& dptr = d;

    std::cout << bptr.getM_a() << " " << bptr.getM_b() << std::endl;
    std::cout << dptr.getM_a() << " " << dptr.getM_b() << std::endl;




    return 0;
}