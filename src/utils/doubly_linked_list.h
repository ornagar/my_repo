/*****************************************************************************
 * Or Nagar.
 * Doubly linked list library.
 * The queue is based on a singly linked list, where the data
 * is entred into a node in the tail of the list and dequeued 
 * from the list's head.
 * Functions definition.
 * 19/06/17
 ****************************************************************************/
#ifndef __DOUBLY_LINKED_LIST_H__ 
#define __DOUBLY_LINKED_LIST_H__ 

typedef struct dlist_node dlist_node_t;
typedef struct dlist dlist_t;
typedef dlist_node_t *dlist_iter_t;

/*  
 * Create and init a doubly linked list
 * When faild return NULL
 */
dlist_t *DlistCreate(void);

/* Release memory of doubly linked list */
void DlistDestroy(dlist_t *dl);

/* Return the number of nodes in the list */
size_t DlistCount(const dlist_t *dl);

/* Return boolean: 1 true, 0 false */
int DlistIsEmpty(const dlist_t *dl);

/* Return iterator to the first real node */
dlist_iter_t DlistBegin(const dlist_t *dl);

/* Return iterator to the node after the last real node */
dlist_iter_t DlistEnd(const dlist_t *dl);

/* Return iterator to the next node */
dlist_iter_t DlistNext(const dlist_iter_t iter);

/* Return iterator to the previous node */
dlist_iter_t DlistPrev(const dlist_iter_t iter);

/* Return a pointer to the data of the iterator place */
void *DlistGetData(const dlist_iter_t iter);

/* 
 * Check if 2 iterator are the same, 
 * Return boolean value: 1 true, 0 false 
 */
int DlistIsSameIterator(const dlist_iter_t iter1, const dlist_iter_t iter2);

/* 
 * Check if the iterator is non valid one, 
 * Return boolean value: 1 non-valid, 0 valid 
 */
int DlistIsBadIterator(const dlist_t *dl, const dlist_iter_t iter);

/* 
 * Insert node before "where" and return iterator to the inserted node.
 * When faild- return bad iterator.
 */
dlist_iter_t DlistInsert(dlist_t *dl, dlist_iter_t where, void *data);

/* 
 * Remove node and release its memory.
 * When Erase the last element or failed - return "bad iterator"
 * Returns an iterator to the next node.
 */
dlist_iter_t DlistErase(dlist_iter_t iter);

/* 
 * Create node with the given data and insert it in the beginning of the list.
 * Return iterator to the inserted node
 * Note: After using, previous itrators may be invalid
 */
dlist_iter_t DlistPushFront(dlist_t *dl, void *data);

/* 
 * Create node with the given data and insert it in the end of the list.
 * Return iterator to the inserted node 
 * Note: After using, previous itrators may be invalid
 */
dlist_iter_t DlistPushBack(dlist_t *dl, void *data);

/* 
 * Remove node from the beginning of the list.
 * Return pointer to the removed data.
 * Note: After using, previous itrators may be invalid
 */
void *DlistPopFront(dlist_t *dl);

/* 
 * Remove node from the end of the list.
 * Return pointer to the removed data.
 * Note: After using, previous itrators may be invalid
 */
void *DlistPopBack(dlist_t *dl);

/* 
 * Remove nodes from "from" to "to", and insert them befor "where".
 * Note: After using, previous itrators may be invalid
 */
void DlistSpliceBefore(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to);

/* 
 * Returns 0 on success and non-zero on failure.
 * Run "action_func" in the range of "from -> to".
 * On failure of action_func, stop the iteration and returns a failure status 
 * action_func shall return 0 on suceess and non-zero on failure.
 * Param is optional. If not needed, set to NULL.
 */
int DlistForeach(dlist_iter_t from, dlist_iter_t to,
				 int (*action_func)(void *data, void *param),
				 void *param);
/* 
 * "is_equal_func" compares each data in the range of "from -> to" 
 * to the given param.
 * Return pointer to the first found node or bad iterator if not found.
 * "is_equal_func" shall return 1 on equality, 0 otherwise.
 */
dlist_iter_t DlistFind(dlist_t *dl, dlist_iter_t from, dlist_iter_t to,
					int (*is_equal_func)(const void *data, const void *param),     
					const void *param);
/*
 * For Hash Table usage.
 */
dlist_iter_t DlistHFind(dlist_t *dl, dlist_iter_t from, dlist_iter_t to,			
					int (*is_equal_func)(const void *data, const void *param),     
					const void *param);

				    
#endif /* __DOUBLY_LINKED_LIST_H__  */

