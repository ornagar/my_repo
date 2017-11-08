/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Dhcp                                   #################################
 *                                         ##########    ####       ########
 *  Functions definition                   ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  09-08-2017                             ##########    ####  ###  ######## 
 *  13:51:54                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <assert.h>					 /* assert()					  */
#include <string.h>

#include "dhcp.h"					 /* all functions declerations	  */
#include "utils.h"					 /* Or's functions                */

#define BITS_IN_BYTE 		(8)
#define TOTAL_BITS			(32)

/* Children side enum */
enum
{
	LEFT,
	RIGHT
};

/*
 * The node struct contains a pointer to parent node and
 * both children nodes, also contains a boolean is_occupied field.
 */
typedef struct node
{
    struct node *parent;
    struct node *children[2];
    int is_occupied;
} node_t;

/*
 * The management struct for the trie, holds the subnet_addr,
 * the number of dynamic bits in an ip address, and a pointer to the trie's root
 */
struct dhcp
{
    int dyn_bits;
    ip_t subnet_addr;
    node_t *root;
};

/*********************************STATIC FUNCTIONS*****************************/
/* Creates a new node and connect with parent. */
static node_t *NodeCreate(node_t *parent);

/* Checks if the requested ip address is legal. */
static int IsLegalIp(dhcp_t *trie, ip_t request);

static void DHCPDestroyIMP(node_t *current);

/* Creates a bit array for iterating on the trie purpuses. */
static unsigned long CreateBitArr(dhcp_t *trie, ip_t request);

static void TurnOcupationOn(dhcp_t *trie, node_t *current);
static void TurnOcupationOff(dhcp_t *trie, node_t *current);

/* Finds the requested ip in the trie and returns a pointer to last node */
static node_t *FindRoute(dhcp_t *trie, ip_t addr, dhcp_status_t *status);

/* Copies the result given in the FindRoute to the result ip_t struct */
static void SaveResult(dhcp_t *trie, unsigned long temp_result, ip_t *result);

/* 
 * The main static function in allocating a new address.
 * It iterates throw the trie in order to find and allocate the right ip
 */
static dhcp_status_t FindAndInsert(unsigned long request, dhcp_t *trie, 
														 unsigned long *result);
/******************************************************************************/

/********************************LIBRARY FUNCTIONS*****************************/
dhcp_t *DHCPCreate(ip_t subnet_addr, int static_bits)
{
	dhcp_t *trie = NULL;
	ip_t result = {{0}};
	ip_t temp = {{0}};
	
	int i = 0;
	int dyn_bytes = N_BYTES - (static_bits / BITS_IN_BYTE);
	
	while (i < dyn_bytes)
	{
		if (0 != subnet_addr.byte[N_BYTES - dyn_bytes])
		{
			return (NULL);
		}
		--dyn_bytes;
	}
	
	if (NULL == (trie = (dhcp_t *)malloc(sizeof(dhcp_t))))
	{
		PRINT_ERROR("malloc error");
		return (NULL);
	}
	
	if (NULL == (trie->root = NodeCreate(NULL)))
	{
		PRINT_ERROR("NodeCreate error");
		free(trie);
		return(NULL);
	}
	
	trie->subnet_addr = subnet_addr;
	trie->dyn_bits = TOTAL_BITS - static_bits;
	
	dyn_bytes = N_BYTES - (static_bits / BITS_IN_BYTE);
	memcpy(&temp, &trie->subnet_addr, sizeof(ip_t));
	memset(&temp.byte[N_BYTES - dyn_bytes], 0xff, dyn_bytes);

	DHCPAllocIp(trie, subnet_addr, &result);
	DHCPAllocIp(trie, temp, &result);
	
	temp.byte[N_BYTES - 1] ^= 1;
	DHCPAllocIp(trie, temp, &result);
	
	return (trie);
}

void DHCPDestroy(dhcp_t *trie)
{
	if (NULL != trie)
	{
		DHCPDestroyIMP(trie->root);
		free(trie);
	}
	
	return;
}

dhcp_status_t DHCPAllocIp(dhcp_t *trie, ip_t request, ip_t *result)
{
	dhcp_status_t status1 = DHCP_OK;
	dhcp_status_t status2 = DHCP_OK;
	unsigned long temp = 0;
	unsigned long new_ip = 0;
	unsigned long res = 0;

	assert(trie);
	
	status1 = IsLegalIp(trie, request);
	temp = CreateBitArr(trie, request);
	
	if (DHCP_ADDR_ILLEGAL == status1)
	{

		status2 = FindAndInsert(new_ip, trie, &res);
	}
	else
	{
		status2 = FindAndInsert(temp, trie, &res);
	}
	
	SaveResult(trie, res, result);

	return (MAX(status1, status2));
}

dhcp_status_t DHCPFreeIp(dhcp_t *trie, ip_t addr)
{
	int static_bytes = 0;
	int i = 0;
	node_t *current = NULL;
	dhcp_status_t status = DHCP_OK;
	ip_t b_cast = {{190, 1, 255, 255}};
	ip_t dhcp = {{190, 1, 255, 254}};
	
	assert(trie);
	
	current = trie->root;
	
	static_bytes = N_BYTES - (trie->dyn_bits / BITS_IN_BYTE);
	
	if (0 == memcmp(&addr, &trie->subnet_addr, N_BYTES) ||
		0 == memcmp(&addr, &b_cast, N_BYTES) 		    ||
		0 == memcmp(&addr, &dhcp, N_BYTES))
	{
		return (DHCP_ADDR_ILLEGAL);
	}
	
	while (i < static_bytes)
	{
		if (addr.byte[i] != trie->subnet_addr.byte[i])
		{
			return (DHCP_ADDR_NOT_EXIST);
		}
		++i;
	}
	
	current = FindRoute(trie, addr, &status);
	
	if (DHCP_OK == status)
	{
		TurnOcupationOff(trie, current);
	}
	
	return (status);
}
/******************************************************************************/

/*********************************STATIC FUNCTIONS*****************************/
static node_t *NodeCreate(node_t *parent)
{
	node_t *new = NULL;
	
	if (NULL == (new = (node_t *)calloc(sizeof(node_t), 1)))
	{
		PRINT_ERROR("malloc error");
		return (NULL);
	}
	
	new->parent = parent;
	
	return (new);
}

static int IsLegalIp(dhcp_t *trie, ip_t request)
{
	ip_t temp = {{0}};
	int i = 0;
	
	while (i < (N_BYTES - (trie->dyn_bits / BITS_IN_BYTE)))
	{
		temp.byte[i] = request.byte[i];
		if (temp.byte[i] != trie->subnet_addr.byte[i])
		{
			return (DHCP_ADDR_ILLEGAL);
		}
		++i;
	}
	
	
	return (DHCP_OK);
}

static unsigned long CreateBitArr(dhcp_t *trie, ip_t request)
{
	unsigned long req_cpy = 0;
	unsigned long temp = 0;
	unsigned char mask = 1;
	unsigned char *cpy_ptr = (unsigned char *)&req_cpy;
	int dyn_bytes = 0;
	int dyn_bits = 0;
	int count = 1;
	
	assert(trie);

	dyn_bits = trie->dyn_bits;
	dyn_bytes = dyn_bits / BITS_IN_BYTE;

	while (dyn_bytes--)
	{
		*cpy_ptr = request.byte[N_BYTES - count++];
		++cpy_ptr;
	}
	
	while (dyn_bits--)
	{
		temp <<= 1;
		temp |= req_cpy & mask;
		req_cpy >>= 1;
	}
	
	return (temp);
}


static dhcp_status_t FindAndInsert(unsigned long request, dhcp_t *trie, 
														  unsigned long *result)
{
	int level = 0;
	int mask = 1;
	unsigned long bit = 0;
	int fixed_bit = 0;
	node_t *current = trie->root;
	dhcp_status_t status = DHCP_OK;
	
	/* Check if all addresses are taken */
	if (trie->root->is_occupied)
	{
		return (DHCP_ALL_ADDR_TAKEN);
	}
	
	/* Find the requested address */
	while (level++ < trie->dyn_bits)
	{
		bit = request & mask;
		if (NULL == current->children[bit])
		{
			if (NULL == (current->children[bit] = NodeCreate(current)))
			{
				return (DHCP_ALLOC_ERROR);
			}
		}
		else if (current->children[bit]->is_occupied)
		{
			status = DHCP_ADDR_TAKEN;
			fixed_bit = bit;
			--level;
			break;
		}	
		
		current = current->children[bit];
		*result <<= 1;
		*result |= bit;
		request >>= 1;
	}
	
	/* If requested address is taken find the closest address to it (closest in
	 * tree does not meen for shure it will be the closest in number).
	 */
	while (level++ < trie->dyn_bits)
	{
		bit = fixed_bit;
		if (NULL == current->children[fixed_bit])
		{
			if (NULL == (current->children[bit] = NodeCreate(current)))
			{
				return (DHCP_ALLOC_ERROR);
			}
		}
		else if (current->children[fixed_bit]->is_occupied)
		{
			bit = fixed_bit ^ mask;
			if (NULL == current->children[bit])
			{
				if (NULL == (current->children[bit] = NodeCreate(current)))
				{
					return (DHCP_ALLOC_ERROR);
				}
			}
		}

		current = current->children[bit];
		*result <<= 1;
		*result |= bit;
	}
	
	current->is_occupied = 1;
	
	TurnOcupationOn(trie, current->parent);
	
	return (status);
}

static void TurnOcupationOn(dhcp_t *trie, node_t *current)
{
	while (NULL != current)
	{
		if (current->children[LEFT] && current->children[RIGHT])
		{
			if (current->children[LEFT]->is_occupied &&
				current->children[RIGHT]->is_occupied)
			{
				current->is_occupied = 1;
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
		
		current = current->parent;
	}
	
	return;
}

static void TurnOcupationOff(dhcp_t *trie, node_t *current)
{
	while (NULL != current && current->is_occupied)
	{
		current->is_occupied = 0;
		current = current->parent;
	}
	
	return;
}

static void SaveResult(dhcp_t *trie, unsigned long temp_result, ip_t *result)
{
	int i = 0;
	int dyn_bytes = trie->dyn_bits / BITS_IN_BYTE;
	unsigned char *cpy_ptr = (unsigned char *)(&temp_result);
	cpy_ptr += dyn_bytes;
	
	while (i < N_BYTES - dyn_bytes)
	{
		result->byte[i] = trie->subnet_addr.byte[i];
		++i;
	}

	while (i < N_BYTES)
	{
		--cpy_ptr;
		result->byte[i++] = *cpy_ptr;
	}
	
	return;
}

static void DHCPDestroyIMP(node_t *current)
{
	if (NULL == current)
	{
		return;
	}
	
	DHCPDestroyIMP(current->children[LEFT]);
	DHCPDestroyIMP(current->children[RIGHT]);
	free(current);
	
	return;
}

static node_t *FindRoute(dhcp_t *trie, ip_t addr, dhcp_status_t *status)
{
	int level = 0;
	int mask = 1;
	int bit = 0;
	node_t *current = trie->root;
	unsigned long bit_arr = CreateBitArr(trie, addr);

	while (level++ < trie->dyn_bits)
	{
		bit = bit_arr & mask;
		
		if (NULL == current->children[bit])
		{
			*status = DHCP_ADDR_NOT_EXIST;
			return (NULL);
		}
		else
		{
			current = current->children[bit];
		}
		bit_arr >>= 1;
	}
	
	*status = DHCP_OK;
	return (current);
}
/******************************************************************************/
