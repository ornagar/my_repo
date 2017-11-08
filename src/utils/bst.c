/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Bst                                    #################################
 *                                         ##########    ####       ########
 *  Functions definition                   ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  17-07-2017                             ##########    ####  ###  ######## 
 *  11:18:13                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <assert.h>					 /* assert()					  */
#include <time.h>					 /* time_t						  */

#include "bst.h"					 /* all functions declerations	  */
#include "utils.h"					 /* Or's functions                */

enum 
{
	SUCCESS, 
	FAIL
};

enum 
{
	LEFT,   
	RIGHT
};

enum 
{
	HAS_LEFT_CHILD, 
	HAS_RIGHT_CHILD, 
	HAS_NONE, 
	HAS_BOTH
};

/*
 * struct to hold a node in the btree.
 */
struct bst_node
{
	bst_node_t *parent;
	bst_node_t *children[2];
	void		*data;
};

/*
 * Management struct for the Binary search tree.
 */
struct bst
{
	bst_node_t stub;
	int (*compare_func)(const void *d1, const void *d2, void *param);
	void *param;
};

/****************************STATIC FUNCS**************************************/
static bst_iter_t RunLeft(bst_iter_t iter);
static bst_iter_t RunRight(bst_iter_t iter);
static int ChildrenStatus(bst_iter_t iter);
static int WhichChildAmI(bst_iter_t iter);
/******************************************************************************/

bst_t *BSTCreate(int (*compare_func)(const void *d1,
					  const void *d2, void *param)
					 , void *param)
{
	bst_t *bst = NULL;

	assert(compare_func);

	if (NULL == (bst = malloc(sizeof(bst_t))))
	{
		MALLOC_ERROR;
		return(NULL);
	}
	bst->compare_func = compare_func;
	bst->param = param;

	bst->stub.data = DEADBEEF;
	bst->stub.parent = DEADBEEF;

	bst->stub.children[RIGHT] = DEADBEEF;
	bst->stub.children[LEFT] = NULL;

	return(bst);
}

void BSTDestroy(bst_t *tree)
{
	bst_iter_t runner = {NULL};
	bst_iter_t temp = {NULL};
	int child = 0;
	
	assert(tree);

	temp.bst = tree;
	runner.bst = tree;
	runner.node = &tree->stub;

	while (!BSTIsEmpty(tree))
	{
		if (HAS_NONE != ChildrenStatus(runner))
		{
			runner = RunLeft(runner);
			runner = RunRight(runner);
		}
		else
		{
			temp.node = runner.node;
			runner.node = runner.node->parent;
			
			child = WhichChildAmI(temp);
			temp.node->parent = NULL;
			runner.node->children[child] = NULL;
			
			free(temp.node);
			temp.node = NULL;
		}
	}

	free(tree);
	return;
}

bst_iter_t BSTInsert(bst_t *tree, void *data)
{
	bst_iter_t iter = {NULL};
	int child = LEFT;
	int status = 0;

	assert(tree && data);

	iter.bst = tree;
	iter.node = &tree->stub;

	while (NULL != iter.node->children[child])
	{
		iter.node = iter.node->children[child];
		status = tree->compare_func(data, iter.node->data, tree->param);

		if (0 < status)
		{
			child = RIGHT;
		}
		else if (0 > status)
		{
			child = LEFT;
		}
		else
		{
			return(BSTEnd(tree));
		}
	}

	if (NULL == (iter.node->children[child] = malloc(sizeof(bst_node_t))))
	{
		MALLOC_ERROR;
		return(BSTEnd(tree));
	}

	iter.node->children[child]->parent = iter.node;
	iter.node = iter.node->children[child];
	iter.node->children[LEFT] = NULL;
	iter.node->children[RIGHT] = NULL;
	iter.node->data = data;
	
	return(iter);
}

void *BSTRemove(bst_iter_t iter)
{
	bst_iter_t temp = {NULL};
	int my_child = 0;
	int i_am = 0;
	void *return_data = iter.node->data;

	if (BSTIsBadIterator(iter))
	{
		return(NULL);
	}

	temp.bst = iter.bst;
	my_child = ChildrenStatus(iter);
	i_am = WhichChildAmI(iter);

	/* If iter has both children - find next, swap data, point from iter
	 * parent to iter child and continue 
	 * (check if new node has one or no children)
	 */
	if (HAS_BOTH == my_child)
	{
		temp = BSTNext(iter);
		iter.node->data = temp.node->data;
		iter.node = temp.node;

		my_child = ChildrenStatus(iter);
		i_am = WhichChildAmI(iter);
	}

	temp.node = iter.node->parent;

	/* If iter has no children, remove node */
	if (HAS_NONE == my_child)
	{
		temp.node->children[i_am] = NULL;
		iter.node->parent = NULL;
		iter.node->data = NULL;
		free(iter.node);
		iter.node = NULL;

		return(return_data);
	}
	/* If iter has one children,
	 * point from iter parent to iter child (and vice versa) and remove it 
	 */
	else if (HAS_NONE != my_child)
	{
		temp.node->children[i_am] = iter.node->children[my_child];
		iter.node->children[my_child]->parent = temp.node;
	
		iter.node->parent = NULL;
		iter.node->data = NULL;
		iter.node->children[LEFT] = NULL;
		iter.node->children[RIGHT] = NULL;
		free(iter.node);
		iter.node = NULL;

		return(return_data);
	}

	return(NULL);
}

void *BSTGetData(const bst_iter_t iter)
{	
	return(iter.node->data);
}

size_t BSTCount(const bst_t *tree)
{
	bst_iter_t iter = {NULL};
	size_t counter = 0;

	assert(tree);

	iter = BSTBegin(tree);

	while (!BSTIsBadIterator(iter))
	{
		++counter;
		iter = BSTNext(iter);
	}

	return(counter);
}

int BSTIsEmpty(const bst_t *tree)
{
	assert(tree);

	return(NULL == tree->stub.children[LEFT]);
}

bst_iter_t BSTBegin(const bst_t *tree)
{
	bst_iter_t iter = {NULL};

	assert(tree);

	iter = BSTEnd(tree);

	while(NULL != iter.node->children[LEFT])
	{
		iter.node = iter.node->children[LEFT];
	}

	return(iter);
}

bst_iter_t BSTEnd(const bst_t *tree)
{
	bst_iter_t iter = {NULL};

	assert(tree);

	iter.bst = (bst_t *)tree;
	iter.node = (bst_node_t *)&tree->stub;

	return(iter);
}

bst_iter_t BSTPrev(const bst_iter_t iter)
{
	bst_iter_t runner = iter;

	if (BSTIsSameIterator(iter, BSTBegin(iter.bst)))
	{
		return(BSTEnd(iter.bst));
	}

	if (HAS_LEFT_CHILD == ChildrenStatus(runner) || 
		HAS_BOTH == ChildrenStatus(runner))
	{
		runner.node = runner.node->children[LEFT];
		return(RunRight(runner));
	}
	else
	{
		while (LEFT == WhichChildAmI(runner))
		{
			runner.node = runner.node->parent;
		}

		runner.node = runner.node->parent;
		return(runner);
	}
}

bst_iter_t BSTNext(const bst_iter_t iter)
{
	bst_iter_t runner = iter;

	if (HAS_RIGHT_CHILD == ChildrenStatus(runner) || 
		HAS_BOTH == ChildrenStatus(runner))
	{
		runner.node = runner.node->children[RIGHT];
		return(RunLeft(runner));
	}
	else
	{
		while (LEFT != WhichChildAmI(runner))
		{
			runner.node = runner.node->parent;
		}
		
		runner.node = runner.node->parent;
		return(runner);
	}
}

int BSTIsBadIterator(const bst_iter_t iter)
{
	return(DEADBEEF == iter.node->data);
}

int BSTIsSameIterator(const bst_iter_t iter1, const bst_iter_t iter2)
{
	return(iter1.node == iter2.node);
}

bst_iter_t BSTMax(const bst_t *tree)
{
	bst_iter_t iter = {NULL};

	assert(tree);

	if (BSTIsEmpty(tree))
	{
		return(BSTEnd(tree));
	}

	iter.bst = (bst_t *)tree;
	iter.node = tree->stub.children[LEFT];

	while(NULL != iter.node->children[RIGHT])
	{
		iter.node = iter.node->children[RIGHT];
	}

	return(iter);
}

bst_iter_t BSTFind(const bst_t *tree, const void *data)
{
	bst_iter_t iter = {NULL};
	int compare_status = 0;

	assert(tree && data);

	iter.bst = (bst_t *)tree;
	iter.node = ((bst_t *)tree)->stub.children[LEFT];

	while (NULL != iter.node)
	{
		compare_status = tree->compare_func(data, iter.node->data, tree->param);

		if (0 < compare_status)
		{
			iter.node = iter.node->children[RIGHT];
		}
		else if (0 > compare_status)
		{
			iter.node = iter.node->children[LEFT];
		}
		else
		{
			return(iter);
		}
	}

	return(BSTEnd(tree));
}


int BSTForEach(const bst_iter_t from, const bst_iter_t to,
					int (*action_func)(const void *data, const void *param),     
					const void *param)
{
	bst_iter_t runner = {NULL};
	int status = SUCCESS;

	assert(action_func);

	runner.bst = from.bst;
	runner.node = from.node;

	while (runner.node != to.node)
	{
		status = action_func(runner.node->data, param);
		if (SUCCESS != status)
		{
			break;
		}

		runner = BSTNext(runner);
	}

	return(status);
}


static bst_iter_t RunLeft(bst_iter_t iter)
{
	assert(iter.bst && iter.node);

	while(NULL != iter.node->children[LEFT])
	{
		iter.node = iter.node->children[LEFT];
	}

	return(iter);
}

static bst_iter_t RunRight(bst_iter_t iter)
{
	assert(iter.bst && iter.node);

	while(NULL != iter.node->children[RIGHT])
	{
		iter.node = iter.node->children[RIGHT];
	}

	return(iter);
}

static int ChildrenStatus(bst_iter_t iter)
{
	if (NULL != iter.node->children[LEFT] && 
		NULL == iter.node->children[RIGHT])
	{
		return(HAS_LEFT_CHILD);
	}
	else if (NULL == iter.node->children[LEFT] && 
		     NULL != iter.node->children[RIGHT])
	{
		return(HAS_RIGHT_CHILD);
	}
	else if (NULL == iter.node->children[LEFT] && 
		     NULL == iter.node->children[RIGHT])
	{
		return(HAS_NONE);
	}
	/* If both children are != NULL */
	return(HAS_BOTH);	
}

static int WhichChildAmI(bst_iter_t iter)
{
	if (iter.node->parent->children[LEFT] == iter.node)
	{
		return(LEFT);
	}
	else
	{
		return(RIGHT);
	}
}
