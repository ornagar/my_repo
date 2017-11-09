//
// Created by xyz on 09/11/17.
//

#ifndef MY_PROJ_BASE_H
#define MY_PROJ_BASE_H


class Base {
public:
    explicit Base(int a = 10, double b = 20.5);
    virtual ~Base() = default;
    Base(const Base& other) = delete;
    Base& operator=(const Base& other) = delete;

    virtual int getM_a() const;
    virtual void setM_a(int m_a);
    virtual double getM_b() const;
    virtual void setM_b(double m_b);
private:
    int m_a;
    double m_b;
};


#endif //MY_PROJ_BASE_H
