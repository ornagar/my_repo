/*******************************************************************************
 *  Or Nagar.
 *  Stack library.  
 *  Functions definitions.
 *  07/06/17
 ******************************************************************************/
#include <stdio.h>			/* printf()			*/
#include <stdlib.h>			/* EXIT_SUCCESS		*/

#include "utils.h"			/* DBG() 			*/
#include "stack.h"			/* StackPop()		*/

static void Tester(long return_value, long wanted_value, char *str);

void TestStackInteger(void);
void TestStackString(void);
void TestStackLong(void);
void TestStackChar(void);

int main(void)
{
	TestStackInteger();
	
	TestStackLong();
	
	TestStackChar();
	
	TestStackString();
	
	return (EXIT_SUCCESS);
}

void TestStackInteger(void)
{

	int a = 1;
	const int *ptr = NULL;
	stack_t *st = StackCreate(4, 4);
	
	if (NULL != st)
	{
		puts("StackCreate - Success!!");
	}
	else
	{
		puts("fail... wanted creation returned NULL\n");
	}
	
	Tester((long)StackPush(st, &a), (long) 0, "push test: ");
	ptr = StackPeek(st);
	Tester(*(int*)ptr, (long) 1, "peek test: ");
	++a;
	Tester((long)StackSize(st), (long) 1, "Size: ");
	Tester((long)StackPush(st, &a), (long) 0, "push test: ");
	ptr = StackPeek(st);
	Tester(*(int*)ptr, (long) 2, "peek test: ");
	++a;
	
	Tester((long)StackPush(st, &a), (long) 0, "push test: ");
	ptr = StackPeek(st);
	Tester(*(int*)ptr, (long) 3, "peek test: ");
	++a;
	
	Tester((long)StackPush(st, &a), (long) 0, "push test: ");
	ptr = StackPeek(st);
	Tester(*(int*)ptr, (long) 4, "peek test: ");
	++a;
	
	Tester((long)StackPush(st, &a), (long) 1, "push test: ");
	ptr = StackPeek(st);
	Tester(*(int*)ptr, (long) 4, "peek test: ");
	Tester((long)StackSize(st), (long) 4, "Size: ");
	
	Tester((long)StackPop(st), (long) 0, "pop test: ");
	
	Tester((long)StackPop(st), (long) 0, "pop test: ");
	
	Tester((long)StackPop(st), (long) 0, "pop test: ");
	
	Tester((long)StackPop(st), (long) 0, "pop test: ");
	
	Tester((long)StackPop(st), (long) 1, "pop test: ");
	
	
	Tester((long)StackCapacity(st), (long) 4, "Capacity: ");
	Tester((long)StackSize(st), (long) 0, "Size: ");
	
	StackDestroy(st);
}

void TestStackLong(void)
{

	long a = 1;
	const int *ptr = NULL;
	stack_t *st = StackCreate(4, 8);
	
	if (NULL != st)
	{
		puts("StackCreate - Success!!");
	}
	else
	{
		puts("fail... wanted creation returned NULL\n");
	}
	
	Tester((long)StackPush(st, &a), (long) 0, "push test: ");
	ptr = StackPeek(st);
	Tester(*(int*)ptr, (long) 1, "peek test: ");
	++a;
	Tester((long)StackSize(st), (long) 1, "Size: ");
	Tester((long)StackPush(st, &a), (long) 0, "push test: ");
	ptr = StackPeek(st);
	Tester(*(int*)ptr, (long) 2, "peek test: ");
	++a;
	
	Tester((long)StackPush(st, &a), (long) 0, "push test: ");
	ptr = StackPeek(st);
	Tester(*(int*)ptr, (long) 3, "peek test: ");
	++a;
	
	Tester((long)StackPush(st, &a), (long) 0, "push test: ");
	ptr = StackPeek(st);
	Tester(*(int*)ptr, (long) 4, "peek test: ");
	++a;
	
	Tester((long)StackPush(st, &a), (long) 1, "push test: ");
	ptr = StackPeek(st);
	Tester(*(int*)ptr, (long) 4, "peek test: ");
	Tester((long)StackSize(st), (long) 4, "Size: ");
	
	Tester((long)StackPop(st), (long) 0, "pop test: ");
	
	Tester((long)StackPop(st), (long) 0, "pop test: ");
	
	Tester((long)StackPop(st), (long) 0, "pop test: ");
	
	Tester((long)StackPop(st), (long) 0, "pop test: ");
	
	Tester((long)StackPop(st), (long) 1, "pop test: ");
	
	
	Tester((long)StackCapacity(st), (long) 4, "Capacity: ");
	Tester((long)StackSize(st), (long) 0, "Size: ");
	
	StackDestroy(st);
}

void TestStackChar(void)
{

	unsigned char a = 1;
	const char *ptr = NULL;
	stack_t *st = StackCreate(4, 1);
	
	if (NULL != st)
	{
		puts("StackCreate - Success!!");
	}
	else
	{
		puts("fail... wanted creation returned NULL\n");
	}
	
	Tester((long)StackPush(st, &a), (long) 0, "push test: ");
	ptr = StackPeek(st);
	Tester(*ptr, (long) 1, "peek test: ");
	++a;
	printf("%d\n", a);
	Tester((long)StackSize(st), (long) 1, "Size: ");
	Tester((long)StackPush(st, &a), (long) 0, "push test: ");
	ptr = StackPeek(st);
	Tester(*ptr, (long) 2, "peek test: ");
	++a;
	
	Tester((long)StackPush(st, &a), (long) 0, "push test: ");
	ptr = StackPeek(st);
	Tester(*ptr, (long) 3, "peek test: ");
	++a;
	
	Tester((long)StackPush(st, &a), (long) 0, "push test: ");
	ptr = StackPeek(st);
	Tester(*ptr, (long) 4, "peek test: ");
	++a;
	
	Tester((long)StackPush(st, &a), (long) 1, "push test: ");
	ptr = StackPeek(st);
	Tester(*ptr, (long) 4, "peek test: ");
	Tester((long)StackSize(st), (long) 4, "Size: ");
	
	Tester((long)StackPop(st), (long) 0, "pop test: ");
	
	Tester((long)StackPop(st), (long) 0, "pop test: ");
	
	Tester((long)StackPop(st), (long) 0, "pop test: ");
	
	Tester((long)StackPop(st), (long) 0, "pop test: ");
	
	Tester((long)StackPop(st), (long) 1, "pop test: ");
	
	
	Tester((long)StackCapacity(st), (long) 4, "Capacity: ");
	Tester((long)StackSize(st), (long) 0, "Size: ");
	
	StackDestroy(st);
}

void TestStackString(void)
{

	const char *ptr = NULL;
	stack_t *st = StackCreate(4, 23);
	
	if (NULL != st)
	{
		puts("StackCreate - Success!!");
	}
	else
	{
		puts("fail... wanted creation returned NULL\n");
	}
	StackPush(st, "String test 1 success");
	ptr = StackPeek(st);
	printf("%s\n", ptr);
	StackPush(st, "String test 2 success");
	ptr = StackPeek(st);
	printf("%s\n", ptr);
	
	StackDestroy(st);
}

static void Tester(long return_value, long wanted_value, char *str)
{	
	if (return_value == wanted_value)
	{
		printf("%s ", str);
		puts("Success!!");
	}
	else
	{
		printf("%s: ", str);
		printf("fail... wanted value was 0x%lx and return value is 0x%lx\n",
				wanted_value, return_value);
	}
}
