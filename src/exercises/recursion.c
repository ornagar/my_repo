#include <stdio.h>
#include <stdlib.h>

#include "../utils/stack.h"

typedef struct node
{
	int data;
	struct node *next;
}node_t;


static int Tester(long actual_value, long expected_value, char *str, int line);
static int TestFibo(void);
static int TestStrLen(void);
static int TestStrCmp(void);
static int TestStrCpy(void);


static unsigned int IterFibo(unsigned int n);
static unsigned int RecursiveFibo(unsigned int n);
size_t StrLen(const char *s);
int StrCmp(const char *s1, const char *s2);
char *StrCpy(char *dest, const char *src);
char *StrCat(char *dest, const char *src);
char *StrStr(const char *haystack, const char *needle);
node_t *ListCreate(void);
node_t *IterativeRotate(node_t *head);
node_t *RecursiveRotate(node_t *head);
stack_t *MyStackCreate(void);
void StackSort(stack_t *stack);
static void StackInsert(stack_t *stack, int data);


int main(void)
{
	int err_sum = 0;
	char dest[15] = "hello";
	char *new;
	node_t *head = NULL;
	node_t *current = NULL;
	stack_t *stack = MyStackCreate();
	
	new = StrStr(dest, "ll");
	
	printf("%s\n%s\n", new, dest);
	
	head = ListCreate();
	current = head;
	
	while (NULL != current)
	{
		printf("%d\n", current->data);
		current = current->next;
	}
	
	current = IterativeRotate(head);
	
	while (NULL != current)
	{
		printf("%d\n", current->data);
		current = current->next;
	}
	
	err_sum += TestFibo();
	err_sum += TestStrLen();
	err_sum += TestStrCmp();
	err_sum += TestStrCpy();
	
	if (0 == err_sum)
	{
		puts("Recursion TEST SUCCESS!!");
	}
	else
	{
		printf("found %d bugs in the program\n", err_sum);
	}
	
	StackSort(stack);
	
	while (0 < StackSize(stack))
	{
		printf("peek: %d\n", *(int *) StackPeek(stack));
		StackPop(stack);
	}
	
	return (EXIT_SUCCESS);
}

static unsigned int IterFibo(unsigned int n)
{
	int f[2] = {0, 1};
	int i = 0;
	
	for (i = 2; i < n; ++i)
	{
		f[i & 1] = f[0] + f[1];
	}

	return (f[0] + f[1]);
}

unsigned int RecursiveFibo(unsigned int n)
{
	if (1 >= n)
	{
		return (n);
	}

	return (RecursiveFibo(n - 1) + RecursiveFibo(n - 2));
}

size_t StrLen(const char *s)
{
	size_t count = 0;

	return (('\0' == *s) ? (0) : (++count + StrLen(++s)));
}

int StrCmp(const char *s1, const char *s2)
{
	if (('\0' == *s1) || (*s1 != *s2))
	{
		return (*s1 - *s2);
	}
	
	return (StrCmp(++s1, ++s2));
}

char *StrCpy(char *dest, const char *src)
{
	*dest = *src;
	
	if ('\0' != *src)
	{
		StrCpy(++dest, ++src);
	}
	
	return (--dest);
}

char *StrCat(char *dest, const char *src)
{
	size_t size = 0;
	
	if ('\0' != *src)
	{
		if ('\0' != *dest)
		{
			size = StrLen(dest);
			dest += size;
		}
		
		*dest = *src;
		++dest;
		*dest = '\0';
		StrCat(dest, ++src);
	}
	
	return (dest - (size + 1));
}

char *StrStr(const char *haystack, const char *needle)
{
	if ('\0' == *needle)
	{
		return ((char *)haystack);
	}
	
	if ('\0' == *haystack)
	{
		return (NULL);
	}
	
	if (*needle == *haystack && 
							 StrStr(haystack + 1, needle + 1) == haystack + 1)
	{
		return ((char *)haystack);
	}
	
	return (StrStr(haystack + 1, needle));
}

node_t *ListCreate(void)
{
	node_t *head = (node_t *)malloc(sizeof(node_t));
	head->data = 1;
	head->next = (node_t *)malloc(sizeof(node_t));
	head->next->data = 2;
	head->next->next = (node_t *)malloc(sizeof(node_t));
	head->next->next->data = 3;
	head->next->next->next = (node_t *)malloc(sizeof(node_t));
	head->next->next->next->data = 4;
	head->next->next->next->next = (node_t *)malloc(sizeof(node_t));
	head->next->next->next->next->data = 5;
	head->next->next->next->next->next = (node_t *)malloc(sizeof(node_t));
	head->next->next->next->next->next->data = 6;
	head->next->next->next->next->next->next = NULL;
	
	return (head);
}

node_t *IterativeRotate(node_t *head)
{
	node_t *last = NULL;
	node_t *second = head;
	node_t *first = second->next;
	
	while (NULL != first)
	{
		second->next = last;
		last = second;
		second = first;
		first = first->next;
	}
	
	second->next = last;
	return (second);
}

node_t *RecursiveRotate(node_t *head)
{
	node_t *current = head;
	node_t *next = head->next;
	node_t *new_head = NULL;
	
	if (NULL == next)
	{
		return (head);
	}
	
	new_head = RecursiveRotate(next);
	
	next->next = current;
	
	current->next = NULL;
	
	return (new_head);
}

stack_t *MyStackCreate(void)
{
	stack_t *my_stack = StackCreate(15, sizeof(int));
	int arr[10];
	int i = 0;
	
	for (i = 0; i < 10; ++i)
	{
		arr[i] = rand();
	}
	
	for (i = 0; i < 10; ++i)
	{
		StackPush(my_stack, &arr[i]);
	}
	
	return (my_stack);
}

void StackSort(stack_t *stack)
{
	int temp = *(int *) StackPeek(stack);
	StackPop(stack);
	
	if (0 != StackSize(stack))
	{
		StackSort(stack);
	}
	
	StackInsert(stack, temp);
	
	return;	
}
static void StackInsert(stack_t *stack, int data)
{
	int temp = 0;

	if (0 == StackSize(stack) || data >= *(int *)StackPeek(stack))
	{
		StackPush(stack, &data);
		return;
	}
	
	temp = *(int *)StackPeek(stack);
	StackPop(stack);
	StackInsert(stack, data);
	StackPush(stack, &temp);
	
	return;
}

/********************************TESTERS***************************************/
static int TestFibo(void)
{
	size_t count_errs = 0;
	
	count_errs += Tester(RecursiveFibo(1), 1, "Test RecursiveFibo2: ", __LINE__);
	count_errs += Tester(IterFibo(1), 1, "Test IterFibo2: ", __LINE__);
	
	count_errs += Tester(RecursiveFibo(10), 55, "Test RecursiveFibo3: ", __LINE__);
	count_errs += Tester(IterFibo(10), 55, "Test IterFibo3: ", __LINE__);
	
	return (count_errs);
}

static int TestStrLen(void)
{
	size_t count_errs = 0;
	
	count_errs += Tester(StrLen("a"), 1, "Test StrLen1: ", __LINE__);
	
	count_errs += Tester(StrLen(""), 0, "Test StrLen2: ", __LINE__);
	
	count_errs += Tester(StrLen("hello world"), 11, "Test StrLen1: ", __LINE__);
	
	return (count_errs);
}

static int TestStrCmp(void)
{
	size_t count_errs = 0;
	
	count_errs += Tester(StrCmp("abc", "abc"), 0, "Test StrCmp1: ", __LINE__);
	
	count_errs += Tester(StrCmp("ab", "abc"), -99, "Test StrCmp2: ", __LINE__);
	
	count_errs += Tester(StrCmp("hello world", "helko world"), 1, "Test StrCmp3: ", __LINE__);
	
	return (count_errs);
}

static int TestStrCpy(void)
{
	size_t count_errs = 0;
	char dest[15];
	char *new;
	
	new = StrCpy(dest, "hello");
	count_errs += Tester(StrCmp(new, "hello"), 0, "Test StrCpy1: ", __LINE__);
	
	new = StrCpy(dest, "");
	count_errs += Tester(StrCmp(new, ""), 0, "Test StrCpy2: ", __LINE__);
	
	new = StrCpy(dest, "hi my name is");
	count_errs += Tester(StrCmp(new, "hi my name is"), 0, "Test StrCpy3: ", __LINE__);
	
	return (count_errs);
}

static int Tester(long actual_value, long expected_value, char *str, int line)
{	
	if (actual_value != expected_value)
	{
		printf("function: %s  in line: %d ", str, line);
		printf("- status: fail... expected value was %ld and actual\
		 value is %ld\n",
				expected_value, actual_value);
		puts("");
				
		return (1);
	}
	
	return (0);
}

/******************************************************************************/

