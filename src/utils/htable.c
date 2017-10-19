/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Htable                                 #################################
 *                                         ##########    ####       ########
 *  Functions definition                   ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  28-07-2017                             ##########    ####  ###  ######## 
 *  10:43:52                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <assert.h>					 /* assert()					  */
#include <math.h>					 /*pow()						  */

#include "doubly_linked_list.h"		 /* DlistCreate()				  */
#include "htable.h"					 /* all functions declerations	  */
#include "utils.h"					 /* Or's functions                */

enum
{
	SUCCESS,
	FAILURE
};

/*
 * A Management struct to hold the hash table
 */ 
struct hash_table
{
	size_t size;
	size_t(*hash_func)(const void *key);
	int(*is_equal_func)(const void *data1, const void *data2);
	dlist_t **lists;
};

hash_table_t *HTCreate(size_t size, 
		size_t(*hash_func)(const void *key),
		int(*is_equal_func)(const void *data1, const void *data2))
{
	hash_table_t *table = NULL;
	size_t i = 0;
	
	assert(hash_func && is_equal_func);
	
	if (NULL == (table = (hash_table_t *) malloc(sizeof(hash_table_t))))
	{
		PRINT_ERROR("Malloc error");
		return (NULL);
	}
	
	if (NULL == (table->lists = (dlist_t **)malloc(size * sizeof(dlist_t *))))
	{
		PRINT_ERROR("Malloc error");
		free(table);
		return (NULL);
	}
	
	table->size = size;
	table->hash_func = hash_func;
	table->is_equal_func = is_equal_func;
	
	while (i < table->size)
	{
		table->lists[i++] = NULL;
	}
	
	return (table);
}

void HTDestroy(hash_table_t *table)
{
	size_t i = 0;
	
	assert(table);
	
	while (i < table->size)
	{
		DlistDestroy(table->lists[i++]);
	}
	
	free(table->lists);
	free(table);
	return;
}

int HTInsert(hash_table_t *table, const void *data)
{
	size_t hash = 0;
	
	assert(table && data);

	hash = table->hash_func(data);
	
	if (NULL == table->lists[hash])
	{
		if (NULL == (table->lists[hash] = DlistCreate()))
		{
			return (FAILURE);
		}
	}
	
	if (NULL == (DlistPushBack(table->lists[hash], (void *)data)))
	{
		PRINT_ERROR("Dlist insert error");
		
		return(FAILURE);
	}
	
	return (SUCCESS);
}

void *HTRemove(hash_table_t *table, const void *data)
{
	size_t hash = 0;
	void *return_data = NULL;
	dlist_iter_t iter;
	
	assert(table && data);
	
	hash = table->hash_func(data);
	iter = 	DlistFind(table->lists[hash], DlistBegin(table->lists[hash]),
	    			  DlistEnd(table->lists[hash]), table->is_equal_func, data);
	
	if (DlistIsBadIterator(table->lists[hash], iter))
	{
		return (NULL);
	}
	
	return_data = DlistGetData(iter);
	
	iter = DlistErase(iter);
	
	if (DlistIsEmpty(table->lists[hash]))
	{
		DlistDestroy(table->lists[hash]);
		table->lists[hash] = NULL;
	}
	
	return (return_data);
}

size_t HTSize(const hash_table_t *table)
{
	size_t i = 0;
	size_t count = 0;
	
	assert(table);
	
	while (i < table->size)
	{
		count += DlistCount(table->lists[i++]);
	}
	
	return (count);
}

int HTIsEmpty(const hash_table_t *table)
{
	assert(table);
	return (0 == HTSize(table));
}

void *HTFind(const hash_table_t *table, const void *data)
{
	size_t hash = 0;
	dlist_iter_t iter = NULL;
	
	assert(table && data);
	
	hash = table->hash_func(data);	
	iter = DlistFind(table->lists[hash], DlistBegin(table->lists[hash]),
			   DlistEnd(table->lists[hash]), table->is_equal_func, data);
	
	if (DlistIsBadIterator(table->lists[hash], iter))
	{
		return (NULL);
	}
	
	return(DlistGetData(iter));
}

int HTForEach(hash_table_t *table, int(*act_func)(void *data, void *args),
		void *args)
{
	size_t i = 0;
	int status = 0;
	
	assert(table && act_func);
	
	while (i < table->size && 0 == status)
	{
		if (NULL != table->lists[i])
		{
			status = DlistForeach(DlistBegin(table->lists[i]),
						    DlistEnd(table->lists[i]), act_func, args);
		}
		++i;
	}
	
	return (status);
}

double HTGetStatistics(const hash_table_t *table, type_t type_of_data)
{
	int i = 0;
	double max = 0;
	double average = 0;
	double variance = 0.0;
	double size = 0;
	double temp = 0;
	
	switch (type_of_data)
	{
		case MAX_COLLISIONS:
			while (i < table->size)
			{
				temp = (double)DlistCount(table->lists[i++]);
				max = temp > max ? temp : max;
			}
			return (max);
			
		case COLLISIONS_AVERAGE:
			i = 0;
			while (i < table->size)
			{
				average += (double)DlistCount(table->lists[i++]);
			}
			return (average / (double)table->size);
		
		case COLLISIONS_VARIANCE:
			i = 0;
			while (i < table->size)
			{
				average += DlistCount(table->lists[i++]);
			}
			average = (double)average / table->size;
			i = 0;
			while (i < table->size)
			{	
				size = (double)DlistCount(table->lists[i++]);
				variance += pow((double)size - average, 2);
			}
			variance /= (double)table->size - 1;
			return (variance);
		default:
			return (0);
	}	
}
