/*******************************************************************************
 *  Or Nagar.
 *  Singly Linked List.  
 *  Functions tests.
 *  12/06/17
 ******************************************************************************/
#include <stdio.h>			/* printf()			*/
#include <stdlib.h>			/* EXIT_SUCCESS		*/

#include "singly_linked_list.h"	

int Tester(long actual_value, long expected_value, char *str, int line);
int TestSinglyList(void);		

int IsEqual(const void *data, const void *param);
int Action(void *data, void *param);
int MyPrint(void *data, void *param);


int main(void)
{
	int err_sum = 0;
	
	err_sum += TestSinglyList();
	
	if (0 == err_sum)
	{
		puts("Singly Linked List TEST SUCCESS!!");
	}
	else
	{
		printf("found %d bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

int TestSinglyList(void)		
{
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12}; 
	int a = 5;
	int b = 8;
	int count_errs = 0;
	
	slist_node_t *head = NULL;
	slist_node_t *head2 = NULL;
	slist_node_t *current = NULL;
	
	/* 1: create test				*/
	slist_node_t *node = SolistCreateNode(&data[0], NULL);
	if (NULL == node)
	{
		printf("function: SListCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	head = node;
	
	/* 2: create test				*/
	node = SolistCreateNode((void *)&data[1], head);
	if (NULL == node)
	{
		printf("function: SListCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	head = node;
	
	/* 3: create test				*/
	node = SolistCreateNode((void *)&data[2], head);
	if (NULL == node)
	{
		printf("function: SListCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	head = node;
	
	/* 4: create test				*/
	node = SolistCreateNode((void *)&data[3], head);
	if (NULL == node)
	{
		printf("function: SListCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	head = node;
	
	/* 5: create test				*/
	node = SolistCreateNode((void *)&data[4], head);
	if (NULL == node)
	{
		printf("function: SListCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	head = node;
	
	/* 6: create test				*/
	node = SolistCreateNode((void *)&data[5], head);
	if (NULL == node)
	{
		printf("function: SListCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	head = node;
		
	/* 8: create test				*/
	node = SolistCreateNode((void *)&data[6], head);
	if (NULL == node)
	{
		printf("function: SListCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	head = node;
	
	/* 9: create test				*/
	node = SolistCreateNode((void *)&data[7], head);
	if (NULL == node)
	{
		printf("function: SListCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	head = node;
	
	/* 10: count test				*/
	count_errs += Tester((long)SolistCountNodes(head), 8, "Count: ", __LINE__);
	
	/* 11: foreach and print test	*/
	SolistForeach(head, MyPrint, &a);
	puts("");

	/* 12: remove after test		*/
	current = SolistRemoveAfter(node);
	if (NULL == current)
	{
		printf("function: SListRemoveAfter\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted removal returned NULL\n");
		++count_errs;
	}
	
	node = node->next->next;
	
	/* 13: insert before			*/
	current = SolistInsertBefore(node, current);
	if (NULL == current)
	{
		printf("function: SolistInsertBefore\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted insertion returned NULL\n");
		++count_errs;
	}
	
	/* 14: foreach and print test	*/
	SolistForeach(head, MyPrint, &a);	
	puts("");
	
	/* 15: remove test				*/
	current = SolistRemove(current);
	if (NULL == current)
	{
		printf("function: SListRemove\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted removal returned NULL\n");
		++count_errs;
	}
	
	/* 16: foreach and print test	*/
	SolistForeach(head, MyPrint, &a);	
	puts("");
	
	/* 17: insert after				*/
	current = SolistInsertAfter(node, current);
	if (NULL == current)
	{
		printf("function: SolistInsertAfter\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted insertion returned NULL\n");
		++count_errs;
	}
	
	/* 18: foreach and print test	*/
	SolistForeach(head, MyPrint, &a);	
	puts("");
	
	/* 19: find	test				*/
	current = SolistFind(head, IsEqual, &a);
	count_errs += Tester(*(int *)current->data, 5, "SolistFind: ", __LINE__);
	current = head;
	
	/* 20: flip test				*/
	head = SolistFlip(head);
	if (NULL == head)
	{
		printf("function: SListFlip\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted Flip returned NULL\n");
		++count_errs;
	}
	
	/* 21: foreach and print test	*/
	SolistForeach(head, MyPrint, &a);	
	puts("");
	
	
	
	/********************* 22: Find Intersection test ************************/
	
	node = SolistCreateNode(&data[11], NULL);
	if (NULL == node)
	{
		printf("function: SListCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	head2 = node;
	
	node = SolistCreateNode(&data[10], head2);
	if (NULL == node)
	{
		printf("function: SListCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	head2 = node;
	
	head2->next->next = head->next->next->next;
	
	node = SolistFindIntersection(head2, head);
	count_errs += Tester(*(int *)node->data, 7, "SolistFindIntersection: ", __LINE__);
	
	head2->next->next = NULL;
	
	/*************************************************************************/
	
	SolistForeach(head, MyPrint, &a);	
	puts("");
	/************************** 23: Has Loop test ****************************/
	
	current = SolistFind(head, IsEqual, &b);
	
	current->next = head->next->next->next;
	
	b = SolistHasLoop(head);
	count_errs += Tester(b, 1, "SolistHasLoop: ", __LINE__);
	
	current->next = NULL;
	/*************************************************************************/
	
	/* 24: free all test			*/
	SolistFreeAll(head);
	SolistFreeAll(head2);
	
	return (count_errs);

}



int IsEqual(const void *data, const void *param)
{
	return (*(int *) data == *(int *) param);
}

int Action(void *data, void *param)
{
	*(int *)data = (*(int*)data) * (*(int*)param);
	
	return(0);
}

int MyPrint(void *data, void *param)
{
	printf(" - %d", *(int *) data);
	return(0);
}
int Tester(long actual_value, long expected_value, char *str, int line)
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

