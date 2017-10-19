/******************************************************************************
 ws5_funcs.c includes Handle input to files funcions.
 
 22.05.17
 
 Or Nagar.
*******************************************************************************/
#include <stdio.h> 		 /* printf()     */
#include <stdlib.h>		 /* Exit_success */
#include <assert.h>		 /* assert() */

#include "utils.h"		 /* DBG          */

/*
 * Takes an input from the user and appends it
 * to the logger file.
 * Return Values:
 * 0 - for successfull return.
 * 1 - if file couldn't be opened.
 */
int HandleAppend(char *input, char *name)		
{
	FILE *fptr = NULL;
	
	assert(input);
	assert(name);
	
	if (NULL == (fptr = fopen(name, "a")))	/*opens the file in append mode	*/
	{
		DBG(fprintf(stderr, "error while opening file: aborting...\n");)
		return (1);
	}
	
	fputs(input, fptr);						/* appends input to EOF			*/
	fputs("\n", fptr);
	fclose(fptr);
	
	return (0);
}

/*
 * Exits the program safely.
 * Return Values:
 * 1 - to exit program.
 */
int HandleExit(char *input, char *name)
{
	return (1); 
}

/*
 * Counts the number of lines in the file.
 * Return Values:
 * 0 - for successfull return.
 * 1 - if file couldn't be opened.
 */
int HandleCount(char *input, char *name)
{
	FILE *fptr = NULL;
	char ch = '\0';
	int count = 0;
	
	assert(input);
	assert(name);
	
	if (NULL == (fptr = fopen(name, "r")))	/*opens the file in read mode	*/
	{
		DBG(fprintf(stderr, "error while opening file: aborting...\n");)
		return (1);
	}
	
	while(EOF != ch)								/*counts number of EOL	*/
	{
		ch = fgetc(fptr);
		if ('\n' == ch)
		{
			++count;
		}
	}
	fclose(fptr);
	
	printf("Number of lines is: %d\n", count);/*???*/
	
	return (0);
}

/*
 * Removes the file created by the program's run.
 * Return Values:
 * 0 - for successfull return.
 * 1 - if file couldn't be removed.
 */
int HandleRemove(char *input, char *name)
{
	int check = 0;
	
	assert(input);
	assert(name);
	
	check = remove(name);
	
	if(0 == check) 
	{
		printf("File deleted successfully\n");
	}
	else
	{
		printf("couldn't remove.....\n");
	}
	return (0);
}

/*
 * Adds the user's input to the begining of the file.
 * Return Values:
 * 0 - for successfull return.
 * 1 - if file couldn't be opened.
 */
int HandlePreppend(char *input, char *name)		
{
	FILE *fptr = NULL;
	FILE *ftmp = NULL;
	char ch = '\0';
	
	assert(input);
	assert(name);
	
	++input;
	
	if (NULL == (fptr = fopen(name, "r")))	/* opens the file in read mode	*/
	{
		DBG(fprintf(stderr, "error while opening file: aborting...\n");)
		return (1);
	}
	/*opens temp file in write mode*/
	if(NULL == (ftmp = fopen("temp.txt", "w")))
	{
		DBG(fprintf(stderr, "error while opening file: aborting...\n");)
		return (1);
	}
	
	fputs(input, ftmp);						/* copies input to temp file	*/
	fputs("\n", ftmp);
	
	while (1)								/* copies the file to temp file	*/
	{
		ch = fgetc(fptr);
		
		if (ch == EOF)
		{	
			break;
		}
		else
		{
			fputc(ch, ftmp);
		}
	}	
	
	fclose(fptr);
	if (NULL == (fptr = fopen(name, "w")))	/* opens the file in w mode		*/
	{
		DBG(fprintf(stderr, "error\n while opening file: aborting...\n");)
		return (1);
	}
	ch = '\0';
	
	fclose(ftmp);
	/*opens temp file in read mode*/
	if (NULL == (ftmp = fopen("temp.txt", "r")))
	{
		DBG(fprintf(stderr, "error while opening file: aborting...\n");)
		return (1);
	}
	
	while (1)								/* copies the temp to the file	*/
	{										/* rewriting it.				*/
		ch = fgetc(ftmp);
		
		if (ch == EOF)
		{	
			break;
		}
		else
		{
			fputc(ch, fptr);
		}
	}		
	
	fclose(fptr);
	fclose(ftmp);
	
	HandleRemove("", "temp.txt");
	
	return (0);
}
