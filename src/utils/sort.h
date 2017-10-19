/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Sort librar                            #################################
 *                                         ##########    ####       ########
 *  A library of sorting functions         ########  ####  ##  ###  ########
 *  arranged by complexity                 ########  ####  ##     ##########
 *  O(n^2): BubbleSort, InsertionSort,     ########  ####  ##  ###  ########
 *  SelectionSort.                         ##########    ####  ###  ######## 
 *  O(n + k): CountingSort, RadixSort.	   #################################
 *                             
 *  Bubble, Insertion and Selection functions receive a comparation      
 *  function (compar) that should return  0 if x = y 
 *           							 >0 if x > y
 *										 <0 if x < y	
 *  Counting and Radix functions receive a key generating      
 *  function that should return a key to each data member.
 *
 *  12-07-2017
 *  14:44:44
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#ifndef __SORT_H__
#define __SORT_H__

/* 
 * Bubble sort receives a pointer to the array's base, 
 * number of elements in the array, the elements size and a 
 * comparition function pointer.
 * Return values: 0 for success
 *				  1 for failure (if malloc fails).
 */
int BubbleSort(void *base, size_t num_of_elements, size_t element_size,
				int (*compar)(const void *x, const void *y));

/* 
 * Insertion sort receives a pointer to the array's base, 
 * number of elements in the array, the elements size and a 
 * comparition function pointer.
 * Return values: 0 for success
 *				  1 for failure (if malloc fails).
 */
int InsertionSort(void *base, size_t num_of_elements, size_t element_size,
				int (*compar)(const void *x, const void *y));

/* 
 * Selection sort receives a pointer to the array's base, 
 * number of elements in the array, the elements size and a 
 * comparition function pointer.
 * Return values: 0 for success
 *				  1 for failure (if malloc fails).
 */
int SelectionSort(void *base, size_t num_of_elements, size_t element_size,
				int (*compar)(const void *x, const void *y));

/* 
 * Counting sort receives a pointer to the array's base, 
 * number of elements in the array, the elements size, a 
 * comparition function pointer, arguments for users function and a range of 
 * keys.
 * Return values: 0 for success
 *				  1 for failure (if malloc fails).
 */
int CountingSort(void *base, size_t num_of_elements, size_t element_size,
				size_t (*key_to_num)(const void *element, const void *args),
				const void *args, size_t range);

/* 
 * Radix sort receives a pointer to the array's base, 
 * number of elements in the array, the elements size, a 
 * comparition function pointer, arguments for users function and the 
 * number of bytes of a key.
 * Return values: 0 for success
 *				  1 for failure (if malloc fails).
 */
int RadixSort(void *base, size_t num_of_elements, size_t element_size,
				size_t (*get_key)(const void *element, const void *args),
				const void *args, size_t num_of_bytes);

int MergeSort(void *base, size_t num_of_elements, size_t element_size,
						   int (*compar)(const void *data1, const void *data2));

int QuickSort(void *base, size_t num_of_elements, size_t element_size,
						   int (*compar)(const void *data1, const void *data2));

void *BinSearch(void *base, size_t num_of_elements, size_t element_size,
						    int (*compar)(const void *data1, const void *data2),
														  const void *req_data);

int HeapSort(void *base, size_t num_of_elements, size_t element_size,
		   int (*is_before)(const void *data1, const void *data2, void *param),
																   void *param);
										
#endif /* __SORT_H__ */

