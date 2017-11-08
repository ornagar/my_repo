/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Rtree                                  #################################
 *                                         ##########    ####       ########
 *  Tester                                 ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  26-07-2017                             ##########    ####  ###  ######## 
 *  11:33:14                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <time.h>

#include "rtree.h"					 /* all functions declerations	  */
#include "utils.h"					 /* Or's functions                */

static int MyCompar(const void *data1, const void *data2);
/*static int ActionPrint(void *data, void *arg);
*/
static int TestRTree(void);

int main(void)
{
	size_t err_sum = 0;

	err_sum = TestRTree();

	if (0 == err_sum)
	{
		puts("\nAVL TREE TEST SUCCESS!!\n");
	}
	else
	{
		printf("\nfound %lu bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

static int TestRTree(void)
{
	rtree_t *tree = RTreeCreate(MyCompar);
	int arr[5000];
	int i = 0; 
	int b = 3250;
	int count_errs = 0;
	
	TEST(0 == RTreeSize(tree), "size test", count_errs);
	
	TEST(1 == RTreeIsEmpty(tree), "is empty test", count_errs);
	
	srand(clock());
	for (i = 0; i < 5000; ++i)
	{
		arr[i] = rand();
	}
	
	TEST(0 == RTreeInsert(tree, &b), "insert test", count_errs);
	TEST(2 == RTreeInsert(tree, &b), "insert test", count_errs);
	
	for (i = 0; i < 5000; ++i)
	{
		RTreeInsert(tree, &arr[i]);
	}
	
	TEST(0 == RTreeIsEmpty(tree), "is empty test", count_errs);
	
	TEST(NULL != RTreeFind(tree, &b), "find test", count_errs);
	
	TEST(5001 == RTreeSize(tree), "size test", count_errs);
	
	RTreeRemove(tree, &b);
	
	TEST(5000 == RTreeSize(tree), "size test", count_errs);
	
	TEST(18 >= RTreeHeight(tree), "size test", count_errs);
	
	TEST(NULL == RTreeFind(tree, &b), "find test", count_errs);

	/*printf ("%d\n", RTreeForEach(tree, ActionPrint, NULL));
*/
	RTreeDestroy(tree);
	
	return (count_errs);
}

static int MyCompar(const void *data1, const void *data2)
{
	if (*(int *)data1 == *(int *)data2)
	{
		return (0);
	}
	return ((*(int *)data1 > *(int *)data2) ? 1 : -1);
}

/*static int ActionPrint(void *data, void *arg)
{
	if (3250 == *(int *)data)
	{
		return (1);
	}
	
	printf("%d\n", *(int *)data);
	
	return (0);
}

*/
