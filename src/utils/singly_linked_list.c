/*****************************************************************************
 *  Or Nagar.
 *  Singly Linked List library.
 *  Functions definition.
 *  12/06/17
 ****************************************************************************/
#include <stdlib.h>					/* malloc()		*/
#include <assert.h>					/* assert()		*/

#include "utils.h"					/* MALLOC_ERROR	*/
#include "singly_linked_list.h"					


slist_node_t *SolistCreateNode(void *data, slist_node_t *next)
{
	slist_node_t *node = NULL;
	
	if (NULL == (node = malloc(sizeof(slist_node_t))))
	{
		MALLOC_ERROR;
		
		return (NULL);
	}
	
	node->data = data;
	node->next = next;
	
	return (node);
}

void SolistFreeAll(slist_node_t *head)
{
	slist_node_t *runner = NULL;
	
	assert(head);
	
	runner = head;
	
	while (NULL != head)
	{
		runner = runner->next;
		free(head);
		head = runner;
	}
	
	return;
}

slist_node_t *SolistInsertAfter(slist_node_t *where, slist_node_t *new_node)
{
	assert(where && new_node);
	
	new_node->next = where->next;
	where->next = new_node;
	
	return (new_node);
}

slist_node_t *SolistInsertBefore(slist_node_t *where, slist_node_t *new_node)
{
	void *temp_data = NULL;
	
	
	assert(where && new_node);
	
	new_node->next = where->next;
	where->next = new_node;
	
	temp_data = where->data;
	where->data = new_node->data;
	new_node->data = temp_data;
	
	return (where);
}

size_t SolistCountNodes(const slist_node_t *head)
{
	size_t count = 0;
	
	while (NULL != head)
	{
		++count;
		head = head->next;
	}
	
	return (count);
}

slist_node_t *SolistFind(const slist_node_t *head, 
					int (*is_equal_func)(const void *data, const void *param),
					const void *param)
{
	assert(head && is_equal_func);
	
	while (NULL != head)
	{
		if(is_equal_func(head->data, param))
		{
			return ((slist_node_t *)head);
		}
		else
		{
			head = head->next;
		}
	}
	
	return ((slist_node_t *)head);
}

slist_node_t *SolistForeach(
				slist_node_t *head,
				int (*action_func)(void *data, void *param),
				void *param)
{
	assert(head && action_func);
	
	while (NULL != head)
	{
		if(0 == action_func(head->data, param))
		{
			head = head->next;
		}
		else
		{
			return (head);
		}
	}
	
	return (head);
}

slist_node_t *SolistRemove(slist_node_t *node)
{
	slist_node_t temp;
	assert(node);
	
	if (NULL == node->next)
	{
		return (NULL);	
	}
	
	temp.data = node->data;
	temp.next = node->next;
	
	node->data = node->next->data;
	node->next = node->next->next;
	
	temp.next->data = temp.data;
	temp.next->next = NULL;
	
	return (temp.next);
}

slist_node_t *SolistRemoveAfter(slist_node_t *node)
{
	slist_node_t *temp = NULL;
	
	assert(node);
	
	temp = node->next;
	
	if (NULL == temp)	
	{
		return (NULL);	
	}
	
	node->next = node->next->next;
	temp->next = NULL;
	
	return (temp);
}

slist_node_t *SolistFlip(slist_node_t *head)
{
	slist_node_t *runner1 = head->next;
	
	slist_node_t *runner2 = head->next->next;
	
	assert(head);
	
	head->next = NULL;
	
	while (NULL != runner2)
	{
		runner1->next = head;
		
		head = runner1;
		runner1 = runner2;
		runner2 = runner2->next;
	}
		runner1->next = head;
		return (head);
}

int SolistHasLoop(const slist_node_t *head)
{
	slist_node_t *runner = NULL;
	int i = 0;
	
	assert(head);
	
	runner = head->next;

	while (runner)
	{
		head = head->next;
		
		for (i = 0; i < 2; ++i)			/* runner makes two steps every time */
		{
			runner = runner->next;
			if (runner == head)
			{
				return (1);
			}
		}
	}
	
	return (0);
}


slist_node_t *SolistFindIntersection(
			const slist_node_t *head1, const slist_node_t *head2)
{
	size_t count1 = 0;
	size_t count2 = 0;
	
	assert(head1 && head2);
	
	count1 = SolistCountNodes(head1);
	count2 = SolistCountNodes(head2);

	if (count1 > count2)		  /* Advance with the pointer of longer list */
	{
		count1 -= count2;		
		while (count1--)		
		{
			head1 = head1->next;
		}
	}
	else
	{
		count2 -= count1;
		while (count2--)
		{
			head2 = head2->next;
		}
	}
	
	while (NULL != head1)		
	{
		if (head1 == head2)
		{
			return ((slist_node_t *)head1);
		}
		
		head1 = head1->next;
		head2 = head2->next;
	}
	
	return (NULL);
}
