/*******************************************************************************
 *  Author: Or Nagar.
 *  Creation date: 21.06.17
 *  Last modified: 22.06.17
 *  Building Sorted Linked List.
 *  Functions definition, C. file.
 ******************************************************************************/
#include <stdlib.h>					/* malloc()			*/
#include <assert.h>					/* assert()			*/

#include "utils.h"					/* MALLOC_ERROR		*/
#include "doubly_linked_list.h"		/* DlistEnd()		*/
#include "sorted_list.h"

struct sorted_list
{
	dlist_t *dl;
	int (*is_before) (const void *data1, 
					  const void *data2, void *param);
	void *param;
};

sorted_list_t *SlistCreate(
		int (*is_before)(const void *data1, const void *data2, void *param), 
		void *param)
{
	sorted_list_t *sl = NULL;
	
	assert(is_before);
	
	if (NULL == (sl = malloc(sizeof(sorted_list_t))))
	{
		MALLOC_ERROR;
		
		return(NULL);
	}
	
	if (NULL == (sl->dl = DlistCreate()))
	{
		MALLOC_ERROR;
		
		free(sl);
		
		return(NULL);
	}
	
	sl->is_before = is_before;
	sl->param = param;
	
	return(sl);
}

void SlistDestroy(sorted_list_t *sl)
{
	assert(sl && sl->dl);
	
	DlistDestroy(sl->dl);
	
	sl->dl = NULL;
	
	free(sl);
	
	return;
}

size_t SlistSize(const sorted_list_t *sl)
{
	assert(sl && sl->dl);
	
	return(DlistCount(sl->dl));
}

int SlistIsEmpty(const sorted_list_t *sl)
{
	assert(sl && sl->dl);
	
	return(DlistIsEmpty(sl->dl));
}

sorted_list_iter_t SlistBegin(const sorted_list_t *sl)
{
	sorted_list_iter_t iter = {NULL};

	assert(sl && sl->dl);

	iter.iter = DlistBegin(sl->dl);
	
	return(iter);
}

sorted_list_iter_t SlistEnd(const sorted_list_t *sl)
{
	sorted_list_iter_t iter = {NULL};

	assert(sl && sl->dl);

	iter.iter = DlistEnd(sl->dl);
	
	return(iter);
}

sorted_list_iter_t SlistPrev(const sorted_list_iter_t iterator)
{
	sorted_list_iter_t iter = {NULL};
	
	assert(iterator.iter);
	
	iter.iter = DlistPrev(iterator.iter);
	
	return(iter);
}

sorted_list_iter_t SlistNext(const sorted_list_iter_t iterator)
{
	sorted_list_iter_t iter = {NULL};
	
	assert(iterator.iter);
	
	iter.iter = DlistNext(iterator.iter);
	
	return(iter);
}

void *SlistGetData(const sorted_list_iter_t iterator)
{
	assert(iterator.iter);
	
	return(DlistGetData(iterator.iter));
}

int SlistIsSameIterator(const sorted_list_iter_t iterator1,
                        const sorted_list_iter_t iterator2)
{
	assert(iterator1.iter && iterator2.iter);
	
	return(iterator1.iter == iterator2.iter);
}

int SlistIsBadIterator(const sorted_list_t *sl, const sorted_list_iter_t iter)
{
	assert(sl && iter.iter);
	
	return(DlistIsBadIterator(sl->dl, iter.iter));
}

sorted_list_iter_t SlistInsert(sorted_list_t *sl, const void *data)
{
	sorted_list_iter_t iter;
	sorted_list_iter_t end;
	
	assert(sl && data && sl->dl && sl->is_before);
	
	end = SlistEnd(sl);
	
	for (iter = SlistBegin(sl); 
		iter.iter != end.iter && !sl->is_before(data, SlistGetData(iter), NULL);
	 	iter = SlistNext(iter));
	
	iter.iter = DlistInsert(sl->dl, iter.iter, (void *)data);
	if (NULL == iter.iter)
	{
		iter = SlistEnd(sl);
		return(iter);
	}
	
	return(iter);
}

sorted_list_iter_t SlistRemove(sorted_list_iter_t iterator)
{
	sorted_list_iter_t iter;
	
	assert(iterator.iter);
	
	iter.iter = DlistErase(iterator.iter);
	
	return(iter);
}

void *SlistPopFront(sorted_list_t *sl)
{
	assert(sl);
	
	return(DlistPopFront(sl->dl));
}

void *SlistPopBack(sorted_list_t *sl)
{
	assert(sl);
	
	return(DlistPopBack(sl->dl));
}

void SlistMerge(sorted_list_t *dest, sorted_list_t *src)
{
	sorted_list_iter_t iter_dest;
	sorted_list_iter_t iter_src;
	sorted_list_iter_t end_dest;
	sorted_list_iter_t end_src;
	
	assert(dest && src);
	
	iter_dest = SlistBegin(dest);
	iter_src = SlistBegin(src);
	end_dest = SlistEnd(dest);
	end_src = SlistEnd(src);
	
	while (!SlistIsEmpty(src))
	{
		/* Moves dest iterator to the correct place 							*/
		while (iter_dest.iter != end_dest.iter && 
		(!dest->is_before(SlistGetData(iter_src), SlistGetData(iter_dest),
		 dest->param)))
		{
			iter_dest = SlistNext(iter_dest);
		}	
		
		
		if (iter_dest.iter == end_dest.iter)
		{
			iter_src = end_src;
		}
		
		/* Moves source iterator to the correct place 						*/
		while (iter_src.iter != end_src.iter && 
		(dest->is_before(SlistGetData(iter_src), SlistGetData(iter_dest), 
		 dest->param)))
		{
			iter_src = SlistNext(iter_src);
		}
		
		DlistSpliceBefore(iter_dest.iter, SlistBegin(src).iter, iter_src.iter);
	}
}

int SlistForEach(sorted_list_iter_t from, sorted_list_iter_t to,
                    int (*action_func)(void *data, void *param), void *param)
{
	assert(from.iter && to.iter && action_func);
	
	return(DlistForeach(from.iter, to.iter, action_func, param));
}

sorted_list_iter_t SlistFind(const sorted_list_t *sl, 
			sorted_list_iter_t from, sorted_list_iter_t to,
 			int (*is_equal_func)(const void *data,const void *param), 
 			void *param)
{
	sorted_list_iter_t iter;
	
	assert(sl && from.iter && to.iter && is_equal_func);
	
	iter.iter = DlistFind(sl->dl, from.iter, to.iter, is_equal_func, param);
	
	return(iter);
}
