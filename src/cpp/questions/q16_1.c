#include <iostream>
#include <stdio.h>
//#include "q16.h"

template <typename T>
T Max(T t1, T t2)
{
	return t1 > t2 ? t1 : t2;
}

int main(void)
{
	std::cout << "hello" << Max<int>(3, 5) << std::endl;
	fprintf(stderr, "wlskdgfj");
	return 0;
}
