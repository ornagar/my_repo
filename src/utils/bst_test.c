/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Bst                                    #################################
 *                                         ##########    ####       ########
 *  Tester                                 ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  17-07-2017                             ##########    ####  ###  ######## 
 *  11:18:13                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* rand(), EXIT_SUCCESS		  */

#include "bst.h"					 /* all functions declerations	  */
#include "utils.h"					 /* Or's functions                */

static int Tester(long actual_value, long expected_value, char *str, int line);
static int TestBst(void);		
static int MyPrint(const void *data, const void *param);
static int IsEqual(const void *data, const void *data2, void *param);

int main(void)
{
	int err_sum = 0;

	err_sum += TestBst();
	
	if (0 == err_sum)
	{
		puts("Binary Search Tree TEST SUCCESS!!");
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
 * 4: Insert test 50 rand numbers
 * 5: IsEmpty test
 * 6: Count test	
 * 7: Foreach->Print test
 * 8: remove test		
 * 9: Count test	
 * 10: Find test
 * 11: Foreach->Print test	
 * 12: remove test		
 * 13: Foreach->Print test	
 * 14: Find test	
 * 15: remove test	
 * 16: Foreach->Print test	
 * 17: Find test	
 * 18: Prev test	
 * 19: remove test	
 * 20: Foreach->Print test	+ Max
 * 21: Count test	
 * 22: Begin test
 * 23: Prev test
 * 24: BadIterator test	
 * 25: Destroy test						
 */
int TestBst(void)		
{
	int data[50]; 
	int count_errs = 0;
	int *data_pop = NULL;
	bst_t *bst = NULL;
	bst_iter_t iter;
	int i = 0;
	int count = 0;

	for (i = 0; i < 50; ++i)
	{
		data[i] = rand() % 100;
	}
	
	
	/* 1: create test						*/
	bst = BSTCreate(IsEqual, NULL);
	if (NULL == bst)
	{
		printf("function: Create\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 2: IsEmpty test						*/
	count_errs += Tester((long)BSTIsEmpty(bst), 1, "IsEmpty: ", __LINE__);
	
	/* 3: Count test						*/
	count_errs += Tester((long)BSTCount(bst), 0, "Count: ", __LINE__);
	
	/* 4: Insert test						*/
	for (i = 0; i < 50; ++i)
	{
		iter = BSTInsert(bst, &data[i]);
		if (!BSTIsBadIterator(iter))
		{
			++count;
		}
	}

	/* 5: IsEmpty test						*/
	count_errs += Tester((long)BSTIsEmpty(bst), 0, "IsEmpty: ", __LINE__);
	
	/* 6: Count test						*/
	count_errs += Tester((long)BSTCount(bst), count, "Count: ", __LINE__);

	/* 7: Foreach->Print test				*/
	BSTForEach(BSTBegin(bst), BSTEnd(bst), MyPrint, NULL);
	puts("");
	
	/* 8: remove test						*/
	data_pop = BSTRemove(iter);
	if (70 != *data_pop)
	{
		printf("function: Remove\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 62,
															 *data_pop);
		++count_errs;
	}
	--count;
	
	/* 9: Count test						*/
	count_errs += Tester((long)BSTCount(bst), count, "Count: ", __LINE__);

	/* 10: Find test						*/
	*data_pop = 98;
	iter = BSTFind(bst, data_pop);
	if (*(int *) BSTGetData(iter) != *data_pop)
	{
		printf("function: find\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 98,
															 *data_pop);
		++count_errs;
	}

	/* 11: Foreach->Print test				*/
	BSTForEach(BSTBegin(bst), BSTEnd(bst), MyPrint, NULL);
	puts("");

	/* 12: remove test						*/
	data_pop = BSTRemove(iter);
	if (98 != *data_pop)
	{
		printf("function: Remove\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 62,
															 *data_pop);
		++count_errs;
	}
	--count;

	/* 13: Foreach->Print test				*/
	BSTForEach(BSTBegin(bst), BSTEnd(bst), MyPrint, NULL);
	puts("");

	/* 14: Find test						*/
	*data_pop = 11;
	iter = BSTFind(bst, data_pop);
	if (*(int *) BSTGetData(iter) != *data_pop)
	{
		printf("function: Find\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 98,
															 *data_pop);
		++count_errs;
	}

	/* 15: remove test						*/
	data_pop = BSTRemove(iter);
	if (11 != *data_pop)
	{
		printf("function: Remove\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 62,
															 *data_pop);
		++count_errs;
	}
	--count;

	/* 16: Foreach->Print test				*/
	BSTForEach(BSTBegin(bst), BSTEnd(bst), MyPrint, NULL);
	puts("");

	/* 17: Find test						*/
	*data_pop = 63;
	iter = BSTFind(bst, data_pop);
	if (*(int *) BSTGetData(iter) != *data_pop)
	{
		printf("function: Find\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 98,
															 *data_pop);
		++count_errs;
	}
	
	/* 18: Prev test						*/
	iter = BSTPrev(iter);

	/* 19: remove test						*/
	data_pop = BSTRemove(iter);
	if (62 != *data_pop)
	{
		printf("function: Remove\t in line: %d\t", __LINE__);
		printf("- status: fail... expected value: %d actual value: %d\n", 62,
															 *data_pop);
		++count_errs;
	}
	--count;

	/* 20: Foreach->Print test + Max		*/
	BSTForEach(BSTBegin(bst), BSTMax(bst), MyPrint, NULL);
	puts("");

	/* 21: Count test						*/
	count_errs += Tester((long)BSTCount(bst), count, "Count: ", __LINE__);

	/* 22: Begin test						*/
	iter = BSTBegin(bst);
	/* 23: Prev test						*/
	iter = BSTPrev(iter);
	
	/* 24: BadIterator test					*/
	if (!BSTIsBadIterator(iter))
	{
		printf("Error, should be bad iterator\n");
		++count_errs;
	}

	/* 25: Destroy test						*/
	BSTDestroy(bst);
	
	return (count_errs);
}

/* Action function for Foreach function to print list */
static int MyPrint(const void *data, const void *param)
{
	printf(" - %d", *(int *) data);
	
	return(0);
}

static int IsEqual(const void *data, const void *data2, void *param)
{
	if (*(int *) data == *(int *) data2)
	{
		return(0);
	}
	else if (*(int *) data > *(int *) data2)
	{
		return(1);
	}
	else
	{
		return(-1);
	}

	return(-54);
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



