/******************************************************************************
 * 29.05.17
 * Work Sheet 9 header file.
 * Or Nagar.
 *****************************************************************************/
#include <stdio.h>		

/*
 * The function fills the first n bytes of the memory 
 * area pointed to by s with the constant byte c.
 */
void *MemSet(void *s, int c, size_t n);

/*
 * The function copies n bytes from memory area src
 * to memory area dest.  The memory areas must not overlap.
 */
void *MemCpy(void *dest, const void *src, size_t n);


/*
 * The function converts a number represented by 
 * an integer to a string.
 */
char *Itoa(int src);

/*
 * The function converts a number represented by 
 * a string to an integer.
 */
int Atoi(char *src);

/*
 * The function converts a number represented by 
 * a string to any base number
 */
int AtoAny(char *src, int base);

