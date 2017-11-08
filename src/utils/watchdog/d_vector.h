/*******************************************************************************
 * Or Nagar
 * Dynamic Vector  
 *  
 * The structure will take advantage of a fixed-size array, with a counter
 * invariant that keeps track of how many elements are currently present. 
 * If the underlying array becomes exhausted, the addition operation will 
 * re-allocate the contents to a larger size, by way of a copy.
 *
 * Functions declaration
 *   
 * 08/06/17
 ******************************************************************************/
#ifndef __D_VECTOR_H__
#define __D_VECTOR_H__

typedef struct dyn_vec dyn_vec_t;

/*
 * Creates new vector
 * Receives number and size of elements
 * Returns either NULL if failed, or a unique pointer value that can
 * later be successfully passed to DynVecDestroy().
 * Allocating an array of size 0 is possible but depends 
 * on mallocs behavior.
 */
dyn_vec_t *DynVecCreate(size_t capacity, size_t element_size);
 
/*
 * Delete's vector, and free's the memory.
 */
void DynVecDestroy(dyn_vec_t *dv);

/*
 * Pushes new element to the top of the vector
 * Returns 0 -> success.
 *         1 -> fail. (no heap space)
 */
int DynVecPushBack(dyn_vec_t *dv, const void *data);

/*
 * Deletes the data at the top of the vector.
 * Returns 0 -> success.
 *         1 -> fail. (empty vector).
 */
int DynVecPopBack(dyn_vec_t *dv);

/*
 * Returns a pointer to the data in the index
 * NULL if the item index is not valid
 * index should be from 0 to (capacity - 1).
 *
 * Note:	returned address is valid as long as no further call
 *  		to PushBack, PopBack, Reserve or Destroy.
 */
void *DynVecGetItemAddres(const dyn_vec_t *dv, size_t index);

/*
 * Returns the number of elements in the vector
 */
size_t DynVecSize(const dyn_vec_t *dv);

/*
 * Returns vector's capacity (in elements)
 */
size_t DynVecCapacity(const dyn_vec_t *dv);

/*
 * Changes the capacity to the requested capacity.
 * Receives the new capacity (= number of elements)
 * and the dyn_vec_t pointer.
 *
 * Returns 0 -> success.
 *         1 -> fail. (no heap room)
 *		   2 -> fail. (if new capacity is smaller or equal
 *		   to the old capacity)
 */
int DynVecReserve(dyn_vec_t *dv, size_t capacity);

#endif	/* __D_VECTOR_H__ */
