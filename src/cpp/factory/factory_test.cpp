#include <string>
#include <memory>
#include <iostream>

#include "factory.hpp"

using namespace ilrd;

class Base {
public:
    Base(int a = 4): m_a(a) { }
    virtual ~Base() = default;
    virtual void print() { std::cout << "This is Base: " << m_a << std::endl; }
private:
    int m_a;
};

class Derived: public Base {
public:
    Derived(int a = 4): Base(), m_b(a) { }
    virtual ~Derived() = default;
    virtual void print() { std::cout << "This is Derived: " << m_b << std::endl; }
private:
    int m_b;
};

std::shared_ptr<Base> function_base(int a)
{
    std::shared_ptr<Base> ptr(new Base());
    return ptr;
}

std::shared_ptr<Base> function_derived(int a)
{
    std::shared_ptr<Base> ptr(new Derived(a));
    return ptr;
}

int main()
{
    Factory<std::string, Base> factory;
    std::string key = "a";
    factory.add(std::string(key), function_base);
    std::shared_ptr<Base> b = factory.create(key);
    b->print();
    key = "b";
    factory.add(std::string(key), function_derived);
    std::shared_ptr<Base> d = factory.create(key, 48);
    d->print();
    /*
    try {
        d = factory.create("x", 48);
    } catch(Factory<std::string, Base>::BadKey& b) {
        std::cout << "caught: " << b.what() << std::endl;
        return 1;
    }
    */
    Base *c = new Base();
    typedef void (Base::*func)();
    func f =  &Base::print;
    (c->*f)();
    
}
