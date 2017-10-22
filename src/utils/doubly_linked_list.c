/*****************************************************************************
 * Or Nagar.
 * Doubly linked list library.
 *
 * Functions definition.
 * 19/06/17
 ****************************************************************************/
#include <stdlib.h>					/* malloc()			 */
#include <assert.h>					/* assert()			 */

#include "utils.h"					/* MALLOC_ERROR		 */
#include "doubly_linked_list.h"

static int MyCount(void *data, void *param);

enum 
{
	SUCCESS,
	FAILURE
};

struct dlist_node
{
	void *data;
	dlist_node_t *prev;
	dlist_node_t *next;
};

struct dlist
{
	dlist_node_t head;
	dlist_node_t tail;
};


dlist_t *DlistCreate(void)
{
	dlist_t *dl = NULL;
	
	if (NULL == (dl = malloc(sizeof(dlist_t))))
	{
		MALLOC_ERROR;
		
		return (NULL);
	}
	
	dl->head.next = &dl->tail;
	dl->head.prev = NULL;
	dl->tail.prev = &dl->head;
	dl->tail.next = NULL;
	
	dl->head.data = (void *) DEADBEEF;
	dl->tail.data = (void *) DEADBEEF;
	
	return(dl);
}

void DlistDestroy(dlist_t *dl)
{
	dlist_iter_t next = NULL;
	dlist_iter_t current = NULL;
	
	if (NULL == dl)
	{
		return;
	}
	
	current = next = DlistBegin(dl);
	
	while (DlistEnd(dl) != current)
	{
		next = next->next;
		free(current);
		current = next;
	}
	
	free(dl);
	
	return;
}

size_t DlistCount(const dlist_t *dl)
{
	size_t counter = 0;
	
	if (NULL == dl) 
	{
		return (0);
	}
	
	DlistForeach(DlistBegin(dl), DlistEnd(dl), MyCount, &counter);
	
	return(counter);
}

int DlistIsEmpty(const dlist_t *dl)
{
	assert(dl);
	
	return(dl->head.next == &dl->tail);
}

dlist_iter_t DlistBegin(const dlist_t *dl)
{
	assert(dl);
	
	return(dl->head.next);
}

dlist_iter_t DlistEnd(const dlist_t *dl)
{	
	assert(dl);
	
	return((dlist_iter_t)&dl->tail);
}

dlist_iter_t DlistNext(const dlist_iter_t iter)
{
	assert(iter);
	
	return(iter->next);
}

dlist_iter_t DlistPrev(const dlist_iter_t iter)		
{
	assert(iter);
	
	return(iter->prev);
}

void *DlistGetData(const dlist_iter_t iter)
{
	assert(iter);
	
	return(iter->data);
}

int DlistIsSameIterator(const dlist_iter_t iter1, const dlist_iter_t iter2)
{
	assert(iter1 && iter2);
	
	return(iter1 == iter2);
}

int DlistIsBadIterator(const dlist_t *dl, const dlist_iter_t iter)
{	
	assert(dl);
	
	return(iter == DlistPrev(DlistBegin(dl)) || 
		   iter == DlistEnd(dl) || 
		   iter == NULL);
}

dlist_iter_t DlistInsert(dlist_t *dl, dlist_iter_t where, void *data)
{
	dlist_iter_t iter = NULL;
	
	assert(dl && where);
	
	if (NULL == (iter = malloc(sizeof(dlist_node_t))))
	{
		MALLOC_ERROR;
		
		return(DlistEnd(dl));
	}
	
	iter->data = data;
	
	iter->prev = where->prev;
	iter->next = where;
	
	where->prev->next = iter;
	where->prev = iter;
	
	return (iter);
}

dlist_iter_t DlistErase(dlist_iter_t iter)
{
	dlist_iter_t return_node = NULL;	/* points to next node */
	
	assert(iter);
	
	if (NULL == iter->next || NULL == iter->prev)
	{
		return(iter);
	}
	
	return_node = iter->next;
	
	iter->next->prev = iter->prev;
	iter->prev->next = iter->next;
	
	iter->prev = NULL;
	iter->next = NULL;
	
	free(iter);
	
	return(return_node);
}

dlist_iter_t DlistPushFront(dlist_t *dl, void *data)
{
	assert(dl);

	return(DlistInsert(dl, DlistBegin(dl), data));
}

dlist_iter_t DlistPushBack(dlist_t *dl, void *data)
{
	assert(dl);
	
	return(DlistInsert(dl, DlistEnd(dl), data));
}

void *DlistPopFront(dlist_t *dl)
{
	void *temp_data = NULL;
	
	assert(dl);
	
	temp_data = DlistGetData(DlistBegin(dl));
	
	DlistErase(DlistBegin(dl));
	
	return(temp_data);	
}

void *DlistPopBack(dlist_t *dl)  /* ??? */
{
	dlist_iter_t iter = NULL;
	void *temp_data = NULL;
	
	assert(dl);

	iter = DlistPrev(DlistEnd(dl));
	
	temp_data = iter->data;
	
	DlistErase(iter);
	
	return(temp_data);	
}

void DlistSpliceBefore(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to)
{
	assert(where && from && to);
	
	to = DlistPrev(to);
	
	from->prev->next = to->next;	
	to->next->prev = from->prev;	
											
	from->prev = where->prev;	
	to->next = where;				
	
	where->prev->next = from;
	where->prev = to;
	
	return;
}

int DlistForeach(dlist_iter_t from, dlist_iter_t to,
				 int (*action_func)(void *data, void *param),
				 void *param)
{
	int err_number = 0;

	assert(from && to && action_func);

	while (from != to)
	{
		err_number = action_func(from->data, param);
		if (SUCCESS != err_number)
		{
			return (err_number);
		}
		else
		{
			from = from->next;
		}
	}
	
	return(SUCCESS);
}

dlist_iter_t DlistFind(dlist_t *dl, dlist_iter_t from, dlist_iter_t to,			
					int (*is_equal_func)(const void *data, const void *param),     
					const void *param)
{
	assert(dl && from && to && is_equal_func);
	
	while (from != to)
	{
		if(is_equal_func(from->data, param)) 
		{
			return (from);
		}
		else
		{
			from = from->next;
		}
	}
	
	return(DlistEnd(dl));
}

static int MyCount(void *data, void *param)
{
	++(*(int *)param);
	
	return(SUCCESS);
}
