/*******************************************************************************
 * Or Nagar
 * Dynamic Vector  
 *  
 * Functions definition
 *   
 * 08/06/17
 ******************************************************************************/
#include <stdlib.h>				/* malloc()			*/
#include <assert.h>				/* assert()			*/
#include <string.h>				/* memcpy()			*/

#include "utils.h"				/* DBG()			*/
#include "d_vector.h"				
#include "d_vector_debug.h"		/* DynVecPrint()	*/

struct dyn_vec
{
	size_t element_size;
	size_t capacity;
	size_t elements_num;
	void *arr;
};

dyn_vec_t *DynVecCreate(size_t capacity, size_t element_size)
{
	dyn_vec_t *dv = NULL;
	 
	if (NULL == (dv = malloc(sizeof(dyn_vec_t))))		 /* creates dyn_vec   */
	{
		MALLOC_ERROR;
		return (NULL);
	}
	
	if (NULL == (dv->arr = malloc(capacity * element_size))) 
	{													 /* creates the array */
		MALLOC_ERROR;
		free(dv);
		return (NULL);
	}

	dv->element_size = element_size;
	dv->elements_num = 0;
	dv->capacity = capacity;
	
	return (dv);
}

void DynVecDestroy(dyn_vec_t *dv)
{
	assert(dv);
	
	free(dv->arr);
	dv->arr = NULL;
	
	free(dv);
	dv = NULL;
	
	return;
}

int DynVecPushBack(dyn_vec_t *dv, const void *data)
{
	void *temp = dv->arr;

	assert(dv);
	assert(data);
	
	if (dv->elements_num == dv->capacity)		/* If the array is full */
	{
		if (NULL == (temp = realloc(dv->arr, dv->element_size *
				  ((dv->capacity == 0) ? 1 : dv->capacity) * 2)))
		{	
			MALLOC_ERROR;
			return (1);
		}
		
		dv->arr = temp;
		dv->capacity = ((dv->capacity == 0) ? 1 : dv->capacity) * 2;
	}	
		
	memcpy((char*)dv->arr + (dv->elements_num * dv->element_size),
										 data, dv->element_size);
	++dv->elements_num;
	
	return (0);
}

int DynVecPopBack(dyn_vec_t *dv)
{
	void *temp;
	
	assert(dv);
	
	if (dv->elements_num == 0)	/* If the vector is empty	 		     */
	{
		return (1);
	}
		
	if (dv->elements_num <= (dv->capacity/4))	/* realloc smaller array */
	{
		if (NULL != (temp = realloc(dv->arr, dv->element_size * 
														   (dv->capacity / 2))))
		{	
			dv->arr = temp;
			dv->capacity /= 2;
		}
		else
		{
			PRINT_ERROR("realloc error");
		}
	}

	--dv->elements_num; 
	temp = NULL;
	
	return (0);

}

void *DynVecGetItemAddres(const dyn_vec_t *dv, size_t index)
{
	assert(dv);
	
	if (dv->elements_num > 0 && index < dv->elements_num)
	{
		
		return ((char *)dv->arr + (index * dv->element_size));
	}
	else
	{
		return (NULL);
	}
}

size_t DynVecSize(const dyn_vec_t *dv)
{
	assert(dv);
	
	return (dv->elements_num);
}

size_t DynVecCapacity(const dyn_vec_t *dv)
{
	assert(dv);
	
	return (dv->capacity);
}

int DynVecReserve(dyn_vec_t *dv, size_t capacity)
{
	void *temp = NULL;
	
	assert(dv);
	
	if (dv->capacity >= capacity)
	{
		return (2);
	}	
	
	if (NULL == (temp = realloc(dv->arr, dv->element_size * capacity)))
	{	
		MALLOC_ERROR;
		
		return (1);
	}
	
	dv->arr = temp;
	dv->capacity = capacity;
	
	return (0);
}



#ifdef _DEBUG
void DynVecPrint(const dyn_vec_t *dv)
{
	unsigned char *runner = dv->arr;
	unsigned char *end_ptr = (unsigned char *)dv->arr +
				   			 dv->elements_num * dv->element_size;
	
	while (runner < end_ptr)				
	{
		printf("0x%02x ", *runner);
		++runner;
		
		if (0 == (size_t)runner % 8)
		{
			puts("");
		}
	}
	printf("\n");
}
#endif


