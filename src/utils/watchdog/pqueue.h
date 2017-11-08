/*******************************************************************************
 * pqueue.h
 * Implementation of Priority Queue
 * Infinity Labs R&D
 * RD33
 * Priority queue API
 * Thu Jun 22 15:02:03 2017
 ******************************************************************************/
#ifndef __PQUEUE_H__
#define __PQUEUE_H__

#include <stdlib.h>

typedef struct pqueue pqueue_t;

/* Create a priority queue.
 *  is_before is a function for determining order
 *  param is optional
 * returns NULL on failure.
 */
pqueue_t *PqueueCreate(
        int (*is_before)(const void *data1, const void *data2, void *param), 
        void *param);

/* Destroy a priority queue
 */
void PqueueDestroy(pqueue_t *pq);

/* Query a priority queue for its number of elements
 * returns the size.
 */
size_t PqueueSize(const pqueue_t *pq);

/* Query a priority queue
 * returns whether the queue is empty (1) / non-empty (0)
 */
int PqueueIsEmpty(const pqueue_t *pq);

/* Add data to a priority queue 
 * returns 1 on failure.
 */
int PqueueEnqueue(pqueue_t *pq, void *data);

/* Remove the element with the highest priority
 * from a priority queue
 */
int PqueueDequeue(pqueue_t *pq);

/* Return the data with the highest priority 
 * from a priority queue
 */
void *PqueuePeek(const pqueue_t *pq);

/* 
 * Find and remove the data in a priority queue
 */
void *PqueueRemove(pqueue_t *pq, 
                int (*is_equal_func)(const void *data, const void *param), 
                void *param);

/* Clear a priority queue (empty)
 */
void PqueueClear(pqueue_t *pq);

#endif /* __PQUEUE_H__ */
