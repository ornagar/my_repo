//
// Created by xyz on 09/11/17.
//

#include "Base.h"
Base::Base(int a, double b) : m_a(a), m_b(b) {}


int Base::getM_a() const {
    return m_a;
}

void Base::setM_a(int m_a) {
    Base::m_a = m_a;
}

double Base::getM_b() const {
    return m_b;
}

void Base::setM_b(double m_b) {
    Base::m_b = m_b;
}
