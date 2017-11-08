#include <iostream>
using namespace std;

void Foo(const double &a)
{
	cout << &a << endl;
}

void Bar(double &b)
{
	cout << &b << endl;
}

int main(void)
{
	int a = 5;
	Foo(reinterpret_cast<double &>(a));
	Bar((double &)a);
	
	
	return 0;
}
