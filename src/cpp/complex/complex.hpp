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
 *  The API gives the user the option to work with complex numbers in a very
 *  straight forward way. You can make all basic arithmetic operations (+,-,/,*)
 *  Relational operations (!=, ==) io operations << , >> extract absolute value
 *  and more.
 *
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#ifndef COMPLEX_HPP_
#define COMPLEX_HPP_

#include <iosfwd>       //ostream.
#include <cmath>        //pow()

namespace ilrd {
    
class Complex;
    
const Complex operator+(const Complex& lhs, const Complex& rhs);
const Complex operator-(const Complex& lhs, const Complex& rhs);
const Complex operator*(const Complex& lhs, const Complex& rhs);
const Complex operator/(const Complex& lhs, const Complex& rhs);

std::ostream& operator<<(std::ostream& os, const Complex& num);
std::istream& operator>>(std::istream& is, Complex& num);

// relational operators
bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);

const Complex Sin(const Complex& comp);
const Complex Cos(const Complex& comp);

class Complex {
public:
    inline Complex(double real = 0, double imag = 0); //non explicit
    //~Complex() = default;
    //Complex(const Complex& other) = default;
    //Complex& operator=(const Complex& other) = default;

    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);
    
    double abs() const;
    Complex conjugate() const;
    
    inline double real() const; //getter
    inline double imag() const; //getter

    inline void real(double);   //setter
    inline void imag(double);   //setter


private:
    double m_real;
    double m_imag;
};

inline Complex::Complex(double real, double imag) : m_real(real), m_imag(imag){}

inline double Complex::real() const
{
    return m_real;
}

inline double Complex::imag() const
{
    return m_imag;
}

inline void Complex::real(double real)
{
    m_real = real;
}

inline void Complex::imag(double imag)
{
    m_imag = imag;
}

inline Complex& Complex::operator+=(const Complex& other)
{
    m_real += other.m_real;
    m_imag += other.m_imag;

    return *this;
}

inline Complex& Complex::operator-=(const Complex& other)
{
    m_real -= other.m_real;
    m_imag -= other.m_imag;

    return *this;
}

inline const Complex operator+(const Complex& lhs, const Complex& rhs)
{
    Complex temp(lhs);
    temp += rhs;

    return temp;
}

inline const Complex operator-(const Complex& lhs, const Complex& rhs)
{
    Complex temp(lhs);
    temp -= rhs;

    return temp;
}

inline Complex Complex::conjugate() const
{
    Complex temp(*this);

    temp.m_imag *= -1;

    return temp;
}

inline Complex& Complex::operator/=(const Complex& other)
{
    double temp_real = m_real;
    double temp_imag = m_imag;

    m_real = (((m_real * other.m_real) + (m_imag * other.m_imag)) /
           (other.m_real * other.m_real) + (other.m_imag * other.m_imag));

    m_imag = (((temp_imag * other.m_real) - (temp_real * other.m_imag)) /
           (other.m_real * other.m_real) + (other.m_imag * other.m_imag));

    return *this;
}

inline const Complex operator*(const Complex& lhs, const Complex& rhs)
{
    Complex temp(lhs);
    temp *= rhs;

    return temp;
}

inline const Complex operator/(const Complex& lhs, const Complex& rhs)
{
    Complex temp(lhs);
    temp /= rhs;

    return temp;
}

inline double Complex::abs() const
{
    return sqrt((m_real * m_real) + (m_imag * m_imag));
}

inline bool operator==(const Complex& lhs, const Complex& rhs)
{
    return (lhs.real() == rhs.real()) && (lhs.imag() == rhs.imag());
}

inline bool operator!=(const Complex& lhs, const Complex& rhs)
{
    return !(lhs == rhs);
}

inline std::ostream& operator<<(std::ostream& os, const Complex& num)
{
    if (0 == num.real()) {
        return os << num.imag() << "i";
    }
    if (0 < num.imag()) {
        return os << num.real() << " + " << num.imag() << "i";
    }
    else if (0 > num.imag()) {
        return os << num.real() << " - " << num.imag() * -1 << "i";
    }
    else { // == 0
        return os << num.real();
    }
}

inline const Complex Sin(const Complex& comp)
{
    Complex temp(sin(comp.real())*cosh(comp.imag()),
                cos(comp.real())*sinh(comp.imag()));

    return temp;
}

inline const Complex Cos(const Complex& comp)
{
    Complex temp(cos(comp.real())*cosh(comp.imag()),
                -1 * (sin(comp.real())*sinh(comp.imag())));

    return temp;
}

} //namespace ilrd
#endif //COMPLEX_HPP_
