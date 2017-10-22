/*******************************************************************************
 * Or Nagar
 * vsm.h
 * Variable Size Memory Block Allocation
 * Infinity Labs R&D
 * RD33
 * Features:
 * O(1) Free
 * Wed Jul  5 16:31:57 2017
 ******************************************************************************/
#include <stdlib.h>						/* abs()				*/
#include <assert.h>						/* assert()				*/

#include "utils.h"						/* MAX()				*/
#include "vsm.h"

/* MAGIC is a special signature for VSMFree to check its releasinig
 * the right place in the VSM pool without corupting data in another place.
 */
#define MAGIC 				(0x8080808080808080)
#define WORD_SIZE 			(sizeof(size_t))

/* CALCULATE_BLOCK calculates the size of the new block after
 * allignment to a machine word size.
 */
#define CALCULATE_BLOCK(x)  (x + ((WORD_SIZE - x % WORD_SIZE) % 8))

/* The head of the vsm_pool, holds the total size of the pool
 * after substracting it's own size and the first blk_header_t's size.
 */
struct  vsm_pool
{
	size_t total_size;
}; 

/* The head of each block allocated or freed 
 * from the VSM pool. Holds the size of the block allocated or the size 
 * of the block (in negative value) that was freed with VSMFree.
 * in debug mode it also holds a field of magic number explained above.
 */
typedef struct
{
    ssize_t size;
    #ifdef _DEBUG
        unsigned long magic_num;    
    #endif
}blk_header_t;

/***********************STATIC FUNCTIONS DECLARATION***************************
 *
 * MoveBlock funcs return a new pointer equal to (block (+/-) var)
 * example: If block = 1000, var = 2: 
 * Then MoveUpBlock(block, var) = 1002.
 */
static blk_header_t *MoveUpBlock(blk_header_t *block, size_t var);
static blk_header_t *MoveDownBlock(blk_header_t *block, size_t var);
/******************************************************************************/

vsm_pool_t *VSMInit(void *memory, size_t seg_size)
{
	vsm_pool_t *vsm = NULL;
	blk_header_t *blk = NULL;
	assert(memory);

	vsm = (vsm_pool_t *) memory;
	vsm->total_size = seg_size - sizeof(vsm_pool_t) - (sizeof(blk_header_t));
	blk = MoveUpBlock((blk_header_t *) vsm, sizeof(vsm_pool_t));
	blk->size = vsm->total_size;
	
	#ifdef _DEBUG
		blk->magic_num = MAGIC;
	#endif

	return(vsm);
}

void *VSMAlloc(vsm_pool_t *mem_pool, size_t block_size)
{
	blk_header_t *block 	 = NULL;
	blk_header_t *end 		 = NULL;
	blk_header_t *hold		 = NULL;
	blk_header_t *return_ptr = NULL;
	ssize_t new_block_size   = 0;
	size_t temp 			 = 0;

	assert(mem_pool);

	end   = MoveUpBlock((blk_header_t *) mem_pool, mem_pool->total_size);
	block = MoveUpBlock((blk_header_t *) mem_pool, sizeof(vsm_pool_t));
	new_block_size = CALCULATE_BLOCK(block_size);

	while (end > block)
	{	
		/* Handles allocated blocks in a tight loop */
		if (0 > block->size)
		{
			block = MoveUpBlock(block, abs(block->size) + sizeof(blk_header_t));
			continue;
		}

		hold = block;
		temp = hold->size;
		return_ptr = MoveUpBlock(hold, sizeof(blk_header_t));

		/* Handles the merging and searching for a block of wanted size */
		while (end > block && 0 < block->size)
		{
			hold->size = temp;
			block = MoveUpBlock(block, block->size + sizeof(blk_header_t));

			/* Found the wanted block size 							    */
			if (temp >= new_block_size + sizeof(blk_header_t))
			{
				hold->size = (-new_block_size);
				block = MoveUpBlock(hold, new_block_size + sizeof(blk_header_t));
				block->size = temp - new_block_size - sizeof(blk_header_t);
				
				#ifdef _DEBUG
					block->magic_num = MAGIC;
				#endif

				return(return_ptr);
			}
			/* Found the wanted block size without space for block head */
			else if (temp >= new_block_size)
			{
				hold->size *= -1;
				return(return_ptr);
			}
			
			temp += block->size + sizeof(blk_header_t);
		}
	}

	return(NULL);
} 

void VSMFree(void *block_ptr)
{
	blk_header_t *block = NULL;

	if (NULL == block_ptr)
	{
		return;
	}

	block = MoveDownBlock((blk_header_t *) block_ptr, sizeof(blk_header_t));

	#ifdef _DEBUG
		if (MAGIC != block->magic_num)
		{
			return;
		}
	#endif
		
	block->size = abs(block->size);

	return;
}

size_t VSMCountFree(const vsm_pool_t *mem_pool)
{
	size_t count = 0;
	blk_header_t *block = NULL;
	blk_header_t *end = NULL;

	assert(mem_pool);

	block = MoveUpBlock((blk_header_t *) mem_pool, sizeof(vsm_pool_t));
	end   = MoveUpBlock((blk_header_t *) mem_pool, mem_pool->total_size);

	while (end > block)
	{
		if (0 < block->size)
		{
			count += block->size;
		}

		block = MoveUpBlock(block, abs(block->size)  + sizeof(blk_header_t));
	}

	return(count);
}

size_t VSMLargestChunk(const vsm_pool_t *mem_pool)
{
	blk_header_t *block = NULL;
	blk_header_t *end 	= NULL;
	size_t 		  max	= 0;
	size_t 	 temp_count = 0;

	end   = MoveUpBlock((blk_header_t *) mem_pool, mem_pool->total_size);
	block = MoveUpBlock((blk_header_t *) mem_pool, sizeof(vsm_pool_t));

	while (block < end)
	{
		while (block < end && 0 < block->size)
		{
			temp_count += block->size;
			block = MoveUpBlock(block, block->size + sizeof(blk_header_t));
		}

		if (block < end)
		{
			block = MoveUpBlock(block, abs(block->size) + sizeof(blk_header_t));
		}
		
		max = MAX(max, temp_count);
		temp_count = 0;
	}

	return(max);
}


/***************************STATIC FUNCTIONS*********************************/
static blk_header_t *MoveUpBlock(blk_header_t *block, size_t var)
{
	block = (blk_header_t *)((char *) block + var);

	return(block);
}

static blk_header_t *MoveDownBlock(blk_header_t *block, size_t var)
{
	block = (blk_header_t *)((char *) block - var);

	return(block);
}
/****************************************************************************/


