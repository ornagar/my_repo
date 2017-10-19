/*******************************************************************************
 *  Or Nagar.
 *  DynVec library.  
 *  Functions tests.
 *  08/06/17
 ******************************************************************************/
#include <stdio.h>			/* printf()			*/
#include <stdlib.h>			/* EXIT_SUCCESS		*/

#include "utils.h"			/* DBG()	 		*/
#include "d_vector.h"			
#include "d_vector_debug.h"	

void Tester(long actual_value, long expected_value, char *str, int line);
void TestDynVecInteger(void);
void TestDynVecChar(void);

int main(void)
{
	TestDynVecInteger();
	
	TestDynVecChar();
	
	puts("SUCCESS!!");
	
	return (EXIT_SUCCESS);
}

void TestDynVecInteger(void)			/* Try to make one function for all */
{
	int a = 1;
	const int *ptr = NULL;
	
	dyn_vec_t *dv = DynVecCreate(0, sizeof(int));
	if (NULL == dv)
	{
		printf("function: DynVecCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
	}

	Tester((long)DynVecCapacity(dv), (long) 0, "Capacity: ", __LINE__);
	
	Tester((long)DynVecSize(dv), (long) 0, "Size: ", __LINE__);
	
	Tester((long)DynVecPushBack(dv, &a), (long) 0, "push test: ", __LINE__);
	
	ptr = DynVecGetItemAddres(dv, 0);
	Tester(*ptr, 1, "peek test: ", __LINE__);
	++a;
	
	Tester((long)DynVecSize(dv), (long) 1, "Size: ", __LINE__);
	
	Tester((long)DynVecPushBack(dv, &a), (long) 0, "push test: ", __LINE__);
	
	Tester((long)DynVecSize(dv), (long) 2, "Size: ", __LINE__);
	
	ptr = DynVecGetItemAddres(dv, 1);
	Tester(*ptr, (long) 2, "peek test: ", __LINE__);
	
	Tester((long)DynVecReserve(dv, 100), (long) 0, "Reserve: ", __LINE__);
	
	Tester((long)DynVecCapacity(dv), (long) 100, "Capacity: ", __LINE__);
	
	DBG(DynVecPrint(dv));
	
	Tester((long)DynVecPopBack(dv), (long) 0, "pop test: ", __LINE__);
	
	Tester((long)DynVecCapacity(dv), (long) 50, "Capacity: ", __LINE__);
	
	Tester((long)DynVecSize(dv), (long) 1, "Size: ", __LINE__);
	
	Tester((long)DynVecPopBack(dv), (long) 0, "pop test: ", __LINE__);
	
	Tester((long)DynVecSize(dv), (long) 0, "Size: ", __LINE__);
	
	Tester((long)DynVecPopBack(dv), (long) 1, "pop test: ", __LINE__);
	
	Tester((long)DynVecSize(dv), (long) 0, "Size: ", __LINE__);
	
	DynVecDestroy(dv);
}

/*
 * Test flow:
 * 1. Create
 * 2. 
 */
void TestDynVecChar(void)
{
	char a = 1;
	const char *ptr = NULL;
	
	int i = 0;

	/* 1. Create */
	dyn_vec_t *dv = DynVecCreate(0, sizeof(char));
	if (NULL == dv)
	{
		printf("function: DynVecCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
	}
	
	Tester((long)DynVecCapacity(dv), (long) 0, "Capacity: ", __LINE__);
	
	Tester((long)DynVecSize(dv), (long) 0, "Size: ", __LINE__);
	
	Tester((long)DynVecPushBack(dv, &a), (long) 0, "push test: ", __LINE__);
	
	ptr = DynVecGetItemAddres(dv, 0);
	Tester(*ptr, (long) 1, "peek test: ", __LINE__);
	++a;
	
	Tester((long)DynVecSize(dv), (long) 1, "Size: ", __LINE__);
	
	Tester((long)DynVecPushBack(dv, &a), (long) 0, "push test: ", __LINE__);
	
	Tester((long)DynVecSize(dv), (long) 2, "Size: ", __LINE__);
	
	ptr = DynVecGetItemAddres(dv, 1);
	Tester(*ptr, (long) 2, "peek test: ", __LINE__);
	
	Tester((long)DynVecReserve(dv, 100), (long) 0, "Reserve: ", __LINE__);
	
	Tester((long)DynVecCapacity(dv), (long) 100, "Capacity: ", __LINE__);
	
	Tester((long)DynVecPopBack(dv), (long) 0, "pop test: ", __LINE__);
	
	Tester((long)DynVecCapacity(dv), (long) 50, "Capacity: ", __LINE__);
	
	Tester((long)DynVecSize(dv), (long) 1, "Size: ", __LINE__);
	
	Tester((long)DynVecPopBack(dv), (long) 0, "pop test: ", __LINE__);
	
	Tester((long)DynVecSize(dv), (long) 0, "Size: ", __LINE__);
	
	Tester((long)DynVecPopBack(dv), (long) 1, "pop test: ", __LINE__);
	
	Tester((long)DynVecSize(dv), (long) 0, "Size: ", __LINE__);

	for (i = 0; i < 4800; ++i)
	{
		DynVecPushBack(dv, &a);
	}
	
	ptr = DynVecGetItemAddres(dv, 240);
	Tester(*ptr, 2, "peek test: ", __LINE__);

	DynVecDestroy(dv);
}

/* Tester for all integers */
void Tester(long actual_value, long expected_value, char *str, int line)
{	
	if (actual_value != expected_value)
	{
		printf("function: %s\t in line: %d\t", str, line);
		printf("- status: fail... wanted value was 0x%lx\
				 and return value is 0x%lx\n",
				expected_value, actual_value);
	}
}
