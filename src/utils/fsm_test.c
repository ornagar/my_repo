/*****************************************************************************
 * Or Nagar.
 * FSM library.
 * Test file.
 * 04/07/17
 ****************************************************************************/
#include <stdio.h>			/* printf()										*/
#include <stdlib.h>			/* EXIT_SUCCESS									*/

#include "utils.h"			/* PRINT_ERROR									*/
#include "fsm.h"

static int Tester(long actual_value, long expected_value, char *str, int line);
int TestFsm(void);
void PrintFsm(const fsm_t *fsm);				/* Prints the FSM pool status 	*/

int main(void)
{
	size_t err_sum = 0;

	err_sum = TestFsm();

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


/* 1: SugestSize test
 * 2: Count test
 * 3: Alloc test
 * 4: Count test
 * 5: Count test
 * 6: Alloc All test
 * 7: Count test
 */
int TestFsm(void)
{
	int count_errs = 0;
	void *pool = NULL;
	void *allocated = NULL;
	fsm_t *fsm = NULL;

	/* 1: SugestSize test									*/
	if (NULL == (pool = malloc(FSMSugestSize(50, 7))))
	{
		MALLOC_ERROR;		/* Prints an error message 		*/
		
		return (-1);			
	}

	fsm = FSMInit(pool, 50, 7);
	if (NULL == fsm)
	{
		printf("function: FSMInit\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted Init returned NULL\n");
		++count_errs;
	}


	/* 2: Count test										*/
	count_errs += Tester((long)FSMCountFree(fsm), 50, "Count: ", __LINE__);

	/* 3: Alloc test										*/
	allocated = FSMAlloc(fsm);

	/* 4: Count test										*/
	count_errs += Tester((long)FSMCountFree(fsm), 49, "Count: ", __LINE__);

	PrintFsm(fsm);

	FSMFree(allocated);

	/* 5: Count test										*/
	count_errs += Tester((long)FSMCountFree(fsm), 50, "Count: ", __LINE__);

	/* 6: Alloc All test									*/
	while (1)
	{
		if (NULL == (allocated = FSMAlloc(fsm)))
		{
			break;			
		}
	}
	
	/* 7: Count test										*/
	count_errs += Tester((long)FSMCountFree(fsm), 0, "Count: ", __LINE__);
	
	PrintFsm(fsm);

	free(pool);

	return(0);
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
