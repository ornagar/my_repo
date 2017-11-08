/*******************************************************************************
 *  Author: Or Nagar.
 *  Creation date: 21.06.17
 *  Last modified: 22.06.17
 *  Building Sorted Linked List. 
 *  Functions test file.
 ******************************************************************************/
#include <stdio.h>			/* printf()			*/
#include <stdlib.h>			/* EXIT_SUCCESS		*/

#include "pqueue.h"

static int Tester(long actual_value, long expected_value, char *str, int line);
static int TestPqueue(void);		
static int IsBefore(const void *data1,const void *data2, void *param);
static int IsEqual(const void *data, const void *param);

int main(void)
{
	int err_sum = 0;
	
	err_sum += TestPqueue();
	
	if (0 == err_sum)
	{
		puts("PRIORITY QUEUE TEST SUCCESS!!");
	}
	else
	{
		printf("found %d bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

/* 1: create test
 * 2: IsEmpty test
 * 3: Size test
 * 4: Enqueue test
 * 5: IsEmpty test
 * 6: Size test
 * 7: Dequeue test
 * 8: IsEmpty test
 * 9: Enqueue test
 * 10: Enqueue test
 * 11: Insert test
 * 12: Clear test	
 * 13: IsEmpty test	
 * 14: Enqueue test
 * 15: Enqueue test
 * 16: Insert test
 * 17: Size test
 * 18: Remove test	
 * 19: Size test
 * 20: Destroy test					
 */

int TestPqueue(void)		
{
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12, 13, 14, 15, 16, 17}; 
	int count_errs = 0;
	int x = 1;
	void *data1 = &x;
	pqueue_t *pq = NULL;

	/*1: create test						*/					
	pq = PqueueCreate(IsBefore,  NULL);
	if (NULL == pq)
	{
		printf("function: Create\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}

	/*		 2: IsEmpty test					*/
	count_errs += Tester((long)PqueueIsEmpty(pq), 1, "IsEmpty: ", __LINE__);

	/*		 3: Size test						*/
	count_errs += Tester((long)PqueueSize(pq), 0, "Size: ", __LINE__);

	/*		 4: Enqueue test						*/
		PqueueEnqueue(pq,  &data[5]);
	if (6 != *(int *)PqueuePeek(pq))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 6, *(int *)PqueuePeek(pq));
		++count_errs;
	}

	/*		 5: IsEmpty test					*/
	count_errs += Tester((long)PqueueIsEmpty(pq), 0, "IsEmpty: ", __LINE__);

	/*		 6: Size test						*/
	count_errs += Tester((long)PqueueSize(pq), 1, "Size: ", __LINE__);

	/*		 7: Dequeue test						*/
	PqueueDequeue(pq);
	PqueueDequeue(pq);	/* underflow */

	/*		 8: IsEmpty test					*/
	count_errs += Tester((long)PqueueIsEmpty(pq), 1, "IsEmpty: ", __LINE__);

	/*		 9: Enqueue test						*/
		PqueueEnqueue(pq,  &data[6]);
	if (7 != *(int *)PqueuePeek(pq))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 7, *(int *)PqueuePeek(pq));
		++count_errs;
	}

	/*		 10: Enqueue test					*/
		PqueueEnqueue(pq,  &data[0]);
	if (7 != *(int *)PqueuePeek(pq))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 7, *(int *)PqueuePeek(pq));
		++count_errs;
	}

	/*		 11: Insert test					*/
	PqueueEnqueue(pq,  &data[10]);
	if (11 != *(int *)PqueuePeek(pq))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 7, *(int *)PqueuePeek(pq));
		++count_errs;
	}

	/*		 12: Clear test					*/
	PqueueClear(pq);

	/*		 13: IsEmpty test					*/
	count_errs += Tester((long)PqueueIsEmpty(pq), 1, "IsEmpty: ", __LINE__);

	/*		 14: Enqueue test						*/
		PqueueEnqueue(pq,  &data[6]);
	if (7 != *(int *)PqueuePeek(pq))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 7, *(int *)PqueuePeek(pq));
		++count_errs;
	}

	/*		 15: Enqueue test					*/
		PqueueEnqueue(pq,  &data[0]);
	if (7 != *(int *)PqueuePeek(pq))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 7, *(int *)PqueuePeek(pq));
		++count_errs;
	}

	/*		 16: Insert test					*/
	PqueueEnqueue(pq,  &data[10]);
	if (11 != *(int *)PqueuePeek(pq))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 7, *(int *)PqueuePeek(pq));
		++count_errs;
	}

	/*		 17: Size test						*/
	count_errs += Tester((long)PqueueSize(pq), 3, "Size: ", __LINE__);


	/*		18: Remove test						*/
	if (1 !=  *(int *)PqueueRemove(pq, IsEqual, data1))
	{
		printf("function: Remove\t in line: %d\t", __LINE__);
		printf("- status: fail... expected 7,  returned NULL");
		++count_errs;
	}

	/*		 19: Size test						*/
	count_errs += Tester((long)PqueueSize(pq), 2, "Size: ", __LINE__);



	/*		 20: Destroy test					*/
	PqueueDestroy(pq);

	return (count_errs);
}



static int IsBefore(const void *data1, const void *data2, void *param)
{
	return(*(int *) data1 > *(int *) data2);
}

static int IsEqual(const void *data, const void *param)
{
	return(*(int *) data == *(int *) param);
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

