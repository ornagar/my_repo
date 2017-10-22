#include <iostream>
using namespace std;

template <typename T>
void foo(T t)
{
	cout << t << " Generic foo" << endl;
}

template <>
void foo<int>(int t)
{
	cout << t << " Specialized foo (for int param)"
		<< endl;
}

int main(void)
{
	foo<int>(5);
	foo(5);
	return 0;
}
