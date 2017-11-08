#include <stdio.h>

typedef struct test
{
	int x;
	double y;
}test_t;

int foo(test_t a, test_t b)
{
	return a == b;
}
int main(void)
{
	struct test t;
	struct test x;
	t.x = 14; t.y = 3.14;
	
	printf("%d\n", foo());
	
	return 0;
}
