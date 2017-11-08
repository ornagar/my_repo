#include <stdio.h>

#include "utils.h"

int FlipVal(int num)
{
	int new_num = 0;
	int flag = 0;
	
	if (0 > num)
	{
		num *= -1;
		flag = 1;
	}
	
	while (0 < num)
	{
		new_num *= 10;
		new_num += num % 10;
		num /= 10;
	}
	
	if (1 == flag)
	{
		return (new_num * (-1));
	}
	else
	{
		return (new_num);
	}
}

unsigned char ByteMirrorA(unsigned char num)
{
	unsigned char new_num = 0;
	int i = 8;
	
	while (0 != i--)
	{
		new_num <<= 1;
		new_num |= num & 0x01;
		num >>= 1;
	}
	
	return (new_num);
} 

unsigned char ByteMirrorB(unsigned char num)
{
	num = (num << 4) | (num >> 4);
	num = ((num << 2) & 0xcc) | ((num >> 2) & 0x33);
	num = ((num << 1) & 0xaa) | ((num >> 1) & 0x55);
		
	return (num);
} 

int CountOnNoLoops(int n)
{
	n = (n & 0x55) + ((n>>1) & 0x55);
	n = (n & 0x33) + ((n>>2) & 0x33);
	n = (n & 0x0f) + ((n>>4) & 0x0f);
	
	return (n);
}

char RotateLeft(char byte, int n)
{
	n %= 8;
	return (((unsigned char) byte << n) | ((unsigned char) byte >> (8-n)));
}

void SwapPointers(int **ptr_a, int **ptr_b)
{
	int *temp = *ptr_a;
	*ptr_a = *ptr_b;
	*ptr_b = temp;
	
	return;
}

size_t Strlen(char *str)
{
	size_t counter = 0;
	
	while ('\0' != *str)
	{
		++counter;
		++str;
	}
	
	return (counter);
}

int Strcmp(char *str1, char *str2)
{
	while ('\0' != *str1 || '\0' != *str2)
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		
		++str1;
		++str2;
	}
	
	return (0);
}

char *Strcpy(char *dest, char *src)
{
	char *dest_start = dest;
	
	while ('\0' != *src)
	{
		*dest = *src;
		++src;
		++dest;
	}
	
	*dest = '\0';
	
	return (dest_start);
}

char *Strncpy(char *dest, char *src, size_t n)
{
	char *runner = dest;
	char *dest_end = dest + n;
	
	while (('\0' != *src) && (runner < dest_end))
	{
		*runner = *src;
		++runner;
		++src;
	}
	
	while (runner < dest_end)
	{
		*runner = '\0';
		++runner;
	}
	
	return (dest);
}

char *Strcat(char *dest, const char *src)
{
	char *cat = dest + Strlen(dest);
	Strcpy(cat, (char*)src);
	
	return (dest);
}

long fibonacci(unsigned int n)
{
	long num1 = 0;
	long num2 = 1;
	long total = 0;
	
	while (0 < n)
	{
		total = num1 + num2;
		num1 = num2;
		num2 = total;
		--n;
	}
	
	return (total);
}

char *ItToString(int src, char *dest)
{
	char *runner = dest;
	int copy = 0;
	int count = 0;
	
	if (0 > src)
	{
		*runner = '-';
		++runner;
		src *= -1;
	}
	
	copy = src;
	
	while (0 < copy)
	{
		copy /= 10;
		++count;
	}
	
	runner += count;
	*runner = '\0';
	
	while (0 < src)
	{
		--runner;
		*runner = (src % 10) + '0';
		src /= 10;
	}
	
	if (0 == src)
	{
		*runner = '0';
		++runner;
		*runner = '\0';
	}
	
	return (dest);
}

int main(void)
{
	int a = 1;
	int b = 2;
	int *ptr_a = &a;
	int *ptr_b = &b;
	
	printf("a = %d, b = %d\n*ptr_a = %d, *ptr_b = %d\n", a, b, *ptr_a, *ptr_b);
	
	SwapPointers(&ptr_a, &ptr_b);
	
	printf("a = %d, b = %d\n*ptr_a = %d, *ptr_b = %d\n", a, b, *ptr_a, *ptr_b);
	
	printf("%d\n", FlipVal(12340));
	printf("0x%x\n", ByteMirrorA(0x1));
	printf("0x%x\n", ByteMirrorB(0x1));
	printf("%lu\n", Strlen("hello"));
	printf("%d\n", Strcmp("hello", "hedlo"));
	return (0);
}
