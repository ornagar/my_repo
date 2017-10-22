/*****************************************************************************
 * Or Nagar.
 * Scheduler library.
 * Test file.
 * 27/06/17
 ****************************************************************************/
#include <stdio.h>			/* printf()			*/
#include <stdlib.h>			/* EXIT_SUCCESS		*/
#include <unistd.h>
#include <time.h>
#include "scheduler_task.h"


int main(void)
{
	size_t err_sum = 5;

	err_sum += 5;

	if (0 == err_sum)
	{
		puts("\nScheduler TEST SUCCESS!!\n");
	}
	else
	{
		printf("\nfound %lu bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

