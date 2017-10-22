#include <stdio.h>
#include <time.h>

int array[100000] = {0};

int main(int argc, char **argv)
{
    int a[100000];

	#pragma omp parallel for
    for (int i = 0; i < 100000; i++) 
    {
        a[i] = 2 * i;
    }


printf("%d\n", a[0]);
    return 0;
}

