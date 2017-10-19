#include <stdio.h>

void PrintMostCommonChar(unsigned char c)
{
	static int arr[256] = {0};
	size_t frequency_counter = 0;
	int i = 0;
	
	if (0 == c)
	{
		for (i = 0; i < 256; ++i)
		{
			if(arr[i] > frequency_counter)
			{
				frequency_counter = arr[i];
			}
		}
		
		printf("%lu\n", frequency_counter);
	}
	else
	{
		++arr[c];
	}
}

int main(void)
{
	PrintMostCommonChar(171);
	PrintMostCommonChar(171);
	PrintMostCommonChar(171);
	PrintMostCommonChar(171);
	PrintMostCommonChar(171);
	PrintMostCommonChar(171);
	PrintMostCommonChar('d');
	PrintMostCommonChar('d');
	PrintMostCommonChar('d');
	PrintMostCommonChar(0);
	
	return(0);
}
