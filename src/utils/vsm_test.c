/*****************************************************************************
 * Or Nagar.
 * VSM library.
 * Test file.
 * 05/07/17
 ****************************************************************************/
#include <stdio.h>			/* printf()			*/
#include <stdlib.h>			/* EXIT_SUCCESS		*/

#include "utils.h"			/* PRINT_ERROR		*/
#include "vsm.h"

static int Tester(long actual_value, long expected_value, char *str, int line);
int TestVsm(void);

int main(void)
{
	size_t err_sum = 0;

	err_sum = TestVsm();

	if (0 == err_sum)
	{
		puts("\nFSM TEST SUCCESS!!\n");
	}
	else
	{
		printf("\nfound %lu bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

/* 1: Init test
 * 2: Count test
 * 3: LargestChunk test	
 * 4: Alloc test	
 * 5: Count test
 * 6: LargestChunk test
 * 7: Free test			
 * 8: Count test
 * 9: Alloc All test
 * 10: LargestChunk test	
 * 11: Free test		
 * 12: Count test	
 * 13: LargestChunk test	
 * 14: Alloc test	
 * 15: Count test	
 * 16: Free test	
 * 17: LargestChunk test
 * 18: Count test																				
 */
int TestVsm(void)
{
	int count_errs = 0;
	void *temp = NULL;
	void *temp1 = NULL;
	void *pool = NULL;
	vsm_pool_t *vsm = NULL;


	
	if (NULL == (pool = malloc(496)))
	{
		MALLOC_ERROR;		/* Prints an error message 		*/
		
		return (-1);			
	}

	/* 1: Init test									*/
	vsm = VSMInit(pool, 496);
	if (NULL == vsm)
	{
		printf("function: VSMInit\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted Init returned NULL\n");
		++count_errs;
	}

	/* 2: Count test										*/
	count_errs += Tester((long)VSMCountFree(vsm), 472, "Count: ", __LINE__);

	/* 3: LargestChunk test									*/
	count_errs += Tester((long)VSMLargestChunk(vsm), 472, "Count: ", __LINE__);

	/* 4: Alloc test										*/
	if (NULL == (temp = VSMAlloc(vsm, 56)))
	{
		++count_errs;
		printf("function: VSMAlloc\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted Alloc returned NULL\n");			
	}	
	
	temp1 = temp;

	/* 5: Count test										*/
	count_errs += Tester((long)VSMCountFree(vsm), 400, "Count: ", __LINE__);


	/* 6: LargestChunk test									*/
	count_errs += Tester((long)VSMLargestChunk(vsm), 400, "Count: ", __LINE__);

	/* 7: Free test											*/
	VSMFree(temp);

	/* 8: Count test										*/
	count_errs += Tester((long)VSMCountFree(vsm), 456, "Count: ", __LINE__);

	/* 9: Alloc All test									*/
	while (1)
	{
		if (NULL == (temp = VSMAlloc(vsm, 5)))
		{
			break;			
		}
	}

	/* 10: LargestChunk test									*/
	count_errs += Tester((long)VSMLargestChunk(vsm), 0, "Count: ", __LINE__);

	/* 11: Free test											*/
	VSMFree(temp1);

	/* 12: Count test										*/
	count_errs += Tester((long)VSMCountFree(vsm), 8, "Count: ", __LINE__);

	/* 13: LargestChunk test									*/
	count_errs += Tester((long)VSMLargestChunk(vsm), 8, "Count: ", __LINE__);

	/* 14: Alloc test										*/
	if (NULL != (temp = VSMAlloc(vsm, 57)))
	{
		++count_errs;
		printf("function: VSMAlloc\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted NULL returned Alloc\n");			
	}

	/* 15: Count test										*/
	count_errs += Tester((long)VSMCountFree(vsm), 8, "Count: ", __LINE__);
	
	/* 16: Free test										*/
	VSMFree(temp);

	/* 17: LargestChunk test									*/
	count_errs += Tester((long)VSMLargestChunk(vsm), 8, "Count: ", __LINE__);

	/* 18: Count test										*/
	count_errs += Tester((long)VSMCountFree(vsm), 8, "Count: ", __LINE__);

	free(pool);

	return(count_errs);
}


static int Tester(long actual_value, long expected_value, char *str, int line)
{	
	if (actual_value != expected_value)
	{
		printf("function: %s  in line: %d ", str, line);
		printf("- status: fail... expected value was %ld and actual value is %ld\n",
				expected_value, actual_value);
		puts("");
				
		return (1);
	}
	
	return (0);
}
