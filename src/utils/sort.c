/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Sort                                   #################################
 *                                         ##########    ####       ########
 *                                         ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  12-07-2017                             ##########    ####  ###  ######## 
 *  14:44:44                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdlib.h>					 /* malloc()					  */
#include <assert.h>					 /* assert()					  */
#include <string.h>					 /* memcpy()					  */

#include "heapify.h"
#include "sort.h"					 /* all functions declerations	  */
#include "utils.h"					 /* Or's functions                */

#define BYTE_MASK 	(0x00000000000000FF)

enum
{
	SUCCESS,
	FAIL
};
enum
{
	SWAP_FLAG_OFF,
	SWAP_FLAG_ON
};

static size_t MyKey(const void *element, const void *args);

static void MergeSortImp(void *base,void *block, size_t num_of_elements,
	  size_t element_size, int (*compar)(const void *data1, const void *data2));
static void Merge(void *base_l, void *base_r, void *block,  size_t element_size,
				 size_t l_num_of_elements, size_t r_num_of_elements, 
				  int (*compar)(const void *data1, const void *data2));

static void QuickSortImp(void *base, void *end, void *temp,
						 size_t num_of_elements, size_t element_size, 
						 int (*compar)(const void *data1, const void *data2));
	  				  
/* A utility struct that should keep a 
 * pointer and a key to each member in the source array.
 * The struct is a utility for Radix Sort
 */ 
typedef struct 
{
	void *data;
	size_t key;

} rdx_t;

int BubbleSort(void *base, size_t num_of_elements, size_t element_size,
				int (*compar)(const void *x, const void *y))
{
	int i = 0;
	int swaped_flag = SWAP_FLAG_ON;
	void *runner = NULL;
	void *temp = NULL;

	assert(base && compar);

	if (NULL == (temp = malloc(element_size)))
	{
		MALLOC_ERROR;
		return(FAIL);
	}

	while (swaped_flag)
	{	
		swaped_flag = SWAP_FLAG_OFF;
		runner = base;
		for (i = 0; i < num_of_elements - 1; ++i)
		{
			if (0 < compar(runner, ((char *)runner + element_size)))
			{
				memcpy(temp, runner, element_size);
				memcpy(runner, ((char *)runner + element_size), element_size);
				memcpy(((char *)runner + element_size), temp, element_size);

				swaped_flag = SWAP_FLAG_ON;
			}
			runner = ((char *)runner + element_size);
		}
		--num_of_elements;
	}

	free(temp);

	return(SUCCESS);
}

int InsertionSort(void *base, size_t num_of_elements, size_t element_size,
				int (*compar)(const void *x, const void *y))
{
	void *first_unsorted = NULL;
	void *runner = NULL;
	void *temp = NULL;
	void *end = NULL;

	assert(base && compar);

	if (NULL == (temp = malloc(element_size)))
	{
		MALLOC_ERROR;
		return(FAIL);
	}

	first_unsorted = (char *)base + element_size;
	end = (char *)base + (num_of_elements * element_size);

	while (first_unsorted < end)
	{
		runner = (char *)first_unsorted - element_size;

		if (0 < compar(((char *)first_unsorted - element_size), first_unsorted))
		{
			memcpy(temp, first_unsorted, element_size);

			while ((runner >= base) && (0 < compar(runner, temp)))
			{
				runner = (char *)runner - element_size;
			}

			runner = (char *)runner + element_size;
			memmove(((char *)runner + element_size), runner, 
									((char *)first_unsorted - (char *)runner));
			memcpy(runner, temp, element_size);
		}

		first_unsorted = (char *)first_unsorted + element_size;
	}

	free(temp);

	return(SUCCESS);
}

int SelectionSort(void *base, size_t num_of_elements, size_t element_size,
				int (*compar)(const void *x, const void *y))
{
	void *first_unsorted = NULL;
	void *min_val = NULL;
	void *runner = NULL;
	void *temp = NULL;
	void *end = NULL;

	assert(base && compar);

	if (NULL == (temp = malloc(element_size)))
	{
		MALLOC_ERROR;
		return(FAIL);
	}

	runner = first_unsorted = base;
	end = (char *)base + (num_of_elements * element_size);

	while (first_unsorted < end)
	{
		min_val = first_unsorted;

		while (runner < end)
		{
			if (0 > compar(runner, min_val))
				{
					min_val = runner;
				}

			runner = (char *)runner + element_size;
		}

		if (min_val != first_unsorted)
		{
			memcpy(temp, min_val, element_size);
			memcpy(min_val, first_unsorted, element_size);
			memcpy(first_unsorted, temp, element_size);
		}

		first_unsorted = (char *)first_unsorted + element_size;
		runner = (char *)first_unsorted;
	}

	free(temp);

	return(SUCCESS);
}

int CountingSort(void *base, size_t num_of_elements, size_t element_size,
				size_t (*key_to_num)(const void *element, const void *args),
				const void *args, size_t range)
{
	void *runner = NULL;
	void *end = NULL;
	void *dest = NULL;
	size_t *histogram = NULL;
	size_t i = 0;
	size_t index = 0;

	assert(base && key_to_num);
	
	/* Allocate a temporary destination array */
	if (NULL == (dest = malloc(element_size * num_of_elements)))
	{
		MALLOC_ERROR;
		return(FAIL);
	}
	
	/* Allocate an histogram for counting sort */
	if (NULL == (histogram = calloc((range + 1), sizeof(size_t))))
	{
		MALLOC_ERROR;
		free(dest);
		return(FAIL);
	}

	runner = base;
	end = (char *)base + (num_of_elements * element_size);
	
	/* Iterate throw the array and add one for each key in the histogram */
	while (runner < end)
	{
		++histogram[key_to_num(runner, args)];
		runner = (char *)runner + element_size;
	}
	
	/* Sum each entry in the histogram with its previous to get indexes */
	for (i = 1; i <= range; ++i)
	{
		histogram[i] += histogram[i - 1];
	}

	runner = (char *)end - element_size;
	
	/* Iterate from end of the array to the beginning and copy the value to 
	 * the temporary destination by the key's index (in the histogram)
	 */
	while (runner >= base)
	{
		index = key_to_num(runner, args);
		--histogram[index];
		memcpy(((char *)dest + (histogram[index] * element_size)),
													 runner, element_size);
		runner = (char *)runner - element_size;
	}
	
	/* Copy dest to base and free resources */
	memcpy(base, dest, element_size * num_of_elements);
	free(histogram);
	free(dest);

	return(SUCCESS);
}

int RadixSort(void *base, size_t num_of_elements, size_t element_size,
				size_t (*get_key)(const void *element, const void *args),
				const void *args, size_t num_of_bytes)
{
	void *runner = NULL;
	void *end = NULL;
	void *dest = NULL;
	rdx_t *mem_manager = NULL;
	rdx_t *mem_runner = NULL;
	size_t iter_num = 0;

	assert(base && get_key);

	if (NULL == (dest = malloc(element_size * num_of_elements)))
	{
		MALLOC_ERROR;
		return(FAIL);
	}

	if (NULL == (mem_manager = malloc(num_of_elements * sizeof(rdx_t))))
	{
		MALLOC_ERROR;
		free(dest);
		return(FAIL);
	}

	runner = base;
	end = (char *)base + element_size * num_of_elements;
	mem_runner = mem_manager;

	/* Update mem_manager: Data & keys 		*/
	while (runner < end)
	{
		mem_runner->data = runner;
		mem_runner->key  = (size_t)get_key(runner, args);
		runner = (char *)runner + element_size;
		++mem_runner;
	}

	/* Call CountingSort for each byte 		*/
	while (iter_num < num_of_bytes)
	{
		if (CountingSort(mem_manager, num_of_elements, sizeof(rdx_t), MyKey,
											&iter_num, 255))
		{
			PRINT_ERROR("RADIX ERROR");
			return(FAIL);
		}
		++iter_num;
	}

	runner = dest;
	end = (char *)dest + element_size *num_of_elements;
	mem_runner = mem_manager;

	/* Update dest with sorted data			*/
	while (runner < end)
	{
		memcpy(runner, mem_runner->data, element_size);
		runner = (char *)runner + element_size;
		++mem_runner;
	}

	/* Copy dest to base and free recources	 */	
	memcpy(base, dest, element_size * num_of_elements);
	free(mem_manager);
	free(dest);

	return(SUCCESS);
}

static size_t MyKey(const void *element, const void *args)
{
	size_t mask = BYTE_MASK; 
	size_t iter_num = ((*(size_t *) args) * 8);
	size_t key = (size_t)(((rdx_t *)element)->key);
	mask <<= iter_num;
	key &= mask;
	key >>= iter_num;

	return(key);
}

int MergeSort(void *base, size_t num_of_elements, size_t element_size,
							int (*compar)(const void *data1, const void *data2))
{
	void *block = NULL;
	
	assert(base && compar);
	
	if (NULL == (block = malloc(num_of_elements * element_size)))
	{
		return (FAIL);
	}
	
	MergeSortImp(base, block, num_of_elements, element_size, compar);
	
	free(block);
	
	return (SUCCESS);	
}

static void MergeSortImp(void *base,void *block, size_t num_of_elements,
	   size_t element_size, int (*compar)(const void *data1, const void *data2))
{
	size_t l_num_of_elements = num_of_elements / 2;
	
	if (1 < num_of_elements)
	{
		MergeSortImp(base, block, l_num_of_elements, element_size, compar);
	
		MergeSortImp(((char *)base + (l_num_of_elements * element_size)), block, 
					num_of_elements - l_num_of_elements, element_size, compar);
	}
	
	Merge(base, ((char *)base + l_num_of_elements * element_size), block, 
								  element_size, l_num_of_elements,
								  num_of_elements - l_num_of_elements, compar);
	return;						  
}

static void Merge(void *base_l, void *base_r, void *block,  size_t element_size,
				 size_t l_num_of_elements, size_t r_num_of_elements, 
				  int (*compar)(const void *data1, const void *data2))			
{
	void *l_runner	 = base_l;
	void *r_runner 	 = base_r;
	void *m_runner	 = block;
	void *l_end 	 = (char *)base_l + (element_size * l_num_of_elements);
	void *r_end  	 = (char *)base_r + (element_size * r_num_of_elements);
		  
	while (l_runner < l_end && r_runner < r_end)
	{
		if (0 > compar(l_runner, r_runner))
		{
			memcpy(m_runner, l_runner, element_size);
			m_runner = (char *)m_runner + element_size;
			l_runner = (char *)l_runner + element_size;
		}
		else 
		{
			memcpy(m_runner, r_runner, element_size);
			m_runner = (char *)m_runner + element_size;
			r_runner = (char *)r_runner + element_size;
		}
	}
	
	/* Copy reminders (if exist) to m_runner 				*/
	memcpy(m_runner, l_runner, (char*)l_end - (char*)l_runner);
	memcpy(m_runner, r_runner, (char*)r_end - (char*)r_runner);
	
	/* Copy block to base								    */
	memcpy(base_l, block, (element_size * (l_num_of_elements + 
														   r_num_of_elements)));
	
	return;
}


int QuickSort(void *base, size_t num_of_elements, size_t element_size,
						    int (*compar)(const void *data1, const void *data2))
{
	void *temp = NULL;
	
	assert(base && compar);
	
	if (NULL == (temp = malloc(element_size)))
	{
		MALLOC_ERROR;
		return (1);
	}
	
	QuickSortImp(base, (char *)base + (num_of_elements * element_size), temp,
										 num_of_elements, element_size, compar);
	
	return (0);
}

static void QuickSortImp(void *base, void *end, void *temp,
						  size_t num_of_elements, size_t element_size,
							int (*compar)(const void *data1, const void *data2))
{
	void *pivot = (char *)end - element_size;
	void *runner = base;
	void *big_side = base;
	size_t new_size = 0;

	while (runner < pivot)
	{
		if (0 > compar(runner, pivot))
		{
			if (runner != big_side)
			{	
				memcpy(temp, runner, element_size);
				memcpy(runner, big_side, element_size);
				memcpy(big_side, temp, element_size);	
			}
			big_side = (char *)big_side + element_size;
		}

		runner = (char *)runner + element_size;
	}

	memcpy(temp, pivot, element_size);
	memcpy(pivot, big_side, element_size);
	memcpy(big_side, temp, element_size);
	
	new_size = ((char *)big_side - (char *)base) / element_size;
	if (1 < new_size)
	{
		QuickSortImp(base, big_side, temp, new_size, element_size, compar);
	}
	
	big_side = (char *)big_side + element_size;
	new_size = ((char *)end - (char *)big_side) / element_size;
	
	if (1 < new_size)
	{
		QuickSortImp(big_side, end, temp, new_size, element_size, compar);
	}

	return;						  
}

void *BinSearch(void *base, size_t num_of_elements, size_t element_size,
						    int (*compar)(const void *data1, const void *data2),
												const void *req_data)
{
	char *end = NULL;
	char *mid = NULL;
	char *begin = NULL;
	int status = 0;
	
	assert(base && compar);
	
	begin = (char *)base;
	end = begin + (num_of_elements * element_size);
	mid = begin + ((num_of_elements / 2) * element_size);
	
	while (begin < end)
	{
		if (0 > (status = compar(req_data, mid)))
		{
			num_of_elements = ((mid - begin) / element_size) / 2;
			end = mid;
			mid = begin + (num_of_elements * element_size);
		}
		else if (0 < status)
		{
			mid += element_size;
			num_of_elements = ((end - mid) / element_size) / 2;
			begin = mid;
			mid += ((num_of_elements * element_size));
		}
		else 
		{
			return (mid);
		}
	}
	
	return (NULL);
}

int HeapSort(void *base, size_t num_of_elements, size_t element_size,
			int (*is_before)(const void *data1, const void *data2, void *param),
																	void *param)
{
	size_t i = 1;
	char *runner = NULL;
	void *temp = NULL;
	
	assert(base && is_before);
		
	if (NULL == (temp = malloc(element_size)))
	{
		MALLOC_ERROR;
		return (1);
	}
		
	while (i < num_of_elements)
	{
		HeapifyUp(base, num_of_elements, element_size, i++, is_before, param);
	}
	
	runner = (char *)base + ((num_of_elements - 1) * element_size);
	
	while ((char *)base < runner)
	{
		memcpy(temp, base, element_size);
		memcpy(base, runner, element_size);
		memcpy(runner, temp, element_size);

		runner = runner - element_size;
		--num_of_elements;
		HeapifyDown(base, num_of_elements, element_size, 0, is_before, param);
	}

	return (0);
}
