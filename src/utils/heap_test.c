/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Heap                                   #################################
 *                                         ##########    ####       ########
 *  Tester                                 ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  02-08-2017                             ##########    ####  ###  ######## 
 *  14:30:43                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <time.h>					 /* clock()						  */

#include "heap.h"					 /* all functions declerations	  */
#include "utils.h"					 /* Or's functions                */

#define ARR_SIZE 		(5000)

static int IsBefore(const void *data1, const void *data2, void *param);

static int TestHeap(void);

int main(void)
{
	size_t err_sum = 0;

	err_sum = TestHeap();

	if (0 == err_sum)
	{
		puts("\nHEAP TEST SUCCESS!!\n");
	}
	else
	{
		printf("\nfound %lu bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

static int TestHeap(void)
{
	heap_t *hp = HeapCreate(sizeof(int), IsBefore, NULL);
	int arr[ARR_SIZE];
	int i = 0; 
	/*int b = 3250;
	*/int count_errs = 0;
	
	TEST(0 == HeapSize(hp), "size test", count_errs);
	
	srand(clock());
	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = rand() % ARR_SIZE;
	}
	
	for (i = 0; i < ARR_SIZE; ++i)
	{
		HeapPush(hp, &arr[i]);
	}
	
	TEST(ARR_SIZE == HeapSize(hp), "size test", count_errs);
	
	for (i = 0; i < ARR_SIZE; ++i)
	{
		HeapPop(hp);
	}
	
	HeapPop(hp);
	TEST(0 == HeapSize(hp), "size test", count_errs);
	
	HeapDestroy(hp);
	
	return (count_errs);
}

static int IsBefore(const void *data1, const void *data2, void *param)
{
	return (*(int *)data1 > *(int *)data2);
}
