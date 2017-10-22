/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Dicount                                #################################
 *                                         ##########    ####       ########
 *  Functions definition                   ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  21-08-2017                             ##########    ####  ###  ######## 
 *  17:48:56                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>					/* printf()							*/
#include <stdlib.h>					/* system(), EXIT_SUCCESS			*/
#include <assert.h>					/* assert()							*/
#include <string.h>					/* strcmp()							*/
#include <pthread.h>				/* pthread_create()					*/
#include <sys/types.h>				/* open()							*/
#include <sys/stat.h>				/* fstat()							*/
#include <fcntl.h>					/* for mmap()						*/
#include <unistd.h>					/* for open()						*/
#include <sys/mman.h>				/* mmap()							*/

#include "../utils/utils.h"			/* Or's functions					*/

enum
{
	SUCCESS,
	FAILURE
};

/*
 * A struct containing a section of words_array 
 * and the size of it for each thread
 */
typedef struct
{
	unsigned char **thread_array;
	size_t limit;
	
} thread_struct_t;

void *ThreadSort(void *arg);
static int Compare(const void *data1, const void *data2);
static void Merge(char *base_l, char *base_r, char *temp,  size_t element_size,
				 size_t l_num_of_elements, size_t r_num_of_elements, 
				  int (*compar)(const void *data1, const void *data2));
static void Swap(void *a, void *b, size_t element_size);

int main(int argc, char *argv[])
{
	thread_struct_t *attr			= NULL;
	unsigned char	**words_array	= NULL;
	unsigned char	*runner			= NULL;
	unsigned char	*end 		 	= NULL;
	unsigned char 	*fptr			= NULL;
	struct stat 	s				= {0};
	pthread_t 		*thread_ids		= NULL;
	size_t 			thread_chunk	= 0;
	size_t 			lines			= 0;
	FILE 			*file 			= NULL;
	char			**temp			= NULL;
	char			*dictionary		= "/home/super29/svn/Proj/src/OS/words";
	char			*letter_file	= "/home/super29/svn/Proj/src/OS/sorted_dic";
	int 			num_of_threads  = 5;
	int 			fd				= 0;
	int 		  	status			= 0;
	int 			i				= 0;
	int 			j 				= 0;
	
	/* Number of thread_ids to create, if no argument given default is one */ 
	if (1 < argc)
	{
		num_of_threads = atoi(argv[1]);
	}
	
	/* Allocate thread_ids */
	thread_ids = calloc(sizeof(thread_ids), num_of_threads);
	if (NULL == thread_ids)
	{
		PRINT_ERROR("malloc error");
		return (FAILURE);
	}
	
	/* Open dictonary */
	fd = open(dictionary, O_RDWR);
	if (-1 == fd)
	{
		PRINT_ERROR("open error");
		free(thread_ids);
		return (FAILURE);
	}
	
	status = fstat(fd, &s);
	if (-1 == status)
	{
		PRINT_ERROR("fstat error");
		free(thread_ids);
		close(fd);
		return (FAILURE);
	}
	
	/* Map file to VM */
	fptr = mmap(NULL, s.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (MAP_FAILED == fptr)
	{
		PRINT_ERROR("mmap error");
		free(thread_ids);
		close(fd);
		return (FAILURE);
	}
	
	runner = fptr;
	end = fptr + s.st_size;
	
	/*calculate number of words (lines) and allocate pointers for each word */
	while (runner < end)
	{
		if ('\n' == *runner)
		{
			lines++;
		}
		++runner;
	}
	
	/* An array of pointers to words in dictionary */
	if (NULL == (words_array = calloc(lines, sizeof(char *))))
	{
		PRINT_ERROR("malloc error");
		free(thread_ids);
		return (FAILURE);
	}
	
	words_array[0] = fptr;
	for (i = 1, runner = fptr; 1; ++runner)
	{
		if ('\n' == *runner)
		{
			*runner = '\0';
			++runner;
			if (runner >= end)
			{
				break;
			}
			words_array[i] = runner;
			++i;
		}
	}
	
	/* Shuffle */
	srand(clock());
	for (i = 0; i < lines; ++i)
	{
		Swap(&words_array[i], &words_array[rand() % lines], sizeof(char *));
	}

	/* Size of words_array for each thread */
	thread_chunk = lines / num_of_threads;
	
	/* Allocate struct for each thread and assign them values */
	attr = calloc(sizeof(thread_struct_t), num_of_threads);
	if (NULL == attr)
	{
		PRINT_ERROR("malloc error");
		free(thread_ids);
		close(fd);
		return (FAILURE);
	}
	for (i = 0; i < num_of_threads; ++i)
	{
		attr[i].thread_array = words_array + i * thread_chunk;
		attr[i].limit = thread_chunk;
	}
	attr[i - 1].limit += lines % num_of_threads;
	
	/* Create threads and send them to work */
	for (i = 0; i < num_of_threads; ++i)
	{
		status = pthread_create(&thread_ids[i], NULL, ThreadSort, &attr[i]);
		if (0 != status)
		{
			PRINT_ERROR("pthread_create error");
			PRINT_ERROR("pthread_create error");
			free(thread_ids);
			free(attr);
			close(fd);
			for (j = 0; j < i; ++j)
			{
				pthread_cancel(thread_ids[j]);
			}
			return (1);
		}
	}
			
	/* Wait for thread_ids and collect them */
	for (i = 0; i < num_of_threads; ++i)
	{
		pthread_join(thread_ids[i], NULL);
		if (0 != status)
		{
			PRINT_ERROR("pthread_join error");
			free(thread_ids);
			free(attr);
			close(fd);
			return (1);
		}
	}
	
	
	/* temp is an attribute array for swaps and sorts */
	if (NULL == (temp = calloc(sizeof(char *), lines)))
	{
		PRINT_ERROR("pthread_join error");
		free(thread_ids);
		free(words_array);
		free(attr);
		close(fd);
		return (FAILURE);
	}
	
	/* Merge */	
	for (i = 1; i < num_of_threads; ++i)
	{
		Merge((char *)attr[0].thread_array, 
			(char *)attr[i].thread_array, (char *)temp, sizeof(char *), 
								attr[0].limit, attr[i].limit, Compare);
								
		attr[0].limit += attr[i].limit;
	}
	
	if (NULL == (file = fopen(letter_file, "w")))
	{
		PRINT_ERROR("fopen error");
		free(thread_ids);
		free(attr);
		close(fd);
		return (1);
	}
	
	while (i < lines)
	{
		fprintf(file, "%s\n", words_array[i]);
		++i;
	}
	
	/* Free resources */
	munmap(fptr, s.st_size);
	close(fd);
	free(words_array);
	free(thread_ids);
	free(temp);
	free(attr);
	fclose(file);

	return (EXIT_SUCCESS);
}

void *ThreadSort(void *arg)
{
	thread_struct_t *attr = arg;

	qsort(attr->thread_array, attr->limit, sizeof(char *), Compare);
	
	return (NULL);
}

static void Merge(char *base_l, char *base_r, char *temp,  size_t element_size,
				 size_t l_num_of_elements, size_t r_num_of_elements, 
				  int (*compar)(const void *data1, const void *data2))			
{
	char *l_runner	  = base_l;
	char *r_runner 	  = base_r;
	char *temp_runner = temp;
	char *l_end 	  = base_l + (element_size * l_num_of_elements);
	char *r_end  	  = base_r + (element_size * r_num_of_elements);

	while (l_runner < l_end && r_runner < r_end)
	{
		if (0 > compar(l_runner, r_runner))
		{
			memcpy(temp_runner, l_runner, element_size);
			l_runner = l_runner + element_size;
		}
		else 
		{
			memcpy(temp_runner, r_runner, element_size);
			r_runner = r_runner + element_size;
		}
		temp_runner = temp_runner + element_size;
	}
	
	/* Copy reminders (if exist) to temp_runner 				*/
	memcpy(temp_runner, l_runner, l_end - l_runner);
	memcpy(temp_runner, r_runner, r_end - r_runner);
	
	/* Copy temp to base								    */
	memcpy(base_l, temp, (element_size * (l_num_of_elements + 
														   r_num_of_elements)));
	
	return;
}

static int Compare(const void *data1, const void *data2)
{
	return(strcmp(*(char **)data1, *(char **)data2));
}

static void Swap(void *a, void *b, size_t element_size)
{
	size_t temp;
	memcpy(&temp, a, element_size);
	memcpy(a, b, element_size);
	memcpy(b, &temp, element_size);
}
