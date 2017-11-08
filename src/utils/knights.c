/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Knights                                #################################
 *                                         ##########    ####       ########
 *  Functions definition                   ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  06-08-2017                             ##########    ####  ###  ######## 
 *  13:57:30                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <assert.h>					 /* assert()					  */
#include <string.h>

#include "knights.h"				 /* all functions declarations	  */
#include "bits_array.h"
#include "utils.h"					 /* Or's functions                */


#define ROW			(8)
#define COL 		(8)
#define BOARD_SIZE	(64)
typedef struct
{
	int x;
	int y;
	int index;
	int num_of_mooves;
}moove_t;

const int table[64] = 
{
	2, 3, 4, 4, 4, 4, 3, 2,
	3, 4, 6, 6, 6, 6, 4, 3,
	4, 6, 8, 8, 8, 8, 6, 4,
	4, 6, 8, 8, 8, 8, 6, 4,
	4, 6, 8, 8, 8, 8, 6, 4,
	4, 6, 8, 8, 8, 8, 6, 4,
	3, 4, 6, 6, 6, 6, 4, 3,
	2, 3, 4, 4, 4, 4, 3, 2
};


static void KnightsTourImp(int x, int y, size_t arr, int *status,
														 int *array, int steps);
static void FindLegalIndex(int x, int y, moove_t *moove);
static int Compare(const void *x, const void *y);

void KnightsTour(int x, int y)
{
	size_t arr = 0;
	int status = 1;
	int array[64] = {0};
	int steps = 1;
	int i = 0;
	
	assert(0 <= x && 0 <= y && 64 > x && 64 > y);

	KnightsTourImp(x, y, arr, &status, array, steps);
	
	for (i = 0; i < 64; ++i)
	{
		if (0 == i % 8)
		{
			puts("\n");
		}
		printf("[%02d] ", array[i]);
	}
	puts("\n");
	return;
}

static void KnightsTourImp(int x, int y, size_t arr, int *status, 
														  int *array, int steps)
{
	int i = 0;
	moove_t next[8];
	int index = y * 8 + x;
	
	arr = BitArrSetOn(arr, index);
	array[index] = steps++;
	
	if (BITS_ARR_IS_ALL_ON(arr))
	{
		*status = 0;
		return;
	}

	FindLegalIndex(x, y, next);
	
	for (i = 0; i < 8 && 0 != *status; ++i)
	{
		if (64 > next[i].index && BitArrIsOff(arr, next[i].index))
		{
			KnightsTourImp(next[i].x, next[i].y, arr, status, array, steps);	
		}
	}
	
	return;
}

static void FindLegalIndex(int x, int y, moove_t *moove)
{
	int i = 0;
	
	moove[0].x = x + 1;
	moove[0].y = y + 2;
	
	moove[1].x = x + 2;
	moove[1].y = y + 1;
	
	moove[2].x = x + 2;
	moove[2].y = y - 1;
	
	moove[3].x = x + 1;
	moove[3].y = y - 2;
	
	moove[4].x = x - 1;
	moove[4].y = y - 2;
	
	moove[5].x = x - 2;
	moove[5].y = y - 1;
	
	moove[6].x = x - 2;
	moove[6].y = y + 1;
	
	moove[7].x = x - 1;
	moove[7].y = y + 2;
	
	for (i = 0; i < 8; ++i)
	{
		if ((0 <= moove[i].x && 8 > moove[i].x) &&
			(0 <= moove[i].y && 8 > moove[i].y))
		{
			moove[i].index = (8 * moove[i].y) + moove[i].x ;
		}
		else
		{
			moove[i].index = 100;
		}
	}
	
	qsort(moove, 8, sizeof(moove_t), Compare);
	
	return ;
}

static int Compare(const void *x, const void *y)
{
	moove_t *i = (moove_t *)x;
	moove_t *j = (moove_t *)y;
	
	return (table[i->index] - table[j->index]);
}
