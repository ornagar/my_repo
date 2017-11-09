//
// Created by xyz on 09/11/17.
//

#include "Derived.h"

Derived::Derived(int a, double b) : Base(a, b) {}

int Derived::getM_a() const {
    return Base::getM_a();
}

void Derived::setM_a(int m_a) {
    Base::setM_a(m_a);
}

double Derived::getM_b() const {
    return Base::getM_b();
}

void Derived::setM_b(double m_b) {
    Base::setM_b(m_b);
}


