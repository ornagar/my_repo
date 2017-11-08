/*******************************************************************************
 * Or Nagar.
 * Circular Buffer.  
 * Functions decleration.
 * 12.6.17
 * Functions: CircBufCreate, CircBufDestroy, CircBufFreeSpace,
 * CircBufCapacity, CircBufIsEmpty, CircBufRead, CircBufWrite.
 *
 * None of the functions check for pointers validation.
 ******************************************************************************/

#ifndef __CIRCBUF_H__ 
#define __CIRCBUF_H__

typedef struct circbuf circbuf_t;

/*
 * Creates a new circular buffer.
 * Returns a pointer to the circular buffer that must be 
 * removed with CircBufDestroy.
 * Returns NULL if function fails to allocate memory.
 * Receives number of bytes needed.
 *
 * In case of capacity of 0 - the default buffer size will 
 * become 100 bytes.
 */
circbuf_t *CircBufCreate(size_t capacity);
 
/*
 * Removes the circular buffer and the data inside.
 */
void CircBufDestroy(circbuf_t *cb);

/*
 * Returns available space (in bytes) for writing. 
 */
size_t CircBufFreeSpace(const circbuf_t *cb);

/*
 * Returns the circular buffer's capacity in bytes.
 */
size_t CircBufCapacity(const circbuf_t *cb);

/*
 * Returns 1 if the circular buffer is empty.
 * Returns 0 if the circular buffer is not empty.
 */
int CircBufIsEmpty(const circbuf_t *cb);

/*
 * Returns number of bytes read, 0 if none.
 * In case of an attempt to read from the buffer
 * when it's empty it returns (-1).
 */
ssize_t CircBufRead(circbuf_t *cb, void *dest, size_t nbytes);

/*
 * Returns number of bytes written, 0 if none.
 * In case of an attempt to write to the buffer
 * when it's full it returns (-1).
 */
ssize_t CircBufWrite(circbuf_t *cb, void *src, size_t nbytes);

#endif /* __CIRCBUF_H__ */

