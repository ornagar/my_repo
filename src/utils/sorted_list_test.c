/*******************************************************************************
 *  Author: Or Nagar.
 *  Creation date: 21.06.17
 *  Last modified: 22.06.17
 *  Building Sorted Linked List. 
 *  Functions test file.
 ******************************************************************************/
#include <stdio.h>			/* printf()			*/
#include <stdlib.h>			/* EXIT_SUCCESS		*/

#include "sorted_list.h"

static int Tester(long actual_value, long expected_value, char *str, int line);
static int TestSorted(void);		
static int MyPrint(void *data, void *param);
static int IsBefore(const void *data1,const void *data2, void *param);
static int IsEqual(const void *data1, const void *param);

int main(void)
{
	int err_sum = 0;
	
	err_sum += TestSorted();
	
	if (0 == err_sum)
	{
		puts("Sorted Linked List TEST SUCCESS!!");
	}
	else
	{
		printf("found %d bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

/*  1: create test 
 *  2: IsEmpty test 
 *  3: Size test 
 *  4: Insert test	 
 *  5: IsEmpty test 
 *  6: Size test 
 *  7: Erase test	 
 *  8: IsEmpty test
 *  9: Insert test	 
 * 10: Insert test * 11: Insert test 
 * 12: Foreach->Print test 
 * 13: create test 
 * 14: IsEmpty test 
 * 15: Insert test 
 * 16: IsEmpty test 
 * 17: Insert test
 * 18: Insert test 
 * 19: Insert test 
 * 20: Insert test 
 * 21: Foreach->Print test 
 * 22: Merge test 
 * 23: Foreach->Print test 
 * 24: Size test	 
 * 25: Size test 
 * 26: IsSameIterator test 
 * 27: IsBadIterator test	
 * 28: PopBack test
 * 29: PopFront test
 * 31: Find test		
 * 32: Find test	
 * 33: Find test			
 * 34: Destroy test					
 */
int TestSorted(void)		
{
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12, 13, 14, 15, 16, 17}; 
	int count_errs = 0;
	int *data_pop = NULL;
	sorted_list_t *sl = NULL;
	sorted_list_t *sl2 = NULL;
	sorted_list_iter_t iter;
	sorted_list_iter_t iter2;

	/*1: create test						*/					
	sl = SlistCreate(IsBefore,  NULL);
	if (NULL == sl)
	{
		printf("function: Create\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}

	/*	 2: IsEmpty test					*/
	count_errs += Tester((long)SlistIsEmpty(sl), 1, "IsEmpty: ", __LINE__);

	/*	 3: Size test						*/
	count_errs += Tester((long)SlistSize(sl), 0, "Size: ", __LINE__);

	/*	 4: Insert test						*/
	iter = SlistInsert(sl,  &data[5]);
	if (6 != *(int *)SlistGetData(iter))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 6, *(int *)SlistGetData(iter));
		++count_errs;
	}

	/*	 5: IsEmpty test					*/
	count_errs += Tester((long)SlistIsEmpty(sl), 0, "IsEmpty: ", __LINE__);

	/*	 6: Size test						*/
	count_errs += Tester((long)SlistSize(sl), 1, "Size: ", __LINE__);

	/*	 7: Erase test						*/
	iter2 = SlistEnd(sl);
	iter = SlistRemove(iter);
	if (iter2.iter != iter.iter)
	{
		printf("function: Remove\t in line: %d\t", __LINE__);
		puts("- status: fail... expected removal\n");
		++count_errs;
	}

	/*	 8: IsEmpty test					*/
	count_errs += Tester((long)SlistIsEmpty(sl), 1, "IsEmpty: ", __LINE__);

	/*	 9: Insert test						*/
	iter = SlistInsert(sl,  &data[6]);
	if (7 != *(int *)SlistGetData(iter))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 7, *(int *)SlistGetData(iter));
		++count_errs;
	}

	/*	 10: Insert test					*/
	iter = SlistInsert(sl,  &data[0]);
	if (1 != *(int *)SlistGetData(iter))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 1, *(int *)SlistGetData(iter));
		++count_errs;
	}

	/*	 11: Insert test					*/
	iter = SlistInsert(sl,  &data[10]);
	if (11 != *(int *)SlistGetData(iter))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 11, *(int *)SlistGetData(iter));
		++count_errs;
	}

	/*	 12: Foreach->Print test			*/
	SlistForEach(SlistBegin(sl), SlistEnd(sl), MyPrint, NULL);
	puts("");

	/*	 13: create test					*/
	sl2 = SlistCreate(IsBefore,  NULL);
	if (NULL == sl2)
	{
		printf("function: Create\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}

	/*	 14: IsEmpty test					*/
	count_errs += Tester((long)SlistIsEmpty(sl2), 1, "IsEmpty: ", __LINE__);

	/*	 15: Insert test					*/
	iter2 = SlistInsert(sl2, &data[3]);
	if (4 != *(int *)SlistGetData(iter2))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 4, *(int *)SlistGetData(iter2));
		++count_errs;
	}

	/*	 16: IsEmpty test					*/
	count_errs += Tester((long)SlistIsEmpty(sl2), 0, "IsEmpty: ", __LINE__);

	/*	 17: Insert test					*/
	iter2 = SlistInsert(sl2, &data[16]);
	if (17 != *(int *)SlistGetData(iter2))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 17, *(int *)SlistGetData(iter2));
		++count_errs;
	}	

	/*	 18: Insert test					*/
	iter2 = SlistInsert(sl2, &data[15]);
	if (16 != *(int *)SlistGetData(iter2))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 16, *(int *)SlistGetData(iter2));
		++count_errs;
	}	

	/*	 19: Insert test					*/
	iter2 = SlistInsert(sl2, &data[1]);
	if (2 != *(int *)SlistGetData(iter2))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 2, *(int *)SlistGetData(iter2));
		++count_errs;
	}	

	/*	 20: Insert test					*/
	iter2 = SlistInsert(sl2, &data[2]);
	if (3 != *(int *)SlistGetData(iter2))
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 3, *(int *)SlistGetData(iter2));
		++count_errs;
	}	

	/*	 21: Foreach->Print test			*/
	SlistForEach(SlistBegin(sl2), SlistEnd(sl2), MyPrint, NULL);
	puts("");


	/*	 22: Merge test						*/
	SlistMerge(sl, sl2);

	/*	 23: Foreach->Print test			*/
	SlistForEach(SlistBegin(sl), SlistEnd(sl), MyPrint, NULL);
	puts("");

	/*	 24: Size test						*/
	count_errs += Tester((long)SlistSize(sl), 8, "Size: ", __LINE__);

	/*	 25: Size test						*/
	count_errs += Tester((long)SlistSize(sl2), 0, "Size: ", __LINE__);

	/*	 26: IsSameIterator test			*/
	count_errs += Tester((long)SlistIsSameIterator(iter, iter2), 0, "Size: ", __LINE__);
	iter2.iter = iter.iter;
	count_errs += Tester((long)SlistIsSameIterator(iter, iter2), 1, "Size: ", __LINE__);

	/*	 27: IsBadIterator test				*/
	count_errs += Tester((long)SlistIsBadIterator(sl, iter), 0, "Size: ", __LINE__);
	iter = SlistEnd(sl);
	count_errs += Tester((long)SlistIsBadIterator(sl, iter), 1, "Size: ", __LINE__);

	/*	 28: PopBack test					*/
	data_pop = SlistPopBack(sl);
	if (17 != *data_pop)
	{
		printf("function: PopBack\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 17, *data_pop);
		++count_errs;
	}

	/*	 29: PopFront test					*/
	data_pop = SlistPopFront(sl);
	if (1 != *data_pop)
	{
		printf("function: PopFront\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 1, *data_pop);
		++count_errs;
	}

	/*	 31: Find test						*/
	*data_pop = 16;
	iter = SlistFind(sl, SlistBegin(sl), SlistEnd(sl),	IsEqual, data_pop);
	if (*(int *) SlistGetData(iter) != *data_pop)
	{
		printf("function: PopFront\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", *(int *) SlistGetData(iter), *data_pop);
		++count_errs;
	}

	/*	 32: Find test						*/
	*data_pop = 9;
	iter = SlistFind(sl, SlistBegin(sl), SlistEnd(sl),	IsEqual, data_pop);
	if (iter.iter != SlistEnd(sl).iter)
	{
		printf("function: PopFront\t in line: %d\t", __LINE__);
		printf("- status: fail... expected SlistEnd");
		++count_errs;
	}

	/*	 33: Find test						*/
	*data_pop = 4;
	iter = SlistFind(sl, SlistBegin(sl), SlistPrev(SlistEnd(sl)),	IsEqual, data_pop);
	if (*(int *) SlistGetData(iter) != *data_pop)
	{
		printf("function: PopFront\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", *(int *) SlistGetData(iter), *data_pop);
		++count_errs;
	}


	/*	 34: Destroy test					*/
	SlistDestroy(sl2);
	SlistDestroy(sl);

	return (count_errs);
}

static int IsBefore(const void *data1, const void *data2, void *param)
{
	return(*(int *) data1 <= *(int *) data2);
}

/* Action function for Foreach function to print list */
static int MyPrint(void *data, void *param)
{
	printf(" - %d", *(int *) data);
	
	return(0);
}

static int IsEqual(const void *data1, const void *param)
{
	return(*(int *) data1 == *(int *) param);
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

