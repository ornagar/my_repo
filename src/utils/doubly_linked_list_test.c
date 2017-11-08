/*****************************************************************************
 * Or Nagar.
 * Doubly linked list library.
 * Test file.
 * 19/06/17
 ****************************************************************************/
#include <stdio.h>			/* printf()			*/
#include <stdlib.h>			/* EXIT_SUCCESS		*/

#include "doubly_linked_list.h"

static int Tester(long actual_value, long expected_value, char *str, int line);
static int TestDoubly(void);		
static int MyPrint(void *data, void *param);
static int IsEqual(const void *data, const void *param);

int main(void)
{
	int err_sum = 0;
	
	err_sum += TestDoubly();
	
	if (0 == err_sum)
	{
		puts("Doubly Linked List TEST SUCCESS!!");
	}
	else
	{
		printf("found %d bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

/* 1: create test
 * 2: IsEmpty test
 * 3: Count test
 * 4: Insert test
 * 5: IsEmpty test
 * 6: Count test
 * 7: Erase test
 * 8: IsEmpty test
 * 9: PushBack test
 * 10: PushBack test
 * 11: PushFront test
 * 12: Foreach->Print test
 * 13: create test
 * 14: IsEmpty test
 * 15: Insert test
 * 16: IsEmpty test
 * 17: Erase test
 * 18: IsEmpty test
 * 19: PushBack test
 * 20: PushBack test
 * 21: PushFront test
 * 22: Foreach->Print test
 * 23: SpliceBefore test
 * 24: Foreach->Print test
 * 25: Count test
 * 26: Count test
 * 27: IsSameIterator test
 * 28: IsBadIterator test
 * 29: PopBack test
 * 30: PopFront test
 * 31: Find test
 * 32: Find test
 * 33: Find test
 * 34: Destroy test
 */
int TestDoubly(void)		
{
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12, 13, 14, 15, 16, 17}; 
	int count_errs = 0;
	int temp = 2;
	int *data_pop = NULL;
	dlist_t *dl = NULL;
	dlist_t *dl2 = NULL;
	dlist_iter_t iter = NULL;
	dlist_iter_t iter2 = NULL;
	dlist_iter_t iter3 = NULL;
	
	/* 1: create test						*/
	dl = DlistCreate();
	if (NULL == dl)
	{
		printf("function: Create\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 2: IsEmpty test						*/
	count_errs += Tester((long)DlistIsEmpty(dl), 1, "IsEmpty: ", __LINE__);
	
	/* 3: Count test						*/
	count_errs += Tester((long)DlistCount(dl), 0, "Count: ", __LINE__);
	
	/* 4: Insert test						*/
	iter = DlistInsert(dl, DlistEnd(dl), &data[0]);
	if (DlistEnd(dl) == iter)
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 5: IsEmpty test						*/
	count_errs += Tester((long)DlistIsEmpty(dl), 0, "IsEmpty: ", __LINE__);
	
	/* 6: Count test						*/
	count_errs += Tester((long)DlistCount(dl), 1, "Count: ", __LINE__);
	
	/* 7: Erase test						*/
	iter = DlistErase(iter);
	if (DlistEnd(dl) != iter)
	{
		printf("function: Erase\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 8: IsEmpty test						*/
	count_errs += Tester((long)DlistIsEmpty(dl), 1, "IsEmpty: ", __LINE__);
	
	/* 9: PushBack test						*/
	iter = DlistPushBack(dl, &data[0]);
	if (DlistEnd(dl) == iter)
	{
		printf("function: PushBack\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 10: PushBack test					*/
	iter = DlistPushBack(dl, &data[1]);
	if (DlistEnd(dl) == iter)
	{
		printf("function: PushBack\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 11: PushFront test					*/
	iter = DlistPushFront(dl, &data[2]);
	if (DlistEnd(dl) == iter)
	{
		printf("function: PushFront\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 12: Foreach->Print test				*/
	DlistForeach(DlistBegin(dl), DlistEnd(dl), MyPrint, NULL);
	puts("");
	
	/* 13: create test						*/
	dl2 = DlistCreate();
	if (NULL == dl2)
	{
		printf("function: Create\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 14: IsEmpty test						*/
	count_errs += Tester((long)DlistIsEmpty(dl2), 1, "IsEmpty: ", __LINE__);
	
	/* 15: Insert test						*/
	iter2 = DlistInsert(dl2, DlistEnd(dl2), &data[3]);
	if (DlistEnd(dl2) == iter2)
	{
		printf("function: Insert\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 16: IsEmpty test						*/
	count_errs += Tester((long)DlistIsEmpty(dl2), 0, "IsEmpty: ", __LINE__);
	
	/* 17: Erase test						*/
	iter2 = DlistErase(iter2);
	if (DlistEnd(dl2) != iter2)
	{
		printf("function: Erase\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 18: IsEmpty test						*/
	count_errs += Tester((long)DlistIsEmpty(dl2), 1, "IsEmpty: ", __LINE__);
	
	/* 19: PushBack test					*/
	iter2 = DlistPushBack(dl2, &data[3]);
	if (DlistEnd(dl2) == iter2)
	{
		printf("function: PushBack\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 20: PushBack test					*/
	iter3 = DlistPushBack(dl2, &data[4]);
	if (DlistEnd(dl2) == iter3)
	{
		printf("function: PushBack\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 21: PushFront test					*/
	iter2 = DlistPushFront(dl2, &data[5]);
	if (DlistEnd(dl2) == iter2)
	{
		printf("function: PushFront\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 22: Foreach->Print test				*/
	DlistForeach(DlistBegin(dl2), DlistEnd(dl2), MyPrint, NULL);
	puts("");
	
	iter = DlistBegin(dl);
	iter3 = DlistEnd(dl2);
	
	/* 23: SpliceBefore test				*/
	DlistSpliceBefore(iter, iter2, iter3);
	
	/* 24: Foreach->Print test				*/
	DlistForeach(DlistBegin(dl), DlistEnd(dl), MyPrint, NULL);
	puts("");
	
	/* 25: Count test						*/
	count_errs += Tester((long)DlistCount(dl), 6, "Count: ", __LINE__);
	
	/* 26: Count test						*/
	count_errs += Tester((long)DlistCount(dl2), 0, "Count: ", __LINE__);
	
	/* 27: IsSameIterator test				*/
	count_errs += Tester((long)DlistIsSameIterator(iter, iter2), 0, "Count: ", __LINE__);
	iter2 = iter;
	count_errs += Tester((long)DlistIsSameIterator(iter, iter2), 1, "Count: ", __LINE__);
	
	
	/* 28: IsBadIterator test				*/
	count_errs += Tester((long)DlistIsBadIterator(dl, iter), 0, "Count: ", __LINE__);
	iter = DlistEnd(dl);
	count_errs += Tester((long)DlistIsBadIterator(dl, iter), 1, "Count: ", __LINE__);
	
	/* 29: PopBack test						*/
	data_pop = DlistPopBack(dl);
	if (temp != *data_pop)
	{
		printf("function: PopBack\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", temp, *data_pop);
		++count_errs;
	}
	
	/* 30: PopFront test					*/
	temp = 6;
	data_pop = DlistPopFront(dl);
	if (6 != *data_pop)
	{
		printf("function: PopFront\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", temp, *data_pop);
		++count_errs;
	}
	
	/* 31: Find test						*/
	*data_pop = 1;
	iter = DlistFind(dl, DlistBegin(dl), DlistEnd(dl),	IsEqual, data_pop);
	if (*(int *) DlistGetData(iter) != *data_pop)
	{
		printf("function: PopFront\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", temp, *data_pop);
		++count_errs;
	}
	/* 32: Find test						*/
	*data_pop = 9;
	iter = DlistFind(dl, DlistBegin(dl), DlistEnd(dl),	IsEqual, data_pop);
	if (DlistGetData(iter) == DlistEnd(dl))
	{
		printf("function: PopFront\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", temp, *data_pop);
		++count_errs;
	}
	/* 33: Find test						*/
	*data_pop = 4;
	iter = DlistFind(dl, DlistBegin(dl), DlistPrev(DlistEnd(dl)),	IsEqual, data_pop);
	if (*(int *) DlistGetData(iter) != *data_pop)
	{
		printf("function: PopFront\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", temp, *data_pop);
		++count_errs;
	}
	
	
	/* 34: Destroy test						*/
	DlistDestroy(dl2);
	DlistDestroy(dl);
	
	return (count_errs);

}

/* Action function for Foreach function to print list */
static int MyPrint(void *data, void *param)
{
	printf(" - %d", *(int *) data);
	
	return(0);
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

