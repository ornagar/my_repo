#include <iostream>
#include <string>

#include "shared_ptr.hpp"

using namespace ilrd;
using namespace std;

class B
{
public:
    B(int a): m_a(a){}
private:
    int m_a;
};

class X
{
public:
    X(int a): m_a(a){}
private:
    int m_a;
};

class Y : public X
{
public:
    Y (int a, int b): X(a), m_b(b){}
private:
    int m_b;
};

class Z
{
public:
    Z(int c): m_c(c){}
private:
    int m_c;
};

int main()
{
    SharedPtr<int> sp1(new int(3));

    cout << *sp1 << endl;

    *sp1 = 5;

    cout << *sp1 << endl;

    if (sp1)
        cout << "hi" << endl;

    *sp1 = 0;

    cout << *sp1 << endl;

    SharedPtr<int> sp2;

    if (sp2)
        cout << "hi" << endl;
    else
        cout << "bi" << endl;


    SharedPtr<int> sp3(sp1);

    if (sp1 == sp3)
        cout << "eq" << endl;

    SharedPtr<string> sp4(new string("hello world"));

    cout << *sp4 << endl;

    cout << sp4->size() << endl;

    SharedPtr<string> sp5(new string("no one knows"));

    cout << *sp5 << endl;

    sp5 = sp4;

    cout << *sp5 << endl;

    SharedPtr<Y> spy(new Y(2,3));

    SharedPtr<X> spx(spy);

    //compilation error
    //SharedPtr<Z> spz(spy);






    return 0;
}

