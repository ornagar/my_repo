/*******************************************************************************
 *  Or Nagar.
 *  Circular Buffer.  
 *  Functions tests.
 *  12/06/17
 ******************************************************************************/
#include <stdio.h>			/* printf()			*/
#include <stdlib.h>			/* EXIT_SUCCESS		*/
#include <sys/types.h>		/* ssize_t			*/

#include "circbuf.h"			

#ifdef _DEBUG
/*
 * Prints the current data in the circular buffer.
 */
void CircBufPrint(const circbuf_t *cb);
#endif		/* _DEBUG				*/

int Tester(long actual_value, long expected_value, char *str, int line);
int TestCircBuf(void);

int main(void)
{
	int err_sum = 0;
	
	err_sum += TestCircBuf();
	
	if (0 == err_sum)
	{
		puts("TEST SUCCESS!!");
	}
	else
	{
		printf("found %d bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

/* 1 : create test				
 * 2 : FreeSpace test			
 * 3 : Capacity test				
 * 4 : isempty test				
 * 5 : write test				
 * 6 : read test				
 * 7 : FreeSpace test			
 * 8 : write test				
 * 9 : read test
 * 10: FreeSpace test
 * 11: write test
 * 12: FreeSpace test
 * 13: FreeSpace test
 * 14: capacity test
 * 15: isempty test
 * 16: write test
 * 17: isempty test
 * 18: read test
 * 19: FreeSpace test
 * 20: write test
 * 21: read test
 * 22: FreeSpace test
 * 23: write test
 * 24: read test
 * 25: FreeSpace test
 * 26: isempty test
 * 27: capacity test
 */
int TestCircBuf(void)		
{
	int count_errs = 0;
	char *src = "012345678901234567890123456789012345678901234567890123456789";
	char dest[100] = {0};

	/* 1: create test					*/
	circbuf_t *cb = CircBufCreate(50);
	if (NULL == cb)
	{
		printf("function: CircBufCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 2: FreeSpace test				*/
	count_errs += Tester((long)CircBufFreeSpace(cb), (long) 50, "Capacity: ", __LINE__);

	/* 3: Capacity test					*/
	count_errs += Tester((long)CircBufCapacity(cb), (long) 50, "Capacity: ", __LINE__);
	
	/* 4: isempty test					*/
	count_errs += Tester((long)CircBufIsEmpty(cb), (long) 1, "Size: ", __LINE__);
	
	/* 5: write test					*/
	count_errs += Tester((long)CircBufWrite(cb, src, 10), (long) 10, "Size: ", __LINE__);
	
	/* 6: read test						*/
	count_errs += Tester((long)CircBufRead(cb, dest, 10), (long) 10, "Size: ", __LINE__);
	
	/* 7: FreeSpace test				*/
	count_errs += Tester((long)CircBufFreeSpace(cb), (long) 50, "Capacity: ", __LINE__);
	
	/* 8: write test					*/
	count_errs += Tester((long)CircBufWrite(cb, src, 0), (long) 0, "Size: ", __LINE__);
	
	/* 9: read test						*/
	count_errs += Tester((long)CircBufRead(cb, dest, 100), (long) 0, "Size: ", __LINE__);
	
	/* 10: FreeSpace test				*/
	count_errs += Tester((long)CircBufFreeSpace(cb), (long) 50, "Capacity: ", __LINE__);
	
	/* 11: write test					*/
	count_errs += Tester((long)CircBufWrite(cb, src, 100), (long) 50, "Size: ", __LINE__);
	
	/* 12: FreeSpace test				*/
	count_errs += Tester((long)CircBufRead(cb, dest, 100), (long) 50, "Size: ", __LINE__);
	
	/* 13: FreeSpace test				*/
	count_errs += Tester((long)CircBufFreeSpace(cb), (long) 50, "Capacity: ", __LINE__);
	
	/* 14: capacity test				*/
	count_errs += Tester((long)CircBufCapacity(cb), (long) 50, "Capacity: ", __LINE__);
	
	/* 15: isempty test					*/
	count_errs += Tester((long)CircBufIsEmpty(cb), (long) 1, "Size: ", __LINE__);
	
	/* 16: write test					*/
	count_errs += Tester((long)CircBufWrite(cb, src, 60), (long) 50, "Size: ", __LINE__);
	
	/* 17: isempty test					*/
	count_errs += Tester((long)CircBufIsEmpty(cb), (long) 0, "Size: ", __LINE__);
	
	/* 18: read test					*/
	count_errs += Tester((long)CircBufRead(cb, dest, 10), (long) 10, "Size: ", __LINE__);
	
	/* 19: FreeSpace test				*/
	count_errs += Tester((long)CircBufFreeSpace(cb), (long) 10, "Capacity: ", __LINE__);
	
	/* 20: write test					*/
	count_errs += Tester((long)CircBufWrite(cb, src, 2), (long) 2, "Size: ", __LINE__);
	
	/* 21: read test					*/
	count_errs += Tester((long)CircBufRead(cb, dest, 100), (long) 42, "Size: ", __LINE__);
	
	/* 22: FreeSpace test				*/
	count_errs += Tester((long)CircBufFreeSpace(cb), (long) 50, "Capacity: ", __LINE__);
	
	/* 23: write test					*/
	count_errs += Tester((long)CircBufWrite(cb, src, 100), (long) 50, "Size: ", __LINE__);
	
	
	#ifdef _DEBUG

	CircBufPrint(cb);
	
	#endif
	
	/* 24: read test					*/
	count_errs += Tester((long)CircBufRead(cb, dest, 100), (long) 50, "Size: ", __LINE__);
	
	/* 25: FreeSpace test				*/
	count_errs += Tester((long)CircBufFreeSpace(cb), (long) 50, "Capacity: ", __LINE__);
	
	/* 26: isempty test					*/
	count_errs += Tester((long)CircBufIsEmpty(cb), (long) 1, "Size: ", __LINE__);
	
	/* 27: capacity test				*/
	count_errs += Tester((long)CircBufCapacity(cb), (long) 50, "Capacity: ", __LINE__);
	
	CircBufDestroy(cb);
	
	return (count_errs);
}

int Tester(long actual_value, long expected_value, char *str, int line)
{	
	if (actual_value != expected_value)
	{
		printf("function: %s\t in line: %d\t", str, line);
		printf("- status: fail... expected value was %ld\
				 and actual value is %ld\n",
				expected_value, actual_value);
				
		return (1);
	}
	
	return (0);
}
