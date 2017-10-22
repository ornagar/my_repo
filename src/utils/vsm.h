/*******************************************************************************
 * Or Nagar
 * Infinity Labs R&D
 * RD33
 * Wed Jul  5 16:31:57 2017
 *
 * Variable Size Memory Block Allocation
 * Features:
 * 
 * The VSM must be alligned with a machine word size,
 * if not it will be alligned to it.
 * The blocks assigned will be round up to machine word size.
 * Complexity of VLMFree O(1)
 ******************************************************************************/
#ifndef __VSM_H__
#define __VSM_H__
#define ADVANCED

#include <sys/types.h>      /* size_t */

typedef struct  vsm_pool vsm_pool_t; /* Optional */

/*
 * Initialize a variable size memory pool for management.
 * seg_size is in bytes.
 */
vsm_pool_t *VSMInit(void *memory, size_t seg_size);

/*
 * Allocates a block within the VSM pool.
 * Returns a pointer to the block (void *).
 * On failure, returns NULL.
 */
void *VSMAlloc(vsm_pool_t *mem_pool, size_t block_size);

/*
 * Frees the pointed block within the VSM pool.
 * Complexity: O(1).
 */
void VSMFree(void *block_ptr);

#ifdef ADVANCED

/*
 * Returns the number of bytes that are free within a block.
 */
size_t VSMCountFree(const vsm_pool_t *mem_pool);

/*
 * Finds the largest chunk within the VSM pool.
 * Returns the size of chunk.
 */
size_t VSMLargestChunk(const vsm_pool_t *mem_pool);

#endif

#endif /* __VSM_H__ */