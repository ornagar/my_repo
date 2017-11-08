/******************************************************************************

 ******************************************************************************/
#ifndef __SINGLY_LINKED_LIST_H__ 
#define __SINGLY_LINKED_LIST_H__ 

typedef struct slist_node 
{
    void *data;
    struct slist_node *next;
} slist_node_t;

/* Create and init a single node */
slist_node_t *SolistCreateNode(void *data, slist_node_t *next);

/* Release memory of all nodes in the list */
void SolistFreeAll(slist_node_t *head);

/* Return pointer to the next element on success; NULL on failure*/
slist_node_t *SolistInsertAfter(slist_node_t *where, slist_node_t *new_node);

/* Return pointer to the previos element on success; NULL on failure*/
slist_node_t *SolistInsertBefore(slist_node_t *where, slist_node_t *new_node);

/* Return the number of elements in the list */
size_t SolistCountNodes(const slist_node_t *head);

/* 
 * is_equal_func compares each node data to the given param.
 * return pointer to the first found node; NULL if not found.
 * is_equal_func shall return 1 on equality, 0 otherwise.
 */
slist_node_t *SolistFind(const slist_node_t *head, 
					int (*is_equal_func)(const void *data, const void *param),     
					const void *param);

/* Returns NULL on success.
 * on failure of action_func, stop the iteration and returns a pointer 
 * to the failed node.
 * action_func shall return 0 on suceess; non-zero on failure.
 * param is optional. if not needed, set to NULL.
 */
slist_node_t *SolistForeach(
				slist_node_t *head,
				int (*action_func)(void *data, void *param),
				void *param);


/* Returns the removed node;  NULL on failure. No memory release */
slist_node_t *SolistRemove(slist_node_t *node);


/* Returns the removed node;  NULL on failure. No memory release */
slist_node_t *SolistRemoveAfter(slist_node_t *node);

/* Return a new head pointer to the flipped list */
slist_node_t *SolistFlip(slist_node_t *head);

/* return 1 if true, 0 if false */
int SolistHasLoop(const slist_node_t *head);

/* returns the found intersection node; NULL if not found */
slist_node_t *SolistFindIntersection(
			const slist_node_t *head1, const slist_node_t *head2);

#endif /* __SINGLY_LINKED_LIST_H__  */

