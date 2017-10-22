#include <iostream>
using namespace std;

class X
{
public:
	X();
	bool operator==(const X& o_)const{ return m_a==o_.m_a; }
	//java style inline - not allowed in our coding standard
private:
	friend ostream& operator<<(ostream& os_, const X& x_);
	friend int operator+(const X& x1_, const X& x2_);
	int m_a;
};

X::X(): m_a(4){}

int operator+(const X& x1_, const X& x2_)
{
	return x1_.m_a + x2_.m_a;
}

int main()
{
	X x1;
	X x2;
	
	std::cout<<"x1 + x2:"<<x1+x2<<" x1==x2:"<<(x1==x2) <<
	"   x1:"<<x1<<"  x2:"<<x2<<std::endl;
	
	return 0;
}

ostream& operator<<(ostream& os_, const X& x_)
{
	return os_<<x_.m_a;
}

