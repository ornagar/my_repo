#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"

void SevenBoom(int from, int limit);
void RmSpaces(char *str);
void Tester(double return_value, double wanted_value);
int IsPalindrome(const char *str);
void PointerSwap(int **ptr1, int **ptr2);
char *BigSum(char *const x, char *const y);

int main(void)
{
	
	int x = 5;
	int y = 10;
	int *ptr_a = &x;
	int *ptr_b = &y;
	char string[60] = "hello .  .          	  .    .";
	
	/*BigSum test*/
	char *a = "485";
	char *b = "2";
	char *total1 = BigSum(a, b);
	printf("%s\n", total1);
	printf("sdfsdh %d\n",total1[0]);
	free(total1);
	
	/* testing variables for ws2_exercises */
	
	/*SevenBoom test*/
	SevenBoom(10, 20);
	
	/*IsPalindrome test*/
	printf("%d\n", IsPalindrome("varrav"));
	printf("%d\n", IsPalindrome("varrev"));
	
	/*PointerSwap test*/
	Tester((double)(*ptr_a), (double)(x));
	PointerSwap(&ptr_a, &ptr_b);
	Tester((double)(*ptr_a), (double)(y));
	
	/*RmSpaces test*/
	printf("%s\n", string);
	RmSpaces(string);
	printf("%s\n", string);
	
	return (EXIT_SUCCESS); 
}

/*
 *aid function to SevenBoom.
 * checks if the number contains 7.
 */
 
#define BOOM_NUM	(7)


int IsSeven(int num)
{  
	while (0 < num)			
	{
		if (BOOM_NUM == num % 10)			/* Is least significant digit equal to 7 */
		{
			return (1);
		}	
		
		num /= 10;
   	}
   	
   	return (0);
}

/*
 * Seven Boom game simulating function.
 */
void SevenBoom(int from, int limit)
{
	int i = 0;

    for (i = from; i <= limit; ++i)
    {
		if ((0 == (i % BOOM_NUM)) || (IsSeven(i)))
		{
			puts("BOOM!");
		}
		else
		{
			printf("%d\n", i);
		}
	}
}

/*
 * IsPalindrome checks if a string is palidrom.
 * RETURN VALUE:
 * 1 - if true.
 * 0 - if false. 
 */
int IsPalindrome(const char *str)
{
	/* Pointer starts on last char, and decremented on each iteration */
	const char *right = NULL;			
	
	assert(str);
	
	/* We like re-use of code */
	right = str + strlen(str) - 1;
	
	while (str < right)
	{
		if ( *str != *right)
		{
			return (0);
		}
		
		++str;
		--right;
	}
	
	return (1);
}

/*
 * PointerSwap swaps the addresses each pointer 
 * points to between two pointers. 
 */
void PointerSwap(int **ptr1, int **ptr2)
{
	int *temp = *ptr1;
	
	*ptr1 = *ptr2;
	*ptr2 = temp;
	
	return;
}

/*
 * RmSpaces takes a string and removes spaces from the begining 
 * and the end of the string, and removes spaces in the middle 
 * of the string if there is more than one.
 */
void RmSpaces(char *str)
{
	char *read  = str;
	char *write = str;
	
	assert(str);
	
	/* Skip leading blanks */
	while (isspace(*read))
	{
		++read;
	}
	
	while ('\0' != *read)
	{
		*write = *read;
		++read;
		
		/* If two consecutive blanks */
		if ((isspace(*read) && isspace(*write)))
		{
			while (isspace(*read))	/* Skip blanks from the second blank */
			{
				++read;
			}
		}
		
		++write;
	}
	
	/* If last char is blank, delete it */
	if ((write > str) && isspace(*(write-1)))
	{
		--write;
	}

	*write = '\0';
	
	return;
}

/*
 * BigSum returns a pointer to char array containing
 * the result of adition of two very big numbers.
 */
char *BigSum(char *const x, char *const y)
{
	int carry = 0;
	
	char *end_x = NULL; 		/*x last char before null         */
	char *end_y = NULL; 		/*y last char before null         */

	char *sum = NULL;
	char *end_sum = NULL;
	size_t sum_size = 0;
	
	int two_digits_sum = 0;
	
	assert(x);
	assert(y);
	
	end_x = x + (strlen(x)-1);	/*x last char before null         */
	end_y = y + (strlen(y)-1);	/*y last char before null         */
	sum_size = (MAX(strlen(x),strlen(y)) + 2);
	
	if (NULL == (sum = (char *)malloc(sum_size)))
	{
		fprintf(stderr, "Error in memory allocation");
		return ((char*)EXIT_FAILURE);
	}
	
	end_sum = sum + (sum_size-1);
	*end_sum = '\0';
	
	--end_sum;

#define ASCII_TO_NUM(a)	((a)-'0')	
#define NUM_TO_ASCII(n)	((n)+'0')

	while (end_x >= x && end_y >= y)		/*while the short number exists   */
	{
		two_digits_sum = carry + (ASCII_TO_NUM(*end_x) + ASCII_TO_NUM(*end_y));
		carry = (two_digits_sum) / 10;
		*end_sum = NUM_TO_ASCII(two_digits_sum % 10);  
		
		--end_x;
		--end_y;
		--end_sum;
	}
	
	while (end_x >= x)						/* if x is the long number        */
	{
		two_digits_sum = carry + ASCII_TO_NUM(*end_x);
		carry = (two_digits_sum) / 10;
		*end_sum = NUM_TO_ASCII(two_digits_sum % 10);  
		
		--end_x;
		--end_sum;
	}
	
	while (end_y >= y)						/* if y is the long number        */
	{
		two_digits_sum = carry + ASCII_TO_NUM(*end_y);
		carry = (two_digits_sum) / 10;
		*end_sum = NUM_TO_ASCII(two_digits_sum % 10);  

		--end_y;
		--end_sum;
	}
	
	*end_sum = NUM_TO_ASCII(carry);
	
	if (('0' == *sum))				   	 /*a condition to fix starting -0-    */ 
	{
	
		end_x = sum;
		++end_sum;
		
		while ('\0' != *end_sum)
		{
			*end_x = *end_sum;
			++end_sum;
			++end_x;
		}
		
		*end_x = '\0';	
	}

	return (sum);
}



void Tester(double return_value, double wanted_value)
{
	float epsilon = 0.0000001;
	static int counter = 0;
	if (abs(return_value - wanted_value) < epsilon)
	{
		printf("%d: ", counter);
		puts("Success!!");
		++counter;
	}
	else
	{
		printf("%d: ", counter);
		printf("fail... wanted value was %f and return value is %f\n",
											wanted_value, return_value);
		++counter;
	}
}


















