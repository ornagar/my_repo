/******************************************************************************
 ws5_main.c test the functions of work sheet 5.
 
 22.05.17
 
 Or Nagar.
*******************************************************************************/
#include <stdio.h> 		 /* printf()     */
#include <stdlib.h>		 /* Exit_success */
#include <string.h>		 /* strcmp		 */

#include "ws2_string.h"	 /* RmSpaces()   */
#include "ws5_funcs.h"	 /* HandleAppend */

#define HANDLE_SIZE ((sizeof(handle)) / (sizeof(HANDLER)))
#define LINE_SIZE (100)
typedef struct 
{
	char str[10];
	int (*func_ptr)(char*, char*);
} HANDLER;

static const HANDLER handle[] = 
{
	{"-exit",   HandleExit		},
	{"-count",  HandleCount		},
	{"-remove", HandleRemove	},
	{"<", 		HandlePreppend	},
	{"*", 		HandleAppend	}
};

int main(int argc, char **argv)
{
	char buffer[LINE_SIZE];
	int quit = 0;
	int i = 0;
	char *name;
	
	++argv;
	
	if (*argv)
	{
		name = *argv;
	}
	else
	{
		name = "default.txt";
			
		printf("no name found in argument[1],"
		"\nfiles name: \"default.txt\"\n");	
	}
	
	while (1 != quit)
	{
		printf("Please enter your string:\n");
		fgets(buffer,LINE_SIZE, stdin);
		
		i = 0;
		
		while (i < HANDLE_SIZE)
		{
			if  ((0 == strcmp(buffer, handle[i].str)) || 
				(('<' == (buffer[0]) && '<' == (handle[i].str[0]))) ||
				(0 == strcmp("*",handle[i].str)))  /* check for default*/
			{
				quit = handle[i].func_ptr(buffer, name);
				break;
			}
			++i;
		}
	}
	
	return (0);
}

