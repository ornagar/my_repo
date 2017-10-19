/*******************************************************************************
 *  Or Nagar.
 *  Stack library.
 *  Functions declerations.
 *  07/06/17
 ******************************************************************************/
#ifndef __Stack_H__ 
#define __Stack_H__

typedef struct stack stack_t;

/*
 * Creates new stack
 * receives number and size of elements
 * returns pointer to the data struct that must be freed using StackDestroy()
 * If malloc fails the function returns a NULL pointer.
 */
stack_t *StackCreate(size_t capacity, size_t element_size);
 
/*
 * Delete all stack and the data inside 
 * and free the memory 
 */
void StackDestroy(stack_t *st);

/*
 * Push new element to the top of the stack
 * Returns 0 -> success.
 *         1 -> fail.
 */
int StackPush(stack_t *st, void *data);

/*
 * Delete the data at the top of the stack
 * Returns 0 -> success.
 *         1 -> fail.
 */
int StackPop(stack_t *st);

/*
 * Returns a const pointer to the data at the top of the stack
 * Returns NULL if stack is empty
 */
const void *StackPeek(const stack_t *st);

/*
 * Returns the number of element in the stack
 */
size_t StackSize(const stack_t *st);

/*
 * Returns the stack capacity (max element)
 */
size_t StackCapacity(const stack_t *st);

#endif /* __Stack_H__ */
