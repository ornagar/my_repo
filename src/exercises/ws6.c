/******************************************************************************
 ws6.c BitWise Tricks
 
 23.05.17
 
 Or Nagar.
*******************************************************************************/
#include <stdio.h> 		 /* printf()     */
#include <stdlib.h>		 /* Exit_success */

#define BITS_IN_BYTE 8

double pow2(unsigned int x, int y);
int IsPowTwo(unsigned int x);
int IsPowTwoNoLoop(unsigned int x);
int PlusOne(unsigned int x);
void ThreeBits(unsigned int *arr, int size);
unsigned char ByteMirror(unsigned char src);
unsigned char ByteMirrorNoLoops(unsigned char src);
void BitCheck(unsigned char src);
int TwoAndSix(unsigned char src);
int TwoOrSix(unsigned char src);
unsigned char ThreeFiveSwap(unsigned char src);
unsigned int ClosestTo_16(unsigned int src);
void Swap(unsigned long int *a, unsigned long int *b);
int CountOn(int src);
int CountOnNoLoops(int n);
void FloatToBits();
unsigned int Josephus(unsigned int soldiers);

int main(void)
{
	printf("%d\n", Josephus(1000000000));
	return (EXIT_SUCCESS);
}


/*
 *	The function returns (x*(2^y)).
 */
double pow2(unsigned int x, int y)
{
	if (0 < y)
	{ 
		x <<= y;
	}
	else
	{
		x >>= abs(y);
	}
	return ((double) x);
}

/*
 * The function checks if x is power of 2.
 */
int IsPowTwo(unsigned int x)
{
	int mask = 1;
	
	while (0 == (mask & x))     	/* moves the mask until it matches */
	{								/* the first set bit in x          */
		 mask <<= 1;
	}
	
	if (mask == x)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/*
 * The function checks if x is power of 2 without a loop.
 */
int IsPowTwoNoLoop(unsigned int x)
{
	return (0 != x && (!(x & (x-1))));	
}

/*
 * The function adds one to x.
 */
int PlusOne(unsigned int x)
{
	int i = 0;
	int mask = 1;
	
	if (x & 1)									/* if x is even 		*/
	{
		while (1 == ((x & mask) >> i)) 			/* while bit is 1		*/ 
		{
			x ^= mask;
			mask <<= 1;
			++i;
		}
		x ^= mask;   							/* set 1 in the first 0 */
	}
	else
	{
		x |= mask;
	}
	
	return (x);
}

/*
 * The function prints an integer from an array
 * only if it has exactly 3 bits set.
 */
void ThreeBits(unsigned int *arr, int size)
{
	unsigned int copy = *arr;
	int counter = 0;
	int mask = 1;
	
	while (0 < size)
	{
		while (0 != copy)
		{
			counter += (mask & copy);	  /* if (mask & copy) == 1 counter ++ */
			copy >>= 1;
		}
	
		if (3 == counter)
		{
			printf("%x\n", *arr);
		}
		
		++arr;
		copy = *arr;
		--size;
		counter = 0;
	}
	
	return;
}

/*
 * The function returns a mirror of src's bits.
 */
unsigned char ByteMirror(unsigned char src)
{
	unsigned char dest = 0;
	unsigned char mask = 1;
	int bits = BITS_IN_BYTE;
	
	while (1 < bits)
	{
		dest |= (mask & src);
		dest <<= 1;
		src >>= 1;
		--bits;
	}
	
	dest |= (mask & src);
		
	return dest;
}

/*
 * The function returns a mirror of src's bits.
 */
unsigned char ByteMirrorNoLoops(unsigned char src)
{
	src = (src << 4) | (src >> 4);
	src = ((src << 2) & 0xcc) | ((src >> 2) & 0x33);
	src = ((src << 1) & 0xaa) | ((src >> 1) & 0x55);
		
	return src;
}

/*
 * The function checks if second's and sixt's bits
 * of an unsigned char are set.
 */
int TwoAndSix(unsigned char src)
{
	return (src & 0x22);
}

/*
 * The function checks if second's and/or sixt's bits
 * of an unsigned char are set.
 */
int TwoOrSix(unsigned char src)
{
	return ((src & 0x20) || (src && 0x02));
}

/*
 * The function swaps a byte's 3rd and 5th bits.
 */
unsigned char ThreeFiveSwap(unsigned char src)
{
	unsigned char mask_for_five = 0x04;
	unsigned char mask_for_three = 0x10;
	unsigned char three_five_turnoff = 0xeb;
	
	mask_for_five = (mask_for_five & src) << 2;
	mask_for_three = (mask_for_three & src) >> 2;
	
	src = (three_five_turnoff & src) | (mask_for_three | mask_for_five);
	
	return (src);
}

/*
 * The function returns the closest number to src
 * that is divided by 16.
 */
unsigned int ClosestTo_16(unsigned int src)
{
	return (src & 0xfffffff0);
}

/*
 * The function swaps two integers without the use
 * of a third var. 
 * the integers must be (0 <= a, b <= (2^32)-1).
 */
void Swap(unsigned long int *a, unsigned long int *b)
{
	*a <<= 32;
	*a |= *b;
	*b = 0xffffffff00000000;
	*b &= (*a);
	*b >>= 32;
	*a &= 0x00000000ffffffff;
	
	return;
}

/*
 * The function counts the number of set bits in an int.
 */
int CountOn(int src)
{
	int counter = 0;
	int mask = 0x01;
	int flag = 0;
	
	while (0 != (unsigned int)src)
	{
		flag = (mask & (unsigned int)src);
		src = (unsigned int)src >> 1;
		counter += flag;
	}
	
	return (counter);
}

/*
 * The function counts the number of set bits in an int.
 */
int CountOnNoLoops(int n)
{
	n = (n & 0x55) + ((n>>1) & 0x55);
	n = (n & 0x33) + ((n>>2) & 0x33);
	n = (n & 0x0f) + ((n>>4) & 0x0f);
	
	return (n);
}

/*
 * The function asks the user to input a float number
 * then it prints the binary representation.
 */
void FloatToBits()
{
	float f = 0.0;
	unsigned int *fake_ptr = NULL;
	printf("Enter float number: ");
	scanf("%f", &f);
	fake_ptr = (unsigned int*)&f;
	printf("0x%x\n", *fake_ptr);
	
	return;
}

/*
 * The function solves the Josephus problem in
 * bit manipulation way.
 */
unsigned int Josephus(unsigned int soldiers)
{
	unsigned int mask = soldiers;
	int count = 0;
	while (1 < mask)
	{
		mask >>= 1;
		++count;
	}
	
	while (0 < count)
	{
		mask <<= 1;
		--count;
	}
	soldiers = ((soldiers ^ mask) << 1) | 1;
	
	return (soldiers);
}


