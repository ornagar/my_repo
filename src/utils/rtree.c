/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Rtree                                  #################################
 *                                         ##########    ####       ########
 *  Functions definition                   ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  26-07-2017                             ##########    ####  ###  ######## 
 *  11:33:14                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <assert.h>					 /* assert()					  */
#include <sys/types.h>				 /* ssize_t						  */

#include "rtree.h"					 /* all functions declerations	  */
#include "utils.h"					 /* Or's functions                */

typedef struct rtree_node node_t;

/****************************IMP STATIC FUNCS**********************************/
static node_t *InsertImp(rtree_t *tree, node_t *node, void *data, int *status);
static size_t SizeImp(node_t *node);
static void DestroyImp(node_t *node);
static node_t *RemoveImp(rtree_t *tree, node_t *node, const void *data); 
static void *FindImp(const rtree_t *tree, node_t *node, const void *data);
static int ForEachImp(node_t *node, int (*action_func)(void *data, void *arg),
																	 void *arg);
/******************************************************************************/
/*****************************STATIC FUNCS*************************************/
static size_t UpdateHeight(node_t *node);
static node_t *Balance(node_t *node);
static node_t *RotateRight(node_t *node);
static node_t *RotateLeft(node_t *node);
static node_t *FindMin(node_t *node);
static node_t *RemoveMin(node_t *node);
/******************************************************************************/

/*
 * The management struct for the AVL Tree.
 */
struct rtree
{
	node_t *root;
	int(*compare)(const void *, const void *);
	
};

/*
 * The node holds a pointer to data and is the 
 * container inside the tree.
 * Holds a pointer to left and right sons, and the height of the node
 * in the tree.
 */
struct rtree_node
{
	void *data;
	node_t *left;
	node_t *right;
	size_t height;
};

rtree_t *RTreeCreate(int(*compare)(const void *data1, const void *data2))
{
	rtree_t *tree = NULL;
	
	assert(compare);
	
	if (NULL == (tree = (rtree_t *) malloc(sizeof(rtree_t))))
	{
		PRINT_ERROR("Malloc Error");
		return (NULL);
	}
	
	tree->compare = compare;
	tree->root = NULL;
	
	return (tree);
}

void RTreeDestroy(rtree_t *tree)
{
	assert(tree);
	
	DestroyImp(tree->root);
	free(tree);
	
	return;
}

int RTreeInsert(rtree_t *tree, void *data)
{
	int status = 0;
	
	assert(tree && data);
	
	tree->root = InsertImp(tree, tree->root, data, &status);

	return (status);
}

void RTreeRemove(rtree_t *tree, const void *data)
{
	assert(tree);
	
	tree->root = RemoveImp(tree, tree->root, data);
	
	return;
}

size_t RTreeSize(const rtree_t *tree)
{
	assert(tree);
	return (SizeImp(tree->root));
}

int RTreeIsEmpty(const rtree_t *tree)
{
	assert(tree);
	return (tree->root == NULL);
}

size_t RTreeHeight(const rtree_t *tree)
{
	assert(tree);
	return (tree->root->height);
}

void *RTreeFind(const rtree_t *tree, const void *data)
{
	assert(tree && data);
	
	return (FindImp(tree, tree->root, data));
}

int RTreeForEach(rtree_t *tree, int(*action_func)(void *data, void *arg), 
																	void *arg)
{
	assert(tree && action_func);
	return (ForEachImp(tree->root, action_func, arg));
}

/****************************IMP STATIC FUNCS**********************************/
static void DestroyImp(node_t *node)
{
	if (NULL == node)
	{
		return;
	}
	
	DestroyImp(node->left);
	DestroyImp(node->right);
	free(node);
	
	return;
}

static node_t *InsertImp(rtree_t *tree, node_t *node, void *data, int *status)
{
	if (NULL == node)
	{
		if (NULL == (node = (node_t *)malloc(sizeof(node_t))))
		{
			PRINT_ERROR("malloc error");
			*status = FAILURE;
			return (node);
		}
		node->data = data;
		node->right = node->left = NULL;
		node->height = 1;
		
		return (node);
	}
	
	if (0 == tree->compare(data, node->data))
	{
		*status = WRONG_DATA;
		return (node);
	}
	else if (0 < tree->compare(data, node->data))
	{
		node->right = InsertImp(tree, node->right, data, status);
	}
	else if (0 > tree->compare(data, node->data))
	{
		node->left = InsertImp(tree, node->left, data, status);
	}
	
	
	node = Balance(node);
	
	
	return (node);
}

static node_t *RemoveImp(rtree_t *tree, node_t *node,const void *data)
{
	node_t *left = NULL;
	node_t *right = NULL;
	
	if (NULL == node)
	{
		return (NULL);
	}
	else if (0 < tree->compare(data, node->data))
	{
		node->right = RemoveImp(tree, node->right, data);
	}
	else if (0 > tree->compare(data, node->data))
	{
		node->left = RemoveImp(tree, node->left, data);
	}
	else
	{
		left = node->left;
		right = node->right;
		free(node);
		node = NULL;
		
		if (!right && !left)
		{
			return (NULL);
		}
		
		if (NULL == right)
		{
			return (Balance(left));
		}
		
		node = FindMin(right);

		node->right = RemoveMin(right);
		node->left = left;
	}
	
	return (Balance(node));
}

static size_t SizeImp(node_t *node)
{
	if (NULL == node)
	{
		return (0);
	}
	return (1 + SizeImp(node->left) + SizeImp(node->right));
}

static void *FindImp(const rtree_t *tree, node_t *node, const void *data)
{
	if (NULL == node)
	{
		return (NULL);
	}
	else if (0 < tree->compare(data, node->data))
	{
		return (FindImp(tree, node->right, data));
	}
	else if (0 > tree->compare(data, node->data))
	{
		return (FindImp(tree, node->left, data));
	}
	else
	{
		return (node->data);
	}
}

static int ForEachImp(node_t *node, int (*action_func)(void *data, void *arg),
																	  void *arg)
{
	int status = 0;
	if (NULL == node)
	{
		return (SUCCESS);
	}
	
	if (1 == (status = ForEachImp(node->left, action_func, arg)))
	{
		return(1);
	}
	if (1 == (status = action_func(node->data, arg)))
	{
		return(1);
	}
	if (1 == (status = ForEachImp(node->right, action_func, arg)))
	{
		return(1);
	}
	
	return (status);
}

/******************************STATIC FUNCS************************************/
static ssize_t Factor(node_t *node)
{
	if (node->right && node->left)
	{
		return ((ssize_t)node->right->height - (ssize_t)node->left->height);
	}
	else if (node->right)
	{
		return ((ssize_t)node->right->height);
	}
	else if (node->left)
	{
		return ((ssize_t) -node->left->height);
	}
	else
	{
		return (0);
	}
	
}
static size_t UpdateHeight(node_t *node)
{
	size_t left_height = node->left ? node->left->height : 0;
	size_t right_height = node->right ? node->right->height : 0;

	return (MAX(left_height, right_height) + 1);
}

static node_t *Balance(node_t *node)
{
	ssize_t factor = Factor(node);
	
	if (1 < factor)
	{
		if (0 > Factor(node->right))
		{
			node->right = RotateLeft(node->right);
		}
		return (RotateRight(node));
	}
	else if (-1 > factor)
	{
		if (0 < Factor(node->left))
		{
			node->left = RotateRight(node->left);
		}
		return (RotateLeft(node));
	} 
	
	node->height = UpdateHeight(node);
	return (node);
}

static node_t *RotateRight(node_t *node)
{
	node_t *pivot = node->right;
	node->right = pivot->left;
	pivot->left = node;
	
	node->height = UpdateHeight(node);
	pivot->height = UpdateHeight(pivot);
	
	return (pivot);
}
static node_t *RotateLeft(node_t *node)
{
	node_t *pivot = node->left;
	node->left = pivot->right;
	pivot->right = node;
	
	node->height = UpdateHeight(node);
	pivot->height = UpdateHeight(pivot);
	
	return (pivot);
}

static node_t *FindMin(node_t *node)
{
	return (node->left ? FindMin(node->left) : node);
}

static node_t *RemoveMin(node_t *node)
{
	if (NULL == node->left)
	{
		return (node->right);
	}
	
	node->left = RemoveMin(node->left);
	
	return (Balance(node));
}
