#include <stdio.h> 		 /*printf()*/
#include <stdlib.h>		 /*Exit_success*/
#include <assert.h>		 /*assert()*/
#include <ctype.h>
#include <string.h>
#include "ws2_string.h"
/*
 *Strlen takes a char pointer and returns its (size_t)length.
 */
size_t Strlen(const char *str)
{
	const char *copy = str;
	
	assert(str);
	
	while('\0' != *copy)
	{
		++copy;
	}
	
	return (copy - str);
}

/*
 *Strcmp takes two char pointers and returns
 *an integer 0 if they are equal, >0 or <0 if not
 *if not equal the integer represents the The differnce 
 *between the first unmatched characters.
 */
int Strcmp(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);
	
	while(*str2 == *str1 && '\0' != *str1)
	{
		++str1;
		++str2;
	}

	return (*str1 - *str2);
}

/*
 *Strcpy function takes two char arrays pointers
 *it copyies the source array to destination array
 ******************W A R N I N G*******************************
 ***DESTINATION ARRAY MUST BE EQUAL OR LARGER THAN SOURCE!!!***
 *************************************************************/
char *Strcpy(char *dest, const char *src)
{
	char *copy = dest;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	while ('\0' != *src)
	{
		*copy = *src;
		++copy;
		++src;
	}
	
	*copy = '\0';
	
	return (dest);
}

/*
 *Strncpy function takes two char arrays pointers and a size limitator.
 *it copyies the source array to destination array
 *until it reaches the end of one of them.
 */
char *Strncpy(char *dest, char *src, size_t size)
{
	char *copy = dest;
	char *dest_end = dest + size;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	while ('\0' != *src && copy < dest_end)			
	{
		*copy = *src;
		++src;
		++copy;
	}
	
	while (copy < dest_end)
	{
		*copy = '\0';
		++copy;
	}
		
	return (dest);
}

/*
 *Strcmp function takes two char pointers and returns
 *an integer 0 if they are equal, >0 or <0 if not
 *if not equal the integer represents the The differnce 
 *between the first unmatched characters.
 */
int Strcasecmp(char *str1, char *str2)
{
	int compare = 0;        
	
	assert(NULL != str1);
	assert(NULL != str2);
	
	while('\0' != *str1 || '\0' != *str2)
	{
		if(91 > *str1 && 64 < *str1 &&				   /*if str1 is uppercase */
		     91 < *str2 && 64 > *str2)				   /*and str2 is lowercase*/
		{
			compare = (*str1 + 32) - *str2;
			if(0 != compare)
			{
				break;
			}					
		}
		else if(91 < *str1 && 64 > *str1 &&			  /*if str2 is uppercase */
		          91 > *str2 && 64 < *str2)			  /*if str1 is lowercase */
		{
			compare = *str1 - (*str2 +32);
			if(0 != compare)
			{
				break;
			}			
		}
		else										/*if both are of same case*/
		{
			compare = *str1 - *str2;
			if(0 != compare)
			{
				break;
			}			
		}			
		++str1;
		++str2;
	}
	
	return (compare);
}

/*
 * Strchr returns a pointer to the first occurrence
 * of the character ch in the string str.
 */
char *Strchr(const char *str, int ch)
{
	assert(str);
	
	while (ch != *str && *str != '\0') 
	{
		++str;
	}
	
	if(0 == (*str - ch))						/*if ch is null byte*/
	{
   		return ((char*)str);	
	}

	return (NULL);
}

/*
 * Strdup duplicates a given string to a new assigned char pointer.
 * It is the user's responsability to free the allocated memory using free().
 */
char *Strdup(const char *str)
{
	size_t size = (Strlen(str)+1);
	char *start = NULL;
	start = (char*)malloc(size*sizeof(char));
	if (start == NULL)
	{
		return ((char*)EXIT_FAILURE);
	}

	assert(str);
	assert(start);
	
	
	memcpy(start, str, size);
	
	return (start);
}

/*
 * Strcat takes a pointer src and appends it to the end of dest
 * overwriting the terminating null byte and then adds a new one 
 * at the end of the string.
 */
char *Strcat(char *dest, const char *src)
{
	char *copy = dest;
	
	assert(dest);
	assert(src);
	
	while ('\0' != *copy) 	/*runs to null byte of dest*/
	{
		++copy;
	}								
					
	while ('\0' != *src)	/*copies src to end of dest*/
	{
		*copy = *src;
		++copy;				/* CHANGE WITH STRCPY */
		++src;
	}

	*copy = '\0';			/*adds a null byte to dest*/
	
	return (dest);
}
		
/*
 * Strncat takes a pointer src and appends -n- bytes of it to 
 * the end of dest overwriting the terminating null byte and then
 * adds a new one at the end of the string.
 */
char *Strncat(char *dest, const char *src, size_t size)
{
	char *copy = dest;
	
	assert(dest);
	assert(src);
	
	while ('\0' != *copy)			/*runs to null byte of dest*/
	{
		++copy;
	}
	
	while (('\0' != *src) &&		/*copies -n- bytes from src to end of dest*/
	             (0 < size))  
	{
		*copy = *src;
		++copy;
		++src;
		--size;
	}
	
	*copy = '\0';					/*adds a null byte to dest*/
	
	return (dest);
}	
	
/*
 * Strstr checks if needle is a substring of haystack.
 */
char *Strstr(const char *haystack, const char *needle)
{
	const char *ptr_n = NULL;
	const char *ptr_h = NULL;
	
	assert(haystack);
	assert(needle);
	while ('\0' != *haystack)		
	{
		if (0 == (*haystack - *needle))					/*if the first char*/
		{											    /*in src is equal  */
   			ptr_n = needle;
   			ptr_h = haystack;
   			
   			while (*ptr_n == *ptr_h && '\0' != ptr_n)	/*checks equality  */
   			{											/*untill null byte */
   				++ptr_n;
   				++ptr_h;
   				
   				if ('\0' == *ptr_n)
   				{
   					return (char*)(haystack);
   				}
   			}
		}
		++haystack;
	}
	
	return (NULL);
}

/*
 * Strtok
 */
char *Strtok(char *str, const char *delim)
{
	static char *token_start = NULL;
	static char *token_end = NULL;
	
	if (str != NULL)
	{
		token_start = str;
		token_end  = str;
	}
	else
	{
		token_start = token_end;
	}
	
	if (*token_start)
	{
		while (NULL != strchr(delim, *token_start))
		{
			++token_start;
		}
		
		token_end = token_start + 1;
		
		while ((NULL == (strchr(delim, *token_end))) || (*token_end = '\0'))
		{
			++token_end;
		}
		
		*token_end = '\0';
		++token_end;
	
	
		return (token_start);
	}
	
	return (NULL);
}


/*
 * RmSpaces takes a string and removes spaces from the begining 
 * and the end of the string, and removes spaces in the middle 
 * of the string if there is more than one.
 */
void RmSpaces(char *str)
{
	char *read  = str;
	char *write = str;
	
	assert(str);
	
	/* Skip leading blanks */
	while (isspace(*read))
	{
		++read;
	}
	
	while ('\0' != *read)
	{
		*write = *read;
		++read;
		
		/* If two consecutive blanks */
		if ((isspace(*read) && isspace(*write)))
		{
			while (isspace(*read))	/* Skip blanks from the second blank */
			{
				++read;
			}
		}
		
		++write;
	}
	
	/* If last char is blank, delete it */
	if ((write > str) && isspace(*(write-1)))
	{
		--write;
	}

	*write = '\0';
	
	return;
}


