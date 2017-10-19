/*****************************************************************************
 * Or Nagar. 
 * Fixed size memory allocation
 * Functions definition.
 * 04/07/17
 ******************************************************************************/
#include <sys/types.h>				/*  ssize_t								  */
#include <assert.h>					/*  assert()							  */		
#include <stdio.h>					/*  printf()						   	  */

#include "utils.h"					/* PRINT_ERROR							  */
#include "fsm.h"

#define FSM_END	  			(-1)
#define WORD_SIZE 			(sizeof(size_t))
#define CALCULATE_BLOCK(x)  (x + ((WORD_SIZE - x % WORD_SIZE) % WORD_SIZE)\
											 + (sizeof(block_info_t)))

/* FSM - the managment struct for a fixed size memory pool 					  */ 
struct fixed_size_mem	
{	
	ssize_t next_free_block_offset;			/* An offset to next free block   */
	size_t block_size;						/* The size of each block 		  */
	size_t num_blocks;						/* The number of blocs to allocate*/
};	

/* The managment struct for each block in the pool 							  */
typedef struct 	
{	
	ssize_t next_free_block_offset;			/* An offset to next free block   */
}block_info_t;	

/***********************STATIC FUNCTIONS DECLARATION***************************/
static void swap(size_t *a, size_t *b);
/*
 * MoveBlock funcs return a new pointer equal to (block (+/-) var)
 * example: block = 1000, var = 2 - then MoveUpBlock(block, var) = 1002.
 */
static block_info_t *MoveUpBlock(block_info_t *block, size_t var);
static block_info_t *MoveDownBlock(block_info_t *block, size_t var);
/******************************************************************************/

size_t FSMSugestSize(size_t num_blocks, size_t block_size)
{
	return(num_blocks * CALCULATE_BLOCK(block_size) + sizeof(fsm_t));
}

fsm_t *FSMInit(void *memory, size_t num_blocks, size_t block_size)
{
	fsm_t *fsm = (fsm_t *) memory;
	block_info_t *block = memory;
	ssize_t offset = 0;

	assert(memory);

	block = MoveUpBlock(block, sizeof(fsm_t));
	block_size = CALCULATE_BLOCK(block_size);

	fsm->next_free_block_offset = offset;
	fsm->block_size = block_size;
	fsm->num_blocks = num_blocks;

	while(1 < num_blocks--)
	{	
		offset += block_size;
		block->next_free_block_offset = offset;
		block = MoveUpBlock(block, fsm->block_size);
	}
	block->next_free_block_offset = FSM_END;

	return(fsm);
}

void *FSMAlloc(fsm_t *fsm_pool)
{
	block_info_t *block = NULL; 

	assert(fsm_pool);

	block = (block_info_t *)fsm_pool; 

	if (FSM_END == fsm_pool->next_free_block_offset)
	{
		PRINT_ERROR("FSM ERROR");
		return(NULL);
	}

	block = MoveUpBlock(block, sizeof(fsm_t));
	block = MoveUpBlock(block, fsm_pool->next_free_block_offset);

	swap((size_t*)&block->next_free_block_offset, 
		 (size_t*)&fsm_pool->next_free_block_offset);

	block = MoveUpBlock(block, sizeof(block_info_t));

	return((void *) block);
}

void FSMFree(void *block_ptr)				
{
	block_info_t *runner = block_ptr;
	fsm_t *fsm = NULL;
	
	assert(block_ptr);

	runner = MoveDownBlock(runner, sizeof(block_info_t));
	fsm    = (fsm_t *)MoveDownBlock(runner, runner->next_free_block_offset);
	fsm    = (fsm_t *)MoveDownBlock((block_info_t *)fsm, sizeof(fsm_t));

	swap((size_t*)&runner->next_free_block_offset, 
		 (size_t*)&fsm->next_free_block_offset);
	
	return;
}

size_t FSMCountFree(const fsm_t *fsm_pool)
{
	block_info_t *block = NULL;

	size_t count = 1;

	assert(fsm_pool);

	if(FSM_END == fsm_pool->next_free_block_offset)
	{
		return(0);
	}

	block = (block_info_t *) fsm_pool;
	block = MoveUpBlock(block, sizeof(fsm_t));
	block = MoveUpBlock(block, fsm_pool->next_free_block_offset);

	while(FSM_END != block->next_free_block_offset)
	{
		++count;
		block = MoveUpBlock((block_info_t *)fsm_pool, 
							(sizeof(fsm_t) + block->next_free_block_offset));
	}

	return(count);
}

void PrintFsm(const fsm_t *fsm)
{
	block_info_t *block = (block_info_t *)fsm;
	block_info_t *static_block = (block_info_t *)fsm;
	size_t count = 0;

	assert(fsm);

	count = fsm->num_blocks;

	block = (block_info_t *)((char *) block + sizeof(fsm_t));
	static_block = block;

	printf("-------------------------------------------------\n");
	printf("print FSM test:\t prints a bit map off the FSM\n");
	printf("1 - allocated space\n");
	printf("0 - free space\n");
	printf("\n");
	
	while(count--)
	{
		if(0 == count % WORD_SIZE)
		{
			printf("\n");
		}

		if (((char *)block - block->next_free_block_offset) == (char *)static_block)
		{
			printf(" 1 ");
		}
		else
		{
			printf(" 0 ");
		}
		block = (block_info_t *)((char *)block + fsm->block_size);
	}
	printf("\n-------------------------------------------------\n");
	printf("\n\n");
}

/***************************STATIC FUNCTIONS*********************************/
static void swap(size_t *a, size_t *b)
{
	size_t temp = *a;
	*a = *b;
	*b = temp;

	return;
}

static block_info_t *MoveUpBlock(block_info_t *block, size_t var)
{
	block = (block_info_t *)((char *) block + var);

	return(block);
}

static block_info_t *MoveDownBlock(block_info_t *block, size_t var)
{
	block = (block_info_t *)((char *) block - var);

	return(block);
}
/****************************************************************************/
