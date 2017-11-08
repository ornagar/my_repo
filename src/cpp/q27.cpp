#include <iostream>

class X
{
public:
    X(int n): m_num(n) { std::cout <<"inside constructor"<<n<<std::endl; }
    ~X() {std::cout<<"inside destructor"<<m_num<<std::endl; }
    operator int() const { return m_num; }
    int GetNum() const { return m_num; }
    
private:
    int m_num;
};

void Foo(X& x)
{
    std::cout << x.GetNum()<<std::endl;
    std::cout << x << std::endl;
}

void Bar(int num)
{
    std::cout<<num<<std::endl;
}

int main()
{
    Foo(2);
    X x_inst(3);
    Bar(x_inst);
    
    return 0;
}