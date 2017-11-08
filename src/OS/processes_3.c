#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void Handler(int signal_num);
struct sigaction old;

int main(void)
{
	struct sigaction act;
	int counter = 0;
	
	act.sa_handler = Handler;
	act.sa_flags = SIGINT;
	sigaction(SIGINT, &act, &old);
	
	while (1)
	{
		printf("%d\n", counter++);
		sleep(2);
	}
	
	printf("\nexit normally\n");
	return (EXIT_SUCCESS);
}

void Handler(int signal_num)
{
	printf("\nin handler\n");
	sigaction(SIGINT, &old, NULL);
	raise(SIGINT);
	
	return;
}
