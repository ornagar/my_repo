/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Htable                                 #################################
 *                                         ##########    ####       ########
 *  Functions decleration                  ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  28-07-2017                             ##########    ####  ###  ######## 
 *  10:43:52                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#ifndef __HTABLE_H__
#define __HTABLE_H__

typedef struct hash_table hash_table_t;

typedef enum 
{
 	MAX_COLLISIONS,
	COLLISIONS_AVERAGE,
	COLLISIONS_VARIANCE
} type_t;

/* In case of failure returns a NULL pointer */
/* size is number of elements requested 	 */
hash_table_t *HTCreate(size_t size, 
		size_t(*hash_func)(const void *key),
		int(*is_equal_func)(const void *data1, const void *data2));

/* Complexity: O(n) */
void HTDestroy(hash_table_t *table);

/* In case of failure returns a non-zero value */
/* Complexity: O(1) */
int HTInsert(hash_table_t *table, const void *data);

/* If data is not found in the table, no action takes place */
/* Complexity: O(1) */
void *HTRemove(hash_table_t *table, const void *data);

/* Complexity: O(n) */
size_t HTSize(const hash_table_t *table);

/* Complexity: O(n) */
int HTIsEmpty(const hash_table_t *table);

/* Returns a NULL pointer if data wasn't found */
/* Complexity: O(n) */
void *HTFind(const hash_table_t *table, const void *data);

/* If the Action Function returns a non-zero value, HTFind stops and
   returns the exit status of the action function.*/
/* Complexity: O(n) */
int HTForEach(hash_table_t *table, int(*act_func)(void *data, void *args),
		void *args);

/* This function returns data regarding the max number of collisions, as well as
   the average and the variance  */
double HTGetStatistics(const hash_table_t *table, type_t type_of_data);

#endif /* __HTABLE_H__ */
