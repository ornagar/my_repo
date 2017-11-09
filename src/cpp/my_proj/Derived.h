//
// Created by xyz on 09/11/17.
//

#ifndef MY_PROJ_DERIVED_H
#define MY_PROJ_DERIVED_H


#include "Base.h"

class Derived: public Base {
public:
    explicit Derived(int a = 0, double b = 0);
    ~Derived() override = default ;

    int getM_a() const override;

    void setM_a(int m_a) override;

    double getM_b() const override;

    void setM_b(double m_b) override;
};


#endif //MY_PROJ_DERIVED_H
