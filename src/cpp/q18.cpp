#include <iostream>
using namespace std;

int main(void)
{
	long i = 8;
	long &ip = i;
	ip = 9;
	cout << &ip << "  " << &i << endl;
	
	return 0;
}
