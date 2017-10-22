#include <stdio.h>

enum E {AA, BB, CC, DD};

int main(void)
{
	enum E e;
	enum E s;
	enum E w;
	enum E a;
	
	int i = e;
	
	printf("%d %d %d %d %d\n", e, s, w, a, i);
	return (0);
}

