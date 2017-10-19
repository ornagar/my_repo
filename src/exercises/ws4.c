/******************************************************************************
 * 19.05.17
 * Work Sheet 4.
 * Or Nagar.
 * One Sorvivor game simulation.
 *****************************************************************************/
#include <stdio.h> 		 /* printf()     */
#include <stdlib.h>		 /* Exit_success */
#include <string.h>		 /* atoi()       */
#include "utils.h"		 /* DBG          */

void OneSorvivor(int arg);

int main(int argc, char **argv)
{
	int arg = 0;
	++argv;
	
	if (*argv)
	{
	
	arg = atoi(*argv);
	OneSorvivor(arg);
	
	return (0);
	}
	else
	{
		printf("No argument found on *argv[1]: aborting...\n");
		
		return (1);
	}				
}
/*
 * A function that simulates the game of "One Sorvivor".
 */
void OneSorvivor(int arg)
{
	
	int n = arg;
	int soldiers_alive = arg;
	char *arr = NULL;
	int i = 0;

	arr = calloc(soldiers_alive, sizeof(char)); /* sets an integer array      */
	if (NULL == arr)							/* sized (*argv) parameter.   */
	{
		DBG(fprintf(stderr, "error while allocating data: aborting...\n");)
		return;
	}
	
	while (soldiers_alive > 1)					/* while there are more       */
	{											/* then one soldier alive.    */
	
		do										/* finds next living soldier. */
		{
			++i;
			if (i >= n)
			{
				i = 0;
			}
		}
		while (1 == arr[i]);					
		
		arr[i] = 1;								/* kils the soldier.          */
		--soldiers_alive;

		do										/* finds next living soldier. */
		{
			++i;
			if (i >= n)
			{
				i = 0;
			}

		}
		while (1 == arr[i]);	
	}
	printf("%d - Won The Game!\n", (i+1));
	free(arr);
}

