#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include "../utils/utils.h"

int main(int argc, char *argv[])
{

	char name[20];
	
	memcpy(&name, argv[1], strlen(argv[1]));
	name[strlen(argv[1])] = '\0';
	printf("%s\n", name);
	
	if (1 >= argc)
	{
		PRINT_ERROR("No argument for process to watch for.");		
		return (EXIT_FAILURE);
	}
	
	++argv;
	
	while (1)
	{
		if (0 > system(name))
		{
			PRINT_ERROR("system error");
			return (EXIT_FAILURE);
		}
	}
	
	return (EXIT_SUCCESS);
}
