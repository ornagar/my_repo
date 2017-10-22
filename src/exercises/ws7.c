/******************************************************************************
 Worksheet 7.
 
 22.05.17
 
 Or Nagar.
*******************************************************************************/
#include <stdio.h> 		 /* puts()     */
#include <stdlib.h>		 /* Exit_success */

#define ASCII (256)
#define ESC (27)

int HandleA(void);
int HandleT(void);
int HandleEsc(void);
int HandleNothing(void);
void HandlerCreateor(void);

enum EXIT_STATUS
{
EXIT_FUNC,
EXIT_PROGRAM
};

typedef int (*func_ptr_t)(void);
func_ptr_t handle[ASCII];

int main(void)
{
	unsigned char choise;
	int quit = 0;
	
	HandlerCreateor();
	
	system("stty -icanon -echo");
	puts("Please press a key:");
	while (!quit)
	{
		choise = getchar();
		quit = handle[choise]();
	}
	
	system("stty icanon echo");
	
	return (EXIT_SUCCESS);
}

void HandlerCreateor(void)				/* creates the array for 256 funcs */
{
	int i = 0;

	for (i = 0; i < ASCII; ++i)	/* cpoints 253 pointers to HnadleNothing*/
	{
		handle[i] = HandleNothing;
	}
	
	handle['A'] = HandleA;				/* creates the func for 'A' */
	handle['T'] = HandleT;				/* creates the func for 'T' */
	handle[ESC] = HandleEsc;			/* creates the func for esc */
}



int HandleA(void)
{
	puts("A pressed");
	
	return (EXIT_FUNC);
}

int HandleT(void)
{
	puts("T pressed");
	
	return (EXIT_FUNC);
}

int HandleEsc(void)
{
	return (EXIT_PROGRAM);
}

int HandleNothing(void)
{
	puts("Nothing...");
	
	return (EXIT_FUNC);
}

