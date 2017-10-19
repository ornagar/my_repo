#include <stdio.h>

int main(void)
{
	const int i = 3;
	int  *ip = (int *)&i;
	
	*ip = 5;
	
	printf("%d  %d\n", i, *ip);
	
	return (0);
}
