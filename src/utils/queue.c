/*****************************************************************************
 * Or Nagar.
 * Queue library.
 * The queue is based on a singly linked list, where the data
 * is entred into a node in the tail of the list and dequeued 
 * from the list's head.
 * Functions definition.
 * 18/06/17
 ****************************************************************************/
#include <stdlib.h>					/* malloc()			 */
#include <assert.h>					/* assert()			 */

#include "utils.h"					/* MALLOC_ERROR		 */
#include "singly_linked_list.h"		/* SolistCreateNode() */
#include "queue.h"

struct queue
{
	slist_node_t *head;
	slist_node_t *tail;
};

queue_t *QueueCreate(void)
{
	queue_t *queue = malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		MALLOC_ERROR;	/* Prints an error message to stderr */
		
		return(NULL);
	}
	
	if (NULL ==(queue->head = SolistCreateNode(NULL, NULL)))
	{
		MALLOC_ERROR;	/* Prints an error message to stderr */
		free(queue);
		
		return(NULL);
	}
	
	queue->tail = queue->head;
	
	return(queue);
}

void QueueDestroy(queue_t *queue)
{
	assert(queue);

	SolistFreeAll(queue->head);
	queue->head = queue->tail = NULL;
	
	free(queue);
	
	return;
}

size_t QueueSize(queue_t *queue)
{
	assert(queue);
	
	return(SolistCountNodes(queue->head->next));
}

int QueueIsEmpty(queue_t *queue)
{
	assert(queue);
	
	return(queue->tail == queue->head);
}

int QueueEnqueue(queue_t *queue, void *data)
{
	slist_node_t *temp;
	
	assert(queue);
	
	if (NULL ==(temp = SolistCreateNode(data, NULL)))
	{
		MALLOC_ERROR;	/* Prints an error message to stderr */
		
		return(1);
	}
	
	queue->tail->next = temp;
	queue->tail = temp;

	return (0);
}

void *QueueDequeue(queue_t *queue)
{
	void *temp_data = NULL;
	slist_node_t *temp_node = NULL;
	
	assert(queue);
	
	if (QueueIsEmpty(queue))
	{
		return(NULL);
	}	
		
	temp_data = queue->head->next->data;
	temp_node = SolistRemoveAfter(queue->head);
	
	if (NULL == queue->head->next) 
	{
	 	queue->tail = queue->head;
	}
	
	free(temp_node);

	return(temp_data);
}

void *QueuePeek(const queue_t *queue)
{
	assert(queue);
	
	if (queue->tail == queue->head)
	{
		return(NULL);
	}
	
	return(queue->head->next->data);
}

void QueueAppend(queue_t *to, queue_t *from)
{
	assert(from && to);
	
	if (NULL == from)
	{
		return;
	}
	
	to->tail->next = from->head->next;
	to->tail = from->tail;
	
	from->tail = from->head;
	
	from->tail->next = NULL;
	
	return;
}

 
