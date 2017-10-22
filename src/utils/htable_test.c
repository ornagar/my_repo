/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Htable                                     #################################
 *                                             ##########    ####       ########
 *  Tester                                     ########  ####  ##  ###  ########
 *                                             ########  ####  ##     ##########
 *  Or Nagar                                   ########  ####  ##  ###  ########
 *  28-07-2017                                 ##########    ####  ###  ######## 
 *  10:43:52                                   #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <string.h>					 /* strcmp()					  */
#include <ctype.h>					 /* tolower()					  */

#include "htable.h"					 /* all functions declerations	  */
#include "utils.h"					 /* Or's functions                */

#define DICT_WORDS							   (100000)
#define LINE_SIZE		    				   (50)
#define SIZE 								   (1000)

void SpellChecker(void);
void SimpleTest(void);
size_t HashFunc(const void *key);
int CmpFunc(const void *data1, const void *data2);
int IntCmpFunc(const void *data1, const void *data2);
int MyPrint(void *data, void *args);
size_t Hash (const void* word);
void MainLoop(hash_table_t *table);

int main(void)
{
	SpellChecker();
	return(EXIT_SUCCESS);
}

void SimpleTest(void)
{
	int data[] = {5, 25, 15, 35 ,51, 1521, 11, 21};
	hash_table_t *table = HTCreate(10, HashFunc, IntCmpFunc);
	void *check = NULL;
	
	printf("%lu\n", HTSize(table));
	HTInsert(table, &data[0]);
	HTInsert(table, &data[1]);
	HTInsert(table, &data[2]);
	HTInsert(table, &data[3]);
	HTInsert(table, &data[4]);
	HTInsert(table, &data[5]);
	HTInsert(table, &data[6]);
	HTInsert(table, &data[7]);
	
	printf("%lu\n", HTSize(table));
	
	printf("found: %d\n", *(int *)HTFind(table, &data));
		
	printf("MAX COL:%f\n", HTGetStatistics(table, MAX_COLLISIONS));
	printf("AV  COL:%f\n", HTGetStatistics(table, COLLISIONS_AVERAGE));
	printf("VARIANC:%f\n", HTGetStatistics(table, COLLISIONS_VARIANCE));
	
	check = HTRemove(table, &data);
	
	if (NULL == check)
	{
		puts("error");
	}
	
	printf("%lu\n", HTSize(table));
	
	HTDestroy(table);
}

void SpellChecker(void) 
{
	hash_table_t *table;
	char **runner;
	int i = 0;
	int j = 0;
	FILE *fp = NULL;
	
	char c[LINE_SIZE] = "hello";
	
	if (NULL == (table = HTCreate(1000, Hash, CmpFunc)))
	{
		PRINT_ERROR("HTCreate error");
		return;
	}
	
	if (NULL == (runner = malloc(sizeof(char *) * DICT_WORDS)))
	{
		PRINT_ERROR("malloc error");
	}
	
	while (i < DICT_WORDS)
	{
		if (NULL == (runner[i++] = malloc(LINE_SIZE)))
		{
			PRINT_ERROR("HTCreate error");
			return;
		}
	}
	
	if (NULL == (fp = fopen("/usr/share/dict/words", "r")))
	{
		PRINT_ERROR("fopen error");
		return;
	}
	
	i = 0;
	while(fgets(runner[i], LINE_SIZE, fp))
	{
		while(runner[i][j])
		{
			if (10 == runner[i][j])
			{
				runner[i][j] = '\0';
			}
			else
			{
				runner[i][j] = tolower(runner[i][j]);
			}
			++j;
		}
		j = 0;
		HTInsert(table, runner[i]);
		++i;
	}
	fclose(fp);
	
	printf("MAX COL:%f\n", HTGetStatistics(table, MAX_COLLISIONS));
	printf("AV  COL:%f\n", HTGetStatistics(table, COLLISIONS_AVERAGE));
	printf("VARIANCE:%f\n", HTGetStatistics(table, COLLISIONS_VARIANCE));
	printf("Size: %lu\n", HTSize(table));
	
	while (0 != strcmp("q", c))
	{
		i = scanf("%s", c);
		
		for(i = 0; '\0' != c[i]; ++i)
		{
			c[i] = tolower(c[i]);
		}

		if (NULL != (char *)HTFind(table, &c))
		{
			puts("Found");
		}
		else
		{
			puts("Not found");
		}
	}
	
	HTDestroy(table);
	i = 0;
	while (i < DICT_WORDS)
	{
		free(runner[i++]);
	}
	
	free(runner);
	
	return;
}

size_t HashFunc(const void *key)
{
	return (*(int *)key % 10);
}

int IntCmpFunc(const void *data1, const void *data2)
{
	return(*(int *)data1 == *(int *)data2);
}

int CmpFunc(const void *data1, const void *data2)
{
	return (!strcmp((char *)data1, (char *)data2));
}

int MyPrint(void *data, void *args)
{
	printf("%s\n", (char *)data);
	
	return (0);
}

size_t Hash(const void *data)
{
    unsigned long hash = 5381;
    unsigned char *str = (unsigned char *)data;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (hash % 1000);
}
