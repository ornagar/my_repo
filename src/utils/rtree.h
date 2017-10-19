/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Rtree                                  #################################
 *                                         ##########    ####       ########
 *  Functions decleration                  ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  26-07-2017                             ##########    ####  ###  ######## 
 *  11:33:14                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#ifndef __RTREE_H__
#define __RTREE_H__

typedef enum
{
	SUCCESS,
	FAILURE,
	WRONG_DATA
}status;

typedef struct rtree rtree_t;

/*
 * Creates a recursive tree. 
 * Compare func:
 * - > 0		a > b
 * - < 0		a < b
 * - = 0		a = b
 * Will return a valid tree pointer or NULL upon failure.
 */
rtree_t *RTreeCreate(int(*compare)(const void *data1, const void *data2));

/*
 * Releases all resources of a given tree. 
 */
void RTreeDestroy(rtree_t *tree);

/*
 * Inserts the given data to the tree, at the right position.
 * Balances the tree after insertion for keeping O(n) complexity of 
 * all operations
 * 
 * Return statuses:
 * 0 - SUCCESS.
 * 1 - Memory allocation failure.
 * 2 - New data was already in the tree.
 */
int RTreeInsert(rtree_t *tree, void *data);

/*
 * Removes the node that holds the data.
 * In case data was not found nothing will be done.
 */
void RTreeRemove(rtree_t *tree, const void *data);

/*
 * Returns number of elements of the tree,
 * Complexity - O(n).
 */
size_t RTreeSize(const rtree_t *tree);

/*
 * Return 1 if the tree is empty or 0 if not.
 * Complexity - O(1). 
 */
int RTreeIsEmpty(const rtree_t *tree);

/*
 * Returns the height of the tree.
 */
size_t RTreeHeight(const rtree_t *tree);

/*
 * Function searches for data in the tree.
 * Returns a pointer to data if found or NULL if not.
 * Complexity - O(n).
 */
void *RTreeFind(const rtree_t *tree, const void *data);

/*
 * Applies an action_func on all elements of the tree. 
 * Action function should return 0 upon success and 1 upon failure. 
 * The function will also return 0 upon success.
 * In case of failure, the function will stop and return 1.
 * The function will not complete the iteration in case of failure.
 */
int RTreeForEach(rtree_t *tree, int(*action_func)(void *data, void *arg), 
																	void *arg);

#endif /* __RTREE_H__ */
