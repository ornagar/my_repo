/******************************************************************************
 * 29.05.17
 * Work Sheet 9 function definitions
 * Or Nagar.
 *****************************************************************************/
#include <stdio.h>			/* printf()		*/
#include <stdlib.h>			/* malloc()		*/
#include <string.h>			/* strcpy()		*/
#include <assert.h>			/* assert()		*/

#include "utils.h"			/*DEBUG()		*/
#include "ws9.h"


/*
 * The function fills the first n bytes of the memory 
 * area pointed to by s with the constant byte c.
 */
void *MemSet(void *s, int c, size_t n)
{
	char *end_ptr = (char *) s + n;
	unsigned long word = 0;
	int i = 0;
	
	assert(s);
										
	while ((0 != ((size_t)s & 0x07)) &&					/* write to head */
		 ((char *)s < (char *)end_ptr))
	{						
		*(char *) s = c; 
		s = (char *)s + 1;
	}
	
	while (i++ < 8)
	{
		word <<= 8;	
		word  |= c;
	}
	
	while (((size_t)s < ((size_t)end_ptr & ~0x07)) &&		/* write to body */		
		  (8 < n)) 
	{
		*(unsigned long *) s = word;
		s = (unsigned long *)s + 1;
	}
	
	while ((char *)s < (char *)end_ptr)					/* write to tail */
	{
		*(char *) s = c;
		s = (char *)s + 1;
	}
	
	return (end_ptr - n);
}

/*
 * The function copies n bytes from memory area src
 * to memory area dest.  The memory areas must not overlap.
 */
void *MemCpy(void *dest, const void *src, size_t n)
{
	char *end_ptr = (char *) dest + n;
	
	assert(dest);
	assert(src);
									
	while ((0 != ((size_t)dest & 0x07)) &&					/* write to head */
		 ((char *)dest < (char *)end_ptr))
	{						
		*(char *) dest = *(char *) src; 
		dest = (char *)dest + 1;
		src = (char *)src + 1;
	}
	
	while (((size_t)dest < ((size_t)end_ptr & ~0x07)) &&	/* write to body */		
		  (8 < n))
	{
		*(unsigned long *) dest = *(unsigned long *) src;
		dest = (unsigned long *)dest + 1;
		src = (unsigned long *)src + 1;
	}
	
	while ((char *)dest < (char *)end_ptr)					/* write to tail */
	{
		*(char *) dest = *(char *) src;
		dest = (char *)dest + 1;
		src = (char *)src + 1;
	}
	
	return (end_ptr - n);
}

/*
 * The function converts a number represented by 
 * an integer to a string.
 */
char *Itoa(int src)
{
	char *dest = NULL;
	int counter = 0;
	int copy = src;
	int neg_flag = 0;
	
	do											/* count number's length	*/
	{
		copy /= 10;
		++counter;
	}
	while (0 != copy);
	
	if (NULL == (dest = malloc(counter + 2)))	/* allocate size of src		*/
	{											/* + null + '-'				*/
		DBG(perror("error in line __LINE__ while allocating memory");)
		return (NULL);
	}
	
	if (0 >= src)
	{
		*dest = '-';
		dest += counter + 1;					/* go to end of string		*/
		*dest = '\0';
		src *= -1;
		neg_flag = 1;
	}
	else
	{
		dest += counter;						/* go to end of string		*/
		*dest = '\0';
	}
	
	while (0 < counter)							/*add last int and move back*/
	{
		--dest;
		*dest = (src % 10) + '0';
		src /= 10;
		--counter;
	}
	
	if (neg_flag)
	{
		--dest;
	}
	
	return (dest);
}

/*
 * The function converts a number represented by 
 * a string to an integer.
 */
int Atoi(char *src)
{
	int dest = 0;
	int neg_flag = 0;
	
	assert(src);
	
	if ('-' == *src)
	{
		++src;
		neg_flag = 1;
	}
	
	while ('\0' != *src)
	{	
		dest *= 10;
		dest += *src - '0';
		++src;
	}
	
	if (neg_flag)
	{
		dest *= (-1);
	}
	
	return (dest);
}

/*
 * The function converts a number represented by 
 * a string to any base number
 */
int AtoAny(char *src, int base)
{
	int dest = 0;
	
	assert(src);
	
	while ('\0' != *src)
	{	
		dest *= base;

		if ('0' <= *src && '9' >= *src)
		{
			dest += *src - '0';
		}
		else if ('a' <= *src && 'f' >= *src)
		{
			dest += *src - 87;
		}
		else
		{
			dest += *src - 55;
		}
		++src;
	}
	
	return (dest);
}


