/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Heapify                                #################################
 *                                         ##########    ####       ########
 *  Functions decleration                  ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  02-08-2017                             ##########    ####  ###  ######## 
 *  14:32:23                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#ifndef __HEAPIFY_H__
#define __HEAPIFY_H__

void HeapifyDown(void *base, size_t num_element, size_t element_size,
																   size_t index,
				int (*is_before)(const void *data1, const void *data2,
																   void *param), 
																 void *param);


void HeapifyUp(void *base, size_t num_element, size_t element_size, size_t index,
			int (*is_before)(const void *data1, const void *data2, void *param), 
       			void *param);

#endif /* __HEAPIFY_H__ */
