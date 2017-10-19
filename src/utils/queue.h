/*****************************************************************************
 *  Or Nagar.
 *  Queue library.
 *  Header file - Functions declaration.
 *  18/06/17
 ****************************************************************************/
#ifndef __QUEUE_H__ 
#define __QUEUE_H__ 

typedef struct queue queue_t;

/*
 *	Creates the managment struct.
 * 	Returns pointer to the queue
 * 	NULL if fail.
 */
queue_t *QueueCreate(void);

/*
 *	Removes all nodes and the managment struct.
 * 	Frees all allocated memory.
 */
void QueueDestroy(queue_t *queue);

/*
 *	Returns the queue size.
 */
size_t QueueSize(queue_t *queue);

/*
 *	Returns: 1 if the queue is empty, 
 *			 0 otherwise.
 */
int QueueIsEmpty(queue_t *queue);

/*
 *	Adds the "data" to the given queue's tail.
 * 	Returns: 0 for sucsses
 * 			 Non-zero for fail
 */
int QueueEnqueue(queue_t *queue, void *data);

/*
 *	Removes the data in the queue's head.
 * 	Returns a pointer to the removed data.
 * 	Returns NULL if fail.
 */
void *QueueDequeue(queue_t *queue);

/*
 * 	Returns a pointer to the next data in the queue's head.
 */
void *QueuePeek(const queue_t *queue);

/*
 *	Append "from" queue to the "to" queue
 * 	"queue_t *from" will stay valid but empty
 * 	If not needed user should use "QueueDestroy".
 */
void QueueAppend(queue_t *to, queue_t *from);

#endif		/* __QUEUE_H__ */
