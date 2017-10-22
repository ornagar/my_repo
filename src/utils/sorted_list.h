/*******************************************************************************
 *  Author: Or Nagar.
 *  Creation date: 21.06.17
 *  Last modified: 22.06.17
 *  Building Sorted Linked List.
 *  Functions declaration, H. file.
 *  Warning: If the data is altered after it is entered, there is no guarantee 
 *  that it will remain sorted.
 ******************************************************************************/
#ifndef __SORTED_LIST_H__ 
#define __SORTED_LIST_H__ 

typedef struct sorted_list sorted_list_t;

typedef struct
{
	void *iter;
} sorted_list_iter_t;

/* Function creates a sorted linked list
 * and returns a pointer to the list / NULL on malloc error.
 * NOTE: is_before shall compare data1 to data2
 *       & return 1 if data1 is bigger, 0 otherwise.
 * 		 param is optional.
 */
sorted_list_t *SlistCreate(
		int (*is_before)(const void *data1, const void *data2, void *param), 
		void *param);

/* Function receives sorted linked list pointer.
 * and free it
 */
void SlistDestroy(sorted_list_t *sl);

/* Function receives sorted linked list pointer.
 * Return it's size.
 */
size_t SlistSize(const sorted_list_t *sl);

/* Function receives sorted linked list pointer.
 * Return 1 if it is empty 0 if not.
 */
int SlistIsEmpty(const sorted_list_t *sl);

/* Function receives sorted linked list pointer.
 * Return the first iterator. (empty list will return "bad iterator")
 */
sorted_list_iter_t SlistBegin(const sorted_list_t *sl);

/* Function receives sorted linked list pointer.
 * Return the end iterator (1 element after the list).
 */
sorted_list_iter_t SlistEnd(const sorted_list_t *sl);

/* Function receives sorted linked list iterator.
 * Returns the previous iterator.
 */
sorted_list_iter_t SlistPrev(const sorted_list_iter_t iterator);

/* Function receives sorted linked list iterator.
 * Return the next iterator, the end iteraor will return itself
 * "bad iterator"
 */
sorted_list_iter_t SlistNext(const sorted_list_iter_t iterator);

/* Function receives sorted linked list iterator.
 * Returns a pointer to the data of the iterator place
 * If the data is altered after it is entered, there is no guarantee 
 * that it will remain sorted.
 */
void *SlistGetData(const sorted_list_iter_t iterator);

/* Function receives 2 sorted linked list iterators
 * and checks if they are the same.
 * Return 1 when true, 0 when false.
 */
int SlistIsSameIterator(const sorted_list_iter_t iterator1,
                        const sorted_list_iter_t iterator2);

/*
 * Function checks if the iterator is non valid one (1 before begin, end, NULL)
 * Return 1 when true, 0 when false.
 */
int SlistIsBadIterator(const sorted_list_t *sl, const sorted_list_iter_t iter);

/* Function receives sorted linked list pointer & pointer
 *  to data
 * Function inserts the data in the rigth place.
 * Function returns an iterator to inserted element.
 * On failure will return "bad iterator"
 */
sorted_list_iter_t SlistInsert(sorted_list_t *sl, const void *data);

/* Function receives sorted linked list iterator
 * & erases it.
 * Function returns a pointer to the next element.
 * erasing Last element will return "bad iterator"
 */
sorted_list_iter_t SlistRemove(sorted_list_iter_t iterator);


/* Function receives sorted linked list pointer,
 * erases the element in the start of the sorted linked list & retuns it's data.
 */
void *SlistPopFront(sorted_list_t *sl);

/* Function receives sorted linked list pointer,
 * erases the element in the end of the list & returns it's data.
 */
void *SlistPopBack(sorted_list_t *sl);

/* Function receives 2 sorted linked list pointers, 
 * merges them in the right order, and empty the second list.
 */
void SlistMerge(sorted_list_t *dest, sorted_list_t *src);

/* Function receives sorted linked list iterators,
 * pointer to function - action_func
 * & pointer to a parameter -  param.
 * Function runs the function on each element between from to to.
 * Returns the returned status of the action_func (0 if all succeed)
 * NOTE : if action_func returns a non zero status the function stops.
 */
int SlistForEach(sorted_list_iter_t from, sorted_list_iter_t to,
                    int (*action_func)(void *data, void *param), void *param);

/* Function receives sorted linked list pointer,
 * pointer to function - is_equal_func
 * & pointer to a parameter for matching -  param.
 * Function Returns an iterator to the first found element;
 * "bad iterator" if not found.
 * NOTE :  is_equal_func shall compare data to the given param
 *           & return 1 on equality, 0 otherwise.
 */
sorted_list_iter_t SlistFind(const sorted_list_t *sl, 
			sorted_list_iter_t from, sorted_list_iter_t to,
 			int (*is_equal_func)(const void *data,const void *param),
            void *param);
                       
#endif /* __SORTED_LIST_H__  */