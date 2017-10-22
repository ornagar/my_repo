/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Binary Search Tree.                    #################################
 *                                         ##########    ####       ########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  17-07-2017                             ########  ####  ##     ##########
 *  11:18:13                               ########  ####  ##  ###  ########
 *                                         ##########    ####  ###  ######## 
 *                                         #################################
 * Specieal notes:
 *  1. Searching the tree is with O(log(n)) complexity.
 *	2. Finding a minimum / maximum with O(h) complexity (h is the tree hight)
 *  3. WARNING Remove function may corrupt any iterator 
 *     given in previous functions. 
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#ifndef __BST_H__
#define __BST_H__

typedef struct bst  bst_t;
typedef struct bst_node bst_node_t;

typedef struct bst_iter
{
	bst_node_t *node;
	bst_t  *bst;
} bst_iter_t;
 
/*
 * This function will create a new BST
 * inputs: 
 * 1. user compare function with return values:
 * 			> 0 for a > b
 * 			< 0 for a < b
 * 			= 0 for a = b
 * 2. optional parameter for the compare function.
 * 
 * BSTCreate return value:
 * 1. NULL - for failure.
 * 2. a valid BST pointer for success.
 */
bst_t *BSTCreate(int (*compare_func)(const void *d1,
					  const void *d2, void *param)
					 , void *param);
/*
 * Release the memory for a given BST. 
 */
void BSTDestroy(bst_t *tree);

/*
 * Insert a given data pointer to the right place in a given tree
 * - returns values: 
 * 				1. valid iterator to the created node.
 * 				2. bad iterator in case of failue.
 * NOTE: it is the user's responsibility to check the return value 
 * 		(using BSTIsBadIterator)  
 */
bst_iter_t BSTInsert(bst_t *tree, void *data);

/* 
 * Remove node and release its resources.
 * function returns a pointer to the data of the removed node.
 * WARNING Remove function may corrupt any iterator given in previous functions,
 */
void *BSTRemove(bst_iter_t iter);

/* 
 * function returns a pointer to the data of a given iterator.
 */
void *BSTGetData(const bst_iter_t iter);

/*
 * Return the number of nodes in a given BST.
 */
size_t BSTCount(const bst_t *tree);


/*
 * Checks if the given tree is empty. 
 * Returns boolean value: 1 true, 0 false.
 */
int BSTIsEmpty(const bst_t *tree);

/*
 * Return an iterator to the first node 
 */
bst_iter_t BSTBegin(const bst_t *tree);

/*
 * Return an iterator to the node after the last node
 */
bst_iter_t BSTEnd(const bst_t *tree);

/*
 * Returns an iterator to the node before a given node.
 * Will return bad iterator if there is no previous node.
 */
bst_iter_t BSTPrev(const bst_iter_t iter);

/*
 * Returns an iterator to the node after a given node.
 * Will return bad iterator if there is no next node.
 */
bst_iter_t BSTNext(const bst_iter_t iter);

/* 
 * Checks if a given iterator is valid, 
 * Return boolean value: 1 non-valid, 0 valid 
 */
int BSTIsBadIterator(const bst_iter_t iter);

/* 
 * Check if two iterators are the same, 
 * Return boolean value: 1 true, 0 false 
 */
int BSTIsSameIterator(const bst_iter_t iter1, const bst_iter_t iter2);

/*
 * Returns the node with the max value in a given tree.
 */
bst_iter_t BSTMax(const bst_t *tree);

/* 
 * This function will search a given tree using a user defined func.
 * "is_equal_func" compares each key in the range of "from -> to" 
 * to the given param.
 * Returns a pointer to the found node or bad iterator if not found.
 * "is_equal_func" shall return 1 on equality, 0 otherwise.
 */
bst_iter_t BSTFind(const bst_t *tree, const void *data);
/* 
 * Runs "action_func" in the range of "from -> to".
 * On failure of action_func, stop the iteration and returns a failure status 
 * action_func shall return 0 on suceess and non-zero on failure.
 * Param is optional. If not needed, set to NULL.
 * 
 * NOTE: it is the user's responsibility not to change fileds 
 * 		 related to compare_func
 */
int BSTForEach(const bst_iter_t from, const bst_iter_t to,
					int (*action_func)(const void *data, const void *param),     
					const void *param);

#endif /* __BST_H__ */
