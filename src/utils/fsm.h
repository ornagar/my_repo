/*****************************************************************************
 * Name. 
 * Fixed size memory allocation
 * Functions decleration.
 * Manage memory of a given memory area that is allready allocated.
 * alloc() and free() work in complexty of O(1). 
 * 04/07/17
 ******************************************************************************/
#ifndef __FSM_H__
#define __FSM_H__

#include <stdlib.h>				/*  size_t                        */


typedef struct fixed_size_mem fsm_t;

/* Returns the minimum size for FSM implamentation */ 
size_t FSMSugestSize(size_t num_blocks, size_t block_size);	

/* The function prepares the FSM pool.
 * Memory is a pointer to the allocated pool of size "FSMSugestSize()".
 * Returns a pointer to  
 * returns NULL on failure.
 */
fsm_t *FSMInit(void *memory, size_t num_blocks, size_t block_size);	

/* Returns you block of memory from your memory surface.
 * the size of the block is as 'block_size' from FSMSugestSize
 * returns NULL on failure.
 * complexty of O(1).
 */ 
void *FSMAlloc(fsm_t *fsm_pool);	

/* Free the space of the block_ptr
 * complexty of O(1).
 */	
void FSMFree(void *block_ptr);	
	
/* Returns the number of free block int your memory surface 
 * complexty of O(n).
 */
size_t FSMCountFree(const fsm_t *fsm_pool);	

#endif /* __FSM_H__ */