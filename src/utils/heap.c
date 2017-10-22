/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Heap                                   #################################
 *                                         ##########    ####       ########
 *  Functions definition                   ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  02-08-2017                             ##########    ####  ###  ######## 
 *  14:30:43                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <assert.h>					 /* assert()					  */
#include <string.h>					 /* memcpy()					  */

#include "heap.h"					 /* all functions declerations	  */
#include "heapify.h"				 /* HeapifyUp()					  */
#include "d_vector.h"				 /* DvecCreate()				  */
#include "utils.h"					 /* Or's functions                */

static void Swap(void *data1, void *data2, size_t element_size);

enum
{
	SUCCESS,
	FAIL
};

/*
 * Management struct for heap DS.
 */
struct heap
{
	dyn_vec_t *d_vec;
	size_t element_size;
	int (*is_before) (const void *data1, 
					  const void *data2, 
					  void *param);
	void *param;
};

heap_t *HeapCreate(size_t element_size, int (*is_before)(const void *data1, 
								   const void *data2, void *param), void *param)
{
	heap_t *hp = NULL;
	
	assert(is_before);
	
	if (NULL == (hp = (heap_t *)malloc(sizeof(heap_t))))
	{
		PRINT_ERROR("malloc error");
		return (NULL);
	}
	
	if (NULL == (hp->d_vec = DynVecCreate(64, element_size)))
	{
		PRINT_ERROR("DynVecCreate error");
		free(hp);
		return(NULL);
	}
	
	hp->element_size = element_size;
	hp->is_before = is_before;
	hp->param = param;
	
	return(hp);
}

void HeapDestroy(heap_t *hp)
{
	if (NULL == hp)
	{
		return;
	}
	
	DynVecDestroy(hp->d_vec);
	hp->d_vec = NULL;
	hp->is_before = NULL;
	hp->param = NULL;
	free(hp);
	
	return;
}

void HeapPop(heap_t *hp)
{
	void *head = NULL;
	void *tail = NULL;
	
	assert(hp);
	
	if (0 == HeapSize(hp))
	{
		return;
	}
	
	head = DynVecGetItemAddres(hp->d_vec, 0);
	tail = DynVecGetItemAddres(hp->d_vec, DynVecSize(hp->d_vec) - 1);
	
	Swap(head, tail, hp->element_size);
	
	DynVecPopBack(hp->d_vec);
	
	HeapifyDown(head, DynVecSize(hp->d_vec), hp->element_size, 0,
													 hp->is_before, hp->param);
	return;
}

int HeapPush(heap_t *hp, void *data)
{
	assert(hp);
	
	if (0 != DynVecPushBack(hp->d_vec, data))
	{
		PRINT_ERROR("DynVecPushBack error");
		return (1);
	}
	
	HeapifyUp(DynVecGetItemAddres(hp->d_vec, 0), DynVecSize(hp->d_vec), 
	  hp->element_size, DynVecSize(hp->d_vec) - 1, hp->is_before, hp->param);
					  
	return (0);
}

void *HeapTop(heap_t *hp)
{
	assert(hp);
	
	return (DynVecGetItemAddres(hp->d_vec, 0));
}

int HeapRemove(heap_t *hp, void *data, void *to_remove,
						int (*cmp_func)(const void *data1, const void *data2))
{
	void *begin  = NULL;
	void *runner = NULL;
	void *last 	 = NULL;
	size_t size;
	int i = 0;
	
	assert(hp && data && cmp_func);
	
	size = DynVecSize(hp->d_vec);
	begin = DynVecGetItemAddres(hp->d_vec, 0);
	
	while (i < size)
	{
		runner = DynVecGetItemAddres(hp->d_vec, i);
		if (0 == cmp_func(runner, data))
		{
			last = DynVecGetItemAddres(hp->d_vec, DynVecSize(hp->d_vec) - 1);
			
			Swap(runner, last, hp->element_size);
			
			if (NULL != to_remove)
			{
				memcpy(to_remove, DynVecGetItemAddres(hp->d_vec, size - 1), 
															  hp->element_size);
			}														 
			DynVecPopBack(hp->d_vec);
			
			HeapifyUp(begin, size, hp->element_size, i, hp->is_before, 
																	 hp->param);
			HeapifyDown(begin, size, hp->element_size, i, hp->is_before, 
																	 hp->param);
			
			return (0);
		}
		++i;
	}
	
	return (1);
}

size_t HeapSize(heap_t *hp)
{
	assert(hp);
	
	return (DynVecSize(hp->d_vec));
}

size_t HeapCapacity(heap_t *hp)
{
	assert(hp);
	
	return(DynVecCapacity(hp->d_vec));
}


static void Swap(void *data1, void *data2, size_t element_size)
{
	char temp = 0;
	char *a = data1;
	char *b = data2;
	
	while (element_size--)
	{
		temp = *a;
		*a = *b;
		*b = temp;
		++a;
		++b;
	}
	
	return;
}
