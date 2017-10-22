/******************************************************************************
 * 29.05.17
 * Work Sheet 9 assignments.
 * Or Nagar.
 *****************************************************************************/
#include <stdio.h>			/* printf()		*/
#include <stdlib.h>			/* EXIT_SUCCESS	*/

#include "utils.h"			/* MAX()		*/
/**********************function's declarations*********************************/
void IsLittleEndian(void);
void PtStr(char *str1, char *str2, char *str3, int size1, int size2, int size3);
/******************************************************************************/
#define ENDIAN (*(char *)&argc ? (puts("Is Little Endian")) : puts("Is Big Endian"))

int main(int argc, char **argv)
{
	IsLittleEndian();
	PtStr("hellqwo", "vqwanel", "ebnmv", 7, 7, 5);

	printf("%d\n", atoi("-15"));
	ENDIAN;
	return (EXIT_SUCCESS);
}

void IsLittleEndian(void)
{
	unsigned int x = 0x01;
	
	if(*(unsigned char *) &x)
	{
		puts("Is Little Endian");
	}
	else
	{
		puts("Is Big Endian");
	}
	
	return;
}

void PtStr(char *str1, char *str2, char *str3, int size1, int size2, int size3)
{
	char dest[256] = {0};
	int i = 0;
	char *str_end = NULL;
	
	str_end = str1 + size1;
	while (str1 < str_end)
	{
		dest[(int)*str1] = 1;
		++str1;
	}
	
	str_end = str2 + size2;
	while (str2 < str_end)
	{
		if (1 == dest[(int)*str2])
		{
			dest[(int)*str2] = 2;
		}
		++str2;
	}
	
	str_end = str3 + size3;
	while (str3 < str_end)
	{
		if (dest[(int)*str3] == 2)
		{
			dest[(int)*str3] = 0;
		}
		++str3;
	}
	
	for (i = 0;256 > i; ++i)
	{
		if (2 == dest[i])
		{
			printf("%c\n", i);
		}
	}
	
	return;
}
