#include <stdio.h> 		 /* printf()    */
#include <stdlib.h>		 /* Exit_success*/
#include <assert.h>		 /* assert()    */
#include <string.h>		 /* strlen()    */

#include "utils.h"

void PrintEnv(char **buf);
char **CopyLowEnv(char **env);
static void FreeEnv(char **env);

int main(int argc, char **argv, char **env)
{
	
	char **buffer = CopyLowEnv(env);
	
	PrintEnv(buffer);
	
	FreeEnv(buffer);
	
	return (EXIT_SUCCESS); 
}

/*
 * Prints a char **ptr as a multydimension array.
 */
void PrintEnv(char **env)
{
	assert(env);
	
	while (*env)
	{
		puts(*env);
		++env;
	}
	
	return;
}

/*
 * uses free() recursively to free dynamicly allocated memory
 * in a **ptr.
 */
void FreeEnv(char **env)
{
	char **copy = NULL;
	
	assert(env);
	
	copy = env;
	while (*copy)				/*while there are *pointers in the big one ** */
	{
		free(*copy);
		++copy;
	}
	
	free(env);
	
	return;
}

/*
 * copyes a src string to a given dest string replaceing 
 * upper case letters into lower case.
 */
static void StrToLow(char *dest, const char *src)
{
	char *copy = NULL;
	
	assert(dest);
	assert(src);
	
	copy = dest;
	
	while ('\0' != *src)			
	{
		if ('Z' >= *src && 'A' <= *src)
		{
			*copy = (*src + 32);
		}
		else
		{
			*copy = *src;
		}
		
		++copy;
		++src;
	}
	*copy = '\0';
	
	return;
}

/*
 * copyes the enviorment list into a dynamic  
 * allocated char **buffer converting upper into
 * lower case and returns a pointer to buffer.
 * WARNING: the function calls recursive malloc
 * FreeEnv() function should be used to free all allocated memory. 
 */
char **CopyLowEnv(char **env)
{
	char **buffer = NULL;
	char **buf_runner = NULL;
	char **env_runner = NULL;
	size_t size = 0;				
	
	assert(env);
	
	env_runner = env;
	
	while (*env_runner)					    /* a loop to check env's size     */
	{
		++env_runner;
	}
	
	size = env_runner - env;
	env_runner = env;
	
	/*allocate memory for the big block **pointer*/
	buffer = (char**)malloc((size+1)*sizeof(char*)); 
	if (NULL == buffer)
		{
			DBG(fprintf(stderr, "error\n");)
			return NULL;
		}
		
	buf_runner = buffer;
	
	while (*env_runner)						/* while there are *pointer in env*/
	{
		/*allocate memory for small *pointers.    */	
		*buf_runner = (char*)malloc((strlen(*env_runner)+1));
		if (NULL == *buf_runner)
		{
			DBG(fprintf(stderr, "error\n");)
			FreeEnv(buffer);
			return NULL;
		}
		
		StrToLow(*buf_runner, *env_runner);
		++buf_runner;
		++env_runner;
	}
	
	*buf_runner = NULL;
	
	return buffer;
}

