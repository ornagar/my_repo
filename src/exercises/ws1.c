/******************************************************************************
 * 11.05.17
 * Work Sheet 1
 * Or Nagar
 *****************************************************************************/
#include <stdio.h>		
#include <stdlib.h>

void Hello(void);			  /*prints "hello world!"*/
double TenPower(int);		  /*raises 10^(int)*/
int FlipInt(int);	          /*flips the number given by user*/
void Swap(int*, int*);	      /*swaps values of two variables*/
void Tester(double return_value, double wanted_value);

int main(void)
{
	
	
	/*Test 1*/
	Hello();
	
	/*Test 2*/
	Tester(TenPower(2), (double)(100));
	Tester(TenPower(0), (double)(1));
	Tester(TenPower(-2), (double)(0.1));
	
	/*Test 3*/
	Tester((double)FlipInt(0), (double)(0));
	Tester((double)FlipInt(1), (double)(1));
	Tester((double)FlipInt(-1), (double)(-1));
	Tester((double)FlipInt(13), (double)(31));
	Tester((double)FlipInt(-15), (double)(-51));
	Tester((double)FlipInt(105), (double)(501));
	
	return (EXIT_SUCCESS);
}

/*
 * Prints "hello world!"
 */
void Hello(void)
{
	/*char str[] = {0x22,0x48,0x65,0x6C,0x6C,0x6F,	*/	/*takes characters in */ 
	/*0x20,0x57,0x6F,0x72,0x6C,0x64,0x21,0x22,'\0'};*/	  	/*Hexa ascii          */
	printf("hello world\n");	
	
	return;
}

/*
 * Raises 10^(int)
 */
double TenPower(int exp)
{
	double result = 1;
	double const mult = 10.0;
	int i = 0;
	int is_neg = 0;
	if (0 > exp)
	{
		is_neg = 1;
		exp *= -1;
	}

	for (i = 0; i < exp; ++i)
	{
		result *= mult;
	}
	
	if (is_neg)
	{
		result = 1 / result;
	}	
		
	return (result);
}

/*
 * Flips the number given by user
 */
int FlipInt(int src)
{
	int reversed = 0;
	int is_positive = src;
	src = (0 <= src ? ((-1) * src) : src);
		
	while (src)		/*while src is greater then 0*/
	{
		reversed *= 10;
		reversed += (src % 10);	
		src /= 10;
	}		
	reversed = (0 <= is_positive ?
	 ((-1) * reversed) : reversed);	   /*if src was negative, negate reversed*/
	
	return (reversed);
}

/*
 *Swaps values of two variables
 */
void Swap(int *const a, int *const b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
	
	return;
}

/*
 *the tester checks if the functions return value is
 *equal to the expectation.
 */
void Tester(double return_value, double wanted_value)
{
	float epsilon = 0.0000001;
	
	if (abs(return_value - wanted_value) < epsilon)
	{
		puts("Success!!");
	}
	else
	{
		printf("fail... wanted value was %f and return value is %f\n",
											wanted_value, return_value);
	}
}
