/*******************************************************************************
 * pqueue.h
 * Implementation of Priority Queue
 * Infinity Labs R&D
 * RD33
 * Priority queue API, based on a Heap.
 * Thu Jun 22 15:02:03 2017
 ******************************************************************************/
#include <stdlib.h>				/* malloc()			*/
#include <assert.h>				/* assert()			*/

#include "heap.h"				/* HeapCreate()	*/
#include "utils.h"
#include "pqueue.h"

/*
 * Wrapper for users is before function
 */
typedef struct
{
	int (*is_before)(const void *data1, const void *data2, void *param);
	void *param;
}wraper_t;

/*
 * Wrapper for users compare function
 */
typedef struct
{
	int (*cmp_func)(const void *data1, const void *param);
	void *param;
}cmp_t;

/*
 * Management structure for priority queue
 */
struct pqueue
{
    heap_t *hp;
    wraper_t *wraper;
};

/**********************************STATIC FUNCTIONS****************************/
static int MyIsBefore(const void *data1, const void *data2, void *param);
static int MyCmp(const void *data, const void *param);
/******************************************************************************/

pqueue_t *PqueueCreate(int (*is_before)(const void *data1, const void *data2, 
													  void *param), void *param)
{
	pqueue_t *pq = NULL;
	
	assert(is_before);
	
	if (NULL == (pq = malloc(sizeof(pqueue_t))))
	{
		PRINT_ERROR("malloc error");
		return(NULL);
	}
	if (NULL == (pq->wraper = (wraper_t *)malloc(sizeof(wraper_t))))
	{
		PRINT_ERROR("malloc error");
		free(pq);
		return (NULL);
	}
	
	pq->wraper->is_before = is_before;
	pq->wraper->param = param;
	if (NULL == (pq->hp = HeapCreate(sizeof(void *), MyIsBefore, pq->wraper)))
	{
		PRINT_ERROR("HeapCreate error");
		free(pq->wraper );
		free(pq);
		return(NULL);
	}
	
	return(pq);
}

void PqueueDestroy(pqueue_t *pq)
{
	if (NULL == pq)
	{
		return;
	}
	
	HeapDestroy(pq->hp);
	pq->hp = NULL;
	free(pq->wraper);
	pq->wraper = NULL;
	free(pq);
	
	return;
}

size_t PqueueSize(const pqueue_t *pq)
{
	assert(pq);
	
	return(HeapSize(pq->hp));
}

int PqueueIsEmpty(const pqueue_t *pq)
{
	assert(pq);
	
	return(0 == HeapSize(pq->hp));
}

int PqueueEnqueue(pqueue_t *pq, void *data)
{
	assert(pq && data);
	
	
	if(0 != HeapPush(pq->hp, &data))
	{
		PRINT_ERROR("HeapPush error");
		return(1);
	}
	
	return(0);
}

int PqueueDequeue(pqueue_t *pq)
{
	assert(pq);
		
	if (PqueueIsEmpty(pq))
	{
		return (1);
	}
	
	HeapPop(pq->hp);
	
	return(0);		
}

void *PqueuePeek(const pqueue_t *pq)
{
	if (PqueueIsEmpty(pq))
	{
		return (NULL);
	}
	
	return(*(void **)HeapTop(pq->hp));
}

void *PqueueRemove(pqueue_t *pq, 
                int (*is_equal_func)(const void *data, const void *param), 
                void *param)
{
	cmp_t cmp = {0};
	void *buf = NULL;
	assert(pq && is_equal_func);

	cmp.param = param;
	cmp.cmp_func = is_equal_func;
	
	if (0 != (HeapRemove(pq->hp, &cmp, &buf, MyCmp)))
	{
		return (NULL);
	}
	
	return (buf);
}

void PqueueClear(pqueue_t *pq)
{
	assert(pq);
	
	while (!PqueueIsEmpty(pq))
	{
		PqueueDequeue(pq);
	}

	return;
}

/***********************************STATIC FUNCTIONS***************************/

static int MyIsBefore(const void *data1, const void *data2, void *param)
{
	wraper_t *wraper = param;
	
	return (wraper->is_before(*(void **)data1, *(void **)data2, wraper->param));
}

static int MyCmp(const void *data, const void *param)
{
	cmp_t *cmp = (cmp_t *)param;
	
	return (!cmp->cmp_func(*(void **)data, cmp->param));
}
