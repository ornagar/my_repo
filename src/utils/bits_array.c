/******************************************************************************
 * Or Nagar	.			                                                      *
 * 04/06                                                                      *	
 * Bits array library functions definitions.                                  *
 ******************************************************************************/
#include <stdio.h>				/* printf()			 */
#include <assert.h>				/* assert()			 */

#include "utils.h"				/* DBG()			 */
#include "bits_array.h"		

#define WORD_BITS (64)
#define BYTE_MASK_ON (0XFF)

unsigned long BitArrSetOn(unsigned long arr, unsigned int index)
{
	assert(index < WORD_BITS);
	
	return (arr | (0x01UL << index));
}

unsigned long BitArrSetOff(unsigned long arr, unsigned int index)
{
	assert(index < WORD_BITS);
	assert(index);
    
	return (arr & (~(0x01 << index)));
}

unsigned long BitArrSet(unsigned long arr, unsigned int index, unsigned int value)
{
	assert(index < WORD_BITS);
	
	value = !!value;
	
	return ((arr & (~(0x01ul << index))) | ((unsigned long)value << index));
}

int BitArrIsOn(unsigned long arr, unsigned int index)
{
	assert(index < WORD_BITS);
	
	return (0x01UL & (arr >> index));
}

int BitArrIsOff(unsigned long arr, unsigned int index)
{
	assert(index < WORD_BITS);
	
	return (!(0x01UL & (arr >> index)));
}

unsigned long BitArrFlip(unsigned long arr, unsigned int index)
{
	assert(index < WORD_BITS);
	
	return (arr ^ (0x01UL << index));
}

unsigned long BitArrRotateRight(unsigned long arr, size_t n)
{
	assert(n < WORD_BITS);
	
	return ((arr >> n) | (arr << (WORD_BITS - n)));
}

unsigned long BitArrRotateLeft(unsigned long arr, size_t n)
{
	assert(n < WORD_BITS);
	
	return ((arr << n) | (arr >> (WORD_BITS - n)));
}

unsigned long BitArrMirror(unsigned long arr)
{
  arr =  (arr << 32)                       |  (arr                       >> 32);
  arr = ((arr << 16) & 0xffff0000ffff0000) | ((arr & 0xffff0000ffff0000) >> 16);
  arr = ((arr <<  8) & 0xff00ff00ff00ff00) | ((arr & 0xff00ff00ff00ff00) >>  8);
  arr = ((arr <<  4) & 0xf0f0f0f0f0f0f0f0) | ((arr & 0xf0f0f0f0f0f0f0f0) >>  4);
  arr = ((arr <<  2) & 0xcccccccccccccccc) | ((arr & 0xcccccccccccccccc) >>  2);
	
  return (((arr <<  1) & 0xaaaaaaaaaaaaaaaa) |
  		  ((arr & 0xaaaaaaaaaaaaaaaa) >>  1));
}

/*
 * counts set bits using hamming-weight
 */
int BitArrCountOn(unsigned long arr)
{
	arr = (arr & 0x5555555555555555) + ((arr>>1) & 0x5555555555555555);
	arr = (arr & 0x3333333333333333) + ((arr>>2) & 0x3333333333333333);
	arr = (arr & 0x0f0f0f0f0f0f0f0f) + ((arr>>4) & 0x0f0f0f0f0f0f0f0f);
	arr = (arr & 0x00ff00ff00ff00ff) + ((arr>>8) & 0x00ff00ff00ff00ff);
	arr = (arr & 0x0000ffff0000ffff) + ((arr>>16)& 0x0000ffff0000ffff);

	return ((arr & 0x00000000ffffffff) + ((arr>>32)& 0x00000000ffffffff));
}

int BitArrCountOff(unsigned long arr)
{	
	arr = ~arr;
	
	arr = (arr & 0x5555555555555555) + ((arr>>1) & 0x5555555555555555);
	arr = (arr & 0x3333333333333333) + ((arr>>2) & 0x3333333333333333);
	arr = (arr & 0x0f0f0f0f0f0f0f0f) + ((arr>>4) & 0x0f0f0f0f0f0f0f0f);
	arr = (arr & 0x00ff00ff00ff00ff) + ((arr>>8) & 0x00ff00ff00ff00ff);
	arr = (arr & 0x0000ffff0000ffff) + ((arr>>16)& 0x0000ffff0000ffff);

	return ((arr & 0x00000000ffffffff) + ((arr>>32)& 0x00000000ffffffff));
}

#ifdef _DEBUG
void BitArrPrint(unsigned long arr)
{
	int count_down = WORD_BITS;
	unsigned long mask = 0x8000000000000000;
	
	while (count_down--)
	{
		printf("%3d", count_down);
	}
	printf("\n");
	count_down = WORD_BITS;

	while (mask)
	{
		printf((mask & arr) ? "  1" : "  0");
		mask >>= 1;
	}
	printf("\n");
}
#endif
