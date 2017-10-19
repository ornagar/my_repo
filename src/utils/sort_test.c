/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Sort                                   #################################
 *                                         ##########    ####       ########
 *  Tester                                 ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  12-07-2017                             ##########    ####  ###  ######## 
 *  14:44:44                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* EXIT_SUCCESS		 		  */
#include <time.h>					 /* clock()						  */

#include "sort.h"					 /* all functions declerations	  */

#define ARR_SIZE 	(5000)
static int IsBefore(const void *data1, const void *data2, void *param);
static size_t MyKey(const void *element, const void *args);
static int compare(const void *x, const void *y);
static int TestBubble(long array[]);
static int TestInsertion(long array[]);
static int TestSelection(long array[]);
static int TestCounting(long array[]);
static int TestRadix(long array[]);
static int Testqsort(long array[]);
static int TestMergesort(long array[]);
static int TestMyQsort(long array[]);
static int TestBinSearch(long array[]);
static int TestHeapSort(long array[]);
/*
 * A module to test the sorting algorithms.
 * each algorithm is tested with an array of 5000 
 * random numbers, and all of them are compared by execution time.
 */
int main(void)
{
	int err_sum = 0;
	unsigned long i = 0;
	long int arr[ARR_SIZE];

	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = rand();
	}

	err_sum += TestBubble(arr);
	err_sum += TestInsertion(arr);
	err_sum += TestSelection(arr);
	err_sum += TestCounting(arr);
	err_sum += TestRadix(arr);
	err_sum += Testqsort(arr);
	err_sum += TestMergesort(arr);
	err_sum += TestMyQsort(arr);
	err_sum += TestBinSearch(arr);
	err_sum += TestHeapSort(arr);
	
	if (0 == err_sum)
	{
		puts("Sort TEST SUCCESS!!");
	}
	else
	{
		printf("found %d bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

static int TestBubble(long array[])
{
	unsigned long i = 0;
	long arr[ARR_SIZE];

	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = array[i];
	}

	i = clock();
	BubbleSort(arr, ARR_SIZE, sizeof(long), compare);
	i = clock() - i;
	printf("Buble sort: %lu\n", i);

	for (i = 0; i < ARR_SIZE - 1; ++i)
	{
		if (arr[i] > arr[i + 1])
		{
			printf("Error in function BubbleSort\n");
			return(1);
		}
	}

	return(0);
}

static int TestInsertion(long array[])
{
	unsigned long i = 0;
	long int arr[ARR_SIZE];

	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = array[i];
	}

	i = clock();
	InsertionSort(arr, ARR_SIZE, sizeof(long), compare);
	i = clock() - i;
	printf("Insertion sort: %lu\n", i);

	for (i = 0; i < ARR_SIZE - 1; ++i)
	{
		if (arr[i] > arr[i + 1])
		{
			printf("Error in function InsertionSort\n");
			return(1);
		}
	}

	return(0);
}

static int TestSelection(long array[])
{
	unsigned long i = 0;
	long int arr[ARR_SIZE];

	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = array[i];
	}

	i = clock();
	SelectionSort(arr, ARR_SIZE, sizeof(long), compare);
	i = clock() - i;
	printf("Selection sort: %lu\n", i);

	for (i = 0; i < ARR_SIZE - 1; ++i)
	{
		if (arr[i] > arr[i + 1])
		{
			printf("Error in function SelectionSort\n");
			return(1);
		}
	}

	return(0);
}

static int TestCounting(long array[])
{
	unsigned long i = 0;
	unsigned long arr[ARR_SIZE];

	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = (size_t)((rand() % 99) + 1);
	}

	i = clock();
	CountingSort(arr, ARR_SIZE, sizeof(long), MyKey, NULL, 100);
	i = clock() - i;
	printf("Counting sort: %lu\n", i);

	for (i = 0; i < ARR_SIZE - 1; ++i)
	{
		if (arr[i] > arr[i + 1])
		{
			printf("Error in function CountingSort\n");
			return(1);
		}
	}

	return(0);
}

static int TestRadix(long array[])
{
	unsigned long i = 0;
	unsigned long arr[ARR_SIZE];

	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = rand();
	}

	i = clock();
	RadixSort(arr, ARR_SIZE, sizeof(long), MyKey, NULL, 4);
	i = clock() - i;
	printf("Radix sort: %lu\n", i);

	for (i = 0; i < ARR_SIZE - 1; ++i)
	{	
		if (arr[i] > arr[i + 1])
		{
			printf("Error in function RadixSort\n");
			return(1);
		}
	}

	return(0);
}

static int Testqsort(long array[])
{
	unsigned long i = 0;
	long int arr[ARR_SIZE];

	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = array[i];
	}

	i = clock();
	qsort(arr, ARR_SIZE, sizeof(long), compare);
	i = clock() - i;
	printf("qsort: %lu\n", i);

	for (i = 0; i < ARR_SIZE - 1; ++i)
	{
		if (arr[i] > arr[i + 1])
		{
			printf("Error in function SelectionSort\n");
			return(1);
		}
	}

	return(0);
}

static int TestMergesort(long array[])
{
	unsigned long i = 0;
	long int arr[ARR_SIZE];

	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = array[i];
	}

	i = clock();
	MergeSort(arr, ARR_SIZE, sizeof(long), compare);
	i = clock() - i;
	printf("merrge sort: %lu\n", i);

	for (i = 0; i < ARR_SIZE - 1; ++i)
	{	
		if (arr[i] > arr[i + 1])
		{
			printf("Error in function MergeSort\n");
			return(1);
		}
	}

	return(0);
}

static int TestMyQsort(long array[])
{
	unsigned long i = 0;
	long int arr[ARR_SIZE];
	long *data = NULL;
	
	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = array[i];
	}

	i = clock();
	QuickSort(arr, ARR_SIZE, sizeof(long), compare);
	i = clock() - i;
	printf("My quick sort: %lu\n", i);

	for (i = 0; i < ARR_SIZE - 1; ++i)
	{	
		if (arr[i] > arr[i + 1])
		{
			printf("Error in function MyQSort\n");
			return(1);
		}
	}
	
	data = (long *)BinSearch(arr, ARR_SIZE, sizeof(long), compare, &array[2]);
	if (data == NULL)
	{
		puts("error");
	}

	return(0);
}

static int TestBinSearch(long array[])
{
	unsigned long i = 0;
	long int arr[10];
	long find = 2;
	long *data = NULL;
	
	for (i = 0; i < 10; ++i)
	{
		arr[i] = i;
	}
	
	data = (long *)BinSearch(arr, 10, sizeof(long), compare, &find);
	if (data != NULL)
	{
		printf("found: %lu\n", *data);
	}
	else
	{
		puts("error");
	}
	return(0);
}

static int TestHeapSort(long array[])
{
	unsigned long i = 0;
	long int arr[ARR_SIZE];
	
	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = array[i];
	}
	
	i = clock();
	HeapSort(arr, ARR_SIZE, sizeof(long), IsBefore, NULL);
	i = clock() - i;
	printf("Heap sort: %lu\n", i);

	for (i = 0; i < ARR_SIZE - 1; ++i)
	{	
		if (arr[i] > arr[i + 1])
		{
			printf("Error in function HeapSort\n");
			return(1);
		}
	}
	
	return(0);
}

static int compare(const void *x, const void *y)
{
	if (*(long *)x > *(long *)y)
	{
		return(1);
	}
	else if (*(long *)x < *(long *)y)
	{
		return(-1);
	}
	else
	{
		return(0);
	}
}

static size_t MyKey(const void *element, const void *args)
{
	return(*(size_t *)element);
}

static int IsBefore(const void *data1, const void *data2, void *param)
{
	return (*(int *)data1 > *(int *)data2);
}
