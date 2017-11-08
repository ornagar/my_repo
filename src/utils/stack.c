/*******************************************************************************
 *  Or Nagar.
 *  Stack library.
 *  Tester.
 *  07/06/17
 ******************************************************************************/
#include <stdlib.h>				/* malloc()			*/
#include <assert.h>				/* assert()			*/
#include <string.h>				/* memcpy()			*/

#include "utils.h"				/* DBG()			*/
#include "stack.h"				/* This header file */

struct stack
{
	void *current;
	void *end;
	size_t element_size;
	size_t head[1];
};

/* 			
 * Use malloc() to allocate sizeof(struct - struct->head +capacity * size) 
 * to the stack.
 */
stack_t *StackCreate(size_t capacity, size_t element_size)
{
	stack_t *stack = NULL;
	
	
	if (NULL == (stack = malloc((sizeof(stack_t) + capacity *
					element_size) - sizeof(size_t))))
	{
		MALLOC_ERROR;
		return (NULL);
	}
	
	stack->element_size = element_size;
	stack->current = &stack->head;
	stack->end = (char*)stack->current + (capacity * element_size);
	
	return (stack);
}

void StackDestroy(stack_t *st)
{
	assert(st);
	
	free(st);
	st = NULL;
	
	return;
}

/* 			
 * Updates the data of the stack's top and grous the size
 */
int StackPush(stack_t *st, void *data)
{
	assert(st);
	assert(data);
	
	if ((char*)st->current < (char*)st->end)
	{
		memcpy(st->current, data, st->element_size);
		st->current = (char*)st->current + st->element_size;
		
		return (0);
	}
	else
	{
		DBG(puts("stack overflow"));
		
		return (1);
	} 	
}

int StackPop(stack_t *st)
{
	assert(st);
	
	if ((void*)st->current > (void*)st->head)
	{
		st->current = (char*)st->current - st->element_size;

		return (0);
	}
	else
	{
		DBG(puts("stack underflow"));
		
		return (1);
	}
}

const void *StackPeek(const stack_t *st)
{
	assert(st);
	
	if ((void*)st->current > (void*)st->head)
	{
		return ((char*)st->current - st->element_size);
	}
	else
	{
		return (NULL);
	}
}

size_t StackSize(const stack_t *st)
{
	assert(st);
	
	return (((char*)st->current - (char*)st->head) / st->element_size);
}

size_t StackCapacity(const stack_t *st)
{
	assert(st);
	
	return (((char*)st->end - (char*)st->head) / st->element_size);
}
