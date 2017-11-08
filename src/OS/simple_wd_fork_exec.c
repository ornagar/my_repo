#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "../utils/utils.h"

void Handler(int signal_num);

int main(int argc, char *argv[])
{
	pid_t child = 0;
	int child_status = 0;
	struct sigaction act;
	act.sa_handler = Handler;

	sigaction(SIGINT, &act, NULL);
	
	if (1 >= argc)
	{
		PRINT_ERROR("No argument for process to watch for.");		
		return (EXIT_FAILURE);
	}
	
	++argv;
	
	while (1)
	{
		
		child = fork();
		if (0 > child)
		{
			PRINT_ERROR("fork error");
			return (EXIT_FAILURE);
		}
		
		if (0 == child)
		{
			if (0 > execvp(argv[0], argv))
			{
				PRINT_ERROR("execvp error");
				return (EXIT_FAILURE);
			}
		}
		
		if (0 > wait(&child_status))
		{
			PRINT_ERROR("wait error");
			return (EXIT_FAILURE);
		}
		kill(child, SIGKILL);
	}
	
	return (EXIT_SUCCESS);
}

void Handler(int signal_num)
{
	printf("\nin handler\n");
	
	return;
}
