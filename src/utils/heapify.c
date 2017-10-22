/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Heapify                                #################################
 *                                         ##########    ####       ########
 *  Functions definition                   ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  02-08-2017                             ##########    ####  ###  ######## 
 *  14:32:23                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <assert.h>					 /* assert()					  */
#include <string.h>					 /* memcpy()					  */

#include "heapify.h"				 /* all functions declerations	  */
#include "utils.h"					 /* Or's functions                */

enum
{
	LEFT = 0,
	RIGHT
};

static void Swap(void *data1, void *data2, size_t element_size);

void HeapifyDown(void *base, size_t num_element, size_t element_size, 
		    size_t index, int (*is_before)(const void *data1, const void *data2, 
													  void *param), void *param)
{
	char *runner	  = NULL;
	char *end		  = NULL;
	char *child[2] 	  = {NULL};
	int bigger_child  = 0;
	int new_index 	  = 0;
	
	assert(base && is_before);
	
	runner = (char *)base + (index * element_size);
	new_index = index * 2;
	
	child[LEFT] = (char *)base + (element_size * (new_index + 1));
	child[RIGHT] = (char *)base + (element_size * (new_index + 2));
	
	end = (char *)base + num_element * element_size;
	
	while (child[RIGHT] < end)
	{
		bigger_child = is_before(child[RIGHT], child[LEFT], param);
		
		if (is_before(child[bigger_child], runner, param))
		{
			Swap(child[bigger_child], runner, element_size);
		}
		else
		{
			break;
		}
		
		runner = child[bigger_child];
		new_index = (runner - (char *)base) / element_size;
		child[LEFT] = (char *)base + (element_size * (new_index * 2 + 1));
		child[RIGHT] = (char *)base + (element_size * (new_index * 2 + 2));
	}
	
	if (child[LEFT] < end)
	{
		if (is_before(child[LEFT], runner, param))
		{
			Swap(child[LEFT], runner, element_size);
		}
	}
	
	return;
}


void HeapifyUp(void *base, size_t num_element, size_t element_size, 
			size_t index, int (*is_before)(const void *data1, const void *data2,
												      void *param), void *param)
{
	char *runner	  = NULL;
	char *parent	  = NULL;
	size_t new_index  = 0;
	
	assert(base && is_before);
	
	if (0 == index)
	{
		return;
	}
	
	runner = (char *)base + (index * element_size);
	new_index = ((index - 1) / 2);
	parent = (char *)base + (element_size * new_index);
	
	while (parent >= (char *)base)
	{
		if (is_before(runner, parent, param))
		{
			Swap(runner, parent, element_size);
		}
		else
		{
			break;
		}
		runner = parent;
		new_index = (new_index - 1) / 2;
		parent = (char *)base + (element_size * new_index);
	}
	
	return;
} 

static void Swap(void *data1, void *data2, size_t element_size)
{
	char temp = 0;
	char *a = data1;
	char *b = data2;
	
	while (element_size--)
	{
		temp = *a;
		*a = *b;
		*b = temp;
		++a;
		++b;
	}
	
	return;
}
