/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Heap                                   #################################
 *                                         ##########    ####       ########
 *  Functions decleration                  ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  02-08-2017                             ##########    ####  ###  ######## 
 *  14:30:43                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#ifndef __HEAP_H__
#define __HEAP_H__

typedef struct heap heap_t;

/* 
 * Create new heap.
 * Return NULL if faild.
 * * NOTE: is_before shall compare data1 to data2
 *       & return 1 if data1 is bigger, 0 otherwise.
 */
heap_t *HeapCreate(size_t element_size, int (*is_before)(const void *data1, 
								  const void *data2, void *param), void *param);
/*
 * Delete Heap, and free its resource.
 */
void HeapDestroy(heap_t *hp);

/* 
 * Remove the element with the highest value
 * on top of the Heap, and return its data.
 * Complexity: O(log n) 
 */
void HeapPop(heap_t *hp);

/* 
 * Function receives Heap pointer & pointer to data
 * Function inserts the data in the rigth place.
 * Function returns status: failure will return '1' otherwise '0'.
 * Complexity: O(log n) 
 */
int HeapPush(heap_t *hp, void *data);

/* 
 * Return pointer to the data of the element with the highest value
 * on top of the Heap
 * If the heap is empty- return NULL
 * Complexity: O(1) 
 */
void *HeapTop(heap_t *hp);

/* 
 * Find and remove the data from the Heap
 */
int HeapRemove(heap_t *hp, void *data, void *to_remove,
						 int (*cmp_func)(const void *data1, const void *data2));

/* 
 * Function receives Heap pointer.
 * Return it's size.
 * Complexity: O(1) 
 */
size_t HeapSize(heap_t *hp);
/*
 * Function receives Heap pointer.
 * Returns the Heap capacity (current allocated space)
 * Complexity: O(1) 
 */
size_t HeapCapacity(heap_t *hp);

#endif /* __HEAP_H__ */
