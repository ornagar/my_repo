/*****************************************************************************
 *  Or Nagar.
 *  Circular Buffer library.  
 *  Functions definition.
 *  12/06/17
 ****************************************************************************/
#include <stdlib.h>			/* malloc()										*/
#include <assert.h>			/* assert()										*/
#include <string.h>			/* memcpy()										*/
#include <sys/types.h>		/* ssize_t										*/
#include <errno.h>			/* errno										*/

#include "utils.h"			/* DBG()										*/
#include "circbuf.h"				
#include "circbuf_debug.h"	

#define BUF_FULL_CONST 	(1)	/* The border betwin write and read				*/

struct circbuf 
{
	char *writer; 			/* Dynamic pointer to the writing point 		 */
	char *reader;			/* Dynamic pointer to the reading point 		 */
	char *start;			/* Static pointer to the beginning of the buffer */
	char *end;				/* Static pointer to the end of the buffer		 */
};

/*****************************************************************************/
circbuf_t *CircBufCreate(size_t capacity)
{
	circbuf_t *cb = NULL;
	
	if (!capacity)
	{
		capacity = 100;		/* Default buffer size 		   */
	}
	
	if (NULL == (cb = malloc(sizeof(circbuf_t))))
	{
		MALLOC_ERROR;		/* Prints an error message 		*/
		
		return (NULL);			
	}
	
	/* Adds one to the buffer to allow (write = read - 1) 	*/
	if (NULL == (cb->start = malloc(capacity + BUF_FULL_CONST)))	
	{												
		MALLOC_ERROR;		/* Prints an error message 		*/
		free(cb);
		
		return (NULL);
	}
	
	cb->end = cb->start + capacity + BUF_FULL_CONST;
	cb->reader = cb->writer= cb->start;

	
	return (cb);
}
 

void CircBufDestroy(circbuf_t *cb)
{
	assert(cb);
	
	free(cb->start);
	cb->start = NULL;
	
	free(cb);
	
	return;
}

size_t CircBufFreeSpace(const circbuf_t *cb)
{
	assert(cb);
	
	if (cb->reader > cb->writer)
	{
		return (cb->reader - cb->writer - BUF_FULL_CONST);
	}
	else
	{
		return (cb->end - cb->writer + cb->reader - cb->start - BUF_FULL_CONST);
	}
}

size_t CircBufCapacity(const circbuf_t *cb)
{
	assert(cb);

	return (cb->end - cb->start - BUF_FULL_CONST);
}

int CircBufIsEmpty(const circbuf_t *cb)
{
	assert(cb);	
	
	return (cb->reader == cb->writer);
}

ssize_t CircBufRead(circbuf_t *cb, void *dest, size_t nbytes)
{
	size_t n = MIN(nbytes, (CircBufCapacity(cb) - CircBufFreeSpace(cb)));
	
	size_t first_n = 0;

	assert(cb && dest);
	
	if (CircBufIsEmpty(cb))
	{	
		errno = ENODATA;
	
		return (0);
	}
	
	if (cb->writer < cb->reader)
	{
		first_n = MIN(cb->end - cb->reader, n);
	}
	else
	{
		first_n = n;
	}
	
	memcpy(dest, cb->reader, first_n);			/* copy until n or cb.end */
	dest = (char *) dest + first_n;
	cb->reader += first_n;
	
	if (n > first_n)
	{
		memcpy(dest, cb->start, n - first_n);	/* copy from start to read */
		cb->reader = cb->start + (n - first_n);
	}

	return (n);
}

ssize_t CircBufWrite(circbuf_t *cb, void *src, size_t nbytes)
{
	const size_t n = MIN(nbytes, CircBufFreeSpace(cb));
	size_t first_n = 0;
	
	assert(cb && src);
	
	if (0 == CircBufFreeSpace(cb))
	{	
		errno = EOVERFLOW;
	
		return (0);
	}
	
	if (cb->writer >= cb->reader)				
	{
		first_n = MIN(cb->end - cb->writer, n);
	}
	else
	{
		first_n = n;
	}
	
	memcpy(cb->writer, src, first_n);			/* copy until n or cb.end */
	src = (char *) src + first_n;
	cb->writer += first_n;
	
	if (n > first_n)
	{
		memcpy(cb->start, src, n - first_n);	/* copy until n or cb.end */	
		cb->writer = cb->start + (n - first_n);
	}

	return (n);
}

#ifdef _DEBUG
void CircBufPrint(const circbuf_t *cb)
{
	
	size_t n = CircBufCapacity(cb) - CircBufFreeSpace(cb);
	unsigned char *print_runner = (unsigned char *)cb->reader;
	int i = 1;
	
	assert(cb);

	while (n > 0)
	{
		printf("0x%x ", *print_runner);

		if (0 == i % 8)
		{
			puts("");
		}
		
		++print_runner;
		++i;
		--n;
		
		if (print_runner == (unsigned char *)cb->end)
		{
			print_runner = (unsigned char *)cb->start;
		}
	}
	
	puts("");
	
	return;
}
#endif

